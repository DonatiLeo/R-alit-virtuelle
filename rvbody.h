#ifndef RVBODY_H
#define RVBODY_H

#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QMatrix4x4>

#include "rvcamera.h"

class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();


    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO() = 0;

    // accesseurs et mutateurs

    RVCamera *getCamera() const;
    void setCamera(RVCamera *camera);
    QVector3D getPosition() const;
    void setPosition(const QVector3D &position);
    QQuaternion getOrientation() const;
    void setOrientation(const QQuaternion &orientation);
    void setOrientation(float yaw, float pitch, float roll);
    int getNumVertices() const;
    int getNumTriangles() const;
    int getNumIndices() const;

    void setVS(const QString &VSFileName);
    void setFS(const QString &FSFileName);
    float getOpacity() const;
    void setOpacity(int new_opacity);
    bool getWireframe() const;
    void setWireframe(bool wireframe);
    bool getCulling() const;
    void setCulling(bool culling);
    float getScale() const;
    void setScale(int scale);
    QVector3D getGlobalColor() const;
    void setGlobalColor(QVector3D newGlobalColor);

    void translate(QVector3D position); 
    void rotate(float angle, QVector3D axis);



protected:
    QString VSFileName;               //!< : nom du fichier qui contient le vertex shader
    QString FSFileName;               //!< : nom du fichier qui contient le fragment shader
    QOpenGLBuffer vbo;                //!< : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer ibo;                //!< : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject vao;     //!< : vertex array object (obligatoire)
    QOpenGLShaderProgram program;     //!< : shader program (obligatoire)

    QVector3D position;               //!< : position de l'objet dans la scène
    QQuaternion orientation;          //!< : attitude de l'objet dans la scène

    int numVertices;                  //!< : nombre de sommets de l'objet (lecture seule)
    int numTriangles;                 //!< : nombre de triangles de l'objet (lecture seule)
    int numIndices;                   //!< : nombre d'index (0 si on n'utilise pas l'ibo)

    RVCamera *camera;                 //!< : pointeur sur la caméra utilisée pour le rendu.

    float opacity;
    bool wireframe;
    bool culling;
    float scale;
    QVector3D globalColor;

};

#endif // RVBODY_H
