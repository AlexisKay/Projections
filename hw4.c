/* 
	Alexis McBeain
	hw3 - 3D Scene
	
	I used the examples given in Canvas for some functions and as guides for my program 

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//MANY angle variables
double zh=0; 
int mode=0;       
int th=180;         
int ph=0;         
int fov=55;       
double asp=1;     
double dim=5.0;   
float a = 1.0;
float b = 1.0;
float c = 0.0;
int first = 0;
int rot = 1.0;
double Ex = 1;
double Ey = 0;
double Ez = -5;
double Vx =0;
double Vz=0;
int axes=0; 

#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

#define LEN 8192  
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


static void Project()
{
 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   if(first){
	   gluPerspective(fov,asp,dim/10,10*dim);
   }
   else {
		if (mode)
			gluPerspective(fov,asp,dim/10,10*dim);
    // Orthogonal projection
		else
			glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   }
   glMatrixMode(GL_MODELVIEW);
 
   glLoadIdentity();
}




static void Buildings(double x, double y, double z, double dx, double dy, double dz, double th){
	
  
  glPushMatrix();
  
  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  //buildings
  glBegin(GL_QUADS);
	//Front
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,-1, 1);
	glVertex3f(1,-1, 1);
	glVertex3f(1,1, 1);
	glVertex3f(-1,1, 1);
	//Back
	glColor3f(0.8,0.8,0.8);
	glVertex3f(1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,1,-1);
	glVertex3f(1,1,-1);
	//Right
	glColor3f(0.8,0.8,0.8);
	glVertex3f(1,-1,1);
	glVertex3f(1,-1,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,1);
	//Left
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,1,1);
	glVertex3f(-1,1,-1);
	//Top
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,1,1);
	glVertex3f(1,1,1);
	glVertex3f(1,1,-1);
	glVertex3f(-1,1,-1);
	//Bottom
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,-1,-1);
	glVertex3f(1,-1,-1);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
  glEnd();
  
	//triangles are hard :(

  //window
	glBegin(GL_QUADS);
		glColor4f(a, b, c, 0.0f);
		//Front
		glVertex3f(.1,-.5,-1.1);
		glVertex3f(-.3,-.5,-1.1);
		glVertex3f(-.3,0,-1.1);
		glVertex3f(.1,0,-1.1);
		//Top
		glVertex3f(.1,0,-1.1);
		glVertex3f(.1,0,-1.1);
		glVertex3f(-.1,0,-1.1);
		glVertex3f(-.1,0,-1.1);
		//Right
		glVertex3f(.1,0,-1.1);
		glVertex3f(.1,-.5,-1.1);
		glVertex3f(.1,-.5,-1.1);
		glVertex3f(.1,0,-1.1);
		//Left
		glVertex3f(-.3,0,-1.1);
		glVertex3f(-.3,-.5,-1.1);
		glVertex3f(-.3,-5,-1.1);
		glVertex3f(-.3,0,-1.1);
	glEnd();
  
   //door
  glBegin(GL_QUADS);
	glColor3f(0.1f, 0.0f, 0.0f);
	//Front
	glVertex3f(.8,-1,-1.1);
	glVertex3f(.3,-1,-1.1);
	glVertex3f(.3,0,-1.1);
	glVertex3f(.8,0,-1.1);
	//Top
	glVertex3f(.8,0,-1.1);
	glVertex3f(.8,0,-1);
	glVertex3f(.3,0,-1.1);
	glVertex3f(.3,0,-1);
	//Right
	glVertex3f(.8,0,-1);
	glVertex3f(.8,-1,-1);
	glVertex3f(.8,-1,-1);
	glVertex3f(.8,0,-1);
	//Left
	glVertex3f(.3,0,-1);
	glVertex3f(.3,-1,-1);
	glVertex3f(.3,-1,-1);
	glVertex3f(.3,0,-1);
  glEnd();

   

  glPopMatrix();
}

void display()
{	
	const double len=3;
   
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity();
  /*  glOrtho(-3, 3, -3, 3, -10, 10); */
   
   if (first){
	   Vx = 2*dim*Sin(rot);
	   Vz = 2*dim*Cos(rot);
	   
		gluLookAt(Ex,Ey,Ez, Vx+Ex,Ey,Vz+Ez,0,1,0);

   }
   else{
	if (mode)
		{
		double Ex = -2*dim*Sin(th)*Cos(ph);
		double Ey = +2*dim        *Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);
		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
		}
	//  Orthogonal - set world orientation
	else
	{
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}
   }
   
   //  Draw axes
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   
  
   //build city thing
    /* Buildings(5,0, 1, 1,1,1, -50); */
	Buildings(5.5,0,1, 1.5,1,1.5, -25);
	Buildings(1,0,1 , 1,1,1, 0); 
	Buildings(-3,0,1 , .5,1,.5, 25);
	Buildings(-7,0,5 , 2,1,2, 50);
   
  
   
   //ground
	glColor3f(0.0f, 0.1f, 0.0f); //DARK GREEN
	glBegin(GL_QUADS);
		glVertex3f(-10,-1.1,-10);
		glVertex3f(-10,-1.1,10);
		glVertex3f(10,-1.1,10);
		glVertex3f(10,-1.1,-10);
   glEnd();

   glColor3f(1,1,1);
   glWindowPos2i(5,5);
    Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
   
  /*  glWindowPos2i(5,25);
   Print("W = Window Lights on");
   
   glWindowPos2i(5, 45);
   Print("S = Window Lights off"); */
   

   glFlush();
   glutSwapBuffers();
}



