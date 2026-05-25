#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>
#include <string.h>

#define MAX 256

void insertar(char arr[]);
int verificarParentesis(char *cadena);
int precedencias(char c);
void pasar( char posfix[], char infix[], Pila *pila);
void imprimirCad(char arr[]);
int main(void)
{
	Pila pila = {NULL, 0, 100, NULL, free};
	char infix [MAX];
	char posfix [MAX];
    int opc;
    do{
        printf("CONVERSION DE INFIX A POSTFIX\n");
        printf("1.infix\n");
        printf("2.salir\n");
        scanf("%d", &opc);
        getchar();

    
        switch (opc)
        {
        case 1:
            insertar(infix);
                        pasar(posfix, infix, &pila);
                                    imprimirCad(posfix);
            break;
        case 2:
            printf("bye");
            break;
        }
    } while (opc != 2);
	printf("\n\n FIN DE PROGRAMA\n\n");
	return 0;
}
//insertar infix
void insertar(char arr[])
{
	int check = 0;
	while (!check)
	{
		printf("Ingrese la cadena: ");
		fgets(arr, MAX, stdin);
		arr[strcspn(arr, "\n")] = '\0';

		if (verificarParentesis(arr) == 0)
			printf("Input incorrecto, intente de nuevo\n");
		else
			check = 1;
	}
	printf("Operacion lograda\n");
	return;
}
//pasar a posfix
void pasar( char posfix[], char infix[], Pila *pila)
{
	int i = 0, j = 0, top = 0;

	vaciarPila(pila);

	while (infix[i] != '\0' && infix[i] != '\n')
	{
		if (infix[i] != ' ' && infix[i] != 0)
		{
			top = precedencias(infix[i]);
            if(top==0)
            {
                posfix[j] = infix[i];
                j++;
            }else if (top == 4)
			{
				pushDato(pila, &infix[i]);
			}
			else if (top == 5)
			{
				while(pila->cima && precedencias(*(char*)pila->cima->dato) != 4)
				{
					posfix[j] = *(char*)popDato(pila);
					j++;
						
				}
                popDato(pila);
			}
			else if(top != 0)
			{
				while(pila->cima && precedencias(*(char*)pila->cima->dato) >= top && precedencias(*(char*)pila->cima->dato) != 4)
				{

                        posfix[j] = *(char*)popDato(pila);
                        j++;
				}
                pushDato(pila, &infix[i]);

			}
		}
		i++;
	}

	while(pila->cima)
	{
		posfix[j] = *(char*)popDato(pila);
		j++;
	}
	posfix[j] = '\0';
}
//verificar que se cierren los parentesis
int verificarParentesis(char *cadena)
{
	Pila pila = {NULL, 0, 100, NULL, NULL};
	char *ptr;
	char *dato;
	ptr = cadena;
	while(*ptr != '\0')
	{
		if(*ptr=='('||*ptr=='['||*ptr=='{')
		{
			pushDato(&pila, ptr);
			ptr++;
		}
		if(*ptr==')'||*ptr==']'||*ptr=='}')
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
int precedencias(char c)
{
	switch (c)
	{
		case '+': return 1;
		case '-': return 1;
		case '/': return 2;
		case '*': return 2;
		case '^': return 3;
		case '(': return 4;
		case ')': return 5;
		default:  return 0;
	}
}
void imprimirCad(char arr[])
{
	printf("Postfix: %s\n", arr);
}