#include"Mesh.h"


Object::Object()
{
	Vec3 Position = Vec3(1.0f);
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale = Vec3(1.0f);
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
	Shader::GetActiveShader()->SetCacheUniforms(MVP * Transform); //SetUniformMat4("ModelViewProjectionMatrix", MVP * Transform);
#endif
}
void Mesh::Unbind()
{
#if _DEBUG
	//Polygons->Unbind();
	//if (Surface != NULL)
	//	{
	//		Surface->Unbind();
	//	}
#endif
#ifdef _OPENGL_FIXED_FUNCTION
	glPopMatrix();
#endif
}
void Mesh::Render()
{
	Update();
	Bind();
	//	BenchMark Performance;
	_GL(glDrawElements(GL_TRIANGLES, Polygons->Indices->ElementCount, GL_UNSIGNED_INT, nullptr));
	//	glBindVertexArray(0);

	Unbind();

}
void Mesh::Update()
{
	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::translate(Transform, Position);
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
}