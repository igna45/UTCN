#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp" //core glm functionality
#include "glm/gtc/matrix_transform.hpp" //glm extension for generating common transformation matrices
#include "glm/gtc/matrix_inverse.hpp" //glm extension for computing inverse matrices
#include "glm/gtc/type_ptr.hpp" //glm extension for accessing the internal data structure of glm types

#include "Window.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "SkyBox.hpp"

#include <iostream>

// window
gps::Window myWindow;
int glWindowWidth = 900;
int glWindowHeight = 700;

GLint afisLuminaLoc;
GLuint shadowMapFBO;
GLuint depthMapTexture;
GLint viewLoc;
GLint projectionLoc;
GLint lightPunctiformColorLoc;
GLint normalMatrixLoc;
GLint lightDirLoc;
GLint modelLoc;
GLint lightColorLoc;
GLint afisCeataLoc;
GLint lightPunctiformLoc;
bool animateGround = false; 

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat3 normalMatrix;
glm::mat4 lightRotation;

glm::vec3 lightDir;
glm::vec3 lightColor;
glm::vec3 lightPunctiform;
glm::vec3 lightPunctiformColor;

// camera
gps::Camera myCamera(
    glm::vec3(0.0f, 2.0f, 4.0f),
    glm::vec3(0.0f, 0.0f, -10.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));

GLfloat cameraSpeed = 0.3f;

GLboolean pressedKeys[1024];

gps::Shader myBasicShader;

gps::Shader depthMapShader;
gps::Shader lightShader;
gps::Shader screenQuadShader;
gps::Shader skyboxShader;

gps::Model3D ground;
gps::Model3D lightCube;
gps::Model3D screenQuad;


GLfloat angle;
GLfloat objectAngle = 0.0f;

const unsigned int SHADOW_WIDTH = 2048;
const unsigned int SHADOW_HEIGHT = 2048;
bool showDepthMap;

std::vector<const GLchar*> faces;
gps::SkyBox mySkyBox;

bool firstMouse = true;
float lastX = glWindowWidth / 2;
int retina_width, retina_height;
float lastY = glWindowHeight / 2;
float yaw = -90.0f, pitch = 0.0f;
const float sensitivity = 0.3f;
float angleY = 0.0f;

bool automove = false;
bool autoShadow = false;


GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    fprintf(stdout, "Window resized!");
    glfwGetFramebufferSize(myWindow.getWindow(), &retina_width, &retina_height);
    WindowDimensions a = { retina_width, retina_height };
    myWindow.setWindowDimensions(a);
    glViewport(0, 0, (float)myWindow.getWindowDimensions().width, (float)myWindow.getWindowDimensions().height);
    myBasicShader.useShaderProgram();
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
    projectionLoc = glGetUniformLocation(myBasicShader.shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) { pressedKeys[key] = true; }
        else if (action == GLFW_RELEASE) { pressedKeys[key] = false; }
    }

}


void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) {
        lastX = xpos; lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;

    yoffset *= sensitivity;

    yaw += xoffset;

    pitch += yoffset;

    if (pitch < -88.0f) pitch = -88.0f;

    if (pitch > 88.0f) pitch = 88.0f;

    myCamera.rotate(pitch, yaw);
    view = myCamera.getViewMatrix();
    myBasicShader.useShaderProgram();
    glUniformMatrix4fv(viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(view));

}



