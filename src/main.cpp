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


#include <string>
#include <format>
#include <iostream>

#include <CLI/CLI.hpp>


// char yml_buf[] = "{foo: 1, bar: [2, 3], john: doe}";
// 	ryml::Tree tree = ryml::parse_in_place(yml_buf);
// 	ryml::ConstNodeRef root = tree.rootref();  // a const node reference
// 	int foo=0;
// 	tree["foo"] >> foo;


struct CubeMap {
    Texture2D left;
    Texture2D right;
    Texture2D front;
    Texture2D back;
    Texture2D up;
    Texture2D down;
};


void make_art28(CubeMap& cb, std::string& base_dir) {
    
    //std::string base_dir = "f:/a/a28/art/sb01/";
    std::string left_file = base_dir+"skybox_LF.jpg";
    std::string right_file = base_dir+"skybox_RT.jpg";
    std::string front_file = base_dir+"skybox_FR.jpg";
    std::string back_file = base_dir+"skybox_BK.jpg";
    std::string up_file = base_dir+"skybox_UP.jpg";
    std::string down_file = base_dir+"skybox_DN.jpg";

    Image left = LoadImage(left_file.c_str());
    Image right = LoadImage(right_file.c_str());
    Image front = LoadImage(front_file.c_str());
    Image back = LoadImage(back_file.c_str());
    Image up = LoadImage(up_file.c_str());
    Image down = LoadImage(down_file.c_str());


    // NOTE: Rotate by angle had issue creating lines
    ImageRotateCW(&left);
    ImageRotateCW(&front);
    ImageRotateCW(&front);
    ImageRotateCCW(&right);
    ImageRotateCW(&down);
    ImageRotateCW(&down);

    cb.left = LoadTextureFromImage(left);
    cb.right = LoadTextureFromImage(right);
    cb.front = LoadTextureFromImage(front);
    cb.back = LoadTextureFromImage(back);
    cb.up = LoadTextureFromImage(up);
    cb.down = LoadTextureFromImage(down);


}

void make_blender(CubeMap& cb, std::string& base_dir, std::string& base_name, bool no_rotate=false) {
    std::string left_file = base_dir+base_name+"0001.png";
    std::string right_file = base_dir+base_name+"0003.png";
    std::string up_file = base_dir+base_name+"0002.png";
    std::string down_file = base_dir+base_name+"0004.png";
    std::string front_file = base_dir+base_name+"0005.png";
    std::string back_file = base_dir+base_name+"0006.png";


    Image left = LoadImage(left_file.c_str());
    Image right = LoadImage(right_file.c_str());
    Image front = LoadImage(front_file.c_str());
    Image back = LoadImage(back_file.c_str());
    Image up = LoadImage(up_file.c_str());
    Image down = LoadImage(down_file.c_str());

    if (!no_rotate) {
        // NOTE: Rotate by angle had issue creating lines
        ImageRotateCCW(&left);
        //ImageRotateCW(&front);
        ImageRotateCCW(&up);
        //ImageRotateCCW(&down);
        ImageRotateCCW(&back);
        ImageRotateCCW(&back);
        ImageRotateCW(&right);
        //ImageRotateCCW(&right);
        ImageRotateCCW(&down);
        //ImageRotateCCW(&down);
    }
    
    

    cb.left = LoadTextureFromImage(left);
    cb.right = LoadTextureFromImage(right);
    cb.front = LoadTextureFromImage(front);
    cb.back = LoadTextureFromImage(back);
    cb.up = LoadTextureFromImage(up);
    cb.down = LoadTextureFromImage(down);
}

void make_space_scape(CubeMap& cb, std::string& base_dir, std::string& base_name) {
    std::string left_file = base_dir+base_name+"_left.png";
    std::string right_file = base_dir+base_name+"_right.png";
    std::string front_file = base_dir+base_name+"_front.png";
    std::string back_file = base_dir+base_name+"_back.png";
    std::string up_file = base_dir+base_name+"_up.png";
    std::string down_file = base_dir+base_name+"_down.png";

    Image left = LoadImage(left_file.c_str());
    Image right = LoadImage(right_file.c_str());
    Image front = LoadImage(front_file.c_str());
    Image back = LoadImage(back_file.c_str());
    Image up = LoadImage(up_file.c_str());
    Image down = LoadImage(down_file.c_str());


    // NOTE: Rotate by angle had issue creating lines
    ImageRotateCW(&left);
    ImageRotateCW(&up);
    ImageRotateCW(&up);
    ImageRotateCW(&front);
    ImageRotateCW(&front);
    ImageRotateCCW(&right);
    //ImageRotateCW(&down);
    //ImageRotateCW(&down);

    cb.left = LoadTextureFromImage(left);
    cb.right = LoadTextureFromImage(right);
    cb.front = LoadTextureFromImage(front);
    cb.back = LoadTextureFromImage(back);
    cb.up = LoadTextureFromImage(up);
    cb.down = LoadTextureFromImage(down);
}


