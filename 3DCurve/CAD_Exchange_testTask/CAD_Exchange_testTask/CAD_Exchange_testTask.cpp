#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <random>
#include <chrono>
#include "curve.h"

#define NUM_THREADS 8

bool compareCircles(const std::shared_ptr<MyCurves::Circle>& circle1, const std::shared_ptr<MyCurves::Circle>& circle2)
{
    return circle1->getRadius() < circle2->getRadius();
}

int partition(std::vector<std::shared_ptr<MyCurves::Circle>>& circles, int low, int high)
{
    double pivot = circles[high]->getRadius();
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (circles[j]->getRadius() < pivot)
            std::swap(circles[++i], circles[j]);
    }

    std::swap(circles[i + 1], circles[high]);
    return (i + 1);
}

void quickSort(std::vector<std::shared_ptr<MyCurves::Circle>>& circles, int low, int high)
{
    if (low < high) 
    {
        int pivotIndex = partition(circles, low, high);

        quickSort(circles, low, pivotIndex - 1);
        quickSort(circles, pivotIndex + 1, high);
    }
}

int main()
{
    std::vector<std::shared_ptr<MyCurves::Curve>> curves;
    std::vector<std::shared_ptr<MyCurves::Circle>> circles;
    
    createCurves(curves, 400000);

    for (const auto& curve : curves)
        if (curve->getTypeCurve() == MyCurves::CIRCLE)
            circles.push_back(std::dynamic_pointer_cast<MyCurves::Circle>(curve));

    //for (const auto& circle : circles)
    //    std::cout << "Circle Radius before sorted: " << circle->getRadius() << std::endl;

    quickSort(circles, 0, circles.size() - 1);

    double totalRadiusSum{ 0.0 };
    
    omp_set_num_threads(NUM_THREADS);

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for reduction(+:totalRadiusSum)
    for (int i = 0; i < circles.size(); i++)
    {
        totalRadiusSum += circles[i]->getRadius();
    }        

    auto stop_thread = std::chrono::high_resolution_clock::now();
    auto duration_programm = std::chrono::duration_cast<std::chrono::milliseconds>(stop_thread - start);

    std::cout << "work cycle 'for' for radius sum:\n"
        << duration_programm.count() << " ms\n";

    //for (const auto& circle : circles)
    //    std::cout << "Circle Radius after sorted: " << circle->getRadius() << std::endl;

    std::cout << "Total Radius Sum: " << totalRadiusSum << std::endl;

    return 0;
}