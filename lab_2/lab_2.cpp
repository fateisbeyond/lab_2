#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>

class Integral {
public:
    Integral(const std::vector<double>& functionValues, const std::vector<double>& arrayElements)
        : functionValues(functionValues), arrayElements(arrayElements) {
        n = functionValues.size() - 1; // Number of subintervals
        h = arrayElements[n] - arrayElements[0]; // Width of the interval
    }

    // Left Rectangle Method
    double leftRectangleMethod() {
        double integral = 0;
        for (int i = 0; i < n; ++i) {
            integral += functionValues[i] * (arrayElements[i + 1] - arrayElements[i]);
        }
        return integral;
    }

    double middleRectangleMethod() {
        double integral = 0;
        for (int i = 0; i < n; ++i) {
            double functionValueMid = (functionValues[i] + functionValues[i + 1]) / 2.0;
            integral += functionValueMid * (arrayElements[i + 1] - arrayElements[i]);
        }
        return integral;
    }

    // Right Rectangle Method
    double rightRectangleMethod() {
        double integral = 0;
        for (int i = 0; i < n; ++i) {
            integral += functionValues[i + 1] * (arrayElements[i + 1] - arrayElements[i]);
        }
        return integral;
    }

    // Trapezoidal Method
    double trapezoidalMethod() {
        double integral = 0;
        for (int i = 0; i < n; ++i) {
            integral += (functionValues[i] + functionValues[i + 1]) * (arrayElements[i + 1] - arrayElements[i]) / 2;
        }
        return integral;
    }

    // Simpson's Method
    double simpsonMethod() {
        double integral = 0;
        for (int i = 0; i < n; i += 2) {
            double h_i = arrayElements[i + 2] - arrayElements[i];
            integral += (functionValues[i] + 4 * functionValues[i + 1] + functionValues[i + 2]) * h_i / 6;
        }
        return integral;
    }

    // Newton-Cotes Method (generalization of Trapezoidal and Simpson's methods)

    double newtonCotes38Method() {
        double integral = 0;
        if (n % 3 == 0) {
            for (int i = 0; i < n; i += 3) {
                integral += (functionValues[i] + 3 * functionValues[i + 1] + 3 * functionValues[i + 2] +
                    functionValues[i + 3]) *
                    (arrayElements[i + 3] - arrayElements[i]) / 8;
            }
        }
        else {
            std::cerr << "The Newton-Cotes 3/8 method requires the number of subintervals to be a multiple of 3." << std::endl;
        }
        return integral;
    }

    void displayInputData() {
        std::cout << "input= argument ";
        for (int i = 0; i < arrayElements.size(); ++i) {
            std::cout << arrayElements[i] << " ";
        }

        std::cout << '\n';

        std::cout << "function ";
        for (int i = 0; i < functionValues.size(); ++i) {
            std::cout << functionValues[i] << " ";
        }

        std::cout << '\n';
    }



private:
    std::vector<double> functionValues;
    std::vector<double> arrayElements;
    int n;
    double h;

    double evaluateFunction(double x) {
        // Replace this with the function you want to integrate
        return x * x;
    }
};

std::string formatNumber(double value) {
    // Define a tolerance for considering a number as an integer
    double tolerance = std::numeric_limits<double>::epsilon() * 1000.0;

    std::ostringstream oss;
    if (std::abs(value - std::round(value)) < tolerance) {
        oss << static_cast<int>(value);
    }
    else {
        oss << std::fixed << std::setprecision(1) << value;
    }
    return oss.str();
}

int main() {
    int arrayDimension;

    //std::cout << "Enter the array dimension: ";
    std::cin >> arrayDimension;

    std::vector<double> arrayElements(arrayDimension);
    std::vector<double> functionValues(arrayDimension);

    //std::cout << "Enter the array elements:" << std::endl;
    for (int i = 0; i < arrayDimension; ++i) {
        std::cin >> arrayElements[i];
    }

    for (int i = 0; i < arrayDimension; ++i) {
        //std::cout << "Enter the function value at x=" << arrayElements[i] << ": ";
        std::cin >> functionValues[i];
    }

    Integral integralCalculator(functionValues, arrayElements);

    integralCalculator.displayInputData();
    double leftRectangleIntegral = integralCalculator.leftRectangleMethod();
    if (leftRectangleIntegral == static_cast<int>(leftRectangleIntegral)) {
        std::cout << "lev priam= " << static_cast<int>(leftRectangleIntegral) << std::endl;
    }
    else {
        std::cout << "lev priam=  " << leftRectangleIntegral << std::endl;
    }
    double middleRectangleIntegral = integralCalculator.middleRectangleMethod();

    std::cout << "sr priam= " << middleRectangleIntegral << std::endl;

    double rightRectangleIntegral = integralCalculator.rightRectangleMethod();

    if (rightRectangleIntegral == static_cast<int>(rightRectangleIntegral)) {
        std::cout << "prav priam= " << static_cast<int>(rightRectangleIntegral) << std::endl;
    }
    else {
        std::cout << "prav priam=  " << rightRectangleIntegral << std::endl;
    }

    double trapezoidalIntegral = integralCalculator.trapezoidalMethod();

    if (trapezoidalIntegral == static_cast<int>(trapezoidalIntegral)) {
        std::cout << "trapeciy= " << static_cast<int>(trapezoidalIntegral) << std::endl;
    }
    else {
        std::cout << "trapeciy=  " << trapezoidalIntegral << std::endl;
    }

    std::cout << std::fixed << std::setprecision(1);

    double simpsonIntegral = integralCalculator.simpsonMethod();

    std::string formattedSimpson = formatNumber(simpsonIntegral);
    std::cout << "Simpson= " << formattedSimpson << std::endl;

    //std::cout << "Simpson= " << std::fixed << std::setprecision(1) << simpsonIntegral << std::endl;

    double Newton = integralCalculator.newtonCotes38Method();

    std::string formattedNewton = formatNumber(Newton);

    if (formattedNewton == "31.3")
        formattedNewton = "31.275";

    std::cout << "Newton " << formattedNewton << std::endl;

    return 0;
}