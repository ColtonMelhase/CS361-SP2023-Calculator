#include <string>
#include "solve.cpp"
#include "storage.cpp"

class CalculusSolver {
    public:
        bool containsCalculus(std::string expr);
        void replaceCalculus(std::string &expr);
        double integral(Solver *solver, double a, double b, std::string expr, std::string var) {
            bool negate = false;
            if (a > b) {
                negate = true;
                std::swap(a, b);
            }

            double dx = (b - a)/10000; // Increase denominator for more precision
            double x = solver->storage.getVarValue(var);

            double sum = 0;
            for (double i = a; i < b; i = i + dx) {
                solver->storage.setVarValue(var, i);
                sum += solver->solve(expr);
            }
            sum *= dx;

            if (negate) {sum *= -1;}

            solver->storage.setVarValue(var, x);
            return sum;

        }
        double derivative(Solver *solver, std::string expr, std::string var) {
            double dx = 0.00005;

            double x = solver->storage.getVarValue(var);
            double xPlusH = x + dx;

            solver->storage.setVarValue(var, xPlusH);
            double F_xPlusH = solver->solve(expr);

            solver->storage.setVarValue(var, x);
            double F_x = solver->solve(expr);

            return (F_xPlusH - F_x) / dx;
        }
    private:

};