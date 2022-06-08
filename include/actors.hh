#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <typeinfo>
#include "SQL_parser.hh"

// ======================================================================== //
//                              VECTOR CLASS                                //
// ======================================================================== //
class Vector{
private:
    double x,y; 

public:
    Vector()
    {
        setX(0);
        setY(0);
    }

    Vector(double x_, double y_) 
    {
        setX(x_); 
        setY(y_);
    }

    // ------------------------------------------------------------------

    double getX() const  {return x;}
    double getY() const  {return y;}
    double getL() const  {return sqrt(pow(this->x,2) + pow(this->y,2));}

    void setX(double x_)    {this->x=x_;}
    void setY(double y_)    {this->y=y_;}

    Vector normalize();
    Vector invert();
    Vector times (double m) const;
    double dot(Vector &v);

    // ------------------------------------------------------------------

    bool operator==( const Vector &v){
        return( (this->getX()==v.getX()) && (this->getY()==v.getY()) );
    }
    void operator+=( const Vector &v){
        this->setX(x + v.getX());
        this->setY(y + v.getY());
    }
    void operator-=( const Vector &v){
        this->setX(x - v.getX());
        this->setY(y - v.getY());
    }
    friend std::ostream &operator<<(std::ostream &output, const Vector &v ) {
        output <<  "[" << v.getX() << "," << v.getY()  << "]=>L:" << v.getL();
        return output;
    }
    friend Vector operator+(Vector const&v1, Vector const& v2){
        double x_tmp = v1.getX() + v2.getX(); 
        double y_tmp = v1.getY() + v2.getY();
        Vector v = Vector(x_tmp,y_tmp);
        return v;
    }
    friend Vector operator-(Vector const&v1, Vector const& v2){
        double x_tmp = v1.getX() - v2.getX(); 
        double y_tmp = v1.getY() - v2.getY();
        Vector v = Vector(x_tmp,y_tmp);
        return v;
    }
};


// ======================================================================== //
//                               NODE CLASS                                 //
// ======================================================================== //
class Node{
public: 
    static int total_nodes; 
    const int node_id; 
    Node():
        node_id( (total_nodes++) )
    {
        
    }
    // State variables
    Vector x_ddot = Vector(0.0,0.0); 
    Vector x_dot  = Vector(0.0,0.0); 
    Vector x      = Vector(50,0.0); 

    // Vector forces
    Vector f_spr, f_damp, f_ext, f_fri, f_tot  = Vector(0.0,0.0);
    

    // Physical properties == LINK  
    double k  = 1000;                    // spring coefficient
    double x0 = 200;                    // spring lenght neutral 
    double c  = 50;                     // damper coefficient 
    // Graphical properties == NODE 
    double size = 10; 

    // ----------------------------------------------------------------------

    friend std::ostream &operator<<(std::ostream &output, const Node &n ) {
        output << 
        "NODE id:"  << std::setw(2) <<  n.node_id       <<
        " p:["      << std::setw(6) <<  n.x.getX()      << 
        ","         << std::setw(6) <<  n.x.getY()      << 
        "]=>"       << std::setw(10)<<  n.x.getL()      <<
        " | p_dot:["<< std::setw(6) <<  n.x_dot.getX()  << 
        ","         << std::setw(6) <<  n.x_dot.getY()  << 
        "]=>"       << std::setw(10)<<  n.x_dot.getL()  ;
        return output;
    }

    bool operator==(const Node&n) const{
        return this->node_id == n.node_id;
    }
};


std::vector<Node> get_sample_vector_nodes();

void computeSpringForces(std::vector<Node> &nodes);
void computeDamperForces(std::vector<Node> &nodes);
void computeExternalForces(std::vector<Node> &nodes);
void computeFrictionForces(std::vector<Node> &nodes);
void computeTotForces(std::vector<Node> &nodes);

void updateLayout(std::vector<Node> &nodes);
void updateForces(std::vector<Node> &nodes);
void updatePos(std::vector<Node> &nodes);

void printVectorNodes(std::vector<Node> &nodes);

// ======================================================================== //

