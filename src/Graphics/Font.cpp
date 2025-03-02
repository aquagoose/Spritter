#include "Spritter/Graphics/Font.h"

#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

#define FT_CHECK(Operation) {\
    FT_Error err = Operation;\
    if (err != FT_Err_Ok)\
        throw std::runtime_error("FreeType operation failed.");\
}

namespace Spritter::Graphics
{
    Font::Font(GraphicsDevice& device, const std::string& path) : _device(device)
    {
        assert(_library == nullptr ? _libraryReferences == 0 : false);

        if (!_library)
        {
            FT_CHECK(FT_Init_FreeType(&_library));
            _libraryReferences++;
        }

        FT_CHECK(FT_New_Face(_library, path.c_str(), 0, &_face));

        _textures.push_back(_device.CreateTexture(SP_FONT_TEXTURE_SIZE, SP_FONT_TEXTURE_SIZE, PixelFormat::R8G8B8A8_UNorm, nullptr));
    }

    Font::~Font()
    {
        _libraryReferences--;
        if (_libraryReferences == 0)
        {
            FT_CHECK(FT_Done_FreeType(_library));
            _library = nullptr;
        }
    }

    void Font::Draw(TextureBatcher& batcher, const Math::Vector2f& position, const std::string& text,
        uint32_t size)
    {
        const std::u32string str(text.begin(), text.end());

        for (const auto c : str)
        {
            Character character = GetCharacter(c, size);
        }

        batcher.Draw(_textures[0].get(), position);
    }

    Font::Character Font::GetCharacter(const uint32_t c, const uint32_t size)
    {
        CharSize chr = { c, size };
        if (auto pos = _characterMap.find(chr); pos != _characterMap.end())
            return pos->second;

        std::cout << "Creating character" << std::endl;

        FT_CHECK(FT_Set_Pixel_Sizes(_face, 0, size));
        FT_CHECK(FT_Load_Char(_face, c, FT_LOAD_RENDER));

        const FT_GlyphSlot glyph = _face->glyph;
        const FT_Bitmap bitmap = glyph->bitmap;

        const size_t texIndex = _textures.size() - 1;
        const Math::Size texSize = { static_cast<int32_t>(bitmap.width), static_cast<int32_t>(bitmap.rows) };
        const Math::Vector2i bearing = { glyph->bitmap_left, glyph->bitmap_top };
        const int32_t advance = static_cast<int32_t>(glyph->advance.x >> 6);

        if (_currentPosition.X + texSize.Width >= SP_FONT_TEXTURE_SIZE)
        {
            _currentPosition.X = 0;
            _currentPosition.Y += static_cast<int32_t>(_maxHeightOnThisLine);
            _maxHeightOnThisLine = 0;
        }

        if (size > _maxHeightOnThisLine)
            _maxHeightOnThisLine = size;

        const Math::Rectangle source = { _currentPosition, texSize };

        // Convert to RGBA bitmap.
        const auto bytes = new uint8_t[texSize.Width * texSize.Height * 4];
        for (size_t y = 0; y < texSize.Height; y++)
        {
            for (size_t x = 0; x < texSize.Width; x++)
            {
                const size_t pos = y * texSize.Width + x;
                bytes[(pos * 4) + 0] = 255;
                bytes[(pos * 4) + 1] = 255;
                bytes[(pos * 4) + 2] = 255;
                bytes[(pos * 4) + 3] = bitmap.buffer[pos];
            }
        }

        _textures[texIndex]->Update(source, bytes);

        delete bytes;

        _currentPosition.X += texSize.Width;

        Character character
        {
            texIndex,
            source,
            bearing,
            advance
        };

        _characterMap.emplace(chr, character);

        return character;
    }
}
