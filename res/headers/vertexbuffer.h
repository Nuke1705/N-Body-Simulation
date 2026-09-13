#pragma once
//#include "vertexbuffer.cpp"

class VertexBuffer{
    private:
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size, bool type);
        ~VertexBuffer();

        void Update(const void* data, unsigned int size);
        void Bind() const;
        void Unbind() const;    
};