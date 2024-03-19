#include "Shader.h"
#include <glm/glm.hpp>
#include "Renderer.h"

Shader::Shader()
{
    this->blendMode = OPAQUE;
    rendererID = -1;

}

Shader::Shader(const char* vertexPath, const char* fragmentPath, BlendMode type)
{
    this->blendMode = type;
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
  GLCALL(  glShaderSource(vertex, 1, &vShaderCode, NULL));
  GLCALL(glCompileShader(vertex));
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCALL( glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCALL(glCompileShader(fragment));
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    rendererID = glCreateProgram();
    GLCALL( glAttachShader(rendererID, vertex));
    GLCALL(glAttachShader(rendererID, fragment));
    GLCALL( glLinkProgram(rendererID));
    checkCompileErrors(rendererID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    GLCALL(glDeleteShader(vertex));
    GLCALL(glDeleteShader(fragment));
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(rendererID));
}

void Shader::LoadShader(const char* vertexPath, const char* fragmentPath, BlendMode type)
{
    this->blendMode = type;
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCALL(glShaderSource(vertex, 1, &vShaderCode, NULL));
    GLCALL(glCompileShader(vertex));
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCALL(glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCALL(glCompileShader(fragment));
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    rendererID = glCreateProgram();
    GLCALL(glAttachShader(rendererID, vertex));
    GLCALL(glAttachShader(rendererID, fragment));
    GLCALL(glLinkProgram(rendererID));
    checkCompileErrors(rendererID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    GLCALL(glDeleteShader(vertex));
    GLCALL(glDeleteShader(fragment));
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(rendererID));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

void Shader::setBool(const std::string& name, bool value) 
{
    GLCALL(glUniform1i(FindUniformLocations(name), (int)value));
}
void Shader::setInt(const std::string& name, int value) 
{
    GLCALL(glUniform1i(FindUniformLocations(name), value));
}
void Shader::setFloat(const std::string& name, float value) 
{
    GLCALL(glUniform1f(FindUniformLocations(name), value));
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) 
{
    GLCALL(glUniform2fv(FindUniformLocations(name), 1, &value[0]));
}
void Shader::setVec2(const std::string& name, float x, float y) 
{
    GLCALL(glUniform2f(FindUniformLocations(name), x, y));
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) 
{
    GLCALL(glUniform3fv(FindUniformLocations(name), 1, &value[0]));

}
void Shader::setVec3(const std::string& name, float x, float y, float z) 
{
    GLCALL(glUniform3f(FindUniformLocations(name), x, y, z));
    
}
void Shader::setVec4(const std::string& name, const glm::vec4& value) 
{
    GLCALL(glUniform4fv(FindUniformLocations(name), 1, &value[0]));
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) 
{
    GLCALL(glUniform4f(FindUniformLocations(name), x, y, z, w));
}
void Shader::setMat2(const std::string& name, const glm::mat2& mat) 
{
    GLCALL(glUniformMatrix2fv(FindUniformLocations(name), 1, GL_FALSE, &mat[0][0]));
}
void Shader::setMat3(const std::string& name, const glm::mat3& mat) 
{
    GLCALL(glUniformMatrix3fv(FindUniformLocations(name), 1, GL_FALSE, &mat[0][0]));
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) 
{
    GLCALL(glUniformMatrix4fv(FindUniformLocations(name), 1, GL_FALSE, &mat[0][0]));
}


unsigned int Shader::FindUniformLocations(const std::string& name)
{
    if (m_LocationCache.find(name) != m_LocationCache.end())
    {
        return m_LocationCache[name];
    }
    GLCALL(int value = glGetUniformLocation(rendererID, name.c_str()));

    if (value == -1)
    {
        std::cout << "Warning : uniform '" << name << "' does'nt exist!" << std::endl;
    }
   m_LocationCache[name] = value;
   return value;
}

unsigned int& Shader::GetShaderId()
{
    return rendererID;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        GLCALL(   glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            GLCALL(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        GLCALL(glGetProgramiv(shader, GL_LINK_STATUS, &success));
        if (!success)
        {
            GLCALL(glGetProgramInfoLog(shader, 1024, NULL, infoLog));
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}