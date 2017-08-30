/************************************************************************
* PROGRAMA: validarAlgebraPila.c 										*
* AUTORES:																*
* - Alanís Ramírez Damián												*
* - Mendieta Torres Alfonso Ulises										*
* - Oledo Gilberto														*
*																		*
* DESCRIPCIÓN: Programa que pide una cadena de caracteres (expresión al-*
* gebraica) y procede a analizar los paréntesis, realizar la conversión *
* a postfijo y da la correspondiente solución. Esto por medio del uso de*
* la libreria TADPila(Est|Din).h creada en clase.						*
*																		*
* Compilación: cd (ruta_archivos)										*
* gcc -o validarAlgebraPila validarAlgebraPila.c TADPilaEst.c 			*
*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "TADPilaEst.h"

//DEFINICIONES
#define MAX 100

//VARIABLES GLOBALES
elemento e1;
pila p1;
int indice = 0;
int indiceOperador = 0;
char salidaPostfijo[MAX];
char operadores[MAX];

//DECLARACIÓN DE FUNCIONES
boolean otroProceso();
boolean validarParentesis(char const *cadena);
boolean jerarquiaOperadores(char c, char d);
void esOperando(char c, int i);
void esOperador(char const *cadena);
void pasarPostfijo(char const *cadena);
double solucionAlgebra(char const *cadena);

//MAIN
int main(){
	//DECLARACIÓN DE VARIABLES DEL MAIN
	char expresion[MAX];
	int i;
	while(1){
		Initialize(&p1); 		    	//Inicializa la pila p1
		indice = indiceOperador = 0; 	//Resetea el índice de los arreglos salidaPostfijo y operadores a 0
		//Impresión de las instrucciones y precondiciones del programa
		printf("Programa que valida y resuelve expresiones algebraicas por medio del TAD pila");
		printf("\nIntroduzca una expresion algebraica considerando: ");
		printf("\n + = Suma \t\t - = Resta \n / = Division \t\t * = Multiplicacion \n ^ = Potencia\n");
		printf("Puede introducir parentesis, los cuales seran validados\n");
		printf("Como ejemplo, puede introducir una expresion como (2+3)^2-4\n");
		printf("NOTA: procure no dejar espacios");
		printf("\n\n A continuacion introduzca su expresion: ");
		gets(expresion);
		if(validarParentesis(expresion) == TRUE){
			printf("\nParentesis correctos, se procedera a realizar conversión a posfijo\n");
			Destroy(&p1);
			pasarPostfijo(expresion);
		}
		else{
			printf("\n Parentesis incorrectos, revise la sintaxis \n");
			if(otroProceso() == TRUE) Destroy(&p1);
			else break;
		}
	}
	return 0;
}

//DEFINICIÓN DE FUNCIONES

boolean otroProceso(){
	char sn;
	printf("\n\n\t Desea introducir otra expresion (s|S, n|N)?: ");
	setbuf(stdin, NULL);
	scanf("%c",&sn);
	tolower(sn);
	return (sn == 's')?TRUE:FALSE;
}

/* 
boolean validarParentesis(char const *cadena)
Descripción: valida los paréntesis de una expresión algebráica
Recibe: una cadena de caracteres
Devuelve: TRUE si los paréntesis son correctos o FALSE si son incorrectos
Observaciones: el usuario ha introducido la expresión y esta se ha guardado en una cadena que
se pasa por referencia
*/
boolean validarParentesis(char const *cadena){
	int i;
	printf("\n Su expresión %s fue guardada correctamente. \nSe procedera a validar parentesis\n", cadena);
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] == '('){
			e1.c = cadena[i];
			Push(&p1, e1);
			printf("\n%i Parentesis '(' introducido a la pila", i+1);
		}
		if(cadena[i] == ')'){
			Pop(&p1);
			printf("\n%i Se detecto ')' por lo que se saco un '(' de la pila", i+1);
		}
	}
	return (Empty(&p1) == TRUE)?TRUE:FALSE;
}

