#version 120
 
attribute vec4 Fcolor;
 
void main()
{

gl_Position = gl_Vertex;
Fcolor = gl_Color * .01;
}