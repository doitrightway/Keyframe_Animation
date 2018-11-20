#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec4 vColor;

uniform bool vid;


out vec4 id;
out vec4 color;
varying vec2 tex;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  color= vColor;
  gl_Position = uModelViewMatrix * vPosition;
  tex = texCoord;
  if(!vid){
  	id[0]=0;
  }
  else{
  	id[0]=1;
  }
}
