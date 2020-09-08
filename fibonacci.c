#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *     Filename:  fibonnaci.c
 * =====================================================================================
 */

//long fibonacci(long a);
//void printFibo(long num);

int main(int argc, char const *argv[])
{
/* Declarando e inicializando algunas variables */
  int fpid = getppid();//obtener el PID del Padre
  int pid = getpid();//obtener el PID personal (hijo)
  long numFibo;//declaracion de la variable donde estará el numero de cota superior para la serie de fibonacci
  sscanf(argv[1],"%ld",&numFibo);//convierto el numero ingresado desde el excecv del main a long

/* Declaracion y creacion del archivo en la ruta Archivos_Creados/fibonacci.txt */
  FILE *archivo;//archivo para guardar los datos de los procesos
  char *nombreArchivo = "Archivos_Creados/fibonacci.txt";//apuntador a char para asignarle el nombre del archivo
  if ((archivo = fopen(nombreArchivo,"a+")) == NULL)//abro el archivo con el modo "a+" (permite que cada proceso ingrese datos al final del archivo)
  {
    printf("Error al crear archivo %s", nombreArchivo);
  }

/* Formato de impresion tanto para terminal como para el archivo fibonacci.txt */
  fprintf(archivo, "\n\nPID: %d PPID: %d num: %ld\nSerie: ", pid, fpid, numFibo);//formato para el arachivo
  printf("\n\nPID: %d PPID: %d num: %ld\nSerie: ", pid, fpid, numFibo);//formato para terminal

/* Serie de fibonacci de manera ciclica */
  int t0 = 0;//primer termino de la serie 
  int t1 = 1;//segundo termino de la serie
  int aux;//auxiliar de paso
  for (int i = 1; i <= numFibo; i++)
  {
    fprintf(archivo, "%d ", t0);//formato para el archivo
    printf("%d ", t0);//formato para terminal
    aux = t0 + t1;
    t0 = t1;
    t1 = aux;
    if (t0 >= numFibo)//condicion para verificar que la serie termine al llegar o antes de pasar la cota superior
    {
      break;
    }
  }
/* Cerrar canal del archivo */
  fclose(archivo);
  return 0;
}


/* Algunas funciones para hacer e imprimir la serie de fibonacci de manera recursiva */
/* 
long fibonacci(long a)
{
  if(a == 0 || a == 1)
  {
    return a;
  }
  else if(a >= 2)
  {
    return fibonacci(a - 2) + fibonacci(a - 1);
  }
}

void printFibo(long num)
{
  printf("\nPID: %d PPID: %d num: %ld\nSerie: ", getpid(), getppid(), num);
  int i, n, t1 = 0, t2 = 1, nextTerm;
  for (i = 1; i <= num; i++)
  {
    printf("%d ", t1);
    nextTerm = t1 + t2;
    t1 = t2;
    t2 = nextTerm;
    if (t1 >= num)
    {
      break;
    }
  }
  //printf("\n");
} 
*/