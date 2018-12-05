#pragma once
#include"renderer.h"
#include"core.h"


class Block :public Mesh
{
public:

	~Block() {}
	Block() {}
	Block(Vec3 pos, float size);
	Block(Vec3 pos, float size, Material *surface);
	Material *Surface;
	int ID;
	GLuint VertexCount;
};


class Cube :public Mesh
{
public:

	~Cube() {}
	Cube() {}
	Cube(Vec3 pos, float size);
	Cube(Vec3 pos, float size, Material *surface);
	Material *Surface;
	int ID;
	GLuint VertexCount;
};



class Sphere : public Mesh
{
public:

	int   Mesh_ID;

	float Radius;

public:  // OpenGL Stuff

	Sphere() {}
	Sphere(Vec3 pos, float radius, int sectors);
	Sphere(Vec3 pos, float radius, int sectors, Material *surface);

	//Vec3  Vertices[648];
	//Vec3  Normals[648];
	//Vec2  UVcoord[684];
	//RGBf  Colors[648];
	//GLuint Indices[972];

	GLuint VertexCount;
	GLuint ColorCount;

	// void Set_Position(float x, float y, float z) { Position = Vec3(x, y, z); }
	// void Set_Position(Vec3 pos) { Position = pos; }
	// void Set_Rotation(float x, float y, float z) { Rotation = Vec3(x, y, z); }
	void Rotate(float x, float y, float z);

};
class Plane : public Mesh
{
public:
	~Plane() {}
	Plane(){}
	Plane(Vec3 pos, Vec3 rotation, float width, float height);
	Plane(Vec3 pos, Vec3 rotation, float width, float height, Material *surface);

	Vec2 Size;

};




class Torus : public Mesh
{
public:
	Torus(Vec3 position, int numc, int numt,  float scale);
	Torus(Vec3 position, int numc, int numt );

	void Render() override;
};