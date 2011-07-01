/* plant fractals
 * by Ryan Lucchese
 * May 27 2011 */

#include "plant.h"

plant add_plant(float x, float y, float l, float angle, unsigned int iterations);
void draw_plant(void *pp);
void free_plant(void *pp);
unsigned int grow(plant p, unsigned int n);

plant add_plant(float x, float y, float l, float angle, unsigned int iterations)
{
	plant p;
	int i,j;
	p = malloc(sizeof(*p));

	p->branches = calloc(10000,sizeof(*p->branches));
	p->x = x;
	p->y = y;
	p->l = l;
	p->angle = angle;
	p->iterations = iterations;

	p->nbranches = grow(p,0);

	add_object_2d(p, &draw_plant, NULL, &free_plant);
	return p;
}

void draw_plant(void *pp)
{
	plant p = pp;

	int i=0;

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	for(i=0; i < p->nbranches; i++)
	{
		if(i != 2)
		{
			glVertex3f(p->branches[i].x1,p->branches[i].y1,0.1);
			glVertex3f(p->branches[i].x2,p->branches[i].y2,0.1);
		}
	}
	
	glEnd();
	//glDepthFunc(GL_GEQUAL);
}

// add new branches to the plant
unsigned int grow(plant p, unsigned int n)
{
	// done growing
	if(n == 5*p->iterations)
	{
		return n;
	}

	// first branch
	if(n == 0)
	{
		p->branches[n].x1 = p->x;
		p->branches[n].y1 = p->y;
		p->branches[n].angle = M_PI/2.; // start facing up
		p->branches[n].x2 = p->branches[n].x1 + p->l*cos(p->branches[n].angle);
		p->branches[n].y2 = p->branches[n].y1 + p->l*sin(p->branches[n].angle);
		n++;
	}
	
	if(n == 5)
	{
		p->branches[n].x1 = p->branches[0].x2;
		p->branches[n].y1 = p->branches[0].y2;
		p->branches[n].angle = p->branches[0].angle;
	}
	else if(n == 1)
	{
		p->branches[n].x1 = p->branches[0].x2;
		p->branches[n].y1 = p->branches[0].y2;
		p->branches[n].angle = p->branches[0].angle;
	}
	else
	{
		// start at last end point
		p->branches[n].x1 = p->branches[n-(n/5)-1].x2;
		p->branches[n].y1 = p->branches[n-(n/5)-1].y2;
		p->branches[n].angle = p->branches[n-(n/5)-1].angle;
	}

	if(n != 1)
	{
		p->branches[n].x2 = p->branches[n].x1 + (p->l/sqrt(n))*cos((double)p->branches[n].angle);
		p->branches[n].y2 = p->branches[n].y1 + (p->l/sqrt(n))*sin((double)p->branches[n].angle);
		n++;
	}

	// draw next branches
	p->branches[n].x1 = p->branches[n-1].x2;
	p->branches[n].y1 = p->branches[n-1].y2;
	p->branches[n].angle = p->branches[n-1].angle - p->angle; 
	p->branches[n].x2 = p->branches[n].x1 + (p->l/sqrt(n))*cos((double)p->branches[n].angle);
	p->branches[n].y2 = p->branches[n].y1 + (p->l/sqrt(n))*sin((double)p->branches[n].angle);
	n++;

	p->branches[n].x1 = p->branches[n-2].x2;
	p->branches[n].y1 = p->branches[n-2].y2;
	p->branches[n].angle = p->branches[n-2].angle;
	p->branches[n].x2 = p->branches[n].x1 + (p->l/sqrt(n))*cos((double)p->branches[n].angle);
	p->branches[n].y2 = p->branches[n].y1 + (p->l/sqrt(n))*sin((double)p->branches[n].angle);
	n++;

	p->branches[n].x1 = p->branches[n-1].x2;
	p->branches[n].y1 = p->branches[n-1].y2;
	p->branches[n].angle = p->branches[n-1].angle + p->angle; 
	p->branches[n].x2 = p->branches[n].x1 + (p->l/sqrt(n))*cos((double)p->branches[n].angle);
	p->branches[n].y2 = p->branches[n].y1 + (p->l/sqrt(n))*sin((double)p->branches[n].angle);
	n++;

	p->branches[n].x1 = p->branches[n-2].x2;
	p->branches[n].y1 = p->branches[n-2].y2;
	p->branches[n].angle = p->branches[n-2].angle; 
	p->branches[n].x2 = p->branches[n].x1 + (p->l/sqrt(n))*cos((double)p->branches[n].angle);
	p->branches[n].y2 = p->branches[n].y1 + (p->l/sqrt(n))*sin((double)p->branches[n].angle);
	n++;

	n = grow(p, n);
	
	return n;
}
 
void free_plant(void *pp)
{
	plant p = pp;

	free(p->branches);
	free(p);
}
