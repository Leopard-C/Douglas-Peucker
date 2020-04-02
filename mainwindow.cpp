#include "mainwindow.h"
#include "painterlabel.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupLayout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout() {
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    label = new PainterLabel(600, 400, centralWidget);
    mainLayout->addWidget(label);

    btnSample = new QPushButton("Start Sampling", centralWidget);
    btnClearAll = new QPushButton("Clear All", centralWidget);
    btnClearSimplified = new QPushButton("Clear Simplified", centralWidget);
    btnSimplify = new QPushButton("Simplify", centralWidget);
    connect(btnSample, &QPushButton::clicked, this, &MainWindow::onBtnSample);
    connect(btnClearAll, &QPushButton::clicked, this, &MainWindow::onBtnClearAll);
    connect(btnClearSimplified, &QPushButton::clicked, this, &MainWindow::onBtnClearSimplified);
    connect(btnSimplify, &QPushButton::clicked, this, &MainWindow::onBtnSimplify);
    editTolerance = new QLineEdit(centralWidget);
    editTolerance->setFixedWidth(35);
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnSample);
    btnLayout->addStretch();
    btnLayout->addWidget(btnClearAll);
    btnLayout->addWidget(btnClearSimplified);
    btnLayout->addStretch();
    btnLayout->addWidget(new QLabel("Tolerance:", centralWidget));
    btnLayout->addWidget(editTolerance);
    btnLayout->addStretch();
    btnLayout->addWidget(btnSimplify);
    btnLayout->addStretch();
    mainLayout->addLayout(btnLayout);
}

void MainWindow::onBtnSample() {
    label->startSample();
}

void MainWindow::onBtnClearAll() {
    label->clearAll();
}

void MainWindow::onBtnClearSimplified() {
    label->clearSimplified();
}

void MainWindow::onBtnSimplify() {
    if (editTolerance->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Please input threshold", QMessageBox::Close);
        return;
    }
    int threshold = editTolerance->text().toInt();
    label->simplifyLine(threshold);
}
