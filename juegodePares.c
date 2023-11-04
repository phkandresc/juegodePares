#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_PARTICIPANTES 10
typedef struct palabra
{
    char texto[20];
} palabra;

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
void crearParticipante(participante *primerParticipante, int *ptr_numParticipantes);
struct Participante *buscarParticipantePorNickname(char *nickname, participante *primerParticipante, int *ptr_numParticipantes);
void imprimirParticipantes(participante *vectorParticipantes, int *ptr_numParticipantes);
void crearMatriz();

int main()
{
    int opcion;

    //Participantes
    participante vectorParticipantes [MAX_PARTICIPANTES];
    int numParticipantes = 0;
    int *ptr_numParticipantes = &numParticipantes;
    participante *headParticipantes = &vectorParticipantes[0];

    while (1)//Menu de opciones
    {
        mostrarMenu();
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
                printf("Ha seleccionado Crear Juego.\n");
                break;
            case 2:
                printf("Ha seleccionado Crear Participante.\n");
                crearParticipante(headParticipantes, ptr_numParticipantes);
                break;
            case 3:
                printf("Ha seleccionado Jugar.\n");
                break;
            case 4:
                printf("Ha seleccionado Mostrar Ranking.\n");
                imprimirParticipantes(headParticipantes, ptr_numParticipantes);
                break;
            case 5:
                printf("Ha seleccionado Datos para probar.\n");
                break;
            case 6:
                printf("Saliendo del programa.\n");
                exit(0);
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
            }
        }
    }
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

void crearParticipante(participante *primerParticipante, int *numParticipantes)
{
    if (*numParticipantes < MAX_PARTICIPANTES)
    {
        participante nuevoParticipante;
        printf("Ingrese el nickname del participante: ");
        scanf("%s", nuevoParticipante.nickname);

        // Verificar si ya existe un participante con el mismo nickname
        participante *existente = buscarParticipantePorNickname(nuevoParticipante.nickname, primerParticipante, numParticipantes);
        if (existente == NULL)
        {
            nuevoParticipante.puntaje = 0; // Inicializar el puntaje en 0
            *(primerParticipante + *numParticipantes) = nuevoParticipante;
            (*numParticipantes)++;
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

participante *buscarParticipantePorNickname(char *nickname, participante *primerParticipante, int *numParticipantes)
{
    for (int i = 0; i < *numParticipantes; i++)
    {
        if (strcmp((primerParticipante + i)->nickname, nickname) == 0)
        {
            return primerParticipante + i; // Se encontró el participante
        }
    }
    return NULL; // No se encontró el participante
}

void imprimirParticipantes(participante *vectorParticipantes, int *numParticipantes)
{
    if (*numParticipantes != 0)
    {
        printf("Lista de participantes:\n");
        for (int i = 0; i < *numParticipantes; i++)
        {
            printf("Participante %d:\n", i + 1);
            printf("Nickname: %s\n", vectorParticipantes[i].nickname);
            printf("Puntaje: %d\n", vectorParticipantes[i].puntaje);
            printf("\n");
        }
    }
    else
        printf("ERROR: Todavia no hay participantes registrados\n");
}

void crearMatriz()
{
    int dimension;
    printf("Ingrese la dimension del tablero para jugar\n");
    printf("Solo numeros pares...");
    scanf("%d", &dimension);
    while (dimension % 2 != 0)
    {
        printf("ERROR: Ingrese un numero par para la dimension del tablero\n");
        printf("Ingrese la dimension del tablero para jugar\n");
        printf("Solo numeros pares...");
        scanf("%d", &dimension);
    }
    printf("Creado exitosamente\n");
}