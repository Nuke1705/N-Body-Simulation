#include "shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

ShaderProgramSource Shader::ParseShader(const string &filepath)
{
    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos){
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
            
        }
        else{
            ss[(int)type] << line << '\n';
        }
        
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const string &source)
{
    GLCall(unsigned int id  = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE){
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length*sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));
            cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
            cout << message << endl;
            GLCall(glDeleteShader(id));
            return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const string &vertexShader, const string &fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs  = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs  = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}

Shader::Shader(const string& filepath)
    :m_filepath(filepath), m_shader(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(m_shader));
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_shader));
}

void Shader::Bind() const 
{
    GLCall(glUseProgram(m_shader));
    //cout << "shader" << endl;
}

int Shader::GetUniformLocation(const string & uniform)
{
    if(m_UniformLocationCache.find(uniform) != m_UniformLocationCache.end())
        return m_UniformLocationCache[uniform];

    const char* name = uniform.c_str();
    GLCall(int location = glGetUniformLocation(m_shader, name));
    if(location == -1)
        cout << "Warning: uniform " << uniform << " does not exist" << endl;
    
    m_UniformLocationCache[uniform] = location;
    return location;
}

void Shader::SetUniformMat4f(const string &name, const glm::mat4& mat){
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::SetUniform1f(const string &name, float v0){
    GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::Unbind() const 
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
