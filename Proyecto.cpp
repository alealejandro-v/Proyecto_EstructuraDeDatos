/* 	PROYECTO - ESTRUCTURA DE DATOS
	EXAMENES

	Edgar Alejandro Vázquez Haro - 571846
	Rany Rey Guzmán Esparza - 566297
*/

#include <stdio.h>
#include <stdlib.h>

void menu();
void crear();
void lista();
void modificar();
void aplicar();

int main(){
	
	menu();
	
	return 0;
}

void menu(){
	int opc;
	do{
	printf("\n----Menu----\n");
	printf("Generar un examen_________1\n");
	printf("Lista de examenes_________2\n");
	printf("Modificar un examen_______3\n");
	printf("Aplicar un examen_________4\n");
	printf("Salir_____________________5\n");
	
		printf("Seleccione una opcion: ");
		scanf("%d",&opc);
		getchar();
		
		switch(opc){
			case 1: crear();
					break;
					
			case 2: lista();
					break;
			case 3: break;
			case 4: break;
		}
	} while(opc != 5);
}

void crear(){
	int numP;
    char nombre[100], nombreArch[110];
    char opc[5], pregunta[200], op1[100], op2[100], op3[100], op4[100];
    float puntos;

    FILE *archivoLista, *examen;

    archivoLista = fopen("lista.txt", "a");
    if (archivoLista == NULL){
        printf("Error al abrir lista.txt\n");
        return;
    }

    printf("Nombre del examen: ");
    scanf("%s", nombre);
    getchar();

    fprintf(archivoLista, "%s\n", nombre);
    fclose(archivoLista);

    sprintf(nombreArch, "%s.txt", nombre); //abre un archivo segun el nombre que  le pongas en la corrida
    examen = fopen(nombreArch, "w");
    if (examen == NULL){
        printf("Error al crear el archivo del examen.\n");
        return;
    }

    printf("Cuantas preguntas desea agregar? ");
    scanf("%d", &numP);
    getchar();

	for (int i = 0; i < numP; i++){

        printf("\nPregunta %d: ", i+1);
        fgets(pregunta, 200, stdin);
        pregunta[strcspn(pregunta, "\n")] = '\0'; // quitar salto de linea 

        printf("Opcion 1: "); 
		fgets(op1, 100, stdin); 
		op1[strcspn(op1,"\n")] = '\0';
		
        printf("Opcion 2: "); 
		fgets(op2, 100, stdin); 
		op2[strcspn(op2,"\n")] = '\0';
		
        printf("Opcion 3: "); 
		fgets(op3, 100, stdin); 
		op3[strcspn(op3,"\n")] = '\0';
		
        printf("Opcion 4: "); 
		fgets(op4, 100, stdin); 
		op4[strcspn(op4,"\n")] = '\0';

        printf("Respuesta correcta (op1/op2/op3/op4): ");
        scanf("%s", opc);
        getchar(); //tambien para qquitar asi como el enter pero este es para el scanf

        printf("Puntos asignados: ");
        scanf("%f", &puntos);
        getchar();

        fprintf(examen, ":p;%s\n",   pregunta);
        fprintf(examen, ":op1;%s\n", op1);
        fprintf(examen, ":op2;%s\n", op2);
        fprintf(examen, ":op3;%s\n", op3);
        fprintf(examen, ":op4;%s\n", op4);
        fprintf(examen, ":r;%s\n",   opc);
        fprintf(examen, "%.0f.\n",   puntos);
    }

    printf("\nExamen guardado correctamente!\n");
    fclose(examen);
}

void lista(){
    char nombre[100];
    int cont = 1;

    FILE *archivoLista = fopen("lista.txt", "r");
    if (archivoLista == NULL){
        printf("No hay examenes registrados.\n");
        return;
    }

    printf("\n LISTA DE EXAMENES: \n");
    while(fgets(nombre, 100, archivoLista) != NULL){
        nombre[strcspn(nombre, "\n")] = '\0';
        if(strlen(nombre) > 0)
            printf("%d.- %s\n", cont++, nombre);
    }
    fclose(archivoLista);
}
}
