#include"Buffers.h"
#include"Shader.h"

#ifdef _OPENGL_FIXED_FUNCTION
#    pragma message( "Compiling for Fixed Function Pipeline" )
#else
#    pragma message( "Compiling for Shader Based Programmable Pipeline" )
#endif



VertexBuffer::~VertexBuffer()
{
}

VertexBuffer::VertexBuffer(Vec4 *vertexdata, GLsizei vcount)
	: ElementCount(vcount),
	ID(0)
{
	Data = new Vec4[vcount];
	memcpy(Data, vertexdata, sizeof(Vec4) * vcount);
	_GL(glGenBuffers(1, &ID));
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec4), vertexdata, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::VertexBuffer(Vec3 *vertexdata, GLsizei vcount)
	: ElementCount(vcount),
	ID(0)
{
	Vec4 *tempdata = new Vec4[vcount];

	for_loop(Index, vcount)
	{
		tempdata[Index] = Vec4(vertexdata[Index].r, vertexdata[Index].g, vertexdata[Index].b, 1.0f);
	}
	*this = VertexBuffer(tempdata, vcount);
	delete[]tempdata;
}
void VertexBuffer::Bind()
{
#ifdef _OPENGL_FIXED_FUNCTION
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	_GL(glVertexPointer(4, GL_FLOAT, 0, (char *)NULL));
	glEnableClientState(GL_VERTEX_ARRAY);
#else
	glBindBuffer(GL_ARRAY_BUFFER, ID);
#endif
}

