
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define BARCHART 1
#define QUIT 4


int *dataValue_x;
int change          = 1;
GLsizei winWidth    = 1400;
GLsizei winHeight   = 600;    
GLint xRaster       = 25;
GLint yRaster       = 100;
GLint highest       = 0;
GLint lowest        = 1000000;
GLint normalHighest = 0;
GLint normalLowest  =  1000000;
GLint shifRight     = 40;
GLint intLabel[51]  = { 5,10,15,20,25,30,35,40,45,50,
                        55,60,65,70,75,80,85,90,95,100,
                        105,110,115,120,125,130,135,140,
                        145,150,155,160,165,170,175,180,
                        185,190,195,200,205,210,215,220,
                        225,230,235,240,245,250,255
};

void init (int *dataValue)
{
  dataValue_x = (int*)malloc(255*sizeof(int));
  dataValue_x = dataValue;  
  // normalize data
  for(int i = 0; i < 255; i++)
  {
    if(dataValue[i] > highest)
      highest = dataValue[i];
    if(dataValue[i] < lowest)
      lowest = dataValue[i];
  }

  int endOfScale = yRaster + 15;
  int topOfScale = 500;
  int min = lowest;
  int max = highest;
  for(int c = 0; c < 255; c++)
  {
    int normal = endOfScale + (dataValue_x[c] - min) * (topOfScale - endOfScale) / (max - min);
    if( normal > normalHighest)
      normalHighest = normal;
    if( normal < normalLowest)
      normalLowest = normal;
    dataValue_x[c] = normal;
  }  
  
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (0.0, winWidth, 0.0,winHeight);
}

void barChart (void)
{

  int j;
  int x_end[2];
//ticks along y
  int xpos = shifRight + 18;
  int len = (normalHighest - yRaster)/10;
  int yRaster_base = yRaster + 14;

  GLint k;
  glColor3f (1.0, 0.0, 0.0);      
  
  for (k = 0; k < 255; k++)
    glRecti (20 + shifRight + k*5, yRaster + 15, 23 + shifRight + k*5, dataValue_x[k]);

  glColor3f (0.0, 0.0, 0.0);      
  xRaster = 40 + shifRight;     
  
    for(j = 0; j < normalHighest - yRaster; j=j+len)
  {
    int ypos = yRaster_base+j;
    glRasterPos2i(xpos-20, ypos);
    glPointSize(3.0f); 
    glBegin(GL_POINTS); //starts drawing of points
    glVertex2f(xpos, ypos);//upper-right corner
    glEnd();//end drawing of points 
  }
  // last point
  glPointSize(3.0f); 
  glBegin(GL_POINTS); //starts drawing of points
  glVertex2f(shifRight + 18, normalHighest);//upper-right corner
  glEnd();//end drawing of points 

  // plot characters along the x-axis 
  for (int idx = 0; idx < 51; idx++) 
  {
    glRasterPos2i (xRaster, yRaster);
    // ticks along x
    glPointSize(3.0f); 
    glBegin(GL_POINTS); //starts drawing of points
    glVertex2f(xRaster+6.5, yRaster+14);//upper-right corner
    glEnd();//end drawing of points 
  
    

    int value = intLabel[idx];
    char a;
    char b;
    char c;
    if(value < 10)
    {
      a = '0';
      b = '0';
      c = value + '0';
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, a);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, b);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, c);
          
    }
    else if(value < 100)
    {
      a = '0';
      b = (value/10) + '0';
      c = (value%10) + '0';
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, a);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, b);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, c);
    }
    else 
    {
      a = (value/100) + '0';
      int temp = value%100;
      b = (temp/10) + '0';
      c = (temp%10) + '0';
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, a);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, b);
      glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, c);
    }
      xRaster += 25;

  }
  x_end[0] = xRaster;
  x_end[1] = yRaster;
  
  
  glLineWidth(1.0);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2i(0, yRaster+15);
  glVertex2i(x_end[0], x_end[1]+15);
  glEnd();

  glBegin(GL_LINES);
  glVertex2i(20+shifRight, yRaster - 30);
  glVertex2i(20+shifRight, normalHighest + 15);
  glEnd();
}

void displayFcn (void)
{
  glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
  glColor3f (0.0, 0.0, 1.0);       //  Set circle color to blue.
	if(change == 1)
    barChart();
  glutSwapBuffers ( );
}

void winReshapeFcn (int newWidth, int newHeight)
{
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ( );
  gluOrtho2D (0.0, (newWidth), 0.0, (newHeight));
	
  /*  Reset display-window size parameters.  */
  winWidth = newWidth;
  winHeight = newHeight;    
	glViewport(0, 0, newWidth, newHeight);
  glutPostRedisplay();
}

void quit()
{
	exit(0);
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 'q' || key == 'Q')
		quit();

	if(key == 'z')
	{
		winWidth += 5;
		winHeight += 5;
		glViewport(0, 0, winWidth, winHeight);
		glutPostRedisplay();
	}
	if(key == 'Z')
	{
		winWidth -= 5;
		winHeight -= 5;
		glViewport(0, 0, winWidth, winHeight);
		glutPostRedisplay();
	}
}
void processMenuEvents(int option)
{
	switch(option)
	{
		case BARCHART: change = 1; glutPostRedisplay(); break;
		case QUIT: quit(); break;
	}
}
void createGLUTMenus()
{
	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Bar Chart", BARCHART);
	glutAddMenuEntry("Quit", QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int plot(int *data)
{
  int argc = 1;
  char *argv[1] = {(char*)"Default"};
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition (100, 100);
  glutInitWindowSize (winWidth, winHeight);
  glutCreateWindow ("HISTOGRAM");

  init(data);
	
	
  glutDisplayFunc (displayFcn);
  glutReshapeFunc (winReshapeFcn);
	createGLUTMenus();
	glutKeyboardFunc(keyboard);
  glutMainLoop ( );
}
