#version 150

in vec2 outTexCoord;

uniform sampler2D texUnit;

out vec4 fragColor;

// Lec4 p39
void main(void)
{
	vec4 col = texture(texUnit, outTexCoord);

	fragColor.r = max(col.r - 1.0, 0.0);
	fragColor.g = max(col.g - 1.0, 0.0);
	fragColor.b = max(col.b - 1.0, 0.0);
}

