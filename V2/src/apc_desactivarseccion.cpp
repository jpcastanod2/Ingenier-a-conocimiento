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


int APC_DesactivarSeccion (const char* nombreArea,const char* nomSeccion){
  int fd = shm_open(nombreArea, O_RDWR  , 0660);
  if (fd < 0){
    if (errno == 2) {
      errno = APC_ERROR_NOEXISTE;
    }
    else if (errno == 22) {
      errno = APC_ERROR_ARGUMENTO;
    }
    else{
      errno = APC_ERROR_DESCONOCIDO;
    }
    return -1;
  }

  void *dir;


   if ((dir = mmap(NULL, 30000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    cerr << "Error mapeando la memoria compartida: "
         << errno << strerror(errno) << endl;
  }
  struct Area_t *area = (struct Area_t *) dir;
   
   int contador = 0;
   while (contador < 10) {
     const char*  nombre = area->seccion[contador].nombre;
     if(strcmp(nombre,nomSeccion)== 0) {
       area->estadoSecciones[contador] = 0;
       area->conexion.numElementos = area->conexion.numElementos +
	area->seccionAdm[contador].tamano;
       cout << area->conexion.numElementos << endl;
       strncpy(area->seccion[contador].nombre , "", MAX_NOMBRE);
       area->seccion[contador].activa = false;
       return 0;
     }
     contador++;
   }
      
   errno = APC_ERROR_NOSECCION;
   return -1;
}

int main (){
 
  cout << APC_DesactivarSeccion ("1234x12","4")<< endl;
  return 0;
}
