#version 150

in vec2 outTexCoord;

uniform sampler2D texUnit; //Original
uniform sampler2D texUnit2; //Bloom effect

out vec4 fragColor;

// Lec4 p39
void main(void)
{
    vec4 a = texture(texUnit, outTexCoord);
    vec4 b = texture(texUnit2, outTexCoord);

    fragColor = (a*0.5 + b*1.0);
}


