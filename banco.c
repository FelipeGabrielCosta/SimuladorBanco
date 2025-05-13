#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

Conta* contas = NULL;

Conta* buscar_conta(int numero, int agencia) {
    Conta* atual = contas;
    while (atual != NULL) {
        if (atual->numero == numero && atual->agencia == agencia) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void cadastrar_conta() {
    Conta* nova = (Conta*)malloc(sizeof(Conta));
    if (!nova) return;

    printf("\n--- Cadastro de Conta ---\n");
    printf("Número da conta: ");
    scanf("%d", &nova->numero);
    printf("Agência: ");
    scanf("%d", &nova->agencia);
    
    if (buscar_conta(nova->numero, nova->agencia)) {
        printf("Conta já existe!\n");
        free(nova);
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", nova->nome);
    printf("CPF: ");
    scanf(" %[^\n]", nova->cpf);
    printf("Telefone: ");
    scanf(" %[^\n]", nova->telefone);

    nova->saldo = 0;
    nova->total_saques = 0;
    nova->total_sacado = 0;
    nova->saques = NULL;
    nova->prox = contas;
    contas = nova;

    printf("Conta cadastrada com sucesso!\n");
}

void excluir_conta(int numero, int agencia) {
    Conta *atual = contas, *anterior = NULL;
    
    while (atual != NULL) {
        if (atual->numero == numero && atual->agencia == agencia) {
            if (anterior == NULL) {
                contas = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            
            // Liberar memória dos saques
            Saque *saque = atual->saques;
            while (saque != NULL) {
                Saque *temp = saque;
                saque = saque->prox;
                free(temp);
            }
            
            free(atual);
            printf("Conta excluída com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Conta não encontrada!\n");
}

void realizar_saque(int numero, int agencia, float valor) {
    Conta* conta = buscar_conta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    if (conta->saldo < valor) {
        printf("Saldo insuficiente!\n");
        return;
    }

    Saque* novo_saque = (Saque*)malloc(sizeof(Saque));
    novo_saque->valor = valor;
    novo_saque->prox = conta->saques;
    conta->saques = novo_saque;

    conta->saldo -= valor;
    conta->total_saques++;
    conta->total_sacado += valor;
    
    printf("Saque realizado! Saldo atual: R$ %.2f\n", conta->saldo);
}

void realizar_deposito(int numero, int agencia, float valor) {
    Conta* conta = buscar_conta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    conta->saldo += valor;
    printf("Depósito realizado! Saldo atual: R$ %.2f\n", conta->saldo);
}

void ver_saldo() {
    int num, ag;
    
    printf("\n--- Consultar Saldo ---\n");
    printf("Número da conta: ");
    scanf("%d", &num);
    printf("Agência: ");
    scanf("%d", &ag);
    
    Conta* conta = buscar_conta(num, ag);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    printf("Saldo atual: R$ %.2f\n", conta->saldo);
}

void gerar_relatorio() {
    printf("\n--- Relatório de Contas ---\n");
    
    Conta* atual = contas;
    while (atual != NULL) {
        printf("\nConta: %d | Agência: %d\n", atual->numero, atual->agencia);
        printf("Cliente: %s | CPF: %s\n", atual->nome, atual->cpf);
        printf("Saldo: R$ %.2f | Saques: %d | Total sacado: R$ %.2f\n", 
               atual->saldo, atual->total_saques, atual->total_sacado);
        
        Saque* saque = atual->saques;
        if (saque) printf("Últimos saques:\n");
        while (saque != NULL) {
            printf("- R$ %.2f\n", saque->valor);
            saque = saque->prox;
        }
        
        atual = atual->prox;
    }
}

void salvar_dados() {
    FILE* arquivo = fopen("dados/contas.txt", "w");
    
    if (!arquivo) {
        arquivo = fopen("contas.txt", "w");
        if (!arquivo) {
            printf("Erro ao salvar dados!\n");
            return;
        }
        printf("Dados salvos em 'contas.txt'\n");
    } else {
        printf("Dados salvos em 'dados/contas.txt'\n");
    }

    Conta* atual = contas;
    while (atual != NULL) {
        fprintf(arquivo, "%d|%d|%s|%s|%s|%.2f|%d|%.2f\n",
                atual->numero, atual->agencia, atual->nome, 
                atual->cpf, atual->telefone, atual->saldo,
                atual->total_saques, atual->total_sacado);

        Saque* saque = atual->saques;
        while (saque != NULL) {
            fprintf(arquivo, "%.2f ", saque->valor);
            saque = saque->prox;
        }
        fprintf(arquivo, "\n");
        
        atual = atual->prox;
    }

    fclose(arquivo);
}

void carregar_dados() {
    FILE* arquivo = fopen("dados/contas.txt", "r");
    if (!arquivo) {
        arquivo = fopen("contas.txt", "r");
        if (!arquivo) {
            printf("Arquivo não encontrado. Iniciando com dados vazios.\n");
            return;
        }
    }

    char linha[500];
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        Conta* nova = (Conta*)malloc(sizeof(Conta));
        if (!nova) break;

        if (sscanf(linha, "%d|%d|%99[^|]|%19[^|]|%19[^|]|%f|%d|%f",
                   &nova->numero, &nova->agencia, nova->nome,
                   nova->cpf, nova->telefone, &nova->saldo,
                   &nova->total_saques, &nova->total_sacado) != 8) {
            free(nova);
            continue;
        }

        nova->saques = NULL;
        
        // Lê a linha de saques
        if (fgets(linha, sizeof(linha), arquivo)) {
            float valor;
            char* ptr = linha;
            while (sscanf(ptr, "%f", &valor) == 1) {
                Saque* saque = (Saque*)malloc(sizeof(Saque));
                saque->valor = valor;
                saque->prox = nova->saques;
                nova->saques = saque;
                
                while (*ptr && *ptr != ' ') ptr++;
                ptr++;
            }
        }

        nova->prox = contas;
        contas = nova;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void liberar_memoria() {
    Conta* atual = contas;
    while (atual != NULL) {
        Saque* saque = atual->saques;
        while (saque != NULL) {
            Saque* temp = saque;
            saque = saque->prox;
            free(temp);
        }
        
        Conta* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    contas = NULL;
}