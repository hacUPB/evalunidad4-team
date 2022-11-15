#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define HILOS 2

sem_t snada;
sem_t slleno;

pthread_mutex_t lock;

int buffer[64];
int count = 0;
int* Lista;
int Ndatos;
int flag = 1;
void * Productor(void * args)
{
    for (int i = 0; i < Ndatos; i++) 
    {

        int x = rand() % 31;
        sem_wait(&snada);
        pthread_mutex_lock(&lock);
            buffer[count] = x;
            count++;
        pthread_mutex_unlock(&lock);
        sem_post(&slleno);
    }
}

void* Consumidor (void * args)
{
    for (int i = 0; i < Ndatos; i++)
    {
        int y;

        sem_wait(&slleno);
        pthread_mutex_lock(&lock);
            y = buffer[count-1];
            count--;
        pthread_mutex_unlock(&lock);
        sem_post(&snada);

        int *Dir = Lista;
        Dir[i] = y;
        
    }
}

void GenerarLista()
{
    int* Dir = Lista;
    for (int i = 0; i < Ndatos; i++)
    {
        printf("%i" ,i +1);
        printf(" .");
        printf("%i", Dir[i]);
        printf(" \n");
    }
    
}

void OrganizarLista()
{
    int*Dir = Lista;
    int a;

    for (int i = 0; i < Ndatos; ++i) 
    {
 
        for (int j = i + 1; j < Ndatos; ++j)
        {
            if (Dir[i] > Dir[j]) 
            {
                a =  Dir[i];
                Dir[i] = Dir[j];
                Dir[j] = a;
            }
        }
    }
}

int main ()
{

    printf("Este programa simula la toma y analisis de datos en una prueba de campo\n");
    printf("Bienvenido investigador.\n");

    while (flag)
    {
        
        

        printf("¿Que deseas hacer en este experimento?\n");
        printf("1. Tomar Datos\n");
        printf("2. Generar Lista\n");
        printf("3. Organizar Lista\n");
        printf("4. Salir\n");
        int n;
        scanf("%d",&n);
        system("clear");
        switch (n)
        {
        case 1:


            if (Lista != NULL)
            {
                free(Lista);
            }

            printf("Cuantos datos desea tomar?\n");
            scanf("%d",&Ndatos);
            Lista = malloc(Ndatos*sizeof(int));
            srand(time(NULL));
            pthread_t hilos[HILOS];
            pthread_mutex_init(&lock,NULL);
            sem_init(&snada,0,64);
            sem_init(&slleno,0,0);
            int i;

            for ( i = 0; i < HILOS; i++)
            {
                if (i%2 == 0)
                {
                    if (pthread_create(&hilos[i],NULL,&Productor, NULL) != 0 )
                    {
                        perror("No se pudo crear el productor\n");
                    }
                }
                else
                {
                    if (pthread_create(&hilos[i], NULL, &Consumidor, NULL) != 0)
                    {
                        perror("No se pudo crear el consumidor\n");
                    }  
                }
            }

            for (i = 0; i < HILOS; i++)
            {
                if (pthread_join(hilos[i],NULL) != 0)
                {
                    perror("No se pudo conectar al hilo principal\n");
                }
                
            }
            sem_destroy(&snada);
            sem_destroy(&slleno);
            pthread_mutex_destroy(&lock);

            printf("Datos Tomados con exito\n");
    
        break;
        
        case 2:

            GenerarLista();

        break;

        case 3:
            OrganizarLista();
            printf("La Lista se ha organizado de menor a mayor\n");
        break;

        case 4:

            free(Lista);
            flag = 0;

        break;
        default:
            printf("El valor ingresado no corresponde a ninguna opcion");
        break;
        }
    }        
    return 0;
}
