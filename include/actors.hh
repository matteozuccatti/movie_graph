#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <typeinfo>
#include "SQL_parser.hh"


static std::string main_actor = "Leonardo DiCaprio"; 
// ======================================================================== //
//                              VECTOR CLASS                                //
// ======================================================================== //
class Vector{
private:
    double x; 
    double y;
    double L;

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

    void setX(double x_)    {this->x=x_; updateL();}
    void setY(double y_)    {this->y=y_; updateL();}

    void updateL()  {this->L = sqrt(pow(this->x,2) + pow(this->y,2));}
    Vector normalize();
    Vector invert();
    Vector times (double m) const;

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
    /*
    friend Vector operator*(Vector const &v1, const double m){
        double new_x = v1.getX() * m ; 
        double new_y = v1.getY() * m ; 
        Vector v = Vector(new_x,new_y);
        return v;
    }
    friend Vector operator/(Vector const &v1, const double m){
        double new_x = v1.getX() / m ; 
        double new_y = v1.getY() / m ; 
        Vector v = Vector(new_x,new_y);
        return v;
    }
    */

};


// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //

class Actor{
public:
    Actor(std::string actorId_ , std::string actorName_ )
    {
        this->actorId   = actorId_; 
        this->actorName = actorName_;
    }

    // -----------------------------------------------

    std::string actorId = "";
    std::string actorName = ""; 
    std::vector<std::string> commonMovies = {}; 
    int commonMovies_number = 0; 
    int allMovies = 0; 
    int actorSize = 0; 

    std::vector<std::string> connectedTo = {};

    // -----------------------------------------------

    void printActor();

    // -----------------------------------------------

    bool operator==(const Actor &a) const {
        return(this->actorId == a.actorId);
    }
    bool operator!=(const Actor &a) const {
        return(this->actorId != a.actorId);
    }
    bool operator<(const Actor &a) const {
        return(this->allMovies > a.allMovies);
    }

};


// ======================================================================== //
//                               NODE CLASS                                 //
// ======================================================================== //

class Node{
public: 
    // State variables
    Vector x_ddot = Vector(0.0,0.0); 
    Vector x_dot  = Vector(0.0,0.0); 
    Vector x      = Vector(50,0.0); 

    Vector f_ext  = Vector(0.0,0.0);
    Vector f_tot  = Vector(0.0,0.0);

    // Physical properties  
    double k  = 100;   // spring coefficient
    double x0 = 200;   // spring lenght neutral 
    double c  = 15;   // damper coefficient 

    // Functions 
    bool euler_complete = false; 
    void evaluateF_ext(std::vector<Node> &nodes);
    void evaluateF(std::vector<Node> &nodes);

    // ----------------------------------------------------------------------

    friend std::ostream &operator<<(std::ostream &output, const Node &n ) {
        output << "NODE PRINT p:[" << n.x.getX() << "," << n.x.getY()  << "]=>" << n.x.getL() 
                <<" p_dot:[" << n.x_dot.getX() << "," << n.x_dot.getY() << "]=>" << n.x_dot.getL();
        return output;
    }
};


// ======================================================================== //
// ======================================================================== //
// ======================================================================== //

void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors);
void actorListInit(std::vector<Actor> &actors);
void printActorMap(std::vector<Actor> &actors);
void printActorVec(std::vector<Actor> &actors);

// ======================================================================== //

void euler_method(std::vector<Node> &nodes, Node &node);
void compute_forces(std::vector<Node> &nodes, Node &node);
void compute_graph_layout(std::vector<Node> &nodes);
bool stop_euler(std::vector<Node> &nodes);
void testEuler(); 

