#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// TODO: compute world space vectors
	vec3 world_position = vec3( Model * vec4(v_position, 1));
	vec3 world_normal = normalize(vec3( Model * vec4(v_normal, 0)));
	vec3 V = normalize(eye_position - world_position);
	vec3 L = normalize(light_position - world_position);
	vec3 N = normalize(world_normal);
	vec3 H = normalize( L + V );


	// TODO: define ambient light component
	float ambient_light = 2 * material_kd * 0.25 ;

	/// TODO: compute diffuse light component
	// float difuza = Kd * intensitateLumina * max (dot(N,L), 0); 
	float diffuse_light = material_kd * max (dot(N, L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		// float speculara = Ks * intensitateLumina * primesteLumina * pow(max(dot(N, H), 0), n
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	// TODO: compute light
	//float intensitate = emisiva + ambientala + factorAtenuare * ( difuza + speculara )
	//float factorAtenuare = 1/(pow(distance(light_position, v_position), 2));
	float factorAtenuare = 1/(pow(distance(light_position, world_position), 2));
	float light = ambient_light + (specular_light + diffuse_light) * factorAtenuare;

	// TODO: send color light output to fragment shader
	color = object_color * light;
	
	// TODO: send color light output to fragment shader
	//color = vec3(1);
	//Comentata pentru tema  - asta de jos nu era comentata
	//color = object_color * (ambient_light + (specular_light + diffuse_light) * factorAtenuare);

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