void esOperando(char c, int i){
	if(c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/' && c != '^'){
		salidaPostfijo[indice] = c;
		printf("\n%i Operando detectado, agregado a arreglo salidaPostfijo[%d]", i+1, indice);
		indice++;
	}
	return;
}

void esOperador(char const *cadena){
	int i;
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] == '(' || cadena[i] == ')' || cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/' || cadena[i] == '^'){
			operadores[indiceOperador] = cadena[i];
			indiceOperador++;
		}
	}
	return;
}

boolean jerarquiaOperadores(char c, char d){
	boolean salida;
	if(Empty(&p1) == TRUE) salida = TRUE;
	else{
		switch(c){
			case '+':
				if(d == '*' || d == '/' || d == '^') salida = FALSE;
				else salida = TRUE;
				break;
			case '-':
				if(d == '*' || d == '/' || d == '^') salida = FALSE;
				else salida = TRUE;
				break;
			case '*':
				if(d == '^' || d == '/') salida = FALSE;
				else salida = TRUE;
				break;
			case '/':
				if(d == '^' || d == '*') salida = FALSE;
				else salida = TRUE;
				break;
			case '^':
				salida = TRUE;
				break;	
			default:
				salida = TRUE;
				break;	
		}
	}
	return salida;
}
void pasarPostfijo(char const *cadena){
	int i, j, n;
	esOperador(cadena);
	for(i = 0; i < strlen(cadena); i++){
		j = 0;
		esOperando(cadena[i], i);
		if(cadena[i] == '('){
			e1.c = cadena[i];
			Push(&p1, e1);
			printf("\n%d Analizando expresion, %c detectado", i+1, e1.c);
		}
		if(cadena[i] == ')'){
			do{
				e1 = Pop(&p1);
				printf("\n%d '(' Detectado, sacando elementos de la pila hasta encontrar ')'", i+1);
			}while(e1.c != '(');
		}
		if(cadena[i] == '+' || cadena [i] == '-' || cadena[i] == '/' || cadena[i] == '*'){
			if(jerarquiaOperadores(operadores[i + 1], operadores[j]) == FALSE){
				do{
					printf("\n%d.%d Jerarquia de operadores es menor al que se encuentra abajo, desempilando anterior", i+1, j);
					e1 = Pop(&p1);
					printf("\nEl operador %c fue desmpilado y colocado en el arreglo salidaPostfijo[%d]", e1.c, indice);
					salidaPostfijo[indice] = e1.c;
					indice++;
					j--;
				}while(jerarquiaOperadores(operadores[i + 1], operadores[j]) == FALSE);
			}
			else{
				e1.c = cadena[i];
				Push(&p1, e1);
				printf("\n%d Analizando expresion, %c detectado y empilado", i+1, e1.c);
			}
		}
		if(cadena[i] == '^'){
			e1.c = cadena[i];
			Push(&p1, e1);
			printf("\n%d Analizando expresion, %c detectado y empilado", i+1, e1.c);
		}
	}
	n = Size(&p1);
	printf("\nEl tamano de la pila de operadores es: %d", n);
	for(i = 0; i < n; i++){
		e1 = Pop(&p1);
		salidaPostfijo[indice + i] = e1.c;
	}
	if(Empty(&p1) == TRUE){
		printf("\nLa pila esta vacia, a continuacion se imprimira la expresion en Postfijo: ");
		printf("\nExpresion en postffijo = %s \n", salidaPostfijo);
	}
	else printf("\n ERROR Desconocido");
	return;
}
/*
double solucionAlgebra(char const *cadena)
Descripción: resuleve la expresion algebraica empleando TAD pila y arreglos
Recibe: una cadena de caracteres
Devuelve: el resultado de la expresión algebraica
Observaciones: el usuario ha introducido la expresión y esta se ha guardado en una cadena que
se pasa por referencia, además de que los paréntesis han sido validados
*/