#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,270,100);
    trem2 = new Trem(2,540,100);
    trem3 = new Trem(3,120,220);
    trem4 = new Trem(4,390,220);
    trem5 = new Trem(5,660,220);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTrainsPositions(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTrainsPositions(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTrainsPositions(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTrainsPositions(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTrainsPositions(int,int,int)));

    /*Threads iniciam automaticamente*/
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}


void MainWindow::resetTrailsColors(int id){
    switch(id){
    case 1:
        ui->trilho1->setStyleSheet("QLabel { background: gray}");
        ui->trilho16->setStyleSheet("QLabel { background: gray}");
        ui->trilho3->setStyleSheet("QLabel { background: gray}");
        break;
    case 2:
        ui->trilho2->setStyleSheet("QLabel { background: gray}");
        ui->trilho5->setStyleSheet("QLabel { background: gray}");
        ui->trilho17->setStyleSheet("QLabel { background: gray}");
        break;
    case 3:
        ui->trilho6->setStyleSheet("QLabel { background: gray}");
        ui->trilho13->setStyleSheet("QLabel { background: gray}");
        ui->trilho9->setStyleSheet("QLabel { background: gray}");
        break;
    case 4:
        ui->trilho7->setStyleSheet("QLabel { background: gray}");
        ui->trilho14->setStyleSheet("QLabel { background: gray}");
        break;
    case 5:
        ui->trilho8->setStyleSheet("QLabel { background: gray}");
        ui->trilho12->setStyleSheet("QLabel { background: gray}");
        ui->trilho15->setStyleSheet("QLabel { background: gray}");
        break;
    }
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterfaceTrainsPositions(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3:
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4:
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5:
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

//Segunda opção da função que será executada quando o sinal UPDATEGUI for emitido
//Com cores nos trilhos
void MainWindow::updateInterface(int id, int x, int y){
    resetTrailsColors(id);
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        ui->trilho16->setVisible(false);
        if (y == 100 && x <540)
            ui->trilho1->setStyleSheet("QLabel { background: pink}");
        else if (x == 540 && y < 220){
            ui->trilho4->setStyleSheet("QLabel { background: pink}");
        }else if (x > 270 && y == 220){
            ui->trilho4->setStyleSheet("QLabel { background: gray}");
            ui->trilho16->setVisible(true);
            ui->trilho16->raise();
            ui->label_trem1->raise();
            ui->trilho16->setStyleSheet("QLabel { background: pink}");
        }
        else
            ui->trilho3->setStyleSheet("QLabel { background: pink}");
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        ui->trilho17->setVisible(false);
        if (y == 100 && x <810){
            ui->trilho4->setStyleSheet("QLabel { background: gray}");
            ui->trilho2->setStyleSheet("QLabel { background: red}");
        }else if (x == 810 && y < 220)
            ui->trilho5->setStyleSheet("QLabel { background: red}");
        else if (x > 540 && y == 220){
            ui->trilho17->setVisible(true);
            ui->trilho17->raise();
            ui->label_trem2->raise();
            ui->trilho17->setStyleSheet("QLabel { background: red}");
        }
        else
            ui->trilho4->setStyleSheet("QLabel { background: red}");

        break;
    case 3:
        ui->label_trem3->setGeometry(x,y,21,17);
        if (y == 220 && x < 390){
            ui->trilho6->setStyleSheet("QLabel { background: orange}");
        }else if(x == 390 && y < 340)
            ui->trilho10->setStyleSheet("QLabel { background: orange}");
        else if( x > 120 && y == 340){
            ui->trilho10->setStyleSheet("QLabel { background: gray}");
            ui->trilho13->setStyleSheet("QLabel { background: orange}");
        }else
            ui->trilho9->setStyleSheet("QLabel { background: orange}");
        break;
    case 4:
        ui->label_trem4->setGeometry(x,y,21,17);

        if(y == 220 && x < 660){
            ui->trilho10->setStyleSheet("QLabel { background: gray}");
            ui->trilho7->setStyleSheet("QLabel { background: yellow}");
        }else if(x == 660 && y <340)
            ui->trilho11->setStyleSheet("QLabel { background: yellow}");
        else if(x > 390 && y == 340){
            ui->trilho11->setStyleSheet("QLabel { background: gray}");
            ui->trilho14->setStyleSheet("QLabel { background: yellow}");
        }else
            ui->trilho10->setStyleSheet("QLabel { background: yellow}");
        break;
    case 5:
        ui->label_trem5->setGeometry(x,y,21,17);

        if(y == 220 && x < 930){
            ui->trilho11->setStyleSheet("QLabel { background: gray}");
            ui->trilho8->setStyleSheet("QLabel { background: green}");
        }else if(x == 930 && y < 340)
            ui->trilho12->setStyleSheet("QLabel { background: green}");
        else if(x > 660 && y == 340)
            ui->trilho15->setStyleSheet("QLabel { background: green}");
        else
            ui->trilho11->setStyleSheet("QLabel { background: green}");
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate(); //finaliza a thread que está sendo executada
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value == 200){
        trem1->terminate();
        return;
    }
    if(!trem1->isRunning())
        trem1->start();

    trem1->setVelocidade(value);
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    if(value == 200){
        trem2->terminate();
        return;
    }
    if(!trem2->isRunning())
        trem2->start();

    trem2->setVelocidade(value);
}

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    if(value == 200){
        trem3->terminate();
        return;
    }
    if(!trem3->isRunning())
        trem3->start();

    trem3->setVelocidade(value);
}

void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    if(value == 200){
        trem4->terminate();
        return;
    }
    if(!trem4->isRunning())
        trem4->start();
    trem4->setVelocidade(value);
}

void MainWindow::on_horizontalSlider_10_valueChanged(int value)
{
    if(value == 200){
        trem5->terminate();
        return;
    }
    if(!trem5->isRunning())
        trem5->start();
    trem5->setVelocidade(value);
}

