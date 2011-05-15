/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

void init_scene(void)
{
	if(0>load_texture("gfx/textures/bg/world_map_2.texture"))
	{
		fprintf(stderr,"Error loading texture!\n");
	}
	if(0>load_texture("gfx/textures/sprites/noxx/noxx.texture"))
	{
		fprintf(stderr,"Error loading texture!\n");
	}
	player = player_sprite(400,300,33,64,gltextures[1]);
	dir_frame=0;
	flip=0;
	framecount=0;
	t=clock();
	at=clock();
	mt=clock();
}
	
void render(void)
{
	double et;
	framecount++;

	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(player->x-400, player->x+400, player->y-300, player->y+300);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gltextures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(1520,1520);
		glTexCoord2f(1,0); glVertex2f(0,1520);
		glTexCoord2f(1,1); glVertex2f(0,0);
		glTexCoord2f(0,1); glVertex2f(1520,0);
	glEnd();	
	glDisable(GL_TEXTURE_2D);

	// update our sprites
	player->draw(player);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	SDL_GL_SwapBuffers();

	glEnd();
	glFlush();

	if((et = (double)(clock()-t)/CLOCKS_PER_SEC) >= .25)
	{
		//fprintf(stderr,"\r%.f\tfps",framecount/et);
		framecount=1;
		t=clock();
	}
}
