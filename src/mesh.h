#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

#include <vector>
#include <string>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>      vertices;
        std::vector<GLuint>      indices;
        std::vector<Texture>     textures;
        GLuint VAO;

        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
        void DrawInstances(Shader &shader, GLuint amount);
        void DeleteBuffers();
        
    private:
        //render data
        GLuint VBO, EBO;

        void setupMesh();
};

#endif