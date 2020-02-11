#include "shader.h"

using namespace std;

Shader::Shader() {

}

Shader::~Shader() { 

}

char* Shader::readShaderSource(const char* shaderFile)
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

    printf("shader in : %s \n", buf);
    return buf;
}

GLuint Shader::load(const char* vShaderFile, const char* fShaderFile) {

  struct Shaders {
	const char*  filename;
	GLenum       type;
	GLchar*      source;
  }  shaders[2] = {
	       { vShaderFile, GL_VERTEX_SHADER, NULL },
	       { fShaderFile, GL_FRAGMENT_SHADER, NULL }
     };

  GLuint program = glCreateProgram();
    
  for ( int i = 0; i < 2; ++i ) {
	Shaders& s = shaders[i];
	s.source = readShaderSource( s.filename );
	if ( shaders[i].source == NULL ) {
	    cerr << "Failed to read " << s.filename << endl;
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
    
    programID = program;
  
    return program;
}

void Shader::EditMatrix4(std::string m_name, glm::mat4 matrix) {
    int modelLoc = glGetUniformLocation(programID, m_name.c_str());
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::getProgramID() {
	return programID;
}