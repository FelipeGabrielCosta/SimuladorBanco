#ifndef BANCO_H
#define BANCO_H

typedef enum {
    POR_CONTA,
    POR_VALOR
} Criterio;

typedef struct Saque {
    float valor;
    struct Saque* prox;
} Saque;

typedef struct Conta {
    char nome[100];
    char cpf[20];
    char telefone[20];
    int numero;
    int agencia;
    float saldo;
    int total_saques;
    float total_sacado;
    Saque* saques;
    struct Conta* prox;
} Conta;

// Funções básicas
void cadastrar_conta();
void excluir_conta(int numero, int agencia);
void realizar_saque(int numero, int agencia, float valor);
void realizar_deposito(int numero, int agencia, float valor);
void ver_saldo();
void gerar_relatorio();
void salvar_dados();
void carregar_dados();
void ordenar_contas(Criterio c, int ordem);
void liberar_memoria();

// Funções auxiliares
Conta* buscar_conta(int numero, int agencia);

extern Conta* contas;

#endif