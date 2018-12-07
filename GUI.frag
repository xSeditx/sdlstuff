#version 130
#pragma debug(off)



in vec3 Fposition;
in vec4 Fcolor;
in vec3 FNormal;

void main()
{
    vec3 LightColor = vec3(1.0, 1.0, 1.0);
	float distance = length(LPos - Fposition);
    vec3 Norm = texture(NormalsTexture, gl_TexCoord[0].st).xyz;
    Norm = normalize(Norm * 2.0 - 1.0);

	//Norm *= dot(FNormal, Norm);

    vec3 LightDir = normalize(LPos - Fposition);

    vec3 diffuse = max(dot(Norm, LightDir), 0.1) * LightColor;

    diffuse = diffuse * (1.0 / (1.0 + (0.00125 * (distance * distance))));
    vec4 result = texture(DiffuseTexture, gl_TexCoord[0].st); // (diffuse) * 
    gl_FragColor =  result * diffuse; // vec4(result, 1.0)
}
 







