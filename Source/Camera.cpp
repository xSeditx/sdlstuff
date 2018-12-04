#include"camera.h"

Viewport *Viewport::Camera;




#ifdef _OPENGL_FIXED_FUNCTION

Viewport::Viewport(Vec3 position, Vec3 rotation)
{
	FOV = 60.0;
	AspectRatio = 640.0f / 480.0f;
	Near = 1.0f;
	Far = 1024.0f;
	Speed = 1.0;

	Position = position;
	Rotation = rotation;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, AspectRatio, Near, Far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(Rotation.x, 1.0, 0, 0);
	glRotatef(Rotation.y, 0.0, 1.0, 0);
	glRotatef(Rotation.z, 0.0, 0, 1.0);
	glTranslatef(Position.x, Position.y, Position.z);
	Camera = this;

}
Matrix Viewport::GetModelViewMatrix()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, &ViewMatrix[0][0]);
	return ViewMatrix;
}
void Viewport::MoveForward(float speed)
{
	Speed = speed;
	float  SIN_X = sin(RADIANS(Rotation.x - 90));
	Position.x -= (cos(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
	Position.y -= cos(RADIANS(Rotation.x - 90)) * speed;
	Position.z -= (sin(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
}
void Viewport::MoveBack(float speed)
{
	Speed = speed;
	float  SIN_X = sin(RADIANS(Rotation.x - 90));
	Position.x += (cos(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
	Position.y += cos(RADIANS(Rotation.x - 90))* speed;
	Position.z += (sin(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
}
void Viewport::MoveLeft(float speed)
{
	Speed = speed;
	Position.x += cos(RADIANS(Rotation.y - 0)) * Speed;
	Position.z += sin(RADIANS(Rotation.y - 0)) * Speed;
}
void Viewport::MoveRight(float speed)
{
	Speed = speed;
	Position.x += cos(RADIANS(Rotation.y - 180)) * Speed;
	Position.z += sin(RADIANS(Rotation.y - 180)) * Speed;
}
void Viewport::Rotate(float x, float y)
{
	Rotation.y += (x * .8);
	Rotation.x += (y * .8);
}
void Viewport::Update()
{
	//_GL(glMatrixMode(GL_MODELVIEW));
	glLoadIdentity();
	//  ROTATE the Camera  
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
	//  Move Camera into Position       
	glTranslatef(Position.x, Position.y, Position.z);
}


#else  //  PROGRAMABLE PIPELINE

Viewport::Viewport(Vec3 position, Vec3 rotation)
{
	FOV = 60.0;
	AspectRatio = 640.0f / 480.0f;
	Near = .10f;
	Far = 1024.0f;

	Speed = 1.0;

	Position = position;
	Rotation = rotation;

	Forward = Vec3(0.0f, 0.0f, 1.0f);
	Right = Vec3(0.1f, 0.0f, 0.0f);
	Up = Vec3(0.0f, 1.0f, 0.0f);

	ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, Near, Far);
	ViewMatrix = Matrix(1.0f);
	Camera = this;
}
void Viewport::Update()
{
	glm::mat4 Pitch = glm::rotate(Identity, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Yaw   = glm::rotate(Identity, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Roll  = glm::rotate(Identity, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
//	ViewMatrix = (Roll * Pitch *  Yaw) * (glm::translate(glm::mat4(1.0f), -Position));

	ClampCamera();
	ViewMatrix = RotateX(Rotation.x) * RotateY(Rotation.y) * (glm::translate(glm::mat4(1.0f), -Position)); //  (Pitch *  Yaw) *

	Forward = glm::normalize(Vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]));
	Right   = glm::normalize(Vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]));

}
Matrix Viewport::GetViewMatrix()
{
	ViewMatrix = glm::lookAt(Position, Position + Forward, Up);
	return ViewMatrix; 
}

void Viewport::MoveForward(float speed)
{
	Position -= (speed * Forward);
}
void Viewport::MoveBack(float speed)
{
	Position += (speed * Forward);
}
void Viewport::MoveLeft(float speed)
{
	Position -= (speed)* Right;
}
void Viewport::MoveRight(float speed)
{
	Position += (speed)* Right;
}

Matrix Viewport::RotateX(GLfloat angle)
{
	Matrix ret = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(angle), -sin(angle), 0.0f,
		0.0f, sin(angle),  cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return ret;
}
Matrix Viewport::RotateY(GLfloat angle)
{
	Matrix ret = {
		cos(angle), 0.0f,-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin(angle), 0.0f, cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return ret;
}
Matrix Viewport::RotateZ(GLfloat Angle)
{
	Matrix ret = {
		0, 0.0f,0, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0, 0.0f,0, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return ret;
}
void Viewport::Rotate(float pitch, float yaw)
{
	Rotation.x -= yaw * RADIANS(.5);//.005;
	Rotation.y -= pitch * RADIANS(.5); //.008;
}
void Viewport::ClampCamera()
{
	if (Rotation.x > RADIANS(89))  Rotation.x = RADIANS(89);
	if (Rotation.x < -RADIANS(89)) Rotation.x = -RADIANS(89);
}


#endif








//Right = glm::normalize(glm::cross(cameraFront, cameraUp));
//if (Rotation.y < .0)    Rotation.y += 360.0f;
//if (Rotation.y> 360.0f)  Rotation.y -= 360.0f;