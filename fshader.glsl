#version 130

out vec4 frag_color;

uniform sampler2D texture;

in vec4 id;
in vec4 color;
varying vec2 tex;

void main () 
{
	if(id[0]>0.5)
	{
		frag_color=color;
	}
	else
    {
    	frag_color = texture2D(texture, tex);
    }
}
