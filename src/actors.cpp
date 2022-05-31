#include "../include/actors.hh"

void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors){

    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root"; // user
    mysqlD.password = "1L0ck3D97"; // the password for the database
    mysqlD.database = "movies";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    const char *sql_query1 = "select all person_name,person_id from person where person_id in (select person_id from movie_cast where movie_id in (\"";
    const char *sql_query2 = "\"));";

     std::vector<Actor>::iterator it = actors.begin(); 
     std::string actorName, actorId;

    for(int i=0; i<movieVec.size(); i++){

        const char *movie_id = movieVec[i].first.c_str(); 
        char sql_query_tmp[250];
        std::strcpy(sql_query_tmp,sql_query1); 
        std::strcat(sql_query_tmp,movie_id); 
        std::strcat(sql_query_tmp,sql_query2); 

        const char *sql_query = sql_query_tmp; 

        res = mysql_perform_query(con, sql_query);

        while ((row = mysql_fetch_row(res)) != NULL){
            actorName = row[0];
            actorId   = row[1];
            Actor act(actorName, actorId); 

            it = std::find(actors.begin(), actors.end(), act);
            if(it==actors.end()){
                // New actor
                act.commonMovies.push_back(movieVec[i].second);
                actors.push_back(act);
            }else{
                // Exsistent
                it->commonMovies.push_back(movieVec[i].second);
            }
        }
    }
    // clean up the database result
    mysql_free_result(res);
    // close database connection
    mysql_close(con);

    actorListInit(actors);
    actorComputeForces(actors);
}

void actorListInit(std::vector<Actor> &actors){

    // Initialize SQL connection 
    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root"; // user
    mysqlD.password = "1L0ck3D97"; // the password for the database
    mysqlD.database = "movies";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    // SQL query 
    const char *sql_query1 = "select movie_id from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_id = \"";
    const char *sql_query2 = "\"));"; 

    // Run through the list of actors 
    std::vector<Actor>::iterator it = actors.begin(); 
    while(it != actors.end()){
        // -- SPECIFIC ACTOR -- 

        // Create query for specific actor 
        const char *actorId = it->actorId.c_str(); 
        char sql_query_tmp[250];
        std::strcpy(sql_query_tmp,sql_query1); 
        std::strcat(sql_query_tmp,actorId); 
        std::strcat(sql_query_tmp,sql_query2); 
        const char *sql_query = sql_query_tmp; 

        // allMovies 
        res = mysql_perform_query(con, sql_query);

        // Count how many movies the specific actor has
        while ((row = mysql_fetch_row(res)) != NULL){
            it->allMovies++;
        }

        // commonMovies_number
        it->commonMovies_number = it->commonMovies.size();
        it++; 

        // actors connected to the specific actor
        it->connectedTo.push_back(main_actor);

    }
}

void printActorMap(std::vector<Actor> &actors){

    std::sort(actors.begin(), actors.end());

    std::cout << std::endl; 

    std::cout.width(26); std::cout<< std::left<< "Actor's Name ";
    std::cout.width(3); std::cout<< std::left<< "TOT  ";
    std::cout.width(25); std::cout<< std::left<< "| Common movies";
    std::cout<< "\n\n===================================================\n\n";

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it!=actors.end()){
        std::cout.width(26); std::cout<< std::left << it->actorName << "(";
        std::cout.width(2);  std::cout<< std::right << it->allMovies; 
        std::cout << ") | "; 

        for(int i=0; i<it->commonMovies.size(); i++){
            if(i!=0)
                std::cout.width(33); std::cout << "";
            std::cout << it->commonMovies[i] << "\n"; 
        }
        it++;
    }
}

void actorComputeForces(std::vector<Actor> &actors){

    std::vector<Actor>::iterator it = actors.begin(); 

    while(it!=actors.end()){
        it->computeRepulsiveForce(actors);
        it->computeAttractiveForce(actors);
        it->computeDisplacementForce();
        it++;
    }
}

void testFunction(){
    std::vector<Actor> actors;
    // Constructor 
    Actor a0 = {"00", "Actor MAIN"};
    Actor a1 = {"01", "Actor 1"};
    Actor a3 = {"02", "Actor 2"};
    Actor a2 = {"03", "Actor 3"};
    // Common movies 
    a1.commonMovies_number = 1; 
    a1.commonMovies_number = 2;
    a3.commonMovies_number = 2;
    // Actor size 
    a1.actorSize = 10; a1.springStiffness=10;  
    a2.actorSize = 20; a2.springStiffness=20;  
    a3.actorSize = 10; a3.springStiffness=10;  
    // Connected to 
    a1.connectedTo.push_back("Actor MAIN");
    a2.connectedTo.push_back("Actor MAIN");
    a3.connectedTo.push_back("Actor MAIN");

    // Push actors into vector 
    actors.push_back(a1); 
    actors.push_back(a2); 
    actors.push_back(a3); 


}

// ======================================================================== //
//                              VECTOR CLASS                                //
// ======================================================================== //

void Vector::normalize(){
    this->updateL();
    this->x = this->getX() / this->getL();
    this->y = this->getY() / this->getL();
    this->updateL();
}



// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //

void Actor::computeRepulsiveForce(std::vector<Actor> &actors){

    std::vector<Actor>::iterator it = actors.begin(); 

    while(it!=actors.end()){
        if(it->actorId != this->actorId){
            
        }
        it++;
    }
}

void Actor::computeAttractiveForce(std::vector<Actor> &actors){

    std::vector<Actor>::iterator it = actors.begin(); 

    while(it!=actors.end()){
        if(it->actorId != this->actorId){

        }
        it++;
    }
}

void Actor::computeDisplacementForce(){
    this->f_displacement += this->f_repulsive;
    this->f_displacement += this->f_attractive;

}

