#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <glm/0.9.9.3/include/glm/glm.hpp>
#include <glm/0.9.9.3/include/glm/gtc/type_ptr.hpp>
class Shader {

public:
    Shader();
    ~Shader();

    char* readShaderSource(const char* shaderFile);
    GLuint load(const char* vShaderFile, const char* fShaderFile);
    void EditMatrix4(std::string m_name, glm::mat4 matrix);

private:
    GLuint programID;
    std::string VertexShaderCode;
    std::string FragmentShaderCode;

};