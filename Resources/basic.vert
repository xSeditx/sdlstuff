#version 130
#pragma debug(off)
precision lowp vec4;
precision lowp vec3;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 CameraPos;
//-------------------------------------------------------------------------
//         VERTEX ATTRIBUTES IN
attribute vec4 VertexPosition;
attribute vec4 VertexColor;
attribute vec4 VertexNormal;              

//-------------------------------------------------------------------------
//           MATERIAL IN + LIGHTING IN

uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;

uniform vec3 AmbientLight;
uniform vec3 DiffuseLight;
uniform vec3 SpecularLight;

uniform vec3 LightPosition1;

 

//=========================================================================

//-------------------------------------------------------------------------
//    VERTEX COLOR AND NORMAL OUT
out vec4 FColor;
out vec3 Fposition;
out vec3 FNormal;

//-------------------------------------------------------------------------
//        LIGHTING OUT
//out vec3 Diffuse;
//out float Diffuse;
out vec3 Ambient;
out vec3 LPos;
//-------------------------------------------------------------------------

void main()
{
//----------------------------------------------------------------------------------------------------------------------
// TEMPORARY STUFF JUST FOR CLARITY. LATER TO BE REPLACED BY UNIFORMS AND ALL AROUND BETTER CODE
//----------------------------------------------------------------------------------------------------------------------

	mat4 ModelViewMatrix =  (ViewMatrix * ModelMatrix);                               // GET EYE SPACE MATRIX
	mat4 ModelViewProjectionMatrix =  (ProjectionMatrix * ViewMatrix *  ModelMatrix);  // GET THE MVP MATRIX

//----------------------------------------------------------------------------------------------------------------------
// TRANSFORM CORDS INTO EYE SPACE 
//----------------------------------------------------------------------------------------------------------------------

	FNormal   =  (ModelViewMatrix * vec4(VertexNormal.xyz, 0.0f)).xyz;            // NORMAL ORIENTATION IN EYE SPACE: NOTE: Notice the 0.0f in the Vec4 for VertexNormal. That has caused me issues I think.
	Fposition =  (ModelViewMatrix * vec4(VertexPosition.xyz, 1.0f)).xyz;          // EYE SPACE VERTEX
	LPos      =  (ViewMatrix * vec4(LightPosition1,  1.0f)).xyz;  // !! Already in World Space No Need for Translation like the above vertices and Normals !! // LIGHT POSITION IN WORLD SPACE !! 

//----------------------------------------------------------------------------------------------------------------------
    Ambient = MaterialAmbient * vec3(1,1,1);                               // VERTEX COLOR FROM GL COLOR BUFFER
    gl_TexCoord[0] = gl_MultiTexCoord0;                                     // GET THE TEXTURE COORD TO BE USED IN THE FRAGMENT SHADER. THIS TO WILL SOON BE A VERTEX ATTRIBUTE OF VertexUVCoords
    gl_Position = ModelViewProjectionMatrix * VertexPosition;
}





//  View matrix transforms worldspace to viewspace
//  Model matrix transforms object space to world space







//    Distance = length(LPos - Fposition);                                    // GET THE MAGNITUDE OF LIGHT VECTOR

//----------------------------------------------------------------------------------------------------------------------
// Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
// pointing in the same direction then it will get max illumination.
//----------------------------------------------------------------------------------------------------------------------

  //  float Intensity = max(dot(FNormal, LightVector), 0.1);  
//	Intensity = Intensity * (1.0 / (1.0 + (0.0025 * (Distance * Distance))));                  // FADE THE LIGHTING OVER DISTANCE







// FColor = VertexColor * Diffuse;
// gl_Position is a special variable used to store the final position.
// Multiply the vertex by the matrix to get the final point in normalized screen coordinates.
//  gl_Position = u_MVPMatrix * a_Position;
//    vec3 modelViewVertex = vec3(u_MVMatrix * a_Position);
// Transform the normal's orientation into eye space.
//    vec3 modelViewNormal = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
// Will be used for attenuation.
// LPos =       (ModelViewMatrix * vec4(LightPosition1.xyz, 1.0f)).xyz;          // EYE SPACE LIGHT POSITION

//vec3 modelViewVertex = vec3(u_MVMatrix * a_Position);
// Transform the normal's orientation into eye space.
//   vec3 modelViewNormal = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
//   vec3(CameraPos * vec4(VertexNormal.xyz,  1.0));   // 
// vec3(normalize(CameraPos * vec4(VertexPosition.xyz, 1.0)));	//
//  ((VertexNormal * .2) + VertexPosition); < adjust the vertex position to move towards the normal
//   Diffuse = MaterialDiffuse.rgb;
//    Ambient = MaterialAmbient.rgb;
//  vec3 EyePosition = vec3(ModelViewMatrix[12], ModelViewMatrix[13], ModelViewMatrix[14])
