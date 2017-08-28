/************************************************************************
* IMPLEMENTACIÓN DE LA LIBRERÍA TAD PILA ESTÁTICA						*
* AUTORES:																*
* - Alanís Ramírez Damián												*
* - Mendieta Torres Alfonso Ulises										*
* - Oledo Gilberto														*
*																		*
* DESCRIPCIÓN: TAD pila o stack.										*
* Estructura de datos en la cual se cumple:								*
* Los elementos se añaden y remueven por un solo extremo (siguiendo el 	*
* criterio LIFO - Last In First Out).									*
* Este extremo se llama "tope" de la pila.								*
* 																		*
* OBSERVACIONES: Hablamos de una estructura de datos estática cuando se *
* le asigna una cantidad fija de memoria antes de la ejecución del pro- *
* grama.																*
*																		*
* COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc -c TADPilaEst.c 		*												
*************************************************************************/

//LIBRERIAS
#include "TADPilaEst.h"

//DEFINICIÓN DE FUNCIONES

/*
void Initialize(pila *s);
Descripción: Inicializar pila (Iniciar una pila para su uso)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: 
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, 
si esto no ha pasado se producirá un error.
*/
void Initialize(pila *s){
	s -> tope = -1;		//(*s).tope = -1 
	return;
}

/*
void Push(pila *s, elemento e);
Descripción: Esta función empila un elemento (lo introduce a la pila)
Recibe: pila *s (Referencia a la pila "s" a operar), elemento e (Elemento a introducir en la pila)
Devuelve:
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida el indice del arreglo (tope) si esta fuera del arreglo es decir hay desbordamiento
y se producirá un error.
*/
void Push(pila *s, elemento e){
	(*s).tope++;
	(*s).arreglo[(*s).tope] = e; //(*s).tope es el índice, es el tope, en el cual se introduce el elemento
	return;
}

/*
elemento Pop(pila *s);
Descripción: Desempila (extrae un elemento de la pila)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: elemento (Elemento e extraido de la pila)
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida si la pila esta vacia (tope == -1) antes de desempilar (causa error desempilar si la pila es vacía)
*/
elemento Pop(pila *s){
	elemento e;	
	e = (*s).arreglo[(*s).tope];	//guarda en e el valor contenido en arreglo[tope] de la pila s
	(*s).tope--;					//reduce en 1 el tope debido a que ya se extrajo un elemento
	return e;
}	

/*
boolean Empty(pila *s);
Descripción: ¿Es vacia? (Preguntar si la pila esta vacia)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
*/
boolean Empty(pila *s){
	/*
	boolean b;
	if(s-> tope == -1) b = TRUE;
	else b = FALSE;
	return b;
	*/
	return (s -> tope == -1)?TRUE:FALSE;//esta expresión es equivalente a todo el bloque anterior
}

/*
elemento Top(pila *s);
Descripción: Tope (Obtener el "elemento" del tope de la pila si extraerlo de la pila)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: elemento (Elemento del tope de la pila)
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida si la pila esta vacia antes de consultar al elemento del tope (causa error si esta esta vacía).
*/
elemento Top(pila *s){					//se diferencia de Pop en que este no lo saca de la pila, solo lo muestra
	elemento e;
	e = (*s).arreglo[(*s).tope];
	return e;
}

/*
elemento Size(pila *s);
Descripción: Función que devuelve el tamaño de la pila (Obtener el número de elementos en la pila)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: int (Tamaño de la pila -1->Vacia, 1->1 elemento, 2->2 elementos, ...)
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
*/
int Size(pila *s){
	int size;
	size = s -> tope +1;				//debido a que tope inicialmente es -1
	return size;
}

/*
void Destroy(pila *s);
Descripción: Elimina pila (Borra a todos los elementos en a la pila de memoria)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve: 
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella.
*/
void Destroy(pila *s){
	Initialize(s);
	return;
}