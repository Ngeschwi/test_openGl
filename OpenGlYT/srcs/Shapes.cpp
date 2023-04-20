#include "../includes/Shapes.hpp"

Shape::Shape() {
    this->Projection = glm::mat4(1.0f);
    this->View = glm::mat4(1.0f);
    this->Model = glm::mat4(1.0f);
    this->Translation = glm::mat4(1.0f);
    this->Rotation = glm::mat4(1.0f);
    this->Scale = glm::mat4(1.0f);
    this->MVP = glm::mat4(1.0f);
    this->Texture = 0;
    this->TextureID = 0;
    this->Vertices = NULL;
    this->Colors = NULL;
    this->Uv = NULL;
    this->VertexBuffer = 0;
    this->ColorBuffer = 0;
    this->UvBuffer = 0;
}

Shape::~Shape() {}

void Shape::setProjection(glm::mat4 Projection) {
    this->Projection = Projection;
}

void Shape::setView(glm::mat4 View) {
    this->View = View;
}

void Shape::setTranslation(glm::vec3 Translation) {
    this->Translation = glm::translate(glm::mat4(1.0f), Translation);
}

void Shape::setRotation(float radians, glm::vec3 Axis) {
    this->Rotation = glm::rotate(glm::mat4(1.0f), radians, Axis);
}

void Shape::setScale(glm::vec3 Scale) {
    this->Scale = glm::scale(glm::mat4(1.0f), Scale);
}

void Shape::setModel() {
    this->Model = this->Translation * this->Rotation * this->Scale;
}

void Shape::setMVP() {
    this->MVP = this->Projection * this->View * this->Model;
}

void Shape::setTexture(std::string pathTexture) {
    if (pathTexture.substr(pathTexture.length() - 3) == "DDS") {
        this->Texture = loadDDS(pathTexture.c_str());
    } else if (pathTexture.substr(pathTexture.length() - 3) == "bmp") {
        this->Texture = loadBMP_custom(pathTexture.c_str());
    } else {
        std::cout << "Error: Texture format not supported" << std::endl;
    }
}

void Shape::setTextureID(GLuint programID, std::string name) {
    this->TextureID = glGetUniformLocation(programID, name.c_str());
}

void Shape::setVertices(const GLfloat* vertices) {
    this->Vertices = vertices;
}

void Shape::setColors(const GLfloat* colors) {
    this->Colors = colors;
}

void Shape::setUv(const GLfloat* uv) {
    this->Uv = uv;
}

void Shape::setBufferVBO() {
    glGenBuffers(1, &this->VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->Vertices), this->Vertices, GL_STATIC_DRAW);

    if (this->Texture != 0) {
        glGenBuffers(1, &this->UvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->UvBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->Uv), this->Uv, GL_STATIC_DRAW);
    } else {
        glGenBuffers(1, &this->ColorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->ColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->Colors), this->Colors, GL_STATIC_DRAW);
    }
}

glm::mat4 Shape::getProjection() {
    return this->Projection;
}

glm::mat4 Shape::getView() {
    return this->View;
}

glm::mat4 Shape::getModel() {
    return this->Model;
}

glm::mat4 Shape::getTranslation() {
    return this->Translation;
}

glm::mat4 Shape::getRotation() {
    return this->Rotation;
}

glm::mat4 Shape::getScale() {
    return this->Scale;
}

glm::mat4 Shape::getMVP() {
    return this->MVP;
}

GLuint Shape::getTexture() {
    return this->Texture;
}

GLuint Shape::getTextureID() {
    return this->TextureID;
}

const GLfloat* Shape::getVertices() {
    return this->Vertices;
}

const GLfloat* Shape::getColors() {
    return this->Colors;
}

const GLfloat* Shape::getUV() {
    return this->Uv;
}

GLuint Shape::getVertexBuffer() {
    return this->VertexBuffer;
}

GLuint Shape::getColorBuffer() {
    return this->ColorBuffer;
}

GLuint Shape::getUvBuffer() {
    return this->UvBuffer;
}

void Shape::draw(GLuint matrixID, GLenum mode, float start, float end) {
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &this->MVP[0][0]);

    if (this->Texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->Texture);
        glUniform1i(this->TextureID, 0);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    if (this->Texture != 0) {
        std::cout << "uv" << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, this->UvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    } else {
        std::cout << "color" << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, this->ColorBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }

    glDrawArrays(mode, start, end);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Shape::cleanUp() {
    glDeleteBuffers(1, &this->VertexBuffer);
    glDeleteBuffers(1, &this->ColorBuffer);
    glDeleteBuffers(1, &this->UvBuffer);
    glDeleteTextures(1, &this->Texture);
}