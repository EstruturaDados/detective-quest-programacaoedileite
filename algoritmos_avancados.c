#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

// Estrutura para representar uma sala (nó da árvore binária)
typedef struct Sala {
    char Nome[60];
    struct Sala* Esquerda;
    struct Sala* Direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* Nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(novaSala->Nome, Nome);
    novaSala->Esquerda = NULL;
    novaSala->Direita = NULL;
    return novaSala;
}

// Função para explorar as salas interativamente
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        printf("Sala não existe!\n");
        return;
    }
    
    printf("\n--- Você está no: %s ---\n", salaAtual->Nome);
    
    // Verifica se é uma sala final (nó folha)
    if (salaAtual->Esquerda == NULL && salaAtual->Direita == NULL) {
        printf("Este é um cômodo sem saída. Fim da exploração nesta direção.\n");
        return;
    }
    
    // Mostra opções disponíveis
    printf("Opções de exploração:\n");
    if (salaAtual->Esquerda != NULL) {
        printf("  [e] - Ir para a esquerda (%s)\n", salaAtual->Esquerda->Nome);
    }
    if (salaAtual->Direita != NULL) {
        printf("  [d] - Ir para a direita (%s)\n", salaAtual->Direita->Nome);
    }
    printf("  [s] - Sair da exploração\n");
    
    // Loop de interação com o usuário
    char Opcao;
    int opcaoValida = 0;
    
    while (!opcaoValida) {
        printf("\nEscolha uma opção: ");
        scanf(" %c", &Opcao);
        
        switch (Opcao) {
            case 'e':
            case 'E':
                if (salaAtual->Esquerda != NULL) {
                    explorarSalas(salaAtual->Esquerda);
                    opcaoValida = 1;
                } else {
                    printf("Não há caminho à esquerda!\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->Direita != NULL) {
                    explorarSalas(salaAtual->Direita);
                    opcaoValida = 1;
                } else {
                    printf("Não há caminho à direita!\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Saindo da exploração...\n");
                return;
                
            default:
                printf("Opção inválida! Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");
                break;
        }
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Sala* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->Esquerda);
        liberarArvore(raiz->Direita);
        free(raiz);
    }
}

// Função principal

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    printf("=== DETECTIVE QUEST - EXPLORAÇÃO DA MANSÃO ===\n");
    printf("Bem-vindo, detetive! Explore a mansão para encontrar pistas.\n\n");
    
    // Construção do mapa da mansão (árvore binária)
    // Nível 0: Raiz
    Sala* hallEntrada = criarSala("Hall de Entrada");
    
    // Nível 1: Filhos da raiz
    hallEntrada->Esquerda = criarSala("Sala de Estar");
    hallEntrada->Direita = criarSala("Biblioteca");
    
    // Nível 2: Filhos da Sala de Estar
    hallEntrada->Esquerda->Esquerda = criarSala("Quarto dos Hóspedes");
    hallEntrada->Esquerda->Direita = criarSala("Cozinha");
    
    // Nível 2: Filhos da Biblioteca
    hallEntrada->Direita->Esquerda = criarSala("Escritório");
    hallEntrada->Direita->Direita = criarSala("Jardim de Inverno");
    
    // Nível 3: Alguns cômodos adicionais
    hallEntrada->Esquerda->Esquerda->Esquerda = criarSala("Banheiro Social");
    hallEntrada->Esquerda->Direita->Direita = criarSala("Despensa");
    hallEntrada->Direita->Esquerda->Esquerda = criarSala("Arquivo Secreto");
    
    printf("Mapa da mansão criado com sucesso!\n");
    printf("Iniciando exploração a partir do Hall de Entrada...\n");
    
    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hallEntrada);
    
    printf("\n=== Exploração finalizada ===\n");
    printf("Obrigado por jogar Detective Quest!\n");
    
    // Libera a memória alocada para a árvore
    liberarArvore(hallEntrada);
    
    return 0;
}

