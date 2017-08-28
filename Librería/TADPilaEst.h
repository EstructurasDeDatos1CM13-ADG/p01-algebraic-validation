/************************************************************************
* LIBRERIA: TAD Pila Estática 						*
* AUTORES:								*
* - Alanís Ramírez Damián						*
* - Mendieta Torres Alfonso Ulises					*
* - Oledo Gilberto							*
*									*									*
* DESCRIPCIÓN: TAD pila o stack.					*
* Estructura de datos en la cual se cumple:				*
* Los elementos se añaden y remueven por un solo extremo (siguiendo el 	*
* criterio LIFO - Last In First Out).					*
* Este extremo se llama "tope" de la pila.				*
* 									*									*
* OBSERVACIONES: Hablamos de una estructura de datos estática cuando se *
* le asigna una cantidad fija de memoria antes de la ejecución del pro- *
* grama.								*												
*************************************************************************/

//DEFINICIONES DE CONSTANTES
#define MAX_ELEMENT 1000
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATOS

//Definición de un boolean con un char
typedef unsigned char boolean;
//Definición de un elemento con un estructura Elemento
typedef struct elemento{ 			//Define una estructura Elemento
	//Variables de la estructura elemento, el usuario puede crear y/o modificarlas
	char c;	
	int n;						//Permitirá introducir caracteres como '(' o '+'
	//***
	//***
	//***
}elemento;							//Define un tipo de dato llamado elemento
//Definición de una pila por medio de una estructura Pila que contiene puntero a Elemento
typedef struct pila{
	elemento arreglo[MAX_ELEMENT];	//La pila es un arreglo estático de MAX_ELEMENT
	int tope;						//El tope es un entero (índice del arreglo de elementos)
}pila;

//DECLARACIÓN DE FUNCIONES

/* Nota:
   La variable tipo pila se pasa por referencia debido a que si no se hace así se perdería todo cambio
   sobre esa variable pues se pasa por valor, y es una variable local de la función. Pasando por refe-
   rencia se logra que la variable pila conserve sus modificaciones en cualquier otra función o segmen-
   to del programa.

   Siempre que se trabaje con estructuras de datos se pasan los tipos de datos por REFERENCIA.
*/

void Initialize(pila *s);			//Inicializa la pila para su uso
void Push(pila *s, elemento e);		//Empila (introduce un elemento en la cima de la pila)
elemento Pop(pila *s);				//Desempila (saca el elemento de la pila)
boolean Empty(pila *s);				//Vacia (pregunta si la pila esta vacia y retorna TRUE o FALSE)
elemento Top(pila *s);				//Devuelve el elemento que se encuentra en el tope sin extraerlo
int Size(pila *s);					//Tamaño de la pila, obtiene el número de elementos de la pila
void Destroy(pila *s);				//Elimina pila (borra todos los elementos y a la pila de memoria)

