#include "Spritter/Graphics/Font.h"

#include <cassert>
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
}
