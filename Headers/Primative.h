#pragma once
#include"renderer.h"
#include"core.h"


class Block :public Mesh
{
public:

	~Block() {}
	Block() {}
	Block(Vec3 pos, float size);

	int ID;

	GLuint VertexCount;

	std::vector<Vec3>    VertexList;
	std::vector<Vec3>    NormalList;
	std::vector<Vec2>    TextureCoords;
	std::vector<Vec4>    ColorList;
	std::vector<GLuint>  IndexList;

	// Vec3     Verts[24];
	// Vec3     Norms[24];
	// Vec2        UV[24];
	//	GLuint               Indice[36];

	IndexBuffer    *Indices;
	VertexBuffer   *Vertices;
	NormalBuffer   *Normals;

	//	Vec3                Color[24];
	ColorBuffer    *Colors;
};
class Sphere : public Mesh
{
public:
	// Vec3 Position;
	Vec3 Rotation;
	Vec3 Scale;

	int   Mesh_ID;

	float Radius;

public:// OpenGL Stuff

	Sphere() {}
	Sphere(Vec3 pos, float radius, int sectors);

	Vec3  Vertices[648];
	Vec3  Normals[648];
	GLuint Indices[972];
	RGBf  Colors[648];

	GLuint VertexCount;
	GLuint ColorCount;

	void Set_Position(float x, float y, float z) { Position = Vec3(x, y, z); }
	void Set_Position(Vec3 pos) { Position = pos; }
	void Set_Rotation(float x, float y, float z) { Rotation = Vec3(x, y, z); }
	void Rotate(float x, float y, float z);
	void SetRotation(Vec3 rot) { Rotation = rot; }

	Vec3 Get_Position() { return Position; }
	Vec3 Get_Rotation() { return Rotation; }
};

