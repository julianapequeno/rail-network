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
    bool OCUPADO = false;
    bool isOcupado();
private:
    char label; //label do semáforo
    sem_t s;
};

#endif // SEMAFORO_H
