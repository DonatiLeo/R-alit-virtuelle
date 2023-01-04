#include "rvplane.h"

RVPlane::RVPlane() :RVBody()
    {
        FSFileName = ":/shaders/FS_plan.fsh";
        longueur = 10;
        largeur = 10;
        setGlobalColor(QVector3D(0,1,0));
    }

void RVPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_opacity", opacity/100);
    program.setUniformValue("u_color", globalColor);

    //Commande de rendu
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    vao.release();
    program.release();
}

void RVPlane::initializeBuffer()
{

    //Définition de 4 points
    QVector3D A(-longueur/2,0,-largeur/2);
    QVector3D B(longueur/2,0,-largeur/2);
    QVector3D C(longueur/2,0,largeur/2);
    QVector3D D(-longueur/2,0,largeur/2);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
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

QMatrix4x4 RVPlane::modelMatrix()
{
    QMatrix4x4 model;
   // model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVPlane::initializeVAO(){}


