//
// Created by VictorStefano on 03-05-2019.
//

#include "lepp.h"
#include <math.h>
#include <string>
#include <stdexcept>

bool inCircle(Vertex *a, Vertex *b, Vertex *c, Vertex *d, double epsilon){

    double ax=a->X(), ay=a->Y(),
           bx=b->X(), by=b->Y(),
           cx=c->X(), cy=c->Y(),
           dx=d->X(), dy=d->Y();

    double ix=ax-dx, iy=ay-dy, iz=pow(ix,2.0)+pow(iy, 2.0),
           jx=bx-dx, jy=by-dy, jz=pow(jx,2.0)+pow(jy, 2.0),
           kx=cx-dx, ky=cy-dy, kz=pow(kx,2.0)+pow(ky, 2.0);

    double det = ix*(jy*kz-ky*jz)-iy*(jx*kz-kx*jz)+iz*(jx*ky-kx*jy);

    return det > epsilon;
}

int orientation(Vertex *a, Vertex *b, Vertex *c, double epsilon){

    double bx_origin = b->X() - a->X();
    double by_origin = b->Y() - a->Y();
    double cx_origin = c->X() - b->X();
    double cy_origin = c->Y() - b->Y();

    double cross = bx_origin*cy_origin - cx_origin*by_origin;

    if (cross>epsilon)
        {return 1;}
    else if ((epsilon>cross && cross>-epsilon) || cross == 0)
        {return 0;}
    else
        {return -1;}
}

bool terminalFaces(Face* f1, Face* f2){
    if(f2== nullptr){

        //-----------------------------------------------------------------------
        std::cout << "f2 is null. Then, "<< *f1 <<" is terminal \n" << std::endl;
        //-----------------------------------------------------------------------

        return true;
    }

    //----------------------------------------------------------------------------------
    std::cout << "Checking if "<< *f1 <<" and "<< *f2 <<" are terminal.\n" << std::endl;
    //----------------------------------------------------------------------------------

    return *(f1->ME_V1()) == *(f2->ME_V2()) && *(f1->ME_V2()) == *(f2->ME_V1());
}

Vertex* centroid(Vertex* a, Vertex* b, Vertex* c, Vertex* d){

    double x = (a->X() + b->X() + c->X() + d->X())*0.25;
    double y = (a->Y() + b->Y() + c->Y() + d->Y())*0.25;

    auto v = new Vertex(x,y);

    //----------------------------------------------------
    std::cout << "Centroid is "<< *v <<" \n" << std::endl;
    //----------------------------------------------------

    return v;
}

Vertex* midpoint(Vertex* a, Vertex* b){

    double x = (a->X() + b->X())*0.5;
    double y = (a->Y() + b->Y())*0.5;

    auto v = new Vertex(x,y);

    //----------------------------------------------------
    std::cout << "Midpoint is "<< *v <<" \n" << std::endl;
    //----------------------------------------------------

    return v;
}

