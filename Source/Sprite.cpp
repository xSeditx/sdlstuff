#include"Sprite.h"

#include<memory>


//std::vector<Sprite *> Sprite::List;
//int Sprite::Count = 0;

AssetManager<Sprite> Sprite::Manager;

//=========================================================================================================================================
//_______________________________________  Frame Class ____________________________________________________________________________________
//                                                                                                                                  
//Each Frame is a UV buffer whos Index is Bound prior to rendering in accordance with the current timestep for the Animated Sprite
//=========================================================================================================================================
// I suppose I could also store the Frame Data linearly here and
// Offset to the frame that I wish to render from
// That might be the best method honestly.

Frame::Frame(Image *img, Quad f) // IDK, possibly pass the UnitX/Y instead of Image. Like to just pass Quad but how... Normalize in Shader? Use Values for finding proper index? Suck it up and just leave it the fuck alone....
{
	float UnitX = (1.0f / img->Width);
	float UnitY = (1.0f / img->Height);
	float UnitXH = UnitX * .5f;
	float UnitYH = UnitY * .5f;

	Coords[0] = Vec2((float)f.x * UnitX + (float)f.Width  * UnitX - UnitXH, 
		             (float)f.y * UnitY + (float)f.Height * UnitY - UnitYH);

	Coords[1] = Vec2((float)f.x * UnitX + UnitXH,
		             (float)f.y * UnitY + (float)f.Height * UnitY - UnitYH);

	Coords[2] = Vec2((float)f.x * UnitX + UnitXH, 
		             (float)f.y * UnitY + UnitYH);

	Coords[3] = Vec2((float)f.x * UnitX + (float)f.Width * UnitX - UnitXH, 
		             (float)f.y * UnitY + UnitYH);

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4, Coords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Frame::Bind()
{
	glActiveTexture(GL_TEXTURE0);  // <- This should currently work but perhaps a better way would be to send the UV information to the shader, 
	glBindBuffer(GL_ARRAY_BUFFER, ID); 	// or even better an index that resprents how much to multiply U and V by to get the correct coords since that could greatly increase performance....
	glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glVertexAttribPointer(TEXTURE_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,  (char *) NULL); // THIS IS HOW I SHOULD BE DOING IT INSTEAD OF THIS CLIENT STATE SHIT	
}
void Frame::Unbind()
{
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//=========================================================================================================================================
//_______________________________________  Animation Class ____________________________________________________________________________________
//                                                                                                                                  
//   Each Animation is a state that an Entity can be in, Dead alive etc and is a group of frames that represents a state of the StaticSprite
//=========================================================================================================================================


// Animation::Animation(Sprite *spr, Quad srcrect, GLuint numframes) OLD ONE. MIGHT NEED TO DO IT THIS WAY>>>> MIGHT NOT....
Animation::Animation(Image *spr, Quad srcrect, GLuint numframes)
	:TotalFrames(numframes)
{
	CurrentFrame = 0;
	Frames.reserve(numframes);
	GLuint x = srcrect.x;
	for_loop(Count, numframes)
	{
		Quad  Source(x, srcrect.y, srcrect.Width, srcrect.Height);
		Frame frame(spr, Source);
		x += srcrect.Width;
		*this += frame;
	}
}
Animation::Animation(Image *spr, Quad srcrect, int border, GLuint numframes) // SAME HERE
	:TotalFrames(numframes)
{
	CurrentFrame = 0;
	Frames.reserve(numframes);
	GLuint x = srcrect.x;
	for_loop(Count, numframes)
	{
		Quad  Source(x, srcrect.y, srcrect.Width, srcrect.Height);
		Frame frame(spr, Source);
		x += srcrect.Width + border;
		*this += frame;
	}
}

std::vector<Frame> &Animation::AddFrame(Frame frame)
{
	Frames.emplace_back(frame);
	return Frames;
} // Adds a frame to the Animation

  //=========================================================================================================================================
  //_______________________________________  Sprite Class ___________________________________________________________________________________
  //                                                                                                                                  
  // Sprite is a Collection of States which can be Enumerated or Defined so Various Animations can play our in accordance with Gameplay
  //=========================================================================================================================================

Sprite::Sprite(char *name, Image *source, Vec2 dimensions, int numstates)
	:
	NumberofStates(numstates),
	CurrentState(0)
{
	Name = name;
	Scale = Vec3(1.0f);
	Position = Vec3(0);

	Timer = SDL_GetTicks();
	Animations.reserve(numstates);

	for_loop(count, NumberofStates)
	{
		Animation temp;
		Animations.emplace_back(temp);
	}

	Vec3 VertexData[] =  // DO I SERIOUSLY NOT HAVE A SIMPLE QUAD ABSTRACTED OUT YET? WHAT IS WRONG WITH ME!
	{
		Vec3(0,0,0),
		Vec3(dimensions.x, 0, 0),
		Vec3(dimensions.x, dimensions.y,0),
		Vec3(0, dimensions.y, 0),
	};

	GLuint IndexData[] =
	{
		2,3,1,  0,1,3,
	};

	Vec2 Coord[] = 
	{
		Vec2(0.0f,0.0f),
		Vec2(1.0f,0.0f),
		Vec2(1.0f,1.0f),
		Vec2(0.0f,1.0f)
	};

	Polygons = new VAOBuffer();
	Polygons->Attach(new VertexBuffer(&VertexData[0], 4));
	Polygons->Attach(new IndexBuffer(&IndexData[0], 6));

	Surface = new Material();
	Surface->Attach(SKIN_DIFFUSE, source);


	SetAnimationSpeed(150);
	ResetFrames();

	Moving = true;
	ID = Manager.Add(this);
}
void Sprite::ResetFrames()
{
	for (auto &A : Animations)//Animations is Equal to STATES[] in my past implementation. 
	{
		A.CurrentFrame = 0;
	}
}
void Sprite::Update()
{
	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::translate(Transform, Position);
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f)); // WAIT... ONE OF THESE IS USELESS IN ORTHOGRAPHIC IS IT NOT? UNLESS ITS WILL ROTATE MY SPRITE ..  MATTER FACT... ITS ALL USELESS....
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));

	AnimationTimer = SDL_GetTicks() - Timer;

	if (Moving == true)
	{ // Checks to see if Animation should even be currently playing.
		if (AnimationTimer > Animations[CurrentState].AnimationSpeed)
		{
			Timer = SDL_GetTicks();
			GLuint ticks = (AnimationTimer * 1000);
			Animations[CurrentState].CurrentFrame = (ticks / Animations[CurrentState].AnimationSpeed) % Animations[CurrentState].TotalFrames; // Fix this so that each sprite has its own Timer

			if (Animations[CurrentState].PlayOnce == true && Animations[CurrentState].CurrentFrame == Animations[CurrentState].TotalFrames)
			{ // Checks to see if the Animation is only supposed to play a single time then stop.
				Animations[CurrentState].CurrentFrame = 0; // Maybe remove this. Perhaps a Default frame would be an OK idea.
				Moving = false;
			}
		}
	}
}
void Sprite::SetAnimationSpeed(float speed)
{
	for (auto &A : Animations)
	{
		A.AnimationSpeed = speed;
	}
}
void Sprite::Render()
{
	Bind();
	_GL(glDrawElements(GL_TRIANGLES, Polygons->ElementCount(), GL_UNSIGNED_INT, nullptr));

}
void Sprite::Render(Vec2 position)
{

	Update();
	Bind();

	glDrawElements(GL_TRIANGLES, Polygons->ElementCount(), GL_UNSIGNED_INT, nullptr);

}
// I could also probably change the Data in the UV buffer every frame update to reflect the correct position in the
// Image used to render from by providing a new Source rect everytime.
//	Animations[CurrentState].Frames[Animations[CurrentState].CurrentFrame].Unbind();
//	Unbind();
//	glPopMatrix();
//Vertices->Bind();
//Indices->Bind();
//	Animations[CurrentState].Frames[Animations[CurrentState].CurrentFrame].Bind();
//	glPushMatrix();
//Picture->Bind();
//	glTranslatef(position.x, position.y, 0.0f);
//	glScalef(Scale.x, Scale.y, 0.0f);

