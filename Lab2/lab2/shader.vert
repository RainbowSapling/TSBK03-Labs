#version 150

//in vec3 in_Color;
in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
uniform mat4 matrix;

uniform mat4 Rbone1;
uniform mat4 Rbone2;
uniform mat4 Tbone1;
uniform mat4 Tbone2;

out vec4 g_color;
const vec3 lightDir = normalize(vec3(0.3, 0.5, 1.0));

// Uppgift 3: Soft-skinning på GPU
//
// Flytta över din implementation av soft skinning från CPU-sidan
// till vertexshadern. Mer info finns på hemsidan.

void main(void)
{
	mat4 Mbone1 = Tbone1*Rbone1;
	mat4 invMbone1 = inverse(Mbone1);
	mat4 altMbone1 = Mbone1*Rbone1;
	mat4 M1 = altMbone1*invMbone1;

	mat4 Mbone2 = Tbone2*Rbone2;
	mat4 invMbone2 = inverse(Mbone2);
	mat4 altMbone2 = Mbone2*Rbone2;
	mat4 M2 = altMbone1*altMbone2*invMbone2*invMbone1;

	vec3 newPos = vec3(in_TexCoord.x * M1 * vec4(in_Position,1.0) + in_TexCoord.y * M2 * vec4(in_Position,1.0));

	// transformera resultatet med ModelView- och Projection-matriserna
	//gl_Position = matrix * vec4(in_Position, 1.0);
	gl_Position = matrix * vec4(newPos, 1.0);

	// sätt röd+grön färgkanal till vertex Weights
	vec4 color = vec4(in_TexCoord.x, in_TexCoord.y, 0.0, 1.0);

	// Lägg på en enkel ljussättning på vertexarna
	float intensity = dot(in_Normal, lightDir);
	color.xyz *= intensity;

	g_color = color;
}

