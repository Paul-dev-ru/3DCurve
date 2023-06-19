#pragma once

#ifdef CURVEDLL_EXPORTS
#define CURVEDLL_API __declspec(dllexport)
#else
#define CURVEDLL_API __declspec(dllimport)
#endif

#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <memory>
#include <random>

namespace MyCurves
{
    enum CURVEDLL_API TypeCurve : int
    {
        UNDEFINED = 404,
        CIRCLE = 1,
        ELLIPSE = 2,
        HELIX = 3
    };


    struct CURVEDLL_API Point
    {
        double x;
        double y;
        double z;
    };

    class CURVEDLL_API Curve
    {
    public:
        virtual Point getPoint(double t) const = 0;
        virtual Point getDerivative(double t) const = 0;
        virtual TypeCurve getTypeCurve() const = 0;
    };

    double randomDoubleNumber(double min, double max)
    {
        return (double)(rand()) / RAND_MAX * (max - min) + min;
    }

    class CURVEDLL_API Circle : public Curve
    {
    public:
        Circle() 
        {
            minVal = 1.0;
            maxVal = 30.0;

            radius = randomDoubleNumber(minVal, maxVal);
        }

        Point getPoint(double t) const override
        {
            double x = radius * cos(t);
            double y = radius * sin(t);
            double z = 0.0;

            return { x, y, z };
        }

        Point getDerivative(double t) const override
        {
            double dx = -radius * sin(t);
            double dy = radius * cos(t);
            double dz = 0.0;

            return { dx, dy, dz };
        }

        TypeCurve getTypeCurve() const override
        {
            return CIRCLE;
        }

        double getRadius() const
        {
            return radius;
        }

    private:
        double radius;
        double minVal;
        double maxVal;
    };

    class CURVEDLL_API Ellipse : public Curve
    {
    public:
        Ellipse() 
        {
            minVal = 30.0;
            maxVal = 50.0;

            radiusX = randomDoubleNumber(minVal, maxVal);

            minVal = 10.0;
            maxVal = 25.0;

            radiusY = randomDoubleNumber(minVal, maxVal);
        }

        Point getPoint(double t) const override {
            double x = radiusX * cos(t);
            double y = radiusY * sin(t);
            double z = 0.0;

            return { x, y, z };
        }

        Point getDerivative(double t) const override
        {
            double dx = -radiusX * sin(t);
            double dy = radiusY * cos(t);
            double dz = 0.0;

            return { dx, dy, dz };
        }

        TypeCurve getTypeCurve() const override
        {
            return ELLIPSE;
        }

    private:
        double radiusX;
        double radiusY;
        double minVal;
        double maxVal;
    };

    class CURVEDLL_API Helix : public Curve
    {
    public:
        Helix()
        {
            minVal = 1.0;
            maxVal = 30.0;

            radius = randomDoubleNumber(minVal, maxVal);

            minVal = 1.0;
            maxVal = 5.0;

            step = randomDoubleNumber(minVal, maxVal);
        }

        Point getPoint(double t) const override
        {
            double x = radius * cos(t);
            double y = radius * sin(t);
            double z = step * t / (2 * M_PI);

            return { x, y, z };
        }

        Point getDerivative(double t) const override
        {
            double dx = -radius * sin(t);
            double dy = radius * cos(t);
            double dz = step / (2 * M_PI);

            return { dx, dy, dz };
        }

        TypeCurve getTypeCurve() const override
        {
            return HELIX;
        }

    private:
        double radius;
        double step;
        double minVal;
        double maxVal;
    };
}

extern "C" CURVEDLL_API void createCurves(std::vector<std::shared_ptr<MyCurves::Curve>>&curves, int numberOfCurves);