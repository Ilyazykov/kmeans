#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H

#include <vector>
#include <cmath>

template <typename T = double>
class Point {
    std::vector<T> coordinates;

public:
    Point() : coordinates() {}
    explicit Point(int size) : coordinates(size, 0) {}

    Point(const typename std::vector<T>::const_iterator& begin, const typename std::vector<T>::const_iterator& end) : coordinates(begin, end) {}
    Point(const std::istream_iterator<T>& begin, const std::istream_iterator<T>& end) : coordinates(begin, end) {}

    Point(const Point<T>& point) : coordinates(point.coordinates.begin(), point.coordinates.end()) {}
    Point(Point<T>&& point) noexcept : coordinates(std::move(point.coordinates)) {}


    Point& operator= (const Point<T>& point) {
        for (int i = 0; i < coordinates.size(); ++i) {
            coordinates[i] = point.coordinates[i];
        }

        return *this;
    }

    Point& operator= (Point<T>&& point) noexcept {
        coordinates = std::move(point.coordinates);

        return *this;
    }

    T get_distance(const Point<T>& another) const {
        int dimentions = coordinates.size();
        if (dimentions != another.coordinates.size()) {
            throw std::runtime_error("different dimentions for Point::get_distance");
        }

        T result = T();
#pragma omp parallel for reduction(+:result)
        for (int i = 0; i < dimentions; ++i) {
            result += (coordinates[i] - another.coordinates[i]) * (coordinates[i] - another.coordinates[i]);
        }

        return std::pow(result, 1.0/dimentions);
    }

    void zeroize()
    {
        for (int i = 0; i < coordinates.size(); ++i) {
            coordinates[i] = 0;
        }
    }

    int getDimention()
    {
        return coordinates.size();
    }

    friend Point<T>& operator+=(Point<T>& left, const Point<T>& right)
    {
#pragma omp parallel for
        for (int i = 0; i < left.coordinates.size(); ++i) {
            left.coordinates[i] += right.coordinates[i];
        }

        return left;
    }

    friend Point<T>& operator/=(Point<T>& left, int right)
    {
#pragma omp parallel for
        for (int i = 0; i < left.coordinates.size(); ++i) {
            left.coordinates[i] /= right;
        }

        return left;
    }

    friend bool operator< (const Point<T>& left, const Point<T>& right)
    {
        if (left.coordinates.size() != right.coordinates.size()) {
            return left.coordinates.size() < right.coordinates.size();
        }

        for (int i = 0; i < left.coordinates.size(); ++i) {
            if (left.coordinates[i] != right.coordinates[i]) {
                return left.coordinates[i] < right.coordinates[i];
            }
        }

        return true;
    }

    friend std::ostream& operator<< (std::ostream &out, const Point<T> &point)
    {
        for (auto i : point.coordinates) {
            out << i << ' ';
        }

        return out;
    }
};

#endif //KMEANS_POINT_H
