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



// ======================================================================== //
//                              VECTOR CLASS                                //
// ======================================================================== //

void Vector::normalize(){
    this->updateL();
    this->x = this->getX() / this->getL();
    this->y = this->getY() / this->getL();
    this->updateL();
}

void Vector::invert(){
    this->setX(-this->getX());
    this->setY(-this->getY());
}

Vector Vector::times(double m){
    return Vector(this->getX()*m, this->getY()*m);
}


// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //





// ======================================================================== //
//                               NODE CLASS                                 //
// ======================================================================== //

void Node::evaluateF_ext(){

}

void Node::evaluateF(){
    evaluateF_ext();
    f_tot =  x.times(k * (x0-(x.getL()))) + x_dot.times(-c) + f_ext;
    //f_tot = f_tot.times(1/100);
}

void euler_method(Node &node){

    if(!node.euler_complete){
        double dT = 0.1; 
        node.evaluateF(); 

        Vector new_x     = node.x     + node.x_dot.times(dT); 
        Vector new_x_dot = node.x_dot + node.f_tot.times(dT);

        node.x     = new_x; 
        node.x_dot = new_x_dot;

        
        if(isnan(node.x.getX())){
            std::cout << "WARNING : nan \n";
            node.euler_complete = true;
        }
        
        if(node.x_dot.getL() < 0.00001){
            std::cout << "STOP SLOW \n";
            node.euler_complete = true;
        }
        
        /*
        if(node.x.getL() < 1.5)
            node.euler_complete = true;
        */
    }
}

void euler_method(std::vector<Node> &nodes){
    std::vector<Node>::iterator it = nodes.begin();

    while(it!=nodes.end()){
        euler_method(*it); 
        it++;
    }
}

void testEuler(){
    Node node_test; 
    while(!node_test.euler_complete){
        euler_method(node_test);
        std::cout << node_test;
    }
}