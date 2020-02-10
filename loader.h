#include <stdlib.h>
#include <vector> 
#include "mat.h"
#include "Angel.h"

using namespace std;
class Loader {

public:
    Loader();
    ~Loader();

    void initializeObject(const char* path, std::vector<vec3> &out_vertices, std::vector<vec3> &out_normals);
    GLuint initializeShaders(const char* vShaderFile, const char* fShaderFile);
    char* readShaderSource(const char* shaderFile);

};