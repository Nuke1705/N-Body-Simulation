#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"

#define ASSERT(x) if(!(x)) __debugbreak;
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
    public:
    void Clear() const; 
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void DrawP(const VertexArray &va, const int &size, const Shader &shader);
    float GetTime();
};