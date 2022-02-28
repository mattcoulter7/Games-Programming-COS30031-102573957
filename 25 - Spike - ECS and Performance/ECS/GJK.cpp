#include "GJK.h"

bool GJK::TestCollision(Collider2D* convex1, Collider2D* convex2){
    std::vector<Vector2> simplex;
    MinkowskiSum minkowskiSum(convex1, convex2);
    Vector2 direction = CalcInitialDirection(convex1, convex2);

    return Detect(minkowskiSum, simplex, direction);
}

Vector2 GJK::CalcInitialDirection(Collider2D* convex1, Collider2D* convex2)
{
    Vector2 dir = convex1->GetCenter().To(convex2->GetCenter());
    return dir;
}

bool GJK::Detect( MinkowskiSum& minkowskiSum, std::vector<Vector2>& simplex, Vector2& direction)
{
    // check for a zero direction vector
    if (Vector2::IsZero(direction))
    {
        direction = Vector2{ 1.0, 0.0 };
    }

    // add the first point
    simplex.push_back(minkowskiSum.GetSupportPoint(direction));

    // is the support point past the origin along d?
    if (Vector2::DotProduct(simplex[0], direction) <= 0.0) {
        return false;
    }

    // negate the search direction
    direction *= -1.0;
    // start the loop
    while (true) {
        if (Vector2::IsIND(direction)) {
            return false;
        }
        // always add another point to the simplex at the beginning of the loop
        simplex.push_back(minkowskiSum.GetSupportPoint(direction));

        // make sure that the last point we added was past the origin
        Vector2 lastPoint = simplex.back();
        if (Vector2::DotProduct(lastPoint, direction) <= 0.0) {
            // a is not past the origin so therefore the shapes do not intersect
            // here we treat the origin on the line as no intersection
            // immediately return with null indicating no penetration
            return false;
        }
        else {
            // if it is past the origin, then test whether the simplex contains the origin
            if (CheckSimplex(simplex, direction)) {
                // if the simplex contains the origin then we know that there is an intersection.
                // if we broke out of the loop then we know there was an intersection
                return true;
            }

            // if the simplex does not contain the origin then we need to loop using the new
            // search direction and simplex
        }
    }
}


bool GJK::CheckSimplex(std::vector<Vector2>& simplex, Vector2& direction) {
    // get the last point added (a)
    Vector2 a = simplex.back();

    // this is the same as -a
    Vector2 ao = a.ToOrigin();

    // check to see what type of simplex we have
    if (simplex.size() == 3)
    {
        // then we have a triangle
        Vector2 b = simplex[1];
        Vector2 c = simplex[0];

        // get the edges
        Vector2 ab = b - a;
        Vector2 ac = c - a;

        // get the edge normals
        Vector2 abPerp = Vector2::TripleProduct(ac, ab, ab);
        Vector2 acPerp = Vector2::TripleProduct(ab, ac, ac);

        // see where the origin is at
        float acLocation = Vector2::DotProduct(acPerp, ao);

        if (acLocation >= 0.0) {
            // the origin lies on the right side of A->C
            // because of the condition for the gjk loop to continue the origin
            // must lie between A and C so remove B and set the
            // new search direction to A->C perpendicular vector
            simplex.erase(simplex.begin() + 1);

            // this used to be direction.set(Vector.tripleProduct(ac, ao, ac));
            // but was changed since the origin may lie on the segment created
            // by a -> c in which case would produce a zero vector normal
            // calculating ac's normal using b is more robust
            direction = acPerp;
        }
        else {
            float abLocation = Vector2::DotProduct(abPerp, ao);

            // the origin lies on the left side of A->C
            if (abLocation < 0.0) {
                // the origin lies on the right side of A->B and therefore in the
                // triangle, we have an intersection
                return true;
            }
            else {
                // the origin lies between A and B so remove C and set the
                // search direction to A->B perpendicular vector
                simplex.erase(simplex.begin());

                // this used to be direction.set(Vector.tripleProduct(ab, ao, ab));
                // but was changed since the origin may lie on the segment created
                // by a -> b in which case would produce a zero vector normal
                // calculating ab's normal using c is more robust
                direction = abPerp;
            }
        }
    }
    else {
        // get the b point
        Vector2 b = simplex[0];
        Vector2 ab = b - a;

        // otherwise we have 2 points (line segment)
        // because of the condition for the gjk loop to continue the origin
        // must lie in between A and B, so keep both points in the simplex and
        // set the direction to the perp of the line segment towards the origin
        direction = Vector2::TripleProduct(ab, ao, ab);

        // check for degenerate cases where the origin lies on the segment
        // created by a -> b which will yield a zero edge normal
        if (direction.magnitude_sq() <= std::numeric_limits<float>::epsilon()) {
            // in this case just choose either normal (left or right)
            direction = Vector2::Left(ab);
        }
    }

    return false;
}