QT       += core gui widgets opengl core5compat openglwidgets

TARGET = Moteur_de_jeu
TEMPLATE = app

SOURCES += main.cpp \
    colliderbox.cpp \
    collidermesh.cpp \
    gameobject.cpp \
    mesh.cpp \
    transform.cpp \
    scene.cpp \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    colliderbox.h \
    collidermesh.h \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    transform.h \
    scene.h

RESOURCES += \
    maillages.qrc \
    objects.qrc \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    scene/corridor.obj \
    scene/corridor.off \
    scene/corridor_back.off \
    scene/corridor_ground.off \
    scene/corridor_left.off \
    scene/corridor_right.off \
    scene/corridor_s.obj \
    scene/corridor_s.off \
    scene/corridor_top.off \
    scene/scene.txt \
    scene/sphere.off
