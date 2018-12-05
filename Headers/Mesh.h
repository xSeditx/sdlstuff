#pragma once
#include"window.h"
#include"buffers.h"
#include"material.h"


/*

WE IMPLIMENT THE API AS SUCH. 

Make your Object via the appropriate object type,

Sprite generally for HUD or Sprites since it produces a renderable Quad containing a Texture Material whos UV coords can be adjusted for various animation effects.

Mesh is generally for 3D objects, Primatives are avalible for creation and are derived from the Mesh class as well as an OBJ loader( currently not working ).


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

USE: Create your object, 
Set its Position 
Set its Rotation( generally in part the job of the Ctor of the Object type if its a Primative Object ) 
Set its Scale (normally just 1.0f but other values are acceptable yet may lead to problems and one should be cautious )

Add a Material to the object using the Add(Material *) method;
Add a VAOBuffer via Add(VAOBuffer *vao) if needed For Added Flexibility in future use. Allows for the creation of a blank object which can be built later.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------


The Following Methods of the Object class are pure Virtual and are implemented in the Appropriate Derived class type

void Bind() override;
---- Binds all your Buffers Via a VAOBuffer Bind which handles all the binding of any Buffers and VAOs it has. 
---- It also binds any Materials the Object contains and sets up and Uniforms and Texture Samplers the Shaders will need

void Unbind() override;
---- Reverses the process of the Above clearing OpenGLs state for the various stuff

void Render() override;
---- Handles the Bind() function described above...
---- Performs the Drawcall for the Object rendering it to the screen or currently active Framebuffer

void Update() override;
---- Updates any Transforms or Uniforms that will need to be bound using bind. This allows for seperation of the Rendering from the Physics if Implemented properly.

*/

class Object
{
public:
	Object::Object();

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;


	void Set_Rotation(Vec3 rot) { Rotation = rot; }
	void Set_Position(Vec3 pos) { Position = pos; }
	void Set_Scale(Vec3 scale)  { Scale = scale;  }
	void Set_Transform(Matrix mat) { Transform = mat; }


	Vec3 Get_Position() { return Position; }
	Vec3 Get_Rotation() { return Rotation; }
	Vec3 Get_Scale()    { return Scale;    }
	Material Get_Surface() { return *Surface; }

	inline void Object::Add(VAOBuffer *vao)    { Polygons = vao; }
	inline void Object::Add(Material *surface) { Surface = surface; }

	void LoadOBJ(char *file);



protected:

	Vec3 Position = Vec3(1.0f);
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale = Vec3(1.0f);

	Matrix Transform;

	VAOBuffer *Polygons;
	Material *Surface;
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