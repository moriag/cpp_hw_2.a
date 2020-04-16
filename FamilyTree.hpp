#include <string>
using namespace std;
namespace family{
    class Tree{
        string root;
        Tree* father;
        Tree* mother;
        public:
        Tree(string name);
        Tree addFather(string name, string father);
        Tree addMother(string name, string mother);
        void remove(string name);
        void display();
        string relation(string name);
        string find(string relation);
    };
}