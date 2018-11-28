#pragma once
#include"window.h"
#include"buffers.h"
#include"material.h"


class Object
{
public:
	Object::Object();

	Vec3 Position = Vec3(1.0f);
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale = Vec3(1.0f);

	Matrix Transform;

	VAOBuffer *Polygons;
	Material *Surface;
	GLuint VAO;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	inline void Object::Add(VAOBuffer *vao) { Polygons = vao; }
	inline void Object::Add(Material *surface) { Surface = surface; }
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