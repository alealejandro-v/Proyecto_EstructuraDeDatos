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

Nodo* nuevoNodo(){
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->ant = NULL;
    n->sig = NULL;
    return n;
}

void liberarLista(Nodo *cabeza){
    Nodo *auxiliar;
    while(cabeza){
        auxiliar = cabeza->sig;
        free(cabeza);
        cabeza = auxiliar;
    }
}

int cargarExamen(const char *nombreArch, Nodo **cabeza){
    FILE *f = fopen(nombreArch, "r");
    if (f == NULL) return 0;

    *cabeza = NULL; // cabeza apunta al inicio de la lista
    Nodo *cola = NULL; // cola es para insertar al final sin recorrer toda la lista
    char linea[210];
    int count = 0;

    while(1){
        Nodo *n = nuevoNodo();
        int ok = 0;

        // leer hasta encontrar :p o que llegue al final
        while(fgets(linea, 210, f)){
            linea[strcspn(linea,"\n")] = '\0';
            if(strncmp(linea, ":p;", 3) == 0){
                strcpy(n->pregunta, linea+3);
                ok = 1;
                break;
            }
        }
        if(!ok){ free(n); break; }

        if(fgets(linea,210,f)){ 
			linea[strcspn(linea,"\n")]='\0'; strcpy(n->op1, linea+5); 
		}
        if(fgets(linea,210,f)){ 
			linea[strcspn(linea,"\n")]='\0'; strcpy(n->op2, linea+5); 
		}
        if(fgets(linea,210,f)){ 
			linea[strcspn(linea,"\n")]='\0'; strcpy(n->op3, linea+5); 
		}
        if(fgets(linea,210,f)){ 
			linea[strcspn(linea,"\n")]='\0'; strcpy(n->op4, linea+5); 
		}
        if(fgets(linea,210,f)){ 
			linea[strcspn(linea,"\n")]='\0'; strcpy(n->correcta, linea+3); 
		}
        if(fgets(linea,210,f)){ 
			n->puntos = atof(linea); 
		}

        if(*cabeza == NULL){
            *cabeza = n;
            cola = n;
        } else {
            cola->sig = n;
            n->ant    = cola;
            cola      = n;
        }
        count++;
    }
    fclose(f);
    return count;
}

void guardarExamen(const char *nombreArch, Nodo *cabeza){
    FILE *f = fopen(nombreArch, "w");
    if (f == NULL){ printf("Error al guardar.\n"); return; }

    Nodo *actual = cabeza;
    while(actual){
        fprintf(f, ":p;%s\n",   actual->pregunta);
        fprintf(f, ":op1;%s\n", actual->op1);
        fprintf(f, ":op2;%s\n", actual->op2);
        fprintf(f, ":op3;%s\n", actual->op3);
        fprintf(f, ":op4;%s\n", actual->op4);
        fprintf(f, ":r;%s\n",   actual->correcta);
        fprintf(f, "%.0f.\n",   actual->puntos);
        actual = actual->sig;
    }
    fclose(f);
}

void imprimirNodo(Nodo *n, int num){
    printf("\n-- Pregunta %d --\n", num);
    printf("P: %s\n",    n->pregunta);
    printf("op1: %s\n",  n->op1);
    printf("op2: %s\n",  n->op2);
    printf("op3: %s\n",  n->op3);
    printf("op4: %s\n",  n->op4);
    printf("Correcta: %s  |  Puntos: %.0f\n", n->correcta, n->puntos);
}

