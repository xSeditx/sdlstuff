#include"Mesh.h"


Object::Object()
{
	Vec3 Position = Vec3(1.0f);
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale = Vec3(1.0f);
}
void Object::LoadOBJ(char *path)
{
		//const char *filename = path.c_str();


		FILE *file = fopen(path, "r");

		if (file == nullptr)
		{
			printf("Impossible to open the file !\n");
			exit(0x20);
		}


		std::vector<Vec3> Vertices;
		std::vector<Vec3> Normals;
		std::vector<Vec2> UVCoords;
		std::vector<GLuint> Indices;

		while (TRUE)
		{

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
			{
				break; // EOF = End Of File. Quit the loop.
			}

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 Vert;
				fscanf(file, "%f %f %f\n", &Vert.x, &Vert.y, &Vert.z);
				Vertices.push_back(Vert);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				UVCoords.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				Normals.push_back(normal);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				glm::vec3 inds;
				fscanf(file, "%f %f %f\n", &inds.x, &inds.y, &inds.z);
				Indices.push_back(inds.x);
				Indices.push_back(inds.y);
				Indices.push_back(inds.z);
			}

		}

		Polygons = new VAOBuffer();
		Polygons->Attach(new VertexBuffer(&Vertices[0], Vertices.size()));
		Polygons->Attach(new IndexBuffer(&Indices[0], Indices.size()));
		Polygons->Attach(new NormalBuffer(&Normals[0], Normals.size()));
}

Mesh::Mesh()
{
	Surface = NULL;
}
void Mesh::Bind()
{
	if (Surface != NULL)
	{
		Surface->Bind(); // This seems like its going to get called to much. // If there is multiple levels The Uniforms are going to get passed way to much and I will have to call// Set uniform entirely to much unless I change something.// Make this the first stop if more performance is needed
	}

#ifdef _OPENGL_FIXED_FUNCTION
	_TRANSFORM();
	Polygons->Bind();
#else

	Polygons->Bind();
	Matrix MVP = Viewport::Camera->GetViewMatrix();
	Shader::GetActiveShader()->SetCacheUniforms(Transform, Viewport::Camera->ViewMatrix, Viewport::Camera->ProjectionMatrix);
	Shader::GetActiveShader()->SetUniformMat4("CameraPos", Viewport::Camera->ViewMatrix * Transform);
#endif
}
void Mesh::Unbind()
{

#ifdef _OPENGL_FIXED_FUNCTION
	glPopMatrix();
#endif
}
void Mesh::Render()
{
	Update();
	Bind();
	//Rotation.x++;
	//.y++;

	glDrawElements(GL_TRIANGLES, Polygons->ElementCount(), GL_UNSIGNED_INT, nullptr);
}
void Mesh::Update()
{
	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::translate(Transform, Position);
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
}




// Inside the main function we have to compute the eye vector, and the half - vector.
// To compute the eye vector we have to transform the vertex’s position with the View Model matrix(m_viewModel in the shader) to get it in Camera space.