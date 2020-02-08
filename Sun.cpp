#include "sun.h"

Sun::Sun() {
    vao = 0;
    vbo = 0;
    radius = 696;
    sectorCount = 144;
    stackCount = 48;

    vertices = new vector<vec3>();
    indices = new vector<vec3>();
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

    // Initializing vertices
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
        
            vertices->push_back(x);
            vertices->push_back(y);
            vertices->push_back(z);
            vertices->push_back(xy);

        }
    }
    // Initliazed vertices

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if(i != (stackCount-1))
            {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if(i != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }


}

void Sun::draw() {



}