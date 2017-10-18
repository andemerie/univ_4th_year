#include <iostream>
#include <random>
using namespace std;

void perform_geom_distr(const double p, const int size, int *geom_distr_array) {
    double random_array[size];
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0, 1);
    for (int i = 0; i < size; ++i) {
        random_array[i] = distribution(generator);
    }

    const double q = 1 - p;

    for (int i = 0; i < size; ++i) {
        geom_distr_array[i] = (int) ceil(log(random_array[i]) / log(q));
    }
}

int l_func(const double z) {
    return z <= 0 ? 0 : 1;
}

void perform_binom_distr(const int m, const double p, const int size, int *binom_distr_array) {
    double random_array[size * m];
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0, 1);
    for (int j = 0; j < size * m; ++j) {
        random_array[j] = distribution(generator);
    }

    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += l_func(p - random_array[i * m + j]);
        }

        binom_distr_array[i] = sum;
    }
};

void show_distribution_result(const string &distribution_name, const int size, const int *array) {
    cout << "Realizations of the discrete random variable (in the amount of " << size << ")," << endl
         << "obtained with the help of a " << distribution_name << ": " << endl
         << '[';
    for (int i = 0; i < size; ++i) {
        cout << array[i];
        if (i < size - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl;
        }
    }
}

int factorial(const int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double binom_coefficient(const int n, const int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

void retrieve_binom_probabilities(const int m, const double p, const int intervals_number, double *binom_probabilities) {
    for (int i = 0; i < intervals_number; ++i) {
        binom_probabilities[i] = binom_coefficient(m, i) * pow(p, i) * pow(1 - p, m - i);
    }
};

void test_with_pearson(const double *probabilities, const int intervals_number,
                       const double delta, const int size, const int *array, const string &for_output) {
    double frequencies[intervals_number] = {};
    for (int i = 0; i < size; ++i) {
        frequencies[array[i]]++;
    }

    double statistics = 0;
    for (int i = 0; i < intervals_number; ++i) {
        statistics += pow(frequencies[i] - size * probabilities[i], 2) / (size * probabilities[i]);
    }

    if (statistics < delta) {
        cout << for_output << ": Pearson test is passed." << endl;
    } else {
        cout << for_output << ": Pearson test failed." << endl;
    }
}

int main() {
    const int size = 1000;

    double p = 0.25;

    int geom_distr_array[size];
    perform_geom_distr(p, size, geom_distr_array);

    string geom_distr_string = "geometric distribution";
    show_distribution_result(geom_distr_string, size, geom_distr_array);
    cout << endl;

    const int m = 6;
    p = 0.3333333;

    int binom_distr_array[size];
    perform_binom_distr(m, p, size, binom_distr_array);

    string binom_distr_string = "binomial distribution";
    show_distribution_result(binom_distr_string, size, binom_distr_array);
    cout << endl;

    const int intervals_number = m + 1;
    const double pearson_delta = 12.596;

    double binom_probabilities[intervals_number];
    retrieve_binom_probabilities(m, p, intervals_number, binom_probabilities);

    test_with_pearson(binom_probabilities, intervals_number, pearson_delta, size, binom_distr_array, binom_distr_string);

    return 0;
}
