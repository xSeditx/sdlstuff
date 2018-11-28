#version 130
#pragma debug(off)
precision lowp vec4;
precision lowp vec3;

uniform mat4 ModelViewProjectionMatrix;

attribute vec4 VertexPosition;
attribute vec4 VertexNormal;
attribute vec4 VertexColor;

uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;

varying vec4 Fcolor;
varying vec4 Fnorm;

uniform sampler2D DiffuseTexture;

void main()
{
    Fcolor = VertexColor;
    Fnorm = VertexNormal;

	gl_TexCoord[0] = gl_MultiTexCoord0;   

    gl_Position = ModelViewProjectionMatrix * VertexPosition;
}


 