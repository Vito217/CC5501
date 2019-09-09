//
// Created by VictorStefano on 03-05-2019.
//

#ifndef TAREADOSMALLAS_LEPP_H
#define TAREADOSMALLAS_LEPP_H

#endif //TAREADOSMALLAS_LEPP_H

#include "Face.h"

typedef struct continfo{
    Face* f;
    int status;
}*ContInfo;

bool inCircle(Vertex *a, Vertex *b, Vertex *c, Vertex *d, double epsilon);

int orientation(Vertex *a, Vertex *b, Vertex *c, double epsilon);

bool terminalFaces(Face* f1, Face* f2);

Vertex* centroid(Vertex* a, Vertex* b, Vertex* c, Vertex* d);

Vertex* midpoint(Vertex* a, Vertex* b);

void legalizeEdge(Face* f, Vertex* vert1, Vertex* vert2, double epsilon);

void insertCentroid(std::vector<Face*> *face_list, Face *f1, Vertex *edge_v1, Vertex *edge_v2, double epsilon);

void insertMidpoint(std::vector<Face*> *face_list, Face *f, Vertex *edge_v1, Vertex *edge_v2, double epsilon);

void updateDelaunay(std::vector<Face*> *triangulation, double epsilon, double tolerance, int detail);

int contained(Face *f, Vertex *v, double epsilon);

ContInfo faceContainingVertex(std::vector<Face*> *face_list, Vertex *v, double epsilon);

void addThreeEdges(std::vector<Face*> *face_list, Face *f, Vertex *p);

void addTwoEdges(std::vector<Face*> *face_list, Face *f, Vertex *p, double epsilon);