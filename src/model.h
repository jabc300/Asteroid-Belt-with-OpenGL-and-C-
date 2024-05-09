#ifndef MODEL_H
#define MODEL_H

#include"shader.h"
#include "mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Model
{
    public:
        Model(const char *path);
        void Draw(Shader &shader);
        void DrawInstances(Shader &shader, GLuint amount);
        void DeleteBuffers();
        std::vector<Mesh> meshes;
    
    private:
        
        std::string directory;
        std::vector<Texture> textures_loaded;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        GLuint TextureFromFile(std::string location, std::string directory);
};

#endif