#ifndef KMEANS_KMEANS_H
#define KMEANS_KMEANS_H

#include <vector>
#include "Point.h"
#import "omp.h"

template <typename T>
std::vector<Point<T>> init_centers(const std::vector<Point<T>>& points, int groupsNumber)
{
    typename std::vector<Point<T>>::const_iterator begin = points.begin();
    typename std::vector<Point<T>>::const_iterator end = points.begin() + groupsNumber;

    return std::vector<Point<T>>(begin, end);
}

template <typename T>
bool change_groups(const std::vector<Point<T>>& points, const std::vector<Point<T>>& centers, std::vector<int>& groups)
{
    bool is_last_iteration = true;

#pragma omp parallel for
    for (int point_number = 0; point_number < points.size(); ++point_number) {
        int min_distance_group = 0;
        T min_distance = points[point_number].get_distance(centers[0]);

        for (int i = 1; i < centers.size(); ++i) {
            T current_distence = points[point_number].get_distance(centers[i]);
            if (current_distence < min_distance) {
                min_distance = current_distence;
                min_distance_group = i;
            }
        }

    #pragma omp critical
        if (groups[point_number] != min_distance_group) {
            is_last_iteration = false;
        }

        groups[point_number] = min_distance_group;
    }

    return is_last_iteration;
}

template <typename T>
void change_centers(const std::vector<Point<T>>& points, const std::vector<int>& groups, std::vector<Point<T>>& centers)
{
#pragma omp parallel for
    for (int i = 0; i < centers.size(); ++i) {
        centers[i].zeroize();
    }

    std::vector<int> center_numbers(centers.size(), 0);

#pragma omp parallel
    {
        std::vector<Point<T>> centers_private(centers.size(), Point<T>(centers[0].getDimention()));
        std::vector<int> center_numbers_private(centers.size(), 0);

    #pragma omp for
        for (int i = 0; i < points.size(); ++i) {
            centers_private[groups[i]] += points[i];
            center_numbers_private[groups[i]]++;
        }

    #pragma omp critical
        for (int j = 0; j < centers.size(); ++j) {
            centers[j] += centers_private[j];
            center_numbers[j] += center_numbers_private[j];
        }
    }

#pragma omp parallel for
    for (int j = 0; j < centers.size(); ++j) {
        centers[j] /= center_numbers[j];
    }
}

template <typename T>
std::vector<Point<T>> kmeans(const std::vector<Point<T>>& points, int groupsNumber)
{
    std::vector<Point<T>> centers = init_centers(points, groupsNumber);

    // TODO refactoring: it will be better to move groups to extended point class as field
    std::vector<int> groups(points.size());
    bool is_last_iteration = change_groups(points, centers, groups);

    while (!is_last_iteration) {
        change_centers(points, groups, centers);
        is_last_iteration = change_groups(points, centers, groups);
    }

    return centers;
}

#endif //KMEANS_KMEANS_H
