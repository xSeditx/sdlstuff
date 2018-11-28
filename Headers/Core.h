#pragma once
#include"Renderer.h"
#include"Light.h"
#include"material.h"
#include"mesh.h"

///      ENGINE 
/*=============================================================================================================================================================
//
//      ENGINE MODULE
//
=============================================================================================================================================================*/

/*===============================================================================================================================================================


This handles buffers but not all:

Scene->Groups->Mesh->Polygon->Buffers;

Mesh
=====
--Material
_____________
----Shader
----Lighting
----Normals
----Texture
-------- UVBuffer
-------- Image
--Polygon
_____________
---- Indices
---- Vertices
---- Normals
---- Colors

=================================================================================================================================================================*/


//---------------------------------------------------------------------------------------------------------------------------------------------------------------


class Group
{
public:
	Group();
	Vec3 Position = Vec3(0.0f);
	Vec3 Rotation = Vec3(0.0f);

	std::vector<Mesh> Objects;
	Material *Surface;

	int ObjectCount = 0;

	void Add(Mesh object);
	void Attach(Material *surface);
	void Bind();
	void Unbind();
	void Update();
	void Render();
};
class Scene
{
public:
	Scene();
	Scene(Material *renderer);

	std::vector<Group> Groups;
	std::vector<Light> Lights;

	int LightCount = 0;
	int GroupCount = 0;

	Viewport Camera;
	Material *Surface;

	void Update();
	void Render();

	void AddGroup(const Group& group);
	void AddLight(const Light& light);
	void Attach(Material *renderer);
	void Attach(Viewport camera);
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------

