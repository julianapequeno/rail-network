#include "semaforo.h"
#include <semaphore.h>
#include <iostream>
Semaforo::Semaforo(char label) {
    this->label =  label;
    sem_init(&this->s, 0,1);
}

void Semaforo::destroySemaforo(){
    sem_destroy(&this->s);
}

void Semaforo::ocupar(char trem){
    std::cout << trem << " trem ocupando " << this->label << std::endl;
    int resul = sem_wait(&this->s);
    if(resul == 0 ){
        this->OCUPADO = true;
    }
}

void Semaforo::liberar(char trem){
    std::cout << trem << " trem liberando " << this->label << std::endl;
    sem_post(&this->s);
    this->OCUPADO = false;
}

bool Semaforo::isOcupado(){
    std::cout << "IS OCUPADO : " << this->OCUPADO << std::endl;
    if(this->OCUPADO)
        return true;
    else
        return false;
}

