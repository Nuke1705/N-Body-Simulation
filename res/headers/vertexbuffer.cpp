#include "vertexbuffer.h"
#include "renderer.h"
//#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool type){
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    if(!type){
       GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
    else{
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    } 
}
    

VertexBuffer::~VertexBuffer(){
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Update(const void* data, unsigned int size){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
void VertexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}