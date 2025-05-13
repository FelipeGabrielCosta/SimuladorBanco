#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void iniciar_fila(Fila* f) {
    f->inicio = f->fim = NULL;
}

void entrar_na_fila(Fila* f, int conta, int agencia) {
    Cliente* novo = (Cliente*)malloc(sizeof(Cliente));
    if (!novo) return;
    
    novo->conta = conta;
    novo->agencia = agencia;
    novo->prox = NULL;
    
    if (f->fim == NULL) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    
    printf("Cliente da conta %d entrou na fila.\n", conta);
}

void atender_cliente(Fila* f) {
    if (f->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    
    Cliente* atendido = f->inicio;
    printf("Atendendo conta %d...\n", atendido->conta);
    
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(atendido);
}

void mostrar_fila(Fila* f) {
    if (f->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("\n--- Fila de Atendimento ---\n");
    Cliente* atual = f->inicio;
    while (atual != NULL) {
        printf("Conta: %d | Agência: %d\n", atual->conta, atual->agencia);
        atual = atual->prox;
    }
}