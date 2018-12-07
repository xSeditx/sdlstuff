#version 130
#pragma debug(off)


uniform sampler2D DiffuseTexture;
uniform sampler2D NormalsTexture;

 
//-------------------------------------------------------------------------
//        LIGHTING IN

in vec3 Ambient;
in vec3 LPos;


//-------------------------------------------------------------------------
in vec3 Fposition;
in vec4 FColor;
in vec3 FNormal;
 

void main()
{ 

	float Distance = length(LPos - Fposition);
    vec3  LightVector = normalize(LPos - Fposition);                               // GET THE DIRECTION OF THE LIGHT VECTOR

    float Intensity = max(dot(FNormal , LightVector), 0.1);  
    Intensity = Intensity * (1.0 / (1.0 + (0.000025 * (Distance * Distance))));  

    vec3 result = texture(DiffuseTexture, gl_TexCoord[0].st).xyz;  

    gl_FragColor =  vec4(result,1.0f) * Ambient * Intensity;
}
 


  




















 //    vec3 NormalMap = texture(NormalsTexture, gl_TexCoord[0].st).xyz;

   //FColor = vec4( Intensity);                                                 
   //gl_TexCoord[0] = gl_MultiTexCoord0;                                        


//
//    vec3 LightColor = vec3(1.0, 1.0, 1.0);
//	float distance = length(LPos - Fposition);
//
//   vec3 Norm = texture(NormalsTexture, gl_TexCoord[0].st).xyz;
//  // Norm = normalize(Norm * 2.0 - 1.0);
//
//	//Norm *= dot(FNormal, Norm);
//
//   vec3 LightDir = normalize(LPos - Fposition);
//
//   vec3 diffuse = max(dot(Norm, LightDir), 0.1) * LightColor;
//
//   diffuse = diffuse * (1.0 / (1.0 + (0.00125 * (distance * distance))));
//   vec3 result = (diffuse) *  texture(DiffuseTexture, gl_TexCoord[0].st); // 
//   gl_FragColor =   vec4(result, 1.0);// * diffuse;// * (Fcolor * .5); //
//







// float3 LightDirection = LightPosition1 - EyePosition;
// float Distance = length(lightdir);
// LightDirection = LightDirection / Distance;
// Distance = Disttance * Distance;
// 
// float NdotL = dot( normal, lightDir );
// float Intensity = saturate( NdotL );
// 
// vec3 Diffuse =  Intensity * light.diffuseColor * light.diffusePower / distance