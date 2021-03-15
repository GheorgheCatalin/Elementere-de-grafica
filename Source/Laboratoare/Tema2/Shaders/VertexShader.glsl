#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform float Time;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform int deformation;
uniform int isSphere;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coord;
out vec3 frag_color;


void main()
{
	frag_position = v_position;
	frag_coord = tex_coord;
	 //+ v_position; //------------------------pt minge si ... diferit
	frag_normal = v_normal;

	if (isSphere == 1)
	{
		frag_color = object_color + v_position;

		if (deformation) {
		int frequency = 20;
		float displacement = 2 * sin(v_position.z * frequency * Time );

		gl_Position = Projection * View * Model * vec4(v_position + displacement * vec3(v_normal.x / 10, v_normal.y / 10, v_normal.z /10), 1.0);

		//gl_Position = Projection * View * Model * vec4(v_position + vNormal * sin(Time), 1.0);
		//gl_Position = Projection * View * Model * vec4(v_position + vec3(v_normal.x * sin(Time), v_normal.y / 5 * cos(Time), v_normal.z/10) , 1.0);
		}
		else {
			gl_Position = Projection * View * Model * vec4(v_position, 1.0) ;
		}
	}
	else 
	{
		frag_color = object_color;
		gl_Position = vec4(-1, -1, 1, 0) * vec4(v_position, 1.0) ;
	}
	// TODO: compute gl_Position
	//gl_Position = Projection * View * Model * vec4(v_position + vec3(sin(Time), 1 - sin(Time), 0), 1.0);
	//gl_Position = Projection * View * Model * vec4(v_position, 1.0) * vec4(vec3(1.7, 1.8, 0.2), 1.0) ;
	//gl_Position = Projection * View * Model * vec4(v_position  + v_normal , 1.0) ;
	//gl_Position = Projection * View * Model * vec4(v_position, 1.0) ;
}