void movement(int key,int x,int y)
{
  
   if (key == GLUT_KEY_RIGHT)
      th += 5;

   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   
   else if (key == GLUT_KEY_UP)
      ph += 5;
  
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
	
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   
   th %= 360;
   ph %= 360;
    Project();
   glutPostRedisplay();
}


void key(unsigned char ch,int x,int y)
{
     //  Exit on ESC
   if (ch == 27)
      exit(0);
	else if (ch == 'x')
      axes = 1-axes;
   //  Toggle first person with F
   else if (ch == 'f' || ch == 'F')
   {
      first = 1- first;
	  
   }

   //wasd keys for movements when in first person
   if (first){
      double dt = 0.05;
      if (ch == 'w' || ch == 'W'){
         Ex += Vx*dt; 
         Ez += Vz*dt;
      }
      else if (ch == 'a' || ch == 'A'){
         rot -= 3;
      }
      else if (ch == 's' || ch == 'S'){
         Ex -= Vx*dt;
         Ez -= Vz*dt;
      }
      else if (ch == 'd' || ch == 'D'){
         rot += 3;
      }
	  else if( ch == 32){
		   rot = 1.0;
			Ex = 1;
			Ey = 0;
			Ez = -5;
			Vx =0;
			Vz=0;
	  }

      //  Keep angles to +/-360 degrees
      rot %= 360;
   }
   else {
     if (ch == 32){
         th = 180;
		 ph = 0;
		 fov = 55;
		 dim = 5.0;
	 }
      //  Switch display mode with M -> example 9 from Canvas
    else if (ch == 'm' || ch == 'M')
         mode = 1-mode;
      //  Change field of view angle with + and -
      else if (ch == '-')
         fov--;
      else if (ch == '+')
         fov++;
   }
 
   Project();
   glutPostRedisplay();
}


void reshape(int width,int height)
{
   const double dim=2.5;
 
   double w2h = (height>0) ? (double)width/height : 1;

   glViewport(0,0, width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   glMatrixMode(GL_MODELVIEW);
   
   Project();
   glLoadIdentity();
}


void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}


int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitWindowSize(800,800);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Alexis McBeain - Assignment 4");
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(movement);
   glutKeyboardFunc(key);
   glutMainLoop();
   
   return 0;
}