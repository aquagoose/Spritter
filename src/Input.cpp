#include "Spritter/Input.h"

namespace Spritter
{
    void Input::Update()
    {
        _keysPressed.clear();
        _buttonsPressed.clear();

        _deltaMousePos = Math::Vector2f::Zero();
    }
}
