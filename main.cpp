#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include "tests.h"

int width = 800;
int height = 600;
double epsilon = 0.0;
//30 en radianes es 0.523599
double tolerance = 0.523599;
int detail = 0;
std::vector<Face*> delaunay;

void mouse(int button, int state, int x, int y) {
    if(button==GLUT_LEFT_BUTTON && GLUT_DOWN == state){
        float x1 = 2*(x /(float) glutGet(GLUT_WINDOW_WIDTH)) - 1;
        float y1 = -(2*(y /(float) glutGet(GLUT_WINDOW_HEIGHT)) - 1);
        auto v = new Vertex(x1,y1);
        ContInfo cnt = faceContainingVertex(&delaunay, v, epsilon);
        if(cnt->status==1){
            addThreeEdges(&delaunay, cnt->f, v);
        }
        else{
            addTwoEdges(&delaunay, cnt->f, v, epsilon);
        }
        free(cnt);
    }
    else if(button==GLUT_RIGHT_BUTTON && GLUT_DOWN == state){
        updateDelaunay(&delaunay, epsilon, tolerance, detail);
    }
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    for(Face* t: delaunay){
        Vertex vert1 = *(t->V1());
        Vertex vert2 = *(t->V2());
        Vertex vert3 = *(t->V3());
        glColor3f(t->C1(),t->C2(),t->C3());
        glBegin(GL_POLYGON);
        glVertex2f((float) vert1.X() , (float) vert1.Y());
        glVertex2f((float) vert2.X() , (float) vert2.Y());
        glVertex2f((float) vert3.X() , (float) vert3.Y());
        glEnd();
    }
    glutSwapBuffers();
}

int main(int argc, char** argv) {

    basic_canvas(&delaunay);
    //test1(&delaunay);
    //test2(&delaunay);
    //test3(&delaunay);
    //test4(&delaunay);
    //test5(&delaunay);

    //updateDelaunay(&delaunay, epsilon, tolerance, detail);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Triangulacion de Delaunay");
    myInit();
    glutMouseFunc(mouse);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}