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

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 100 && x <540){
                if(y==100 && x==520 && (**this->semaforos[1]).isOcupado()){
                    x-=10;
                    break;
                }
                if(x==520 && y==100){ //!CONFERE ENTRADA EM S0
                    this->mutex.lock();
                    (**this->semaforos[0]).ocupar('1');
                    this->mutex.unlock();
                }
                x+=10;
            }else if (x == 540 && y < 220){//!EM S0
                if(y==200 && x==540 && ((**this->semaforos[1]).isOcupado() || (**this->semaforos[2]).isOcupado()) && (**this->semaforos[5]).isOcupado()){
                    y-=10;
                    break;
                }
                if(x==540 && y==200){ //!No final de S0, ocupando S1
                    this->mutex.lock();
                    (**this->semaforos[1]).ocupar('1');
                    this->mutex.unlock();
                }
                y+=10;
            }else if (x > 270 && y == 220){
                if(!(x < 390)){ //!Saiu do S0 e entrou no S1; entre [S1,S2]
                    if(x==530 && y==220){ //!Em S1, liberando S0
                        this->mutex.lock();
                        (**this->semaforos[0]).liberar('1');
                        this->mutex.unlock();
                    }
                    if(x==420 && y==220){ //! No final de S1, ocupando S2
                        this->mutex.lock();
                        (**this->semaforos[2]).ocupar('1');
                        this->mutex.unlock();
                    }
                }else{ //! Saiu de S1 e entrou em S2; entre [S2;-]
                    if(x==370 && y==220){ //! Em S2, liberando S1
                        this->mutex.lock();
                        (**this->semaforos[1]).liberar('1');
                        this->mutex.unlock();
                    }
                }
                x-=10;
            }else{
                if(x==270 && y==220){ //!Libera S2
                    this->mutex.lock();
                    (**this->semaforos[2]).liberar('1');
                    this->mutex.unlock();
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal - mudou de posição
            break;
        case 2: //Trem 2
            if (y == 100 && x <810){
                x+=10;
            }else if (x == 810 && y < 220){
                if(y==200 && x==810 && ((**this->semaforos[3]).isOcupado() || (**this->semaforos[4]).isOcupado()) && (**this->semaforos[6]).isOcupado()){
                    y-=10;
                    break;
                }
                if(x==810 && y==200){ //! CONFERE ENTRADA EM S3
                    this->mutex.lock();
                    (**this->semaforos[3]).ocupar('2');
                    this->mutex.unlock();
                }
                y+=10;
            }else if (x > 540 && y == 220){
                if (x > 660){ //!Em S3
                    if(y==220 && x==680 && (**this->semaforos[1]).isOcupado() && (**this->semaforos[0]).isOcupado()){
                        x+=10;
                        break;
                    }
                    if((x==680 && y==220)){ //!CONFERE ENTRADA EM S4
                        this->mutex.lock();
                        (**this->semaforos[4]).ocupar('2');
                        this->mutex.unlock();
                    }
                }else{
                    if(x==640 && y==220){ //!LIBERA S3
                        this->mutex.lock();
                        (**this->semaforos[3]).liberar('2');
                        this->mutex.unlock();
                    }
                    //!ÁREA DE S4
                    if(y==220 && x==560){ //!CONFERE ENTRADA EM S0
                        this->mutex.lock();
                        (**this->semaforos[0]).ocupar('2');
                        this->mutex.unlock();
                    }
                }
                x-=10;
            }else{
                y-=10;
                if(x==540 && y==200){ //!LIBERA O S4
                    this->mutex.lock();
                    (**this->semaforos[4]).liberar('2');
                    this->mutex.unlock();
                }
                if((x+10)==550 && y==100){ //! LIBERA O S0 qnd vai para o S1
                    this->mutex.lock();
                    (**this->semaforos[0]).liberar('2');
                    this->mutex.unlock();
                }
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 220 && x < 390){
                if(y==220 && x==250 && ((**this->semaforos[1]).isOcupado() || (**this->semaforos[2]).isOcupado()) && (**this->semaforos[5]).isOcupado()){
                    x-=10;
                    break;
                }

                if(x==250 && y==220){ //Entra em S2
                    this->mutex.lock();
                    (**this->semaforos[2]).ocupar('3');
                    this->mutex.unlock();
                }
                if(x==370 && y==220){ //prestes a entrar em S5
                   this->mutex.lock();
                    (**this->semaforos[5]).ocupar('3');
                   this->mutex.unlock();
                }
                x+=10;
            }else if(x == 390 && y < 340){
                //! Aqui ele está parando o S2 e o S5 enquanto passa pela encruzilhada
                if(x==390 && y==230){ //Está dentro do trilho do S5.
                    this->mutex.lock();
                    (**this->semaforos[2]).liberar('3');
                    this->mutex.unlock();
                }
                y+=10;
            }else if( x > 120 && y == 340){
                if(x == 370 && y==340){
                    this->mutex.lock();
                    (**this->semaforos[5]).liberar('3');
                    this->mutex.unlock();
                }
                x-=10;
            }else
                y-=10;
            emit updateGUI(ID,x,y); //Emite um sinal
            break;
        case 4: //Trem 4
            if(y == 220 && x < 660){
                if(y==220 && x < 540){ //! ÁREA DE S1
                    if(x==390 && y==220){ //!ocupa S1
                        this->mutex.lock();
                        (**this->semaforos[1]).ocupar('4');
                        this->mutex.unlock();
                    }
                    if(y==220 && x==520 && ((**this->semaforos[4]).isOcupado() || (**this->semaforos[3]).isOcupado()) && (**this->semaforos[6]).isOcupado()){
                        x-=10;
                        break;
                    }
                    if(y==220 && x==520){ //!CONFERE ENTRADA EM S4
                        this->mutex.lock();
                        (**this->semaforos[4]).ocupar('4');
                        this->mutex.unlock();
                    }
                }else{//! ÁREA DE S4
                    if(y==220 && x==560){//!LIBERA S1
                        this->mutex.lock();
                        (**this->semaforos[1]).liberar('4');
                        this->mutex.unlock();
                    }
                    if(y==220 && x==640){ //! CONFERE S6
                        this->mutex.lock();
                        (**this->semaforos[6]).ocupar('4');
                        this->mutex.unlock();
                    }

                }
                x+=10;
            }else if(x == 660 && y <340){ //EM S6
                if(x==660 && y==240){ //Libera o S4
                    this->mutex.lock();
                    (**this->semaforos[4]).liberar('4');
                    this->mutex.unlock();
                }                
                y+=10;
            }else if(x > 390 && y == 340){ //LIVREs
                if(y==340 && x==410 && (**this->semaforos[1]).isOcupado() && (**this->semaforos[2]).isOcupado()){
                    x+=10;
                    break;
                }
                if(y== 340 &&  x== 640){ //!LIBERA S6
                    this->mutex.lock();
                    (**this->semaforos[6]).liberar('4');
                    this->mutex.unlock();
                }
                if(x==410 && y==340){ //!Antes de S5, ocupa S5
                    this->mutex.lock();
                    (**this->semaforos[5]).ocupar('4');
                    this->mutex.unlock();
                }
                x-=10;
            }else{ //EM S5
              if((y-20)==220 && x== 390 && ((**this->semaforos[1]).isOcupado())){
                    y+=10;
                    break;
                }
              if((y-20)==220 && x==390 && ((**this->semaforos[1]).isOcupado() || (**this->semaforos[4]).isOcupado()) && (**this->semaforos[0]).isOcupado()){
                  y+=10;
                  break;
              }
                if(x==390 && (y-10)==220){ //!liberar S5
                    this->mutex.lock();
                    (**this->semaforos[5]).liberar('4');
                    this->mutex.unlock();
                }

                y-=10;
            }
            emit updateGUI(ID,x,y);
            break;
        case 5: //Trem 5
            if(x==660 && y==220){
                this->mutex.lock();
                (**this->semaforos[3]).ocupar('5');
                this->mutex.unlock();
                x+=10;
            }else if(y == 220 && (x < 930) && (x>660)){
                if(x==830){//! LIBERA EM S3
                    this->mutex.lock();
                    (**this->semaforos[3]).liberar('5');
                    this->mutex.unlock();
                }
                x+=10;
            }else if(x == 930 && y < 340)
                y+=10;
            else if(x > 660 && y == 340){
                if(y==340 && x==680 && ((**this->semaforos[6]).isOcupado() || (**this->semaforos[4]).isOcupado()) && (**this->semaforos[3
                ]).isOcupado()){
                    x+=10;
                    break;
                }
                if(x==680 && y==340){ //Quase em S6
                    this->mutex.lock();
                    (**this->semaforos[6]).ocupar('5');
                    this->mutex.unlock();
                }
                x-=10;
            }else{
                if((y-20)==220 && x== 660 && ((**this->semaforos[3]).isOcupado())){
                    y+=10;
                    break;
                }
                if(x==660 && (y-10)==220){ //! LIBERA O S6 qnd passa do semaforo
                    this->mutex.lock();
                    (**this->semaforos[6]).liberar('5');
                    this->mutex.unlock();
                }
                y-=10;
            }
            emit updateGUI(ID,x,y);
            break;
        default:
            break;
        }
        msleep(velocidade);
        // Quão mais alto a velocidade, mais devagar o trem anda
    }

    for(auto a: this->semaforos)
        (**a).destroySemaforo();
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
