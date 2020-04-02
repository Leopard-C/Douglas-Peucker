#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PainterLabel;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupLayout();

public slots:
    void onBtnSample();
    void onBtnClearAll();
    void onBtnClearSimplified();
    void onBtnSimplify();

private:
    PainterLabel* label;
    QLineEdit* editTolerance;
    QPushButton* btnSample;
    QPushButton* btnClearAll;
    QPushButton* btnClearSimplified;
    QPushButton* btnSimplify;
};
#endif // MAINWINDOW_H
