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

    enum class UniformType
    {
        ConstantBuffer,
        Texture
    };

    struct ShaderUniform
    {
        UniformType Type;
        std::string Name;
        uint32_t BufferSize;
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;
    };
}
