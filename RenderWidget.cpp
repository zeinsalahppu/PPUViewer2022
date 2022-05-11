//
// Copyright 2022 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academic use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 10.05.2022
//


#include "RenderWidget.h"
#include <glut.h>
#include <QPainter>
#include <iostream>


RenderWidget::RenderWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  m_ViewPoint.x = 5.0;
  m_ViewPoint.y = 5.0;
  m_ViewPoint.z = 5.0;
}


RenderWidget::~RenderWidget()
{

}


QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}


QSize RenderWidget::sizeHint() const
{
  return QSize(600, 600);
}


void RenderWidget::initializeGL()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(15.0, 1.0, 1.0, 100.0);

  GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z,      /* view point */
            0.0, 0.0, 0.0,      /* ref point */
            0.0, 1.0, 0.0);     /* up direction is positive y-axis */

  drawCube();
}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //  glViewport(0, 0, width, height);
}


void RenderWidget::zoomIn()
{
  std::cout << "Zooming In..\n";

  m_ViewPoint.x *= 0.95;
  m_ViewPoint.y *= 0.95;
  m_ViewPoint.z *= 0.95;

  update();
}


void RenderWidget::zoomOut()
{
  std::cout << "Zooming Out..\n";

  m_ViewPoint.x /= 0.95;
  m_ViewPoint.y /= 0.95;
  m_ViewPoint.z /= 0.95;

  update();
}


void RenderWidget::rotateAboutY()
{
  double angle = 3.0 / 180 * M_PI;

  std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.x * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.z = newz;

  update();
}


void RenderWidget::normalize(GLfloat vec[3])
{
  double epsilon = 1e-6;
  double n = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

  if (n >= epsilon)
  {
    for (int i = 0; i < 3; ++i)
      vec[i] /= n;
  }
}


void RenderWidget::drawCube(void)
{
  GLfloat cubeCorner[8][3];

  cubeCorner[0][0] = -0.5;  cubeCorner[0][1] = -0.5;  cubeCorner[0][2] = -0.5;
  cubeCorner[1][0] = 0.5;   cubeCorner[1][1] = -0.5;  cubeCorner[1][2] = -0.5;
  cubeCorner[2][0] = 0.5;   cubeCorner[2][1] = 0.5;   cubeCorner[2][2] = -0.5;
  cubeCorner[3][0] = -0.5;  cubeCorner[3][1] = 0.5;   cubeCorner[3][2] = -0.5;
  cubeCorner[4][0] = -0.5;  cubeCorner[4][1] = -0.5;  cubeCorner[4][2] = 0.5;
  cubeCorner[5][0] = 0.5;   cubeCorner[5][1] = -0.5;  cubeCorner[5][2] = 0.5;
  cubeCorner[6][0] = 0.5;   cubeCorner[6][1] = 0.5;   cubeCorner[6][2] = 0.5;
  cubeCorner[7][0] = -0.5;  cubeCorner[7][1] = 0.5;   cubeCorner[7][2] = 0.5;

  for (int i = 0; i < 8; ++i)
    normalize(cubeCorner[i]);

  GLfloat mat_ambient[] = { 0.33, 0.22, 0.03, 1.0 };
  GLfloat mat_diffuse[] = { 0.78, 0.57, 0.11, 1.0 };
  GLfloat mat_specular[] = { 0.99, 0.94, 0.81, 1.0 };
  GLfloat mat_shininess[] = { 28.0 };

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);
  glBegin(GL_QUADS);

  glColor3f(0.0, 0.0, 0.0);   // blue
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(1.0, 1.0, 0.0);  // yellow
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 1.0);
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);

  glColor3f(1.0, 0.0, 0.0);   // red
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);

  glColor3f(1.0, 0.0, 1.0);
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 0.0);   // green
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}