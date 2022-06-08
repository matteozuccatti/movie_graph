#include "../include/actors.hh"


// ======================================================================== //
//                              VECTOR CLASS                                //
// ======================================================================== //


Vector Vector::normalize(){
    if(this->getL()<1e-10)
        return Vector(0.0,0.0);
    return Vector( this->getX() / this->getL(),
                   this->getY() / this->getL() );
}

Vector Vector::invert(){
    return Vector( (-this->getX()),
                   (-this->getY()));
}

Vector Vector::times (double m) const{
    return Vector( this->getX()*m, 
                   this->getY()*m );
}

double Vector::dot(Vector &v){
    return (this->getX()*v.getX()) + (this->getY()*v.getY());
}

// ======================================================================== //
//                              ACTOR CLASS                                 //
// ======================================================================== //


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
        // Run through all the movies of the main actor
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
            Actor act(actorId, actorName); 

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
    const char *sql_query1 = "select movie_id,popularity from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_id = \"";
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
            it->actorScore += std::strtod(row[1], NULL);
        }

        // commonMovies_number
        it->commonMovies_number = it->commonMovies.size();
        it++; 
    }
}

void printActorMap(std::vector<Actor> &actors){

    std::sort(actors.begin(), actors.end());

    std::cout << std::endl; 

    std::cout.width(26); std::cout<< std::left<< "Actor's Name ";
    std::cout.width(8); std::cout<< std::left<< "SCORE  ";
    std::cout.width(25); std::cout<< std::left<< "| Common movies";
    std::cout<< "\n\n===================================================\n\n";

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it!=actors.end()){
        std::cout.width(26); std::cout<< std::left << it->actorName << "(";
        std::cout.width(8);  std::cout<< std::right << it->actorScore; 
        std::cout << ") | "; 

        for(int i=0; i<it->commonMovies.size(); i++){
            if(i!=0)
                std::cout.width(37); std::cout << "";
            std::cout << it->commonMovies[i] << "\n"; 
        }
        it++;
    }
}


// ======================================================================== //
//                               NODE CLASS                                 //
// ======================================================================== //



// -----------------------
// Static variable initialization
int Node::total_nodes = 0;

std::vector<Node> get_sample_vector_nodes(){

    Node n1,n2,n3,n4; 
    Node n5,n6,n7,n8; 
    n1.x0 = 350;    n1.x = Vector( 300,  0);
    n2.x0 = 650;    n2.x = Vector( 300,  50);       n2.size = 50;
    n3.x0 = 450;    n3.x = Vector(-100,   50);      n3.size = 20;
    n4.x0 = 450;    n4.x = Vector(-300,-50);
    n5.x0 = 250;    n5.x = Vector( 300,  0);
    n6.x0 = 250;    n6.x = Vector( 300,  50);       n6.size = 20;
    n7.x0 = 350;    n7.x = Vector(-100,   -50);     n7.size = 40;
    n8.x0 = 450;    n8.x = Vector(-300,-50);
    std::vector<Node> nodes = {n1,n2,n3,n4,n5,n6,n7,n8}; 
    
    return nodes; 
}


void updateLayout(std::vector<Node> &nodes){
   updateForces(nodes);
   updatePos(nodes);
}

void computeSpringForces(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->f_spr = it->x.normalize().times(it->k * (it->x0 - it->x.getL()));
    }
}

void computeDamperForces(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->f_damp = it->x_dot.invert().normalize().times(it->c * it->x_dot.getL());
    }
}

void computeFrictionForces(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->f_fri = it->x_dot.invert().normalize().times(1000);
    }
}

void computeExternalForces(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->f_ext = Vector(0.0,0.0);
        for(std::vector<Node>::iterator n=nodes.begin(); n!=nodes.end(); n++){
            if(!(*it == *n)){
                Vector dist = it->x - n->x; 
                Vector norm = Vector(it->x.getX(), -it->x.getY()).normalize();  // unit vector normal to the spring direction
                Vector proj = norm.times(norm.dot(dist)); 

                if((it->x-n->x).getL() < 1){
                    it->x += norm;
                }
                it->f_ext += (it->x - n->x).times(5e2*(n->size+10)/((it->x-n->x).getL()));
            }
        }
    }
}

void computeTotForces(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->f_tot = it->f_spr + it->f_damp + it->f_fri + it->f_ext; 
    }
}

void updateForces(std::vector<Node> &nodes){
    computeSpringForces(nodes);
    computeDamperForces(nodes);
    computeExternalForces(nodes);
    computeFrictionForces(nodes);
    computeTotForces(nodes);
}

void updatePos(std::vector<Node> &nodes){
    double dT = 0.01; 
    
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->x     = it->x     + it->x_dot.times(dT); 
        it->x_dot = it->x_dot + it->f_tot.times(dT);
    }
}

// --------------------------------------------------------------------------

void printVectorNodes(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        std::cout << *it << "\n"; 
    }
}