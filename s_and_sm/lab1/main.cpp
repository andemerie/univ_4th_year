#include <iostream>
#include <cmath>
#include <random>
using namespace std;

double deduct_by_module(double z, int M) {
    double integer_part;
    modf(z / M, &integer_part);
    return z - M * integer_part;
}

void perform_mcg(const int alpha_initial, const int beta, const int M, const int size, double *brv_array) {
    double alpha_asterisk = alpha_initial;
    for (int i = 0; i < size; i++) {
        alpha_asterisk = deduct_by_module(beta * alpha_asterisk, M);
        double alpha = alpha_asterisk / M;
        brv_array[i] = alpha;
    }
}

void perform_mmg(const int size, const double *beta_array, const double *gamma_array, double *result_array) {
    double V[size];
    for (int i = 0; i < size; i++) {
        V[i] = beta_array[i];
    }

    for (int i = 0; i < size; i++) {
        double integer_part;
        modf(gamma_array[i] * size, &integer_part);
        const auto random_index = (int) integer_part;
        result_array[i] = V[random_index];
        V[random_index] = beta_array[i + size];
    }
}

void show_generation_result(const string &generator_name, const int size, const double *array) {
    cout << "Realizations of the basic random variable (in the amount of " << size << ")," << endl
         << "obtained with the help of a " << generator_name << ": " << endl
         << '[';
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i <size - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl << endl;
        }
    }
}

int main() {
    const int size = 1000;

    const int m = 20;
    int alpha_initial, beta;
    alpha_initial = beta = (int) pow(2, m) + 3;

    const auto M = (int) pow(2, 31);

    double mcg_array[size];
    perform_mcg(alpha_initial, beta, M, size, mcg_array);

    string generator_name = "multiplicative congruential generator";
    show_generation_result(generator_name, size, mcg_array);

    double random_array[2 * size];
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0, 1);
    for (int i = 0; i < 2 * size; i++) {
        random_array[i] = distribution(generator);
    }

    double mmg_array[size];
    perform_mmg(size, random_array, mcg_array, mmg_array);

    generator_name = "MacLaren-Marsaglia generator";
    show_generation_result(generator_name, size, mmg_array);
    return 0;
}
