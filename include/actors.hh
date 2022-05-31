#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "SQL_parser.hh"

class Vector{
private:
    double x; 
    double y;
    double L;
public:
    Vector()
    {
        this->x = 0; 
        this->y = 0;
    }

    Vector(double x_, double y_) 
    {
        this->x = x_; 
        this->y = y_;
    }

    double getX() const  {return x;}
    double getY() const  {return y;}
    double getL() const  {return L;}

    void setX(double x_)    {this->x=x_; updateL();}
    void setY(double y_)    {this->y=y_; updateL();}
    void setL(double L_)    {this->L=L_;}

    void updateL()  {this->L = sqrt(pow(this->x,2) + pow(this->y,2));}

    void operator+( const Vector &v){
        this->setX(x + v.getX());
        this->setY(x + v.getY());
    }

    void operator-( const Vector &v){
        this->setX(x - v.getX());
        this->setY(x - v.getY());
    }

    bool operator==( const Vector &v){
        return( (this->getX()==v.getX()) && (this->getY()==v.getY()) );
    }
};

class Actor{
public:
    Actor(std::string actorName_, std::string actorId_)
    {
        this->actorId =actorId_; 
        this->actorName =actorName_;
    }

    std::string actorId = "";
    std::string actorName = ""; 
    std::vector<std::string> commonMovies = {}; 
    int commonMovies_number = 0; 
    int allMovies = 0; 
    int actorSize = 0; 
    Vector pos; 
    std::vector<std::string> connectedTo; 

    bool operator==(const Actor &a) const {
        return(this->actorId == a.actorId);
    }
    bool operator<(const Actor &a) const {
        return(this->allMovies > a.allMovies);
    }
};

void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors);
void movieCounter(std::vector<Actor> &actors);
void printActorMap(std::vector<Actor> &actors);