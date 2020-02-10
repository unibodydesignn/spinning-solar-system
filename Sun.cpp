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

void Sun::load(const char* path,  std::vector<vec3> &out_vertices,  std::vector<vec3> &out_normals) {
    std::vector< unsigned int > vertexIndices, normalIndices;
        std::vector< vec3 > temp_vertices;
        std::vector< vec3 > temp_normals;
        
        FILE * file = fopen(path, "r");
        
        if( file == NULL ){
            printf("Impossible to open the file !\n");
        } else {
            printf("Opened the file. Processing data!\n" );
            
            while(1) {
                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break; // EOF = End Of File. Quit the loop.
                else {
                    if ( strcmp( lineHeader, "v" ) == 0 ){
                        vec3 vertex;
                        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                        temp_vertices.push_back(vertex);
                    } else if ( strcmp( lineHeader, "vn" ) == 0 ){
                        vec3 normal;
                        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                        temp_normals.push_back(normal);
                    } else if ( strcmp( lineHeader, "f" ) == 0 ){
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                        if (matches != 9)
                            printf("not 9 \n");

                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                    }
                }
            }
            
            printf("V beginning! %d\n", vertexIndices.size());
            for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
                 int vertexIndex = vertexIndices[i];
                vec3 vertex = temp_vertices[ vertexIndex-1 ];
                out_vertices.push_back(vertex);
            }
            printf("V End!!!!!!!\n");
        }
}

void Sun::init() {
    
    load("/Users/unibodydesignn/Desktop/sp.obj", *vertices, *indices);
    GLuint program = loader->initializeShaders("/Users/unibodydesignn/Desktop/spinning-solar-system/vertex.shader","/Users/unibodydesignn/Desktop/spinning-solar-system/fragment.shader");
    glUseProgram(program);

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
    printf("drawing sphere! \n");
    glDrawArrays(GL_LINES, 0, (int)vertices->size());
}