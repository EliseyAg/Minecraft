#include "Input.hpp"
#include <algorithm>

namespace Game {
    bool Input::m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST)] = {};

    void Input::setFalse()
    {
        for (int i = 0; i < static_cast<size_t>(KeyCode::KEY_LAST); i++)
        {
            Input::m_keys_pressed[i] = false;
        }
    }

    bool Input::IsKeyPressed(const KeyCode key_code)
    {
        return m_keys_pressed[static_cast<size_t>(key_code)];
    }

    void Input::PressKey(const KeyCode key_code)
    {
        m_keys_pressed[static_cast<size_t>(key_code)] = true;
    }

    void Input::ReleaseKey(const KeyCode key_code)
    {
        m_keys_pressed[static_cast<size_t>(key_code)] = false;
    }
}