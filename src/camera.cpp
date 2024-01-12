#include "../inc/camera.hpp"

#include <cassert>
#include <limits>

namespace Vulkan
{

//-------------------------------------------------------------------------------//

void Camera::SetOrthographProjection(float left, float right, float top, float bottom, float near, float far) 
{
    projection_matrix_ = glm::mat4{1.0f};
    projection_matrix_[0][0] = 2.f / (right - left);
    projection_matrix_[1][1] = 2.f / (bottom - top);
    projection_matrix_[2][2] = 1.f / (far - near);
    projection_matrix_[3][0] = -(right + left) / (right - left);
    projection_matrix_[3][1] = -(bottom + top) / (bottom - top);
    projection_matrix_[3][2] = -near / (far - near);
}

//-------------------------------------------------------------------------------//
 
void Camera::SetPerspectiveProjection(float fovy, float aspect, float near, float far) 
{
    assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
    const float tanHalfFovy = tan(fovy / 2.f);
    projection_matrix_ = glm::mat4{0.0f};
    projection_matrix_[0][0] = 1.f / (aspect * tanHalfFovy);
    projection_matrix_[1][1] = 1.f / (tanHalfFovy);
    projection_matrix_[2][2] = far / (far - near);
    projection_matrix_[2][3] = 1.f;
    projection_matrix_[3][2] = -(far * near) / (far - near);
}

//-------------------------------------------------------------------------------//

void Camera::SetViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up) 
{
    const glm::vec3 w{glm::normalize(direction)};
    const glm::vec3 u{glm::normalize(glm::cross(w, up))};
    const glm::vec3 v{glm::cross(w, u)};

    view_matrix_        = glm::mat4{1.f};
    view_matrix_[0][0]  = u.x;
    view_matrix_[1][0]  = u.y;
    view_matrix_[2][0]  = u.z;
    view_matrix_[0][1]  = v.x;
    view_matrix_[1][1]  = v.y;
    view_matrix_[2][1]  = v.z;
    view_matrix_[0][2]  = w.x;
    view_matrix_[1][2]  = w.y;
    view_matrix_[2][2]  = w.z;
    view_matrix_[3][0]  = -glm::dot(u, position);
    view_matrix_[3][1]  = -glm::dot(v, position);
    view_matrix_[3][2]  = -glm::dot(w, position);
}

//-------------------------------------------------------------------------------//

void Camera::SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) 
{
    SetViewDirection(position, target - position, up);
}

//-------------------------------------------------------------------------------//

void Camera::SetViewXZX(glm::vec3 position, glm::vec3 rotation)
{
    const float c3 = glm::cos(rotation.x);
    const float s3 = glm::sin(rotation.x);
    const float c2 = glm::cos(rotation.z);
    const float s2 = glm::sin(rotation.z);
    const float c1 = glm::cos(rotation.x);
    const float s1 = glm::sin(rotation.x);
    const glm::vec3 u{(c2), (c1 * s2), (s1 * s2)};
    const glm::vec3 v{(-c3 * s2), (c1 * c2 * c3 - s1 * s3), (c1 * s3 + c2 * c3 * s1)};
    const glm::vec3 w{(s2 * s3), (-c3 * s1 - c1 * c2 * s3), (c1 * c3 - c2 * s1 * s3)};
    
    view_matrix_        = glm::mat4{1.f};
    view_matrix_[0][0]  = u.x;
    view_matrix_[1][0]  = u.y;
    view_matrix_[2][0]  = u.z;
    view_matrix_[0][1]  = v.x;
    view_matrix_[1][1]  = v.y;
    view_matrix_[2][1]  = v.z;
    view_matrix_[0][2]  = w.x;
    view_matrix_[1][2]  = w.y;
    view_matrix_[2][2]  = w.z;
    view_matrix_[3][0]  = -glm::dot(u, position);
    view_matrix_[3][1]  = -glm::dot(v, position);
    view_matrix_[3][2]  = -glm::dot(w, position);
}

//-------------------------------------------------------------------------------//

} // end of Vulkan namespace