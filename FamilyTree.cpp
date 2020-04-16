#include "FamilyTree.hpp"

namespace family{

    Tree::Tree(string name){
        this->root = name;
    }
    Tree Tree::addFather(string name, string father){
            return Tree("");
    }
    Tree Tree::addMother(string name, string mother){
            return Tree("");
    }
    void Tree::remove(string name){;
    }
    void Tree::display(){;
    }
    string Tree::relation(string name){
        return name;
    }
    string Tree::find(string relation){
        return relation;
    }
   
}