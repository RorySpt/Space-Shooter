#include"MyShape.h"

// From Real-time Collision Detection, p179.
bool b2AABB::RayCast(RayCastOutput* output, const RayCastInput& input) const
{
	double tmin = -DBL_MAX;
	double tmax = DBL_MAX;

	TC::Vector2D p = input.p1;
	TC::Vector2D d = input.p2 - input.p1;
	TC::Vector2D absD = Abs(d);

	TC::Vector2D normal;

	for (int32 i = 0; i < 2; ++i)
	{
		if (absD(i) < DBL_EPS)
		{
			// Parallel.
			if (p(i) < lowerBound(i) || upperBound(i) < p(i))
			{
				return false;
			}

		}
		else
		{
			double inv_d = 1.0f / d(i);
			double t1 = (lowerBound(i) - p(i)) * inv_d;
			double t2 = (upperBound(i) - p(i)) * inv_d;

			// Sign of the normal vector.
			double s = -1.0f;

			if (t1 > t2)
			{
				Swap(t1, t2);
				s = 1.0;
			}

			// Push the min up
			if (t1 > tmin)
			{
				normal.SetZero();
				normal(i) = s;
				tmin = t1;
			}

			// Pull the max down
			tmax = Min(tmax, t2);

			if (tmin > tmax)
			{
				return false;
			}
		}
	}

	// Does the ray start inside the box?
	// Does the ray intersect beyond the max fraction?
	if (tmin < 0.0f || input.maxFraction < tmin)
	{
		return false;
	}

	// Intersection.
	output->fraction = tmin;
	output->normal = normal;
	return true;
}