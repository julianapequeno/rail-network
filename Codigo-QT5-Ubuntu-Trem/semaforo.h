#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <semaphore.h>
#include "semaforo.h"
#include "trem.h"
class Semaforo
{
public:
    Semaforo(char label);
    void destroySemaforo();
    bool verificaRegiaoCritica(int x, int y);
    void checkIfIsAvaiable(Trem *trem);
private:
    sem_t s;//o semáforo
    char label; //label do semáforo
};

#endif // SEMAFORO_H
