#include "precompiled.hpp"
#include "ResourceLoader.hpp"

#include "Singletons/D3D/D3D.hpp"
#include "Resources/Shader/VertexShader.hpp"
#include "Resources/Shader/PixelShader.hpp"
#include "Resources/Shader/Computeshader.hpp"

#include "Utils/FileReader.hpp"

namespace
{
    const std::string TWM_EXT = ".twm";
    const uint32_t FILE_LAYOUT_RELEASE_NUMBER = 2;
    const std::string END_OF_FILE = ".twm END OF FILE";

    const std::string RESOURCE_PATH = "../assets/";
    const std::string SHADER_PATH = RESOURCE_PATH + "Shaders/";
    const std::string MODEL_PATH = RESOURCE_PATH + "Models/";
    const std::string SHADER_PROGRAM_PATH = SHADER_PATH + "ShaderPrograms/";
    const std::string CONSTANT_BUFFER_PATH = SHADER_PATH + "ConstantBuffers/";
    const std::string STRUCTURED_BUFFER_PATH = SHADER_PATH + "StructuredBuffers/";
}

namespace FileExtensions
{
    const std::string VERTEX_SHADER_EXT = ".vert";
    const std::string PIXEL_SHADER_EXT = ".pixel";
    const std::string COMPUTE_SHADER_EXT = ".comp";
}

namespace TwilliEngine
{

void ResourceLoader::LoadAllAssetsInFolder()
{
    LoadAllModels();
    LoadAllConstantBuffers();
    LoadAllStructuredBuffers();
    LoadAllShaderPrograms();
}

void ResourceLoader::UnloadAllAssets()
{
}

    // NOTE: Is it bad that im reading the stuff into a buffer, then decompressing it
    // into another buffer?
    // Why am I even compressing/decompressing this loool
Model::Key ResourceLoader::LoadModel(const std::filesystem::path& path)
{
        // Make sure floats are 32-bit
    static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);

    FileReader model_file(path, std::ios_base::binary);

    if (!model_file.mFileStream.good()) {
        err::LogError("Error loading model, unable to read file: ", path);
        return Model::NullKey;
    }

    // Model Layout Header :
    /////////////////////////////////////////////////////////////////
    std::string twm_string = model_file.GetString(4);

        // 00-03: ".twm"
    if (TWM_EXT.compare(twm_string) != 0) {
        err::LogError("Error loading model, file is not a TWM file ", path);
        return Model::NullKey;
    }

        // 04-07: File Layout Release Version Number
    if (model_file.GetValue<uint32_t>() != FILE_LAYOUT_RELEASE_NUMBER) {
        err::LogError("Error loading model, incorrect file layout number ", path);
        return Model::NullKey;
    }

    Model::Key new_model = Model::Create(path.filename().stem().string());

        // 08-11: # of Meshes (uint32_t)
    uint32_t num_meshes = 0;
    model_file.GetBytes(&num_meshes);

        // 12: Byte Boolean determining if model has a skeleton mesh
    model_file.GetBytes(&new_model->mHasSkeleton);

        // 13-15 RESERVED
    model_file.SkipBytes(3);

    // Skeleton Mesh
    /////////////////////////////////////////////////////////////////
    if (new_model->mHasSkeleton) {
        // Unimplemented
    }

