//
// Created by VictorStefano on 04-05-2019.
//

#ifndef TAREADOSMALLAS_FACE_H
#define TAREADOSMALLAS_FACE_H

#endif //TAREADOSMALLAS_FACE_H

#include "Vertex.h"

class Face{
    private:
        Vertex*  v1;
        Vertex*  v2;
        Vertex*  v3;
        Face*    n1;
        Face*    n2;
        Face*    n3;
        float    c1;
        float    c2;
        float    c3;

        Vertex** max_edge_v1;
        Vertex** max_edge_v2;
        Face**   max_edge_n;

        Vertex** sec_max_edge_v1;
        Vertex** sec_max_edge_v2;
        Face**   sec_max_edge_n;

        double   min_angle;
        void     computeMaxEdges();
        void     computeMinAngle();
    public:
        Face(Vertex *v1, Vertex *v2, Vertex *v3);
        Face(Vertex *v1, Vertex *v2, Vertex *v3, Face *f1, Face *f2, Face*f3);
        virtual ~Face();
        Vertex*  V1();
        Vertex*  V2();
        Vertex*  V3();
        Face*    N1();
        Face*    N2();
        Face*    N3();
        float    C1();
        float    C2();
        float    C3();
        Vertex** ME_V1();
        Vertex** ME_V2();
        Face**   ME_N();
        Vertex** SME_V1();
        Vertex** SME_V2();
        Face**   SME_N();
        double   MA();
        void     updateMEs();
        void     updateMA();
        void     setV1(Vertex* v);
        void     setV2(Vertex* v);
        void     setV3(Vertex* v);
        void     setN1(Face* f);
        void     setN2(Face* f);
        void     setN3(Face* f);
    friend std::ostream& operator<<(std::ostream& out, Face& f);
};