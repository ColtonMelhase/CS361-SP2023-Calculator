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
    vars[key] = val;
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

    //redefining a
    store.setVarValue("a", 5.625);
    store.setVarValue("b", 30.5);

    //get variable value
    printf("\nThe value of variable 'a' is %f", store.getVarValue("a"));
    printf("\nThe value of variable 'b' is %f", store.getVarValue("b"));
}