void processMovement() {

    if (pressedKeys[GLFW_KEY_W]) {
        myCamera.move(gps::MOVE_FORWARD, cameraSpeed);
   
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
       
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    }

    if (pressedKeys[GLFW_KEY_S]) {
        myCamera.move(gps::MOVE_BACKWARD, cameraSpeed);
       
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    }

    if (pressedKeys[GLFW_KEY_A]) {
        myCamera.move(gps::MOVE_LEFT, cameraSpeed);
       
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
       
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    }

    if (pressedKeys[GLFW_KEY_D]) {
        myCamera.move(gps::MOVE_RIGHT, cameraSpeed);
       
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    }

    if (pressedKeys[GLFW_KEY_Z]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (pressedKeys[GLFW_KEY_X]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }


    if (pressedKeys[GLFW_KEY_C]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (pressedKeys[GLFW_KEY_V]) {
        myBasicShader.useShaderProgram();
        glUniform1i(afisCeataLoc, 1);
    }


    if (pressedKeys[GLFW_KEY_B]) {
        myBasicShader.useShaderProgram();
        glUniform1i(afisCeataLoc, 0);
    }

    if (pressedKeys[GLFW_KEY_F]) {
        myBasicShader.useShaderProgram();
        glUniform1i(afisLuminaLoc, 1);
    }


    if (pressedKeys[GLFW_KEY_G]) {
        myBasicShader.useShaderProgram();
        glUniform1i(afisLuminaLoc, 0);
    }
    if (pressedKeys[GLFW_KEY_SPACE]) {
        myCamera.afisCamera();
    }

    if (pressedKeys[GLFW_KEY_Q]) {
        objectAngle -= 1.0f; // Rotire spre stânga
    }

    if (pressedKeys[GLFW_KEY_E]) {
        objectAngle += 1.0f; // Rotire spre dreapta
    }

    if (pressedKeys[GLFW_KEY_P]) {
        animateGround = !animateGround; 
    }

    if (pressedKeys[GLFW_KEY_O]) {
        autoShadow = !autoShadow;
    }
}

void initOpenGLWindow() {

    myWindow.Create(glWindowWidth, glWindowHeight, "OpenGL Project Core");
    glfwGetFramebufferSize(myWindow.getWindow(), &retina_width, &retina_height);
    WindowDimensions a = { retina_width, retina_height };
    myWindow.setWindowDimensions(a);
    glViewport(0, 0, (float)myWindow.getWindowDimensions().width, (float)myWindow.getWindowDimensions().height);


}

void initOpenGLState() {

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glViewport(0, 0, myWindow.getWindowDimensions().width, myWindow.getWindowDimensions().height);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

}

void setWindowCallbacks() {

    glfwSetWindowSizeCallback(myWindow.getWindow(), windowResizeCallback);
    glfwSetKeyCallback(myWindow.getWindow(), keyboardCallback);
    glfwSetCursorPosCallback(myWindow.getWindow(), mouseCallback);

}



void initModels() {

    ground.LoadModel("objects/landscape/landscape.obj");
    lightCube.LoadModel("objects/cube/cube.obj");
    screenQuad.LoadModel("objects/quad/quad.obj");
    mySkyBox.Load(faces);
}

void initShaders() {
    myBasicShader.loadShader("shaders/basic.vert", "shaders/basic.frag");
    lightShader.loadShader("shaders/lightCube.vert", "shaders/lightCube.frag");
    screenQuadShader.loadShader("shaders/screenQuad.vert", "shaders/screenQuad.frag");
    depthMapShader.loadShader("shaders/mapareUmbre.vert", "shaders/mapareUmbre.frag");
    skyboxShader.loadShader("shaders/skyboxShader.vert", "shaders/skyboxShader.frag");
}

void initUniforms() {

    myBasicShader.useShaderProgram();
    model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelLoc = glGetUniformLocation(myBasicShader.shaderProgram, "model");

    view = myCamera.getViewMatrix();
    viewLoc = glGetUniformLocation(myBasicShader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    normalMatrixLoc = glGetUniformLocation(myBasicShader.shaderProgram, "normalMatrix");

    projection = glm::perspective(glm::radians(45.0f),
        (float)myWindow.getWindowDimensions().width / (float)myWindow.getWindowDimensions().height,
        0.1f, 20.0f);
    projectionLoc = glGetUniformLocation(myBasicShader.shaderProgram, "projection");
   
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    lightDir = glm::vec3(0.0f, 50.0f, -80.0f);
    lightDirLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightDir");
  
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));

    lightColor = glm::vec3(0.7f, 0.7f, 0.7f); 
    lightColorLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightColor");
    // send light color to shader
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));


    lightShader.useShaderProgram();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    myBasicShader.useShaderProgram();
    afisCeataLoc = glGetUniformLocation(myBasicShader.shaderProgram, "afisCeata");

    myBasicShader.useShaderProgram();
    // lumina punctiforma
    lightPunctiform = glm::vec3(69.949921, 5.172267, -43.536785);
    lightPunctiformLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightPunctiform");
    glUniform3fv(lightPunctiformLoc, 1, glm::value_ptr(lightPunctiform));
    lightPunctiformColor = glm::vec3(69.949921, 5.172267, -43.536785);
    lightPunctiformColorLoc = glGetUniformLocation(myBasicShader.shaderProgram, " lightPunctiformColor");
    glUniform3fv(lightPunctiformColorLoc, 1, glm::value_ptr(lightPunctiformColor));

    afisLuminaLoc = glGetUniformLocation(myBasicShader.shaderProgram, "afisLuminaDoi");
}





