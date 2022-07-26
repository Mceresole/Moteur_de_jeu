#include "scene.h"
#include "mainwidget.h"

Scene::~Scene() { }

Scene::Scene(QString name) {

    this->name = name;
}

Scene::Scene(QVector3D v1, Scene * s1, int type_scene, QVector3D translation, float angle) {

    passage1 = v1;

    previous = s1;

    //scene 4
    GameObject * o;

    this->angle = angle;
    this->translation = translation;
    this->type_scene = type_scene;

    objectList = new QList<GameObject*>();


    //char back[] = {'.','.','/','M','o','t','e','u','r','_','d','e','_','j','e','u','/','b','a','c','k','.','o','f','f'};
    //char * back = (char*)malloc(sizeof(char) * 26);
    //back = "../Moteur_de_jeu/back.off";
    char* back;
    std::string str_back("../Moteur_de_jeu/back.off");
    back = &str_back[0];

    //char wall1[] = {'.','.','/','M','o','t','e','u','r','_','d','e','_','j','e','u','/','w','a','l','l','1','.','o','f','f'};
    char* wall1;
    std::string str_wall1("../Moteur_de_jeu/wall1.off");
    wall1 = &str_wall1[0];

    //char wall2[] = {'.','.','/','M','o','t','e','u','r','_','d','e','_','j','e','u','/','w','a','l','l','2','.','o','f','f'};
    char* wall2;
    std::string str_wall2("../Moteur_de_jeu/wall2.off");
    wall2 = &str_wall2[0];

    //char floor1[] = {'.','.','/','M','o','t','e','u','r','_','d','e','_','j','e','u','/','f','l','o','o','r','1','.','o','f','f'};
    char* floor1;
    std::string str_floor1("../Moteur_de_jeu/floor1.off");
    floor1 = &str_floor1[0];

    //char floor2[] = {'.','.','/','M','o','t','e','u','r','_','d','e','_','j','e','u','/','f','l','o','o','r','2','.','o','f','f'};
    char* floor2;
    std::string str_floor2("../Moteur_de_jeu/floor1.off");
    floor2 = &str_floor2[0];

    Mesh meshBack = Mesh();
    meshBack = GeometryEngine::loadOffSimple(back);
    Mesh meshWall1 = GeometryEngine::loadOffSimple(wall1);
    Mesh meshWall2 = GeometryEngine::loadOffSimple(wall2);
    Mesh meshFloor1 = GeometryEngine::loadOffSimple(floor1);
    Mesh meshFloor2 = GeometryEngine::loadOffSimple(floor2);

    switch(type_scene) {

    case 1:
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,-20.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,6.0f,0.0f) + translation), 1.0f), true));
        next = NULL;
        passage2 = QVector3D(0.0,0.0,-19.0)+translation;
        break;

    case 2:
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-12.0f+translation.z()+4.0f,0.0f,-18.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 0 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-20.0f+translation.z()+4.0f,0.0f,4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-12.0f+translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,6.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-20.0f+translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-20.0f+translation.z()+4.0f,6.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        next = NULL;
        passage2 = QVector3D(15.0f,0.0f,-24.0f)+translation;
        break;

    case 3:
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(12.0f-translation.z()+4.0f,0.0f,-16.0f-translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(20.0f-translation.z()+4.0f,0.0f,4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(wall2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(12.0f-translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor1), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,6.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(12.0f-translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(floor2), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(12.0f-translation.z()+4.0f,6.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, GeometryEngine::loadOffSimple(back), Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        next = NULL;
        passage2 = QVector3D(-11.0f,0.0f,-24.0f)+translation;
        break;

    case 4:
        addGameObject(new GameObject(GeometryEngine::monde, meshBack, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f)), 1.0f), true));

        addGameObject(new GameObject(GeometryEngine::monde, meshWall1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshWall1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(8.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,0.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,6.0f,0.0f) + translation), 1.0f), true));

        addGameObject(new GameObject(GeometryEngine::monde, meshFloor1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,-20.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,6.0f,-20.0f) + translation), 1.0f), true));

        addGameObject(new GameObject(GeometryEngine::monde, meshWall2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 0 + angle), (QVector3D(8.0f,0.0f,-20.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshWall1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-40.0f+translation.z()+4.0f,0.0f,4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshWall2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-32.0f+translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-40.0f+translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-40.0f+translation.z()+4.0f,6.0f,-4.0f+translation.x())), 1.0f), true));

        addGameObject(new GameObject(GeometryEngine::monde, meshWall2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 00 + angle), (QVector3D(0.0f,0.0f,-20.0f) + translation), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshWall1, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(40.0f-translation.z()+4.0f,0.0f,4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshWall2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(32.0f-translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(32.0f-translation.z()+4.0f,0.0f,-4.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshFloor2, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(32.0f-translation.z()+4.0f,6.0f,-4.0f+translation.x())), 1.0f), true));

        addGameObject(new GameObject(GeometryEngine::monde, meshBack, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90 + angle), (QVector3D(32.0f-translation.z()+4.0f,0.0f,-16.0f+translation.x())), 1.0f), true));
        addGameObject(new GameObject(GeometryEngine::monde, meshBack, Transform(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), -90 + angle), (QVector3D(-40.0f+translation.z()+4.0f,0.0f,-16.0f+translation.x())), 1.0f), true));

        o = new GameObject(GeometryEngine::monde, GeometryEngine::loadOff("../Moteur_de_jeu/octopus_toon.off"), Transform(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f),-90 + angle), (QVector3D(0.0f,39.0f,0.0f)), 1.0f), true);
        o->mesh.TextN = 4;
        addGameObject(o);

        next = NULL;
        passage2 = QVector3D(0.0,0.0,-19.0)+translation;
        break;
    default:

        break;
    }
}

