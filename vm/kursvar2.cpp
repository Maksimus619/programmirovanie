#include <iostream>
#include <vector>
#include <iomanip>

// Параметры модели
struct Params {
    double alphaI, alphaE, beta, kappa, rho, mu, gamma;
    int N; // Общее количество населения
};

// Основные переменные модели
struct Variables {
    double S, E, I, R, D;
};

// Функция для обновления переменных согласно SEIR-D модели
void seirDModel(Variables& vars, const Params& params, double dt) {
    double newS = vars.S - dt * (params.alphaI * vars.S * vars.I / params.N + params.alphaE * vars.S * vars.E / params.N) + dt * params.gamma * vars.R;
    double newE = vars.E + dt * (params.alphaI * vars.S * vars.I / params.N + params.alphaE * vars.S * vars.E / params.N) - dt * (params.kappa + params.rho) * vars.E;
    double newI = vars.I + dt * params.kappa * vars.E - dt * (params.beta + params.mu) * vars.I;
    double newR = vars.R + dt * params.beta * vars.I + dt * params.rho * vars.E - dt * params.gamma * vars.R;
    double newD = vars.D + dt * params.mu * vars.I;

    // Обновление переменных
    vars.S = newS;
    vars.E = newE;
    vars.I = newI;
    vars.R = newR;
    vars.D = newD;
}

int main() {
    // Инициализация параметров
    Params params = {0.999, 0.999, 0.042, 0.952, 0.999, 0.0188, 0.0, 1000000};

    // Инициализация начальных значений переменных
    Variables vars = {999000, 800, 100, 100, 0};

    // Временной интервал и шаг по времени (dt)
    double t = 0.0, T = 90.0, dt = 0.1;

    // Вывод заголовков для столбцов
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Day\tSusceptible\tExposed\tInfected\tRecovered\tDeceased\n";

    // Цикл по времени от 0 до 90 дней
    for (int day = 0; t <= T; day++) {
        std::cout << t << "\t" << vars.S << "\t" << vars.E << "\t" << vars.I << "\t\t" << vars.R << "\t\t" << vars.D << "\n";
        seirDModel(vars, params, dt);
        t += dt;
    }

    return 0;
}
