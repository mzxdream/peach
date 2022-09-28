#version 330 core

layout (location = 0) in vec3 aPos;
uniform float c;

void main()
{
   gl_Position = vec4(aPos.x + c, -aPos.y, aPos.z, 1.0);
}