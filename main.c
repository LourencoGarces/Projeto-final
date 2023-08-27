#include <stdio.h>
#include <stdlib.h>
#include "cabecalhos.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main ()
{
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g=0;
    Node* lista = NULL;
    Node2* lista2 = NULL;
    Node3* lista3 = NULL;
    Node4* lista4 = NULL;
    
    
    
    ler_ficheiros_produtos(&lista, "produtos.txt");
    ler_ficheiros_categorias(&lista2, "categorias.txt");
    ler_ficheiros_clientes(&lista3, "clientes.txt");
    ler_ficheiros_vendas(&lista4, "vendas.txt");

    do {
        Menu(&a, &b);
        switch (b)
        {
            case 1:
                do{
                    produtos(&b , &a); 
                    switch(a){
                        case 1:
                            do{
                                gerircategorias(&b, &d);
                                switch(d){
                                    case 1:
                                        criar_categoria(&lista2);
                                        break;
                                    
                                    case 2:
									    editar_categoria(&lista2);
									    break;
                                    
                                    case 3:
                                        remover_categorias(&lista2);
                                        break;

                                    case 4:
                                        listar_categorias(lista2);
                                        break;
                                }
                            }while(d!=0);
                            break;
                        
                        case 2:
                            do{
                                gerirprodutos(&b, &e);
                                switch(e){
                                    case 1:
                                        criar_produtos(&lista, lista2);
                                        break;
                                    case 2:
                                        editar_produtos(&lista);
                                        break;
                                    case 3:
                                        remover_produto(&lista);
                                        break;  
                                    case 4:
                                        listar_produtos(lista);
                                        break;
                                    
                                }
                                    
                            }while(e!=0);
                            break;
                        
                        case 3:
                            ordenar_produtos(&lista);
                            break;
                        case 4:
                        	ordenar_produtos_por_preco(&lista);
                        	break;
                        case 5:
                        	verificar_listar_categoria_produtos(&lista, &lista2);
                        	break;
                        case 6:
                            colocar_produto_sem_stock(&lista);
                        	break;    
                        case 7:
                            listar_produtos_sem_stock(&lista);
                        	break;   
                        case 8:
                            relatorio_inventario(&lista);
                            break;                                     
                    }
                    
                }while(a!=0);
                break;
                                
            case 2:                
                do {
                    clientes(&b , &a);
                    switch(a){
                        case 1:
                            do{
                                gerirclientes(&b, &c);
                                switch(c){
                                    case 1:
                                        adicionarcliente(&lista3);
                                        break;
                                    case 2:
                                        remover_cliente(&lista3);                                        
                                        break;
                                }
                            }while(c!=0);
                            break;
                            
                        case 2:
                            ordenarcliente(&lista3);                            
                            break;
                        
                        case 3:
                            encontrarcliente_nif(&lista3);
                            break;
                    }
                }while(a!=0);
                break;
            case 3:
                do{
                    vendas(&b , &a);
                    switch(a){
                                case 1:
                                    vender(&lista, &lista3, &lista4);
                                    break;
                                case 2:
                                    listar_vendas_dia(&lista4);                                        
                                    break;
                                case 3:
                                    listar_vendas(&lista4);                                        
                                    break;
                                case 4:
                                    listar_vendas_categoria(&lista4);                                        
                                    break;
                                case 5:
                                    do{
                                        gerirvendas(&b, &f);
                                        switch(f){
                                            case 1:
                                                procurar_mais_vendas_dia(&lista4);
                                                break;
                                            case 2:
                                                procurar_mais_vendas_mes(&lista4);
                                                break;
                                            case 3:
                                                procurar_mais_vendas_ano(&lista4);
                                                break;                                                
                                            }
                                    }while(f!=0);
                                case 0:
                                    break;                                                
                            }
                }while(a!=0);                 
                break;
                
            case 5:
            	gerarRelatorio(lista4);
            	break;
            	
            	
            case 0:
                guardar_no_ficheiro_produtos(lista, "produtos.txt");
                guardar_no_ficheiro_categorias(lista2, "categorias.txt");
                guardar_no_ficheiro_clientes(lista3, "clientes.txt");
                guardar_no_ficheiro_vendas(lista4, "vendas.txt");
                printf("\nA fechar o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
            }
    } while (b != 0);
    
    return 0;
}
