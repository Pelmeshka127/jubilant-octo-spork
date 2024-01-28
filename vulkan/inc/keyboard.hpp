#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "object.hpp"
#include "window.hpp"

namespace Vulkan
{

//-------------------------------------------------------------------------------//

class Keyboard
{
    public:

    struct KeyMappings {
        int MoveLeft        = GLFW_KEY_A;
        int MoveRight       = GLFW_KEY_D;
        int MoveForward     = GLFW_KEY_W;
        int MoveBackward    = GLFW_KEY_S;
        int MoveUp          = GLFW_KEY_E;
        int MoveDown        = GLFW_KEY_Q;
        int LookLeft        = GLFW_KEY_LEFT;
        int LookRight       = GLFW_KEY_RIGHT;
        int LookUp          = GLFW_KEY_UP;
        int LookDown        = GLFW_KEY_DOWN;
    };  

    void MoveInPlainXZ(GLFWwindow* windo, float dt, Object& object);

    KeyMappings keys{};

    float move_speed_{9.f};

    float look_spped_{3.f};

};

//-------------------------------------------------------------------------------//

} // end of Vulkan namespace

#endif