    // Meshes
    /////////////////////////////////////////////////////////////////
    for (std::size_t i = 0; i < num_meshes; ++i) {
        std::string mesh_name(path.filename().string() + ".Mesh." + std::to_string(i));
        Mesh::Key new_mesh = Mesh::Create(mesh_name);

            // 00-07 - Num Verts (uint64_t)
        uint64_t num_verts_;
        model_file.GetBytes(&num_verts_);

        size_t num_verts = static_cast<size_t>(num_verts_);

        new_mesh->mHasVertexAttribute[Mesh::VertexAttributeType::Position] = true;

            // 08-11 Byte Bools determining if vertex attributes exist
        model_file.GetBytes(&new_mesh->mHasVertexAttribute[1], 4);

            // 12 - Byte Bool determining if deformer exists
        model_file.GetBytes(&new_mesh->mHasDeformer);

            // 13-15 RESERVED
        model_file.SkipBytes(3);

            //  All Vertices (3 floats)
        std::vector<float> vertices(num_verts * 3);
        model_file.GetBytes(vertices.data(), sizeof(float) * num_verts * 3);

        new_mesh->CreateVertexBuffer(Mesh::VertexAttributeType::Position, vertices.data(), num_verts);
        
            // All normals (12 bytes each) (3 floats)
        if (new_mesh->mHasVertexAttribute[Mesh::VertexAttributeType::Normal]) {
            std::vector<float> normals(num_verts * 3);
            model_file.GetBytes(normals.data(), sizeof(float) * num_verts * 3);

            new_mesh->CreateVertexBuffer(Mesh::VertexAttributeType::Normal, normals.data(), num_verts);
        }

            // All UVs (12 bytes each) (3 floats)
        if (new_mesh->mHasVertexAttribute[Mesh::VertexAttributeType::UV]) {
            std::vector<float> uvs(num_verts * 2);
            model_file.GetBytes(uvs.data(), sizeof(float) * num_verts * 2);

            new_mesh->CreateVertexBuffer(Mesh::VertexAttributeType::UV, uvs.data(), num_verts);
        }

        // All tangents (12 bytes each) (3 floats)
        if (new_mesh->mHasVertexAttribute[Mesh::VertexAttributeType::Tangent]) {
            std::vector<float> tangents(num_verts * 2);
            model_file.GetBytes(tangents.data(), sizeof(float) * num_verts * 3);

            new_mesh->CreateVertexBuffer(Mesh::VertexAttributeType::Tangent, tangents.data(), num_verts);
        }

        // All binormals (12 bytes each) (3 floats)
        if (new_mesh->mHasVertexAttribute[Mesh::VertexAttributeType::Binormal]) {
            std::vector<float> binormals(num_verts * 2);
            model_file.GetBytes(binormals.data(), sizeof(float) * num_verts * 3);

            new_mesh->CreateVertexBuffer(Mesh::VertexAttributeType::Binormal, binormals.data(), num_verts);
        }

        // ALl indicies
        uint64_t num_indices = 0;
        model_file.GetBytes(&num_indices);
        std::vector<uint32_t> indices(static_cast<size_t>(num_indices));
        model_file.GetBytes(indices.data(), static_cast<size_t>(num_indices) * sizeof(uint32_t));

        new_mesh->CreateIndexBuffer(indices.data(), static_cast<uint32_t>(num_indices));
        new_mesh->mNumIndices = static_cast<uint32_t>(num_indices);

        new_mesh->Build();
        new_model->AppendMesh(new_mesh);
    }

    // Skeleton Mesh Clusters and Blending Weights
    /////////////////////////////////////////////////////////////////
    if (new_model->mHasSkeleton) {
        // UNIMPLEMENTED
    }

    // Animation Data
    /////////////////////////////////////////////////////////////////
    uint32_t num_animations;
    model_file.GetBytes(&num_animations);

    for (uint32_t i = 0; i < num_animations; ++i) {
        // UNIMPLEMENTED
    }


    // FOOTER
    /////////////////////////////////////////////////////////////////
    if (model_file.GetString(16) != END_OF_FILE) {
        err::LogError("Error loading model, did not read end of file footer: ", path);
        
        new_model.Destroy();
        return Model::NullKey;
    }

    new_model->Build();
    return new_model;
}


// Grabs all the shaders in a folder and compiles them into one entire shader pipeline
ShaderProgram::Key ResourceLoader::LoadShaderProgram(const std::filesystem::path& path)
{
    std::filesystem::directory_iterator folder(path);

    // Find all files in folder
    bool b_vertex = false;
    bool b_pixel = false;
    bool b_compute = false;

    std::filesystem::path vertex_path;
    std::filesystem::path pixel_path;
    std::filesystem::path compute_path;

    for (auto &file : folder) 
    {
        std::string ext = file.path().extension().string();

        if (ext == FileExtensions::VERTEX_SHADER_EXT) {
            vertex_path = file.path();
            b_vertex = true;
        }

        else if (ext == FileExtensions::PIXEL_SHADER_EXT) {
            pixel_path = file.path();
            b_pixel = true;
        }

        else if (ext == FileExtensions::COMPUTE_SHADER_EXT) {
            compute_path = file.path();
            b_compute = true;
        }
    }

    bool is_valid_shader_program = (b_vertex && b_pixel) || b_compute;

    if (!is_valid_shader_program) {
        err::LogError("Invalid shaders in shader program: ", path);
        return ShaderProgram::NullKey;
    }

    ShaderProgram::Key shader_program = ShaderProgram::Create(path.filename().string());

    if (b_vertex) {
        VertexShader::Key vertex_shader = VertexShader::Create(vertex_path.filename().string());
        
        if (!vertex_shader->Build(vertex_path)) {
            err::LogError("Unable to create vertex shader: ", vertex_path);
            vertex_shader.Destroy();
        }
        else
            shader_program->AttachVertexShader(vertex_shader);
    }

    if (b_pixel) {
        PixelShader::Key pixel_shader = PixelShader::Create(pixel_path.filename().string());
        
        if (!pixel_shader->Build(pixel_path)) {
            err::LogError("Unable to create pixel shader: ", pixel_path);
            pixel_shader.Destroy();
        }
        else
            shader_program->AttachPixelShader(pixel_shader);
    }

    if (b_compute) {
        ComputeShader::Key compute_shader = ComputeShader::Create(compute_path.filename().string());
        
        if (!compute_shader->Build(compute_path)) {
            err::LogError("Unable to create compute shader shader: ", compute_path);
            compute_shader.Destroy();
        }
        else
            shader_program->AttachComputeShader(compute_shader);
    }

    if (!shader_program->Build()) {
        shader_program.Destroy();
        err::LogError("Unable to create shader program: ", path.filename());
        return ShaderProgram::NullKey;
    }

    return shader_program;
}

