#pragma once

#include <unordered_set>

namespace Spritter
{
    enum class Key
    {
        Unknown = 0,

        Backspace = '\b',
        Tab = '\t',
        Enter = '\r',
        Return = Enter,
        Escape = '\x1B',

        Space = ' ',
        Hash = '#',
        Apostrophe = '\'',

        Comma = ',',
        Minus = '-',
        Period = '.',
        Dot = Period,
        ForwardSlash = '/',

        Num0 = '0',
        Num1 = '1',
        Num2 = '2',
        Num3 = '3',
        Num4 = '4',
        Num5 = '5',
        Num6 = '6',
        Num7 = '7',
        Num8 = '8',
        Num9 = '9',

        Semicolon = ';',
        Equals = '=',

        LeftBracket = '[',
        Backslash = '\\',
        RightBracket = ']',

        Backquote = '`',
        GraveAccent = Backquote,
        Backtick = Backquote,

        A = 'A',
        B = 'B',
        C = 'C',
        D = 'D',
        E = 'E',
        F = 'F',
        G = 'G',
        H = 'H',
        I = 'I',
        J = 'J',
        K = 'K',
        L = 'L',
        M = 'M',
        N = 'N',
        O = 'O',
        P = 'P',
        Q = 'Q',
        R = 'R',
        S = 'S',
        T = 'T',
        U = 'U',
        V = 'V',
        W = 'W',
        X = 'X',
        Y = 'Y',
        Z = 'Z',

        Delete = '\x7F',

        Insert = 256,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,

        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        Keypad0,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,
        KeypadDecimal,
        KeypadDivide,
        KeypadMultiply,
        KeypadSubtract,
        KeypadAdd,
        KeypadEnter,
        KeypadEqual,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,

        Menu
    };

    enum class MouseButton
    {
        Unknown,

        Left,
        Middle,
        Right,

        Button3,
        Button4,
        Button5,
        Button6,
        Button7,
        Button8,
        Button9,
    };

    class Input
    {
        inline static std::unordered_set<Key> _keysDown;
        inline static std::unordered_set<Key> _keysPressed;

        inline static std::unordered_set<MouseButton> _buttonsDown;
        inline static std::unordered_set<MouseButton> _buttonsPressed;

    public:
        /// Check if the given key is currently being held down.
        /// @param key The key to check.
        /// @return True, if the key is currently being held down.
        static bool IsKeyDown(const Key key)
        {
            return _keysDown.count(key);
        }

        /// Check if the given key was pressed on this frame.
        /// @param key The key to check.
        /// @return True, if the key was pressed on this frame.
        static bool IsKeyPressed(const Key key)
        {
            return _keysPressed.count(key);
        }

        /// Check if the given mouse button is currently being held down.
        /// @param button The mouse button to check.
        /// @return True, if the mouse button is currently being held down.
        static bool IsMouseButtonDown(const MouseButton button)
        {
            return _buttonsDown.count(button);
        }

        /// Check if the given mouse button was pressed on this frame.
        /// @param button The mouse button to check.
        /// @return True, if the mouse button was pressed on this frame.
        static bool IsMouseButtonPressed(const MouseButton button)
        {
            return _buttonsPressed.count(button);
        }

        /// Set the given key's state to down.
        /// @param key The key to set.
        static void PushKeyDown(const Key key)
        {
            _keysDown.emplace(key);
            _keysPressed.emplace(key);
        }

        /// Set the given key's state to up.
        /// @param key The key to set.
        static void PushKeyUp(const Key key)
        {
            _keysDown.erase(key);
            _keysPressed.erase(key);
        }

        /// Intended for internal use only.
        static void Update();
    };
}
