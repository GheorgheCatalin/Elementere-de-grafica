#version 330

// TODO: get vertex attributes from each location
/*layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 v_color;*/

//Ex 6
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform float Time;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coord;
out vec3 frag_color;

void main()
{
	// TODO: send output to fragment shader
	frag_position = v_position;
	frag_coord = tex_coord;
	frag_color = v_color ;
	frag_normal = v_normal + vec3(sin(Time), cos(Time), tan(Time));
	//Daca modificarea de la ex5 nu este facuta
	frag_color = v_color + vec3(sin(Time), cos(Time), tan(Time));

	// TODO: compute gl_Position
	//gl_Position = Projection * View * Model * vec4(v_position + vec3(sin(Time), 1 - sin(Time), 0), 1.0);
	//gl_Position = Projection * View * Model * vec4(v_position, 1.0) * vec4(vec3(0.5, 0.4, 0.2), 1.0) ;
	//gl_Position = Projection * View * Model * vec4(v_position  + v_normal , 1.0) ;
	gl_Position = Projection * View * Model * vec4(v_position  + v_normal , 1.0) ;
}
