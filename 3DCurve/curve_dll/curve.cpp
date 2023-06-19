#pragma once

#include "pch.h"
#include "curve.h"

void createCurves(std::vector<std::shared_ptr<MyCurves::Curve>>& curves, int numberOfCurves)
{
    int var_TypeCurve{ 0 };
    
    std::srand(std::time(nullptr));

    for (int i = 0; i < numberOfCurves; i++)
    {
        var_TypeCurve = std::rand() % 3 + 1;//1;

        if (var_TypeCurve == MyCurves::CIRCLE)
            curves.push_back(std::make_shared<MyCurves::Circle>());

        if (var_TypeCurve == MyCurves::ELLIPSE)
            curves.push_back(std::make_shared<MyCurves::Ellipse>());

        if (var_TypeCurve == MyCurves::HELIX)
            curves.push_back(std::make_shared<MyCurves::Helix>());
    }
}