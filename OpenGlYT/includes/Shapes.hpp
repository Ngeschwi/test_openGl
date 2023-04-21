#pragma once

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../common/shader.hpp"
#include "../common/texture.hpp"

class Shape {
private:
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 Translation;
    glm::mat4 Rotation;
    glm::mat4 Scale;
    glm::mat4 MVP;

    GLuint Texture;
    GLuint TextureID;

    const GLfloat* Vertices;
    const GLfloat* Colors;
    const GLfloat* Uv;

    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint UvBuffer;

public:
    Shape();
    ~Shape();

    void setProjection(glm::mat4 Projection);
    void setView(glm::mat4 View);
    void setTranslation(glm::vec3 Translation);
    void setRotation(float radians, glm::vec3 Axis);
    void setScale(glm::vec3 Scale);
    void setModel();
    void setMVP();

    void setTexture(std::string pathTexture);
    void setTextureID(GLuint programID, std::string name);

    void setVertices(const GLfloat* vertices);
    void setColors(const GLfloat* colors);
    void setUv(const GLfloat* uv);

    void setBufferVBO();


    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::mat4 getModel();
    glm::mat4 getTranslation();
    glm::mat4 getRotation();
    glm::mat4 getScale();
    glm::mat4 getMVP();

    GLuint getTexture();
    GLuint getTextureID();

    const GLfloat* getVertices();
    const GLfloat* getColors();
    const GLfloat* getUV();

    GLuint getVertexBuffer();
    GLuint getColorBuffer();
    GLuint getUvBuffer();

    void draw(GLuint matrixID, GLenum mode, float start, float end);
    void cleanUp();
};