void Scene::addGameObject(GameObject* object) {
    objectList->push_back(object);
}

void Scene::deleteGameObject(GameObject* object) {
    objectList->removeOne(object);
}


void Scene::updateScene() {

    QMatrix4x4 mat = QMatrix4x4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0);
    Transform t = GeometryEngine::monde->transform;

    t.transform(&mat);

    if(step == 1) {

        if(previous == NULL) {

            step = 2;
            int i = rand()%3 + 1;

            switch(type_scene) {

            case 1 :
                next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(0.0f,0.0f,-20.0f)+translation, this, i, QVector3D(0.0f,0.0f,-20.0f)+translation, 0);
                break;

            case 2:
                next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(-12.0f+translation.z()+4.0f,0.0f,-18.0f+translation.x()), this, i, QVector3D(-12.0f+translation.z()+4.0f,0.0f,-18.0f+translation.x()), -90+angle);
                break;

            case 3:
                next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(12.0f-translation.z()+4.0f,0.0f,-16.0f-translation.x()), this, i, QVector3D(12.0f-translation.z()+4.0f,0.0f,-16.0f-translation.x()), 90+angle);
                break;

            default:
                break;
            }
        }

        else {

            QVector4D v1 = QVector4D(passage1, 1.0) * mat;
            QVector3D v = QVector3D(v1.x(), v1.y(), v1.z());

            if((v.x() >= -0.5 && v.x() <= 0.5) && (v.z() >= -0.5 && v.z() <= 0.5)) { //si le point de passage1 est à notre niveau

                //animation des portes
                previous->unloadScene();
                step = 2;
                int i = rand()%3 + 1;

                switch(type_scene) {

                case 1 :
                    next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(0.0f,0.0f,-20.0f)+translation, this, i, QVector3D(0.0f,0.0f,-20.0f)+translation, angle);
                    break;

                case 2:
                    next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(-12.0f+translation.z()+4.0f,0.0f,-18.0f+translation.x()), this, i, QVector3D(-12.0f+translation.z()+4.0f,0.0f,-18.0f+translation.x()), -90+angle);
                    break;

                case 3:
                    next = new Scene(QVector3D(0.0,0.0,-3.0)+QVector3D(12.0f-translation.z()+4.0f,0.0f,-16.0f-translation.x()), this, i, QVector3D(12.0f-translation.z()+4.0f,0.0f,-16.0f-translation.x()), 90+angle);
                    break;

                default:
                    break;
                }
            }
        }
    }

    else {

        if(step == 2) {

            QVector3D v = passage2 * mat;

            if((v.x() >= -0.5 && v.x() <= 0.5) && (v.z() >= -0.5 && v.z() <= 0.5)) { //si le point de passage2 est à notre niveau, go

                //next->loadScene();
                step = 3;
            }
        }
    }
}

void Scene::loadScene() {

    for(int i = 0; i < objectList->size(); i++) {

        GeometryEngine::monde->addEnfant(objectList->value(i));

        objectList->value(i)->arrayBuf.create();
        objectList->value(i)->indexBuf.create();

        objectList->value(i)->arrayBuf.bind();
        objectList->value(i)->arrayBuf.allocate(objectList->value(i)->mesh.vertices, objectList->value(i)->mesh.vertexNumber * sizeof(VertexData));

        objectList->value(i)->indexBuf.bind();
        objectList->value(i)->indexBuf.allocate(objectList->value(i)->mesh.indices,  objectList->value(i)->mesh.indexCount* sizeof(GLushort));
    }

    MainWidget::scenes_en_cours->push_back(this);
}

void Scene::unloadScene() {

    for(int i = 0; i < objectList->size(); i++) {

        GeometryEngine::monde->child->removeOne(objectList->value(i));
    }

    MainWidget::scenes_en_cours->removeOne(this);
}


