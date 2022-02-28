#pragma once

#include "Collider2D.h"

class MinkowskiSum
{
public:
    MinkowskiSum(Collider2D* convex1, Collider2D* convex2)
        : convex1(convex1), convex2(convex2){}

    // Returns the farthest point in the Minkowski sum given the direction.
    Vector2 GetSupportPoint(Vector2 dir) {
        // get the farthest point in the given direction in convex1
        Vector2 point1 = convex1->GetFarthestPoint(dir);

        // get the farthest point in the opposite direction in convex2
        dir *= -1.0;
        Vector2 point2 = convex2->GetFarthestPoint(dir);

        // return the Minkowski sum point
        return point2.To(point1);
    }


private:
    Collider2D* convex1;
    Collider2D* convex2;
};
