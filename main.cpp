#include "raylib.h"
#include <iostream>

//an enum is a datatype used to define a set of named constants
enum TileType{
    EMPTY = 0,
    WALL = 1,
    KEY = 2,
    PLAYER = 3
};

const int rows =10;
const int cols =10;
const int tileSize = 40;

int map[rows][cols] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 3, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 2, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int playerRow = 3; //player starting position (row)
int playerColumn = 3; //player starting position (column)


Texture2D pathTexture;
Texture2D wallTexture;
Texture2D keyTexture;
Texture2D playerTexture;

void LoadTextures(){
    pathTexture = LoadTexture("images/tile_path.png");
    wallTexture = LoadTexture("images/tile_wall.png");
    keyTexture = LoadTexture("images/tile_key.png");
    playerTexture = LoadTexture("images/tile_player.png");
}

void UnloadTextures(){
    //unload textures from memory
    UnloadTexture(pathTexture);
    UnloadTexture(wallTexture);
    UnloadTexture(keyTexture);
    UnloadTexture(playerTexture);
}

void DrawMap(){
    //loop through the row
    for(int row=0; row <rows; row++){
        //loop through the columns
        for(int col=0; col<cols;col++){
            int posX = col * tileSize;
            int posY = row * tileSize;
            
            //always draw the path texture first
            DrawTexture(pathTexture, posX, posY, WHITE);

            //check the tile type and draw the appropriate texture
            if(map[row][col] == WALL){
                DrawTexture(wallTexture, posX, posY, WHITE);
            }
            else if(map[row][col] == KEY){
                DrawTexture(keyTexture, posX, posY, WHITE);
            }
            else if(map[row][col] == PLAYER){
                DrawTexture(playerTexture, posX, posY, WHITE);
            }
            else if(map[row][col] == EMPTY){
                DrawTexture(pathTexture, posX, posY, WHITE);
            }
        }
    }
}

void UpdatePlayer(){
    int newRow = playerRow;
    int newCol = playerColumn;
    if(IsKeyPressed(KEY_RIGHT)){
        newCol +=1;
    }
    else if(IsKeyPressed(KEY_LEFT)){
        newCol -=1;
    }
    else if(IsKeyPressed(KEY_UP)){
        newRow -=1;
    }
    else if(IsKeyPressed(KEY_DOWN)){
        newRow +=1;
    }

    if(newCol >=0 && newCol <cols && newRow >=0 && newRow < rows && map[newRow][newCol] != WALL){
        //check if the new position is a key
        if(map[newRow][newCol] == KEY){          
            std::cout << "You found the key!" << std::endl;         
        }

        map[playerRow][playerColumn] = EMPTY; //set the old position to empty 0
        playerRow = newRow;
        playerColumn = newCol;
        map[playerRow][playerColumn] = PLAYER;
    }

   
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Tile Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    LoadTextures();
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdatePlayer();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawMap();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTextures();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}