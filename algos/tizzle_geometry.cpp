#include <bits/stdc++.h>

using namespace std;

namespace geometry {
    constexpr long double PI =
            3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647l;
    constexpr long double precision = 1e-9;


    template<typename T>
    int getSign(const T value) {
        return fabs(value) < precision ? 0 : (value > 0 ? 1 : -1);
    }

    template<typename T>
    struct Point {
        T x, y;

        Point() noexcept : x(0), y(0) {
        }

        Point(T x, T y) noexcept(std::is_nothrow_copy_constructible_v<T>) : x(x), y(y) {
        }

        template<typename U>
        explicit Point(const Point<U> &other) : x(other.x), y(other.y) {
        }

        Point operator-() const {
            return {-x, -y};
        }

        Point &operator+=(const Point &other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Point &operator-=(const Point &other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Point &operator*=(const T &k) {
            x *= k;
            y *= k;
            return *this;
        }

        Point& operator/=(const T& k) {
            x /= k;
            y /= k;
            return *this;
        }

        friend Point operator+(const Point &lhs, const Point &rhs) {
            return Point(lhs) += rhs;
        }

        friend Point operator-(const Point &lhs, const Point &rhs) {
            return Point(lhs) -= rhs;
        }

        friend Point operator*(const Point &lhs, const T &k) {
            return Point(lhs) *= k;
        }

        friend Point operator*(const T &k, const Point &lhs) {
            return Point(lhs) *= k;
        }

        friend Point operator/(const Point &lhs, const T &k) {
            return Point(lhs) /= k;
        }

        friend T operator*(const Point &lhs, const Point &rhs) {
            return lhs.x * rhs.x + lhs.y * rhs.y;
        }

        friend T operator%(const Point &lhs, const Point &rhs) {
            return lhs.x * rhs.y - lhs.y * rhs.x;
        }

        friend long double len(const Point &p) {
            return hypot(p.x, p.y);
        }

        friend T len2(const Point &p) {
            return p.x * p.x + p.y * p.y;
        }

        friend long double polarAngle(const Point &p) {
            auto res = atan2(p.y, p.x);
            if (res < 0) {
                res += 2 * PI;
            }
            return res;
        }

        friend long double angle(const Point &lhs, const Point &rhs) {
            return polarAngle(Point(lhs * rhs, lhs % rhs));
        }

        friend Point getNormal(const Point &lhs) {
            return {-lhs.y, lhs.x};
        }

        friend istream &operator>>(istream &in, Point &p) {
            in >> p.x >> p.y;
            return in;
        }

        friend ostream &operator<<(ostream &out, const Point &p) {
            out << p.x << " " << p.y;
            return out;
        }
    };


    template<typename T>
    struct Segment {
        using point_type = Point<T>;

        point_type first, second;

        Segment(const point_type &first, const point_type &second) : first(first), second(second) {
        }

        // template<typename U>
        // Segment(const Point<U> &first, const Point<U> &second) : first(first), second(second) {
        // }

        friend auto len(const Segment &seg) {
            return len(seg.first - seg.second);
        }

        friend auto len2(const Segment &seg) {
            return len2(seg.first - seg.second);
        }
    };

    template<typename T>
    struct Ray {
        using point_type = Point<T>;

        point_type begin, direction;

        Ray(const point_type &begin, const point_type &to) : begin(begin), direction(to - begin) {
        }

        // template<typename U>
        // Ray(const Point<U> &begin, const Point<U> &direction) : begin(begin), direction(direction) {
        // }
    };

    template<typename T>
    struct Line {
        using point_type = Point<T>;

        point_type first, second;

        Line(const point_type &first, const point_type &second) : first(first), second(second) {
        }

        // template<typename U>
        // Line(const Point<U> &first, const Point<U> &second) : first(first), second(second) {
        // }

        point_type getDirection() const {
            return second - first;
        }
    };

    template<typename T>
    bool collinear(const Point<T> &lhs, const Point<T> &rhs) {
        return getSign(lhs % rhs) == 0;
    }

    template<typename T>
    bool contains(const Segment<T> &seg, const Point<T> &point) {
        return collinear(seg.second - seg.first, point - seg.first)
               && (seg.second - seg.first) * (point - seg.first) >= 0
               && (seg.first - seg.second) * (point - seg.second) >= 0;
    }

    template<typename T>
    bool contains(const Point<T> &point, const Segment<T> &seg) {
        return contains(point, seg);
    }

    template<typename T>
    bool contains(const Point<T> &point, const Ray<T> &ray) {
        return collinear(ray.direction, point - ray.begin) && ray.direction * (point - ray.begin) >= 0;
    }

    template<typename T>
    bool contains(const Ray<T> &ray, const Point<T> &point) {
        return contains(point, ray);
    }

    template<typename T>
    bool contains(const Point<T> &point, const Line<T> &line) {
        return collinear(line.getDirection(), point - line.first);
    }

    template<typename T>
    bool contains(const Line<T> &line, const Point<T> &point) {
        return contains(point, line);
    }

    template<typename T>
    bool isIntersect(const Segment<T> &lhs, const Segment<T> &rhs) {
        if (collinear(lhs.second - lhs.first, rhs.second - rhs.first)) {
            return contains(lhs, rhs.first) || contains(lhs, rhs.second);
        } {
            auto dir1 = lhs.second - lhs.first;
            auto leg1 = rhs.first - lhs.first;
            auto leg2 = rhs.second - lhs.first;
            if (getSign(dir1 % leg1) * getSign(dir1 % leg2) > 0) {
                return false;
            }
        } {
            auto dir1 = rhs.second - rhs.first;
            auto leg1 = lhs.first - rhs.first;
            auto leg2 = lhs.second - rhs.first;
            if (getSign(dir1 % leg1) * getSign(dir1 % leg2) > 0) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool isIntersect(const Ray<T> &ray, const Line<T> &line) {
        if (contains(ray.begin, line)) {
            return true;
        }
        if (collinear(ray.direction, line.getDirection())) {
            return false;
        }
        auto normal = getNormal(line.getDirection());
        if (normal * (line.first - ray.begin) < 0) {
            normal *= -1;
        }
        return normal * ray.direction > 0;
    }

    template<typename T>
    bool isIntersect(const Line<T> &line, const Ray<T> &ray) {
        return isIntersect(ray, line);
    }

    template<typename T>
    bool isIntersect(const Line<T> &line1, const Line<T> &line2) {
        if (collinear(line1.getDirection(), line2.getDirection())) {
            return contains(line1.first, line2);
        }
        return true;
    }

    template<typename T>
    bool isIntersect(const Ray<T> &lhs, const Ray<T> &rhs) {
        if (collinear(lhs.direction, rhs.direction)) {
            return contains(lhs.begin, rhs) || contains(rhs.begin, lhs);
        }
        return isIntersect(lhs, Line(rhs.begin, rhs.begin + rhs.direction)) &&
               isIntersect(rhs, Line(lhs.begin, lhs.begin + lhs.direction));
    }

    template<typename T>
    bool isIntersect(const Segment<T> &seg, const Ray<T> &ray) {
        if (collinear(ray.direction, seg.second - seg.first)) {
            return contains(seg.first, ray) || contains(seg.second, ray);
        }
        auto vec1 = seg.first - ray.begin;
        auto vec2 = seg.second - ray.begin;
        return getSign(ray.direction % vec1) * getSign(ray.direction % vec2) <= 0 && isIntersect(
                   ray, Line(seg.first, seg.second));
    }

    template<typename T>
    long double distance(const Point<T> &lhs, const Point<T> &rhs) {
        return len(lhs - rhs);
    }


    template<typename T>
    long double distance(const Point<T> &p, const Segment<T> &seg) {
        if ((seg.second - seg.first) * (p - seg.first) > 0 && (seg.first - seg.second) * (p - seg.second) > 0) {
            return fabs((seg.first - p) % (seg.second - p)) / len(seg.second - seg.first);
        }
        return min(distance(p, seg.first), distance(p, seg.second));
    }

    template<typename T>
    long double distance(const Segment<T> &lhs, const Point<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Segment<T> &lhs, const Segment<T> &rhs) {
        if (isIntersect(lhs, rhs)) {
            return 0;
        }
        return min({
            distance(lhs.first, rhs),
            distance(lhs.second, rhs),
            distance(rhs.first, lhs),
            distance(rhs.second, lhs)
        });
    }

    template<typename T>
    long double distance(const Point<T> &p, const Ray<T> &ray) {
        auto vec = p - ray.begin;
        if (vec * ray.direction < 0) {
            return len(p - ray.begin);
        }
        auto leg = ray.begin + ray.direction - p;
        return fabs(-vec % leg) / len(ray.direction);
    }

    template<typename T>
    long double distance(const Ray<T> &lhs, const Point<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Point<T> &p, const Line<T> &line) {
        if (getSign((line.first - line.second) % (p - line.second)) == 0) {
            return 0;
        }
        auto leg1 = line.first - p;
        auto leg2 = line.second - p;
        return fabs(leg1 % leg2) / len(line.first - line.second);
    }

    template<typename T>
    long double distance(const Line<T> &lhs, const Point<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Segment<T> &seg, const Ray<T> &ray) {
        if (isIntersect(seg, ray)) {
            return 0;
        }
        return min(min(distance(seg.first, ray), distance(seg.second, ray)), distance(ray.begin, seg));
    }

    template<typename T>
    long double distance(const Ray<T> &lhs, const Segment<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Segment<T> &lhs, const Line<T> &rhs) {
        if (getSign(rhs.getDirection() % (lhs.first - rhs.first)) * getSign(
                rhs.getDirection() % (lhs.second - rhs.first)) <= 0) {
            return 0;
        }
        return min(distance(lhs.first, rhs), distance(lhs.second, rhs));
    }

    template<typename T>
    long double distance(const Line<T> &lhs, const Segment<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Ray<T> &lhs, const Ray<T> &rhs) {
        if (isIntersect(lhs, rhs)) {
            return 0;
        }
        return min(distance(lhs.begin, rhs), distance(lhs, rhs.begin));
    }

    template<typename T>
    long double distance(const Ray<T> &lhs, const Line<T> &rhs) {
        return isIntersect(lhs, rhs) ? 0 : distance(lhs.begin, rhs);
    }

    template<typename T>
    long double distance(const Line<T> &lhs, const Ray<T> &rhs) {
        return distance(rhs, lhs);
    }

    template<typename T>
    long double distance(const Line<T> &lhs, const Line<T> &rhs) {
        return isIntersect(lhs, rhs) ? 0 : distance(lhs.first, rhs);
    }

    template<typename T>
    bool insideAngle(const Point<T>& o, const Point<T>& dir1, const Point<T>& dir2, const Point<T>& p) {
        auto po = p - o;
        return getSign(po % dir1) * getSign(po % dir2) <= 0 && getSign(dir1 % po) * getSign(dir1 % dir2) >= 0 &&
            getSign(dir2 % po) * getSign(dir2 % dir1) >= 0;
    }

    template<typename T>
    variant<monostate, Point<T>, Line<T>> intersection(const Line<T>& line1, const Line<T>& line2) {
        if (!isIntersect(line1, line2)) {
            return {};
        }
        auto dir1 = line1.getDirection();
        auto dir2 = line2.getDirection();
        if (collinear(dir1, dir2)) {
            return line1;
        }
        auto [a1, b1] = getNormal(dir1);
        auto c1 = -(a1 * line1.first.x + b1 * line1.first.y);
        auto [a2, b2] = getNormal(dir2);
        auto c2 = -(a2 * line2.first.x + b2 * line2.first.y);
        return Point((1.0l * b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1), -(1.0l * a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1));
    }

    using point = Point<long double>;
    using segment = Segment<long double>;
    using ray = Ray<long double>;
    using line = Line<long double>;
} // namespace geometry
