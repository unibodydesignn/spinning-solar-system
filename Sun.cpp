#include "sun.h"

using namespace std;

Sun::Sun() {
    vao = 0;
    vbo = 0;
    ibo = 0;
    radius = 696;
    sectorCount = 144;
    stackCount = 48;

    vertices = new vector<vec3>();
    indices = new vector<vec3>();
}

Sun::~Sun() {
    vao = 0;
    vbo = 0;
    ibo = 0;
    radius = 0;
    sectorCount = 0;
    stackCount = 0;

    delete vertices;
    delete indices;
}

void Sun::init() {
    
    loader = new Loader();
    loader->initializeObject("/Users/unibodydesignn/Desktop/sun.obj", *vertices, *indices);
    loader->initializeShaders("/Users/unibodydesignn/Desktop/spinning-solar-system/vertex.shader","/Users/unibodydesignn/Desktop/spinning-solar-system/fragment.shader");

    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
        
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * 9, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

}

void Sun::draw() {
    glDrawArrays(GL_LINES, 0, (int)vertices->size());
}