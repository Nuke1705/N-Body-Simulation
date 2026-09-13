#pragma once

#include <string>
#include "C:\Users\debra\Desktop\project\Physics\Opengl\projects\res\glm\glm.hpp"
#include <unordered_map>


using namespace std;

struct ShaderProgramSource{
    string VertexSource;
    string FragmentSource;
};

class Shader{
    private:
        unsigned int m_shader;
        const string& m_filepath;
        unordered_map<string, int> m_UniformLocationCache;
    public:
        Shader(const string& filepath);
        ~Shader();
        
        void Bind() const;
        void Unbind() const;

        void SetUniformMat4f(const string& name, const glm::mat4& mat);
        void SetUniform1f(const string& name, float v0);
        void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
        
    private:
        int GetUniformLocation(const string& uniform);
        ShaderProgramSource ParseShader(const string& filepath);
        unsigned int CompileShader( unsigned int type, const string& source);
        unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);    
};

