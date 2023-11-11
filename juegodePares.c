#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX_PARTICIPANTES 10
#define MAX_MATRIZ 10
typedef struct palabra
{
    char texto[20];
    bool encontrada;
} palabra;

typedef struct juego
{
    int numerodeJuego;
    int dimension;
    palabra matriz[MAX_MATRIZ][MAX_MATRIZ];
} juego;

typedef struct Participante
{
    char nickname[20];
    int puntaje;
} participante;

typedef struct NodoJuego
{
    juego *juego;
    struct NodoJuego *siguiente;
} NodoJuego;

typedef struct ListaJuegos
{
    NodoJuego *primerNodo;
} ListaJuegos;

// Prototipo de funciones - Menu de inicio
void mostrarMenu();

// Prototipo de funciones - Participantes
void crearParticipante(participante *primerParticipante, int *ptr_numParticipantes);
struct Participante *buscarParticipantePorNickname(char *nickname, participante *primerParticipante, int *ptr_numParticipantes);
void imprimirParticipantes(participante *vectorParticipantes, int *ptr_numParticipantes);
participante ingresarParticipante();
bool validarNickname(const char *nickname);

// Prototipo de funciones - Crear Juego

void agregarJuego(ListaJuegos *juegos, juego *nuevoJuego);
juego *crearJuego(int *numero, ListaJuegos *juegos);
void imprimirMatriz(ListaJuegos *juegos, int numeroJuego);

// Prototipo de funciones - Jugar
void mostrarMatrizConCeldaVisible(juego *juegoSeleccionado, int fila, int columna);
void mezclarPalabrasEnMatriz(juego *juego);
void jugar(ListaJuegos *listaJUEGOS, participante *headParticipantes, int *numParticipantes);
juego *elegirJuegoAleatorio(ListaJuegos *juegos);
void jugar2(juego *juegoSeleccionado);

// Prototipo de funciones - Probar
juego *crearJuegoRapido(int *numero, ListaJuegos *juegos);

