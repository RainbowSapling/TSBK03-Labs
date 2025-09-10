#version 150
// bump mapping should be calculated
// 1) in view coordinates
// 2) in texture coordinates

in vec2 outTexCoord;
in vec3 out_Normal; // Normalvektor
in vec3 Ps; // Tangentvektor
in vec3 Pt; // Bitangent
in vec3 pixPos;  // Needed for specular reflections
uniform sampler2D texUnit;
out vec4 out_Color;

void main(void)
{
    vec3 light = vec3(0.0, 0.7, 0.7); // Light source in view coordinates

	// Calculate gradients here
	float offset = 1.0 / 256.0; // texture size, same in both directions

    vec3 normal = normalize(out_Normal);
	// Simplified lighting calculation.
	// A full solution would include material, ambient, specular, light sources, multiply by texture.

    //"The calculation of bs and bt are done with a simple subtraction between two neighbor texels in the bump map"
	//bs = b[s+1,t] - b[s,t]
	//bt = b[s,t+1] - b[s,t] (Book p77)
	//+1 = offset
    //Needs to be vec3 inorder to multiply with Ps and Pt
	vec3 bs = vec3(texture(texUnit, vec2(outTexCoord.x + offset, outTexCoord.y)) - texture(texUnit, outTexCoord));
    vec3 bt = vec3(texture(texUnit, vec2(outTexCoord.x, outTexCoord.y+offset)) - texture(texUnit, outTexCoord));

	// modified normal = n + bs*Ps + bt*Pt  (Lec4 p62)
	vec3 normalView = normalize(normal - bs*Ps - bt*Pt); // Reversed direction for some reason?

    mat3 mvt = mat3(Ps,Pt,normal);

    vec3 lightTex = light * mvt;

	vec3 normalTex = normalize(vec3(-bs.x,-bt.x,1.0));
    //out_Color = vec4( max(0.0, dot(normalView, light))+0.4) * texture(texUnit, outTexCoord);
    //out_Color = vec4( max(0.0, dot(normalView, light))+0.4);
    out_Color = vec4( max(0.0, dot(normalTex, lightTex))+0.4);
}

