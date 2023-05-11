#include "headers/Cone.hpp"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <vector>
#include <stdlib.h>

RT::Cone::Cone(/* args */)
{
}

RT::Cone::~Cone()
{
}

bool RT::Cone::TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    // to find the interstaction point we need to solve equatoin at^2 + b +c = 0
    // in the giveen a = (vx^2 + vy^2 - vz^2) &&  b = 2 * ( VxPx + VyPy -pzvz) && c = Px^2 + Py^2 - pz^2
    // in local coords and unit CYLINDER we have r = 1;
    // c = px^2 + py^2 - 1
    // smallest t is the distance between camera and point of intersection

    RT::Ray bckRay = m_trasformMatrix.Apply(castRay, RT::BCKTFORM);

    qbVector<double> v = bckRay.m_lab;
    v.Normalize();

    qbVector<double> p = bckRay.m_point1;
    qbVector<double> poi;

    double solution[3] = {100e6, 100e6, 100e6};

    bool is_valide1 = false, is_valide2 = false, is_valide3 = false;
    double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0) - std::pow(v.GetElement(2), 2.0);
    double b = 2.0 * ((p.GetElement(0) * v.GetElement(0)) + (p.GetElement(1) * v.GetElement(1)) - (p.GetElement(2) * v.GetElement(2)));
    double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - std::pow(p.GetElement(2), 2.0);

    double numSQRT = sqrtf(std::pow(b, 2) - 4.0 * a * c);

    std::array<qbVector<double>, 3> intpoints;

    // if numSQRT is negative then the ray those not intersecte with the object
    if (numSQRT > 0)
    {
        solution[0] = (-b + numSQRT) / (2 * a);
        solution[1] = (-b - numSQRT) / (2 * a);

        intpoints.at(0) = p + (solution[0] * v);
        intpoints.at(1) = p + (solution[1] * v);

        if (solution[0] > 0 && intpoints.at(0).GetElement(2) < 1 && (intpoints.at(0).GetElement(2) > 0.0))
            is_valide1 = true;
        else
            solution[0] = 100e6;
        if (solution[1] > 0 && intpoints.at(1).GetElement(2) < 1 && (intpoints.at(1).GetElement(2) > 0.0))
            is_valide2 = true;
        else
            solution[1] = 100e6;
    }

    // if vector hase no z values of very close to 0 no need to test for interstaction
    // with caps cus the vector is paraller to the plan
    if (!CloseEnough(v.GetElement(2), 0.0))
    {
        // calculat the intersection with the caps as a plan
        solution[2] = (p.GetElement(2) - 1) / -v.GetElement(2);
        intpoints.at(2) = p + (solution[2] * v);

        if (solution[2] > 0.0 && (sqrtf(std::pow(intpoints.at(2).GetElement(0), 2) + std::pow(intpoints.at(2).GetElement(1), 2)) < 1.0))
            is_valide3 = true;
        else
            solution[2] = 100e6;
    }

    if (!is_valide1 && !is_valide2 && !is_valide3)
        return false;

    // find nearst intersection point
    int i = 0;
    int minIndex = 0;
    double min = 10e6;

    while (i < 3)
    {
        if (solution[i] < min)
        {
            min = solution[i];
            minIndex = i;
        }
        i++;
    }

    poi = intpoints.at(minIndex);
    // check if ther intersaction with a Cylinder or cap
    if (minIndex < 2)
    {
        // int with Cylinder
        intPoint = m_trasformMatrix.Apply(poi, RT::FWDTFORM);
        // calculat the local normal
        qbVector<double> localOrijin = qbVector<double>{std::vector<double>{0, 0, 0}};
        qbVector<double> GbOrigin = m_trasformMatrix.Apply(localOrijin, RT::FWDTFORM);

        qbVector<double> ORGnormal = qbVector<double>
        {
            std::vector<double>{
                poi.GetElement(0),
                poi.GetElement(1),
                0.0}};

            localNormal = m_trasformMatrix.Apply(ORGnormal, RT::FWDTFORM) - GbOrigin;
            localNormal.Normalize();

            localColor = m_baseColor;
            // calculating u,v cords for cylinder
            double x = poi.GetElement(0);
            double y = poi.GetElement(1);

            double u = atan2(y, x);
            double v = poi.GetElement(2);

            // calculating u,v cords for end caps
            u_v_cords.SetElement(0, u / M_PI);
            u_v_cords.SetElement(1, v);
            return true;
        }
        else
        {
            // int with caps
            if (CloseEnough(v.GetElement(2), 0.0))
                return false;

            // check if int inside the disk
            if (sqrtf(std::pow(poi.GetElement(0), 2) + std::pow(poi.GetElement(1), 2)) >= 1.0)
                return false;

            intPoint = m_trasformMatrix.Apply(poi, RT::FWDTFORM);

            // localnormal;
            qbVector<double> localOrigin{std::vector<double>{0, 0, 0}};
            qbVector<double> normalVector{std::vector<double>{0, 0, 1.0}};

            qbVector<double> GBO = m_trasformMatrix.Apply(localOrigin, RT::FWDTFORM);
            localNormal = m_trasformMatrix.Apply(normalVector, RT::FWDTFORM) - GBO;
            localNormal.Normalize();

            localColor = m_baseColor;
            
            // calculating u,v cords for end caps
            u_v_cords.SetElement(0, poi.GetElement(0));
            u_v_cords.SetElement(1, poi.GetElement(1));

            return true;
        }

        return (false);
    }
