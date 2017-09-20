#include <iostream>
#include <cmath>
using namespace std;

double deduct_by_module(double z, int M) {
    double integer_part;
    modf(z / M, &integer_part);
    return z - M * integer_part;
}

void *perform_mcg(const int alpha_initial, const int beta, const int M, const int brv_number, double *brv_array) {
    double alpha_asterisk = alpha_initial;
    for (int i = 0; i < brv_number; i++) {
        alpha_asterisk = deduct_by_module(beta * alpha_asterisk, M);
        double alpha = alpha_asterisk / M;
        brv_array[i] = alpha;
    }
}

int main() {
    const int brv_number = 1000;

    const int m = 20;
    int alpha_initial, beta;
    alpha_initial = beta = (int) pow(2, m) + 3;

    const auto M = (int) pow(2, 31);

    double brv_array[brv_number];
    perform_mcg(alpha_initial, beta, M, brv_number, brv_array);

    cout << "Realizations of the basic random variable (in the amount of " << brv_number << ")," << endl
         << "obtained with the help of a multiplicative congruential generator: " << endl
         << '[';
    for (int i = 0; i < brv_number; i++) {
        cout << brv_array[i];
        if (i < brv_number - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl;
        }
    }
    return 0;
}
