// QUESTÃO 1

#include <stdio.h>
#define TAM 100

int fila[TAM];
int inicio = 0, fim = 0;

void enfileirar(int valor) {
    if (fim == TAM) {
        printf("Fila cheia!\n");
    } else {
        fila[fim] = valor;
        fim++;
    }
}

void desenfileirarMultiplos2() {
    if (inicio == fim) {
        printf("Fila vazia!\n");
    } else {
        printf("Multiplos de 2:\n");

        while (inicio < fim) {
            if (fila[inicio] % 2 == 0) {
                printf("%d\n", fila[inicio]);
            }
            inicio++;
        }
    }
}

int main() {
    int opcao, num;

    do {
        printf("\n1 - Enfileirar numero positivo\n");
        printf("2 - Desenfileirar tudo e mostrar multiplos de 2\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                printf("Digite um numero positivo: ");
                scanf("%d", &num);

                if(num > 0) {
                    enfileirar(num);
                } else {
                    printf("Numero invalido!\n");
                }
                break;

            case 2:
                desenfileirarMultiplos2();
                break;

            case 3:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 3);

    return 0;
}

//QUESTÃO 2

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 100

char fila[TAM];
char pilha[TAM];

int inicio = 0, fim = 0;
int topo = -1;

void enfileirar(char c) {
    fila[fim] = c;
    fim++;
}

char desenfileirar() {
    char c = fila[inicio];
    inicio++;
    return c;
}

void empilhar(char c) {
    topo++;
    pilha[topo] = c;
}

char desempilhar() {
    char c = pilha[topo];
    topo--;
    return c;
}

int main() {

    char texto[TAM];
    int i;

    printf("Digite uma sequencia de caracteres: ");
    fgets(texto, TAM, stdin);

    for(i = 0; texto[i] != '\0'; i++) {
        enfileirar(texto[i]);
    }

    while(inicio < fim) {

        char c = desenfileirar();

        if(isalpha(c)) {
            empilhar(tolower(c));
        } else {
            empilhar(c);
        }
    }

    printf("\nResultado:\n");

    while(topo >= 0) {
        printf("%c", desempilhar());
    }

    return 0;
}

//QUESTÃO 3

#include <stdio.h>

#define TAM 5

int fila[TAM];
int inicio = 0, fim = 0, qtd = 0;

void enfileirar(int valor) {

    if(qtd == TAM) {
        printf("Fila cheia!\n");
    } else {
        fila[fim] = valor;
        fim = (fim + 1) % TAM;
        qtd++;
    }
}

int desenfileirar() {

    int valor = fila[inicio];

    inicio = (inicio + 1) % TAM;
    qtd--;

    return valor;
}

int main() {

    int opcao, valor;

    do {

        printf("\n1 - Enfileirar valor\n");
        printf("2 - Desenfileirar e mostrar dobro\n");
        printf("3 - Desenfileirar tudo\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                printf("Digite um valor inteiro nao nulo: ");
                scanf("%d", &valor);

                if(valor != 0) {
                    enfileirar(valor);
                } else {
                    printf("Valor invalido!\n");
                }

                break;

            case 2:

                if(qtd == 0) {
                    printf("Fila vazia!\n");
                } else {
                    valor = desenfileirar();
                    printf("Dobro: %d\n", valor * 2);
                }

                break;

            case 3:

                if(qtd == 0) {
                    printf("Fila vazia!\n");
                } else {

                    printf("Valores:\n");

                    while(qtd > 0) {
                        printf("%d\n", desenfileirar());
                    }
                }

                break;

            case 4:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 4);

    return 0;
}

//QUESTÃO 4

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 100

char filaA[TAM];
int filaB[TAM];

int iniA = 0, fimA = 0;
int iniB = 0, fimB = 0;

void enfileirarA(char c) {
    filaA[fimA] = c;
    fimA++;
}

void enfileirarB(int n) {
    filaB[fimB] = n;
    fimB++;
}

int main() {

    char texto[TAM];
    int i;

    printf("Digite um vetor de caracteres: ");
    fgets(texto, TAM, stdin);

    for(i = 0; texto[i] != '\0'; i++) {

        if(isdigit(texto[i])) {

            enfileirarB(texto[i] - '0');

        } else if(isalpha(texto[i])) {

            enfileirarA(texto[i]);
        }
    }

    printf("\nFila B (numeros):\n");

    while(iniB < fimB) {
        printf("%d ", filaB[iniB]);
        iniB++;
    }

    printf("\n\nFila A (letras):\n");

    while(iniA < fimA) {
        printf("%c ", filaA[iniA]);
        iniA++;
    }

    return 0;
}
