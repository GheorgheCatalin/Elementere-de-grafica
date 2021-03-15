#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int is_spot;

layout(location = 0) out vec4 out_color;

void main()
{
	float light;
	float factorAtenuare;
	vec3 V = normalize(eye_position - world_position);
	vec3 L = normalize(light_position - world_position);
	vec3 N = normalize(world_normal);
	vec3 H = normalize( L + V );
	vec3 R = normalize(reflect(L, world_normal));

	// TODO: define ambient light component
	float ambient_light = 2 * material_kd * 0.25;

	// TODO: compute diffuse light component
	//float diffuse_light = material_kd * max (dot(N, L), 0); ---------------------------------------------
	float diffuse_light = material_kd * max(dot(L, N), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	if (is_spot == 0){
		factorAtenuare = 1/(pow(distance(light_position, world_position), 2));

		light = ambient_light + (specular_light + diffuse_light) * factorAtenuare;
	}
	else{
		float cut_off = radians(30);
		float spot_light = dot(-L, light_direction);
		if (spot_light > cos(cut_off)){
			float linear_att = (spot_light - cos(cut_off)) / (1.0f - cos(cut_off));
			factorAtenuare = pow(linear_att, 2);

			light =  ambient_light + (diffuse_light + specular_light) * factorAtenuare;
		}
		else {
			light =  ambient_light;
		}
	}

	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1);
}