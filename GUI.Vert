#version 130
#pragma debug(off)
precision lowp vec4;
precision lowp vec3;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
 
//-------------------------------------------------------------------------
//         VERTEX ATTRIBUTES IN
attribute vec4 VertexPosition;
attribute vec4 VertexColor;
            

 
//=========================================================================

//-------------------------------------------------------------------------
//    VERTEX COLOR AND NORMAL OUT
out vec4 Fcolor;
out vec3 Fposition;
 
 


void main()
{
    Fcolor = VertexColor;
	Fposition =   VertexPosition.xyz;    // vec3(normalize(CameraPos * vec4(VertexPosition.xyz, 1.0)));	//
	LPos = LightPosition1;

 	gl_TexCoord[0] = gl_MultiTexCoord0;   
    gl_Position = ProjectionMatrix *  ModelViewMatrix * VertexPosition; 

}
