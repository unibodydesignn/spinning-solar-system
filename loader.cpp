#include "loader.h"

Loader::Loader() { }

Loader::~Loader() { }

void Loader::initializeObject(const char* path,  std::vector<vec3> &out_vertices,  std::vector<vec3> &out_normals) {
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

char* Loader::readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");

    if ( fp == NULL ) { return NULL; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}

GLuint Loader::initializeShaders(const char* vShaderFile, const char* fShaderFile) {

  struct Shader {
	const char*  filename;
	GLenum       type;
	GLchar*      source;
  }  shaders[2] = {
	       { vShaderFile, GL_VERTEX_SHADER, NULL },
	       { fShaderFile, GL_FRAGMENT_SHADER, NULL }
     };

  GLuint program = glCreateProgram();
    
  for ( int i = 0; i < 2; ++i ) {
	Shader& s = shaders[i];
	s.source = readShaderSource( s.filename );
	if ( shaders[i].source == NULL ) {
	    std::cerr << "Failed to read " << s.filename << std::endl;
	    exit( EXIT_FAILURE );
	}

	GLuint shader = glCreateShader( s.type );
	glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
	glCompileShader( shader );

	GLint  compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
	    std::cerr << s.filename << " failed to compile:" << std::endl;
	    GLint  logSize;
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
	    std::cerr << logMsg << std::endl;
	    delete [] logMsg;

	    exit( EXIT_FAILURE );
	}

	delete [] s.source;

	glAttachShader( program, shader );
  }

    /* link  and error check */
  glLinkProgram(program);

  GLint  linked;
  glGetProgramiv( program, GL_LINK_STATUS, &linked );
  if ( !linked ) {
	std::cerr << "Shader program failed to link" << std::endl;
	GLint  logSize;
	glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
	char* logMsg = new char[logSize];
	glGetProgramInfoLog( program, logSize, NULL, logMsg );
	std::cerr << logMsg << std::endl;
	delete [] logMsg;

	exit( EXIT_FAILURE );
  }

    /* use program object */
    glUseProgram(program);
  return program;
}

