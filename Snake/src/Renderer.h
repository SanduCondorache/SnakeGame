#pragma once

#include <GL/glew.h>

const int GRID_X = 32;
const int GRID_Y = 32;

const float vertices[] = {
      0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 0.0f
};

const size_t indeces[] = {
    0, 1, 2,
    2, 3, 0
};

#define ASSERT(x) if (!x) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {

private:

public:
    void Clear();
    //void Draw(const VertexArray& va, const IndexBuffer& ib, Shader shader, Snake snake);
};