//	glTranslatef(Position.x, Position.y, 0.0f);
//	_GL(glScalef(Scale.x, Scale.y, 0.0f));

void Sprite::Bind()
{
	Polygons->Bind();
	Matrix MVP = Viewport::Camera->GetViewMatrix();
	Shader::GetActiveShader()->SetCacheUniforms(Transform, Viewport::Camera->ViewMatrix, Viewport::Camera->ProjectionMatrix);
	Shader::GetActiveShader()->SetUniformMat4("CameraPos", Viewport::Camera->ViewMatrix * Transform);

	Surface->Bind();
	Polygons->Bind();//<- Now... This Binds Texture Coords... However we do not want those coords I dont think... Or should I change them constantly.. maybe my frame updater changes the coords in here??? 
	Animations[CurrentState].Frames[Animations[CurrentState].CurrentFrame].Bind();//<- So we fix that mistake with this... Hmmmm.....
	
	
	//	glActiveTexture(GL_TEXTURE0);  // <--- THIS SHOULD BE HANDLED IN SURFACE BIND IF I AM CORRECT
//	Shader::GetActiveShader()->SetTexture("DiffuseTexture", 0);

}
void Sprite::Unbind()
{
	Polygons->Unbind();
	Surface->Unbind();
	Animations[CurrentState].Frames[Animations[CurrentState].CurrentFrame].Unbind();
	glPopMatrix();
}

