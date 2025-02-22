#pragma once

#include <string>

namespace Spritter::Graphics
{
    enum class ShaderStage
    {
        Vertex,
        Pixel
    };

    struct ShaderAttachment
    {
        ShaderStage Stage;
        std::string Code;
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;
    };
}
