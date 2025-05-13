#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "banco.h"

void iniciar_pilha(Pilha* p) {
    p->topo = NULL;
}

void registrar_operacao(Pilha* p, TipoOperacao tipo, int conta, int agencia, float valor) {
    Operacao* nova = (Operacao*)malloc(sizeof(Operacao));
    if (!nova) return;
    
    nova->tipo = tipo;
    nova->conta = conta;
    nova->agencia = agencia;
    nova->valor = valor;
    nova->prox = p->topo;
    
    p->topo = nova;
}

void desfazer_operacao(Pilha* p) {
    if (p->topo == NULL) {
        printf("Nenhuma operação para desfazer!\n");
        return;
    }
    
    Operacao* op = p->topo;
    p->topo = op->prox;
    
    Conta* conta = buscar_conta(op->conta, op->agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        free(op);
        return;
    }
    
    if (op->tipo == DEPOSITO) {
        if (conta->saldo >= op->valor) {
            conta->saldo -= op->valor;
            printf("Depósito de R$ %.2f desfeito.\n", op->valor);
        } else {
            printf("Saldo insuficiente para desfazer depósito.\n");
        }
    } else { // SAQUE
        conta->saldo += op->valor;
        conta->total_saques--;
        conta->total_sacado -= op->valor;
        printf("Saque de R$ %.2f desfeito.\n", op->valor);
    }
    
    free(op);
}

void liberar_pilha(Pilha* p) {
    Operacao* atual = p->topo;
    while (atual != NULL) {
        Operacao* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    p->topo = NULL;
}