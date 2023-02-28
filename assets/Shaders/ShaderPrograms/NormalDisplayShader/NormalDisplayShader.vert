#include "../../InputLayouts/default.hlsl"
#include "../../ConstantBuffers/EntityTransform.hlsl"

_c_EntityTransform(0);

VertexIn main(VertexIn vin)
{
    VertexIn output;

    float4 world_pos = mul(float4(vin.pos, 1.0f), model);

    output.pos = world_pos.xyz;
    output.normal = normalize(mul(float4(vin.normal, 0.0f), trans_inv_model).xyz);
    output.uv = vin.uv;

    return output;
}
