#include <string>

class CalculusSolver {
    public:
        bool containsCalculus(std::string expr);
        void replaceCalculus(std::string &expr);
        double integral(double a, double b, std::string expr, double d);
        double derivative(std::string expr, double post);
    private:

};