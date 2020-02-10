#version 150

in vec4 vPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;

void
main()
{
    gl_Position = mvp * vPosition;
}