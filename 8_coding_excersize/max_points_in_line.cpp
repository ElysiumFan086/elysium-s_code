/**
 * Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 */

#include <map>
#include <vector>

struct Rational {
	int num;
	int den;

	Rational(int n, int d) : num(n), den(d) {}
	Rational() : num(0), den(1) {}

	bool operator==(const Rational& r) const {
		int n_temp_n1 = 0, n_temp_d1 = 0;
		int n_temp_n2 = 0, n_temp_d2 = 0;

		if (num > den) {
			n_temp_n1 = num - den;
			n_temp_d1 = den;
			if (r.num <= r.den)    return false;

			n_temp_n2 = r.num - r.den;
			n_temp_d2 = r.den;
		}
		else if (num < den) {
			n_temp_n1 = den - num;
			n_temp_d1 = num;
			if (r.num >= r.den)    return false;

			n_temp_n2 = r.den - r.num;
			n_temp_d2 = r.num;
		}
		else {
			return r.num == r.den;
		}

		long long int temp1 = static_cast<long long int>(n_temp_n1) * n_temp_d2;
		long long int temp2 = static_cast<long long int>(n_temp_d1) * n_temp_n2;

		return abs(temp1 - temp2) < 1e-6;
	}
};

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

/**
 * Self-defined functor for comparing key in map between rational data and integer.
 */
struct RationalComparable{
	bool operator()(const Rational &lhs, const Rational &rhs) const {
		long long int temp1 = static_cast<long long int>(lhs.num) * rhs.den;
		long long int temp2 = static_cast<long long int>(lhs.den) * rhs.num;

		return temp1 - temp2 < 0;
	}
};

int maxPoints(std::vector<Point>& points) {
	if (points.empty())        return 0;
	if (points.size() <= 2)    return points.size();

	int n_max_pt_nb  = 0;
	int n_same_pt_ct = 0;

	for (std::size_t i = 0; i < points.size(); ++i) {
		std::map<Rational, int, RationalComparable> map_count;
		n_same_pt_ct = 0;
		for (std::size_t j = 0; j < points.size(); ++j) {
			if (i == j)    continue;

			if (points[i].x == points[j].x && points[j].y == points[i].y)    n_same_pt_ct++;
			else if (points[i].x - points[j].x == 0 && points[j].y - points[i].y != 0) {
				map_count[Rational(INT_MAX, 1)]++;
			}
			else {
				map_count[Rational(points[j].y - points[i].y, points[j].x - points[i].x)]++;
			}
		}

		int n_temp_max = 0;
		for (auto itr = map_count.begin(); itr != map_count.end(); ++itr)
			if (n_temp_max < itr->second)    n_temp_max = itr->second;

		if (n_temp_max + n_same_pt_ct > n_max_pt_nb)
			n_max_pt_nb = n_temp_max + n_same_pt_ct;
	}

	return n_max_pt_nb + 1;
}