#version 150

in vec2 outTexCoord;

uniform sampler2D texUnit;

out vec4 fragColor;

// Lec4 p40
void main(void)
{
	vec2 texSize = textureSize(texUnit, 0);

	float offset = 1.0 / texSize[0];

	vec4 c = texture(texUnit, outTexCoord);

	vec4 l = texture(texUnit, outTexCoord + vec2(offset, 0.0));

	vec4 r = texture(texUnit, outTexCoord + vec2(-offset, 0.0));

	fragColor = (c + c + l + r) * 0.25;
}