void unload_cubemap(CubeMap& cb) {
    UnloadTexture(cb.left);
    UnloadTexture(cb.right);
    UnloadTexture(cb.up);
    UnloadTexture(cb.down);
    UnloadTexture(cb.front);
    UnloadTexture(cb.back);
}


int main(int argc, char* argv[])
{

    CLI::App app{"Boxey - A skybox creation tool for cubemaps compatible with Artemis Cosmos."};

    bool my_flag{false};
    app.add_flag("-s,--show", my_flag, "Show window");

    int sky_type{0};
    app.add_option("-t,--type", sky_type, "Process as 0 (default) = Created with Blender, 1 = Artemis 2.8 files, 2 = Space scape");

    std::string base_dir = ".";
    app.add_option("-d,--directory", base_dir, "Directory for source file. Default: current directory.");

    std::string base_name = ".";
    app.add_option("-f,--file", base_name, "The file base name for the images. Default: blank for blender, \"skybox\" for artemis and spacescape.");

    std::string outfile = "skybox.png";
    app.add_option("-o,--output", outfile , "Output file name.");

    CLI11_PARSE(app, argc, argv);

    if (base_name==".") {
        if (sky_type==0) base_name = "";
        else if (sky_type!=0) base_name = "skybox";
    }

    

    if (!my_flag) {
        std::cout << "Processing images\n";
        if (sky_type == 0) {
            std::cout << "Using blender rendered format (0001.png)\n";    
        } else if (sky_type == 1) {
            std::cout << "Using artemis format (skybox_??.png) with ?? = BK,DN,FR,LF,RT,UP\n";
        } else if (sky_type == 2) {
            std::cout << "Using spacescape format (skybox_??.png) with ?? = back,down,front,left,right,up\n";
        }
        std::cout << "Base dir: " << base_dir << "\n";
        std::cout << "Base filename: " << base_name << "\n";
        std::cout << "Output: " << outfile << "\n";
        std::cout << "Processing images\n";
    }

    SetTraceLogLevel(LOG_ERROR); 

    int screenWidth = 1280;
    int screenHeight = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT|FLAG_WINDOW_HIGHDPI|FLAG_WINDOW_HIDDEN);
    InitWindow(screenWidth, screenHeight, "Boxey");

    CubeMap cb;
    //std::string dir = std::format("sb{:02d}", 10);
    //std::string base_dir = std::format("f:/a/a28/art/{}/", dir);
    if (sky_type==0) {
        make_blender(cb, base_dir, base_name, true);
    } else if (sky_type==1) {
        make_art28(cb, base_dir);
    } else if (sky_type==2) {
        make_space_scape(cb, base_dir, base_name);
    } else if (sky_type==1) {
        make_blender(cb, base_dir, base_name, false);
    }

    int width = cb.left.width;
    int height = cb.left.height;
    RenderTexture2D output = LoadRenderTexture(width*4, height*3);


    BeginDrawing();
        BeginTextureMode(output);
            // Line 1
            DrawTexture(cb.front, width, 0, RAYWHITE);
            //Line 2
            DrawTexture(cb.left, 0* width, height, RAYWHITE);
            DrawTexture(cb.up, 1*width, height, RAYWHITE);
            DrawTexture(cb.down, 3*width, height, RAYWHITE);
            DrawTexture(cb.right, 2*width, height, RAYWHITE);
            // Line 3
            DrawTexture(cb.back, width, height*2, RAYWHITE);
        EndTextureMode();
    EndDrawing();


    Image offscreen = LoadImageFromTexture(output.texture);
    ImageFlipVertical(&offscreen);
    Texture2D onscreen = LoadTextureFromImage(offscreen);
    //std::string outfile = std::format("{}.png", dir);
    ExportImage(offscreen, outfile.c_str());
    //let mut offscreen = output.texture().load_image().unwrap();
    //offscreen.flip_vertical();
    //offscreen.export_image("cube2.png");
    //let onscreen = rl.load_texture_from_image(&thread, &offscreen).unwrap();
    if (!my_flag) {
        return 0;
    }
    // Initialization
    //--------------------------------------------------------------------------------------
    if (IsWindowHidden()) {
        ClearWindowState(FLAG_WINDOW_HIDDEN); 
    }

    SetTargetFPS(30);


    
    // Main game loop
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /* UPDATE */
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
            camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
        }

        /* DRAW */
    
        BeginDrawing();
            ClearBackground(DARKGRAY);
            BeginMode2D(camera);
                DrawTexture(onscreen, 0,0, RAYWHITE);
            EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context

    unload_cubemap(cb);
    
    //--------------------------------------------------------------------------------------

    return 0;
}