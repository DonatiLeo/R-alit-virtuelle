#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    grabKeyboard();
    angularVelocityX = 0;
    angularVelocityY = 3;
    angularVelocityZ = 0;
    timer = new QTimer(this);
    animation = false;
}

RVWidget::~RVWidget()
{
    delete timer;
    delete camera;
    delete body;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //glDisable(GL_CULL_FACE);

    camera = new RVCamera();
    camera -> setPosition(QVector3D(0, 7, 3));
    camera -> setTarget(QVector3D(0, 0, 0));
    camera -> setZMin(3);
    camera -> setZMax(20);

    body = new RVCube();
    plane = new RVPlane();

    body->setCamera(camera);
    body->setPosition(QVector3D(0, 0, -1));
    body->initialize();

    plane->setCamera(camera);
    plane->setPosition(QVector3D(0,0,0));
    plane->initialize();

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = -10; i<10 ; i=i+2){
        for(int j = -10; j<10; j=j+2){
            body->setPosition(QVector3D(i, 0, j));
            body->draw();
        }
    }
   // body->draw();
    //body->setPosition(QVector3D(2,0,1));
    //body->draw();
    //body->setPosition(QVector3D(-2,0,1));
    //body->draw();
    plane->draw();

}

void RVWidget::resizeGL(int w, int h)
{
    //Pour tenir compte du changement de format du widget
    float aspect = float(w)/h;
    camera->setAspect(aspect);
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::update()
{
    if (animation) {
        float angularVelocity = 3.0f;
        body->rotate(angularVelocity, QVector3D(0, 1, 0));
    }
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    animation = ! animation;
    this->update();
}

void RVWidget::changeFov(int newFov)
{
    camera->setFov(newFov);
    this->update();
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = float(event->x() - oldPos.x()) / width();
    float dy = float(event->y() - oldPos.y()) / height();
    float angleX = 180 * dy;
    float angleY = 180 * dx;
    body->rotate(angleX, QVector3D(1, 0, 0));
    body->rotate(angleY, QVector3D(0, 1, 0));
    oldPos = event->pos();

    QOpenGLWidget::update();
}

void RVWidget::changeOpacity(int newOpacity)
{
   body -> setOpacity(newOpacity);
   this->update();
}

void RVWidget::changeWireframe()
{
    body->setWireframe(!(body->getWireframe()));
    this->update();
}

void RVWidget::changeCulling()
{
    body->setCulling(!(body->getCulling()));
    this->update();
}

void RVWidget::changeScale(int newScale)
{
    plane->setScale(newScale);
    this->update();
}

void RVWidget::changeSaturation(int newSaturation)
{
    body->setGlobalColor(QVector3D(newSaturation,newSaturation,newSaturation));
    this->update();
}

void RVWidget::changeOrthogonal(){
    camera->setOrthogonal(!(camera->getOrthogonal()));
    this->update();
}

void RVWidget::keyPressEvent(QKeyEvent* event){
    QVector3D actual_pos = camera->getPosition();

    if(event->key()== Qt::Key_Left){
        actual_pos.setX(actual_pos.x()-1);
        camera->setPosition(actual_pos);
        this->update();
    }
    if(event->key()== Qt::Key_Right){
        actual_pos.setX(actual_pos.x()+1);
        camera->setPosition(actual_pos);
        this->update();
    }
    if(event->key()== Qt::Key_Down){
        actual_pos.setY(actual_pos.y()-1);
        camera->setPosition(actual_pos);
        this->update();
    }
    if(event->key()== Qt::Key_Up){
        actual_pos.setY(actual_pos.y()+1);
        camera->setPosition(actual_pos);
        this->update();
    }


}


