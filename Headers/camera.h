#pragma once
#include"WindowGLSDL.h"
#include<stack>
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == 


///        CAMERA 
/*===============================================================================================================================================================
//
//
//      CAMERA MODULE
//
//
=================================================================================================================================================================
*/


#if _OPENGL_FIXED_FUNCTION
class Viewport
{
public:
	Viewport() :
		Position(0, 0, 0),
		Rotation(0, 0, 0),
		Speed(1.0f)
	{}

	Viewport(Vec3 position, Vec3 Rotation);

	float
		FOV,
		AspectRatio,
		Near,
		Far;

	Vec3
		Position,
		Rotation,
		Forward,
		Right,
		Up;

	Matrix   ProjectionMatrix;
	Matrix   ViewMatrix;

	float Speed;
	static Viewport *Camera;

	std::vector<Matrix> MatrixStack;
	//=======================================================================================================================================================
	// FUNCTIONS FOR THE CAMERA CLASS
	//=======================================================================================================================================================

	void Update();
	void Render();

	Matrix GetModelViewMatrix();

	void Rotate(float pitch, float yaw);
	void MoveForward(float speed);
	void MoveBack(float speed);
	void MoveLeft(float speed);
	void MoveRight(float speed);
	//=======================================================================================================================================================

	void ClampCamera();

	std::vector<Matrix> View;
	std::vector<Matrix> Projection;

	Matrix GetViewMatrix() { return View.back(); }
	Matrix GetProjectionMatrix() { return Projection.back(); }

};
#else
class Viewport
{
public:
	Viewport() :
		Position(0, 0, 0),
		Rotation(0, 0, 0),
		Speed(1.0f)
	{}

	Viewport(Vec3 position, Vec3 Rotation);

	float
		FOV,
		AspectRatio,
		Near,
		Far;


	Matrix   ProjectionMatrix;
	Matrix   ViewMatrix;
 
	float Speed;

	//=======================================================================================================================================================
	// FUNCTIONS FOR THE CAMERA CLASS
	//=======================================================================================================================================================

	Matrix GetViewMatrix();

	void Update();
	void Rotate(float pitch, float yaw);
	void MoveBack(float speed);
	void MoveLeft(float speed);
	void MoveRight(float speed);
	void MoveForward(float speed);
	//=======================================================================================================================================================
 
	Matrix RotateX(GLfloat Angle);
	Matrix RotateY(GLfloat Angle);
	Matrix RotateZ(GLfloat Angle);

	static Viewport *Camera;

	std::stack<Matrix> ViewMatrixStack;
	std::stack<Matrix> ProjectionMatrixStack;

	void PushProjectionMatrix(Matrix projmat);
	void PushViewMatrix(Matrix viewmat);

	void PopProjectionMatrix();
	void PopViewMatrix();
	Vec3
		Position,
		Rotation,
		Forward,
		Right,
		Up;
private:
	Matrix Identity = Matrix(1.0f);
};
#endif

