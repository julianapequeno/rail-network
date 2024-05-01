#include "semaforo.h"
#include <semaphore.h>
#include <iostream>
Semaforo::Semaforo(char label) {
    this->label =  label;
    //int buf = 1;
    //this->buffer = &buf;
    sem_init(&this->s, 0, 1);
}

bool Semaforo::verificaRegiaoCritica(int x, int y){
    int regiao = -1;
    if (x == 540 && y < 220){
        regiao = 0;
    }else if (x > 390 && y == 220){
        regiao = 2;
    }else if ((x > 270 && x <390) && y == 220){
        regiao = 1;
    }else if(x == 390 && y < 340){
        regiao = 5;
    }else if(x == 660 && y <340){
        regiao = 6;
    }else if (x > 660 && y == 220){
        regiao = 4;
    }else if ((x > 540 && x < 660) && y == 220){
        regiao = 3;
    }

    if(regiao != -1)
        return true;
    else
        return false;
}


void Semaforo::destroySemaforo(){
    sem_destroy(&this->s);
}


void Semaforo::ocupar(char trem){
    std::cout << trem << " trem ocupando " << this->label << std::endl;
    sem_wait(&this->s);
}

void Semaforo::liberar(char trem){
    std::cout << trem << " trem liberando " << this->label << std::endl;
    sem_post(&this->s);
}

