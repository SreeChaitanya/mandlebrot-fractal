#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
int scale=1;
int b=1;
int flag=1;
int no=2;
// Global variables
#define XDIM 1400
#define YDIM 1400
unsigned char image[YDIM][XDIM][3];
float center_re = 0.0;
float center_im = 1.0;
float radius = 2.5;
int n=64;
//---------------------------------------
// Calculate Z=Z^2+C for given C
//---------------------------------------
int mandelbrot(float C_re, float C_im, int max_count,int no)
{
  int count = 0;
  float Z_re = 0;
  float Z_im = 0;
  float magnitude = 0;
  float max_magnitude = 1000000;

  // Calculate Z=Z^2+C for given C
  if(no==2)
  {
    while ((magnitude < max_magnitude) && (count++ < max_count))
    {
      float N_re = Z_re * Z_re - Z_im * Z_im + C_re;
      float N_im = Z_re * Z_im + Z_im * Z_re + C_im;
      Z_re = N_re;
      Z_im = N_im;
      magnitude = Z_re * Z_re + Z_im * Z_im;
    }
  }
  if(no==3)
  {
    while ((magnitude < max_magnitude) && (count++ < max_count))
    {

      float N_re = Z_re * Z_re * Z_re - 3* Z_im * Z_im * Z_re + C_re;
      float N_im =3* Z_re * Z_im * Z_re - Z_im * Z_im * Z_im+ C_im;
      Z_re = N_re;
      Z_im = N_im;
      magnitude = Z_re * Z_re + Z_im * Z_im;
    }
  }
  if(no==5)
  {
    while ((magnitude < max_magnitude) && (count++ < max_count))
    {

      float N_re = Z_re * Z_re * Z_re* Z_re * Z_re - 10* Z_re * Z_re* Z_re * Z_im * Z_im +5*Z_re* Z_im* Z_im* Z_im* Z_im + C_re;
      float N_im =5*Z_im* Z_re* Z_re* Z_re* Z_re- 10* Z_re * Z_re* Z_im * Z_im * Z_im+Z_im* Z_im* Z_im* Z_im*Z_im +C_im;
      Z_re = N_re;
      Z_im = N_im;
      magnitude = Z_re * Z_re + Z_im * Z_im;
    }
  }
  else
  {
    while ((magnitude < max_magnitude) && (count++ < max_count))
    {
      float N_re = pow(Z_re * Z_re + Z_im * Z_im,no/2)*cos(no*atan2(Z_im,Z_re)) + C_re;
      float N_im = pow(Z_re * Z_re + Z_im * Z_im,no/2)*sin(no*atan2(Z_im,Z_re))+ C_im;
      Z_re = N_re;
      Z_im = N_im;
      magnitude = Z_re * Z_re + Z_im * Z_im;
    }

  }
  // Return number of iterations
  if (count >= max_count)
  return 0;
  else
  return count;
}
void input()
{
  printf("\n Enter N (2,3,5):");
  scanf("%d",&no);

}

//---------------------------------------
// Initialize mandelbrot image
//---------------------------------------
void init_mandelbrot()
{
  for (int y = 0; y < YDIM; y++)
  for (int x = 0; x < XDIM; x++)
  {
    float C_re = center_re - radius + (2 * radius * x) / XDIM;
    float C_im = center_im - radius + (2 * radius * y) / YDIM;
    image[y][x][0] = image[y][x][1] = image[y][x][2] =
    100*mandelbrot(C_re, C_im, n,no);
  }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
  // Initialize OpenGL
  glClearColor(0.0, 0.0, 0.0, 1.0);
  init_mandelbrot();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);
  glFlush();
}
void custom()
{
  printf("\n Enter the number of iterations ");
  scanf("%d",&n);
  init();
  glutPostRedisplay();
}
void basic()
{ //n=sqrt(abs(2*sqrt(abs(1-sqrt(5*scale)))))*66.5;
}
void movearound(int key,int x,int y)
{	printf("%d",key);
if(key==GLUT_KEY_RIGHT)
{
  center_re=center_re-0.1;
  init();
  glutPostRedisplay();
}
else if (key==GLUT_KEY_LEFT)
{
  center_re=center_re+0.1;
  init();
  glutPostRedisplay();
}
else if (key==GLUT_KEY_UP)
{
  center_im=center_im-0.05;
  init();
  glutPostRedisplay();
}
else if (key==GLUT_KEY_DOWN)
{
  center_im=center_im+0.05;
  init();
  glutPostRedisplay();
}


}
void ch_input(int choice)
{
  switch(choice)
  {
    case 1:exit(0);
    break;
    case 2:custom();
    break;
    case 3:basic();
    break;
  }
}
void zoom(unsigned char key,int x,int y)
{
  switch(key)
  {
    case 'z':
    //XDIM+=400;

    if(radius>0.1)
    {
      radius-=0.2;
      //YDIM+=400;
      init();
      glutPostRedisplay();}
      break;

      case 'x':
      if(flag==1)
      {
        if(radius<3)
        {
          radius+=0.2;
          init();
          glutPostRedisplay();
        }
      }
      else
      {
        if(radius>0.1)
        {
          radius-=0.2;
          //YDIM+=400;
          init();
          glutPostRedisplay();}
          break;
        }

        case 'w':{ init();
          glPixelZoom(1.1*b,1.1*b);
          b=b+0.1;
          glutPostRedisplay();
          break;
        }

        case 'e':{
          init();
          glPixelZoom(1.5/b,1.5/b);
          if(b!=0.1)
          b=b-0.1;
          glutPostRedisplay();
          break;
        }
        case 'f':
        {
          radius=-radius;

          center_im = -center_im;
          flag=-flag;
          init();
          glutPostRedisplay();
          break;
        }

      }

    }

    void choice()
    {
      glutCreateMenu(ch_input);
      glutAddMenuEntry("quit",1);
      glutAddMenuEntry("Custom Iterations:",2);
      glutAddMenuEntry("Basic View:",3);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
    }

    //---------------------------------------
    // Main program
    //---------------------------------------
    int main(int argc, char *argv[])
    {
      // Create OpenGL window
      glutInit(&argc, argv);
      glutInitWindowSize(XDIM, YDIM);
      glutInitWindowPosition(0, 0);
      glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
      glutCreateWindow("Mandelbrot");
      input();
      choice();
      init();
      // Specify callback function
      glutSpecialFunc(movearound);
      glutKeyboardFunc(zoom);
      //glutMouseFunc();
      glutDisplayFunc(display);

      glutMainLoop();
      return 0;
    }
