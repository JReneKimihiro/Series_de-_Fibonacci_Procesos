#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *     Filename:  main.c
 *  Description:  series de fibonacci de n numeros mediante n procesos.
 *      Version:  3.2
 *      Created:  05/09/20 10:11:33
 *     Revision:  none
 *     Compiler:  gcc
 * =====================================================================================
 */

int main ( int argc, char *argv[] )
{
/* Declarando e inicializando algunas variables */
  int numSeries = 0;//variable para guardar el numero de datos a manejar (procesos e hijos)
  while (argv[numSeries] != NULL)//conteo de series a trabajar
  {
    numSeries++;
  }
  __pid_t pids[numSeries];//array de pids hijos
  __pid_t pid;//variable pid para crear hijos
  pids[0] = getpid();//el pid 0 será el del padre

/* manejo de procesos hijos */
  for (int i = 1; i < numSeries; i++)//Ciclo de creacion de hijos mediante fork()
  {
    if ((pid = fork()) == 0)//validacion de proceso hijo para ejecutar su parte de codigo
    {
      char *args[] = {"fibonacci",argv[i],NULL};//datos a mandar mediante un vector a travez del excecv
      execv("fibonacci",args);//reemplaza el codigo del proceso que está corriendoy manda un vector de argumentos.
    }
    else
    {
      pids[i] = pid;//el proceso padre guarda el pid del hijo en el array
    }
    
  }
  for (int i = 1; i < numSeries; i++)//ciclo de wait() para esperar a todos los hijos creados
  {
    wait(NULL);
  }

/* Formato e impresion del padre del conteo de hijos */
  FILE *archivo;//archivo para guardar los datos de los procesos
  char *nombreArchivo = "Archivos_Creados/fibonacci.txt";//apuntador a char para asignarle el nombre del archivo
  if ((archivo = fopen(nombreArchivo,"a+")) == NULL)//abro el archivo con el modo a+ (permite que cada proceso ingrese datos al final del archivo)
  {
    printf("Error al crear archivo %s", nombreArchivo);
  }

  fprintf(archivo, "\n\nSoy el padre(%d)\nLista de mis hijos: ",pids[0]);//formato para hacer conteo de todos los hijos en archivo
  printf("\n\nSoy el padre(%d)\nLista de mis hijos: ",pids[0]);//formato para hacer conteo de todos los hijos en terminal
  for (int i = 1; i < numSeries; i++)
  {
    fprintf(archivo, "%d ",pids[i]);//impresion de PIDs de hijos en el archivo
    printf("%d ",pids[i]);//impresion de PIDs de hijos en la terminal
  }
  fclose(archivo);
  printf("\n\n");
  return EXIT_SUCCESS;
}
/* ----------  end of function main  ---------- */