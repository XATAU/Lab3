#include <QtGui>
#include <math.h>

#include "glwidget.h"
#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    fig=0;
    xRot=-45; yRot=0; zRot=-45; zTra=0; nSca=1;
    scx=0;
    scy=0;

}

void GLWidget::initializeGL(){


   glClearColor(0,0,0,1);/*цвет области рисования */
   GLfloat light_col[] = {1,1,1};
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);


}
void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(nSca, nSca, nSca);
    glTranslatef(0.0f, zTra, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    drawAxis();

    drawTel();


}
void GLWidget::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}


void GLWidget::setFigure(int input)
{
    fig = input;

}

void GLWidget::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* pe)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}

void GLWidget::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3d( 1.0f,  0.0f,  0.0f);
      glVertex3d(-1.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      glVertex3d( 0.0f,  1.0f,  0.0f);
      glVertex3d( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3d( 0.0f,  0.0f,  1.0f);
      glVertex3d( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void GLWidget::drawTel()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.5f,0.0f);
    glVertex3f( 0.3f, 0.5f,-0.1f);          // Право верх квадрата (Верх)
    glVertex3f(-0.3f, 0.5f,-0.1f);          // Лево верх
    glVertex3f(-0.3f, 0.5f, 0.1f);          // Лево низ
    glVertex3f( 0.3f, 0.5f, 0.1f);          // Право низ
    glColor3f(0.5f,0.25f,0.0f);
    glVertex3f( 0.3f,-0.5f, 0.1f);          // Верх право квадрата (Низ)
    glVertex3f(-0.3f,-0.5f, 0.1f);          // Верх лево
    glVertex3f(-0.3f,-0.5f,-0.1f);          // Низ лево
    glVertex3f( 0.3f,-0.5f,-0.1f);          // Низ право
    glColor3f(0.5f,0.0f,0.0f);
    glVertex3f( 0.3f, 0.5f, 0.1f);          // Верх право квадрата (Перед)
    glVertex3f(-0.3f, 0.5f, 0.1f);          // Верх лево
    glVertex3f(-0.3f,-0.5f, 0.1f);          // Низ лево
    glVertex3f( 0.3f,-0.5f, 0.1f);          // Низ право
    glColor3f(0.5f,0.5f,0.0f);
    glVertex3f( 0.3f,-0.5f,-0.1f);          // Верх право квадрата (Зад)
    glVertex3f(-0.3f,-0.5f,-0.1f);          // Верх лево
    glVertex3f(-0.3f, 0.5f,-0.1f);          // Низ лево
    glVertex3f( 0.3f, 0.5f,-0.1f);          // Низ право
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(-0.3f, 0.5f, 0.1f);          // Верх право квадрата (Лево)
    glVertex3f(-0.3f, 0.5f,-0.1f);          // Верх лево
    glVertex3f(-0.3f,-0.5f,-0.1f);          // Низ лево
    glVertex3f(-0.3f,-0.5f, 0.1f);          // Низ право
    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f( 0.3f, 0.5f,-0.1f);          // Верх право квадрата (Право)
    glVertex3f( 0.3f, 0.5f, 0.1f);          // Верх лево
    glVertex3f( 0.3f,-0.5f, 0.1f);          // Низ лево
    glVertex3f( 0.3f,-0.5f,-0.1f);          // Низ право
    glEnd();
}
