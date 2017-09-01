/************************************************************************
* PROGRAMA: validarAlgebraPila.c                                        *
* AUTORES:                                                              *
* - Alanís Ramírez Damián                                               *
* - Mendieta Torres Alfonso Ulises                                      *
* - Oledo Gilberto                                                      *
* VERSIÓN: 1.5                                                          *
*                                                                       *
* DESCRIPCIÓN: Programa que pide una cadena de caracteres (expresión al-*
* gebraica) y procede a analizar los paréntesis, realizar la conversión *
* a postfijo y da la correspondiente solución. Esto por medio del uso de*
* la libreria TADPila(Est|Din).h creada en clase.                       *
*                                                                       *
* Compilación: cd (ruta_archivos)                                       *
* gcc -o validarAlgebraPila validarAlgebraPila.c TADPila(Est|Din).c     *
*************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "TADPilaDin.h"

//DEFINICIONES
#define MAX 100

//VARIABLES GLOBALES
elemento e1;	//Crea un elemento e1
pila p1;		//Crea una pila p1
int indice = 0; //índice del arreglo salidaPostfijo[], debe estar disponible de forma global
//para poder ser modificado desde cualquier instancia del programa

//DECLARACIÓN DE FUNCIONES
boolean otroProceso();
boolean validarParentesis(char const *cadena);
int precedencia(char c);
boolean esOperador(char c);
void pasarPostfijo(char const *cadena);
float solucionAlgebra(char const *cadena, int n);
float Multiplicacion(float a, float b);
float Suma(float a, float b);
float Resta(float a, float b);
float Division(float a, float b);
float Potencia(float a, float b);

//MAIN
int main(){
	//DECLARACIÓN DE VARIABLES DEL MAIN
	char expresion[MAX]; //Arreglo que contendrá a la expresión algebráica
	int i;				 //Variable para un contador
	while(1){
		Initialize(&p1);//Inicializa la pila p1
		indice = 0; 	//Resetea el índice del arreglo salidaPostfijo a 0
		//Impresión de las instrucciones y precondiciones del programa
		printf("Programa que valida y resuelve expresiones algebraicas por medio del TAD pila");
		printf("\nIntroduzca una expresion algebraica considerando: ");
		printf("\n + = Suma \t\t - = Resta \n / = Division \t\t * = Multiplicacion \n ^ = Potencia\n");
		printf("Puede introducir parentesis, los cuales seran validados\n");
		printf("Como ejemplo, puede introducir una expresion como (a+b)^a-c\n");
		printf("NOTA: procure no dejar espacios");
		printf("\n\n A continuacion introduzca su expresion: ");
		scanf("%s",expresion);
		if(validarParentesis(expresion) == TRUE){ //Llama a la función validarParentesis, si son correctos continua
			printf("\nParentesis correctos, se procedera a realizar conversion a postfijo\n");//la conversión
			Destroy(&p1); //Destruye la pila p1 para ser empleada nuevamente en la función pasarPostfijo(expresion)
			pasarPostfijo(expresion); //Manda a llamar a pasarPostfijo, pasándole expresion como argumento tipo char const *cadena
		}
		else{ //Si los parentesis no son correctos imprime una alerta y lleva a la parte del ciclo en la que se llama a otroProceso()
			printf("\n Parentesis incorrectos, revise la sintaxis \n");
		}
		if(otroProceso() == TRUE){ //Si la función devuelve TRUE se destruye la pila y se limpia el buffer
			Destroy(&p1);
			getchar();
			setbuf(stdin, NULL);
		}
		else break; //Si no se desea otro proceso (la función devuelve FALSE) se sale del while(1) y main retorna 0
	}
	getchar();
	return 0;
}

//DEFINICIÓN DE FUNCIONES

/*
 boolean otroProceso()
 Descripción: imprime letrero y solicita una respuesta al usuario sobre si 
 quiere introducir otra expresión.
 Recibe: -
 Devuelve: TRUE si el usuario teclea 's' ó 'S' y FALSE si teclea 'n' o 'N'
 Observaciones: el usuario ha introducido unicamente letras del siguiente conjunto
 {'s','S','n','N'}
*/
boolean otroProceso(){
	char sn, respuesta[20];
	printf("\n\n\t Desea introducir otra expresion (s|S, n|N)?: ");
	setbuf(stdin, NULL);
	scanf("%c",&sn);
	printf("\n Usted selecciono %c \n", sn);
	return (sn == 's' || sn == 'S')?TRUE:FALSE;
}

