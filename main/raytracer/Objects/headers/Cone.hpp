#ifndef CONE_H
#define CONE_H
#include "objectbase.hpp"

namespace RT
{
    class Cone : public RT::ObjectBase
    {
    private:
        
    public:
        Cone(/* args */);
        ~Cone() override;
        // function to test each section
        bool TestIntersectioons(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;
    };
    
   
    
} // namespace RT

#endif