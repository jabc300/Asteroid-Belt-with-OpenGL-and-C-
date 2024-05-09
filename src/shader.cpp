#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string svShaderCode = loadShader(vertexPath);
    std::string sfShaderCode = loadShader(fragmentPath);
    const GLchar* vShaderCode = svShaderCode.c_str();
    const GLchar* fShaderCode = sfShaderCode.c_str();

    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    vertex = createShader(GL_VERTEX_SHADER, vShaderCode);
    fragment = createShader(GL_FRAGMENT_SHADER, fShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<< std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    std::string svShaderCode = loadShader(vertexPath);
    std::string sfShaderCode = loadShader(fragmentPath);
    std::string sgShaderCode = loadShader(geometryPath);
    const GLchar* vShaderCode = svShaderCode.c_str();
    const GLchar* fShaderCode = sfShaderCode.c_str();
    const GLchar* gShaderCode = sgShaderCode.c_str();

    GLuint vertex, fragment, geometry;
    int success;
    char infoLog[512];

    vertex = createShader(GL_VERTEX_SHADER, vShaderCode);
    fragment = createShader(GL_FRAGMENT_SHADER, fShaderCode);
    geometry = createShader(GL_GEOMETRY_SHADER, gShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, geometry);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<< std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);

}

std::string Shader::loadShader(const char* shaderPath){

    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        return shaderStream.str();
    }
    catch(std::ifstream::failure& e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCEFULLY_READ" <<  e.what() <<std::endl;
        return "";
    }
}

GLuint Shader::createShader(GLenum type, const char* shaderCode)
{    
    GLuint shader;
    int success;
    char infoLog[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string shaderName = "";
        if(type = GL_VERTEX_SHADER){
            shaderName ="VERTEX_SHADER";
        }
        else if (type = GL_FRAGMENT_SHADER){
            shaderName ="FRAGMENT_SHADER";
        }
        else if (type = GL_GEOMETRY_SHADER){
            shaderName ="GEOMETRY_SHADER";
        }
        std::cout << "ERROR::SHADER::"<<shaderName<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation((ID), name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation((ID), name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation((ID), name.c_str()), value);
}

void Shader::setMatrix4(const std::string &name, glm::mat4 matrix) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 vector) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}


