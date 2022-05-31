#pragma once 

#include <string>
#include <vector>
#include <iostream>

#include "SQL_parser.hh"

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