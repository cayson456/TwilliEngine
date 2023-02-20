#pragma once
#include "Components/Component.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"

namespace TwilliEngine
{
class GraphicsComponent : public Component
{
public:
    GraphicsComponent() {}
    GraphicsComponent(std::string_view name) : Component(name) {}
    ~GraphicsComponent() {}

    Model::Key mModel;
    ShaderProgram::Key mShaderProgram;
};

} // namespace TwilliEngine