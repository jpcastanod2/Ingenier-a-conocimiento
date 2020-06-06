const int NSection = 10;
const int MAX_NOMBRE = 64;
#define APC_ERROR_EXISTE 10000
#define APC_ERROR_ARGUMENTO 100001
#define APC_ERROR_DESCONOCIDO 100002
#define APC_ERROR_NOEXISTE 10003
#define APC_ERROR_LLENO 10004
#define APC_ERROR_NOMEMORIA 10005
#define APC_ERROR_NOSECCION 10006
#define APC_ERROR_NOCONEXION 10007
struct Seccion_t {
  char nombre[MAX_NOMBRE];
  bool activa;
  unsigned long base;
  unsigned long limite;
  char semLlenos[MAX_NOMBRE];
  char semVacios[MAX_NOMBRE];
  char semMutex[MAX_NOMBRE];
};

struct SeccionAdministrativa_t{
    int entra;
    int sale;
    int cantidad;
    int tamano;
 };
  
struct ConexionSeccion_B {
  int baseAux;
  int numElementos;
  int* elementosBuffer;
};

struct Area_t {
  int estadoSecciones[NSection];
  int dirDisponible;
  struct SeccionAdministrativa_t seccionAdm[NSection];
  struct Seccion_t seccion[NSection];
  struct ConexionSeccion_B conexion;
};
  
