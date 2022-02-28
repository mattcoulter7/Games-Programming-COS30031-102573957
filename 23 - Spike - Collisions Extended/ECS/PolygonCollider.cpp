#include <cassert>

#include "PolygonCollider.h"

float INV_3 = 1.0 / 3.0;
Vector2 PolygonCollider::GetCenter() {
    size_t size = worldPts.size();

    // check for empty list
    if (size <= 0) {
        assert("Empty set of points");
    }

    // check for list of one point
    if (size == 1)
    {
        return worldPts[0];
    }

    // get the average center
    Vector2 ac;
    for (uint32_t i = 0; i < size; i++)
    {
        Vector2 p = worldPts[i];
        ac += p;
    }

    ac *= (1.0 / size);

    // otherwise perform the computation
    Vector2 center;
    float area = 0.0;

    // loop through the vertices
    for (uint32_t i = 0; i < size; i++)
    {
        // get two vertices
        Vector2 p1 = worldPts[i];
        Vector2 p2 = i + 1 < size ? worldPts[i + 1] : worldPts[0];
        p1 -= ac;
        p2 -= ac;

        // perform the cross product (yi * x(i+1) - y(i+1) * xi)
        float d = Vector2::CrossProduct(p1, p2);

        // multiply by half
        float triangleArea = 0.5 * d;

        // add it to the total area
        area += triangleArea;

        // area weighted centroid
        // (p1 + p2) * (D / 3)
        // = (x1 + x2) * (yi * x(i+1) - y(i+1) * xi) / 3
        // we will divide by the total area later
        center += (p1 + p2) * INV_3 * triangleArea;
    }

    // check for zero area
    if (abs(area) <= std::numeric_limits<float>::epsilon())
    {
        // zero area can only happen if all the points are the same point
        // in which case just return a copy of the first
        return worldPts[0];
    }

    // finish the centroid calculation by dividing by the total area
    center *= (1.0 / area);
    center += ac;

    // return the center
    return center;
};
Vector2 PolygonCollider::GetFarthestPoint(Vector2 dir) {
    // set the farthest point to the first one
    Vector2 point = worldPts[0];

    // prime the projection amount
    float max = Vector2::DotProduct(dir, worldPts[0]);

    // loop through the rest of the vertices to find a further point along the axis
    size_t size = worldPts.size();
    for (uint32_t i = 1; i < size; i++)
    {
        // get the current vertex
        Vector2 v = worldPts[i];

        // project the vertex onto the axis
        float projection = Vector2::DotProduct(dir, v);

        // check to see if the projection is greater than the last
        if (projection > max)
        {
            // otherwise this point is the farthest so far so clear the array and add it
            point = v;

            // set the new maximum
            max = projection;
        }
    }

    return point;
};