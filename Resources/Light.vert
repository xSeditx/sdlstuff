// THIS SHADER IS CURRENTLY KIND OF IN THE WAY, WHAT I WANT IS TO BE ABLE, FOR DEBUG REASONS TO RENDER THE LOCATION IN 3D SPACE OF THE LIGHT WITH A NICE
// FADE/BLEND LOOK COMING OUT FROM THE SOURCE OF THE LIGHT.
// I NEED TO VISUALIZE THE LOCATION OF THE LIGHT AND FIGURED I MAY AS WELL MAKE IT LOOK GOOD WHILE I DO....


#version 130
#pragma debug(off)
precision lowp vec4;
precision lowp vec3;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 CameraPos;
//-------------------------------------------------------------------------
//         VERTEX ATTRIBUTES IN
attribute vec4 VertexPosition;
attribute vec4 VertexNormal;
attribute vec4 VertexColor;


//-------------------------------------------------------------------------
//           LIGHTING IN
uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;
uniform vec3 LightPosition1;

//=========================================================================

//-------------------------------------------------------------------------
//    VERTEX COLOR AND NORMAL OUT
out vec4 Fcolor;
out vec3 Fposition;
out vec3 FNormal;

//-------------------------------------------------------------------------
//        LIGHTING OUT
out vec3 Diffuse;
out vec3 Ambient;
out vec3 LPos;
//-------------------------------------------------------------------------
 
void main()
{

//  vec3 EyePosition = vec3(ModelViewMatrix[12], ModelViewMatrix[13], ModelViewMatrix[14])
//  Fcolor = VertexColor;
	FNormal   =  VertexNormal.xyz;      // vec3(CameraPos * vec4(VertexNormal.xyz,  1.0));   // 
	Fposition =   vec3(normalize(CameraPos * vec4(VertexPosition.xyz, 1.0)));	//VertexPosition.xyz;    // 

    Diffuse = MaterialDiffuse.rgb;
    Ambient = MaterialAmbient.rgb;

	LPos = LightPosition1;

	gl_TexCoord[0] = gl_MultiTexCoord0;   
    gl_Position = ProjectionMatrix *  ModelViewMatrix * VertexPosition;

}
