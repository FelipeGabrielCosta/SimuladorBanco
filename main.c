#include <stdio.h>
#include <stdlib.h>
#include "banco.h"
#include "fila.h"
#include "pilha.h"

void mostrar_menu() {
    printf("\n=== BANCO DIGITAL ===\n");
    printf("1. Cadastrar conta\n");
    printf("2. Realizar saque\n");
    printf("3. Realizar depósito\n");
    printf("4. Consultar saldo\n");
    printf("5. Gerar relatório\n");
    printf("6. Entrar na fila\n");
    printf("7. Atender cliente\n");
    printf("8. Ver fila\n");
    printf("9. Desfazer operação\n");
    printf("10. Ordenar contas\n");
    printf("11. Excluir conta\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    carregar_dados();
    
    Fila fila;
    Pilha pilha;
    iniciar_fila(&fila);
    iniciar_pilha(&pilha);
    
    int opcao;
    do {
        mostrar_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }
        
        int conta, agencia, criterio, ordem;
        float valor;
        
        switch (opcao) {
            case 1: 
                cadastrar_conta(); 
                break;
                
            case 2:
                printf("Conta: "); scanf("%d", &conta);
                printf("Agência: "); scanf("%d", &agencia);
                printf("Valor: "); scanf("%f", &valor);
                
                realizar_saque(conta, agencia, valor);
                registrar_operacao(&pilha, SAQUE, conta, agencia, valor);
                break;
                
            case 3:
                printf("Conta: "); scanf("%d", &conta);
                printf("Agência: "); scanf("%d", &agencia);
                printf("Valor: "); scanf("%f", &valor);
                
                realizar_deposito(conta, agencia, valor);
                registrar_operacao(&pilha, DEPOSITO, conta, agencia, valor);
                break;
                
            case 4: 
                ver_saldo(); 
                break;
                
            case 5: 
                gerar_relatorio(); 
                break;
                
            case 6:
                printf("Conta: "); scanf("%d", &conta);
                printf("Agência: "); scanf("%d", &agencia);
                entrar_na_fila(&fila, conta, agencia);
                break;
                
            case 7: 
                atender_cliente(&fila); 
                break;
                
            case 8: 
                mostrar_fila(&fila); 
                break;
                
            case 9: 
                desfazer_operacao(&pilha); 
                break;
                
            case 10:
                printf("Ordenar por:\n1. Número da conta\n2. Total sacado\nEscolha: ");
                scanf("%d", &criterio);
                printf("Ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
                scanf("%d", &ordem);
                ordenar_contas(criterio == 1 ? POR_CONTA : POR_VALOR, ordem);
                break;
                
            case 11:
                printf("Conta: "); scanf("%d", &conta);
                printf("Agência: "); scanf("%d", &agencia);
                excluir_conta(conta, agencia);
                break;
                
            case 0:
                salvar_dados();
                liberar_memoria();
                liberar_pilha(&pilha);
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}