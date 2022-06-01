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
    //actorComputeForces(actors);
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

    std::vector<Actor>::iterator it;
    long double iteration = 1;  

    while((new_epsilon >= espilon_min) && (iteration < max_iteration)){
        it = actors.begin();

        //std::cout << " * COMPUTING FORCES\n";
        while(it!=actors.end()){
            it->computeRepulsiveForce(actors);
            it->computeAttractiveForce(actors);
            it->computeDisplacementForce();
            it++;
        }

        //std::cout << " * COMPUTING POSITION\n";
        it = actors.begin();
        while(it!=actors.end()){
            it->displacePos(iteration);
            it->printActor();
            std::cout << "cooling : " << cooling_factor(iteration);
            it++;
        }

        iteration++;
    }
    std::cout << "MINIMUM iteration : " << iteration << " MINIMUM epsilon : " << new_epsilon << std::endl; 
}

std::vector<Actor> testFunction(){
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
    a0.actorSize = 35; a0.mainActor = true;
    a1.actorSize = 15; a1.springStiffness=idealSpringL;  
    a2.actorSize = 15; a2.springStiffness=idealSpringL;  
    a3.actorSize = 15; a3.springStiffness=idealSpringL;  
    // Connected to 
    a1.connectedTo.push_back("Actor MAIN");
    a2.connectedTo.push_back("Actor MAIN");
    a3.connectedTo.push_back("Actor MAIN");
    // Initial pos
    a0.pos = Vector(0,0); 
    a1.pos = Vector(50,50); 
    a2.pos = Vector(-50,50); 
    a3.pos = Vector(50,-50);

    // Push actors into vector
    actors.push_back(a0); 
    actors.push_back(a1); 
    actors.push_back(a2); 
    actors.push_back(a3); 

    return actors;
}

void printActorVec(std::vector<Actor> &actors){
    std::vector<Actor>::iterator it = actors.begin(); 

    while(it!=actors.end()){
        it->printActor();
        it++;
    }
    std::cout << std::endl;
}

double cooling_factor(double long t){
    double tmp_ret = 1.0/t; 
    if (abs(tmp_ret) < 0.001){
        return 0.001;
    }else{
        return tmp_ret;
    }
    
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

void Vector::inverse(){
    this->setX(-this->getX());
    this->setY(-this->getY());
}



// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //

void Actor::computeRepulsiveForce(std::vector<Actor> &actors){
    if (this->mainActor)
        return;

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it!=actors.end()){
        if(it->actorId != this->actorId && !it->mainActor){
            Vector pv_pu = it->pos - this->pos;
            pv_pu.updateL(); 
            double mod = pv_pu.getL()+0.1;
            pv_pu.normalize();
            this->f_repulsive += pv_pu * (10.0 / pow(mod,3)); 
        }
        it++;
    }
}

void Actor::computeAttractiveForce(std::vector<Actor> &actors){
    if (this->mainActor)
        return;

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it!=actors.end()){

        if (it->mainActor){
            Vector pu_pv = (this->pos - it->pos); 
            pu_pv.inverse();
            pu_pv.updateL();
            double mod = pu_pv.getL()+0.1;
            pu_pv.normalize();
            this->f_attractive += pu_pv * (1.0 *mod); 
        }

        it++;
    }
}

void Actor::computeDisplacementForce(){
    if (this->mainActor)
        return;
    this->f_displacement = this->f_repulsive + this->f_attractive;
}

void Actor::displacePos(long double iter){
    if (this->mainActor)
        return;
    Vector displacement_pos = this->f_displacement * cooling_factor(iter);
    displacement_pos.updateL();
    double displacement     = displacement_pos.getL();

    if (displacement > new_epsilon){
        new_epsilon = displacement;
        //std::cout << "*********** NEW MINIMUM ************* \n"; 
        //std::cout << "new_epsilon : " << new_epsilon << " min_epsilon : " << espilon_min << "\n";
    }

    //std::cout << "minimum displacement : " << new_epsilon << std::endl;
    this->pos += displacement_pos;
}

void Actor::resetForces(){
    this->f_attractive = Vector(0.0,0.0); 
    this->f_repulsive = Vector(0.0,0.0);
}

void Actor::printActor(){
    std::cout << " Name: ";
    std::cout.width(12); std::cout << std::left << actorName;

    std::cout << " Main: ";  
    std::cout.width(0); std::cout << std::left << mainActor;

    std::cout << " f_rep: ";  
    std::cout.width(4); std::cout << std::left << f_repulsive.getL();

    std::cout << " f_att: ";  
    std::cout.width(4); std::cout << std::left << f_attractive.getL();

    std::cout << " POS: ";  
    std::cout.width(10); std::cout << std::left << "[" << pos.getX() << "," << pos.getY() << "]";



    std::cout << std::endl;
}