void drawObjects(gps::Shader shader, bool depthPass) {

    shader.useShaderProgram();

    glm::mat4 objectRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(objectAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f));
    model = objectRotationMatrix * model; // Apply object rotation
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }

    ground.Draw(shader);
}

void renderSkyBox() {

    skyboxShader.useShaderProgram();
    view = myCamera.getViewMatrix();


    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.shaderProgram, "view"),
        1,
        GL_FALSE,
        glm::value_ptr(view));

    projection = glm::perspective(glm::radians(45.0f),
        (float)retina_width / (float)retina_height,
        0.1f,
        1000.0f);
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.shaderProgram, "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection));
}

void initFBO() {


    //generate FBO ID
    glGenFramebuffers(1, &shadowMapFBO);
    //create depth texture for FBO
    glGenTextures(1, &depthMapTexture);
    glBindTexture(GL_TEXTURE_2D,
        depthMapTexture);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT,
        SHADOW_WIDTH,
        SHADOW_HEIGHT,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        NULL);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR_MIPMAP_LINEAR);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glTexParameterfv(GL_TEXTURE_2D,
        GL_TEXTURE_BORDER_COLOR,
        borderColor);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_BORDER);
    //attach texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER,
        shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        depthMapTexture,
        0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

glm::mat4 computeLightSpaceTrMatrix() {
    
    glm::mat4 lightView = glm::lookAt(glm::inverseTranspose(glm::mat3(lightRotation)) * lightDir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const GLfloat near_plane = 0.1f, far_plane = 200.0f;
    glm::mat4 lightProjection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, near_plane, far_plane);
    glm::mat4 lightSpaceTrMatrix = lightProjection * lightView;
    return lightSpaceTrMatrix;
}


void renderShadow() {
    depthMapShader.useShaderProgram();
    glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "lightSpaceTrMatrix"),1, GL_FALSE,glm::value_ptr(computeLightSpaceTrMatrix()));
    glViewport(0,
        0,
        SHADOW_WIDTH,
        SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER,
        shadowMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    drawObjects(depthMapShader, true);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void renderScene() {


    renderShadow();

    glViewport(0,0,retina_width,retina_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    myBasicShader.useShaderProgram();

    view = myCamera.getViewMatrix();
    glUniformMatrix4fv(viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(view));

    lightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view * lightRotation)) * lightDir));
    //bind the shadow map
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    glUniform1i(glGetUniformLocation(myBasicShader.shaderProgram, "shadowMap"), 3);

    glUniformMatrix4fv(glGetUniformLocation(myBasicShader.shaderProgram, "lightSpaceTrMatrix"),1,
        GL_FALSE,
        glm::value_ptr(computeLightSpaceTrMatrix()));

    drawObjects(myBasicShader, false);

    //draw a white cube around the light

    lightShader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "view"),
        1, GL_FALSE, glm::value_ptr(view));

    model = lightRotation;
    model = glm::translate(model, 1.0f * lightDir);
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "model"), 1, GL_FALSE,
        glm::value_ptr(model));
    lightCube.Draw(lightShader);

    renderSkyBox();
    mySkyBox.Draw(skyboxShader, view, projection);

}

void cleanup() {
    glDeleteTextures(1, &depthMapTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &shadowMapFBO);
    myWindow.Delete();
    //cleanup code for your own data
}

void loadSkyBox() {
    faces.push_back("objects/skybox/right.tga");
    faces.push_back("objects/skybox/left.tga");
    faces.push_back("objects/skybox/top.tga");
    faces.push_back("objects/skybox/bottom.tga");
    faces.push_back("objects/skybox/back.tga");
    faces.push_back("objects/skybox/front.tga");

}

int main(int argc, const char* argv[]) {

    try {
        initOpenGLWindow();

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    initOpenGLState();
    loadSkyBox();
    initModels();
    initShaders();
    initUniforms();
    setWindowCallbacks();
    initFBO();
  

    // application loop
    while (!glfwWindowShouldClose(myWindow.getWindow())) {
        processMovement();

        if (autoShadow) {
            angle += 1.0f; 
        }

        if (animateGround) {
            objectAngle += 1.0f; 
        }
        renderScene();

        glfwPollEvents();
        glfwSwapBuffers(myWindow.getWindow());

        //glCheckError();
    }

    cleanup();

    return EXIT_SUCCESS;
}