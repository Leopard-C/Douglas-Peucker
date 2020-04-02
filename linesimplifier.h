#ifndef LINESIMPLIFIER_H
#define LINESIMPLIFIER_H

#include <vector>
#include <QPoint>

class LineSimplifier
{
public:
    LineSimplifier(const std::vector<QPoint>& lineIn);

public:
    std::vector<QPoint> simplify(int tolerance);

private:
    double distanceSquare(QPoint start, QPoint end, QPoint point);
    void simplifySection(size_t i, size_t j);

private:
    const std::vector<QPoint>& line;
    std::vector<bool> deleteFlags;
    int tolerance;
};

#endif // LINESIMPLIFIER_H
