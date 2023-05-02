//Nome: Gabriel Kento Toledo Takagi  Registro Academico:1929933

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdbool.h>

pthread_mutex_t mutex;
sem_t s1;

int numeroCalculado = 500000;
int contador = 2;
int contadorNumerosPrimos = 0;

bool numeroPrimo(int numero){
    for (int i = 2; i < numero; i++){
        if (numero % i == 0){
            return false;
            break;
        }
    }
    return true;
}

void *contarNumeros(){

    while (1){
        
        pthread_mutex_lock(&mutex);
        sem_wait(&s1);
        if (contador > numeroCalculado){
            sem_post(&s1);
            pthread_mutex_unlock(&mutex);
            break;
        }

        int numero = contador;
        contador ++;
        printf("%d \n", numero);
        sem_post(&s1);
        pthread_mutex_unlock(&mutex);
        
        bool primo = numeroPrimo(numero);

        if (primo == true){
            contadorNumerosPrimos ++;
        }

    }

}

int main(){
    pthread_t t1,t2,t3,t4;

    pthread_mutex_init(&mutex, NULL);

    sem_init(&s1, 1, 1);

    (void) pthread_create(&t1, NULL, contarNumeros, NULL);
    (void) pthread_create(&t2, NULL, contarNumeros, NULL);
    (void) pthread_create(&t3, NULL, contarNumeros, NULL);
    (void) pthread_create(&t4, NULL, contarNumeros, NULL);

    (void) pthread_join(t1, NULL);
    (void) pthread_join(t2, NULL);
    (void) pthread_join(t3, NULL);
    (void) pthread_join(t4, NULL);

    printf("Numeros primos encontrados: %d \n", contadorNumerosPrimos);

    return 0;
}