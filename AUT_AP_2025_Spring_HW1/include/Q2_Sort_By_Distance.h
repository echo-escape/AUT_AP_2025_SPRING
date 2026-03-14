// 传统的 Include Guard（包含卫士），防止同一个头文件被多次编译报错
#ifndef Q2_SORT_BY_DISTANCE_H
#define Q2_SORT_BY_DISTANCE_H

#include <vector>
#include <array>

// 仅仅声明函数：告诉编译器“有一个按距离排序的函数存在”，接收点集引用
void sort_points_by_distance(std::vector<std::array<double, 3>>& points);

#endif // Q2_SORT_BY_DISTANCE_H