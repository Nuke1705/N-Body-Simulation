#pragma once

#include "vertexbuffer.h"
//#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray{
    private:
        unsigned int m_id;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;

};