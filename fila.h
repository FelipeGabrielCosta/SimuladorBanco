#ifndef FILA_H
#define FILA_H

// Definição completa da struct Cliente primeiro
typedef struct Cliente {
    int conta;
    int agencia;
    struct Cliente* prox;
} Cliente;

typedef struct {
    Cliente* inicio;
    Cliente* fim;
} Fila;

void iniciar_fila(Fila* f);
void entrar_na_fila(Fila* f, int conta, int agencia);
void atender_cliente(Fila* f);
void mostrar_fila(Fila* f);

#endif