void legalizeEdge(Face* f, Vertex* vert1, Vertex* vert2, double epsilon){

    //--------------------------------------------------------------
    std::cout << "LEGALIZING EDGES FROM "<< *f <<" \n" << std::endl;
    //--------------------------------------------------------------

    //  * * * * * *v3 * * * * * *           * * * * * *v3 * * * * * *
    //  *         *   *         *           *         * * *         *
    //  *  no   *       *   ne  *           *  no   *   *   *   ne  *
    //  *     *     f     *     *           *     *     *     *     *
    //  *   *               *   *           *   *       *       *   *
    //  * *                   * *           * *         *         * *
    //  v1* * * * * * * * * * *v2   --->    v1    n     *    f     v2
    //  * *                   * *           * *         *         * *
    //  *   *       n       *   *           *   *       *       *   *
    //  *     *           *     *           *     *     *     *     *
    //  *  so   *       *   se  *           *  so   *   *   *   se  *
    //  *         *   *         *           *         * * *         *
    //  * * * * * *op * * * * * *           * * * * * *op * * * * * *

    // Check if the opposite vertex of the actual triangle
    // lies inside the circle.
    // If so, swap inner edge
    // First, get necessary elements

    Vertex *v1, *v2, *v3;
    Face *n, *ne, *no;

    if(vert1 == f->V1() && vert2 == f->V2()){
        v1 = f->V1();
        v2 = f->V2();
        v3 = f->V3();
        n  = f->N1();
        ne = f->N2();
        no = f->N3();
    }
    else if(vert1 == f->V2() && vert2 == f->V3()){
        v1 = f->V2();
        v2 = f->V3();
        v3 = f->V1();
        n  = f->N2();
        ne = f->N3();
        no = f->N1();
    }
    else{
        v1 = f->V3();
        v2 = f->V1();
        v3 = f->V2();
        n  = f->N3();
        ne = f->N1();
        no = f->N2();
    }

    if(n == nullptr) {

        //---------------------------------------------------------
        std::cout << "Neighbour was null. Exiting \n" << std::endl;
        //---------------------------------------------------------

        return;
    }

    Vertex *op;
    Face *so, *se;

    if(v2 == n->V1() && v1 == n->V2()){
        op = n->V3();
        so = n->N2();
        se = n->N3();
    }
    else if(v2 == n->V2() && v1 == n->V3()){
        op = n->V1();
        so = n->N3();
        se = n->N1();
    }
    else {
        op = n->V2();
        so = n->N1();
        se = n->N2();
    }

    //--------------------------------------------------------------
    std::cout << "Triangle f is "<< *f << std::endl;
    if(f->N1()!= nullptr)
        std::cout << "with N1: "<< *(f->N1()) << std::endl;
    if(f->N2()!= nullptr)
        std::cout << "with N2: "<< *(f->N2()) << std::endl;
    if(f->N3()!= nullptr)
        std::cout << "with N3: "<< *(f->N3()) << " \n" << std::endl;

    std::cout << "Triangle n is "<< *n << std::endl;
    if(n->N1()!= nullptr)
        std::cout << "with N1: "<< *(n->N1()) << std::endl;
    if(n->N2()!= nullptr)
        std::cout << "with N2: "<< *(n->N2()) << std::endl;
    if(n->N3()!= nullptr)
        std::cout << "with N3: "<< *(n->N3()) << " \n" << std::endl;
    //--------------------------------------------------------------

    //Check if triangles can swap
    bool o1 = orientation(v1,op,v2,epsilon) == 1;
    bool o2 = orientation(op,v2,v3,epsilon) == 1;
    bool o3 = orientation(v2,v3,v1,epsilon) == 1;
    bool o4 = orientation(v3,v1,op,epsilon) == 1;
    bool isConvex = o1 && o2 && o3 && o4;

    if(!isConvex){
        std::cout << "Pair not convex. Legalizing neighbours \n" << std::endl;
        //if(o2 && !o4){
        //    legalizeEdge(f, v2, v3, epsilon);
        //    legalizeEdge(n, op, v2, epsilon);
        //}
        //else if(o4 && !o2){
        //    legalizeEdge(f, v3, v1, epsilon);
        //    legalizeEdge(n, v1, op, epsilon);
        //}
        return;
    }

    if(inCircle(v1,v2,v3,op,epsilon)){

        f->setV1(op); f->setV2(v2); f->setV3(v3);
        f->setN1(se); f->setN2(ne); f->setN3(n);

        n->setV1(v1); n->setV2(op); n->setV3(v3);
        n->setN1(so); n->setN2(f);  n->setN3(no);

        f->updateMEs();
        f->updateMA();

        n->updateMEs();
        n->updateMA();

        std::cout << "Triangle f is now "<< *f << std::endl;
        if(f->N1()!= nullptr)
            std::cout << "with N1: "<< *(f->N1()) << std::endl;
        if(f->N2()!= nullptr)
            std::cout << "with N2: "<< *(f->N2()) << std::endl;
        if(f->N3()!= nullptr)
            std::cout << "with N3: "<< *(f->N3()) << std::endl;
        std::cout << "Max Edge of f is ("<< *(*(f->ME_V1())) << " , " << *(*(f->ME_V2())) << ")" << std::endl;
        if(*(f->ME_N())!= nullptr)
            std::cout << "and it is pointing to "<< *(*(f->ME_N())) << "\n" << std::endl;

        std::cout << "Triangle n is now "<< *n << std::endl;
        if(n->N1()!= nullptr)
            std::cout << "with N1: "<< *(n->N1()) << std::endl;
        if(n->N2()!= nullptr)
            std::cout << "with N2: "<< *(n->N2()) << std::endl;
        if(n->N3()!= nullptr)
            std::cout << "with N3: "<< *(n->N3()) << std::endl;
        std::cout << "Max Edge of f is ("<< *(*(n->ME_V1())) << " , " << *(*(n->ME_V2())) << ")" << std::endl;
        if(*(n->ME_N())!= nullptr)
            std::cout << "and it is pointing to "<< *(*(n->ME_N())) << "\n" << std::endl;

        //Update no and se neighbourhoods
        if(no!= nullptr){
            if(v1==no->V1() && v3==no->V2()){
                no->setN1(n);
                std::cout << "Triangle no: "<< *no << "has new N1: " << *n << "\n" << std::endl;
            }
            else if(v1==no->V2() && v3==no->V3()){
                no->setN2(n);
                std::cout << "Triangle no: "<< *no << "has new N2: " << *n << "\n" << std::endl;
            }
            else{
                no->setN3(n);
                std::cout << "Triangle no: "<< *no << "has new N3: " << *n << "\n" << std::endl;
            }
        }
        if(se!= nullptr){
            if(v2==se->V1() && op==se->V2()){
                se->setN1(f);
                std::cout << "Triangle se: "<< *se << "has new N1: " << *f << "\n" << std::endl;
            }
            else if(v2==se->V2() && op==se->V3()){
                se->setN2(f);
                std::cout << "Triangle se: "<< *se << "has new N2: " << *f << "\n" << std::endl;
            }
            else{
                se->setN3(f);
                std::cout << "Triangle se: "<< *se << "has new N3: " << *f << "\n" << std::endl;
            }
        }

        legalizeEdge(f, op, v2, epsilon);
        legalizeEdge(n, v1, op, epsilon);
    }
}