int main()
{
    int opcion;

    // Participantes
    participante vectorParticipantes[MAX_PARTICIPANTES];
    int numParticipantes = 0;
    int *ptr_numParticipantes = &numParticipantes;
    participante *headParticipantes = &vectorParticipantes[0];

    // Juegos
    ListaJuegos listaJUEGOS;
    listaJUEGOS.primerNodo = NULL;
    int numJuego = 1;
    int *ptr_numJuego = &numJuego;
    while (1) // Menu de opciones
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
                juego *nuevoJuego = crearJuego(ptr_numJuego, &listaJUEGOS);
                agregarJuego(&listaJUEGOS, nuevoJuego);
                system("pause");
                break;
            case 2:
                printf("Ha seleccionado Crear Participante.\n");
                crearParticipante(headParticipantes, ptr_numParticipantes);
                system("pause");
                break;
            case 3:
                printf("Ha seleccionado Jugar.\n");
                juego *juegoSeleccionado = elegirJuegoAleatorio(&listaJUEGOS);
                jugar2(juegoSeleccionado);
                // jugar(&listaJUEGOS, headParticipantes, ptr_numParticipantes);
                break;
            case 4:
                printf("Ha seleccionado Mostrar Ranking.\n");
                imprimirParticipantes(headParticipantes, ptr_numParticipantes);
                system("pause");
                break;
            case 5:
                printf("Ha seleccionado Datos para probar.\n");
                // Crear un participante
                strcpy(vectorParticipantes[0].nickname, "Kevin");
                vectorParticipantes[0].puntaje = 0;
                numParticipantes++;
                printf("Participante Creado\n");
                // Crear un juego
                juego *nuevoJuegoRapido = crearJuegoRapido(ptr_numJuego, &listaJUEGOS);
                agregarJuego(&listaJUEGOS, nuevoJuegoRapido);
                system("pause");
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

participante ingresarParticipante()
{
    participante nuevoParticipante;
    bool valido;
    do
    {
        printf("Ingrese el nickname del participante: ");
        scanf("%s", nuevoParticipante.nickname);
        valido = validarNickname(nuevoParticipante.nickname);

        if (!valido)
        {
            printf("Nickname no valido. Debe tener al menos 4 caracteres y no contener espacios.\n");
        }
    } while (!valido);
    return nuevoParticipante;
}

bool validarNickname(const char *nickname)
{
    // Verificar la longitud mínima
    if (strlen(nickname) < 4)
    {
        return false;
    }

    // Verificar si contiene espacios
    for (int i = 0; i < strlen(nickname); i++)
    {
        if (nickname[i] == ' ')
        {
            return false;
        }
    }

    return true;
}

void crearParticipante(participante *primerParticipante, int *numParticipantes)
{
    if (*numParticipantes < MAX_PARTICIPANTES)
    {
        participante nuevoParticipante = ingresarParticipante();
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

// Función para crear un juego
juego *crearJuego(int *numero, ListaJuegos *juegos)
{
    juego *nuevoJuego = (juego *)malloc(sizeof(juego));

    if (nuevoJuego == NULL)
    {
        return NULL; // No se pudo asignar memoria para el juego
    }

    nuevoJuego->numerodeJuego = *numero;

    printf("Ingrese la dimension de la matriz (dimension debe ser par): ");
    scanf("%d", &nuevoJuego->dimension);

    // Verificar si la dimensión es par y cuadrada
    if (nuevoJuego->dimension % 2 != 0)
    {
        printf("La dimension debe ser un número par. Saliendo...\n");
        free(nuevoJuego);
        return NULL; // No se pudo crear el juego
    }

    char palabras[nuevoJuego->dimension][20];

    for (int i = 0; i < nuevoJuego->dimension; i++)
    {
        printf("Ingrese una palabra: ");
        scanf("%s", palabras[i]);
    }

    for (int i = 0; i < nuevoJuego->dimension; i++)
    {
        for (int j = 0; j < nuevoJuego->dimension; j++)
        {
            if (i != j)
            {
                strcpy(nuevoJuego->matriz[i][j].texto, palabras[j]);
            }
            else
            {
                strcpy(nuevoJuego->matriz[i][j].texto, palabras[i]);
            }
        }
    }
    mezclarPalabrasEnMatriz(nuevoJuego);
    if (nuevoJuego != NULL)
    {
        printf("Juego %d creado con exito. Dimension: %d x %d\n", nuevoJuego->numerodeJuego, nuevoJuego->dimension, nuevoJuego->dimension);
        (*numero)++;
    }
    return nuevoJuego;
}

// Función para agregar un juego a la lista de juegos
void agregarJuego(ListaJuegos *juegos, juego *nuevoJuego)
{
    NodoJuego *nuevoNodo = (NodoJuego *)malloc(sizeof(NodoJuego));
    nuevoNodo->juego = nuevoJuego;
    nuevoNodo->siguiente = NULL;
    if (juegos->primerNodo == NULL)
    {
        juegos->primerNodo = nuevoNodo;
    }
    else
    {
        NodoJuego *nodoActual = juegos->primerNodo;
        while (nodoActual->siguiente != NULL)
        {
            nodoActual = nodoActual->siguiente;
        }
        nodoActual->siguiente = nuevoNodo;
    }
}

void imprimirMatriz(ListaJuegos *juegos, int numeroJuego)
{
    NodoJuego *nodoActual = juegos->primerNodo;
    while (nodoActual != NULL)
    {
        if (nodoActual->juego->numerodeJuego == numeroJuego)
        {

            printf("Matriz del Juego %d:\n", nodoActual->juego->numerodeJuego);
            for (int j = 0; j < nodoActual->juego->dimension; j++)
            {

                printf("\t[%d]\t", j);
            }
            printf("\n");
            for (int i = 0; i < nodoActual->juego->dimension; i++)
            {
                printf("[%d]", i);
                for (int j = 0; j < nodoActual->juego->dimension; j++)
                {

                    printf("\t[%s]\t", nodoActual->juego->matriz[i][j].texto);
                }
                printf("\n");
            }
            return; // Salir una vez que se ha encontrado y mostrado el juego
        }
        nodoActual = nodoActual->siguiente;
    }
    printf("Juego no encontrado.\n");
}

void mostrarMatrizConCeldaVisible(juego *juegoSeleccionado, int fila, int columna)
{
    printf("Matriz del Juego %d con celda [%d][%d] visible:\n", juegoSeleccionado->numerodeJuego, fila, columna);
    for (int i = 0; i < juegoSeleccionado->dimension; i++)
    {
        for (int j = 0; j < juegoSeleccionado->dimension; j++)
        {
            if (i == fila && j == columna)
            {
                printf("[%s]\t", juegoSeleccionado->matriz[i][j].texto);
            }
            else
            {
                // Puedes ajustar este bloque según tus necesidades, marcando las palabras encontradas de alguna manera
                if (juegoSeleccionado->matriz[i][j].encontrada == true)
                {
                    printf("[ %s ]\t", juegoSeleccionado->matriz[i][j].texto);
                }
                else
                {
                    printf("[*****]\t");
                }
            }
        }
        printf("\n");
    }
}

void mezclarPalabrasEnMatriz(juego *juego)
{ /*
 En cada iteración del bucle, se generan dos números aleatorios x e y, que representan las coordenadas de otra celda en la matriz.

 Se intercambian las palabras en las posiciones (i, j) y (x, y) de la matriz. Esto se hace para mezclar las palabras en la matriz de forma aleatoria.

 El intercambio de palabras se realiza mediante una variable temporal.
 */
    srand(time(NULL));

    // Obtén las dimensiones de la matriz
    int dimension = juego->dimension;

    // Mezcla aleatoriamente las palabras en la matriz
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            int x = rand() % dimension;
            int y = rand() % dimension;

            // Intercambia las palabras en las posiciones (i, j) y (x, y)
            palabra temp;
            strcpy(temp.texto, juego->matriz[i][j].texto);
            strcpy(juego->matriz[i][j].texto, juego->matriz[x][y].texto);
            strcpy(juego->matriz[x][y].texto, temp.texto);
        }
    }
}

juego *crearJuegoRapido(int *numero, ListaJuegos *juegos)
{
    juego *nuevoJuego = (juego *)malloc(sizeof(juego));

    if (nuevoJuego == NULL)
    {
        return NULL; // No se pudo asignar memoria para el juego
    }

    nuevoJuego->numerodeJuego = *numero;
    nuevoJuego->dimension = 2;

    char palabras[nuevoJuego->dimension][20];
    strcpy(palabras[0], "Fortaleza");
    strcpy(palabras[1], "Fluminense");

    for (int i = 0; i < nuevoJuego->dimension; i++)
    {
        for (int j = 0; j < nuevoJuego->dimension; j++)
        {
            if (i != j)
            {
                strcpy(nuevoJuego->matriz[i][j].texto, palabras[j]);
            }
            else
            {
                strcpy(nuevoJuego->matriz[i][j].texto, palabras[i]);
            }
        }
    }
    mezclarPalabrasEnMatriz(nuevoJuego);
    if (nuevoJuego != NULL)
    {
        printf("Juego %d creado con exito. Dimension: %d x %d\n", nuevoJuego->numerodeJuego, nuevoJuego->dimension, nuevoJuego->dimension);
        (*numero)++;
    }
    return nuevoJuego;
}

void jugar(ListaJuegos *listaJUEGOS, participante *headParticipantes, int *numParticipantes)
// inicializar puntaje
{
    if (listaJUEGOS->primerNodo != NULL && headParticipantes->nickname != NULL) // Validar que existan juegos y participantes
    {
        participante Jugador = ingresarParticipante();
        if (buscarParticipantePorNickname(Jugador.nickname, headParticipantes, numParticipantes) != NULL)
        { // Validar participante para jugar
            printf("BIENVENIDO AL JUEGO, %s\n", Jugador.nickname);
            // int juego = juegoAleatorio(listaJUEGOS);
            // mostrarMatrizConCeldaVisible(listaJUEGOS, juego);

            /*
            Una vez validado los juegos, e ingresado con un usuario valido.
            elegir un juego al azar de la lista ligada listaJUEGOS
            Inicializar numero de intentos:
            numero de celdas / 2 + 30%
            Cada par aumenta +1 el puntaje
            El puntaje maximo que se puede alcanzar es
            el numero de celdas / 2 p

            int juego = juegoAleatorio(listaJUEGOS);
            mostrarMatrizConCeldaVisible(listaJUEGOS, juego);
            */
            // funcion que me retorne un int para numero de juego;
        }
        else
        {
            printf("ERROR: No se ha encontrado el participante con el que desea jugar\n");
            printf("Intentelo nuevamente...\n");
        }
    }
    else
    {
        printf("ERROR: No se puede jugar\n");
        printf("Recuerde crear juegos y registrarse como participante\n");
        printf("Intentelo nuevamente...\n");
        system("pause");
    }
}

// Función para jugar el juego seleccionado
void jugar2(juego *juegoSeleccionado)
{
    int puntaje = 0;
    int intentos = (juegoSeleccionado->dimension * juegoSeleccionado->dimension) / 2 + (int)(0.3 * (juegoSeleccionado->dimension * juegoSeleccionado->dimension));
    int fila1, columna1, fila2, columna2;

    // Aquí comienza la lógica principal del juego
    while (intentos > 0)
    {
        // Obtener la entrada del usuario para encontrar un par
        do
        {
            // Obtener la entrada del usuario para encontrar un par
            printf("Ingrese la fila de la primera celda que desea seleccionar: ");
            scanf("%d", &fila1);
            printf("Ingrese la columna de la primera celda que desea seleccionar: ");
            scanf("%d", &columna1);
            // Validar que las filas y columnas estén dentro del rango
            if (fila1 < 0 || fila1 >= juegoSeleccionado->dimension || columna1 < 0 || columna1 >= juegoSeleccionado->dimension)
            {
                printf("Al menos una celda fuera de los limites de la matriz.\n");
                printf("Intentelo nuevamente...\n");
                continue;
            }
            mostrarMatrizConCeldaVisible(juegoSeleccionado, fila1, columna1);
            juegoSeleccionado->matriz[fila1][columna1].encontrada = true;

            printf("Ingrese la fila de la segunda celda que desea seleccionar: ");
            scanf("%d", &fila2);
            printf("Ingrese la columna de la segunda celda que desea seleccionar: ");
            scanf("%d", &columna2);
            // Validar que las filas y columnas estén dentro del rango
            if (fila2 < 0 || fila2 >= juegoSeleccionado->dimension || columna2 < 0 || columna2 >= juegoSeleccionado->dimension)
            {
                printf("Al menos una celda fuera de los limites de la matriz.\n");
                printf("Intentelo nuevamente...\n");
                continue;
            }
            mostrarMatrizConCeldaVisible(juegoSeleccionado, fila2, columna2);
            juegoSeleccionado->matriz[fila2][columna2].encontrada = true;
            // Validar que las coordenadas no sean las mismas
            if (fila1 == fila2 && columna1 == columna2)
            {
                printf("Las coordenadas deben ser diferentes.\n");
                continue; // Volver al comienzo del bucle para pedir la entrada nuevamente
            }

            break; // Sale del bucle
        } while (1);

        // Verificar si las palabras en las coordenadas forman un par
        if (strcmp(juegoSeleccionado->matriz[fila1][columna1].texto, juegoSeleccionado->matriz[fila2][columna2].texto) == 0)
        {
            // Las palabras son iguales, forman un par
            printf("Has encontrado un par!\n");
            puntaje++;
        }
        else
        {
            // Las palabras no son iguales
            juegoSeleccionado->matriz[fila1][columna1].encontrada = false;
            juegoSeleccionado->matriz[fila2][columna2].encontrada = false;
            printf("No es un par.\n");
        }

        // Decrementar el número de intentos
        intentos--;
        printf("Puntaje: %d\tIntentos restantes: %d\n", puntaje, intentos);
    }

    // Mostrar el resultado final del juego
    printf("Juego terminado. Puntaje final: %d\n", puntaje);
    system("pause");
}

juego *elegirJuegoAleatorio(ListaJuegos *juegos)
{
    int elementos = 0;
    int indiceAleatorio;
    srand(time(NULL));
    NodoJuego *juegoSeleccionado = juegos->primerNodo;
    while (juegoSeleccionado != NULL)
    {
        juegoSeleccionado = juegoSeleccionado->siguiente;
        elementos++;
    }

    // Genera un número aleatorio entre 1 y nElementos
    indiceAleatorio = rand() % elementos + 1;
    juegoSeleccionado = juegos->primerNodo;
    for (int i = 1; i < indiceAleatorio; i++)
    {
        if (juegoSeleccionado == NULL)
        {
            // Manejo de errores: el índice está fuera de los límites de la lista
            printf("Índice fuera de los límites de la lista.\n");
        }
        else
            juegoSeleccionado = juegoSeleccionado->siguiente;
    }
    return juegoSeleccionado->juego;
}