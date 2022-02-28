#include "PolygonCollider.h"

class MinkowskiSum
{
public:
    MinkowskiSum(PolygonCollider* col1, PolygonCollider* col2)
        : convex1(col1),convex2(col2)
    {
    }

    //! Returns the farthest point in the Minkowski sum given the direction.
    //!
    //! @param direction the search direction
    //! @return the point farthest in the Minkowski sum in the given direction
    Vector2 getSupportPoint(Vector2 direction) const {
        // get the farthest point in the given direction in convex1
        Vector2 point1 = convex1->FarthestPoint(direction);

        // get the farthest point in the opposite direction in convex2
        direction *= -1.0;
        Vector2 point2 = convex2->FarthestPoint(direction);

        // return the Minkowski sum point
        return point1 - point2;
    }


private:
    PolygonCollider* convex1;
    PolygonCollider* convex2;
};