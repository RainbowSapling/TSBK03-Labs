#version 150

in  vec3  in_Position;
in  vec3  in_Normal;
in  vec2  in_TexCoord;

uniform mat4 projectionMatrix;
uniform mat4 modelToWorldToView;

uniform float time;

out float shade;
out vec2 frag_texcoord;
out vec3 exNormal;


mat3 rotateX = mat3( 1.0, 0.0, 0.0,
                     0.0, cos(time), -sin(time),
                     0.0, sin(time), cos(time));

mat3 rotateY = mat3( cos(time), 0.0, sin(time),
                     0.0, 1.0, 0.0,
                     -sin(time), 0.0, cos(time));

mat3 rotateZ = mat3( cos(time), -sin(time), 0.0,
                     sin(time), cos(time), 0.0,
                     0.0, 0.0, 1.0);

void main(void)
{
	exNormal = inverse(transpose(mat3(modelToWorldToView))) * in_Normal;
	shade = (mat3(modelToWorldToView)*in_Normal).z; // Fake shading
	frag_texcoord=in_TexCoord;
	gl_Position=projectionMatrix*modelToWorldToView*vec4(in_Position * rotateY, 1.0);
}