void VertexBuffer::Unbind()
{
 
#if _OPENGL_FIXED_FUNCTION
// 	glDisableClientState(GL_VERTEX_ARRAY);
// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
#else
#endif
 
}
void VertexBuffer::Lock(GLenum access)
{
	Data = (Vec4 *)glMapBuffer(ID, access);
}
void VertexBuffer::Unlock()
{
	glUnmapBuffer(ID);
}
void VertexBuffer::Rebuild()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ElementCount * sizeof(Vec4), Data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::Write(GLuint pos, GLfloat *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
//	Lock();
	glBufferSubData(GL_ARRAY_BUFFER, 0, ElementCount * sizeof(Vec3), Data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//==================================================================================================================================================
//__________________________________ INDEX BUFFER CLASS ____________________________________________________________________________________________

IndexBuffer::~IndexBuffer()
{// CREATE A DELETE BUFFER FUNCTION WHEN ALL DEBUGGING IS COMPLETE
}
IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
    : 
    ElementCount(count),
    ID(0)
{
	Data = new GLuint[count];
	memcpy(Data, data, sizeof(GLuint) * count);

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void IndexBuffer::Bind()
{
#ifdef _OPENGL_FIXED_FUNCTION
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glIndexPointer(GL_FLOAT, 0, (void *)NULL);
	glEnableClientState(GL_INDEX_ARRAY);
#else
	_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
#endif
}
void IndexBuffer::Unbind()
{// CREATE A DELETE BUFFER FUNCTION WHEN ALL DEBUGGING IS COMPLETE
}

//==================================================================================================================================================
//__________________________________ COLOR BUFFER CLASS ____________________________________________________________________________________________

ColorBuffer::~ColorBuffer()
{// CREATE A DELETE BUFFER FUNCTION WHEN ALL DEBUGGING IS COMPLETE
}
ColorBuffer::ColorBuffer(Vec4 *ColorData, GLsizei count)
	: ElementCount(count),
	ID(0)
{
	Data = new Vec4[count];
	memcpy(Data, ColorData, sizeof(Vec4) * count);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec4), ColorData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind BUFFER_ID since its now bound to the ID;
}
void ColorBuffer::Bind()
{
#ifdef _OPENGL_FIXED_FUNCTION
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glColorPointer(4, GL_FLOAT, 0, (char *)NULL);
	glEnableClientState(GL_COLOR_ARRAY);
#else
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glVertexAttribPointer(Shader::ColorsLocation, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
#endif

}
void ColorBuffer::Unbind()
{
}

//==================================================================================================================================================
//__________________________________ NORMAL BUFFER CLASS ___________________________________________________________________________________________
// TODO: Much work needs to be done here.
NormalBuffer::~NormalBuffer()
{
	//    glDeleteBuffers(1, &ID);
}
NormalBuffer::NormalBuffer(Vec4 *NormalData, GLsizei count)
	: ElementCount(count),
	ID(0)
{
	Data = new Vec4[count];
	memcpy(Data, NormalData, sizeof(Vec4) * count);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec4), NormalData, GL_STATIC_DRAW);
	_GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void NormalBuffer::Bind()

{
#ifdef _OPENGL_FIXED_FUNCTION
	glBindBuffer(GL_ARRAY_BUFFER, ID); // 
	glNormalPointer(GL_FLOAT, 0, (void *)NULL);
	_GL(glEnableClientState(GL_NORMAL_ARRAY));
#else
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glVertexAttribPointer(Shader::NormalsLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
#endif
}
void NormalBuffer::Unbind()
{
}

NormalBuffer::NormalBuffer(Vec3 *NormalData, GLsizei vcount)
	: ElementCount(vcount),
	ID(0)
{
	Vec4 *tempdata = new Vec4[vcount];

	for_loop(Index, vcount)
	{
		tempdata[Index] = Vec4(NormalData[Index].r, NormalData[Index].g, NormalData[Index].b, 1.0f);
	}
	*this = NormalBuffer(tempdata, vcount);
	delete[]tempdata;
}

//==================================================================================================================================================
//__________________________________ SIMULATED VAO CLASS ___________________________________________________________________________________________

VAOBuffer::VAOBuffer()
{
	Vertices = nullptr;
	Normals = nullptr;
	Textures = nullptr;
	Indices = nullptr;
	Colors = nullptr;
	Woven = false;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
void VAOBuffer::Attach(VertexBuffer  *vertices)
{
	Vertices = vertices;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, Vertices->ID);

	GLuint Vpoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexPosition");
	glEnableVertexAttribArray(Vpoint);
	_GL(glVertexAttribPointer(Vpoint, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL));
}
void VAOBuffer::Attach(IndexBuffer   *indices)
{
	Indices = indices;
	Indices->Bind();
}
void VAOBuffer::Attach(NormalBuffer  *normals)
{
	Normals = normals;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, Normals->ID);

	GLint Npoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexNormal");
	glEnableVertexAttribArray(Npoint);
	_GL(glVertexAttribPointer(Npoint, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL));
}
void VAOBuffer::Attach(UVBuffer *texture)
{
	Textures = texture;
	glActiveTexture(GL_TEXTURE0);
	_GL(glBindTexture(GL_TEXTURE_2D, Textures->ID));
}
void VAOBuffer::Attach(ColorBuffer   *color)
{
	Colors = color;
	_GL(glBindVertexArray(VAO));
	_GL(glBindBuffer(GL_ARRAY_BUFFER, Colors->ID));

	GLint Cpoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexColor");
	if (Cpoint != -1)
	{
		_GL(glEnableVertexAttribArray(Cpoint));
		_GL(glVertexAttribPointer(Cpoint, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL));
	}
	else
	{
		Print("!!! WARNING!!! Passing Attribute that the Shader does not contain!: VertexColor");
	}
}
void VAOBuffer::Bind()
{
	if (Woven == true)
	{
#ifdef  _OPENGL_FIXED_FUNCTION
		glBindBuffer(GL_ARRAY_BUFFER, BatchID);
		glVertexPointer(4, GL_FLOAT, sizeof(VertexType), (char *)NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//glBindBuffer(GL_ARRAY_BUFFER, BatchID);
		glColorPointer(4, GL_FLOAT, sizeof(VertexType), (char*)(sizeof(float) * 4));
		glEnableClientState(GL_COLOR_ARRAY);

		//	glBindBuffer(GL_ARRAY_BUFFER, BatchID);
		glNormalPointer(GL_FLOAT, sizeof(VertexType), (char*)(sizeof(float) * 8));
		glEnableClientState(GL_NORMAL_ARRAY);
		Indices->Bind();
#else
	 	glBindVertexArray(VAO);
 	//	Indices->Bind();
#endif
	}
	else
	{
		glBindVertexArray(VAO);
		if (Textures)  Textures->Bind();
//		Indices->Bind();
	}
}
void VAOBuffer::Interleave()
{
//   Kind of need to figure out a different way to do this. 
//   Interleaving does produce better frame rates but I lose a major amount of flexibility

	std::vector<VertexType> Buffer;
	for_loop(Index, Vertices->ElementCount)
	{
		VertexType temp;
		temp.Color = Colors->Data[Index];
		temp.Vertex = Vertices->Data[Index];
		temp.Normals = Normals->Data[Index];
		Buffer.push_back(temp);
	}
	Woven = true;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	 
	glUseProgram(Shader::GetActiveShader()->GetName());
	GLuint Vpoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexPosition"); glEnableVertexAttribArray(Vpoint);
	GLuint Cpoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexColor");	glEnableVertexAttribArray(Cpoint);
	GLuint Npoint = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexNormal"); glEnableVertexAttribArray(Npoint);
	 
	glGenBuffers(1, &BatchID);
	glBindBuffer(GL_ARRAY_BUFFER, BatchID);
	glBufferData(GL_ARRAY_BUFFER, (Vertices->ElementCount * 3) * sizeof(Vec4), &Buffer[0], GL_STATIC_DRAW);

	glVertexAttribPointer(Vpoint, 4, GL_FLOAT, GL_FALSE, sizeof(VertexType), (char *)NULL);
	glVertexAttribPointer(Cpoint, 4, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(Npoint, 4, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void*)(sizeof(float) * 8));
}
void VAOBuffer::Unbind()
{
#if _DEBUG
//	if (Vertices)  Vertices->Unbind();
//	if (Indices)    Indices->Unbind();
//	if (Textures)  Textures->Unbind();
//	if (Colors)      Colors->Unbind();
//	if (Normals)    Normals->Unbind();
#endif
}

//==================================================================================================================================================
//__________________________________ FRAME BUFFER CLASS ____________________________________________________________________________________________
// There are two types of framebuffer-attachable images; texture images and renderbuffer images. If an image of a texture 
//     object is attached to a framebuffer, OpenGL performs "render to texture". And if an image of a renderbuffer object is
//     attached to a framebuffer, then OpenGL performs "offscreen rendering".
// Texture = Read
// RenderBuffer = Offscreen Rendering
// Attach different Textures or Render buffer with Different Bitmask to get different colors
// Depth and Stencil buffer is also an Option.
// Use: Multiple ColorBuffers   [ GL_COLOR_ATTACHMENT0,n....., ] 
// One Depth attachment point   [ GL_DEPTH_ATTACHMENT   ]
// One Stencil attachment point [ GL_STENCIL_ATTACHMENT ]
// Notice that the framebuffer object itself does not have any image storage(array) in it, 
// but it has only multiple attachment points.
