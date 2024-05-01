#include "trem.h"
#include <QtCore>
#include <iostream>
//Construtor
Trem::Trem(int ID, int x, int y,std::vector<Semaforo**> semaforos){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->semaforos = semaforos;
    velocidade = 100; //velocidade padrão
}

int Trem::getID(){
    return this->ID;
}
/*
int Trem::isInTrail(Trem *trem){
    switch(trem->getID()){
    case 1:     //Trem 1
        if (trem->getX() == 100 && trem->getY() <540)
            return 1;
        else if (x == 540 && y < 220){
            return 4;
        }else if (x > 270 && y == 220){
            if(x < 390){
                return 16;
            }else{
                return 17;
            }
        }else
            return 3;
        break;
    case 2: //Trem 2
        if (y == 100 && x <810)
            return 2;
        else if (x == 810 && y < 220)
            return 5;
        else if (x > 540 && y == 220){
            if (x > 660){
                return 19;
            }else{
                return 18;
            }
        }else{
            return 4;
        }
        break;
    case 3: //Trem 3
        if (y == 220 && x < 390){
            if(x < 270){
                return 6;
            }else{
                return 17;
            }
        } else if(x == 390 && y < 340)
            return 10;
        else if( x > 120 && y == 340)
            return 13;
        else
            return 9;
        break;
    case 4: //Trem 4
        if(y == 220 && x < 660){
            if(x < 540){
                return 16;
            }else{
                return 18;
            }
        }else if(x == 660 && y <340)
            return 11;
        else if(x > 390 && y == 340)
            return 14;
        else
            return 10;
        break;
    case 5: //Trem 5
        if(y == 220 && x < 930){
            if(x < 810){
                return 19;
            }else{
                return 8;
            }
        }else if(x == 930 && y < 340)
            return 12;
        else if(x > 660 && y == 340)
            return 15;
        else
            return 11;
        break;
    default:
        break;
    }
}
*/

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 100 && x <540){
                x+=10;
            }else if (x == 540 && y < 220){//entrou no S0
                if(x==530 && y==100){ //assim que está para entrar ele ocupa S0
                    (**this->semaforos[0]).ocupar('1');
                }
                y+=10;
            }else if (x > 270 && y == 220){
                if(x < 390){ //Saiu do S1 e entrou no S2
                    (**this->semaforos[1]).liberar('1');
                    if(x==380 && y==220){
                        (**this->semaforos[2]).ocupar('1');
                    }
                }else{ //saiu do S0 e entrou no S1
                    (**this->semaforos[0]).liberar('1');
                    if(x==530 && y==220){
                        (**this->semaforos[1]).ocupar('1');
                    }
                }
                x-=10;
            }else{
                (**this->semaforos[2]).liberar('1');
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal - mudou de posição
            break;
        case 2: //Trem 2
            if (y == 100 && x <810){
                if(x==550 && y==100){
                    (**this->semaforos[0]).liberar('2');
                }
                x+=10;
            }else if (x == 810 && y < 220)
                y+=10;
            else if (x > 540 && y == 220){
                if (x > 660){
                    if(x==800 && y==100){
                        (**this->semaforos[3]).ocupar('2');
                    }
                }else{
                    (**this->semaforos[3]).liberar('2');
                    if(x==650 && y==220){
                        (**this->semaforos[4]).ocupar('2');
                    }
                }
                x-=10;
            }else{
                (**this->semaforos[4]).liberar('2');
                if(y==220 && x==540){
                    (**this->semaforos[0]).ocupar('2');
                }
                 y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 220 && x < 390)
                x+=10;
            else if(x == 390 && y < 340)
                y+=10;
            else if( x > 120 && y == 340)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID,x,y); //Emite um sinal
            break;
        case 4: //Trem 4
            if(y == 220 && x < 660)
                x+=10;
            else if(x == 660 && y <340)
                y+=10;
            else if(x > 390 && y == 340)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID,x,y);
            break;
        case 5: //Trem 5
            if(y == 220 && x < 930)
                x+=10;
            else if(x == 930 && y < 340)
                y+=10;
            else if(x > 660 && y == 340)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID,x,y);
            break;
        default:
            break;
        }
        msleep(velocidade);
        // Quão mais alto a velocidade, mais devagar o trem anda
    }
}

//Função que altera a velocidade
void Trem::setVelocidade(int nova_vel){
    this->velocidade = nova_vel;
}

int Trem::getX(){
    return this->x;
}

int Trem::getY(){
    return this->y;
}
