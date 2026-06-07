/* 	PROYECTO - ESTRUCTURA DE DATOS
	EXAMENES

	Edgar Alejandro Vázquez Haro - 571846
	Rany Rey Guzmán Esparza - 566297
*/

#include <stdio.h>
#include <stdlib.h>

void menu();

int main(){
	
	menu();
	
	return 0;
}

void menu(){
	int opc;
	printf("\n----Menu----\n");
	printf("Generar un examen_________1\n");
	printf("Lista de examenes_________2\n");
	printf("Modificar un examen_______3\n");
	printf("Aplicar un examen_________4\n");
	printf("Salir_____________________5\n");
	printf("Seleccione una opcion: ");
	
	scanf("%d",&opc);
	
	do{
		switch(opc){
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
		}
	} while(opc != 5);
}