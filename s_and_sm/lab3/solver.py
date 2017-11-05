from random import random
from math import log, sqrt, exp, erf, tan, pi, atan, pow


def get_standart_gauss():
    return sum([random() for _ in range(12)]) - 6


def get_gauss_value(mean, variance):
    return mean + sqrt(variance) * get_standart_gauss()


def perform_gauss(size, mean, variance):
    distr_list = []
    for _ in range(size):
        x = get_gauss_value(mean, variance)
        distr_list.append(x)
    return distr_list


def perform_exponential(size, lmbda):
    distr_list = []
    for _ in range(size):
        x = - 1 / lmbda * log(random())
        distr_list.append(x)
    return distr_list


def perform_lognormal(size, m, variance):
    distr_list = []
    for _ in range(size):
        gauss = get_gauss_value(log(m), variance)
        distr_list.append(exp(gauss))
    return distr_list


def perform_cauchy(size, median, mode):
    distr_list = []
    for _ in range(size):
        standart_gauss1 = get_standart_gauss()
        standart_gauss2 = get_standart_gauss()
        ksi = standart_gauss1 / standart_gauss2
        x = median + mode * tan(pi * (ksi - 0.5))
        distr_list.append(x)
    return distr_list


def perform_logistic(size, mean, param):
    distr_list = []
    for _ in range(size):
        y = random()
        x = mean + param * log(y / (1 - y))
        distr_list.append(x)
    return distr_list


def get_gauss(x, mean, variance):
    return 0.5 * (1 + erf((x - mean) / sqrt(2 * variance)))


def get_lognormal(x, m, variance):
    return 0.5 + 0.5 * erf((log(x) - log(m)) / sqrt(2 * variance))


def get_exponential(x, lmbda):
    return 1 - exp(- lmbda * x)


def get_cauchy(x, median, mode):
    return 0.5 + 1 / pi * atan((x - median) / mode)


def get_logistic(x, mean, param):
    return pow(1 + exp(-(x - mean) / param), -1)


def test_with_kolmogorov(distr_list, get_model, params, delta):
    size = len(distr_list)
    sorted_list = sorted(distr_list)

    for_statistics = []
    for i, x in enumerate(sorted_list):
        empirical_distr = (i + 1) / size
        model_distr = get_model(x, **params)
        for_statistics.append(abs(empirical_distr - model_distr))

    statistics = max(for_statistics)
    response_str = 'Kolmogorov test is passed.' if statistics * sqrt(size) < delta else 'Kolmogorov test failed.'
    return response_str


def show_result(distr_name, distr_list, kolmogorov_str):
    print('{}:\n{}\n{}\n'.format(distr_name, distr_list, kolmogorov_str))
    return


def run(perform_distr, size, params, get_distr, delta, distr_name):
    distr_list = perform_distr(size, **params)
    kolmogorov_str = test_with_kolmogorov(distr_list, get_distr, params, delta)
    show_result(distr_name, distr_list, kolmogorov_str)
    return


SIZE = 1000
DELTA = 1.36

print('Realizations of the discrete random variable (in the amount of {}),\n\
obtained with the help of different distribitions.\n'.format(SIZE))

gauss_params = {'mean': 1, 'variance': 9}
run(perform_gauss, SIZE, gauss_params, get_gauss, DELTA, 'gaussian distribution')

lognormal_params = {'m': 1, 'variance': 9}
run(perform_lognormal, SIZE, lognormal_params, get_lognormal, DELTA, 'lognormal distribution')

exponential_params = {'lmbda': 9}
run(perform_exponential, SIZE, exponential_params, get_exponential, DELTA, 'exponential distribution')

cauchy_params = {'median': 1, 'mode': 2}
run(perform_cauchy, SIZE, cauchy_params, get_cauchy, DELTA, 'Cauchy distribution')

logistic_params = {'mean': 2, 'param': 3}
run(perform_logistic, SIZE, logistic_params, get_logistic, DELTA, 'logistic distribution')
