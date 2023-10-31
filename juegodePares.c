#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_PARTICIPANTES 10
typedef struct palabra
{
    char texto[20];
} palabra;
/*
Una palabra es un arreglo de caracteres.
Podemos hacer que sea una estrutura.
Y crear una matriz de esta estructura.
Se declararia como: palabra matrizpalabras[2][2] por ejemplo
*/
typedef struct juego
{
    int numerodejuego;
    int n;
    palabra matrizdePalabras[MAX_PARTICIPANTES][MAX_PARTICIPANTES];
} juego;

typedef struct nodoJuego
{
    juego Juego;
    struct nodo *sig;
} nodoJuego;

typedef struct Participante
{
    char nickname[20];
    int puntaje;
} participante;
// declarar un vector de participantes

// Prototipo de funciones - Menu de inicio
void mostrarMenu();
void realizarAccion();
void crearParticipante();
struct Participante *buscarParticipantePorNickname(char *nickname);
void crearParticipante();
void imprimirParticipantes(participante *participantes, int numParticipantes);

// Vector estático para almacenar a los participantes en el stack
participante vectorParticipantes[MAX_PARTICIPANTES];

// Puntero a la primera posición del vector de participantes
participante *primerParticipante = &vectorParticipantes[0];

int numParticipantes = 0;
int main()
{
    //  Puntero a la primera posicion de la lista de juegos
    nodoJuego *headListaJuego = NULL;
    realizarAccion();
    return 0;
}

void mostrarMenu()
{
    printf("____________________________\n");
    printf("\tMenu de Opciones:\n");
    printf("____________________________\n");
    printf("1. Crear juego\n");
    printf("2. Crear participante\n");
    printf("3. Jugar\n");
    printf("4. Mostrar ranking\n");
    printf("5. Datos para probar\n");
    printf("6. Salir\n");
}

void realizarAccion()
{
    int opcion;
    mostrarMenu();
    printf("Seleccione una opcion: ");

    while (1)
    {
        if (scanf("%d", &opcion) != 1)
        {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n')
                ; // Limpia el búfer de entrada
            mostrarMenu();
        }
        else
        {
            while (getchar() != '\n')
                ; // Limpia el búfer de entrada
            switch (opcion)
            {
            case 1:
                printf("Ha seleccionado la opcion 1.\n");
                mostrarMenu();
                break;
            case 2:
                printf("Ha seleccionado la opcion 2.\n");
                crearParticipante();
                mostrarMenu();
                break;
            case 3:
                printf("Ha seleccionado la opcion 3.\n");
                mostrarMenu();
                break;
            case 4:
                printf("Ha seleccionado la opcion 4.\n");
                imprimirParticipantes(vectorParticipantes, numParticipantes);
                mostrarMenu();
                break;
            case 5:
                printf("Ha seleccionado la opcion 5.\n");
                mostrarMenu();
                break;
            case 6:
                printf("Saliendo del programa.\n");
                exit(0);
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                mostrarMenu();
            }
        }
    }
}

void crearParticipante()
{
    if (numParticipantes < MAX_PARTICIPANTES)
    {
        participante nuevoParticipante;
        printf("Ingrese el nickname del participante: ");
        scanf("%s", nuevoParticipante.nickname);

        // Verificar si ya existe un participante con el mismo nickname
        participante *existente = buscarParticipantePorNickname(nuevoParticipante.nickname);
        if (existente == NULL)
        {
            nuevoParticipante.puntaje = 0; // Inicializar el puntaje en 0
            *(primerParticipante + numParticipantes) = nuevoParticipante;
            numParticipantes++;
            printf("Participante creado exitosamente.\n");
        }
        else
        {
            printf("El nickname ya existe. No se pudo crear el participante.\n");
        }
    }
    else
    {
        printf("No se pueden crear más participantes, se ha alcanzado el límite.\n");
    }
}

struct Participante *buscarParticipantePorNickname(char *nickname)
{
    for (int i = 0; i < numParticipantes; i++)
    {
        if (strcmp((primerParticipante + i)->nickname, nickname) == 0)
        {
            return primerParticipante + i; // Se encontró el participante
        }
    }
    return NULL; // No se encontró el participante
}

void imprimirParticipantes(participante *vectorParticipantes, int numParticipantes)
{
    if (numParticipantes != 0)
    {
        printf("Lista de participantes:\n");
        for (int i = 0; i < numParticipantes; i++)
        {
            printf("Participante %d:\n", i + 1);
            printf("Nickname: %s\n", vectorParticipantes[i].nickname);
            printf("Puntaje: %d\n", vectorParticipantes[i].puntaje);
            printf("\n");
        }
    }else printf ("ERROR: Todavia no hay participantes registrados\n");
}
