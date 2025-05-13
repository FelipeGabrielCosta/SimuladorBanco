#include <stdio.h>
#include <stdlib.h>
#include "banco.h"  // Inclui apenas banco.h

extern Conta* contas;

void ordenar_contas(Criterio c, int ordem) {
    // Contar contas
    int n = 0;
    Conta* atual = contas;
    while (atual) {
        n++;
        atual = atual->prox;
    }
    
    if (n < 2) {
        printf("Poucas contas para ordenar.\n");
        return;
    }
    
    // Criar vetor de ponteiros
    Conta** lista = (Conta**)malloc(n * sizeof(Conta*));
    if (!lista) return;
    
    atual = contas;
    for (int i = 0; i < n; i++) {
        lista[i] = atual;
        atual = atual->prox;
    }
    
    // Ordenação com bubble sort (considera a ordem)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            int precisaTrocar = 0;
            
            if (c == POR_CONTA) {
                if (ordem == 1) precisaTrocar = lista[j]->numero > lista[j+1]->numero;
                else precisaTrocar = lista[j]->numero < lista[j+1]->numero;
            } 
            else { // POR_VALOR
                if (ordem == 1) precisaTrocar = lista[j]->total_sacado > lista[j+1]->total_sacado;
                else precisaTrocar = lista[j]->total_sacado < lista[j+1]->total_sacado;
            }
            
            if (precisaTrocar) {
                Conta* temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    
    // Mostrar resultado
    printf("\n--- Contas Ordenadas ---\n");
    for (int i = 0; i < n; i++) {
        printf("Conta: %d | Agência: %d | ", lista[i]->numero, lista[i]->agencia);
        if (c == POR_CONTA) {
            printf("Saldo: R$ %.2f\n", lista[i]->saldo);
        } else {
            printf("Total sacado: R$ %.2f\n", lista[i]->total_sacado);
        }
    }
    
    free(lista);
}