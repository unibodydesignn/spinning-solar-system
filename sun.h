#include <GLUT/glut.h>
#include <vector>
#include <stdlib.h>
#include <vector>
#include "Angel.h"
#include "loader.h"

#define PI 3.14151967

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

    vector<vec3> *vertices;
    vector<vec3> *indices;

    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    
    Loader *loader;

public:
    Sun();
    ~Sun();
    void load(const char* path, std::vector<vec3> &out_vertices, std::vector<vec3> &out_normals);
    void init();
    void draw();
};