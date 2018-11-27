#include"Material.h"

Material::Material()
{
	Renderer = NULL;
	Skin = NULL;
}

void Material::SetSurfaceColor(Vec3 A, Vec3 D, Vec3 S)
{
	SurfaceColor.Ambient = A;
	SurfaceColor.Diffuse = D;
	SurfaceColor.Specular = S;
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
		Skin->Texture.Bind();
		Skin->TextureCoords.Bind();
	}
}
void Material::Unbind()
{
#if _DEBUG
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
#endif
}
