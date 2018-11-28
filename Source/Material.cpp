#include"Material.h"
#include"Texture.h"
Material::Material()
{
	Renderer = NULL;
	Skin = new TextureMaterial();
}

void Material::Bind()
{
	if (Renderer != NULL)
	{
		Shader::ActiveShader.push_back(Renderer);
		Renderer->Enable();

		Shader::GetActiveShader()->SetUniform3f("MaterialAmbient", SurfaceColor.Ambient);
		Shader::GetActiveShader()->SetUniform3f("MaterialDiffuse", SurfaceColor.Diffuse);
		Shader::GetActiveShader()->SetUniform3f("MaterialSpecular", SurfaceColor.Specular);

	}
	if (Skin != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		Skin->Texture.Bind();
		Shader::GetActiveShader()->SetTexture("DiffuseTexture", 0);


//	glActiveTexture(GL_TEXTURE1);
//	Skin->NormalsTexture.Bind();
//	glActiveTexture(GL_TEXTURE2);
//	Skin->GlowTexture.Bind();
//	glActiveTexture(GL_TEXTURE3);
//	Skin->SpecularTexture.Bind();

		Skin->TextureCoords.Bind();
	}
}
void Material::Unbind()
{
	if (Skin != NULL)
	{
		Skin->Texture.Unbind();
		Skin->TextureCoords.Unbind();
	}
	if (Renderer != NULL)
	{
		Shader::GetActiveShader()->Disable();
		Shader::ActiveShader.pop_back();
	}
}

void Material::Attach(Skinenum style, Image *skin)
{
	switch (style)
	{
	case SKIN_DIFFUSE:
		Skin->Texture = *skin;
		break;
	case SKIN_NORMALS:
		Skin->NormalsTexture = *skin;
		break;
	case SKIN_GLOW:
		Skin->GlowTexture = *skin;
		break;
	case SKIN_SPECULAR:
		Skin->SpecularTexture = *skin;
		break;
	default:
		EngineErrorResponse(0x123, NULL, "Improper Texture Format");

    }
};
void Material::SetSurfaceColor(Vec3 A, Vec3 D, Vec3 S)
{
	SurfaceColor.Ambient = A;
	SurfaceColor.Diffuse = D;
	SurfaceColor.Specular = S;
}
void Material::SetTextureCoords(UVBuffer coords)
{
	Skin->TextureCoords = coords;
}





Material* BrickMaterial()
{
	Material *ret = new Material();
	ret->SetRenderer(Shader::GetActiveShader());
	ret->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("BrickDiffuse"));
	ret->Attach(SKIN_NORMALS, Image::Manager.GetAsset("BrickNormals"));
	return ret;
}