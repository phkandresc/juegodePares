void crearMatriz()
{
    int dimension;
    printf("Ingrese la dimension del tablero para jugar\n");
    printf("Solo numeros pares...");
    scanf("%d", &dimension);
    while (dimension % 2 == 0)
    {
        printf("Ingrese la dimension del tablero para jugar\n");
        printf("Solo numeros pares...");
        scanf("%d", &dimension);
        if (dimension % 2 == 0)
        {
            printf("Creado exitosamente\n");
        }
        else
            printf("ERROR: Ingrese un numero par para la dimension del tablero\n");
    }
}