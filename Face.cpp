//
// Created by VictorStefano on 04-05-2019.
//

#include "Face.h"
#include <math.h>
#include <cmath>
#define PI 3.14159265

// FACE (TRIANGLE) CONSTRUCTOR AND FUNCTIONS
Face::Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3) {
    v1 = vertex1;
    v2 = vertex2;
    v3 = vertex3;
    n1 = nullptr;
    n2 = nullptr;
    n3 = nullptr;
    c1 = ((float) rand() / (RAND_MAX));
    c2 = ((float) rand() / (RAND_MAX));
    c3 = ((float) rand() / (RAND_MAX));
    computeMaxEdges();
    computeMinAngle();
}

Face::Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3, Face *face1, Face *face2, Face *face3) {
    v1 = vertex1;
    v2 = vertex2;
    v3 = vertex3;
    n1 = face1;
    n2 = face2;
    n3 = face3;
    c1 = ((float) rand() / (RAND_MAX));
    c2 = ((float) rand() / (RAND_MAX));
    c3 = ((float) rand() / (RAND_MAX));
    computeMaxEdges();
    computeMinAngle();
}

Face::~Face() = default;
Vertex*  Face::V1() {return v1;}
Vertex*  Face::V2() {return v2;}
Vertex*  Face::V3() {return v3;}
Face*    Face::N1() {return n1;}
Face*    Face::N2() {return n2;}
Face*    Face::N3() {return n3;}
float    Face::C1() {return c1;}
float    Face::C2() {return c2;}
float    Face::C3() {return c3;}
Vertex** Face::ME_V1() {return max_edge_v1;}
Vertex** Face::ME_V2() {return max_edge_v2;}
Face**   Face::ME_N()  {return max_edge_n;}
Vertex** Face::SME_V1() {return sec_max_edge_v1;}
Vertex** Face::SME_V2() {return sec_max_edge_v2;}
Face**   Face::SME_N()  {return sec_max_edge_n;}
double   Face::MA() {return min_angle;}
void     Face::updateMEs() {computeMaxEdges();}
void     Face::updateMA() {computeMinAngle();}
void     Face::setV1(Vertex* v) {v1 = v;}
void     Face::setV2(Vertex* v) {v2 = v;}
void     Face::setV3(Vertex* v) {v3 = v;}
void     Face::setN1(Face* f) {n1 = f;}
void     Face::setN2(Face* f) {n2 = f;}
void     Face::setN3(Face* f) {n3 = f;}

std::ostream& operator<<(std::ostream& out, Face& f){
    out << "[" << *(f.V1()) << "," << *(f.V2()) << "," << *(f.V3()) << "]";
    return out;
}

void Face::computeMaxEdges() {
    double d1 = sqrt(pow(v2->X()-v1->X(), 2.0)+pow(v2->Y()-v1->Y(), 2.0));
    double d2 = sqrt(pow(v3->X()-v2->X(), 2.0)+pow(v3->Y()-v2->Y(), 2.0));
    double d3 = sqrt(pow(v1->X()-v3->X(), 2.0)+pow(v1->Y()-v3->Y(), 2.0));
    double max, second_max;
    if(d1<d2){
        if(d2<d3){
            second_max = d2;
            max = d3;
        }
        else{
            if(d1<d3){
                second_max = d3;
                max = d2;
            }
            else{
                second_max = d1;
                max = d2;
            }
        }
    }
    else{
        if(d1<d3){
            second_max = d1;
            max = d3;
        }
        else{
            if(d2<d3){
                second_max = d3;
                max = d1;
            }
            else{
                second_max = d2;
                max = d1;
            }
        }
    }

    if(max==d1) {
        max_edge_v1 = &v1;
        max_edge_v2 = &v2;
        max_edge_n  = &n1;
    }
    else if(max==d2) {
        max_edge_v1 = &v2;
        max_edge_v2 = &v3;
        max_edge_n  = &n2;
    }
    else{
        max_edge_v1 = &v3;
        max_edge_v2 = &v1;
        max_edge_n  = &n3;
    }

    if(second_max==d1) {
        sec_max_edge_v1 = &v1;
        sec_max_edge_v2 = &v2;
        sec_max_edge_n = &n1;
    }
    else if(second_max==d2) {
        sec_max_edge_v1 = &v2;
        sec_max_edge_v2 = &v3;
        sec_max_edge_n = &n2;
    }
    else{
        sec_max_edge_v1 = &v3;
        sec_max_edge_v2 = &v1;
        sec_max_edge_n = &n3;
    }
}

void Face::computeMinAngle() {
    double scalar12 = (v2->X()-v1->X())*(v3->X()-v2->X()) + (v2->Y()-v1->Y())*(v3->Y()-v2->Y());
    double scalar23 = (v3->X()-v2->X())*(v1->X()-v3->X()) + (v3->Y()-v2->Y())*(v1->Y()-v3->Y());
    double scalar31 = (v1->X()-v3->X())*(v2->X()-v1->X()) + (v1->Y()-v3->Y())*(v2->Y()-v1->Y());
    double d1 = sqrt(pow(v2->X()-v1->X(),2.0)+pow(v2->Y()-v1->Y(), 2.0));
    double d2 = sqrt(pow(v3->X()-v2->X(),2.0)+pow(v3->Y()-v2->Y(), 2.0));
    double d3 = sqrt(pow(v1->X()-v3->X(),2.0)+pow(v1->Y()-v3->Y(), 2.0));
    double a1 = PI - acos(scalar12/(d1*d2));
    double a2 = PI - acos(scalar23/(d2*d3));
    double a3 = PI - acos(scalar31/(d3*d1));
    double min = std::min(a1,std::min(a2,a3));
    min_angle = min;
}