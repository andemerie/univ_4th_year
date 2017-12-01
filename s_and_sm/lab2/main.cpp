#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <random>
using namespace std;


int m = 0, r = 0;
double lmbda = 0;

double get_base_random() {
    static default_random_engine generator;
    static uniform_real_distribution<double> distribution(0, 1);
    return distribution(generator);
}

int get_bernoulli_value(const double p) {
    return get_base_random() <= p ? 1 : 0;
}

int *perform_bernoulli(const int size, const double p) {
    auto *bernoulli_array = new int [size];
    for (int i = 0; i < size; ++i) {
        bernoulli_array[i] = get_bernoulli_value(p);
    }
    return bernoulli_array;
}

double get_bernoulli_prob(const double p, const int x) {
    return pow(p, x) * pow(1 - p, 1 - x);
};

int *perform_geometric(const int size, const double p) {
    auto *geometric_array = new int [size];
    for (int i = 0; i < size; ++i) {
        geometric_array[i] = (int) ceil(log(get_base_random()) / log(1 - p));
    }
    return geometric_array;
}

double get_geometric_prob(const double p, const int x) {
    return p * pow(1 - p, x - 1);
};

int l_func(const double z) {
    return z <= 0 ? 0 : 1;
}

int factorial(const int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double binom_coefficient(const int n, const int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int *perform_binomial(const int size, const double p) {
    auto *binomial_array = new int [size];

    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += l_func(p - get_base_random());
        }
        binomial_array[i] = sum;
    }

    return binomial_array;
};

double get_binomial_prob(const double p, const int x) {
    return binom_coefficient(m, x) * pow(p, x) * pow(1 - p, m - x);
};

int *perform_pascal(const int size, const double p) {
    auto *pascal_array = new int [size];

    for (int i = 0; i < size; ++i) {
        int sum = 0, experiments_num = 0;
        while (sum < r) {
            sum += get_bernoulli_value(p);
            ++experiments_num;
        }
        pascal_array[i] = experiments_num - r;
    }

    return pascal_array;
};

double get_pascal_prob(const double p, const int x) {
    return binom_coefficient(x + r - 1, x) * pow(p, r) * pow(1 - p, x);
};

int *perform_poisson(const int size, const double p) {
    auto *poisson_array = new int [size];

    for (int i = 0; i < size; ++i) {
        double alpha = get_base_random();
        int j = 0;
        while (alpha >= exp(-lmbda)) {
            alpha *= get_base_random();
            ++j;
        }
        poisson_array[i] = j;
    }

    return poisson_array;
};

double get_poisson_prob(const double p, const int x) {
    return exp(-lmbda) * pow(lmbda, x) / factorial(x);
};

string test_with_pearson(map<int, double> &deltas, double (*get_probability)(const double, const int), const double p,
                         const double threshold, const int size, const int *array) {
    int intervals_num = 0;
    vector<double> probabilities;
    for ( ; intervals_num < deltas.size();  ++intervals_num) {
        const double probability = get_probability(p, intervals_num);
        if (probability <= threshold || probability > 1) {
            break;
        }
        probabilities.push_back(probability);
    }

    double frequencies[intervals_num] = {};
    for (int i = 0; i < size; ++i) {
        if (array[i] >= intervals_num) {
            continue;
        }
        ++frequencies[array[i]];
    }

    const double delta = deltas[intervals_num];
    double statistics = 0;
    for (int i = 0; i < intervals_num; ++i) {
        if (frequencies[i] == 0) {
            continue;
        }
        statistics += pow(frequencies[i] - size * probabilities[i], 2) / (size * probabilities[i]);
    }

    const string response_str = statistics < delta ? "Pearson test is passed." : "Pearson test failed.";
    return response_str;
}

void show_result(const string &distr_name, const int size, const int *array, const string &pearson_str) {
    cout << distr_name << ":" << endl << "[";
    for (int i = 0; i < size; ++i) {
        cout << array[i];
        if (i < size - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl;
        }
    }
    if (!pearson_str.empty()) {
        cout << pearson_str << endl;
    }
    cout << endl;
}

void run(int *(*perform_distr)(const int, const double), const int size, const double p, map<int, double> &deltas,
         double (*get_probability)(const double, const int), const double pearson_threshold, const string &distr_name) {
    int *distr_array = perform_distr(size, p);
    string pearson_str = test_with_pearson(deltas, get_probability, p, pearson_threshold, size, distr_array);
    show_result(distr_name, size, distr_array, pearson_str);
}

int main() {
    const int size = 1000;
    const double pearson_threshold = 0.01;

    ifstream in("../pearson_deltas.txt");
    string line;
    map<int, double> deltas;
    while (getline(in, line)) {
        istringstream iss(line);
        int key;
        double value;
        iss >> key >> value;
        deltas[key] = value;
    }

    cout << "Realizations of the discrete random variable (in the amount of " << size << ")," << endl
         << "obtained with the help of different distributions." << endl << endl;

    double p = 0.8;
    run(&perform_bernoulli, size, p, deltas, &get_bernoulli_prob, pearson_threshold, "Bernoulli distribution");

    p = 0.25;
    run(&perform_geometric, size, p, deltas, &get_geometric_prob, pearson_threshold, "geometric distribution");

    m = 6;
    p = 0.3333333;
    run(&perform_binomial, size, p, deltas, &get_binomial_prob, pearson_threshold, "binomial distribution");

    r = 4;
    p = 0.8;
    run(&perform_pascal, size, p, deltas, &get_pascal_prob, pearson_threshold, "Pascal distribution");

    lmbda = 0.3;
    run(&perform_poisson, size, 0, deltas, &get_poisson_prob, pearson_threshold, "Poisson distribution");

    return 0;
}
