// QUESTÃO 1

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializar(Fila *f) { f->inicio = 0; f->fim = -1; f->tamanho = 0; }
int vazia(Fila *f)         { return f->tamanho == 0; }
int cheia(Fila *f)         { return f->tamanho == MAX; }

int enfileirar(Fila *f, int valor) {
    if (cheia(f)) { printf("Fila cheia!\n"); return 0; }
    f->fim = (f->fim + 1) % MAX;
    f->dados[f->fim] = valor;
    f->tamanho++;
    return 1;
}

int desenfileirar(Fila *f, int *valor) {
    if (vazia(f)) return 0;
    *valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;
    return 1;
}

int main(void) {
    Fila f;
    inicializar(&f);
    int opcao = 0, valor;

    do {
        printf("\n=== MENU - FILA SEQUENCIAL ===\n");
        printf("1. Enfileirar numero inteiro positivo\n");
        printf("2. Desenfileirar tudo e imprimir multiplos de 2\n");
        printf("3. Terminar programa\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) break;   /* EOF ou erro */

        switch (opcao) {
            case 1:
                printf("Digite um numero inteiro positivo: ");
                if (scanf("%d", &valor) != 1) break;
                if (valor <= 0) {
                    printf("Valor invalido! Digite um numero positivo.\n");
                } else if (enfileirar(&f, valor)) {
                    printf("Numero %d enfileirado com sucesso.\n", valor);
                }
                break;

            case 2:
                if (vazia(&f)) {
                    printf("Fila vazia!\n");
                } else {
                    printf("Multiplos de 2 encontrados: ");
                    int encontrou = 0;
                    while (desenfileirar(&f, &valor)) {
                        if (valor % 2 == 0) { printf("%d ", valor); encontrou = 1; }
                    }
                    if (!encontrou) printf("(nenhum)");
                    printf("\nFila esvaziada.\n");
                }
                break;

            case 3:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}
//QUESTÃO 2

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 200

/* ── Fila de char ── */
typedef struct {
    char dados[MAX];
    int inicio;
    int fim;
    int tamanho;
} FilaChar;

void fila_init(FilaChar *f) {
    f->inicio  = 0;
    f->fim     = -1;
    f->tamanho = 0;
}

int fila_vazia(FilaChar *f) { return f->tamanho == 0; }
int fila_cheia(FilaChar *f) { return f->tamanho == MAX; }

int fila_enfileirar(FilaChar *f, char c) {
    if (fila_cheia(f)) return 0;
    f->fim = (f->fim + 1) % MAX;
    f->dados[f->fim] = c;
    f->tamanho++;
    return 1;
}

int fila_desenfileirar(FilaChar *f, char *c) {
    if (fila_vazia(f)) return 0;
    *c = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;
    return 1;
}

/* ── Pilha de char ── */
typedef struct {
    char dados[MAX];
    int topo;
} Pilha;

void pilha_init(Pilha *p) { p->topo = -1; }

int pilha_vazia(Pilha *p) { return p->topo == -1; }
int pilha_cheia(Pilha *p) { return p->topo == MAX - 1; }

int pilha_empilhar(Pilha *p, char c) {
    if (pilha_cheia(p)) return 0;
    p->dados[++p->topo] = c;
    return 1;
}

int pilha_desempilhar(Pilha *p, char *c) {
    if (pilha_vazia(p)) return 0;
    *c = p->dados[p->topo--];
    return 1;
}

int main(void) {
    FilaChar fila;
    Pilha    pilha;

    fila_init(&fila);
    pilha_init(&pilha);

    char entrada[MAX];
    printf("Digite uma sequencia de caracteres: ");
    fgets(entrada, MAX, stdin);

    /* Remove newline */
    int len = strlen(entrada);
    if (len > 0 && entrada[len - 1] == '\n')
        entrada[len - 1] = '\0';

    /* Enfileira todos os caracteres */
    for (int i = 0; entrada[i] != '\0'; i++) {
        fila_enfileirar(&fila, entrada[i]);
    }

    printf("Sequencia enfileirada: %s\n", entrada);

    /* Desenfileira e empilha com conversão */
    char c;
    while (fila_desenfileirar(&fila, &c)) {
        if (isalpha((unsigned char)c)) {
            pilha_empilhar(&pilha, (char)tolower((unsigned char)c));
        } else {
            pilha_empilhar(&pilha, c);
        }
    }

    /* Desempilha e exibe */
    printf("Resultado apos desempilhar: ");
    while (pilha_desempilhar(&pilha, &c)) {
        printf("%c", c);
    }
    printf("\n");

    return 0;
}
//QUESTÃO 3

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
    int contador;
} FilaCircular;

void inicializar(FilaCircular *f) { f->inicio = 0; f->fim = 0; f->contador = 0; }
int vazia(FilaCircular *f) { return f->contador == 0; }
int cheia(FilaCircular *f) { return f->contador == MAX; }

int enfileirar(FilaCircular *f, int valor) {
    if (cheia(f)) { printf("Fila cheia!\n"); return 0; }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    f->contador++;
    return 1;
}

int desenfileirar(FilaCircular *f, int *valor) {
    if (vazia(f)) return 0;
    *valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->contador--;
    return 1;
}

int main(void) {
    FilaCircular f;
    inicializar(&f);
    int opcao = 0, valor;

    do {
        printf("\n=== MENU - FILA CIRCULAR ===\n");
        printf("1. Enfileirar valor inteiro nao nulo\n");
        printf("2. Desenfileirar um valor (exibe o dobro)\n");
        printf("3. Desenfileirar tudo (sem alteracao)\n");
        printf("4. Terminar programa\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                printf("Digite um valor inteiro nao nulo: ");
                if (scanf("%d", &valor) != 1) break;
                if (valor == 0) {
                    printf("Valor invalido! O numero nao pode ser zero.\n");
                } else if (enfileirar(&f, valor)) {
                    printf("Valor %d enfileirado.\n", valor);
                }
                break;

            case 2:
                if (vazia(&f)) {
                    printf("Fila vazia!\n");
                } else if (desenfileirar(&f, &valor)) {
                    printf("Valor desenfileirado: %d | Dobro: %d\n", valor, valor * 2);
                }
                break;

            case 3:
                if (vazia(&f)) {
                    printf("Fila vazia!\n");
                } else {
                    printf("Valores desenfileirados: ");
                    while (desenfileirar(&f, &valor)) printf("%d ", valor);
                    printf("\nFila esvaziada.\n");
                }
                break;

            case 4:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}

//QUESTÃO 4

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 200

/* ── Fila A: simples de char ── */
typedef struct {
    char dados[MAX];
    int inicio;
    int fim;
    int tamanho;
} FilaChar;

void filaA_init(FilaChar *f) {
    f->inicio  = 0;
    f->fim     = -1;
    f->tamanho = 0;
}

int filaA_vazia(FilaChar *f) { return f->tamanho == 0; }
int filaA_cheia(FilaChar *f) { return f->tamanho == MAX; }

int filaA_enfileirar(FilaChar *f, char c) {
    if (filaA_cheia(f)) return 0;
    f->fim = (f->fim + 1) % MAX;
    f->dados[f->fim] = c;
    f->tamanho++;
    return 1;
}

int filaA_desenfileirar(FilaChar *f, char *c) {
    if (filaA_vazia(f)) return 0;
    *c = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;
    return 1;
}

/* ── Fila B: circular de int com contador ── */
typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
    int contador;
} FilaCircularInt;

void filaB_init(FilaCircularInt *f) {
    f->inicio   = 0;
    f->fim      = 0;
    f->contador = 0;
}

int filaB_vazia(FilaCircularInt *f) { return f->contador == 0; }
int filaB_cheia(FilaCircularInt *f) { return f->contador == MAX; }

int filaB_enfileirar(FilaCircularInt *f, int valor) {
    if (filaB_cheia(f)) return 0;
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    f->contador++;
    return 1;
}

int filaB_desenfileirar(FilaCircularInt *f, int *valor) {
    if (filaB_vazia(f)) return 0;
    *valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->contador--;
    return 1;
}

int main(void) {
    FilaChar      filaA;
    FilaCircularInt filaB;

    filaA_init(&filaA);
    filaB_init(&filaB);

    char entrada[MAX];
    printf("Digite uma sequencia de caracteres: ");
    fgets(entrada, MAX, stdin);

    /* Remove newline */
    int len = strlen(entrada);
    if (len > 0 && entrada[len - 1] == '\n')
        entrada[len - 1] = '\0';

    printf("Entrada: %s\n\n", entrada);

    /* Distribui nas filas */
    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];
        if (isdigit((unsigned char)c)) {
            int num = c - '0';  /* converte dígito para valor numérico real */
            filaB_enfileirar(&filaB, num);
        } else if (isalpha((unsigned char)c)) {
            filaA_enfileirar(&filaA, c);
        }
        /* outros caracteres: ignorados */
    }

    /* Desenfileira B (inteiros) */
    printf("Fila B (digitos convertidos para inteiro): ");
    if (filaB_vazia(&filaB)) {
        printf("(vazia)");
    } else {
        int val;
        while (filaB_desenfileirar(&filaB, &val)) {
            printf("%d ", val);
        }
    }
    printf("\n");

    /* Desenfileira A (letras) */
    printf("Fila A (letras):                          ");
    if (filaA_vazia(&filaA)) {
        printf("(vazia)");
    } else {
        char c;
        while (filaA_desenfileirar(&filaA, &c)) {
            printf("%c ", c);
        }
    }
    printf("\n");

    return 0;
}
