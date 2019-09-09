//
// Created by VictorStefano on 04-05-2019.
//

#include "Vertex.h"

// VERTEX CONSTRUCTOR AND FUNCTIONS

Vertex::Vertex(double x_coord, double y_coord) {
    x = x_coord;
    y = y_coord;
}

Vertex::~Vertex() = default;
double Vertex::X() {return x;}
double Vertex::Y() {return y;}
void Vertex::setX(double xCoord) {x = xCoord;}
void Vertex::setY(double yCoord) {y = yCoord;}

std::ostream& operator<<(std::ostream& out, Vertex& v){
    out << "(" << v.X() << "," << v.Y() << ")";
    return out;
}