#pragma once

#include <SDL3/SDL_keycode.h>

#include "Spritter/Input.h"

namespace Spritter::SDLUtils
{
    Key KeycodeToKey(SDL_Keycode keycode);
}
