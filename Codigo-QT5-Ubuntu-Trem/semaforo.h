#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <semaphore.h>

class Semaforo
{
public:
    Semaforo(char label);
    void destroySemaforo();
    bool verificaRegiaoCritica(int x, int y);
    void ocupar(char trem);
    void liberar(char trem);
    int *buffer;
private:
    sem_t s;//o semáforo
    char label; //label do semáforo
};

#endif // SEMAFORO_H
