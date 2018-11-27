#pragma once

#include"Window.h"
#include"Renderer.h"


/*==============================================================================================================================================================
                                                        MATERIAL CLASS
				Contains the surface Color, Vertex Colors, per Object shader if applicable
==============================================================================================================================================================*/


class Material
{
public:

	Material();

	struct
	{
		Vec3
			Ambient = Vec3(.2),
			Diffuse = Vec3(.5),
			Specular = Vec3(1.0f);
	}SurfaceColor;
	struct
	{
		Image Texture;
		Image NormalsTexture;
		Image GlowTexture;
		Image SpecularTexture;
		UVBuffer TextureCoords;
	}*Skin;

	void SetSurfaceColor(Vec3 A, Vec3 D, Vec3 S);
	void Bind();
	void Unbind();


	inline void SetRenderer(Shader *program) { Renderer = program; }
	inline Shader *GetRenderer() { return Renderer; }
private:

	float Shine = .2f;
	Shader *Renderer = NULL;
};
