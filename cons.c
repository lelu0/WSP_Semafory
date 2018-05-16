#include <stdio.h> 
#include "common.h"
#include <sys/mman.h> 
#include <fcntl.h> 
#include <semaphore.h>
#include <unistd.h> 
#include <stdlib.h> 
void main(int argc, char *argv[]) {
       int steps = atoi(argv[1]);
       bufor_t  *wbuf ; 
       int fd=shm_open("bufor", O_RDWR , 0774);
	wbuf = (bufor_t *)mmap(0, sizeof(bufor_t),PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0); 
      if(wbuf == NULL) {perror("map");  _exit(-1); } 
       printf("fd: %d \n",fd);
for(int i = 0; i < steps; i++){     
     printf("Konsument - cnt: %d odebrano %s\n",wbuf->cnt,wbuf->buf[wbuf->tail]);    
     sem_wait(&(wbuf->full)); 
     sem_wait(&(wbuf->mutex)); 
     wbuf-> cnt --; 
     wbuf->tail = (wbuf->tail +1) % BSIZE; 
     sem_post(&(wbuf->mutex)); 
     sem_post(&(wbuf->empty)); 
     sleep(1); 
} 
}    
