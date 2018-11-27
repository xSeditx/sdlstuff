///                                             SHADER MODULE
/*===============================================================================================================================================================
//
//
//                             SHADER MODULE
//
//
=================================================================================================================================================================*/


#include"Shader.h"

std::vector<Shader *> Shader::ActiveShader;


Shader::Shader(const char* vertpath, const char* fragpath)
	: m_Vertpath(vertpath), m_Fragpath(fragpath)
{
	ID = Load();
	ActiveShader.push_back(this);

	_GL(glUseProgram(ID));
	 
//	VertexLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexPosition");
//	glEnableVertexAttribArray(VertexLocation);
//	glVertexAttribPointer(VertexLocation, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
//	 
//	//NormalsLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexNormal");
//	//glEnableVertexAttribArray(NormalsLocation);
//	//glVertexAttribPointer(NormalsLocation, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
//	 
//	ColorsLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexColor");
//	glEnableVertexAttribArray(ColorsLocation);
//	glVertexAttribPointer(ColorsLocation, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
	 
	MVPLocation = GetUniformLocation("ModelViewProjectionMatrix");
	 
}
Shader::Shader()
{
	Print("Default Shader Constructor Called");
}
Shader::~Shader()
{
	Delete();
}
void Shader::Delete()
{
	Print("Called the Shader Destructor: " << m_Fragpath);
	glDeleteProgram(ID);
}
void Shader::Enable()
{
	
	if (GetActiveShader()->ID != this->ID)
	{
		glUseProgram(ID);
		MVPLocation = GetUniformLocation("ModelViewProjectionMatrix");
		for (auto &Uni : Uniforms)
		{
			switch (Uni.Type)
			{

			case(Float):
				SetUniform1f(Uni.Name, *(float*)Uni.Value);
				break;
			case(Integer):
				SetUniform1Int(Uni.Name, *(int*)Uni.Value);
				break;
			case(Vector2):
				SetUniform2f(Uni.Name, *(Vec2*)Uni.Value);
				break;
			case(Vector3):
				SetUniform3f(Uni.Name, *(Vec3*)Uni.Value);
				break;
			case(Vector4):
				SetUniform4f(Uni.Name, *(Vec4*)Uni.Value);
				break;
			case(Matrix4):
				SetUniformMat4(Uni.Name, *(Matrix*)Uni.Value);
				break;
			}
		}
	}
}
void Shader::Disable()
{
	glUseProgram(0);
}
 
void Shader::SetUniform1f(GLchar *name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}
void Shader::SetUniform1Int(GLchar *name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform2f(GLchar *name, Vec2 &vector)
{
	glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}
void Shader::SetUniform3f(GLchar *name, Vec3 &vector)
{
	_GL(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
}
void Shader::SetUniform4f(GLchar *name, Vec4 &vector)
{
	glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}
void Shader::SetUniformMat4(GLchar *name, Matrix &matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetTexture(GLchar *name, int slot)
{
	glUniform1i(GetUniformLocation(name), slot);
}
void Shader::AttachUniform(GLchar *name, Uniformtype type, void *variable)
{
	Uniforms.push_back(Uniform(type, name, variable));
}
void Shader::SetCacheUniforms(Matrix mvp)
{
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}

GLint Shader::GetUniformLocation(GLchar *name)
{
	return glGetUniformLocation(ID, name);
}
GLuint Shader::GetName()
{
	return ID;
}
GLuint Shader::Load()
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSourceString = FileUtils::read_file(m_Vertpath);
	std::string fragSourceString = FileUtils::read_file(m_Fragpath);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	_GL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed to compile VertexShader: " << &error[0] << std::endl;
		glDeleteShader(vertex);
		EngineErrorResponse(0x10, fragment, (char*)m_Fragpath);
		return 0;
	}
	 
	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);
	_GL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed to compile Fragment Shader:" << &error[0] << std::endl;
		glDeleteShader(fragment);
		EngineErrorResponse(0x11, fragment, (char*)m_Fragpath);
		return 0;
	}
	 
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	 
#if	_OPENGL_FIXED_FUNCTION
#else
	//		VertexLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexPosition");
	//		NormalsLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexNormal");
	// 		ColorsLocation = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexColor");

	//	 glBindAttribLocation(vertex, 1, "VertexPosition"); // The index passed into glBindAttribLocation is
	//	 glBindAttribLocation(vertex, 2, "VertexNormals");
	//glBindAttribLocation(program, 3, "TextureCoords"); // used by glEnableVertexAttribArray. "position"   
	//	 _GL(glBindAttribLocation(vertex, 3, "VertexColor"));
#endif

	glLinkProgram(program);
	_GL(glGetProgramiv(program, GL_LINK_STATUS, &result));
	if (result == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetProgramInfoLog(program, length, &length, &error[0]);
		std::cout << "Link Fail " << &error[0] << std::endl;
		glDeleteShader(program);
		EngineErrorResponse(0x12, program, (char*)m_Vertpath);
		return 0;
	}
	_GL(glValidateProgram(program));
	 
	int param;
	glGetProgramiv(program, GL_ATTACHED_SHADERS, &param);
	Print(param);
	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	_GL(glDeleteShader(fragment));
	 
	return program;

}



// STATIC 
Shader* Shader::GetActiveShader()
{
	return ActiveShader.back();
}

GLuint Shader::VertexLocation;
GLuint Shader::ColorsLocation;
GLuint Shader::NormalsLocation;
