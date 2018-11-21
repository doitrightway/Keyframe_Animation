#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec4 vColor;

in vec3 vNormal;
uniform bool vid;
uniform bool light1;
uniform bool light2;

flat out int id;
out vec4 color;
out vec4 eye;
out vec3 normal;
out vec4 coordinate;
varying vec2 tex;
flat out int mylight1;
flat out int mylight2;

uniform mat3 normalMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = normalize((normalMatrix * normalize(vNormal)));
  eye = -gl_Position;
  coordinate= gl_Position;
  color = vColor;
  tex = texCoord;
  if(light1){
    mylight1=1;
  }
  else
  {
    mylight1=0;
  }
  if(light2)
  {
    mylight2=1;
  }
  else
  {
    mylight2=0;
  }
  if(!vid){
  	id=0;
  }
  else{
  	id=1;
  }
}
