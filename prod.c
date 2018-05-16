#include <stdio.h> 
#include "common.h"
#include <sys/mman.h> 
#include <fcntl.h> 
#include <semaphore.h>
#include <unistd.h> 
#include <stdlib.h> 
void main(int argc, char *argv[]) {
       int steps = atoi(argv[2]);
       int nr = atoi(argv[1]);
       bufor_t  *wbuf ; 
       int fd=shm_open("bufor", O_RDWR|O_CREAT , 0774);
	wbuf = (bufor_t *)mmap(0, sizeof(bufor_t),PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0); 
      if(wbuf == NULL) {perror("map");  _exit(-1); } 
	printf("fd %d \n",fd);
for(int i = 0; i < steps; i++){
       printf("Producent - cnt:%d head: %d tail: %d\n",wbuf-> cnt,wbuf->head,wbuf->tail); 
       sem_wait(&(wbuf->empty)); 
       sem_wait(&(wbuf->mutex));
       sprintf(wbuf->buf[wbuf->head],"Producent %d, krok %d",nr,i+1);  
       wbuf-> cnt++; 
       wbuf->head = (wbuf->head +1) % BSIZE; 
       sem_post(&(wbuf->mutex)); 
       sem_post(&(wbuf->full)); 
       sleep(1);
} 
}    
