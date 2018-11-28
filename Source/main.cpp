 //#define _GLFWWINDOW
#define _SDLWINDOW
 
#include"Window.h"
 
#include"Renderer.h"
#include"Camera.h"
#include"core.h"
#include"Primative.h"
#include"Texture.h"


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
		Window::SCREEN->World->Camera.MoveRight(.251);
		break;
	case 80:
		Window::SCREEN->World->Camera.MoveLeft(.251);
		break;
	case 81:
		Window::SCREEN->World->Camera.MoveForward(.251);
		break;
	case 82:
		Window::SCREEN->World->Camera.MoveBack(.251);
		break;
	}
}

void  MouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
		Window::SCREEN->World->Camera.Rotate(-relX, relY);
}
 

void LoadStuff()
{
	Image::Manager.Add(new Image("Moon", "Resources//Moon.bmp"));
	Image::Manager.Add(new Image("BrickDiffuse", "Resources\\Brick\\Brick.bmp"));
    Image::Manager.Add(new Image("BrickNormals", "Resources\\Brick\\Brickn.bmp"));

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


 LoadStuff();
//	 void DebugMessageCallbackARB(DEBUGPROCARB callback,
//		 const void* userParam);
	  
#ifdef	_OPENGL_FIXED_FUNCTION
	Material *Surface = new Material();
	//Surface->SetRenderer(new Shader("Resources\\FF.vert", "Resources\\FF.frag")); // Shader("Resources\\Basic.vert", "Resources\\Basic.frag");
 #else
     GLuint vao;
     glGenVertexArrays(1, &vao);
     glBindVertexArray(vao);

     Material *Surface = new Material();
     Surface->SetRenderer(new Shader("Resources\\Basic.vert", "Resources\\Basic.frag"));  
	 //Surface->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("Moon"));
 #endif

	Block Cube(Vec3(0, 0, 10), 1);
	Block Cube1(Vec3(0, 0, -10), 1);
	Block Cube2(Vec3(0, 10, 0), 1);
	Block Cube3(Vec3(0, -10, 0), 1);
	Block Cube4(Vec3( 10, 0, 0), 1);
	Block Cube5(Vec3(-10, 0, 0), 1);
	Block center(Vec3(0, 0, 0), 2);

	 
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
		//Sphere Ball(Vec3(rand() % 300 - 150, rand() % 300 - 150, rand() % 300 - 150), 1, 20);
		Block Block (Vec3(rand() % 300 - 150, rand() % 300 - 150, rand() % 300 - 150), 2);
		Block.Surface = BrickMaterial();
		 
		MainWin.World->Groups[0].Add(Block);
	}
 	glEnableClientState(GL_INDEX_ARRAY);
//	MainWin.World->Surface = Surface;
   	glDisable(GL_LIGHTING);
   	glDisable(GL_TEXTURE_2D);
   	glDisable(GL_ALPHA_TEST);
   	glDisable(GL_AUTO_NORMAL);
   	glDisable(GL_BLEND);
   	glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_MINMAX);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_NORMALIZE);
    glDisable(GL_POLYGON_SMOOTH);
   	//glDisable();
   	//glDisable();
//	glDrawElementsInstanced(GL_TRIANGLES, 24, GL_FLOAT, MainWin.World->Groups[0].Objects[0].Polygons->Indices, 1);
	GetOpenGLState();
	while (MainWin.EventLoop())
	{
		{
			//Performance.Start();
			BenchMark Performance;
			//Performance.Start();
			MainWin.CLS();
		//	Surface->GetRenderer()->Enable();
			MainWin.World->Camera.Update();
			MainWin.World->Render();
		//	Surface->GetRenderer()->Disable();
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