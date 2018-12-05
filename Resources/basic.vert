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
attribute vec4 VertexColor;
attribute vec4 VertexNormal;              

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
    Fcolor = VertexColor;
	FNormal   =    VertexNormal.xyz;    
	Fposition =   VertexPosition.xyz;   
	LPos = LightPosition1;

	gl_TexCoord[0] = gl_MultiTexCoord0;   
    gl_Position = ProjectionMatrix *  ModelViewMatrix * VertexPosition;
}


//   vec3(CameraPos * vec4(VertexNormal.xyz,  1.0));   // 
// vec3(normalize(CameraPos * vec4(VertexPosition.xyz, 1.0)));	//
//  ((VertexNormal * .2) + VertexPosition); < adjust the vertex position to move towards the normal
//   Diffuse = MaterialDiffuse.rgb;
//    Ambient = MaterialAmbient.rgb;
//  vec3 EyePosition = vec3(ModelViewMatrix[12], ModelViewMatrix[13], ModelViewMatrix[14])
