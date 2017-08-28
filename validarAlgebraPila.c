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

//DECLARACIÓN DE FUNCIONES
boolean otroProceso();
boolean validarParentesis(char const *cadena);
double solucionAlgebra(char const *cadena);

//MAIN
int main(){
	//DECLARACIÓN DE VARIABLES CON UN TIPO DE DATO DEFINIDO POR EL USUARIO
	//DECLARACIÓN DE VARIABLES DEL MAIN
	char expresion[MAX], a[5] = {27,']','2','J',0};
	int i;
	Initialize(&p1); //Inicializa la pila p1
	while(1){
		//Impresión de las instrucciones y precondiciones del programa
		printf("Programa que valida y resuelve expresiones algebraicas por medio del TAD pila");
		printf("\nIntroduzca una expresion algebraica considerando: ");
		printf("\n + = Suma \t\t - = Resta \n / = Division \t\t * = Multiplicacion \n ^ = Potencia\n");
		printf("Puede introducir parentesis, los cuales seran validados\n");
		printf("Como ejemplo, puede introducir una expresion como (2+3)^2-4\n");
		printf("NOTA: procure no dejar espacios");
		printf("\n\n A continuacion introduzca su expresion: ");
		gets(expresion);
		if(validarParentesis(expresion) == TRUE) printf("\nParentesis correctos, se procedera a solucionar expresion\n");
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

/* 
double solucionAlgebra(char const *cadena)
Descripción: resuleve la expresion algebraica empleando TAD pila y arreglos
Recibe: una cadena de caracteres
Devuelve: el resultado de la expresión algebraica
Observaciones: el usuario ha introducido la expresión y esta se ha guardado en una cadena que
se pasa por referencia, además de que los paréntesis han sido validados
*/
/*
double solucionAlgebra(char const *cadena){
	double resultado;
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] == '(') Push
	}
	return resultado;
}
*/