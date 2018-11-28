#version 120
 
varying vec4 Fcolor;
 
void main()
{
gl_Position =  gl_ModelViewProjectionMatrix  * gl_Vertex;
Fcolor = gl_Color *.2;
}
 