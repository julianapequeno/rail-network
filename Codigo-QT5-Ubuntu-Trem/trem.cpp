#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100; //velocidade padrão
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 100 && x <540)
                x+=10;
            else if (x == 540 && y < 220)
                y+=10;
            else if (x > 270 && y == 220)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal - mudou de posição
            break;
        case 2: //Trem 2
            if (y == 100 && x <810)
                x+=10;
            else if (x == 810 && y < 220)
                y+=10;
            else if (x > 540 && y == 220)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
        // Quão mais alto a velocidade, mais devagar o trem anda
    }
}




