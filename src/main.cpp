/*******************************************************************************************
*
*   raylib-extras [ImGui] example - Simple Integration
*
*	This is a simple ImGui Integration
*	It is done using C++ but with C style code
*	It can be done in C as well if you use the C ImGui wrapper
*	https://github.com/cimgui/cimgui
*
*   Copyright (c) 2021 Jeffery Myers
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <ryml.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"




int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 800;

	char yml_buf[] = "{foo: 1, bar: [2, 3], john: doe}";
	ryml::Tree tree = ryml::parse_in_place(yml_buf);
	ryml::ConstNodeRef root = tree.rootref();  // a const node reference
	int foo=0;
	tree["foo"] >> foo;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, "Boxey");
	SetTargetFPS(30);

	Image left = LoadImage(ASSETS_PATH"x.jpg");
	Image right = LoadImage(ASSETS_PATH"x.jpg");
	Image top = LoadImage(ASSETS_PATH"x.jpg");
	Image bottom = LoadImage(ASSETS_PATH"x.jpg");
	Image up = LoadImage(ASSETS_PATH"x.jpg");
	Image down = LoadImage(ASSETS_PATH"x.jpg");

	Texture2D right_texture = LoadTextureFromImage(left);
	Texture2D front_texture = LoadTextureFromImage(left);
	Texture2D back_texture = LoadTextureFromImage(left);
	Texture2D up_texture = LoadTextureFromImage(left);
	Texture2D down_texture = LoadTextureFromImage(left);

	ImageRotate(&left, 90);
	Texture2D left_texture = LoadTextureFromImage(left);


    
	RenderTexture2D output = LoadRenderTexture(left.width*4, left.height*3);
    BeginDrawing();
		BeginTextureMode(output);
			// Line 1
			DrawTexture(front_texture, left.width, 0, RAYWHITE);
			//Line 2
			DrawTexture(left_texture, 0* left.width, left.height, RAYWHITE);
			DrawTexture(up_texture, 1*left.width, left.height, RAYWHITE);
			DrawTexture(right_texture, 2*left.width, left.height, RAYWHITE);
			DrawTexture(down_texture, 3*left.width, left.height, RAYWHITE);
			// Line 3
			DrawTexture(back_texture, left.width, left.height*2, RAYWHITE);
		EndTextureMode();
	EndDrawing();


	Image offscreen = LoadImageFromTexture(output.texture);
	ImageFlipVertical(&offscreen);
	Texture2D onscreen = LoadTextureFromImage(offscreen);
	ExportImage(offscreen, "cube.png");
    //let mut offscreen = output.texture().load_image().unwrap();
    //offscreen.flip_vertical();
    //offscreen.export_image("cube2.png");
    //let onscreen = rl.load_texture_from_image(&thread, &offscreen).unwrap();

	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();
			ClearBackground(DARKGRAY);
			DrawTexture(onscreen, 0,0, RAYWHITE);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	UnloadTexture(left_texture);
	UnloadTexture(right_texture);
	UnloadTexture(up_texture);
	UnloadTexture(down_texture);
	UnloadTexture(front_texture);
	UnloadTexture(back_texture);

	UnloadImage(left);
	//--------------------------------------------------------------------------------------

	return 0;
}