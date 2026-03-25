#include <stdio.h>
#include <iostring.h>
#include <pila.h>


#define MAX 100

int palindromo(char *cadena);
int verificarParentesis(char *cadena);

int main(void)
{
	char *cadena = NULL;
	
	inputCadenaDinamica("\n Captura cadena: ",&cadena,MAX);
	printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");
	
	inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
	printf(" Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
	
	free(cadena);
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}



int palindromo(char *cadena)
{
	Pila pila = {NULL, 0, -1, NULL, NULL};
	char *ptr;
	ptr = cadena;
	while(*ptr != '\0')
	{
		pushDato(&pila, ptr);
		ptr++;
	}
	ptr = cadena;
	char *dato = pila.cima->dato;
	while(*ptr==*dato)
	{
		popNodo(&pila);
		if(pila.cima==NULL)
			return 1;
	}
	return 0;
}

int verificarParentesis(char *cadena)
{
	Pila pila = {NULL, 0, -1, NULL, NULL};
	char *ptr;
	char *dato;
	ptr = cadena;
	//parentesis = 40 "(", 40+1 ")"
	//corchetes =  91 "[", 91+2 "]"
	//llaves = 123 "{", 123+2 "}"
	
	//verificar que sea el ascii correcto, se realiza push
	//  (x+3)[]
	while(*ptr != '\0')
	{
		if(*ptr=='('||*ptr=='['||*ptr=='{')
		{
			pushDato(&pila, ptr);
			ptr++;

			}if(*ptr==')'||*ptr==']'||*ptr=='}')
		{
			if(pila.cima!=NULL)
				dato = pila.cima->dato;
			else
				return 0;
			if((*ptr==')' && *dato=='(')||(*ptr==']'&& *dato=='[')||(*ptr=='}'&& *dato=='{'))
			{	
				popNodo(&pila);
			}
		}
		ptr++;
	}
	if(pila.cima==NULL)
		return 1;
	else
		return 0;
}