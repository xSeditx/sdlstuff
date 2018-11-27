 //#define _GLFWWINDOW
#define _SDLWINDOW
 
#include"Window.h"
  
#include"Renderer.h"
#include"Camera.h"
#include"core.h"
#include"Primative.h"





//
//typedef void (APIENTRY *DEBUGPROCARB)(enum source,
//	enum type,
//	uint id,
//	enum severity,
//	int length,
//	const char* message,
//	const void* userParam);
//
 
 

void Update()
{
}
void Render()
{
}
class MyApp : public Application
{

};

void Keydown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep)
{
	switch (Keycode)
	{
	case 79:
		Window::SCREEN->World->Camera.MoveRight(.51);
		break;
	case 80:
		Window::SCREEN->World->Camera.MoveLeft(.51);
		break;
	case 81:
		Window::SCREEN->World->Camera.MoveForward(.51);
		break;
	case 82:
		Window::SCREEN->World->Camera.MoveBack(.51);
		break;
	}
}

void  MouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
		Window::SCREEN->World->Camera.Rotate(-relX, relY);
}
 
void main()
{

	Window MainWin(10, 30, 640, 480, "SDL OpenGL TestWindow");
	MainWin.Callbacks.SetOnKeyDown(Keydown);
	MainWin.Callbacks.SetOnMouseMove(MouseMove);
	MainWin.SetUpdate(Update);
	MainWin.SetRender(Render);
	MainWin.Framerate.Set(2500);

	//--------Gathering information about OpenGL state and Display it -----------------------------------------------
	int NumberOfExtensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
	for_loop(Count, NumberOfExtensions)
	{
		Print(glGetStringi(GL_EXTENSIONS, Count));
	}
//const GLubyte *extensions = glGetString(GL_EXTENSIONS);
//Print(extensions);
Print("OpenGL Version: "; Print(glGetString(GL_VERSION)));
Print("Renderer: "; Print(glGetString(GL_RENDERER)));
Print("Vendor: "; Print(glGetString(GL_VENDOR)));
Print("Current Context: "; Print(wglGetCurrentContext()));

	//-------------------------------------------------------------------------------------------------------------


//	 void DebugMessageCallbackARB(DEBUGPROCARB callback,
//		 const void* userParam);
	  
#ifdef	_OPENGL_FIXED_FUNCTION
	//Material *Surface = new Material();
	//Surface->Renderer = new Shader("Resources\\FF.vert", "Resources\\FF.frag"); // Shader("Resources\\Basic.vert", "Resources\\Basic.frag");
 #else
     GLuint vao;
     glGenVertexArrays(1, &vao);
     glBindVertexArray(vao);
//
//     glVertexAttribPointer(Shader::VertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
//     glVertexAttribPointer(Shader::NormalsLocation, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
//     glVertexAttribPointer(Shader::ColorsLocation, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
//
     Material *Surface = new Material();
     Surface->SetRenderer(new Shader("Resources\\Basic.vert", "Resources\\Basic.frag"));  
 #endif

//	MainWin.World->Surface->Renderer->Disable();
	  
	Block Cube(Vec3(0, 0, 10), 1);
	Block Cube1(Vec3(0, 0, -10), 1);
	Block Cube2(Vec3(0, 10, 0), 1);
	Block Cube3(Vec3(0, -10, 0), 1);
	Block Cube4(Vec3( 10, 0, 0), 1);
	Block Cube5(Vec3(-10, 0, 0), 1);	Block center(Vec3(0, 0, 0), 2);

	 
	Sphere Ball(Vec3(-5, -5, 0), 1, 15);

	MainWin.World = new Scene();
	MainWin.World->Camera = Viewport(Vec3(0, 0, 0), Vec3(0, 0, 0));
	Viewport::Camera = &MainWin.World->Camera;
   MainWin.World->Groups[0].Add(Cube);
   MainWin.World->Groups[0].Add(Cube1);
   MainWin.World->Groups[0].Add(Cube2);
   MainWin.World->Groups[0].Add(Cube3);
   MainWin.World->Groups[0].Add(Cube4);
   MainWin.World->Groups[0].Add(Cube5);
   MainWin.World->Groups[0].Add(center);
	 
	for_loop(Index, 400)
	{
		Sphere Ball(Vec3(rand() % 300 - 150, rand() % 300 - 150, rand() % 300 - 150), 1, 20);
		MainWin.World->Groups[0].Add(Ball);
	}
 	glEnableClientState(GL_INDEX_ARRAY);

	 
 
//	glDrawElementsInstanced(GL_TRIANGLES, 24, GL_FLOAT, MainWin.World->Groups[0].Objects[0].Polygons->Indices, 1);
	while (MainWin.EventLoop())
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		{
			//Performance.Start();
			BenchMark Performance;
			//Performance.Start();
			MainWin.CLS();

			MainWin.World->Camera.Update();
			MainWin.World->Render();
			MainWin.Sync();
		//	glCheckError();
		//	Performance.End();
		}

		
//		Print(MainWin.Mouse.Position.x << " : " << MainWin.Mouse.Position.y);
//		Print(MainWin.Mouse.Velocity.x << " : " << MainWin.Mouse.Velocity.y);
// 		Print(MainWin.Framerate.Get());
	}
	glBindVertexArray(0);
}






 
//  HWND ConsoleHandle = GetConsoleWindow();
//  LPMSG Msg = 0;
//  if (GetMessage(Msg, ConsoleHandle, 0, 0) != 0)
//  {
//  	if (Msg->message == WM_QUIT)
//  	{
//  
//  		Print("WindowExit");
//  	}
//  }