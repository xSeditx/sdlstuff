#pragma once
#include"Renderer.h"
#include"Light.h"
#include"material.h"

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


class Sprite;

struct Quad
{
	Quad() {};
	Quad(int X, int Y, int W, int H)
		: x(X), y(Y), Width(W), Height(H) {}
	int x, y;
	int Height, Width;
};
struct Frame
{
public:
	Frame() {}
	Frame(Image*img, Quad f);

	Vec2 Coords[4];
	GLuint ID;

	void Bind();
	void Unbind();
};
class Animation
{
public:
	Animation() {}
	~Animation() {}

	Animation(Image *img, Quad sourcerect, uint numframes);
	Animation(Image *img, Quad srcrect, int border, GLuint numframes);

	std::vector<Frame> Frames;

	uint TotalFrames;
	uint CurrentFrame;

	GLint  AnimationSpeed;

	Animation operator +=(Frame newframe)
	{
		this->AddFrame(newframe);
		return *this;
	}
	Animation operator +=(Animation newstate)
	{
		for_loop(count, newstate.TotalFrames)
		{
			this->AddFrame(newstate.Frames[count]);
			this->TotalFrames++;
		}
		return *this;
	}

	bool PlayOnce;
	bool Stopped;
private:
	std::vector<Frame>& AddFrame(Frame frame);
};
class Sprite : public Object
{

	Sprite(char *name, Image *source, Vec2 dimensions, int numstates)
	{

	}

	int ID;

	GLuint CurrentState;

	std::vector<Animation> Animations;
	GLuint NumberofStates;

	float Timer;
	float AnimationTimer;
	float AnimationLength;


	bool Moving;     // Is it currently Animating
	bool Composite;  // Is it made up of multiple sprites
					 // _______________________________________________________________________________________________________________________
	void SetAnimationSpeed(float speed) { Speed = speed; }
	void ResetFrames() {}
public:
	void  Bind() override {}
	void  Unbind() override {}
	void  Update() override {}
	void  Render() override {}


	void  Render(Vec2 pos);






	char *Name;
	static AssetManager<Sprite> Manager;


private:
	float Speed;

};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

class Group
{
public:
	Group()
	{
		Surface = NULL;
	}

	Vec3 Position = Vec3(0.0f);
	Vec3 Rotation = Vec3(0.0f);

	std::vector<Mesh> Objects;
	Material *Surface;

	int ObjectCount = 0;

	void Add(Mesh object)
	{
		Objects.push_back(object);
		ObjectCount++;
	}
	void Attach(Material *surface)
	{
		Surface = surface;
	}

	void Bind()
	{
#ifdef _OPENGL_FIXED_FUNCTION
		_TRANSFORM();
#endif
		if (Surface != NULL)
		{
			Surface->Bind();
		}
	}
	void Unbind()
	{
		if (Surface != NULL)
		{
			Surface->Unbind();
		}
#ifdef _OPENGL_FIXED_FUNCTION
		glPopMatrix();
#endif
	}
	void Update()
	{
		for (auto& M : Objects)
		{
			M.Update();
		}
	}
	void Render()
	{
		Bind();
		for (auto& M : Objects)
		{
			M.Render();
		}
		Unbind();
	}
};
class Scene
{
public:
	Scene()
	{
		Surface = NULL;
		Groups.push_back(Group());
	}
	Scene(Material *renderer)
	{
		Surface = renderer;
		Groups.push_back(Group());
	}

	std::vector<Group> Groups;
	std::vector<Light> Lights;
	int LightCount = 0;
	int GroupCount = 0;

	Viewport Camera;
	Material *Surface;

	void Update()
	{
		for (auto& G : Groups)
		{
			G.Update();
		}
	}
	void Render()
	{

		if (Surface != NULL)
		{
			Surface->Bind();
		}
		{
			for (auto& G : Groups)
			{
				G.Render();
			}
		}
		if (Surface != NULL)
		{
			Surface->Unbind();
		}
	}

	void AddGroup(const Group& group)
	{
		Groups.push_back(group);
		GroupCount++;
	}
	void AddLight(const Light& light)
	{
		Lights.push_back(light);
		LightCount++;
	}

	void Attach(Material *renderer)
	{
		Surface = Surface;
	}
	void Attach(Viewport camera)
	{
		Camera = camera;
	}
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------

