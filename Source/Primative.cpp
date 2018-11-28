#include"primative.h"



//======================================================================================================================================================================================
//                                         PRIMATIVES TO TEST WITH                                                                                                                                                   
//======================================================================================================================================================================================

Block::Block(Vec3 pos, float size)
	:
	VertexCount(0)
{
	//f_TRACE(Print("Block Constructor"));
	Position = pos;

	Vec3 V[] =
	{
		Vec3(-size,-size, size), // FRONT    // 0                                             
		Vec3(size,-size, size),             // 1                                    
		Vec3(size, size, size),             // 2                                    
		Vec3(-size, size, size),             // 3                                    

		Vec3(size, size, size), // RIGHT    // 4    2                                        
		Vec3(size, size,-size),             // 5                                    
		Vec3(size,-size,-size),             // 6                                    
		Vec3(size,-size, size),             // 7    1                                

		Vec3(-size,-size,-size), // BACK     // 8                                            
		Vec3(size,-size,-size),             // 9    6                               
		Vec3(size, size,-size),             // 10   5                                
		Vec3(-size, size,-size),             // 11

		Vec3(-size,-size,-size), // LEFT     // 12   8                                        
		Vec3(-size,-size, size),             // 13   7                              
		Vec3(-size, size, size),             // 14   3                                
		Vec3(-size, size,-size),             // 15  11                                

		Vec3(size, size, size), // TOP      // 16   2                                      
		Vec3(-size, size, size),             // 17   3                                
		Vec3(-size, size,-size),             // 18   11                                
		Vec3(size, size,-size),             // 19   5                                

		Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
		Vec3(size,-size,-size),             // 21   9                          
		Vec3(size,-size, size),             // 22   1                          
		Vec3(-size,-size, size),             // 23   0                               
	};

	Vec2 UVs[] =
	{
		Vec2(0.00f, 0.66f),  // FRONT  // 0   
		Vec2(0.00f, 0.33f),            // 1   
		Vec2(0.25f, 0.33f),            // 2   
		Vec2(0.25f, 0.66f),            // 3   

		Vec2(0.25f, 0.33f),  // RIGHT  // 4   
		Vec2(0.50f, 0.33f),            // 5   
		Vec2(0.50f, 0.00f),            // 6   
		Vec2(0.25f, 0.00f),            // 7   

		Vec2(0.75f, 0.66f),  // BACK   // 8   
		Vec2(0.75f, 0.33f),            // 9   
		Vec2(0.50f, 0.33f),            // 10  
		Vec2(0.50f, 0.66f),            // 11  

		Vec2(0.50f, 1.00f),  // LEFT   // 12  
		Vec2(0.25f, 1.00f),            // 13  
		Vec2(0.25f, 0.66f),            // 14  
		Vec2(0.50f, 0.66f),            // 15  

		Vec2(0.25f, 0.33f),  // TOP    // 16  
		Vec2(0.25f, 0.66f),            // 17  
		Vec2(0.50f, 0.66f),            // 18  
		Vec2(0.50f, 0.33f),            // 19  

		Vec2(0.75f, 0.66f),  // BOTTOM // 20  
		Vec2(0.75f, 0.33f),            // 21  
		Vec2(1.00f, 0.33f),            // 22  
		Vec2(1.00f, 0.66f),            // 23  
	};
	Vec4 Cols[] =
	{
		Vec4(1.0, 1.0, 1.0, 1.0),  // FRONT  // 0         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 1         
		Vec4(0.0, 0.5, 1.0, 1.0),            // 2         
		Vec4(0.0, 0.0, 0.0, 1.0),            // 3         

		Vec4(0.0, 0.0, 0.0, 1.0),  // RIGHT  // 4         
		Vec4(0.0, 0.0, 1.0, 1.0),            // 5         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 6         
		Vec4(1.0, 1.0, 1.0, 1.0),            // 7         

		Vec4(1.0, 0.0, 1.0, 1.0),  // BACK   // 8         
		Vec4(0.0, 1.0, 0.0, 1.0),            // 9         
		Vec4(1.0, 1.0, 0.0, 1.0),            // 10        
		Vec4(1.0, 0.0, 0.0, 1.0),            // 11

		Vec4(0.50f, 1.00f, 1.00f, 1.0),  // LEFT   // 12        
		Vec4(0.25f, 1.00f, 1.00f, 1.0),            // 13        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 14        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 15        

		Vec4(0.25f, 0.33f, 0.33f, 1.0),  // TOP    // 16        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 17        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 18        
		Vec4(0.50f, 0.33f, 0.33f, 1.0),            // 19     

		Vec4(0.75f, 0.66f, 0.66f, 1.0),  // BOTTOM // 20        
		Vec4(0.75f, 0.33f, 0.33f, 1.0),            // 21        
		Vec4(1.00f, 0.33f, 0.33f, 1.0),            // 22        
		Vec4(1.00f, 0.66f, 0.66f, 1.0),            // 23        
	};
	GLuint Indexdata[] =
	{
		0,1,2,    0,2,3,     // FRONT
		6,5,4,    4,7,6,     // RIGHT 
		10,9,8,   8,11,10,   // BACK
		12,13,14, 12,14,15,  // LEFT
		18,17,16, 16,19,18,  // TOP
		20,21,22, 20,22,23   // BOTTOM
	};

	Vec3 NormalData[24];

	for_loop(Index, 24)
	{
		float x = V[Index].x;
		float y = V[Index].y;
		float z = V[Index].z;

		float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));

		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
		NormalData[Index] = Vec3(x, y, z); //  Vec3(RANDOM(2)-1,RANDOM(2)-1,RANDOM(2)-1);//
	}
	for_loop(Index, 24)
	{
		VertexList.push_back(V[Index]);
		TextureCoords.push_back(UVs[Index]);
		NormalList.push_back(NormalData[Index]);
	}
	for_loop(Index, 36)
	{
		IndexList.push_back(Indexdata[Index]);
	}

	// Averages all the normals so Each Faces Vertices have normals facing straight out to prevent interpolation of the light
	// Across the block
	// for(int Index = 0; Index < 24 ; Index += 4)
	// {
	//     Vec3 Norm =  NormalData[Index]   +
	//                  NormalData[Index+1] +
	//                  NormalData[Index+2] +
	//                  NormalData[Index+3];
	//
	//     Norm /= 4; 
	//
	//     NormalData[Index]   = Norm;
	//     NormalData[Index+1] = Norm;
	//     NormalData[Index+2] = Norm;
	//     NormalData[Index+3] = Norm;
	//
	// }
	//



	Polygons = new VAOBuffer();

	Polygons->Attach(new VertexBuffer(&VertexList[0], 24));
	Polygons->Attach(new UVBuffer(&TextureCoords[0], 24));
	Polygons->Attach(new NormalBuffer(&NormalList[0], 24));
	Polygons->Attach(new ColorBuffer(&Cols[0], 24));
	Polygons->Attach(new IndexBuffer(&IndexList[0], 36));

	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
	Transform = glm::translate(Transform, Position);
	Rotation = Vec3(rand() % 360, rand() % 360, rand() % 360);
 
	// model_matrix = glm::translate(glm::rotate(glm::scale( mat4(1.0f), scaling), rotation_angle, rotation_axis), translation);
	// glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	// glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;
}
Sphere::Sphere(Vec3 pos, float radius, int sectors)
	:
	VertexCount(0),
	ColorCount(0),
	Radius(radius)

