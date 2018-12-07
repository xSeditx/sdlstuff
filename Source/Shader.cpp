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
#ifdef _OPENGL_FIXED_FUNCTION	 
#else
	ProjectionMatrixLOC = GetUniformLocation("ProjectionMatrix");
	ModelMatrixLOC = GetUniformLocation("ModelMatrix");
	ViewMatrixLOC = GetUniformLocation("ViewMatrix");
#endif
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
	
	if ( GetActiveShader()->ID != this->ID)
	{
		glUseProgram(ID);
		ActiveShader.push_back(this);
	//	MVPLocation = GetUniformLocation("ModelViewProjectionMatrix");
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
	ActiveShader.pop_back();
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
void Shader::SetCacheUniforms(Matrix m, Matrix v , Matrix p)
{
	glUniformMatrix4fv(ModelMatrixLOC, 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix4fv(ViewMatrixLOC, 1, GL_FALSE, glm::value_ptr(v));
	glUniformMatrix4fv(ProjectionMatrixLOC, 1, GL_FALSE, glm::value_ptr(p));
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
	glBindAttribLocation(program, 10, "VertexPosition");
	glBindAttribLocation(program, 12, "VertexColor");



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




void Shader::Push(Shader *shad)
{
	ActiveShader.push_back(shad);
}
Shader* Shader::Pop()
{
	Shader *ret = ActiveShader.back();
	ActiveShader.pop_back();
	return ret;
}