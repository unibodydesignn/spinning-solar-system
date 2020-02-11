#include <GLUT/glut.h>
#include <vector>
#include <stdlib.h>
#include <vector>
#include <glm/0.9.9.3/include/glm/glm.hpp>
#include "shader.h"

#define PI 3.14151967
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

using namespace std;

struct vertex {
    float x;
    float y;
    float z;
    float xy;
};

class Sun {

private:
    float radius;
    float sectorCount;
    float stackCount;

    vector<glm::vec3> *vertices;
    vector<glm::vec3> *indices;

    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    
    

public:
    Sun();
    ~Sun();
    void load(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals);
    void init();
    void draw();
    void calculateTransformation(glm::mat4& modelMatrix);
    Shader *shader;
};