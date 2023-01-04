#include "rvcube.h"
#include <QTimer>
#include<QDebug>

RVCube::RVCube()
    :RVBody()
    {
        VSFileName = ":/shaders/VS_simple.vsh";
        FSFileName = ":/shaders/FS_simple.fsh";
    }


void RVCube::initializeBuffer()
{

    //Définition de 4 points
    QVector3D A(0,0,1);
    QVector3D B(1,0,1);
    QVector3D C(1,1,1);
    QVector3D D(0,1,1);
    QVector3D E(0,0,0);
    QVector3D F(1,0,0);
    QVector3D G(1,1,0);
    QVector3D H(0,1,0);


    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D majenta(1, 0, 1);
    QVector3D jaune(1, 1, 0);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        C, G, H, D,
        B, F, G, C,
        A, E, F, B,
        E, H, G, F,
        A, D, H, E,
        rouge, rouge, rouge, rouge,
        bleu, bleu, bleu, bleu,
        majenta, majenta, majenta, majenta,
        jaune, jaune, jaune, jaune,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
    };

    //Initialisation du Vertex Buffer Object
    //vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    //vbo.create();
    //Lien du VBO avec le contexte de rendu OpenG
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();
}

void RVCube::initializeVAO()
{
    //Initialisation du VAO
    vao.create();
    vao.bind();
    vbo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    program.enableAttributeArray("rv_Color");

    //Libération
    vao.release();
    program.release();

}

void RVCube::draw(){

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    if (wireframe)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    program.bind();
    vao.bind();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_opacity", opacity/100);
    program.setUniformValue("u_color", globalColor/100);
    //  qInfo() << globalColor;


    vao.bind();
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    for(int i=0; i<=5 ; i=i+1)  glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);

    //glDrawArrays(GL_TRIANGLES, 0, 4);
    vao.release();
    program.release();
}

QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}
