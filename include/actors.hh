#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "SQL_parser.hh"

static double idealSpringL = 20.0; 
static double espilon = 1.0; 
static std::string main_actor = "Leonardo DiCaprio";

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
    double getL() const  {return L;}

    void setX(double x_)    {this->x=x_; updateL();}
    void setY(double y_)    {this->y=y_; updateL();}

    void updateL()  {this->L = sqrt(pow(this->x,2) + pow(this->y,2));}
    void normalize();

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
        output << "Vec pos : [" << v.getX() << "," << v.getY()  << "] =>  L :" << v.getL() << "\n";
        return output;
    }
    friend Vector operator+(Vector const&v1, Vector const& v2){
        double x_tmp = v1.getX() + v2.getX(); 
        double y_tmp = v1.getY() + v2.getY();
        Vector v = Vector(x_tmp,y_tmp);
        return v;
    }

};
class Actor{
public:
    Actor(std::string actorName_, std::string actorId_)
    {
        this->actorId =actorId_; 
        this->actorName =actorName_;
    }

    // -----------------------------------------------

    std::string actorId = "";
    std::string actorName = ""; 
    std::vector<std::string> commonMovies = {}; 
    int commonMovies_number = 0; 
    int allMovies = 0; 
    int actorSize = 0; 
    double springStiffness = 1;
    Vector pos,f_repulsive,f_attractive,f_displacement; 
    std::vector<std::string> connectedTo; 
    bool mainActor = false; 

    // -----------------------------------------------

    void computeRepulsiveForce(std::vector<Actor> &actors);
    void computeAttractiveForce(std::vector<Actor> &actors);
    void computeDisplacementForce();
    void displacePos();

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

void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors);
void actorListInit(std::vector<Actor> &actors);
void actorComputeForces(std::vector<Actor> &actors);
void printActorMap(std::vector<Actor> &actors);
