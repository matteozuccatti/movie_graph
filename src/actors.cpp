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

Vector Vector::normalize(){
    this->updateL();
    return Vector( this->getX() / this->getL(),
                   this->getY() / this->getL() );
}

Vector Vector::invert(){
    return Vector( (-this->getX()),
                   (-this->getY()));
}

Vector Vector::times (double m) const{
    return Vector(this->getX()*m, this->getY()*m);
}


// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //





// ======================================================================== //
//                               NODE CLASS                                 //
// ======================================================================== //

void Node::evaluateF_ext(std::vector<Node> &nodes){
    std::vector<Node>::iterator it = nodes.begin(); 
    this->f_ext = Vector(0,0);

    while(it!=nodes.end()){
        Vector dist_vec = it->x - this->x; 
        double dist_mod = dist_vec.getL();

        if(dist_mod>0){
            this->f_ext += dist_vec.normalize().times(1e3/pow(dist_mod,2));
        }

        it++;
    }
    //std::cout << "f_repulsive :" << this->f_ext;
}

void Node::evaluateF(std::vector<Node> &nodes){
    f_tot =  (x.normalize()).times(k * (x0-(x.getL()))) - x_dot.times(c) + f_ext;
    //std::cout << " f_spring: " <<  x.normalize().times(k * (x0-(x.getL()))) << " f_damper: " << x_dot.times(c).invert() << "\n";
    
}

void euler_method(std::vector<Node> &nodes, Node &node){

    double dT = 0.1; 
    node.x     = node.x     + node.x_dot.times(dT); 
    node.x_dot = node.x_dot + node.f_tot.times(dT);

}

void compute_forces(std::vector<Node> &nodes, Node &node){
    node.evaluateF_ext(nodes);
    node.evaluateF(nodes);
}

void compute_graph_layout(std::vector<Node> &nodes){

    std::vector<Node>::iterator it = nodes.begin();

    // FIRST RUN
    while(it!=nodes.end()){
        compute_forces(nodes,*it);
        it++; 
    }
    it = nodes.begin();

    while(it!=nodes.end()){
        euler_method(nodes,*it); 
        it++;
    }
    it = nodes.begin();


    // GO UNTIL EVERY NODE IS SLOW ENOUGH
    while(!stop_euler(nodes)){

        while(it!=nodes.end()){
           compute_forces(nodes,*it);
           it++; 
        }
        it = nodes.begin();

        while(it!=nodes.end()){
            euler_method(nodes,*it); 
            it++;
        }
        it = nodes.begin();
    }
    std::cout << "\nFULL STOP\n";
}

/*
    Stop when all of the nodes have small enough velocity; 
*/
bool stop_euler(std::vector<Node> &nodes){ 
    /*
    std::vector<Node>::iterator it = nodes.begin();
    while(it!=nodes.end()){
        if(it->x_dot.getL() > 0.0001)
            return false; 
        it++;
    }
    return true;
    */

    Vector f_glob = Vector(0,0);
    std::vector<Node>::iterator it = nodes.begin();
    while(it!=nodes.end()){
        f_glob += it->f_tot; 
        it++;
    }

    std::cout << "F_GLOB: " << f_glob << "\n"; 
    if(f_glob.getL() < 1.5e-9)
        return true;
    return false;

}

void testEuler(){
    Node node_test; 
    std::vector<Node> nodes = {node_test};
    int k = 0;
    while(!node_test.euler_complete){
        std::cout << "it:" << k << " ";
        euler_method(nodes,node_test);
        std::cout << node_test << "\n";
        k++;

    }
}