#include "painterlabel.h"
#include "linesimplifier.h"

#include <QMouseEvent>
#include <QPainter>
#include <algorithm>
#include <QColor>
#include <QDebug>

PainterLabel::PainterLabel(int width, int height, QWidget* parent)
    : QLabel(parent)
{
    this->setFixedSize(width, height);
    this->setMouseTracking(true);
    this->setFrameStyle(QFrame::Box);
    this->setAlignment(Qt::AlignTop);
}

void PainterLabel::startSample() {
    isSampling_ = true;
    clearAll();
    this->setText("Right click to stop sampling");
}

void PainterLabel::clearAll() {
    this->clear();
    std::vector<QPoint>().swap(simplifiedLine);
    std::vector<QPoint>().swap(line);
    update();
}

void PainterLabel::clearSimplified() {
    this->setText("");
    std::vector<QPoint>().swap(simplifiedLine);
    update();
}

void PainterLabel::mousePressEvent(QMouseEvent *event) {
    // Right click to stop sampling
    if (event->button() == Qt::RightButton) {
        this->setText("");
        isSampling_ = false;
        update();
    }
    // Add new point or remove exist point
    if (isSampling_) {
        QPoint newPoint = event->pos();
        auto findIter = std::find_if(line.begin(), line.end(), [&newPoint](QPoint point){
            return (point - newPoint).manhattanLength() < 9;
        });
        if (findIter != line.end()) {
            line.erase(findIter);
        }
        else {
            qDebug() << newPoint;
            line.push_back(newPoint);
        }
        update();
    }
}

void PainterLabel::mouseMoveEvent(QMouseEvent *ev) {
    if (isSampling_) {
        currPos = ev->pos();
        update();
    }
}

void PainterLabel::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event);

    if (line.empty())
        return;

    QPainter painter(this);
    QPen pen;
    pen.setColor(qRgb(128, 0, 128));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw original line
    size_t size = line.size();
    for (size_t i = 1; i < size; ++i) {
        painter.drawLine(line[i - 1], line[i]);
    }

    if (isSampling_) {
        painter.drawLine(line[size - 1], currPos);
    }

    // Draw simplified line
    if (simplifiedLine.size() > 0) {
        pen.setColor(qRgb(255, 0, 0));
        pen.setWidth(1);
        painter.setPen(pen);
        size_t size = simplifiedLine.size();
        for (size_t i = 1; i < size; ++i) {
            painter.drawLine(simplifiedLine[i - 1], simplifiedLine[i]);
        }
    }
}

void PainterLabel::simplifyLine(int tolerance) {
    size_t size = line.size();
    if (size < 3)
        return;

    LineSimplifier simplifer(line);
    simplifiedLine = simplifer.simplify(tolerance);

    double compressRatio = simplifiedLine.size() / double(line.size());
    QString compressRatioText = QString("%1%").arg(compressRatio * 100);
    this->setText(compressRatioText);

    update();
}
