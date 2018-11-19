#version 130

out vec4 frag_color;

uniform sampler2D texture;

flat in int id;
in vec4 color;
in vec2 tex;

void main () 
{
	if(id!=0)
	{
		frag_color=color;
	}
	else	
    {
    	frag_color = texture2D(texture, tex);
    }		
}
