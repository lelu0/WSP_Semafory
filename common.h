#include <semaphore.h> 
#define BSIZE      4   // Rozmiar bufora 
#define LSIZE    256   //  Dlugosc linii 
typedef struct { 
    int head; 
    int tail;
    int cnt;  // Liczba elementów w buforze  
    sem_t mutex; 
    sem_t empty; // Semafor wstrzymuj
    sem_t full;  // Semafor wstrzymuj
    char buf[BSIZE][LSIZE]; 
} bufor_t;
