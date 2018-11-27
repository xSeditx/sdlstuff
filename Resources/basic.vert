#version 130
#pragma debug(off)
precision highp vec4;

uniform mat4 ModelViewProjectionMatrix;

attribute vec4 VertexPosition;
//attribute vec4 VertexNormal;
attribute vec4 VertexColor;


varying vec4 Fcolor;
//varying vec4 Fnorm;
void main()
{
Fcolor = VertexColor;
//Fnorm = VertexNormal;
gl_Position = ModelViewProjectionMatrix * VertexPosition;
}