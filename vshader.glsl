#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec4 vcolor;
in int vid;

flat out int id;
out vec4 color;
out vec2 tex;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  color= vcolor;
  id=vid;
  gl_Position = uModelViewMatrix * vPosition;
  tex = texCoord;
}
