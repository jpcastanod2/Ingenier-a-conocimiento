#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include "../include/apc.h"
#include <cstring>
#include <semaphore.h>




using namespace std;

int APC_Terminar(const char *nombreArea){

  if( nombreArea == NULL){
      errno = APC_ERROR_ARGUMENTO;
  }
  
  if (shm_unlink(nombreArea) < 0) {
    if(errno == 2){
      errno = APC_ERROR_NOEXISTE; 
    }
    else
      errno = APC_ERROR_DESCONOCIDO;
   
    return -1;
  }
  sem_unlink("semVacios");
  sem_unlink("semLlenos");
  sem_unlink("semMutex");
  shm_unlink(nombreArea);

  return 0;

}

int
main(void) {
  cout << APC_Terminar("1234x12");
  return EXIT_SUCCESS;
}
