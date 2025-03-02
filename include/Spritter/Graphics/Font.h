#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicsDevice.h"
#include "SpriteRenderer.h"

#define SP_FONT_TEXTURE_SIZE 1024

namespace Spritter::Graphics
{
    class Font
    {
        inline static FT_Library _library{};
        inline static unsigned int _libraryReferences{};

        struct Character
        {
            size_t TextureIndex{};
            Math::Rectangle Source;
            Math::Vector2i Bearing;
            int32_t Advance{};
        };

        struct CharSize
        {
            uint32_t Char;
            uint32_t Size;

            bool operator ==(const CharSize& other) const
            {
                return Char == other.Char && Size == other.Size;
            }
        };

        struct CharSizeHash
        {
            std::size_t operator()(const CharSize& c) const
            {
                return static_cast<std::size_t>(c.Char) | static_cast<std::size_t>(c.Size << 32);
            }
        };

        GraphicsDevice& _device;
        FT_Face _face{};

        std::unordered_map<CharSize, Character, CharSizeHash> _characterMap;
        std::vector<std::unique_ptr<Texture>> _textures;

        Math::Vector2i _currentPosition{};
        uint32_t _maxHeightOnThisLine{};

    public:
        Font(GraphicsDevice& device, const std::string& path);
        ~Font();

        void Draw(SpriteRenderer& batcher, const Math::Vector2f& position, const std::string& text, uint32_t size,
                  const Math::Color& color = Math::Color::White());

    private:
        Character GetCharacter(uint32_t c, uint32_t size);
    };
}
