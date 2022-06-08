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
                //it->f_ext += proj.times(n->size);
                
               
                
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