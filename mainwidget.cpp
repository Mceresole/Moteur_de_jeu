/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"
#include <QMouseEvent>
#include <math.h>
#include <time.h>

QList<Scene*> * MainWidget::scenes_en_cours = new QList<Scene*>();

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    murs(0),
    sol(0),
    porte(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete murs;
    delete sol;
    delete porte;
    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    if(type == 0){
        // Decrease angular speed (friction)
        angularSpeed *= 0.99;

        // Stop rotation when speed goes below threshold
        if (angularSpeed < 0.01) {
            angularSpeed = 0.0;
        } else {
               // Update rotation
                rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
            update();
        }
    }
    else{
        angle +=0.1;
        update();
    }
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *e){
    float d;
    if(e->key() == Qt::Key_Escape){
        close();
    }
    if(!pause){
        if(e->key() == Qt::Key_Space) {
            pause = true;
        }

        if(e->key() == Qt::Key_Shift){
            if(!course)
                course = true;
            else  {
                course =false;
            }
        }

        if(e->key() == Qt::Key_Z){
            if(!course)
                d = 0.1;
            else {
                d = 0.3;
            }
            int val = rotateY % 360;
            switch(val){
            case 90 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 180 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0*d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0, 0.0f, d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 270 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            default :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    printf("collision\n");
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            }
        }
        if(e->key() == Qt::Key_Left){
            rotateY +=270;
            GeometryEngine::monde->transform.addRotation(rotateY);
        }
        if(e->key() == Qt::Key_Right){
            rotateY +=90;
            GeometryEngine::monde->transform.addRotation(rotateY);
        }
        if(e->key() == Qt::Key_S){
            if(!course)
                d = 0.1;
            else {
                d = 0.3;
            }
            int val = rotateY % 360;
            switch(val){
            case 90 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 180 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 270 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            default :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            }
        }

        if(e->key() == Qt::Key_Q){
            if(!course)
                d = 0.1;
            else {
                d = 0.3;
            }
            int val = rotateY % 360;
            switch(val){
            case 90 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 180 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 270 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                }
                else{
                    if(mouvement){


                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            default :
                GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            }
        }
        if(e->key() == Qt::Key_D){
            if(!course)
                d = 0.1;
            else {
                d = 0.3;
            }
            int val = rotateY % 360;
            switch(val){
            case 90 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 180 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            case 270 :
                GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, d));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.0f, -1.0f*d));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            default :
                GeometryEngine::monde->transform.addTranslation(QVector3D(-1.0f*d, 0.0f, 0.0f));
                if(GeometryEngine::testCollision(GeometryEngine::monde)){
                    GeometryEngine::monde->transform.addTranslation(QVector3D(d, 0.0f, 0.0f));
                }
                else{
                    if(mouvement){
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, 0.01f, 0.0f));
                        mouvement = false;
                    }
                    else {
                        GeometryEngine::monde->transform.addTranslation(QVector3D(0.0f, -0.01f, 0.0f));
                        mouvement = true;
                    }
                }
                break;
            }
        }
        if(e->key() == Qt::Key_C){
            printf("%f %f %f         %f %f %f\n",GeometryEngine::monde->collideB.point1.x(), GeometryEngine::monde->collideB.point1.y(), GeometryEngine::monde->collideB.point1.z(), GeometryEngine::monde->collideB.point2.x(), GeometryEngine::monde->collideB.point2.y(), GeometryEngine::monde->collideB.point2.z());
        }
    }
    else{
        if(e->key() == Qt::Key_Space){
            pause = false;
        }
    }

    update();
    for(int i = 0; i < scenes_en_cours->size(); i++){
        scenes_en_cours->value(i)->updateScene();
    }
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

//! [2]
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]initTextures

//! [4]
void MainWidget::initTextures()
{
    // Load wall.png image
    murs = new QOpenGLTexture(QImage(":/wall.png").mirrored());

    // Set nearest filtering mode for texture minification
    murs->setMinificationFilter(QOpenGLTexture::NearestMipMapLinear);

    // Set bilinear filtering mode for texture magnification
    murs->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    murs->setWrapMode(QOpenGLTexture::Repeat);


    // Load ground.png image
    sol = new QOpenGLTexture(QImage(":/ground.png").mirrored());

    // Set nearest filtering mode for texture minification
    sol->setMinificationFilter(QOpenGLTexture::NearestMipMapLinear);

    // Set bilinear filtering mode for texture magnification
    sol->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    sol->setWrapMode(QOpenGLTexture::Repeat);

    // Load door.png image
    porte = new QOpenGLTexture(QImage(":/door.png").mirrored());

    // Set nearest filtering mode for texture minification
    porte->setMinificationFilter(QOpenGLTexture::NearestMipMapLinear);

    // Set bilinear filtering mode for texture magnification
    porte->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    porte->setWrapMode(QOpenGLTexture::Repeat);

}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = -3.0, zFar = 3.0, fov = 45.0;

    // Reset projectionif(e->key() == Qt::Key_Up){
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    murs->bind(0);
    sol->bind(1);
    porte->bind(2);

//! [6]
    QMatrix4x4 matrix;

    matrix.translate(0.0, -3.5, 0.0);



    // Set modelview-projection matrix
    program.setUniformValue("vp_matrix", projection * matrix);


    // Use texture unit 0 which contains cube.png
    program.setUniformValue("murs", 0);
    program.setUniformValue("sol", 1);
    program.setUniformValue("porte", 2);


    // Draw cube geometry
    geometries->draw(&program);
}

