#pragma once




class Sprite;
#include"core.h"
#include"texture.h"

struct Quad
{
	Quad() {};
	Quad(int X, int Y, int W, int H)
		: x(X), y(Y), Width(W), Height(H) {}
	int x, y;
	int Height, Width;
};
struct Frame
{
public:
	Frame() {}
	Frame(Image*img, Quad f);

	Vec2 Coords[4];
	GLuint ID;

	void Bind();
	void Unbind();
};
class Animation
{
public:
	Animation() {}
	~Animation() {}

	Animation(Image *img, Quad sourcerect, uint numframes);
	Animation(Image *img, Quad srcrect, int border, GLuint numframes);

	std::vector<Frame> Frames;

	uint TotalFrames;
	uint CurrentFrame;

	GLint  AnimationSpeed;

	Animation operator +=(Frame newframe)
	{
		this->AddFrame(newframe);
		return *this;
	}
	Animation operator +=(Animation newstate)
	{
		for_loop(count, newstate.TotalFrames)
		{
			this->AddFrame(newstate.Frames[count]);
			this->TotalFrames++;
		}
		return *this;
	}

	bool PlayOnce;
	bool Stopped;
private:
	std::vector<Frame>& AddFrame(Frame frame);
};
class Sprite : public Object
{

	Sprite(char *name, Image *source, Vec2 dimensions, int numstates)
	{

	}

	int ID;

	GLuint CurrentState;

	std::vector<Animation> Animations;
	GLuint NumberofStates;

	float Timer;
	float AnimationTimer;
	float AnimationLength;


	bool Moving;     // Is it currently Animating
	bool Composite;  // Is it made up of multiple sprites
					 // _______________________________________________________________________________________________________________________
	void SetAnimationSpeed(float speed) { Speed = speed; }
	void ResetFrames() {}
public:
	void  Bind() override {}
	void  Unbind() override {}
	void  Update() override {}
	void  Render() override {}


	void  Render(Vec2 pos);

	char *Name;
	static AssetManager<Sprite> Manager;


private:
	float Speed;
};