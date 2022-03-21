//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.02.2019
//


#include "RenderWidget.h"
#include <glut.h>
#include <QPainter>

RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent)
{

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
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);

    //glOrtho(-2.0, 2.0, -2.0, 2.0, -100, 100);
    //gluPerspective(25.0, 1.0, 1.0, 100.0);

}


void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(3);
    
    glBegin(GL_TRIANGLES);
      glColor3f(1.0, 0.0, 0.0);   // red
      glVertex2f(100, 100);
      glColor3f(0.0, 1.0, 0.0);   // green
      glVertex2f(400, 100);
	  glColor3f(0.0, 0.0, 1.0);   // blue
      glVertex2f(250, 400);
    glEnd();

    glFlush();
}


void RenderWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

//    glViewport(0, 0, width, height);
}


