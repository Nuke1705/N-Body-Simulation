#pragma once

#include <vector>
#include <GL/glew.h>
#include "renderer.h"

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalised;
    static unsigned int GetSizeType(unsigned int type){
        switch(type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

//template<class T>
class VertexBufferLayout{
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout()
            : m_Stride(0) {}
        
        void Push(unsigned int type, unsigned int count){
            if(type == GL_UNSIGNED_BYTE){
                m_Elements.push_back({type, count, GL_TRUE});
            }
            else{
                m_Elements.push_back({type, count, GL_FALSE});
            }    
            m_Stride += count* VertexBufferElement::GetSizeType(type);
        }       
        
        inline const std::vector<VertexBufferElement> GetElements() const& {return m_Elements;}
        inline unsigned int GetStride() const {return m_Stride;}
        
};

