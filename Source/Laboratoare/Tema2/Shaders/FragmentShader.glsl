#version 330

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_coord;
in vec3 frag_color; 

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(frag_color, 1);
	//out_normal = vec4(frag_normal, 1);
	//out_position = vec4(frag_position, 1);
	//out_texture = vec4(frag_texture, 1);
}