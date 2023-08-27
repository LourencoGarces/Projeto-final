#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


// estrutura para o tempo
struct tm *data_hora_atual;

// estrutura para guardar os dados da categoria
typedef struct {
    char categoria[50];
} Categoria;

// estrutura para guardar os dados do produto
typedef struct {
    char nome[50];
    int sku;
    int quantidade;
    float preco;
    char cat_categoria[50];
} Produto;

//estrutura para guardar os dados do cliente
typedef struct {
    char nome[50];
    int nif;
    int contacto;
} Cliente;

//estrutura para guardar os dados das vendas
typedef struct {
    char nome[50];
    int nif;
    int contacto;
    char nome_produto[50];
    int sku;
    int quantidade;
    float preco;
    char cat_categoria[50];
    int dia;
    int mes; 
    int ano;
    int sec;    
    int min;
    int hora;
    int quantvendida;
} Vendas;

//uso de listas duplamente ligadas
typedef struct node2 {
    Categoria categoria;
    struct node2 *proximo;
    struct node2 *anterior;
} Node2;

//uso de listas duplamente ligadas
typedef struct node {
    Produto produto;
    struct node *proximo;
    struct node *anterior;
} Node;

//uso de listas duplamente ligadas
typedef struct node3 {
    Cliente cliente;
    struct node3 *proximo;
    struct node3 *anterior;
} Node3;

//uso de listas duplamente ligadas
typedef struct node4 {
    Vendas vendas;
    struct node4 *proximo;
    struct node4 *anterior;
} Node4;

void gerarRelatorio(Node4 *vendasLista);

void procurar_mais_vendas_ano(Node4** lista4);
void procurar_mais_vendas_mes(Node4** lista4);
void procurar_mais_vendas_dia(Node4** lista4);
void listar_vendas_categoria(Node4** lista4);
void listar_vendas(Node4** lista4);
void listar_vendas_dia(Node4** lista4);
void vender(Node** lista, Node3** lista3, Node4** lista4);
void encontrarcliente_nif(Node3** lista3);
void ordenarcliente(Node3** lista3);
void remover_cliente(Node3** lista3);
void adicionarcliente(Node3** lista3);
void relatorio_inventario(Node** lista);
void listar_produtos_sem_stock(Node** lista);
void colocar_produto_sem_stock(Node** lista);
void verificar_listar_categoria_produtos(Node** lista, Node2** lista2);
void listar_categoria_produtos(Node** lista, Node2** lista2, const char* nome_categoria);
void ordenar_produtos_por_preco(Node** lista);
void ordenar_produtos(Node** lista);
void listar_produtos(Node* lista);
void remover_produto(Node** lista);
void editar_produtos(Node** lista);
void editar_produto(Node** produto);
void criar_produtos(Node** lista, Node2* lista2);
void listar_categorias(Node2* lista);
void remover_categorias(Node2** lista);
void editar_categoria(Node2** lista2);
void criar_categoria(Node2** lista2);
void inserir_no_final_produto(Node** lista, const char* cat_categoria, const char* nome, int sku, int quantidade, float preco);
void inserir_no_final_categoria(Node2** lista2, const char* valor);
void inserir_no_final_cliente(Node3** lista3, const char* nome, int nif, int contacto);
void inserir_no_final_vendas(Node4** lista4, const char* nome, int nif, int contacto, const char* cat_categoria, const char* nome_produto, int sku, int quantidade, float preco, int dia, int mes, int ano, int sec, int min, int hora);
void ler_ficheiros_produtos(Node** lista, const char* nome_arquivo);
void ler_ficheiros_categorias(Node2** lista2, const char* nome_arquivo);
void ler_ficheiros_clientes(Node3** lista3, const char* nome_arquivo);
void ler_ficheiros_vendas(Node4** lista4, const char* nome_arquivo);
void guardar_no_ficheiro_produtos(Node* lista, const char* nome_arquivo);
void guardar_no_ficheiro_categorias(Node2* lista2, const char* nome_arquivo);
void guardar_no_ficheiro_clientes(Node3* lista3, const char* nome_arquivo);
void guardar_no_ficheiro_vendas(Node4* lista4, const char* nome_arquivo);
void gerircategorias(int *b, int *d);
void gerirvendas(int *b, int *a);
void vendas(int *b, int *a);
void gerirclientes(int *b, int*c);
void clientes(int *b, int *a);
void gerirprodutos(int *b, int*e);
int produtos(int *b , int *a);
int Menu(int *a,int *b);
