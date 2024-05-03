#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <semaphore.h>

class Semaforo
{
public:
    Semaforo(char label);
    void destroySemaforo();
    bool verificaRegiaoCritica(int x, int y);
    void ocupar(char trem); //o parâmetro é só para DEBUG
    void liberar(char trem);//o parâmetro é só para DEBUG
    int ocup_resul;
private:
    sem_t s;//o semáforo/
    char label; //label do semáforo
};

#endif // SEMAFORO_H
