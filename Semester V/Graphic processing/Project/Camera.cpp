#include "Camera.hpp"
#include <iostream>

namespace gps {

    // Afisarea detaliilor camerei
    void Camera::afisCamera() {
        std::cout << "Pozitia camerei: " << glm::to_string(cameraPosition) << '\n';
        std::cout << "Target-ul camerei: " << glm::to_string(cameraTarget) << '\n';
        std::cout << '\n';
    }

    // Constructorul clasei Camera
    Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) :
        cameraPosition(pos), cameraTarget(target), cameraUpDirection(up) {

        // Actualizarea parametrilor camerei
        cameraFrontDirection = glm::normalize(target - pos);
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, up));
    }

    // Returneaza matricea de vizualizare
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }

    // Actualizeaza pozitia camerei
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += speed * cameraFrontDirection;
            break;
        case MOVE_BACKWARD:
            cameraPosition -= speed * cameraFrontDirection;
            break;
        case MOVE_RIGHT:
            cameraPosition += speed * cameraRightDirection;
            break;
        case MOVE_LEFT:
            cameraPosition -= speed * cameraRightDirection;
            break;
        }
    }

    // Actualizeaza rotatia camerei
    void Camera::rotate(float pitch, float yaw) {
        glm::vec3 newDirection;
        newDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newDirection.y = sin(glm::radians(pitch));
        newDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFrontDirection = glm::normalize(newDirection);
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }
}
