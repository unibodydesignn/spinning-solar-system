#include "sun.h"

Sun::Sun() {
    vao = 0;
    vbo = 0;
    radius = 696;
    sectorCount = 144;
    stackCount = 48;

    vertices = new vector<vertex>(100);
    indices = new vector<vertex>(100);
}

Sun::~Sun() {
    vao = 0;
    vbo = 0;
    radius = 0;
    sectorCount = 0;
    stackCount = 0;

    delete vertices;
    delete indices;
}

void Sun::init() {

    const double pi = acos(-1);

    float sectorStep = 2 * pi / sectorCount;
    float stackStep = pi / stackCount;

    float x, y, z, xy;
    float sectorAngle, stackAngle;

    for(int i = 0; i < stackCount; ++i) {
        stackAngle = pi / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        // add sectorCount + 1 vertices per stack
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);
            vertex v;
            v.x = x;
            v.y = y;
            v.z = z;
            v.xy = xy;
            vertices->push_back(v);
        }


    }

}

void Sun::draw() {



}