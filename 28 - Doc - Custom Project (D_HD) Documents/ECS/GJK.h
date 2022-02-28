#pragma once

#include "Vector2.h"
#include "MinkowskiSum.h"
#include "Collider2D.h"

class GJK
{
public:
    bool TestCollision(Collider2D* convex1, Collider2D* convex2);
private:
    Vector2 CalcInitialDirection(Collider2D* convex1, Collider2D* convex2);
    bool Detect(MinkowskiSum& minkowskiSum, std::vector<Vector2>& simplex, Vector2& direction);

    // Determines whether the given simplex contains the origin.  If it does contain the origin,
    // then this method will return true.  If it does not, this method will update both the given
    // simplex and also the given search direction.
    bool CheckSimplex(std::vector<Vector2>& simplex, Vector2& direction);
};