//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "RenderWidget.h"
#include <QPainter>

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
  // to be implemeted later
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(600, 600);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

 //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);

  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
  
  //for (int x = 100; x < 300; ++x)
  //{
  //  painter.drawPoint(x, x);
  //}

  //myDrawLine(50, 70, 500, 370);

  drawTicks(300, 300, 200);
}


void RenderWidget::myDrawLine(float x1, float y1, float x2, float y2)
{
  QPainter painter(this);

  //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(255, 0, 0);
  painter.setPen(color);

  float m = (y2 - y1) / (x2 - x1);
  //  SetPixel(x1, y1, color);   // first point
  painter.drawPoint(x1, y1);

  if (m < 1)
  {
    float y = y1;
    for (int i = x1 + 1; i < x2; ++i)
    {
      y = y + m;
      //      SetPixel(i, round(y), color);
      painter.drawPoint(i, round(y));
    }
  }
  else     // i.e., m > 1
  {
    float mm = 1 / m;
    float x = x1;
    for (int i = y1 + 1; i < y2; ++i)
    {
      x = x + mm;
      //      SetPixel(round(x), i, color);
      painter.drawPoint(round(x), i);
    }
  }

  //  SetPixel(x2, y2, color);   // last point
  painter.drawPoint(x2, y2);
}


void RenderWidget::drawTicks(float xc, float yc, float r)
{
  QPainter painter(this);

  //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);

  float PI = 3.14159;
  
  for (int m =0; m<60; ++m)
  {
    float theta = m * 6 * PI / 180;

    float x1 = xc + r * cos(theta);
    float y1 = yc + r * sin(theta);

    float x2, y2;
    if (m % 5 == 0)
    {
      x2 = xc + r * 0.9 * cos(theta);
      y2 = yc + r * 0.9 * sin(theta);
    }
    else
    {
      x2 = xc + r * 0.95 * cos(theta);
      y2 = yc + r * 0.95 * sin(theta);
    }

    painter.drawLine(round(x1), round(y1), round(x2), round(y2));
     
  }


  

}