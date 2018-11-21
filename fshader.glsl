#version 130

out vec4 frag_color;

uniform mat4 viewMatrix;
uniform sampler2D texture;

flat in int id;
flat in int mylight1;
flat in int mylight2;
in vec4 color;
varying vec2 tex;
in vec4 coordinate;
in vec3 normal;
in vec4 eye;

void main () 
{

	vec4 diffuse = vec4(0.45, 0.45, 0.45, 1.0);
    vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 specular = vec4(0.2, 0.2, 0.2, 1.0);
    float shininess = 1.0;
    vec4 spec = vec4(0.5);


    // Defining Light
    vec4 lightPos1 = vec4(10.0, 5.0, 0.0, 0.0);;
    vec3 lightDir1 = vec3(viewMatrix * lightPos1);
    lightDir1 = normalize(lightDir1-vec3(coordinate));

    // Defining second light
    vec4 lightPos2 = vec4(-3.0, -2.0, 0.0, 0.0);
    vec3 lightDir2 = vec3(viewMatrix * lightPos2);
    lightDir2 = normalize(lightDir2-vec3(coordinate));

    vec4 ascolor = vec4(0.0);

    vec3 n = normalize(vec3(normal));

    if(mylight1 > 0.5) {
        //Diffuse
        float dotProduct = dot(n, lightDir1);
        float intensity =  max( dotProduct, 0.0);

        // Compute specular component only if light falls on vertex

        if(intensity > 0.0) {
            vec3 e = normalize(vec3(eye));
            vec3 h = normalize(lightDir1 + e );
            float intSpec = max(dot(h,n), 0.0);
            spec = specular * pow(intSpec, shininess);
        }

        ascolor += (intensity * diffuse  + spec); // All
    }

    if(mylight2 > 0.5) {
        // Adding Second light component
        float dotProduct = dot(n, lightDir2);
        float intensity =  max( dotProduct, 0.0);

        if(intensity > 0.0) {
            vec3 e = normalize(vec3(eye));
            vec3 h = normalize(lightDir2 + e );
            float intSpec = max(dot(h,n), 0.0);
            spec = specular * pow(intSpec, shininess);
        }

        ascolor += (intensity * diffuse  + spec);
    }

    if(id>0.5)
    {
    	frag_color = max(ascolor*color, ambient);
    }
    else
    {
    	vec4 teximage = texture2D(texture, tex);
    	frag_color = max(ascolor*teximage, ambient);
    }

}
