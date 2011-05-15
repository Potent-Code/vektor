/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

//void cleanup(void)
//{
//	TTF_CloseFont(font);
//	TTF_Quit();
//}

void init_scene(void)
{
	//TTF_Init();
	//font = TTF_OpenFont("Tahoma.ttf",11);
	//atexit(cleanup);
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

	/*// up
	if(controls[0] && ! (controls[2] || controls[3]))
	{
		dir_frame=4.;
	}

	// down
	if(controls[1] && ! (controls[2] || controls[3]))
	{
		dir_frame=0.;
	}

	// up right and up left
	if(controls[0] && (controls[2] || controls[3]))
	{
		dir_frame=3.;
	}

	// down right and down left
	if(controls[1] && (controls[2] || controls[3]))
	{
		dir_frame=1.;
	}

	// right and left
	if((controls[2] || controls[3]) && ! controls[1]  && ! controls[0])
	{
		dir_frame=2.;
	}

	// left/right
	if(controls[2])
	{
		flip=1;
	}
	if(controls[3])
	{
		flip=0;
	}

	texcoords[0][0]+=dir_frame/6.;
	texcoords[1][0]+=dir_frame/6.;
	texcoords[2][0]+=dir_frame/6.;
	texcoords[3][0]+=dir_frame/6.;

	// mirroring
	if(flip && !(dir_frame==0 || dir_frame==4))
	{
		// the 2px shift is in here for reasons
		// i dont yet understand...for now it gets
		// rid of some artifacting after flipping
		// swap bottom points
		tmp=texcoords[0][0]-(2./198.);
		texcoords[0][0]=texcoords[1][0];
		texcoords[1][0]=tmp;

		// swap top points
		tmp=texcoords[2][0];
		texcoords[2][0]=texcoords[3][0];
		texcoords[3][0]=tmp-(2./198.);
	}*/

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
		fprintf(stderr,"\r%.f\tfps",framecount/et);
		framecount=1;
		t=clock();
	}
}