{
	Position = pos;
	Rotation = Vec3(rand() % 360, rand() % 360, rand() % 360);
	float size = 20;
	int IndexCount = 0;
	float  x = 0, y = 0, z = 0;
	float x1 = 0, y1 = 0, z1 = 0;
	float x2 = 0, y2 = 0, z2 = 0;
	float x3 = 0, y3 = 0, z3 = 0;
	float Widthinc = (Image::Manager.GetAsset("Moon")->Width / 360);
	float Heightinc = (Image::Manager.GetAsset("Moon")->Height / 180);
	float Uinc = (1.0f / (Image::Manager.GetAsset("Moon")->Width)) * Widthinc; //* size;
	float Vinc = (1.0f / (Image::Manager.GetAsset("Moon")->Height))* Heightinc; // * size;

	float Ucoord = 0, Vcoord = 0;

	std::vector<GLuint> Ind;
	for (float Lat = 0;Lat < 360;Lat += size) {
		for (float Long = 0;Long < 180;Long += size) { // 90 draws top half of a sphere
			x = radius * (sin(RADIANS(Long)) * cos(RADIANS(Lat)));
			y = radius * (sin(RADIANS(Long)) * sin(RADIANS(Lat)));
			z = radius *  cos(RADIANS(Long));

			x1 = radius * (sin(RADIANS(Long + size)) * cos(RADIANS(Lat)));
			y1 = radius * (sin(RADIANS(Long + size)) * sin(RADIANS(Lat)));
			z1 = radius *  cos(RADIANS(Long + size));

			x2 = radius * (sin(RADIANS(Long)) * cos(RADIANS(Lat + size)));
			y2 = radius * (sin(RADIANS(Long)) * sin(RADIANS(Lat + size)));
			z2 = radius *  cos(RADIANS(Long));

			x3 = radius * (sin(RADIANS(Long + size)) * cos(RADIANS(Lat + size)));
			y3 = radius * (sin(RADIANS(Long + size)) * sin(RADIANS(Lat + size)));
			z3 = radius *  cos(RADIANS(Long + size));

			Colors[ColorCount].r = GL_Color(x * 255);
			Colors[ColorCount].g = GL_Color(y * 255);
			Colors[ColorCount].b = GL_Color(z * 255);
			Vertices[VertexCount].x = x;
			Vertices[VertexCount].y = y;
			Vertices[VertexCount].z = z;


			Colors[ColorCount + 1].r = GL_Color(x * 255);
			Colors[ColorCount + 1].g = GL_Color(y * 255);
			Colors[ColorCount + 1].b = GL_Color(z * 255);
			Vertices[VertexCount + 1].x = x1;
			Vertices[VertexCount + 1].y = y1;
			Vertices[VertexCount + 1].z = z1;

			Colors[ColorCount + 2].r = GL_Color(x * 255);
			Colors[ColorCount + 2].g = GL_Color(y * 255);
			Colors[ColorCount + 2].b = GL_Color(z * 255);
			Vertices[VertexCount + 2].x = x2;
			Vertices[VertexCount + 2].y = y2;
			Vertices[VertexCount + 2].z = z2;

			Colors[ColorCount + 3].r = GL_Color(x * 255);
			Colors[ColorCount + 3].g = GL_Color(y * 255);
			Colors[ColorCount + 3].b = GL_Color(z * 255);
			Vertices[VertexCount + 3].x = x3;
			Vertices[VertexCount + 3].y = y3;
			Vertices[VertexCount + 3].z = z3;



//
//		UVcoord[VertexCount + 0].x = Uinc * (Lat + size);
//		UVcoord[VertexCount + 0].y = Vinc * (Long  );
//
//		UVcoord[VertexCount + 1].x = Uinc *(Lat );
//		UVcoord[VertexCount + 1].y = Vinc *(Long + size);
//
//		UVcoord[VertexCount + 2].x = Uinc * (Lat + size);
//		UVcoord[VertexCount + 2].y = Vinc * (Long + size);
//
//
//		UVcoord[VertexCount + 3].x = Uinc * (Lat );
//		UVcoord[VertexCount + 3].y = Vinc * (Long );
 
 

			// 01
			// 11
			// 00 
			// 10


			Ind.push_back(VertexCount + 1);
			Ind.push_back(VertexCount + 3);
			Ind.push_back(VertexCount + 2);
			Ind.push_back(VertexCount);
			Ind.push_back(VertexCount + 1);
			Ind.push_back(VertexCount + 2);



			Indices[IndexCount] = VertexCount;
			Indices[IndexCount + 1] = VertexCount + 1;
			Indices[IndexCount + 2] = VertexCount + 2;

			Indices[IndexCount + 3] = VertexCount + 1;
			Indices[IndexCount + 4] = VertexCount + 3;
			Indices[IndexCount + 5] = VertexCount + 2;



			float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));
			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}
			Normals[VertexCount].x = x;
			Normals[VertexCount].y = y;
			Normals[VertexCount].z = z;

			magnitude = sqrt(Squared(x1) + Squared(y1) + Squared(z1));
			if (magnitude != 0)
			{
				x1 /= magnitude;
				y1 /= magnitude;
				z1 /= magnitude;
			}
			Normals[VertexCount + 1].x = x1;
			Normals[VertexCount + 1].y = y1;
			Normals[VertexCount + 1].z = z1;

			magnitude = sqrt(Squared(x2) + Squared(y2) + Squared(z2));
			if (magnitude != 0)
			{
				x2 /= magnitude;
				y2 /= magnitude;
				z2 /= magnitude;
			}
			Normals[VertexCount + 2].x = x2;
			Normals[VertexCount + 2].y = y2;
			Normals[VertexCount + 2].z = z2;

			magnitude = sqrt(Squared(x3) + Squared(y3) + Squared(z3));
			if (magnitude != 0)
			{
				x3 /= magnitude;
				y3 /= magnitude;
				z3 /= magnitude;
			}
			Normals[VertexCount + 3].x = x3;
			Normals[VertexCount + 3].y = y3;
			Normals[VertexCount + 3].z = z3;

			VertexCount += 4;
			ColorCount += 4;
			IndexCount += 6;

		}
	}
   int c = 0;
   for (float Long = 0; Long < 360;Long += size)
   {
	   for (float Lat = 0; Lat < 180;Lat += size)
	   {
		   UVcoord[c + 0].x = Uinc * (Lat);
		   UVcoord[c + 0].y = Vinc * (Long);

		   UVcoord[c + 1].x = Uinc * (Lat + size);
		   UVcoord[c + 1].y = Vinc * (Long + size);

		   UVcoord[c + 2].x = Uinc * (Lat + size);
		   UVcoord[c + 2].y = Vinc * (Long + size);

		   UVcoord[c + 3].x = Uinc * (Lat + size);
		   UVcoord[c + 3].y = Vinc * (Long);
		   c += 4;
	   }
   }
 
	Polygons = new VAOBuffer();
	Polygons->Vertices = new VertexBuffer(Vertices, VertexCount);
	Polygons->Indices = new IndexBuffer(Indices, IndexCount);
	Polygons->Colors = new ColorBuffer(Colors, ColorCount);
 	Polygons->Normals = new NormalBuffer(Normals, VertexCount);
	Polygons->Textures = new UVBuffer(UVcoord, VertexCount);
}



//(1.0 + x / radius) * .5;
//(1.0 + y / radius) * .5;