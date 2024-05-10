#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"
#include "semaforo.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterfaceTrainsPositions(int id, int x, int y);
    void updateInterfaceColors(int,int,int);
    void resetTrailsColors(int id);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_10_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

    //Cria os objetos SEMÁFOROS
    Semaforo *s0;
    Semaforo *s1;
    Semaforo *s2;
    Semaforo *s3;
    Semaforo *s4;
    Semaforo *s5;
    Semaforo *s6;

    std::vector<Semaforo**> semaforos = {&s0,&s1,&s2,&s3,&s4,&s5,&s6};
};

#endif // MAINWINDOW_H
