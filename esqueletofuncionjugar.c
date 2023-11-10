#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para representar un juego
typedef struct {
    int numerodeJuego;
    int dimension;
    // Otras propiedades del juego, como la matriz de palabras y las celdas emparejadas, si las tienes.
} Juego;

// Estructura para representar a un participante
typedef struct {
    char nickname[50];
    int puntaje;
    // Otras propiedades del participante, si es necesario.
} participante;

void jugarPartida(Juego *juegos, int numJuegos, participante *primerParticipante) {
    // Inicializar variables para el juego
    int juegoActual = -1; // Índice del juego actual
    int intentos = 0;
    int paresEncontrados = 0;
    int maxIntentos = 10; // Cantidad máxima de intentos permitidos

    // Generar una semilla para la función rand() basada en el tiempo actual
    srand(time(NULL));

    // Elegir aleatoriamente un juego que no se haya jugado antes
    while (paresEncontrados < numJuegos) {
        juegoActual = rand() % numJuegos;
        if (juegos[juegoActual].numerodeJuego != -1) {
            break;
        }
    }

    // Mostrar el mensaje de inicio de la partida
    printf("¡Bienvenido, %s! Comienza la partida con el Juego %d.\n", primerParticipante->nickname, juegos[juegoActual].numerodeJuego);

    // Lógica del juego: implementa la lógica del juego aquí
    // Esto incluirá la visualización de la matriz del juego, la lógica de juego y la actualización de intentos y puntaje.

    // Una vez que se complete la partida, almacena el puntaje en el participante
    primerParticipante->puntaje = 0; // Calcula el puntaje según tu lógica de juego.

    // Marcar el juego como jugado para evitar repeticiones en futuras partidas
    juegos[juegoActual].numerodeJuego = -1;
}

int main() {
    // Definir una lista de juegos y participantes
    Juego juegos[5]; // Ejemplo: 5 juegos
    participante primerParticipante;

    // Inicializar los juegos y participantes como sea necesario

    // Solicitar el nickname del participante
    printf("Ingrese su nickname: ");
    scanf("%s", primerParticipante.nickname);

    // Jugar una partida
    jugarPartida(juegos, 5, &primerParticipante);

    // Imprimir el puntaje del participante
    printf("Puntaje de %s: %d\n", primerParticipante.nickname, primerParticipante.puntaje);

    return 0;
}
