/********************************
 Parallax sidescrolling starfield
 Jason Bou-Samra [ParagonSoft]
 28/03/2024
 to compile:
 cc -o stars stars.c -lSDL2
 ********************************/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int initSDL (void);
int shutdownSDL (void);

bool quit = false;                  		/* quit flag */

SDL_Window *window = NULL;
SDL_Renderer *sr;
SDL_Event event;

/* window paramaters */
#define WIDTH 640				/* pixels */
#define HEIGHT 512				/* pixels */
#define TITLE "Starfield"			/* window title */

int StarAmount = 256;
int xres = 640;
int yres = 512;

struct StarField {				/* star structure */
int x;
int y;
int speed;
};

int main(int argc, char **argv)			/* allow StarAmount as paramater */
{

	    const char* filename = argv[1];	/* parse command line arguments */
  if (argc != 2){				/* display usage if less than 2 arguments passed */
      printf("Usage: stars [<quantity>|OPTION]\n\
stars --help for help\n");
      return 1;
    }						// display usage, then exit

if(!strcmp(filename, "--about")) {
    printf("Paralax sidescrolling starfield\n\
Jason Bou-Samra 28/03/2024.\n\n"); return 0;
    }						/* display about, then exit */

if(!strcmp (filename,  "--help")) {
    printf("Usage: stars [<quantity>]\n\n\
OPTIONS\n\
--about            displays about message\n\
--help             displays this help message\n"); return 0;
    }

    StarAmount = atoi(argv[1]);
if (StarAmount == 0) {
printf("invalid options\n\
stars --help for help\n"); return 0;}
	initSDL ();

struct StarField stars[StarAmount];		/* array of StarField structs, named stars */

for (int x = 1; x < StarAmount; x++)		/* setup initial values */
{
stars[x].x = rand() % (xres ); 
stars[x].y = rand() % (yres );
stars[x].speed = rand() % (5+1);
}

  while (quit == false) {			/* poll for quit event */

  	      while (SDL_PollEvent (&event))
	{
	  if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
	    {
	      quit = true;
	    }
	}
      if (quit)
	{
	  break;				/* breakout of loop if quit is true */
	}

	SDL_SetRenderDrawColor(sr, 0x00, 0x00, 0x00, 0xFF);	/* set background colour for window */
	SDL_RenderClear(sr);			/* clear window */

	for (int x = 1; x < StarAmount; x++)
		{
		stars[x].x = stars[x].x + stars[x].speed;

		if (stars[x].x > xres)
			{
			stars[x].x = 0;
			stars[x].y = rand() % (yres );
			}

	SDL_SetRenderDrawColor(sr, 51*stars[x].speed, 51*stars[x].speed, 51*stars[x].speed, 0xFF); /* star color (R, G, B, A) */
	SDL_RenderDrawPoint(sr, stars[x].x, stars[x].y);	/* plot star */
}
 	SDL_RenderPresent (sr);
}																			// keep going until quit event

  shutdownSDL ();				/* bye */
return 0;
}

/* initialise SDL */
int initSDL ()
{
  SDL_Init (SDL_INIT_EVERYTHING);

/* new window */
  window = SDL_CreateWindow (TITLE,			/* title */
			     SDL_WINDOWPOS_UNDEFINED,	/* x pos */
			     SDL_WINDOWPOS_UNDEFINED,	/* w pos */
			     WIDTH,			/* width */
			     HEIGHT,			/* height */
			     0);			/* Additional flag(s) */

  /* deal with error */
  if (window == NULL)
    {
      fprintf (stderr, "SDL window failed to initialise: %s\n",
	       SDL_GetError ());
      return 1;
    }

/* creater renderer */
  sr = SDL_CreateRenderer (window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

/* shutdown routine */
int shutdownSDL ()
{
  SDL_DestroyWindow (window);			/* free memory */
  SDL_Quit ();					/* shutdown entire sdl sub-systems */
  return 0;
}

/* message */
char message[] = { "Yes, Jesus loves you!" };
