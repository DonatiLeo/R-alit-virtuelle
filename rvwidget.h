#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QTimer>
#include <QPoint>
#include <QMouseEvent>

#include "rvcamera.h"
#include "rvpyramid.h"
#include "rvcube.h"
#include "rvplane.h"
#include "QKeyEvent"

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    RVWidget(QWidget *parent = nullptr);

    ~RVWidget() override;

    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int w, int h) override;

public:
    void startAnimation();

private slots:
    void update();

    void changeFov(int);
    void changeOpacity(int);
    void changeWireframe();
    void changeCulling();
    void changeScale(int);
    void changeSaturation(int);
    void changeOrthogonal();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

protected:
    RVCamera *camera;         //!<    Pointeur sur la caméra à utiliser lors du rendu
    RVBody *body;           //!<    Pointeur sur l'objet 3D montré dans le widget
    RVPlane *plane;
    QTimer *timer;            //!<    Timer utilisé lors de l'animation
    float angularVelocityX;   //!<    Vitesse angulaire autour de l'axe x
    float angularVelocityY;   //!<    Vitesse angulaire autour de l'axe y
    float angularVelocityZ;   //!<    Vitesse angulaire autour de l'axe z
    QPoint oldPos;            //!<    Position du clic souris (utilisé dans mouseMove)
    bool animation;           //!<    Booléen qui dit si l'animation est activée ou pas

};
#endif // RVWIDGET_H
