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


int APC_ActivarSeccion (const char* nombreArea,const char* nomSeccion, size_t tamanoSeccion){
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

   
   
   int i = 0;
   while (i < 10) {
     const char*  nombre = area->seccion[i].nombre;
     if(strcmp(nombre,nomSeccion)== 0) {
       return 0;
     }
     i++;
   }
   int contador = 0;
   bool seccionDisp = false;
   while (contador < NSection){

     if (area->estadoSecciones[contador] == 0){
       int resta = area->conexion.numElementos -tamanoSeccion;
       if  (resta < 0){
	   errno = APC_ERROR_NOMEMORIA;
           return -1;
      }
       seccionDisp = true;
       area->estadoSecciones[contador] = 1;
       area->conexion.numElementos = resta;
       cout << area->conexion.numElementos << endl;
       strncpy(area->seccion[contador].nombre, nomSeccion, MAX_NOMBRE);
       area->seccion[contador].activa = true;
       area->seccion[contador].base = area->conexion.baseAux;
       area->seccion[contador].limite = tamanoSeccion -1;
       area->seccionAdm[contador].tamano = tamanoSeccion;
       area->conexion.baseAux = area->seccion[contador].limite +1;
       contador++;
       break;
				
     }
     contador ++;
   }
   if (!seccionDisp){
     errno = APC_ERROR_LLENO;
     return -1;
   }

   return 0;
}

int main (){
  cout << APC_ActivarSeccion ("1234x12","3", 200)<< endl;
  cout << APC_ActivarSeccion ("1234x12" ,"4", 1300)<< endl;
  return 0;
}