/*
 int tamanoReal(char const *cadena)
 Descripción: recibe una cadena y devuelve el tamaño de esta (excluyendo a los
 paréntesis del conteo)
 Recibe: una cadena de caracteres (char const *cadena)
 Devuelve: resultado, es decir, el tamaño de la cadena sin paréntesis
*/
int tamanoReal(char const *cadena){
	int i, resultado = 0;
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] != '(' && cadena[i] != ')') resultado++;
	}
	return resultado;
}

/* 
boolean validarParentesis(char const *cadena)
Descripción: valida los paréntesis de una expresión algebráica
Recibe: una cadena de caracteres (char const *cadena)
Devuelve: TRUE si los paréntesis son correctos o FALSE si son incorrectos
Observaciones: el usuario ha introducido la expresión y esta se ha guardado en una cadena que
se pasa por referencia
*/
boolean validarParentesis(char const *cadena){
	int i;
	printf("\n Su expresion %s fue guardada correctamente. \nSe procedera a validar parentesis\n", cadena);
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
 int precedencia(char c)
 Descripción: analiza el número que le correspondería a un operador en la jerarquía
 de operadores.
 Recibe: un caracter (char c)
 Devuelve: un entero del 1 al 3 según sea la jerarquía del operador para la conversión
 a postfijo
*/
int precedencia(char c){
	int resultado;
	switch(c){
		case '+': resultado = 1; break;
		case '-': resultado = 1; break;
		case '*': resultado = 2; break;
		case '/': resultado = 2; break;
		case '^': resultado = 3; break;
		case '(': resultado = 0; break;
	}
	return resultado;
}

/*
 boolean esOperador(char c)
 Descripción: determina si un caracter es o no un operando.
 Recibe: un caracter (char c)
 Devuelve: TRUE si es un operador o FALSE si no lo es
*/
boolean esOperador(char c){
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')?TRUE:FALSE;
}

/*
 float Suma(float a, float b)
 Descripción: suma dos flotantes y devuelve el resultado
 Recibe: dos números flotantes (float a, float b)
 Devuelve: el resultado de sumar a y b, como dato de tipo flotante
*/
float Suma(float a, float b){
	float resultado;
	resultado = a + b;
	return resultado;
}

/*
 float Resta(float a, float b)
 Descripción: resta un flotante a otro y devuelve el resultado
 Recibe: dos números flotantes (float a, float b)
 Devuelve: el resultado de la resta a - b, como dato de tipo flotante
*/
float Resta(float a, float b){
	float resultado;
	resultado = a - b;
	return resultado;
}

/*
 float Multiplicacion(float a, float b)
 Descripción: multiplica dos flotantes y devuelve el resultado
 Recibe: dos números flotantes (float a, float b)
 Devuelve: el resultado de multiplicar a y b, como dato de tipo flotante
*/
float Multiplicacion(float a, float b){
	float resultado;
	resultado = a * b;
	return resultado;
}

/*
 float Division(float a, float b)
 Descripción: divide un flotante entre otro
 Recibe: dos números flotantes (float a, float b)
 Devuelve: el resultado de la división a/b, como dato de tipo flotante
*/
float Division(float a, float b){
	float resultado;
	resultado = a / b;
	return resultado;
}

/*
 float Potencia(float a, float b)
 Descripción: eleva un flotante a un exponente flotante
 Recibe: dos números flotantes (float a, float b)
 Devuelve: el resultado de la operación a^b, como dato de tipo flotante
*/
float Potencia(float a, float b){
	double resultado;
	resultado = pow(a,b); //Función pow(a,b) eleva a a la b y requiere doubles para operar
	return (float)resultado; //Se realiza el casting a flotante para su incorporación a la pila
}

/*
 float solucionAlgebra(char const *cadena, int n)
 Descripción: función que obtiene el resultado de la expresión algebráica
 mediante el uso de la conversión a postfijo (que se le pasa como argumento)
 y que va pidiendo valores de las variables con el fin de dar la solución
 final de forma numérica
 Recibe: una cadena (salidaPostfijo) y un entero n que es el tamaño de esa cadena salidaPostfijo
 sin contar la basura que habia quedado almacenada en las posiciones libres del arreglo.
 Devuelve: el resultado de la expresión algebráica como tipo flotante
*/
float solucionAlgebra(char const *cadena, int n){
	int i;
	float val[27], valMarcado[27] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	/*
		val[27] esta relacionado con que cada letra del alfabeto va a ocupar una posición en ese arreglo,
		por ejemplo, la 'a' ocuparía val[0] y la 'z' val[26] respectivamente, de modo que cada vez que se
		repita una letra simplemente se direccionará al valor que guarda esa letra en el vector de valores.
		Asimismo, valMarcado sirve para saber si una posición del arreglo val (del 0 al 26) ya cuenta con
		el valor que va a tener esa letra cada vez que aparezca, es decir, nos ayuda a saber si el valor
		de una variable (letra) ya fue preguntado y almacenado en el vector val.
		Cuando cierta letra ha aparecido por primera vez, por defecto el valor en valMarcado es 1, una vez 
		que se le asigna un valor para cada vez que aparezca esa letra en la expresión, y que este valor se
		guarda en val[posición de la letra en el abecedario - 1] se modifica el valor de valMarcado[posición
		de la letra en el abecedario - 1] y pasa a ser 0, lo cual hara que cuando se lea el 0 se sepa que ya
		fue preguntado el valor de esa letra y ya esta almacenado en val[] para su consulta.
		Para hacerlo más cómodo, se consideró lo siguiente:
		el índice val[indice] se determina:
			indice = cadena[i] - 'a', es decir, el código ASCII del caracter contenido en cadena[i] - el valor
			del código ASCII de a, de modo que el resultado vaya de 0 a 26 y no de 97 a 122 como sería original-
			mente.
			Por ejemplo, el código ASCII de 'a' es 97, por lo que la posición a la que estaría relacionada en val
			sería 0 por ser la primera letra del alfabeto, lo cual se obtiene de

			a esta relacionada con val[cadena[i] - 'a']
			si cadena[i] = 'a' -> a esta relacionada con val['a' - 'a'] = val[0]
			es decir, una sola vez se pide el valor de a sie sta aparece en la expresión, y este valor se guarda en
			val[0], si a vuelve a aparecer más adelante en la expresión simplemente se consulta val[0]
	*/
	float resultado, a, b;
	setbuf(stdin, NULL);
	for(i = 0; i < n; i++){
		if(esOperador(cadena[i]) == FALSE){ //Este procedimiento solo se aplica a las letras y no a los operadores
			if(valMarcado[cadena[i] - 'a'] == 1 ){ //Para determinar si el valor ya ha sido indicado
				printf("\nIntroduzca un valor para '%c': ", cadena[i]); //Se pide por única vez el valor númerico de esa variable (letra)
				scanf("%f",&val[cadena[i] - 'a']);
				e1.n = val[cadena[i] - 'a']; //Se copia el valor a un tipo de dato elemento para poder pasarlo a la Pila
				Push(&p1,e1);	//Se apila el operando
				printf("\nOperando %f empilado correctamente", val[cadena[i] - 'a']);
				valMarcado[cadena[i] - 'a'] = 0; //Se modifica el valor de esa posición del arreglo para saber que ya se visitó
			}
			else{	//Ya no pide el valor, simplemente lo empila porque ya se había dado
				if(valMarcado[cadena[i] - 'a'] == 0 ){
					e1.n = val[cadena[i] - 'a'];
					Push(&p1, e1);
					printf("\nOperando %f empilado correctamente", val[cadena[i] - 'a']);
				}

			}
		}
		if(esOperador(cadena[i]) == TRUE && Empty(&p1) == FALSE){ //Si lo que encuentra en el recorrido de la cadena es un operador
			switch(cadena[i]){
				case '+': //Si encuentra un más 
					e1 = Pop(&p1); //Hace un Pop
					b = e1.n; // Guarda ese valor en una variable b
					e1 = Pop(&p1);
					a = e1.n;
					e1.n = Suma(a,b); //Llama a la función pasándole a y b como argumentos
					printf("\n Efectuando suma de %f + %f y empilando", a, b); 
					break;
				case '-':
					e1 = Pop(&p1);
					b = e1.n;
					e1 = Pop(&p1);
					a = e1.n;
					e1.n = Resta(a,b);
					printf("\n Efectuando resta: %f - %f y empilando", a, b);
					break;
				case '*':
					e1 = Pop(&p1);
					b = e1.n;
					e1 = Pop(&p1);
					a = e1.n;
					e1.n = Multiplicacion(a,b);
					printf("\n Efectuando multiplicacion: %f * %f y empilando", a, b);
					break;
				case '/':
					e1 = Pop(&p1);
					b = e1.n;
					e1 = Pop(&p1);
					a = e1.n;
					e1.n = Division(a,b);
					printf("\n Efectuando division: %f / %f y empilando", a, b);
					break;
				case '^':
					e1 = Pop(&p1);
					b = e1.n;
					e1 = Pop(&p1);
					a = e1.n;
					e1.n = Potencia(a,b);
					printf("\n Efectuando potencia: %f ^ %f y empilando", a, b);
					break;
			}
			Push(&p1, e1); //Apila el resultado de la operación que haya realizado
		}
	} // Va haciendo ese ciclo y realiza todas las operaciones hasta que recorre toda la cadena,
	e1 = Pop(&p1); //dejando un solo elemento en la pila, el cual es el resultado, así que se le hace Pop
	resultado = e1.n;
	return resultado; //Devuelve el resultado como tipo flotante de la expresión algebráica
}

/*
 void pasarPostfijo(char const *cadena)
 Descripción: función que realiza la conversión de la expresión en infijo a postfijo (la expresión
 en infijo se le pasa como argumento) y muestra la conversión en pantalla. Finalmente llama a 
 solucionAlgebra(...) y una vez que esta finaliza devuelve el control al main.
 Recibe: una cadena (expresión en infijo).
 Devuelve: 
*/
void pasarPostfijo(char const *cadena){
	int i, j, n, operadorAbajo, operadorArriba, tamano; //operadorAbajo y operadorArriba servirán para analizar jerarquía
	char salidaPostfijo[MAX]; //salidaPostfijo contendrá la expresión en postfijo
	indice = 0; //Pone el ínidice de salidaPostfijo en 0
	strcpy(salidaPostfijo, " ");
	setbuf(stdin, NULL);
	tamano = tamanoReal(cadena); //Guarda el tamaño de la cadena excluyendo los paréntesis
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] >= 97 && cadena[i] <= 122){ //Si es una letra minúscula de la 'a' a la 'z' (es decir, es un operando)
			salidaPostfijo[indice] = cadena[i]; //Directamente agrega el operando a salidaPostfijo
			printf("\n%i Operando detectado, agregado a arreglo salidaPostfijo[%d]", i+1, indice);
			indice++;
		}
		if(cadena[i] == '('){ //Cada paréntesis que abre hace un Push
			e1.c = cadena[i];
			Push(&p1, e1);
			printf("\n%d Analizando expresion, %c detectado", i+1, e1.c);
		}
		if(cadena[i] == ')' && Empty(&p1) == FALSE){ 
			j = 0;			  
			printf("\n%d ')' Detectado, sacando elementos de la pila hasta encontrar '('", i+1);
			do{					
				e1 = Pop(&p1); //Si se detecta paréntesis de cierre se sacán todos los operadores de la Pila
				if(esOperador(e1.c) == TRUE){
					printf("\n%d.%d Operador %c detectado y desempilado, pasado salidaPostfijo[%d]", i + 1, j, e1.c, indice);
					salidaPostfijo[indice] = e1.c; //Los operadores que van saliendo se van almacenando en salidaPostfijo
					indice ++;
				}
				j++;
			}while(e1.c != '(' && Empty(&p1) == FALSE);//Saca operadores hasta que llegue al '('
		}
		if(cadena[i] == '+' || cadena [i] == '-' || cadena[i] == '/' || cadena[i] == '*'){
			operadorArriba = precedencia(cadena[i]);//El operador que esta por entrar a la pila procede del escaneo de cadena
			if(Empty(&p1) == FALSE){
				e1 = Top(&p1);
				operadorAbajo = precedencia(e1.c);		//El operador que esta abajo del que se quiere introducir en la pila se obtiene con Top
			}
			else operadorAbajo = 0;
			if(operadorArriba <= operadorAbajo && Empty(&p1) == FALSE){ //Si el operador que se busca introducir es de menor jerarquía
				e1 = Pop(&p1); //hace un Pop explicando que un operador de menor prioridad no puede estar arriba de uno de mayor
				printf("\n Un operador '%c' no puede estar abajo de un operador '%c', pasando '%c' a salidaPostfijo[%d]", e1.c, cadena[i], e1.c, indice);
				salidaPostfijo[indice] = e1.c; //Guarda el operador que se sacó de la Pila en salidaPostfijo
				indice++;
				e1.c = cadena[i]; //Con el elemento conflictivo afuera será posible introducir el operador a la Pila
				Push(&p1, e1);
				printf("\n El operador '%c' ya pudo ser introducido a la pila", e1.c);
			}
			else{ //Si se cumple la jerarquía empila el operador sin problema alguno
				e1.c = cadena[i];
				Push(&p1, e1);
				printf("\n%d Analizando expresion, %c detectado y empilado", i+1, e1.c);
			}
		}
		if(cadena[i] == '^'){ //El '^' al ser el de mayor prioridad puede hacer una excepción a la comparación
			e1.c = cadena[i]; //y puede empilarse directamente
			Push(&p1, e1);
			printf("\n%d Analizando expresion, %c detectado y empilado", i+1, e1.c);
		}
	}
	j = i; //Se guarda el valor que tenía i al final del for en j simplemente para indicar subpasos (Ej 1.1, 1.2)
	n = Size(&p1); //n es igual al tamaño de la pila
	printf("\nEl tamano de la pila de operadores es: %d", n);
	for(i = 0; i < n; i++){ //Este ciclo for se hará para sacar cualquier operador que todavía quedara en la pila
		if(Empty(&p1) == FALSE){
			e1 = Pop(&p1);//y procede a guardarlos en salidaPostfijo
			salidaPostfijo[indice] = e1.c;
		}
		printf("\n%d.%d Se saco el operador %c de la pila y se agrego a salidaPostfijo[%d]", j + 1, i, e1.c, indice); 
		indice++;
	}
	if(Empty(&p1) == TRUE){ //Cuando se haya vaciado la pila se imprime la expresión en postfijo
		printf("\nLa pila esta vacia, a continuacion se imprimira la expresion en Postfijo: ");
		printf("\nExpresion en postfijo = ");
		for(i = 0; i < tamano; i++){
			printf("%c", salidaPostfijo[i]);
		}
		Destroy(&p1); //Se destruye la pila p1
		setbuf(stdin, NULL);
		printf("\n\n\n\n\t El resultado de la expresion es: %lf ",solucionAlgebra(salidaPostfijo, tamano)); //Se llama a la
		//función solucionAlgebra(char const *cadena, int n) y se le pasan la salidaPostfijo y el tamaño de la cadena 
		//original como argumentos, al finalizar retornará el resultado final, mismo que se imprimirá
	}
	else printf("\n ERROR Desconocido"); 
	return;
}
