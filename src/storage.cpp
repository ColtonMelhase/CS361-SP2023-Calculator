#include <map>
#include <string>

class VarStorage {
    public:

        //Default constructor which initializes with values of e and pi
        VarStorage() {
            vars["e"] = 2.71828183;
            vars["pi"] = 3.14159265;
        }
        void setVarValue(std::string key, double val);  // set value of variable ex: x = 5 : setVarValue("x", 5)
        double getVarValue(std::string key);            // get value of variable ex: getVarValue("x") returns 5
        bool contains(std::string key);                 // returns true/false if the map already contains a variable name (may be needed if we want to warn
                                                        // the user that they have redefined/overwritten an already defined variable for example)
    private:
        std::map<std::string, double> vars;
};

void VarStorage::setVarValue(std::string key, double val) {
    vars[key] = val;
}

double VarStorage::getVarValue(std::string key) {
    return vars.at(key);
}

bool VarStorage::contains(std::string key) {
    return vars.count(key);
}

/*
int main() {
    VarStorage store;

    //testing set variable feature a = 20
    store.setVarValue("a", 20);

    //redefining a
    store.setVarValue("a", 5.625);
    //defining b
    store.setVarValue("b", 30.5);

    //get variable value
    printf("\nThe value of variable 'a' is %f", store.getVarValue("a"));
    printf("\nThe value of variable 'b' is %f", store.getVarValue("b"));
    printf("\nThe value of variable 'e' is %f", store.getVarValue("e"));
    printf("\nThe value of variable 'pi' is %f", store.getVarValue("pi"));
}
*/