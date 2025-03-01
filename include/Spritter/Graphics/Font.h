#pragma once

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicsDevice.h"

namespace Spritter::Graphics
{
    class Font
    {
        inline static FT_Library _library{};
        inline static unsigned int _libraryReferences{};

        GraphicsDevice& _device;
        FT_Face _face{};

    public:
        Font(GraphicsDevice& device, const std::string& path);
        ~Font();
    };
}
