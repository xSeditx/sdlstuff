#pragma once
#include"window.h"
#include"buffers.h"
#include"material.h"


class Object
{
public:
	Object::Object();

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;


	void SetRotation(Vec3 rot) { Rotation = rot; }
	void SetPosition(Vec3 pos) { Position = pos; }
	void SetScale(Vec3 scale)  { Scale = scale;  }

	Vec3 Get_Position() { return Position; }
	Vec3 Get_Rotation() { return Rotation; }
	Vec3 Get_Scale()    { return Scale;    }

	inline void Object::Add(VAOBuffer *vao)    { Polygons = vao; }
	inline void Object::Add(Material *surface) { Surface = surface; }

	void LoadOBJ(char *file);

private:

	Vec3 Position = Vec3(1.0f);
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale = Vec3(1.0f);

	Matrix Transform;

	VAOBuffer *Polygons;
	Material *Surface;

	GLuint VAO;

};


class Mesh : public Object
{
public:
	Mesh();

	void Bind() override;
	void Unbind() override;
	void Render() override;
	void Update() override;
};