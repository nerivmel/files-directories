#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void error(const char *s);
void procesoArchivo(char *archivo);
void procesoArchivo2(char *archivo);

int main(int argc, char **argv)
{

  struct dirent *ent;
  DIR *dir;
  dir = opendir (".");


  if(argc == 2){


    if (dir == NULL) 


    error("No puedo abrir el directorio");

    while ((ent = readdir (dir)) != NULL) 
      {
        if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
        {
        procesoArchivo2(ent->d_name);
       }
     
      }
    closedir (dir);
  return 1;
  }
if (dir == NULL) 
    error("No puedo abrir el directorio");
  

  while ((ent = readdir (dir)) != NULL) 
    {
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      procesoArchivo(ent->d_name);
    }
    }
  closedir (dir);

  return EXIT_SUCCESS;
 
} 

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo)
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
  FILE *fich;
  long ftam;

  fich=fopen(archivo, "r");
  if (fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      printf ("%30s (%ld bytes)\n", archivo, ftam);
    }
  else
    /* Si ha pasado algo, sólo decimos el nombre */
    printf ("%30s (No info.)\n", archivo);
}

void procesoArchivo2(char *archivo)
{

    struct stat fileStat;
    stat(archivo, &fileStat);
    if(archivo,&fileStat < 0)    
        return 1;
 
    printf("INFORMACION DE %s\n",archivo);
    printf("---------------------------\n");
    printf("TAMAÑO DEL ARCHIVO: \t\t%d bytes\n",fileStat.st_size);
    printf("NUMERO DE ENLACES: \t%d\n",fileStat.st_nlink);
    printf("NUMERO DE BLOQUES: \t%d\n",fileStat.st_blocks);
    printf("DIRECCION INODE: \t\t%d\n",fileStat.st_ino);
 
    printf("PERMISOS : \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
 
    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
 
    return 0;
}