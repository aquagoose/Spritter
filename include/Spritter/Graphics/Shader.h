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

    enum class AttributeType
    {
        Float,
        Float2,
        Float3,
        Float4
    };

    struct ShaderAttribute
    {
        const char* Name;
        AttributeType Type;
        uint32_t ByteOffset;
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;
    };
}
