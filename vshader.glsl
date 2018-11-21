#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec4 vColor;

in vec3 vNormal;
uniform bool vid;
uniform bool light1;
uniform bool light2;

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
  vec4 spec1 = vec4(0.0);
  vec4 spec2 = vec4(0.0); 
  gl_Position = uModelViewMatrix * vPosition;
  vec3 eye = normalize( vec3(-gl_Position));

  // Defining Light 
  vec4 lightPos1 = vec4(5.0, 5.0, 5.0, 0.0);
  vec3 lightDir1 = vec3(viewMatrix * lightPos1); 
  lightDir1 = normalize(lightDir1);  

  
  vec3 n = normalize(normalMatrix * normalize(vNormal));
  float dotProduct1 = dot(n, lightDir1);
  float intensity1 =  max( dotProduct1, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity1 > 0.0)
  {
	vec3 h1 = normalize(lightDir1 + eye );
   	float intSpec1 = max(dot(h1,n), 0.0);	
        spec1 = specular * pow(intSpec1, shininess);
  }  

  vec4 lightPos2 = vec4(10.0, 5.0, 0.0, 0.0);
  vec3 lightDir2 = vec3(viewMatrix * lightPos2); 
  lightDir2 = normalize(lightDir2);  

  float dotProduct2 = dot(n, lightDir2);
  float intensity2 =  max( dotProduct2, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity2 > 0.0)
  {
	vec3 h2 = normalize(lightDir2 + eye );
   	float intSpec2 = max(dot(h2,n), 0.0);	
        spec2 = specular * pow(intSpec2, shininess);
  }  


  if(light1 && light2)
  {
  	 color = max(((intensity1 + intensity2) * diffuse  + spec1 + spec2)*vColor, ambient);
  }
  else if(light1)
  {
  	 color = max((intensity1 * diffuse  + spec1)*vColor, ambient);
  }
  else if(light2)
  {
  	 color = max((intensity2 * diffuse  + spec2)*vColor, ambient);
  }
  else
  {
  	 color = ambient;
  }

  tex = texCoord;
  if(!vid){
  	id[0]=0;
  }
  else{
  	id[0]=1;
  }
}
