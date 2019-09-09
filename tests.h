//
// Created by VictorStefano on 18-05-2019.
//

#ifndef TAREADOSMALLAS_TESTS_H
#define TAREADOSMALLAS_TESTS_H

#endif //TAREADOSMALLAS_TESTS_H

#include "lepp.h"

void basic_canvas(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-1.0, 1.0);
    auto v2 = new Vertex(1.0, 1.0);
    auto v3 = new Vertex(1.0, -1.0);
    auto v4 = new Vertex(-1.0, -1.0);
    auto f1 = new Face(v4,v2,v1);
    auto f2 = new Face(v2,v4,v3);
    f1->setN1(f2);
    f2->setN1(f1);
    triangulation->push_back(f1);
    triangulation->push_back(f2);
}

void test1(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-1.0, 1.0);
    auto v2 = new Vertex(1.0, 1.0);
    auto v3 = new Vertex(-1.0, 0.5);
    auto v4 = new Vertex(1.0, 0.5);
    auto v5 = new Vertex(-1.0, 0.0);
    auto v6 = new Vertex(1.0, 0.0);
    auto v7 = new Vertex(-1.0, -0.5);
    auto v8 = new Vertex(1.0, -0.5);
    auto v9 = new Vertex(-1.0, -1.0);
    auto v10 = new Vertex(1.0, -1.0);

    auto f1 = new Face(v3, v2, v1);
    auto f2 = new Face(v3, v4, v2);
    auto f3 = new Face(v5, v4, v3);
    auto f4 = new Face(v5, v6, v4);
    auto f5 = new Face(v7, v6, v5);
    auto f6 = new Face(v7, v8, v6);
    auto f7 = new Face(v9, v8, v7);
    auto f8 = new Face(v9, v10, v8);

    f1->setN1(f2); f1->setN2(nullptr); f1->setN3(nullptr);
    f2->setN1(f3); f2->setN2(nullptr); f2->setN3(f1);
    f3->setN1(f4); f3->setN2(f2); f3->setN3(nullptr);
    f4->setN1(f5); f4->setN2(nullptr); f4->setN3(f3);
    f5->setN1(f6); f5->setN2(f4); f5->setN3(nullptr);
    f6->setN1(f7); f6->setN2(nullptr); f6->setN3(f5);
    f7->setN1(f8); f7->setN2(f6); f7->setN3(nullptr);
    f8->setN1(nullptr); f8->setN2(nullptr); f8->setN3(f7);

    triangulation->push_back(f1);
    triangulation->push_back(f2);
    triangulation->push_back(f3);
    triangulation->push_back(f4);
    triangulation->push_back(f5);
    triangulation->push_back(f6);
    triangulation->push_back(f7);
    triangulation->push_back(f8);
}

void test2(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-1.0, -0.5);
    auto v2 = new Vertex(1.0, 0.5);
    auto v3 = new Vertex(-1.0, 0.5);
    auto v4 = new Vertex(1.0, -0.5);

    auto f1 = new Face(v1, v2, v3);
    auto f2 = new Face(v1, v4, v2);

    f1->setN1(f2); f1->setN2(nullptr); f1->setN3(nullptr);
    f2->setN1(nullptr); f2->setN2(nullptr); f2->setN3(f1);

    triangulation->push_back(f1);
    triangulation->push_back(f2);
}

void test3(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-1.0, 1.0);
    auto v2 = new Vertex(0.0, 0.0);
    auto v3 = new Vertex(0.0, 0.125);
    auto v4 = new Vertex(1.0, 1.0);
    auto v5 = new Vertex(1.0, -1.0);
    auto v6 = new Vertex(-1.0, -1.0);

    auto f1 = new Face(v1,v6,v2);
    auto f2 = new Face(v6,v5,v2);
    auto f3 = new Face(v5,v4,v2);
    auto f4 = new Face(v2,v4,v3);
    auto f5 = new Face(v4,v1,v3);
    auto f6 = new Face(v1,v2,v3);

    f1->setN1(nullptr); f1->setN2(f2); f1->setN3(f6);
    f2->setN1(nullptr); f2->setN2(f3); f2->setN3(f1);
    f3->setN1(nullptr); f3->setN2(f4); f3->setN3(f2);
    f4->setN1(f3); f4->setN2(f5); f4->setN3(f6);
    f5->setN1(nullptr); f5->setN2(f6); f5->setN3(f4);
    f6->setN1(f1); f6->setN2(f4); f6->setN3(f5);

    triangulation->push_back(f1);
    triangulation->push_back(f2);
    triangulation->push_back(f3);
    triangulation->push_back(f4);
    triangulation->push_back(f5);
    triangulation->push_back(f6);
}

void test4(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-0.8, 0.8);
    auto v2 = new Vertex(-0.75,0.6);
    auto v3 = new Vertex(0.8, 0.8);
    auto v4 = new Vertex(0.6, 0.4);
    auto v5 = new Vertex(-0.6, 0.3);
    auto v6 = new Vertex(-0.9, 0.1);
    auto v7 = new Vertex(0.7, -0.2);
    auto v8 = new Vertex(-0.3, -0.5);
    auto v9 = new Vertex(0.4, -0.8);

    auto f1 = new Face(v1,v2,v3);
    auto f2 = new Face(v2,v4,v3);
    auto f3 = new Face(v5,v4,v2);
    auto f4 = new Face(v6,v4,v5);
    auto f5 = new Face(v6,v7,v4);
    auto f6 = new Face(v8,v7,v6);
    auto f7 = new Face(v9,v7,v8);

    f1->setN2(f2);
    f2->setN1(f3); f2->setN3(f1);
    f3->setN1(f4); f3->setN2(f2);
    f4->setN1(f5); f4->setN2(f3);
    f5->setN1(f6); f5->setN3(f4);
    f6->setN1(f7); f6->setN2(f5);
    f7->setN2(f6);

    triangulation->push_back(f1);
    triangulation->push_back(f2);
    triangulation->push_back(f3);
    triangulation->push_back(f4);
    triangulation->push_back(f5);
    triangulation->push_back(f6);
    triangulation->push_back(f7);
}

void test5(std::vector<Face*> *triangulation){
    auto v1 = new Vertex(-0.8, 0.0);
    auto v2 = new Vertex( 0.8,0.0);
    auto v3 = new Vertex(-0.7, 0.2);

    auto f1 = new Face(v1,v2,v3);

    triangulation->push_back(f1);
}