#ifndef PILHA_H
#define PILHA_H

typedef enum { 
    SAQUE, 
    DEPOSITO 
} TipoOperacao;

typedef struct Operacao {
    TipoOperacao tipo;
    int conta;
    int agencia;
    float valor;
    struct Operacao* prox;
} Operacao;

typedef struct {
    Operacao* topo;
} Pilha;

void iniciar_pilha(Pilha* p);
void registrar_operacao(Pilha* p, TipoOperacao tipo, int conta, int agencia, float valor);
void desfazer_operacao(Pilha* p);
void liberar_pilha(Pilha* p);

#endif