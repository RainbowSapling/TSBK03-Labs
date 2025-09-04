#version 150

in float shade;
in vec2 texCoord;
in vec2 frag_texcoord;
in vec3 exNormal;

uniform sampler2D exampletexture;
uniform float time;

out vec4 out_Color;

void main(void)
{
	float r = sin(time);
	float g = cos(time);
	float b = tan(time);

	const vec3 light = vec3(0.58, 1.0, 0.58);
	float diffuse = dot(normalize(exNormal), light);
	diffuse = max(0.0, diffuse);

	const vec3 light2 = vec3(0.2, 0.4, 0.2);
	float diffuse2 = dot(normalize(exNormal), light2);
	diffuse2 = max(0.0, diffuse2);


	float lightSource = 0.7*diffuse + 0.1;
	float lightSource2 = 0.2*diffuse2 + 0.5;

	//out_Color=vec4(shade,shade,shade,1.0);
	out_Color=vec4(lightSource2, lightSource2/5, lightSource,1.0);
	//out_Color=vec4(shade*r,shade*g,shade*b,1.0);
	//out_Color=texture(exampletexture,frag_texcoord);
}

