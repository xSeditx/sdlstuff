 //#define _GLFWWINDOW
//#define _SDLWINDOW
 
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
 
 // https://stackoverflow.com/questions/28287162/why-is-a-simple-shader-slower-than-the-standard-pipeline

void Update()
{
}
void Render()
{
}
class MyApp : public Application
{
	void Update()
	{

	}
	void Render()
	{

	}
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
void LoadStuff()
{
	Image::Manager.Add(new Image("Moon", "Resources//Moon.bmp"));
	Image::Manager.Add(new Image("BrickDiffuse", "Resources\\Brick\\Brick.bmp"));
	Image::Manager.Add(new Image("BrickNormals", "Resources\\Brick\\Brickn.bmp"));
	Image::Manager.Add(new Image("StoneDiffuse", "Resources\\Stone\\Stone.bmp"));
	Image::Manager.Add(new Image("StoneNormals", "Resources\\Stone\\Stonen.bmp"));
}




void main()
{

	Window MainWin(100, 50, 640, 480, "SDL OpenGL TestWindow");
	MainWin.Callbacks.SetOnKeyDown(Keydown);
	MainWin.Callbacks.SetOnMouseMove(MouseMove);
	MainWin.SetUpdate(Update);
	MainWin.SetRender(Render);
	MainWin.Framerate.Set(2500);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    LoadStuff();
	  
#ifdef	_OPENGL_FIXED_FUNCTION
	Material *Surface = new Material();
	//Surface->SetRenderer(new Shader("Resources\\FF.vert", "Resources\\FF.frag")); // Shader("Resources\\Basic.vert", "Resources\\Basic.frag");
 #else


     Material *Surface = new Material();
     Surface->SetRenderer(new Shader("Resources\\Basic.vert", "Resources\\Basic.frag"));  
	 //Surface->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("Moon"));
 #endif

///  Mesh bot = Mesh();
///  bot.LoadOBJ("Resources\\Robot.obj");
///  bot.Surface = new Material(*MoonMaterial());
///  MainWin.World->Groups[0].Add(bot);

	MainWin.World = new Scene();
	MainWin.World->Attach( Viewport( Vec3( 0, 0, 0 ), Vec3( 0, 0, 0 ) ) );
	MainWin.World->AddLight( Light( Vec3( 100,10,100 ) ) );

	Viewport::Camera = &MainWin.World->Camera;

//   MainWin.World->Groups[0].Add( Block( Vec3(   0,   0,  10),  1  ) );
//   MainWin.World->Groups[0].Add( Block( Vec3(   0,   0, -10),  1  ) );
//   MainWin.World->Groups[0].Add( Block( Vec3(   0,  10,   0),  1  ) );
//   MainWin.World->Groups[0].Add( Block( Vec3(   0, -10,   0),  1  ) );
//   MainWin.World->Groups[0].Add( Block( Vec3(  10,   0,   0),  1  ) );
//   MainWin.World->Groups[0].Add( Block( Vec3( -10,   0,   0),  1  ) );
//
	Sphere center(Vec3(0, 0, 0), 1, 25);

	center.Add(new Material(*MoonMaterial()));
    MainWin.World->Groups[0].Add(center);

   int dist = 150;
   for_loop(Index, 200)
   {
	   Vec3 pos = Vec3(rand() % dist - (dist*.5), rand() % dist - (dist*.5), rand() % dist - (dist*.5));
	   MainWin.World->Groups[0].Add(Block(pos, 2), BrickMaterial()); //; Sphere(pos, 1, 30)
   }
   for_loop(Index, 200)
   {
	   Vec3 pos = Vec3(rand() % dist - (dist*.5), rand() % dist - (dist*.5), rand() % dist - (dist*.5));
	   MainWin.World->Groups[0].Add(Block(pos, 2), StoneMaterial()); // Torus(pos, 10, 10, 3)
   }
   for_loop(Index, 20)
   {
	   Vec3 pos = Vec3(rand() % dist - (dist*.5), rand() % dist - (dist*.5), rand() % dist - (dist*.5));
	//   MainWin.World->Groups[0].Add(Sphere(pos, 10, 4), MoonMaterial()); // Torus(pos, 10, 10, 3)
   }
  
	float
		Xangle = 0,
		Yangle = 0;
	int Var = 10;
	int *pointer = &Var;
	while (MainWin.EventLoop())
	{
		{
		//	BenchMark Performance;
			MainWin.CLS(0,0,0);
			MainWin.World->Render();
		 MainWin.World->Lights[0].SetPosition
		 (
		 	Vec3
		 	(
		 		cos(RADIANS(Xangle)) * 10,
		 		sin(RADIANS(Xangle)) * 10,
		 		sin(RADIANS(Yangle)) * 10
		 	)
		 );
	     MainWin.World->Groups[0].Objects[0].Set_Position(MainWin.World->Lights[0].Position);
			MainWin.Sync();
			Xangle+= .5;
			Yangle+= .5;
		}
	 //	Print(MainWin.Framerate.Get());

	//	Print(DEGREES(MainWin.World->Camera.Rotation.x));
	//	Print(DEGREES(MainWin.World->Camera.Rotation.y));
	}
	glBindVertexArray(0);
}















//	 void DebugMessageCallbackARB(DEBUGPROCARB callback,
//		 const void* userParam);
//	glDrawElementsInstanced(GL_TRIANGLES, 24, GL_FLOAT, MainWin.World->Groups[0].Objects[0].Polygons->Indices, 1);
//MainWin.Framerate.Set(60);
//Performance.Start();
//	glCheckError();
//	Performance.End();
//		Print(MainWin.Mouse.Position.x << " : " << MainWin.Mouse.Position.y);
//		Print(MainWin.Mouse.Velocity.x << " : " << MainWin.Mouse.Velocity.y);
// 		
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