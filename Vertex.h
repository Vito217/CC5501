//
// Created by VictorStefano on 04-05-2019.
//

#ifndef TAREADOSMALLAS_VERTEX_H
#define TAREADOSMALLAS_VERTEX_H

#endif //TAREADOSMALLAS_VERTEX_H

#include <iostream>
#include <vector>
#include <tuple>

class Vertex{
    private:
        double x;
        double y;
    public:
        Vertex(double x_coord, double y_coord);
        virtual ~Vertex();
        double  X();
        double  Y();
        void    setX(double xCoord);
        void    setY(double yCoord);
    friend std::ostream& operator<<(std::ostream& out, Vertex& v);
};