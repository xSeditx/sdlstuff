// THIS SHADER IS CURRENTLY KIND OF IN THE WAY, WHAT I WANT IS TO BE ABLE, FOR DEBUG REASONS TO RENDER THE LOCATION IN 3D SPACE OF THE LIGHT WITH A NICE
// FADE/BLEND LOOK COMING OUT FROM THE SOURCE OF THE LIGHT.
// I NEED TO VISUALIZE THE LOCATION OF THE LIGHT AND FIGURED I MAY AS WELL MAKE IT LOOK GOOD WHILE I DO....



#version 130
#pragma debug(off)


uniform sampler2D DiffuseTexture;
uniform sampler2D NormalsTexture;

 
//-------------------------------------------------------------------------
//        LIGHTING IN

in vec3 Diffuse;
in vec3 Ambient;
in vec3 LPos;


//-------------------------------------------------------------------------

 
in vec3 Fposition;
in vec4 Fcolor;
in vec3 FNormal;

void main()
{
    vec3 LightColor = vec3(1.0, 1.0, 1.0);
	float distance = length(LPos - Fposition);
    vec3 Norm = texture(NormalsTexture, gl_TexCoord[0].st).xyz;
    Norm = normalize(Norm * 2.0 - 1.0);

	Norm = -FNormal + Norm;

    vec3 LightDir = normalize(LPos - Fposition);

    vec3 diffuse = max(dot(Norm, LightDir), 0.1) * LightColor;

    diffuse = diffuse * (1.0 / (1.0 + (0.00125 * (distance * distance))));
    vec3 result = (diffuse) * texture(DiffuseTexture, gl_TexCoord[0].st);
    gl_FragColor =  vec4(result, 1.0);
}
 