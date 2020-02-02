#include <GLUT/glut.h>
#include <vector>
#include <stdlib.h>
#include <cmath>

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

    vector<vertex> *vertices;
    vector<vertex> *indices;

    GLuint vao;
    GLuint vbo;

public:
    Sun();
    ~Sun();
    void init();
    void draw();
};