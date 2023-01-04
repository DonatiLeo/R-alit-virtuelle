#include "rvbody.h"

RVBody::RVBody()
    :QOpenGLFunctions(),
      vao(), program(),
      position(), orientation()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo.create();
    ibo.create();
    vao.create();
    program.create();

    numVertices = 0;
    numTriangles = 0;
    numIndices = 0;

    VSFileName = ":/shaders/VS_simpler.vsh";
    FSFileName = ":/shaders/FS_simple.fsh";

    opacity = 100;
    wireframe = false;
    culling = true;
    scale = 100;
    globalColor= QVector3D(100,100,100);

}

RVBody::~RVBody()
{
    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    vao.destroy();
    ibo.destroy();
    vbo.destroy();
}

void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();
    initializeVAO();

}

void RVBody::initializeVAO()
{
    //Initialisation du VAO
    vao.create();
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    //Libération
    vao.release();
    program.release();
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(position);
    model.rotate(orientation);
    model.scale(scale/100);
    return model;
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    bool resultat;

    program.bind();
    //Vertex Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Vertex, VSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Fragment, FSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    program.release();
}

void RVBody::rotate(float angle, QVector3D axis)
{
    orientation =  QQuaternion::fromAxisAndAngle(axis, angle) * orientation ;
}

void RVBody::translate(QVector3D position)
{
    this->position += position;
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

//-------------------------- Accesseurs et Mutateurs ---------------------------
//

int RVBody::getNumVertices() const
{
    return numVertices;
}

int RVBody::getNumTriangles() const
{
    return numTriangles;
}

int RVBody::getNumIndices() const
{
    return numIndices;
}

void RVBody::setFS(const QString &newFSFileName)
{
    FSFileName = newFSFileName;
}

void RVBody::setVS(const QString &newVSFileName)
{
    VSFileName = newVSFileName;
}

RVCamera *RVBody::getCamera() const
{
    return camera;
}

void RVBody::setCamera(RVCamera *camera)
{
    camera = camera;
}

QVector3D RVBody::getPosition() const
{
    return position;
}

void RVBody::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}


QQuaternion RVBody::getOrientation() const
{
    return orientation;
}

void RVBody::setOrientation(const QQuaternion &neworientation)
{
    orientation = neworientation;
}

float RVBody::getOpacity() const {
    return opacity;
}

void RVBody::setOpacity(int new_opacity){
    opacity = new_opacity;
}

bool RVBody::getWireframe() const{
    return wireframe;
}

void RVBody::setWireframe(bool wireframe){
    wireframe = wireframe;
}

bool RVBody::getCulling() const{
    return culling;
}

void RVBody::setCulling(bool culling){
    culling = culling;
}

void RVBody::setScale(int scale){
    scale = scale;
}

float RVBody::getScale() const{
    return scale;
}

QVector3D RVBody::getGlobalColor() const{
    return globalColor;
}

void RVBody::setGlobalColor(QVector3D newGlobalColor){
    globalColor = newGlobalColor;
}
//------------------------------------------------------------------------------
