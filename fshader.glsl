#version 130

out vec4 frag_color;

uniform sampler2D texture;
in vec2 tex;
in vec4 color;
flat in int id;
void main () 
{
	if(id==1)
	{
		frag_color=color;
	}
	else	
    {
    	frag_color = texture2D(texture, tex);
    }		
}
