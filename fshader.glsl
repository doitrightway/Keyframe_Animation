#version 130

out vec4 frag_color;

uniform sampler2D texture;

flat in int id;
in vec4 color;
in vec2 tex;

void main () 
{
	if(id==1)
	{
		frag_color=vec4(1.0,0.5,0.0,1.0);
	}
	else	
    {
    	frag_color = texture2D(texture, tex);
    }		
}