D3DBuffer::Key ResourceLoader::LoadConstantBuffer(const std::filesystem::path &filepath)
{
    std::ifstream in_file(filepath);
    std::stringstream str_stream;

        // Read it into a string stream to find meta data
    str_stream << in_file.rdbuf();
    std::string file_buffer = str_stream.str();

        // Find name of the constant buffer to match it with the corresponding struct
    const std::string search_byte_width = "// byte_width: ";
    size_t search_pos = file_buffer.find(search_byte_width) + search_byte_width.length();
    size_t search_end = file_buffer.find('\n', search_pos);

    std::string byte_width = file_buffer.substr(search_pos, search_end - search_pos);

        // Find name of the constant buffer to match it with the corresponding struct
    const std::string search_name = "// name: ";
    search_pos = file_buffer.find(search_name) + search_name.length();
    search_end = file_buffer.find('\n', search_pos);

    std::string name = file_buffer.substr(search_pos, search_end - search_pos);

    D3DBuffer::Key buffer = D3DBuffer::Create(name);
    if (buffer->Build(static_cast<UINT>(std::stoi(byte_width))))
        return buffer;

    buffer.Destroy();
    return D3DBuffer::NullKey;
}

StructuredBuffer::Key ResourceLoader::LoadStructuredBuffer(const std::filesystem::path& filepath)
{
    std::ifstream in_file(filepath);
    std::stringstream str_stream;

        // Read it into a string stream to find meta data
    str_stream << in_file.rdbuf();
    std::string file_buffer = str_stream.str();

        // Find the byte width of the structured buffer
    const std::string search_byte_width = "// byte_width: ";
    size_t search_pos = file_buffer.find(search_byte_width) + search_byte_width.length();
    size_t search_end = file_buffer.find('\n', search_pos);

    std::string byte_width = file_buffer.substr(search_pos, search_end - search_pos);

        // Find name of the structured buffer to match it with the corresponding struct
    const std::string search_name = "// name: ";
    search_pos = file_buffer.find(search_name) + search_name.length();
    search_end = file_buffer.find('\n', search_pos);

    std::string name = file_buffer.substr(search_pos, search_end - search_pos);

        // Find num of elements of the structured buffer
    const std::string search_num_elements = "// num_elements: ";
    search_pos = file_buffer.find(search_num_elements) + search_num_elements.length();
    search_end = file_buffer.find('\n', search_pos);

    std::string num_elements = file_buffer.substr(search_pos, search_end - search_pos);

    StructuredBuffer::Key buffer = StructuredBuffer::Create(name);
    if (buffer->Build(static_cast<UINT>(std::stoi(byte_width)), std::stoi(num_elements)))
        return buffer;

    buffer.Destroy();
    return StructuredBuffer::NullKey;
}

void ResourceLoader::LoadAllModels()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(MODEL_PATH)) {
        if (file.path().extension() == ".twm") {
            LoadModel(file);
        }
    }
}

void ResourceLoader::LoadAllShaderPrograms()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(SHADER_PROGRAM_PATH)) {
        if (file.is_directory()) {
            LoadShaderProgram(file);
        }
    }
}

void ResourceLoader::LoadAllConstantBuffers()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(CONSTANT_BUFFER_PATH)) {
        if (file.path().extension() == ".hlsl") {
            LoadConstantBuffer(file);
        }
    }
}

void ResourceLoader::LoadAllStructuredBuffers()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(STRUCTURED_BUFFER_PATH)) {
        if (file.path().extension() == ".hlsl") {
            LoadStructuredBuffer(file);
        }
    }
}
}
