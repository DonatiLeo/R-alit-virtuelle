#ifndef RVCAMERA_H
#define RVCAMERA_H


#include <QMatrix4x4>
#include <QVector3D>

class RVCamera
{
public:
    RVCamera();
    // virtual ~RVCamera();

    QMatrix4x4 viewMatrix();
    QMatrix4x4 projectionMatrix();

    QVector3D getPosition() const;
    void setPosition(const QVector3D &position);
    QVector3D getTarget() const;
    void setTarget(const QVector3D &target);
    QVector3D getUp() const;

    void setUp(const QVector3D &up);
    float getZMin() const;
    void setZMin(float zMin);
    float getZMax() const;
    void setZMax(float zMax);
    float getFov() const;
    void setFov(float fov);
    float getAspect() const;
    void setAspect(float aspect);
    bool getOrthogonal();
    void setOrthogonal(bool val);


protected:
    QVector3D position;
    QVector3D target;
    QVector3D up;

    float fov;
    float aspect;
    float zMin;
    float zMax;
    bool isOrthogonal;
};

#endif // RVCAMERA_H
