#pragma once
#include"Window.h"



class Light
{
public:
	Light();
	Light(Vec3 pos);
	Light(Vec3 pos, Vec3 ambient, Vec3 diffuse, Vec3 specular);

	enum Lighttype
	{
		Ambient,
		Diffuse,
		Specular
	};
	void SetRotation(Vec3 rot);
	void SetPosition(Vec3 pos);
	void Set(Lighttype which, Vec3 value);
	void Set(Vec3 ambient, Vec3 diffuse, Vec3 specular);

	void Bind();
	void Unbind();
private:
	Vec3 AmbientColor = Vec3(0.2f);
	Vec3 DiffuseColor = Vec3(0.5f);
	Vec3 SpecularColor = Vec3(1.0f);

	Vec3 Position;
	Vec3 Rotation;
};






// vec3 ambient = light.ambient * material.ambient;
// vec3 diffuse = light.diffuse * (diff * material.diffuse);
// vec3 specular = light.specular * (spec * material.specular);



