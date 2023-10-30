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
    palabra *matrizdePalabras;
} juego;

typedef struct nodoJuego
{
    juego Juego;
    struct nodo *sig;
} nodoJuego;

typedef struct matrix
{

} Matriz;

typedef struct Participante
{
    char nickname[20];
    int puntaje;
} participante;
// declarar un vector de participantes
participante vectorParticipantes[MAX_PARTICIPANTES];

// Prototipo de funciones - Menu de inicio
void mostrarMenu();
void realizarAccion();
void crearParticipante();

int numParticipantes=0;
int main()
{
    nodoJuego *headListaJuego = NULL;
    printf("Juego bytes: %d", sizeof(palabra));
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
                break;
            case 2:
                printf("Ha seleccionado la opcion 2.\n");
                break;
            case 3:
                printf("Ha seleccionado la opcion 3.\n");
                break;
            case 4:
                printf("Ha seleccionado la opcion 4.\n");
                break;
            case 5:
                printf("Ha seleccionado la opcion 5.\n");
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
    participante nuevoParticipante;
    
    
    
}

/*
if (numParticipantes < MAX_PARTICIPANTES)
    {
        struct Participante nuevoParticipante;
        printf("Ingrese el nickname del participante: ");
        scanf("%s", nuevoParticipante.nickname);

        // Verificar si ya existe un participante con el mismo nickname
        int indiceExistente = buscarParticipantePorNickname(nuevoParticipante.nickname);
        if (indiceExistente == -1)
        {
            nuevoParticipante.puntaje = 0; // Inicializar el puntaje en 0
            vectorParticipantes[numParticipantes] = nuevoParticipante;
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
*/