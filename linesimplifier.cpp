#include "linesimplifier.h"

LineSimplifier::LineSimplifier(const std::vector<QPoint>& lineIn)
    : line(lineIn)
{
    deleteFlags = std::vector<bool>(line.size(), false);
}

std::vector<QPoint> LineSimplifier::simplify(int toleranceIn) {
    this->tolerance = toleranceIn;

    simplifySection(0, line.size() - 1);

    std::vector<QPoint> result;
    for (size_t i = 0, size = deleteFlags.size(); i < size; ++i) {
        if (!deleteFlags[i]) {
            result.push_back(line[i]);
        }
    }

    return result;
}

// The distance of point to line
double LineSimplifier::distanceSquare(QPoint start, QPoint end, QPoint point) {
    double A = end.y() - start.y();
    double B = start.x() - end.x();
    double C = end.x() * start.y() - start.x() * end.y();

    double numerator = A * point.x() + B * point.y() + C;
    double denominator = A * A + B * B;

    return numerator * numerator / denominator;
}

// Simplify a line section recursively;
void LineSimplifier::simplifySection(size_t start, size_t end) {
    if (start + 1 == end)
        return;

    size_t max_index = start - 1;
    double max_distance_square = -1;
    QPoint ptStart = line[start];
    QPoint ptEnd = line[end];
    for (size_t i = start + 1; i < end; ++i) {
        double dis = distanceSquare(ptStart, ptEnd, line[i]);
        if (dis > max_distance_square) {
            max_index = i;
            max_distance_square = dis;
        }
    }

    if (max_distance_square < tolerance * tolerance) {
        for (size_t i = start + 1; i < end; ++i) {
            deleteFlags[i] = true;
        }
    }
    else {
        simplifySection(start, max_index);
        simplifySection(max_index, end);
    }
}
