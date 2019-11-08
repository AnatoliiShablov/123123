#include <string.h>
#include "GL/glut.h"
#include "glui.h"

int   wireframe = 0;
int   segments = 8;
int   main_window;

void myGlutIdle()
{
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  glutPostRedisplay();
}


void myGlutReshape( int x, int y )
{
  float xy_aspect;

  xy_aspect = (float)x / (float)y;
  glViewport( 0, 0, x, y );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -xy_aspect*.08, xy_aspect*.08, -.08, .08, .1, 15.0 );

  glutPostRedisplay();
}

void myGlutDisplay()
{
  static float rotationX = 0.0, rotationY = 0.0;

  glClearColor( .9f, .9f, .9f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  rotationX += 3.3f;
  rotationY += 4.7f;

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0.0, 0.0, -1.0 );
  glRotatef( rotationY, 0.0, 1.0, 0.0 );
  glRotatef( rotationX, 1.0, 0.0, 0.0 );

  if ( wireframe )
    glutWireTorus( .2,.5,16,segments );
  else
    glutSolidTorus( .2,.5,16,segments );

  glutSwapBuffers();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 300, 300 );

  main_window = glutCreateWindow( "GLUI Example 1" );
  glutDisplayFunc( myGlutDisplay );
  glutReshapeFunc( myGlutReshape );

  GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
  GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
  GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_DEPTH_TEST);

  GLUI *glui = GLUI_Master.create_glui( "GLUI" );
  new GLUI_Checkbox( glui, "Wireframe", &wireframe );
  (new GLUI_Spinner( glui, "Segments:", &segments ))
    ->set_int_limits( 3, 60 );

  glui->set_main_gfx_window( main_window );

  GLUI_Master.set_glutIdleFunc( myGlutIdle );

  glutMainLoop();

  return EXIT_SUCCESS;
}