void insertCentroid(std::vector<Face*> *face_list, Face *f1, Vertex *edge_v1, Vertex *edge_v2, double epsilon){

    std::cout << "INSERTING CENTROID ON FACES "<< *f1 << " AND HIS NEIGHBOUR \n" << std::endl;

    //  * * * * * *v3 * * * * * *           * * * * * *v3 * * * * * *
    //  *         *   *         *           *         * * *         *
    //  *  no   *       *   ne  *           *  no   *   *   *   ne  *
    //  *     *    f1     *     *           *     *     *     *     *
    //  *   *               *   *           *   *   f1  *  f4   *   *
    //  * *                   * *           * *         *         * *
    //  v1* * * * * * * * * * *v2   --->    v1* * * * * c * * * * *v2
    //  * *                   * *           * *         *         * *
    //  *   *               *   *           *   *   f2  *  f3   *   *
    //  *     *    f2     *     *           *     *     *     *     *
    //  *  so   *       *   se  *           *  so   *   *   *   se  *
    //  *         *   *         *           *         * * *         *
    //  * * * * * *v4 * * * * * *           * * * * * *v4 * * * * * *

    Vertex *v1, *v2, *v3, *v4;
    Face *f2, *ne, *no, *so, *se;

    if(edge_v1 == f1->V1() && edge_v2 == f1->V2()){
        v1 = f1->V1();
        v2 = f1->V2();
        v3 = f1->V3();
        f2 = f1->N1();
        ne = f1->N2();
        no = f1->N3();
    }
    else if(edge_v1 == f1->V2() && edge_v2 == f1->V3()){
        v1 = f1->V2();
        v2 = f1->V3();
        v3 = f1->V1();
        f2 = f1->N2();
        ne = f1->N3();
        no = f1->N1();
    }
    else{
        v1 = f1->V3();
        v2 = f1->V1();
        v3 = f1->V2();
        f2 = f1->N3();
        ne = f1->N1();
        no = f1->N2();
    }

    if(v2==f2->V1() && v1==f2->V2()){
        v4 = f2->V3();
        so = f2->N2();
        se = f2->N3();
    }
    else if(v2==f2->V2() && v1==f2->V3()){
        v4 = f2->V1();
        so = f2->N3();
        se = f2->N1();
    }
    else{
        v4 = f2->V2();
        so = f2->N1();
        se = f2->N2();
    }

    std::cout << "Triangle f1 is  "<< *f1 << std::endl;
    if(f1->N1()!= nullptr)
        std::cout << "with N1: "<< *(f1->N1()) << std::endl;
    if(f1->N2()!= nullptr)
        std::cout << "with N2: "<< *(f1->N2()) << std::endl;
    if(f1->N3()!= nullptr)
        std::cout << "with N3: "<< *(f1->N3()) << std::endl;
    std::cout << "Max Edge of f1 is ("<< *(*(f1->ME_V1())) << " , " << *(*(f1->ME_V2())) << ")" << std::endl;
    if(*(f1->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f1->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f2 is "<< *f2 << std::endl;
    if(f2->N1()!= nullptr)
        std::cout << "with N1: "<< *(f2->N1()) << std::endl;
    if(f2->N2()!= nullptr)
        std::cout << "with N2: "<< *(f2->N2()) << std::endl;
    if(f2->N3()!= nullptr)
        std::cout << "with N3: "<< *(f2->N3()) << std::endl;
    std::cout << "Max Edge of f2 is ("<< *(*(f2->ME_V1())) << " , " << *(*(f2->ME_V2())) << ")" << std::endl;
    if(*(f2->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f2->ME_N())) << "\n" << std::endl;

    Vertex* c = centroid(v1,v4,v2,v3);

    f1->setV1(v3); f1->setV2(v1); f1->setV3(c);
    f2->setV1(v1); f2->setV2(v4); f2->setV3(c);
    auto f3 = new Face(v4,v2,c);
    auto f4 = new Face(v2,v3,c);


    std::cout << "Triangle f3 is  "<< *f3 << std::endl;
    if(f3->N1()!= nullptr)
        std::cout << "with N1: "<< *(f3->N1()) << std::endl;
    if(f3->N2()!= nullptr)
        std::cout << "with N2: "<< *(f3->N2()) << std::endl;
    if(f3->N3()!= nullptr)
        std::cout << "with N3: "<< *(f3->N3()) << std::endl;
    std::cout << "Max Edge of f3 is ("<< *(*(f3->ME_V1())) << " , " << *(*(f3->ME_V2())) << ")" << std::endl;
    if(*(f3->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f3->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f4 is "<< *f4 << std::endl;
    if(f4->N1()!= nullptr)
        std::cout << "with N1: "<< *(f4->N1()) << std::endl;
    if(f4->N2()!= nullptr)
        std::cout << "with N2: "<< *(f4->N2()) << std::endl;
    if(f4->N3()!= nullptr)
        std::cout << "with N3: "<< *(f4->N3()) << std::endl;
    std::cout << "Max Edge of f4 is ("<< *(*(f4->ME_V1())) << " , " << *(*(f4->ME_V2())) << ")" << std::endl;
    if(*(f4->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f4->ME_N())) << "\n" << std::endl;


    f1->setN1(no); f1->setN2(f2); f1->setN3(f4);
    f2->setN1(so); f2->setN2(f3); f2->setN3(f1);
    f3->setN1(se); f3->setN2(f4); f3->setN3(f2);
    f4->setN1(ne); f4->setN2(f1); f4->setN3(f3);

    f1->updateMEs();
    f1->updateMA();
    f2->updateMEs();
    f2->updateMA();
    f3->updateMEs();
    f3->updateMA();
    f4->updateMEs();
    f4->updateMA();

    std::cout << "Triangle f1 is now "<< *f1 << std::endl;
    if(f1->N1()!= nullptr)
        std::cout << "with N1: "<< *(f1->N1()) << std::endl;
    if(f1->N2()!= nullptr)
        std::cout << "with N2: "<< *(f1->N2()) << std::endl;
    if(f1->N3()!= nullptr)
        std::cout << "with N3: "<< *(f1->N3()) << std::endl;
    std::cout << "Max Edge of f1 is now ("<< *(*(f1->ME_V1())) << " , " << *(*(f1->ME_V2())) << ")" << std::endl;
    if(*(f1->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f1->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f2 is now "<< *f2 << std::endl;
    if(f2->N1()!= nullptr)
        std::cout << "with N1: "<< *(f2->N1()) << std::endl;
    if(f2->N2()!= nullptr)
        std::cout << "with N2: "<< *(f2->N2()) << std::endl;
    if(f2->N3()!= nullptr)
        std::cout << "with N3: "<< *(f2->N3()) << std::endl;
    std::cout << "Max Edge of f2 is now ("<< *(*(f2->ME_V1())) << " , " << *(*(f2->ME_V2())) << ")" << std::endl;
    if(*(f2->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f2->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f3 is now "<< *f3 << std::endl;
    if(f3->N1()!= nullptr)
        std::cout << "with N1: "<< *(f3->N1()) << std::endl;
    if(f3->N2()!= nullptr)
        std::cout << "with N2: "<< *(f3->N2()) << std::endl;
    if(f3->N3()!= nullptr)
        std::cout << "with N3: "<< *(f3->N3()) << std::endl;
    std::cout << "Max Edge of f3 is now ("<< *(*(f3->ME_V1())) << " , " << *(*(f3->ME_V2())) << ")" << std::endl;
    if(*(f3->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f3->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f4 is now "<< *f4 << std::endl;
    if(f4->N1()!= nullptr)
        std::cout << "with N1: "<< *(f4->N1()) << std::endl;
    if(f4->N2()!= nullptr)
        std::cout << "with N2: "<< *(f4->N2()) << std::endl;
    if(f4->N3()!= nullptr)
        std::cout << "with N3: "<< *(f4->N3()) << std::endl;
    std::cout << "Max Edge of f4 is now ("<< *(*(f4->ME_V1())) << " , " << *(*(f4->ME_V2())) << ")" << std::endl;
    if(*(f4->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f4->ME_N())) << "\n" << std::endl;

    face_list->push_back(f3);
    face_list->push_back(f4);

    //Update ne and se neighbourhoods
    if(ne!= nullptr){
        if(v3==ne->V1() && v2==ne->V2()){
            ne->setN1(f4);
            std::cout << "Triangle ne: "<< *ne << "has new N1: " << *f4 << "\n" << std::endl;
        }
        else if(v3==ne->V2() && v2==ne->V3()){
            ne->setN2(f4);
            std::cout << "Triangle ne: "<< *ne << "has new N2: " << *f4 << "\n" << std::endl;
        }
        else{
            ne->setN3(f4);
            std::cout << "Triangle ne: "<< *ne << "has new N3: " << *f4 << "\n" << std::endl;
        }
    }
    if(se!= nullptr){
        if(v2==se->V1() && v4==se->V2()){
            se->setN1(f3);
            std::cout << "Triangle se: "<< *se << "has new N1: " << *f3 << "\n" << std::endl;
        }
        else if(v2==se->V2() && v4==se->V3()){
            se->setN2(f3);
            std::cout << "Triangle se: "<< *se << "has new N2: " << *f3 << "\n" << std::endl;
        }
        else{
            se->setN3(f3);
            std::cout << "Triangle se: "<< *se << "has new N3: " << *f3 << "\n" << std::endl;
        }
    }

    legalizeEdge(f1, v3, v1, epsilon);
    legalizeEdge(f2, v1, v4, epsilon);
    legalizeEdge(f3, v4, v2, epsilon);
    legalizeEdge(f4, v2, v3, epsilon);

}

void insertMidpoint(std::vector<Face*> *face_list, Face *f, Vertex *edge_v1, Vertex *edge_v2, double epsilon){

    std::cout<<"INSERTING MIDPOINT ON FACES "<<*f<<" WITH EDGE ("<<*edge_v1<<" , "<<*edge_v2<<") \n"<< std::endl;

    //  * * * * * *v3 * * * * * *           * * * * * *v3 * * * * * *
    //  *         *   *         *           *         * * *         *
    //  *  no   *       *   ne  *           *  no   *   *   *   ne  *
    //  *     *    f      *     *           *     *     *     *     *
    //  *   *               *   *           *   *   f   *  f2   *   *
    //  * *                   * *           * *         *         * *
    //  v1* * * * * * * * * * *v2   --->    v1* * * * * m * * * * *v2

    Vertex *v1, *v2, *v3;
    Face *ne, *no;

    if(edge_v1 == f->V1() && edge_v2 == f->V2()){
        v1 = f->V1();
        v2 = f->V2();
        v3 = f->V3();
        ne = f->N2();
        no = f->N3();
    }
    else if(edge_v1 == f->V2() && edge_v2 == f->V3()){
        v1 = f->V2();
        v2 = f->V3();
        v3 = f->V1();
        ne = f->N3();
        no = f->N1();
    }
    else{
        v1 = f->V3();
        v2 = f->V1();
        v3 = f->V2();
        ne = f->N1();
        no = f->N2();
    }

    std::cout << "Triangle f1 is  "<< *f << std::endl;
    if(f->N1()!= nullptr)
        std::cout << "with N1: "<< *(f->N1()) << std::endl;
    if(f->N2()!= nullptr)
        std::cout << "with N2: "<< *(f->N2()) << std::endl;
    if(f->N3()!= nullptr)
        std::cout << "with N3: "<< *(f->N3()) << std::endl;
    std::cout << "Max Edge of f1 is ("<< *(*(f->ME_V1())) << " , " << *(*(f->ME_V2())) << ")" << std::endl;
    if(*(f->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f->ME_N())) << "\n" << std::endl;

    Vertex* m = midpoint(v1,v2);

    f->setV1(v3); f->setV2(v1); f->setV3(m);
    auto f2 = new Face(v2,v3,m);

    f->setN1(no); f->setN2(nullptr); f->setN3(f2);
    f2->setN1(ne); f2->setN2(f); f2->setN3(nullptr);

    std::cout << "Triangle f2 is "<< *f2 << std::endl;
    if(f2->N1()!= nullptr)
        std::cout << "with N1: "<< *(f2->N1()) << std::endl;
    if(f2->N2()!= nullptr)
        std::cout << "with N2: "<< *(f2->N2()) << std::endl;
    if(f2->N3()!= nullptr)
        std::cout << "with N3: "<< *(f2->N3()) << std::endl;
    std::cout << "Max Edge of f2 is ("<< *(*(f2->ME_V1())) << " , " << *(*(f2->ME_V2())) << ")" << std::endl;
    if(*(f2->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f2->ME_N())) << "\n" << std::endl;

    f->updateMEs();
    f->updateMA();
    f2->updateMEs();
    f2->updateMA();

    std::cout << "Triangle f1 is now "<< *f << std::endl;
    if(f->N1()!= nullptr)
        std::cout << "with N1: "<< *(f->N1()) << std::endl;
    if(f->N2()!= nullptr)
        std::cout << "with N2: "<< *(f->N2()) << std::endl;
    if(f->N3()!= nullptr)
        std::cout << "with N3: "<< *(f->N3()) << std::endl;
    std::cout << "Max Edge of f1 is now ("<< *(*(f->ME_V1())) << " , " << *(*(f->ME_V2())) << ")" << std::endl;
    if(*(f->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f->ME_N())) << "\n" << std::endl;

    std::cout << "Triangle f2 is now "<< *f2 << std::endl;
    if(f2->N1()!= nullptr)
        std::cout << "with N1: "<< *(f2->N1()) << std::endl;
    if(f2->N2()!= nullptr)
        std::cout << "with N2: "<< *(f2->N2()) << std::endl;
    if(f2->N3()!= nullptr)
        std::cout << "with N3: "<< *(f2->N3()) << std::endl;
    std::cout << "Max Edge of f2 is now ("<< *(*(f2->ME_V1())) << " , " << *(*(f2->ME_V2())) << ")" << std::endl;
    if(*(f2->ME_N())!= nullptr)
        std::cout << "and it is pointing to "<< *(*(f2->ME_N())) << "\n" << std::endl;


    face_list->push_back(f2);

    if(ne!= nullptr){
        if(v3==ne->V1() && v2==ne->V2()){
            ne->setN1(f2);
            std::cout << "Triangle ne: "<< *ne << "has new N1: " << *f2 << "\n" << std::endl;
        }
        else if(v3==ne->V2() && v2==ne->V3()){
            ne->setN2(f2);
            std::cout << "Triangle ne: "<< *ne << "has new N2: " << *f2 << "\n" << std::endl;
        }
        else{
            ne->setN3(f2);
            std::cout << "Triangle ne: "<< *ne << "has new N3: " << *f2 << "\n" << std::endl;
        }
    }

    legalizeEdge(f, v3, v1, epsilon);
    legalizeEdge(f2, v2, v3, epsilon);
}

void updateDelaunay(std::vector<Face*> *triangulation, double epsilon, double tolerance, int detail){

    std::cout << "\n" << std::endl;
    std::cout << "##############################################" << std::endl;
    std::cout << "     STARTING LEPP DELAUNAY TRIANGULATION     " << std::endl;
    std::cout << "##############################################\n" << std::endl;

    //Find set of bad quality triangles
    std::vector<Face*> S;
    for(Face* f: *triangulation){
        if(f->MA() <= tolerance){
            S.push_back(f);
        }
    }

    int max_iterations = 0;
    while(!S.empty()) {

        if(detail!= 0 && max_iterations>=detail){
            break;
        }

        std::cout << "\n" << std::endl;
        std::cout << "##############################################" << std::endl;
        std::cout << "              NEW ROUND OF TRIANGLES          " << std::endl;
        std::cout << "##############################################\n" << std::endl;

        //For each triangle in S
        Face *t, *t1, *t2;
        while (!S.empty()) {

            t = S.back();
            S.pop_back();

            std::cout << "Current triangle t: " << *t << " \n" << std::endl;
            if (t->N1() != nullptr)
                std::cout << "with N1: " << *(t->N1()) << std::endl;
            if (t->N2() != nullptr)
                std::cout << "with N2: " << *(t->N2()) << std::endl;
            if (t->N3() != nullptr)
                std::cout << "with N3: " << *(t->N3()) << std::endl;
            std::cout << "Max Edge of t is (" << *(*(t->ME_V1())) << " , " << *(*(t->ME_V2())) << ")" << std::endl;
            if (*(t->ME_N()) != nullptr)
                std::cout << "and it is pointing to " << *(*(t->ME_N())) << "\n" << std::endl;

            std::cout << "\n" << std::endl;
            std::cout << "##############################################" << std::endl;
            std::cout << "        STARTING REFINEMENT PROCCESS          " << std::endl;
            std::cout << "##############################################\n" << std::endl;

            //While t remains unrefined
            while (true) {

                // We exit if triangle is already good
                if (t->MA() > tolerance) {
                    std::cout << "END OF REFINEMENT\n" << std::endl;
                    break;
                }

                //Find terminal triangles (t1,t2)
                std::cout << "SEARCHING FOR TERMINAL TRIANGLES\n" << std::endl;

                t1 = t;
                t2 = *(t1->ME_N());

                std::cout << "Triangle t1 is now " << *t1 << std::endl;
                if (t1->N1() != nullptr)
                    std::cout << "with N1: " << *(t1->N1()) << std::endl;
                if (t1->N2() != nullptr)
                    std::cout << "with N2: " << *(t1->N2()) << std::endl;
                if (t1->N3() != nullptr)
                    std::cout << "with N3: " << *(t1->N3()) << std::endl;
                std::cout << "Max Edge of t1 is now (" << *(*(t1->ME_V1())) << " , " << *(*(t1->ME_V2())) << ")"
                          << std::endl;
                if (*(t1->ME_N()) != nullptr)
                    std::cout << "and it is pointing to " << *(*(t1->ME_N())) << "\n" << std::endl;

                if (t2 != nullptr) {
                    std::cout << "Triangle t2 is now " << *t2 << std::endl;
                    if (t2->N1() != nullptr)
                        std::cout << "with N1: " << *(t2->N1()) << std::endl;
                    if (t2->N2() != nullptr)
                        std::cout << "with N2: " << *(t2->N2()) << std::endl;
                    if (t2->N3() != nullptr)
                        std::cout << "with N3: " << *(t2->N3()) << std::endl;
                    std::cout << "Max Edge of t2 is now (" << *(*(t2->ME_V1())) << " , " << *(*(t2->ME_V2())) << ")"
                              << std::endl;
                    if (*(t2->ME_N()) != nullptr)
                        std::cout << "and it is pointing to " << *(*(t2->ME_N())) << "\n" << std::endl;
                }

                while (!terminalFaces(t1, t2)) {
                    t1 = t2;
                    t2 = *(t1->ME_N());

                    std::cout << "Triangle t1 is now " << *t1 << std::endl;
                    if (t1->N1() != nullptr)
                        std::cout << "with N1: " << *(t1->N1()) << std::endl;
                    if (t1->N2() != nullptr)
                        std::cout << "with N2: " << *(t1->N2()) << std::endl;
                    if (t1->N3() != nullptr)
                        std::cout << "with N3: " << *(t1->N3()) << std::endl;
                    std::cout << "Max Edge of t1 is now (" << *(*(t1->ME_V1())) << " , " << *(*(t1->ME_V2())) << ")"
                              << std::endl;
                    if (*(t1->ME_N()) != nullptr)
                        std::cout << "and it is pointing to " << *(*(t1->ME_N())) << "\n" << std::endl;

                    if (t2 != nullptr) {
                        std::cout << "Triangle t2 is now " << *t2 << std::endl;
                        if (t2->N1() != nullptr)
                            std::cout << "with N1: " << *(t2->N1()) << std::endl;
                        if (t2->N2() != nullptr)
                            std::cout << "with N2: " << *(t2->N2()) << std::endl;
                        if (t2->N3() != nullptr)
                            std::cout << "with N3: " << *(t2->N3()) << std::endl;
                        std::cout << "Max Edge of t2 is now (" << *(*(t2->ME_V1())) << " , " << *(*(t2->ME_V2())) << ")"
                                  << std::endl;
                        if (*(t2->ME_N()) != nullptr)
                            std::cout << "and it is pointing to " << *(*(t2->ME_N())) << "\n" << std::endl;
                    }
                }

                //If E is constrained
                if (t2 == nullptr) {
                    std::cout << "CASE: MAX EDGE CONSTRAINED \n" << std::endl;
                    insertMidpoint(triangulation, t1, *(t1->ME_V1()), *(t1->ME_V2()), epsilon);
                } else {
                    //if exists t1 or t2 with low tolerance and second longest edge is constrained
                    if (t1->MA() <= tolerance && *(t1->SME_N()) == nullptr) {
                        std::cout << "CASE: LOW TOLERANCE T1, SECOND MAX EDGE CONSTRAINED \n" << std::endl;
                        insertMidpoint(triangulation, t1, *(t1->SME_V1()), *(t1->SME_V2()), epsilon);
                    } else if (t2->MA() <= tolerance && *(t2->SME_N()) == nullptr) {
                        std::cout << "CASE: LOW TOLERANCE T2, SECOND MAX EDGE CONSTRAINED \n" << std::endl;
                        insertMidpoint(triangulation, t2, *(t2->SME_V1()), *(t2->SME_V2()), epsilon);
                    }
                        //else, insert centroid
                    else {
                        std::cout << "CASE: LOW TOLERANCE. CENTROID INSERTION \n" << std::endl;
                        insertCentroid(triangulation, t1, *(t1->ME_V1()), *(t1->ME_V2()), epsilon);
                    }
                }
            }
        }

        for(Face* f: *triangulation){
            if(f->MA() <= tolerance){
                S.push_back(f);
            }
        }

        max_iterations++;
    }
}

int contained(Face *f, Vertex *v, double epsilon){
    Vertex* v1 = f->V1();
    Vertex* v2 = f->V2();
    Vertex* v3 = f->V3();
    if(orientation(v1, v2, v, epsilon)==1 &&
       orientation(v2, v3, v, epsilon)==1 &&
       orientation(v3, v1, v, epsilon)==1){
        return 1;
    }
    else if((orientation(v1,v2,v,epsilon)==0 && orientation(v2,v3,v,epsilon)==1 && orientation(v3,v1,v,epsilon)==1) ||
            (orientation(v1,v2,v,epsilon)==1 && orientation(v2,v3,v,epsilon)==0 && orientation(v3,v1,v,epsilon)==1) ||
            (orientation(v1,v2,v,epsilon)==1 && orientation(v2,v3,v,epsilon)==1 && orientation(v3,v1,v,epsilon)==0)){
        return 0;
    }
    else{
        return -1;
    }
}

ContInfo faceContainingVertex(std::vector<Face*> *face_list, Vertex *v, double epsilon){
    Face* f = (*face_list)[0];
    int previous_neighbour = 0;
    while(f != nullptr){
        int cnt = contained(f,v,epsilon);
        if (cnt>=0){
            auto cinf = (ContInfo) malloc(sizeof(ContInfo));
            cinf->f=f;
            cinf->status=cnt;
            return cinf;
        }
        else{
            if(orientation(f->V1(),f->V2(),v,epsilon)==-1 && previous_neighbour!=1){
                if((f->N1())->N1() == f){
                    previous_neighbour = 1;
                }
                else if((f->N1())->N2() == f){
                    previous_neighbour = 2;
                }
                else {
                    previous_neighbour = 3;
                }
                f = f->N1();
            }
            else if(orientation(f->V2(),f->V3(),v,epsilon)==-1 && previous_neighbour!=2){
                if((f->N2())->N1() == f){
                    previous_neighbour = 1;
                }
                else if((f->N2())->N2() == f){
                    previous_neighbour = 2;
                }
                else {
                    previous_neighbour = 3;
                }
                f = f->N2();
            }
            else if(orientation(f->V3(),f->V1(),v,epsilon)==-1 && previous_neighbour!=3){
                if((f->N3())->N1() == f){
                    previous_neighbour = 1;
                }
                else if((f->N3())->N2() == f){
                    previous_neighbour = 2;
                }
                else {
                    previous_neighbour = 3;
                }
                f = f->N3();
            }
        }
    }

    std::cout << "Neighbour is null" << std::endl;

    return nullptr;
}

void addThreeEdges(std::vector<Face*> *face_list, Face *f, Vertex *p){

    //                     v3
    //                    * *
    //                   * * *
    //                  *  *  *
    //                 *   *   *
    //                *    *    *
    //               *     *     *
    //              *      *      *
    //             *       *       *
    //            *        *        *
    //     n3    *         *         *     n2
    //          *          *          *
    //         *    f3     *     f2    *
    //        *            p            *
    //       *           *   *           *
    //      *         *         *         *
    //     *       *               *       *
    //    *     *          f          *     *
    //   *   *                           *   *
    //  * *                                 * *
    // v1* * * * * * * * * * * * * * * * * * *v2
    //
    //                    n1

    // f is the triangle where te new vertex is
    // face_list is the list of triangles
    // First, we retrive all vertex and neighbours
    Vertex* v1 = f->V1();
    Vertex* v2 = f->V2();
    Vertex* v3 = f->V3();
    Face* n1 = f->N1();
    Face* n2 = f->N2();
    Face* n3 = f->N3();

    //We create two more triangles and alter previous one
    f->setV1(v1);
    f->setV2(v2);
    f->setV3(p);
    auto f2 = new Face(v2,v3,p);
    auto f3 = new Face(v3,v1,p);

    //We assign new neighbours

    //f1
    f->setN1(n1);
    f->setN2(f2);
    f->setN3(f3);

    //f2
    f2->setN1(n2);
    f2->setN2(f3);
    f2->setN3(f);

    //f3
    f3->setN1(n3);
    f3->setN2(f);
    f3->setN3(f2);

    //Triangles are ready
    //We add their pointers to the list
    face_list->push_back(f2);
    face_list->push_back(f3);

    // Update n2 and n3 neighbourhood
    // n2 neighbourhood
    if(n2!= nullptr){
        if(v3==n2->V1() && v2==n2->V2()){
            n2->setN1(f2);
        }
        else if(v3==n2->V2() && v2==n2->V3()){
            n2->setN2(f2);
        }
        else{
            n2->setN3(f2);
        }
    }
    // n3 neighbourhood
    if(n3!= nullptr){
        if(v1==n3->V1() && v3==n3->V2()){
            n3->setN1(f3);
        }
        else if(v1==n3->V2() && v3==n3->V3()){
            n3->setN2(f3);
        }
        else{
            n3->setN3(f3);
        }
    }
}

void addTwoEdges(std::vector<Face*> *face_list, Face *f, Vertex *p, double epsilon){

    //  * * * * * *v3 * * * * * *           * * * * * *v3 * * * * * *
    //  *         *   *         *           *         * * *         *
    //  *  no   *       *   ne  *           *  no   *   *   *   ne  *
    //  *     *     f     *     *           *     *     *     *     *
    //  *   *               *   *           *   *   f   *  f4   *   *
    //  * *                   * *           * *         *         * *
    //  v1* * * * * p * * * * *v2   --->    v1* * * * * p * * * * *v2
    //  * *                   * *           * *         *         * *
    //  *   *               *   *           *   *   f2  *  f3   *   *
    //  *     *    f2     *     *           *     *     *     *     *
    //  *  so   *       *   se  *           *  so   *   *   *   se  *
    //  *         *   *         *           *         * * *         *
    //  * * * * * *v4 * * * * * *           * * * * * *v4 * * * * * *

    // Phase 1
    Vertex *v1, *v2, *v3, *v4;
    Face *f2, *ne, *no, *so, *se;
    if(orientation(f->V1(), f->V2(),p,epsilon)==0){
        v1 = f->V1();
        v2 = f->V2();
        v3 = f->V3();
        f2 = f->N1();
        ne = f->N2();
        no = f->N3();
    }
    else if(orientation(f->V2(), f->V3(),p, epsilon)==0){
        v1 = f->V2();
        v2 = f->V3();
        v3 = f->V1();
        f2 = f->N2();
        ne = f->N3();
        no = f->N1();
    }
    else{
        v1 = f->V3();
        v2 = f->V1();
        v3 = f->V2();
        f2 = f->N3();
        ne = f->N1();
        no = f->N2();
    }

    if(v2==f2->V1() && v1==f2->V2()){
        v4 = f2->V3();
        so = f2->N2();
        se = f2->N3();
    }
    else if(v2==f2->V2() && v1==f2->V3()){
        v4 = f2->V1();
        so = f2->N3();
        se = f2->N1();
    }
    else{
        v4 = f2->V2();
        so = f2->N1();
        se = f2->N2();
    }

    f->setV1(v3);
    f->setV2(v1);
    f->setV3(v2);
    f->setN1(no);
    f->setN2(f2);
    f->setN3(ne);

    f2->setV1(v1);
    f2->setV2(v4);
    f2->setV3(v2);
    f2->setN1(so);
    f2->setN2(se);
    f2->setN3(f);

    //Phase 2
    f->setV3(p);
    f2->setV3(p);
    auto f3 = new Face(v4,v2,p);
    auto f4 = new Face(v2,v3,p);
    f->setN3(f4);
    f2->setN2(f3);
    f3->setN1(se);
    f3->setN2(f4);
    f3->setN3(f2);
    f4->setN1(ne);
    f4->setN2(f);
    f4->setN3(f3);

    face_list->push_back(f3);
    face_list->push_back(f4);

    //Update ne and se neighbourhoods
    if(ne!= nullptr){
        if(v3==ne->V1() && v2==ne->V2()){
            ne->setN1(f4);
        }
        else if(v3==ne->V2() && v2==ne->V3()){
            ne->setN2(f4);
        }
        else{
            ne->setN3(f4);
        }
    }
    if(se!= nullptr){
        if(v2==se->V1() && v4==se->V2()){
            se->setN1(f3);
        }
        else if(v2==se->V2() && v4==se->V3()){
            se->setN2(f3);
        }
        else{
            se->setN3(f3);
        }
    }
}