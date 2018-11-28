#version 130
#pragma debug(off)

varying vec4 Fcolor;
varying lowp vec4 Fnorm;

uniform sampler2D DiffuseTexture;

void main()
{
    vec4 Color = texture2D(DiffuseTexture, gl_TexCoord[0].st);
    gl_FragColor = Color * Fcolor;
}