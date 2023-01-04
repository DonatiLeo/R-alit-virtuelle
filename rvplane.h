#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane : public RVBody
{
    float longueur;
    float largeur;

public:
    RVPlane();
    void draw() override;

protected:
    void initializeBuffer() override;
    void initializeVAO() override;
    QMatrix4x4 modelMatrix() override;




};

#endif // RVPLANE_H
