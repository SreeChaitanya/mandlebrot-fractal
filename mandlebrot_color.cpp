#include<stdio.h>
#include<glut.h>
#include<stdlib.h>
#define ImageHeight 500
#define ImageWidth 500
GLdouble MinRe = -2.0;
GLdouble MaxRe = 1.0;
GLdouble MinIm = -1.2;
GLdouble MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
GLdouble Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
GLdouble Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
unsigned MaxIterations = 30;
void display()
{

  for(unsigned y=0; y<ImageHeight; ++y)
  {
    GLdouble c_im = MaxIm - y*Im_factor;
    glBegin(GL_POINTS);
    for(unsigned x=0; x<ImageWidth; ++x)
    {
      GLdouble c_re = MinRe + x*Re_factor;

      GLdouble Z_re = c_re, Z_im = c_im;
      bool isInside = true;
      for(unsigned n=0; n<MaxIterations; ++n)
      {
        GLdouble Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
        if(Z_re2 + Z_im2 > 4)
        {
          isInside = false;
          break;
        }
        Z_im = 2*Z_re*Z_im + c_im;
        Z_re = Z_re2 - Z_im2 + c_re;
      }
      if(isInside) { glVertex2f(x, y); }
    }
  }
}
void myinit()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODEL_VIEW);
}

int main(int argc,char *argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Mandlebrot Set");
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();
}
