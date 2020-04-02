#ifndef PAINTERLABEL_H
#define PAINTERLABEL_H

#include <QLabel>
#include <vector>

class PainterLabel : public QLabel
{
    Q_OBJECT
public:
    PainterLabel(int width, int height, QWidget* parent = nullptr);

public:
    // Start sampling
    void startSample();

    // Clear all contents in the label
    void clearAll();

    // Just clear simplified line
    void clearSimplified();

    // Whether is sampling
    bool isSampling() const { return isSampling_; }

    // Simplify line
    void simplifyLine(int tolerance);

public:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void paintEvent(QPaintEvent *) override;

private:
    bool isSampling_ = false;
    QPoint currPos;
    std::vector<QPoint> line;
    std::vector<QPoint> simplifiedLine;
};

#endif // PAINTERLABEL_H
