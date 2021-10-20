#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>


SDL_Window* gWindow=NULL;

SDL_Renderer* gRenderer = NULL;

int screenWidth=600;
int screenHeight=600;

#include "texture.h"

enum pieceName
{
    whitePawn=0,
    whiteBishop=1,
    whiteKnight=2,
    whiteRock=3,
    whiteQueen=4,
    whiteKing=5,
    blackPawn=6,
    blackBishop=7,
    blackKnight=8,
    blackRock=9,
    blackQueen=10,
    blackKing=11
};
int board[8][8]={blackRock,blackKnight,blackBishop,blackQueen,blackKing,blackBishop,blackKnight,blackRock,
                 blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,
                 -1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,
                 whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,
                 whiteRock,whiteKnight,whiteBishop,whiteQueen,whiteKing,whiteBishop,whiteKnight,whiteRock};

texture blackSquare,whiteSquare;
texture chessPiece[12];

bool Init_SDL()
{
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
		    SDL_SetWindowResizable(gWindow,SDL_TRUE);
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Load_Media()
{
    blackSquare.Load_Image(gRenderer,"blackSquare.png");
    whiteSquare.Load_Image(gRenderer,"whiteSquare.png");
    chessPiece[whitePawn].Load_Image(gRenderer,"wP.png");
    chessPiece[whiteBishop].Load_Image(gRenderer,"wB.png");
    chessPiece[whiteKnight].Load_Image(gRenderer,"wN.png");
    chessPiece[whiteRock].Load_Image(gRenderer,"wR.png");
    chessPiece[whiteQueen].Load_Image(gRenderer,"wQ.png");
    chessPiece[whiteKing].Load_Image(gRenderer,"wK.png");
    chessPiece[blackPawn].Load_Image(gRenderer,"bP.png");
    chessPiece[blackBishop].Load_Image(gRenderer,"bB.png");
    chessPiece[blackKnight].Load_Image(gRenderer,"bN.png");
    chessPiece[blackRock].Load_Image(gRenderer,"bR.png");
    chessPiece[blackQueen].Load_Image(gRenderer,"bQ.png");
    chessPiece[blackKing].Load_Image(gRenderer,"bK.png");
}

void Close_SDL()
{
    chessPiece[whitePawn].Free_Texture();
    chessPiece[whiteBishop].Free_Texture();
    chessPiece[whiteKnight].Free_Texture();
    chessPiece[whiteRock].Free_Texture();
    chessPiece[whiteQueen].Free_Texture();
    chessPiece[whiteKing].Free_Texture();
    chessPiece[blackPawn].Free_Texture();
    chessPiece[blackBishop].Free_Texture();
    chessPiece[blackKnight].Free_Texture();
    chessPiece[blackRock].Free_Texture();
    chessPiece[blackQueen].Free_Texture();
    chessPiece[blackKing].Free_Texture();
    blackSquare.Free_Texture();
    whiteSquare.Free_Texture();

    SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc,char* args[])
{
    Init_SDL();
    Load_Media();
    bool quit = false;

    //Event handler
    SDL_Event e;
    int prevHeight=0,prevWidth=0;
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        int side=screenHeight;
        if(side>screenWidth)
                    side=screenWidth;
        side=side-side%8;
        if(prevHeight!=screenHeight||prevWidth!=screenWidth)
            SDL_SetWindowSize(gWindow,side,side);
        prevHeight=screenHeight;
        prevWidth=screenWidth;
        SDL_GetWindowSize(gWindow,&screenWidth,&screenHeight);
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        //Render background texture to screen

        for(int i=0;i<8;i++)
        {

         int sumI=side/8;
         sumI=sumI*i;
            for(int j=0;j<8;j++)
            {
                int sumJ=side/8;
                sumJ=sumJ*j;

                if(i%2==j%2)
                    whiteSquare.Render_Texture(gRenderer,sumJ,sumI,0.125);
                else
                    blackSquare.Render_Texture(gRenderer,sumJ,sumI,0.125);
                if(board[i][j]!=-1)
                    chessPiece[board[i][j]].Render_Texture(gRenderer,sumJ,sumI,0.125);
            }
        }
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    Close_SDL();
    return 0;
}
