#pragma once
#include "Precompiled.h"

#define ESC_KEY 27

Scene scene( 1.0f / 60.0f, 10 );
Clock g_Clock;
bool frameStepping = false;
bool canStep = false;

void Mouse( int button, int state, int x, int y )
{
	x /= 14.9;
	y /= 13.3;

  if(state == GLUT_DOWN)
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
      {
        PolygonShape poly;
        uint32 count = (uint32)Random( 3, MaxPolyVertexCount );
        Vec2 *vertices = new Vec2[count];
        real e = Random( 5, 10 );
        for(uint32 i = 0; i < count; ++i)
          vertices[i].Set( Random( -e, e ), Random( -e, e ) );
        poly.Set( vertices, count );
        Body *b = scene.Add( &poly, x, y );
        b->SetOrient( Random( -PI, PI ) );
        b->restitution = 0.2f;
        b->dynamicFriction = 0.2f;
        b->staticFriction = 0.4f;
        delete [] vertices;
      }
      break;
    case GLUT_RIGHT_BUTTON:
      {
        Circle c( Random( 1.0f, 3.0f ) );
        Body *b = scene.Add( &c, x, y );
      }
      break;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case ESC_KEY:
    exit( 0 );
    break;
  case 's':
    {
      //Circle c( 25.0f );
      //scene.Add( &c, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
      //OBB obb;
      //real e = Random( 10.0f, 35.0f );
      //obb.extents.Set( e, e );
      //Body *b = scene.Add( &obb, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
      //b->SetOrient( PI / 4.0f );
      //b->restitution = 0.2f;
      //b->dynamicFriction = 0.2f;
      //b->staticFriction = 0.4f;
    }
    break;
  case 'd':
    {
      //Circle c( 25.0f );
      //scene.Add( &c, 420, 50 );
    }
      break;
  case 'f':
    frameStepping = frameStepping ? false : true;
      break;
  case ' ':
    canStep = true;
    break;
  }
}

void PhysicsLoop( void )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  RenderString( 1, 2, "Left click to spawn a polygon" );
  RenderString( 1, 4, "Right click to spawn a circle" );

  static double accumulator = 0;

  // Different time mechanisms for Linux and Windows
#ifdef WIN32
  accumulator += g_Clock.Elapsed( );
#else
  accumulator += g_Clock.Elapsed( ) / static_cast<double>(std::chrono::duration_cast<clock_freq>(std::chrono::seconds(1)).count());
#endif

  g_Clock.Start( );

  accumulator = Clamp( 0.0f, 0.1f, accumulator );
  while(accumulator >= dt)
  {
    if(!frameStepping)
      scene.Step( );
    else
    {
      if(canStep)
      {
        scene.Step( );
        canStep = false;
      }
    }
    accumulator -= dt;
  }

  g_Clock.Stop( );

  scene.Render( );

  glutSwapBuffers( );
}

//int main(int argc, char** argv)
//{
//  glutInit(&argc, argv);
//  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
//  glutInitWindowSize( 1200, 800 );
//  glutCreateWindow( "PhyEngine" );
//  glutDisplayFunc( PhysicsLoop );
//  glutKeyboardFunc( Keyboard );
//  glutMouseFunc( Mouse );
//  glutIdleFunc( PhysicsLoop );
//
//  glMatrixMode( GL_PROJECTION );
//  //glPushMatrix( );
//  glLoadIdentity( );
//  gluOrtho2D( 0, 80, 60, 0 );
//  glMatrixMode( GL_MODELVIEW );
//  //glPushMatrix( );
//  glLoadIdentity( );
//
//  Circle c( 5.0f );
//  Body *b = scene.Add( &c, 40, 40 );
//  b->SetStatic( );
//
//  PolygonShape poly;
//  poly.SetBox( 30.0f, 1.0f );
//  b = scene.Add( &poly, 40, 55 );
//  b->SetStatic();
//  b->SetOrient(0);
//  PolygonShape poly2;
//  poly2.SetBox(1.0f, 30.0f);
//  b = scene.Add(&poly2, 4, 26);
//  b->SetStatic( );
//  b->SetOrient( -0.2 );
//  PolygonShape poly3;
//  poly3.SetBox(3.0f, 5.0f);
//  b = scene.Add(&poly3, 75.0f, 42.0f);
//  b->SetStatic();
//  b->SetOrient(0);
//
//  srand( 1 );
//  glutMainLoop( );
//
//  return 0;
//}
