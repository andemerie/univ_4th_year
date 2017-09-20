#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
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
        if (i < size - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl;
        }
    }
}

void get_frequencies(const int size, const double *array, const int intervals_number, double *frequencies) {
    double sorted_array[size];
    for (int i = 0; i < size; i++) {
        sorted_array[i] = array[i];
    }
    sort(sorted_array, sorted_array + size);

    double step = 1.0 / intervals_number;
    double upper_boundary;
    int j = 0;
    for (int i = 0; i < size; i++) {
        upper_boundary = (j + 1) * step;
        if (sorted_array[i] <= upper_boundary) {
            frequencies[j]++;
            continue;
        }
        j++;
        frequencies[j]++;
    }
}

void test_with_pearson(const int intervals_number, const double delta, const int size, const double *array, const string &for_output) {
    double frequencies[intervals_number] = {};
    get_frequencies(size, array, intervals_number, frequencies);

    double probability = 1.0 / intervals_number;

    double statistics = 0;
    for (double frequency : frequencies) {
        statistics += pow(frequency - size * probability, 2) / (size * probability);
    }

    if (statistics < delta) {
        cout << for_output << ": Pearson test is passed." << endl;
    } else {
        cout << for_output << ": Pearson test failed." << endl;
    }
}

void test_with_kolmogorov(const double delta, const int size, const double *array, const string &for_output) {
    double empirical_distribution[size];
    for (int i = 0; i < size; i++) {
        empirical_distribution[i] = (float) (i + 1) / size;
    }

    double sorted_array[size];
    for (int i = 0; i < size; i++) {
        sorted_array[i] = array[i];
    }
    sort(sorted_array, sorted_array + size);

    double for_statistics[size];
    for (int i = 0; i < size; i++) {
        for_statistics[i] = abs(empirical_distribution[i] - sorted_array[i]);
    }

    double statistics = *max_element(for_statistics, for_statistics + size);

    if (statistics * sqrt(size) < delta) {
        cout << for_output << ": Kolmogorov test is passed." << endl;
    } else {
        cout << for_output << ": Kolmogorov test failed." << endl;
    }
}

void test_for_moments_coincidence(const double delta, const int size, const double *array, const string &for_output) {
    const double mean = 1.0 / 2;
    double mean_sampling = 0;
    for (int i = 0; i < size; i++) {
        mean_sampling += array[i];
    }
    mean_sampling /= size;
    const double random_deviation1 = mean_sampling - mean;

    const double normalization_factor1 = sqrt(12 * size);
    if (normalization_factor1 * abs(random_deviation1) < delta) {
        cout << for_output << ": test for moments coincidence using mean is passed." << endl;
    } else {
        cout << for_output << ": test for moments coincidence using mean failed." << endl;
    }

    const double dispersion = 1.0 / 12;
    double dispersion_sampling = 0;
    for (int i = 0; i < size; i++) {
        dispersion_sampling += pow(array[i] - mean_sampling, 2);
    }
    dispersion_sampling /= size - 1;
    const double random_deviation2 = dispersion_sampling - dispersion;

    const double normalization_factor2 = (size - 1) /
            (size * sqrt(0.0056 / size + 0.0028 / pow(size, 2) - 0.0083 / pow(size, 3)));
    if (normalization_factor2 * abs(random_deviation2) < delta) {
        cout << for_output << ": test for moments coincidence using dispersion is passed." << endl;
    } else {
        cout << for_output << ": test for moments coincidence using dispersion failed." << endl;
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
    cout << endl;

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
    cout << endl;

    const int intervals_number = 30;
    const double pearson_delta = 42.577;
    const double kolmogorov_delta = 1.36;
    const double mc_delta = 3;

    string for_output = "mcg";
    test_with_pearson(intervals_number, pearson_delta, size, mcg_array, for_output);
    test_with_kolmogorov(kolmogorov_delta, size, mcg_array, for_output);
    test_for_moments_coincidence(mc_delta, size, mcg_array, for_output);
    cout << endl;

    for_output = "mmg";
    test_with_pearson(intervals_number,pearson_delta, size, mmg_array, for_output);
    test_with_kolmogorov(kolmogorov_delta, size, mmg_array, for_output);
    test_for_moments_coincidence(mc_delta, size, mmg_array, for_output);
    cout << endl;
    return 0;
}
