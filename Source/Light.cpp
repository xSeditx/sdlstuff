#include"Light.h"
#include"Shader.h"

Light::Light() {}
Light::Light(Vec3 pos)
{
	Position = pos;
}
Light::Light(Vec3 pos, Vec3 ambient, Vec3 diffuse, Vec3 specular)
{
	Position = pos;
	Vec3 AmbientColor = ambient;
	Vec3 DiffuseColor = diffuse;
	Vec3 SpecularColor = specular;
}

void Light::SetRotation(Vec3 rot)
{
	Rotation = rot;
}
void Light::SetPosition(Vec3 pos)
{
	Position = pos;
}
void Light::Set(Lighttype which, Vec3 value)
{
	switch (which)
	{
	case Ambient:
		AmbientColor = value;
		break;

	case Diffuse:
		DiffuseColor = value;
		break;

	case Specular:
		SpecularColor = value;
		break;
	}
}
void Light::Set(Vec3 ambient, Vec3 diffuse, Vec3 specular)
{
	AmbientColor = ambient;
	DiffuseColor = diffuse;
	SpecularColor = specular;
}

void Light::Bind()
{
	Shader::GetActiveShader()->SetUniform3f("AmbientLight", AmbientColor);
	Shader::GetActiveShader()->SetUniform3f("DiffuseLight", DiffuseColor);
	Shader::GetActiveShader()->SetUniform3f("SpecularLight", SpecularColor);
}
void Light::Unbind()
{
}