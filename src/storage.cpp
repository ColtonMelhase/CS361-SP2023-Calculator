#include <map>
#include <string>

class VarStorage {
    public:
        void setVarValue(std::string key, double val);
        double getVarValue(std::string key);
        bool contains(std::string key);
    private:
        std::map<std::string, double> vars;
};

void VarStorage::setVarValue(std::string key, double val) {
    if(!contains(key)) {
        vars[key] = val;
    }
    else {
        printf("\nVariable already defined\n");
    }
}

double VarStorage::getVarValue(std::string key) {
    return vars.at(key);
}

bool VarStorage::contains(std::string key) {
    return vars.count(key);
}

int main() {
    VarStorage store;

    //testing set variable feature a = 20
    store.setVarValue("a", 20);

    //testing to make sure not to redefine already defined variables
    store.setVarValue("a", 5);

    //get variable value
    printf("The value of variable'a' is %f", store.getVarValue("a"));
}