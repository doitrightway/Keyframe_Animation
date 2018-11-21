#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec4 vColor;

in vec3 vNormal;
uniform bool vid;


out vec4 id;
out vec4 color;
varying vec2 tex;

uniform mat3 normalMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  vec4 diffuse = vec4(0.5, 0.0, 0.0, 1.0); 
  vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
  vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  float shininess = 0.05;
  vec4 spec = vec4(0.0); 
  
  // Defining Light 
  vec4 lightPos = vec4(1.0, 1.0, 1.0, 0.0);
  vec3 lightDir = vec3(viewMatrix * lightPos); 
  lightDir = normalize(lightDir);  

  gl_Position = uModelViewMatrix * vPosition;
  
  vec3 n = normalize(normalMatrix * normalize(vNormal));
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec3 eye = normalize( vec3(-gl_Position));
	vec3 h = normalize(lightDir + eye );
   	float intSpec = max(dot(h,n), 0.0);	
        spec = specular * pow(intSpec, shininess);
  }  	
  
  color = max((intensity * diffuse  + spec)*vColor, ambient);

  tex = texCoord;
  if(!vid){
  	id[0]=0;
  }
  else{
  	id[0]=1;
  }
}
