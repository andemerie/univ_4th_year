from random import gauss, random
from math import tan, pi, atan, log, pow, exp, sqrt


def perform_cauchy(size, median, mode):
    distr_list = []
    for i in range(size):
        gauss_value1 = gauss(0, 1)
        gauss_value2 = gauss(0, 1)
        ksi = gauss_value1 / gauss_value2
        x = median + mode * tan(pi * (ksi - 0.5))
        distr_list.append(x)
    return distr_list


def perform_logistic(size, mean, standart_deviation):
    distr_list = []
    for i in range(size):
        y = random()
        x = mean + standart_deviation * log(y / (1 - y))
        distr_list.append(x)
    return distr_list


def show_distr_result(distr_name, distr_list):
    print('Realizations of the discrete random variable (in the amount of ' +
          str(len(distr_list)) + '),')
    print('obtained with the help of ' + distr_name + ': ')
    print(distr_list)
    return


def get_empirical(x, sorted_list):
    size = len(sorted_list)
    sum = 0
    for element in sorted_list:
        sum += 1 if element <= x else 0
    sum /= size
    return sum


def get_cauchy(x, median, mode):
    return 0.5 + 1 / pi * atan((x - median) / mode)


def get_logistic(x, mean, standart_deviation):
    return pow(1 + exp(-(x - mean) / standart_deviation), -1)


def test_with_kolmogorov(distr_list, get_model, parameter1, parameter2, delta, for_output):
    size = len(distr_list)

    sorted_list = sorted(distr_list)

    for_statistics = []
    for x in range(int(sorted_list[0]), int(sorted_list[size - 1])):
        empirical_distr = get_empirical(x, sorted_list)
        model_distr = get_model(x, parameter1, parameter2)
        for_statistics.append(abs(empirical_distr - model_distr))

    statistics = max(for_statistics)

    if statistics * sqrt(size) < delta:
        print(for_output + ': Kolmogorov test is passed.')
    else:
        print(for_output + ': Kolmogorov test failed.')

    return


SIZE = 1000

MEDIAN = 1
MODE = 2

cauchy_list = perform_cauchy(SIZE, MEDIAN, MODE)
cauchy_name = 'Cauchy distribution'
show_distr_result(cauchy_name, cauchy_list)
print()

MEAN = 2
STANDART_DEVIATION = 3

logistic_list = perform_logistic(SIZE, MEAN, STANDART_DEVIATION)
logistic_name = 'logistic distribution'
show_distr_result(logistic_name, logistic_list)
print()

DELTA = 1.36

test_with_kolmogorov(cauchy_list, get_cauchy, MEDIAN, MODE, DELTA, cauchy_name)
test_with_kolmogorov(logistic_list, get_logistic, MEAN, STANDART_DEVIATION, DELTA, logistic_name)
