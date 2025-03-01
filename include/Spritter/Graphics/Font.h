#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicsDevice.h"

#define SP_FONT_TEXTURE_SIZE 1024

namespace Spritter::Graphics
{
    class Font
    {
        inline static FT_Library _library{};
        inline static unsigned int _libraryReferences{};

        struct Character
        {
            int TextureIndex{};
            Math::Rectangle Source;
            Math::Vector2i Bearing;
            int Advance{};
        };

        struct CharSize
        {
            char Char;
            unsigned int Size;
        };

        GraphicsDevice& _device;
        FT_Face _face{};

        std::unordered_set<CharSize, Character> _characterMap;
        std::vector<std::unique_ptr<Texture>> _textures;

    public:
        Font(GraphicsDevice& device, const std::string& path);
        ~Font();

    private:
        Character CreateCharacter(char c, unsigned int size);
    };
}