void modificar(){
    char nombre[100], nombreArch[110];
    char tecla;

    lista();
    printf("\nNombre del examen a modificar: ");
    scanf("%s", nombre);
    getchar();

    sprintf(nombreArch, "%s.txt", nombre);

    Nodo *cabeza = NULL;
    int total = cargarExamen(nombreArch, &cabeza);

    if(total == 0){
        printf("No se pudo cargar el examen o esta vacio.\n");
        return;
    }

    Nodo *actual = cabeza;
    int num = 1;

    printf("\nNavega: [d] siguiente  [a] anterior  [e] editar  [s] guardar y salir\n");

    do {
        imprimirNodo(actual, num);
        printf("\nOpcion: ");
        scanf(" %c", &tecla);
        getchar();

        if(tecla == 'd'){
            if(actual->sig){ actual = actual->sig; num++; }
            else printf("Ya estas en la ultima pregunta.\n");

        } else if(tecla == 'a'){
            if(actual->ant){ actual = actual->ant; num--; }
            else printf("Ya estas en la primera pregunta.\n");

        } else if(tecla == 'e'){
            printf("Nueva pregunta (Enter para dejar igual): ");
            char tmp[200];
            fgets(tmp, 200, stdin);
            tmp[strcspn(tmp,"\n")] = '\0';
            if(strlen(tmp) > 0) strcpy(actual->pregunta, tmp);

            printf("op1: "); fgets(tmp,100,stdin); tmp[strcspn(tmp,"\n")]='\0';
            if(strlen(tmp)>0) strcpy(actual->op1, tmp);
            printf("op2: "); fgets(tmp,100,stdin); tmp[strcspn(tmp,"\n")]='\0';
            if(strlen(tmp)>0) strcpy(actual->op2, tmp);
            printf("op3: "); fgets(tmp,100,stdin); tmp[strcspn(tmp,"\n")]='\0';
            if(strlen(tmp)>0) strcpy(actual->op3, tmp);
            printf("op4: "); fgets(tmp,100,stdin); tmp[strcspn(tmp,"\n")]='\0';
            if(strlen(tmp)>0) strcpy(actual->op4, tmp);

            printf("Respuesta correcta (op1/op2/op3/op4): ");
            scanf("%s", tmp); getchar();
            if(strlen(tmp)>0) strcpy(actual->correcta, tmp);

            printf("Puntos: ");
            float p; scanf("%f",&p); getchar();
            actual->puntos = p;

            printf("Cambios aplicados.\n");
        }

    } while(tecla != 's');

    guardarExamen(nombreArch, cabeza);
    printf("Examen guardado correctamente.\n");
    liberarLista(cabeza);
}

void aplicar(){
    char nombre[100], nombreArch[110];
    char tecla, respuesta[5];

    lista();
    printf("\nNombre del examen a aplicar: ");
    scanf("%s", nombre);
    getchar();

    sprintf(nombreArch, "%s.txt", nombre);

    Nodo *cabeza = NULL;
    int total = cargarExamen(nombreArch, &cabeza);

    if(total == 0){
        printf("No se pudo cargar el examen o esta vacio.\n");
        return;
    }

    // guardar respuestas del alumno
    // uso memoria dinamica porque no se cuantas preguntas tendra el examen
    char **respuestas = (char**)malloc(total * sizeof(char*));
    for(int i = 0; i < total; i++){
        respuestas[i] = (char*)malloc(5 * sizeof(char));
        strcpy(respuestas[i], "");
    }

    Nodo *actual = cabeza;
    int num = 1;

void eliminar(){
    char nombre[100], nombreArch[110];

    lista();
    printf("\nNombre del examen a eliminar: ");
    scanf("%s", nombre);
    getchar();

    sprintf(nombreArch, "%s.txt", nombre);

    // el remove es para borrar el archivo del examen que elijas
    if(remove(nombreArch) != 0){
        printf("No se encontro el archivo %s\n", nombreArch);
        return;
    }

    FILE *archivoLista = fopen("lista.txt", "r");
    FILE *temporal     = fopen("temp.txt",  "w");

    if(archivoLista == NULL || temporal == NULL){
        printf("Error al actualizar la lista.\n");
        return;
    }

    char linea[100];
    while(fgets(linea, 100, archivoLista)){
        linea[strcspn(linea,"\n")] = '\0';
        if(strcmp(linea, nombre) != 0)
            fprintf(temporal, "%s\n", linea);
    }

    fclose(archivoLista);
    fclose(temporal);

    remove("lista.txt");
    rename("temp.txt", "lista.txt");

    printf("Examen '%s' eliminado correctamente.\n", nombre);
}
