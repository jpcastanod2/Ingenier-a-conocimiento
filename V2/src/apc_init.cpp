#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "../include/apc.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int APC_Init(const char* nombreArea, size_t tamano){

   if(tamano < 1000 || tamano > 1048576){
     errno = APC_ERROR_ARGUMENTO ;
     return -1;
   }

  int fd = shm_open(nombreArea, O_RDWR | O_CREAT | O_EXCL, 0660);
  
   if (fd < 0) {
    if(errno == 17){
      errno = APC_ERROR_EXISTE ; 
    }
    else if( errno == 22){
      errno =  APC_ERROR_ARGUMENTO ;
    }
    else{
      errno = APC_ERROR_DESCONOCIDO;
    
   
  }
    
    return -1;
 }

  size_t tamanioTotal = tamano + sizeof(struct Area_t);
   if (ftruncate(fd,tamanioTotal) != 0) {
    cerr << "Error creando la memoria compartida: "
	 << errno << strerror(errno) << endl;
  }
   
void *dir;
   if ((dir = mmap(NULL, sizeof(struct Area_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    cerr << "Error mapeando la memoria compartida: "
	 << errno << strerror(errno) << endl;
  }

   struct Area_t *area = (struct Area_t*) dir;   
   area->conexion.numElementos = tamano/ sizeof(int);
 
   area->conexion.elementosBuffer = new int [area->conexion.numElementos];
   close(fd);
   return 0;
  }

int main(){
  cout <<  APC_Init ("1234x12",30000)<< endl;
  return 0;
}
