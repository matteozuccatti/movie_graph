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
    while(it<actors.begin()+MAX_ACTORS){
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

// Static variable initialization
int Node::total_nodes = 0;

std::vector<Node> get_sample_vector_nodes(){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);

    std::vector<Node> nodes(MAX_ACTORS);
    actorToNodes(actors,nodes);

    //printVectorNodes(nodes);

    return nodes; 
}

void updateLayout(std::vector<Node> &nodes){
    updateForces(nodes);
    updatePos(nodes);
    //printVectorNodes(nodes);
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
        it->f_fri = it->x_dot.invert().normalize().times(1e3);
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

                double true_dist = dist.getL() - it->size/2 - n->size;
                if(true_dist < 0.1)
                    true_dist = 0.1;

                it->f_ext += (it->x - n->x).times(5e2*(n->size+5)/true_dist);
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
    double dT = 0.005; 
    
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        it->x     = it->x     + it->x_dot.times(dT); 
        it->x_dot = it->x_dot + it->f_tot.times(dT);
    }
}

bool keepUpdating(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        if(it->x_dot.getL() > 11)
            return true;   
    }
    return false;
}

// --------------------------------------------------------------------------

void printVectorNodes(std::vector<Node> &nodes){
    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        std::cout << *it << "\n"; 
    }
}

// --------------------------------------------------------------------------

int scoreToSize(double score){
    int size = pow(score,1.7)/1e4;
    if (size<3)
        size = 3;
    return size;
}

double moviesToDistance(double common_movies){
    return 20 + 50/common_movies;
}

void actorToNodes(std::vector<Actor> &actors, std::vector<Node> &nodes){
    int i = 0; 

    std::sort(actors.begin(), actors.end());

    std::vector<Actor>::iterator a = actors.begin(); 
    std::vector<Node>::iterator  n = nodes.begin(); 

    while(i<MAX_ACTORS){
            n->size = scoreToSize(a->actorScore); 
            n->x0 = moviesToDistance(a->commonMovies_number); 

            double random_angle = (rand() % 300 +1)/100.0;
            n->x = Vector(n->x0*cos(random_angle), n->x0*sin(random_angle));

            n->name = a->actorName;
            n->common_movies = a->commonMovies;

            a++; 
            n++; 
            i++; 
    }
}

SColor colorIndex(int i){
    switch(i){
        case 0: 
            return SColor{139/255,0,0};
        case 1: 
            return SColor{178.0/255,34.0/255,34.0/255};
        case 2: 
            return SColor{255.0/255,0/255,0/255};
        case 3: 
            return SColor{255.0/255,99.0/255,71.0/255};
        case 4: 
            return SColor{205.0/255,92.0/255,92.0/255};
        case 5: 
            return SColor{233.0/255,150.0/255,122.0/255};
        case 6: 
            return SColor{255.0/255,160.0/255,122.0/255};
        case 7: 
            return SColor{255.0/255,69.0/255,0/255};
        case 8: 
            return SColor{255.0/255,140.0/255,0.0/255};
        case 9: 
            return SColor{255.0/255,215.0/255,0.0/255};
        case 10: 
            return SColor{218.0/255,165.0/255,32.0/255};
        case 11: 
            return SColor{154.0/255,205.0/255,50.0/255}; 
        case 12: 
            return SColor{107.0/255,155.0/255,45.0/255};
        case 13: 
            return SColor{173.0/255,252.0/255,47.0/255};
        case 14: 
            return SColor{0.0/255,120.0/255,0.0/255};
        case 15: 
            return SColor{34.0/255,140.0/255,34.0/255};
        case 16: 
            return SColor{50.0/255,205.0/255,50.0/255};
        case 17: 
            return SColor{0.0/255,250.0/255,154.0/255};
        case 18: 
            return SColor{102.0/255,205.0/255,170.0/255};
        case 19: 
            return SColor{32.0/255,178.0/255,171.0/255};
        case 20: 
            return SColor{0.0/255,139.0/255,139.0/255};
        case 21: 
            return SColor{0.0/255,255.0/255,240.0/255};
        case 22: 
            return SColor{70.0/255,130.0/255,180.0/255};
        case 23: 
            return SColor{30.0/255,120.0/255,240.0/255};
        case 24: 
            return SColor{0.0/255,0.0/255,140.0/255};
        case 25: 
            return SColor{0.0/255,0.0/255,255.0/255};
        case 26: 
            return SColor{32.0/255,178.0/255,170.0/255};
        case 27: 
            return SColor{138.0/255,43.0/255,230.0/255};
        case 28: 
            return SColor{139.0/255,0/255,139.0/255};
        case 29: 
            return SColor{255.0/255,0/255,255.0/255};
        case 30: 
            return SColor{210.0/255,105.0/255,30.0/255};
        default:
            std::cout << "Movie n." << i << "\n"; 
            return SColor{1,1,1};
    }
}

SColor getColorForMovie(std::string movieName, std::vector<std::pair<std::string, std::string>> &movies){
    for(int i=0; i<movies.size(); i++){
        if(movieName == movies[i].second)
            return colorIndex(i); 
    }
    std::cout << "No movie called " << movieName << "\n";
    return colorIndex(-1);
}








