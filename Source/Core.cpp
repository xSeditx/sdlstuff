#include"core.h"


Scene::Scene()
{
	Surface = NULL;
	//Groups.push_back(Group());
	AddGroup(Group());
}
Scene::Scene(Material *renderer)
{
	Surface = renderer;
	Groups.push_back(Group());
}
void Scene::Update()
{
	Camera.Update();
	for (auto& G : Groups)
	{
		G.Update();
	}
}
void Scene::Render()
{
 
	Lights[0].Bind();
//	Lights[0].Render();

	if (Surface != NULL)
	{
		Surface->Bind();
	}
	{			
		Camera.Update();

		for (auto& G : Groups)
		{
			G.Render();
		}
	}
}
void Scene::AddGroup(const Group& group)
{
	Groups.push_back(group);
	GroupCount++;
}
void Scene::AddLight(const Light& light)
{
	Lights.push_back(light);
	LightCount++;
}
void Scene::Attach(Material *renderer)
{
	Surface = Surface;
}
void Scene::Attach(Viewport camera)
{
	Camera = camera;
}
 


Group::Group()
{
	Surface = NULL;
}
void Group::Add(Mesh object)
{
	Objects.push_back(object);
	ObjectCount++;
}
void Group::Add(Mesh object, Material *surface)
{
	object.Add(surface);
	Objects.push_back(object);
	ObjectCount++;
}

void Group::Attach(Material *surface)
{
	Surface = surface;
}
void Group::Bind()
{
#ifdef _OPENGL_FIXED_FUNCTION
	_TRANSFORM();
#endif
	if (Surface != NULL)
	{
		Surface->Bind();
	}
}
void Group::Unbind()
{
	if (Surface != NULL)
	{
		//	Surface->Unbind();
	}
#ifdef _OPENGL_FIXED_FUNCTION
	glPopMatrix();
#endif
}
void Group::Update()
{
	for (auto& M : Objects)
	{
		M.Update();
	}
}
void Group::Render()
{
	Bind();
	for (auto& M : Objects)
	{
		M.Render();
	}
	Unbind();
}


//	vec3 AmbientColor = Vec3(0.2f);
//	vec3 DiffuseColor = Vec3(0.5f);
//	vec3 SpecularColor = Vec3(1.0f);
//
//	Vec3 Position;
//	Vec3 Rotation;
//
//Matrix Transform;
//
//VAOBuffer *Polygons;
//Material *Surface;
//GLuint VAO;
//void Object::Add(VAOBuffer *vao) { Polygons = vao; }
//void Object::Add(Material *surface) { Surface = surface; }
//
//virtual void Bind() = 0;
//virtual void Unbind() = 0;
//virtual void Update() = 0;
//virtual void Render() = 0;
//};
//
//	for (auto&L : Lights)
//	{
//glUseProgram(0);
//glPointSize(6);
//glBegin(GL_TRIANGLES);
//glColor3f(1, 1, 1);//GL_Color(Lights[0].AmbientColor.r), GL_Color(Lights[0].AmbientColor.g), GL_Color(Lights[0].AmbientColor.b));
//glVertex3f(0, 0, 10);
//glVertex3f(0 + 10, 0, 0 + 10);
//glVertex3f(0, 0 + 10, 0);
//glEnd();
//glUseProgram(Shader::GetActiveShader()->GetName());
//	}