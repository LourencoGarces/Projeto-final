#include "cabecalhos.h"

void gerarRelatorio(Node4 *vendasLista) {
    // Obter a data atual
    time_t agora = time(NULL);
    data_hora_atual = localtime(&agora);
    int dia_atual = data_hora_atual->tm_mday;
    int mes_atual = data_hora_atual->tm_mon + 1;
    int ano_atual = data_hora_atual->tm_year + 1900;

    // Vari�veis para a receita m�xima
    float maxReceitaDia = 0;
    char produtoMaxReceitaDia[50] = "";
    float maxReceitaMes = 0;
    char produtoMaxReceitaMes[50] = "";

    // Vari�veis para a receita acumulada
    float receitaDiaAtual = 0;
    float receitaMesAtual = 0;
    int diaAnterior = -1;
    int mesAnterior = -1;

    // Percorrer todas as vendas na lista
    Node4 *atual = vendasLista;
    while (atual != NULL) {
        Vendas venda = atual->vendas;

        // Verificar se a venda ocorreu hoje
        if (venda.dia == dia_atual && venda.mes == mes_atual && venda.ano == ano_atual) {
            receitaDiaAtual += venda.preco * venda.quantvendida;
        } else {
            // Nova data, verificar se � a maior receita do dia anterior
            if (receitaDiaAtual > maxReceitaDia && diaAnterior != -1) {
                maxReceitaDia = receitaDiaAtual;
                strcpy(produtoMaxReceitaDia, venda.nome_produto);
            }

            // Verificar se a venda ocorreu neste m�s
            if (venda.mes == mes_atual && venda.ano == ano_atual) {
                receitaMesAtual += venda.preco * venda.quantvendida;
            } else {
                // Novo m�s, verificar se � a maior receita do m�s anterior
                if (receitaMesAtual > maxReceitaMes && mesAnterior != -1) {
                    maxReceitaMes = receitaMesAtual;
                    strcpy(produtoMaxReceitaMes, venda.nome_produto);
                }
            }

            // Reiniciar a receita para o novo dia/m�s
            receitaDiaAtual = venda.preco * venda.quantvendida;
            receitaMesAtual = venda.preco * venda.quantvendida;
            diaAnterior = venda.dia;
            mesAnterior = venda.mes;
        }

        atual = atual->proximo;
    }

    // Verificar a �ltima data
    if (receitaDiaAtual > maxReceitaDia && diaAnterior != -1) {
        maxReceitaDia = receitaDiaAtual;
        strcpy(produtoMaxReceitaDia, atual->vendas.nome_produto);
    }
    if (receitaMesAtual > maxReceitaMes && mesAnterior != -1) {
        maxReceitaMes = receitaMesAtual;
        strcpy(produtoMaxReceitaMes, atual->vendas.nome_produto);
    }

    // Imprimir o relat�rio
    printf("Produtos que geraram mais receita hoje:\n");
    printf("Produto: %s\n", produtoMaxReceitaDia);
    printf("Receita: R$ %.2f\n", maxReceitaDia);
    printf("\n");
    printf("Produtos que geraram mais receita neste m�s:\n");
    printf("Produto: %s\n", produtoMaxReceitaMes);
    printf("Receita: R$ %.2f\n", maxReceitaMes);
    sleep(3);
}




void procurar_mais_vendas_ano(Node4** lista4){
    // Criar um array para armazenar os produtos e suas vendas
    Produto produtos[100];
    Vendas vendas[100];
    int numProdutos = 0;

    // Percorrer a lista de vendas
    Node4* atual = *lista4;
    while (atual != NULL) {
        // Verificar se o produto j� est� na lista
        int encontrado = -1;
        int i = 0;
        for (i ; i < numProdutos; i++) {
            if (strcmp(produtos[i].nome, atual->vendas.nome_produto) == 0 && vendas[i].ano == atual->vendas.ano) {
                encontrado = i;
                break;
            }
        }
        
        // Se o produto j� est� na lista, incrementar a quantidade vendida
        if (encontrado != -1) {
            produtos[encontrado].quantidade += atual->vendas.quantidade;
        }
        // Caso contr�rio, adicionar o produto � lista
        else {
            strcpy(produtos[numProdutos].nome, atual->vendas.nome_produto);
            produtos[numProdutos].quantidade = atual->vendas.quantidade;
            numProdutos++;
        }

        atual = atual->proximo;
    }

    // Ordenar os produtos com base na quantidade vendida (ordem decrescente)
    int i, j;
    for (i = 0; i < numProdutos - 1; i++) {
        for (j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].quantidade < produtos[j + 1].quantidade) {
                // Trocar de posi��o
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    // Exibir os tr�s produtos mais vendidos
    printf("Os tres produtos mais vendidos do ano sao:\n");
    for (i = 0; i < 3 && i < numProdutos; i++) {
        printf("Produto: %s, Quantidade Vendida: %d\n", produtos[i].nome, produtos[i].quantidade);
    }
    sleep(5);
}

void procurar_mais_vendas_mes(Node4** lista4){
    // Criar um array para armazenar os produtos e suas vendas
    Produto produtos[100];
    Vendas vendas[100];
    int numProdutos = 0;

    // Percorrer a lista de vendas
    Node4* atual = *lista4;
    while (atual != NULL) {
        // Verificar se o produto j� est� na lista
        int encontrado = -1;
        int i = 0;
        for (i; i < numProdutos; i++) {
            if (strcmp(produtos[i].nome, atual->vendas.nome_produto) == 0 && vendas[i].mes == atual->vendas.mes && vendas[i].ano == atual->vendas.ano) {
                encontrado = i;
                break;
            }
        }
        
        // Se o produto j� est� na lista, incrementar a quantidade vendida
        if (encontrado != -1) {
            produtos[encontrado].quantidade += atual->vendas.quantidade;
        }
        // Caso contr�rio, adicionar o produto � lista
        else {
            strcpy(produtos[numProdutos].nome, atual->vendas.nome_produto);
            produtos[numProdutos].quantidade = atual->vendas.quantidade;
            numProdutos++;
        }

        atual = atual->proximo;
    }

    // Ordenar os produtos com base na quantidade vendida (ordem decrescente)
    int i, j;
    for (i; i < numProdutos - 1; i++) {
        for (j; j < numProdutos - i - 1; j++) {
            if (produtos[j].quantidade < produtos[j + 1].quantidade) {
                // Trocar de posi��o
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    // Exibir os tr�s produtos mais vendidos
    printf("Os tres produtos mais vendidos do mes sao:\n");
    for (i=0; i < 3 && i < numProdutos; i++) {
        printf("Produto: %s, Quantidade Vendida: %d\n", produtos[i].nome, produtos[i].quantidade);
    }
    sleep(5);
}

void procurar_mais_vendas_dia(Node4** lista4){
    // Criar um array para armazenar os produtos e suas vendas
    Produto produtos[100];
    Vendas vendas[100];
    int numProdutos = 0;

    // Percorrer a lista de vendas
    Node4* atual = *lista4;
    while (atual != NULL) {
        // Verificar se o produto j� est� na lista
        int encontrado = -1;
        int i = 0;
        for (i; i < numProdutos; i++) {
            if (strcmp(produtos[i].nome, atual->vendas.nome_produto) == 0 && vendas[i].dia == atual->vendas.dia && vendas[i].mes == atual->vendas.mes && vendas[i].ano == atual->vendas.ano) {
                encontrado = i;
                break;
            }
        }
        
        // Se o produto j� est� na lista, incrementar a quantidade vendida
        if (encontrado != -1) {
            produtos[encontrado].quantidade += atual->vendas.quantidade;
        }
        // Caso contr�rio, adicionar o produto � lista
        else {
            strcpy(produtos[numProdutos].nome, atual->vendas.nome_produto);
            produtos[numProdutos].quantidade = atual->vendas.quantidade;
            numProdutos++;
        }

        atual = atual->proximo;
    }

    // Ordenar os produtos com base na quantidade vendida (ordem decrescente)
    int i = 0, j = 0;
    for (i; i < numProdutos - 1; i++) {
        for (j; j < numProdutos - i - 1; j++) {
            if (produtos[j].quantidade < produtos[j + 1].quantidade) {
                // Trocar de posi��o
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    // Exibir os tr�s produtos mais vendidos
    printf("Os tres produtos mais vendidos do dia sao:\n");
    for (i=0; i < 3 && i < numProdutos; i++) {
        printf("Produto: %s, Quantidade Vendida: %d\n", produtos[i].nome, produtos[i].quantidade);
    }
    sleep(5);
}


void listar_vendas_categoria(Node4** lista4){
    char cat_categoria[50];
    printf("Digite a categoria que deseja listar as vendas: ");
    scanf("%s", cat_categoria);
    Node4* atual = *lista4;
    while (atual != NULL) {
        if (strcmp(atual->vendas.cat_categoria, cat_categoria) == 0) {
            printf("Nome: %s\n", atual->vendas.nome);
            printf("NIF: %d\n", atual->vendas.nif);
            printf("Contacto: %d\n", atual->vendas.contacto);
            printf("Categoria: %s\n", atual->vendas.cat_categoria);
            printf("Nome do produto: %s\n", atual->vendas.nome_produto);
            printf("SKU: %d\n", atual->vendas.sku);
            printf("Quantidade: %d\n", atual->vendas.quantidade);
            printf("Pre�o: %.2f\n", atual->vendas.preco);
            printf("Data: %02d:%02d:%d\n", atual->vendas.dia, atual->vendas.mes, atual->vendas.ano);
            printf("Hora: %d:%d:%d\n", atual->vendas.hora, atual->vendas.min, atual->vendas.sec);
            printf("------------------------------------------\n\n");
            sleep(3);
        }
        atual = atual->proximo;
    }
    sleep(5);
}

void listar_vendas(Node4** lista4){
    Node4* atual = *lista4;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->vendas.nome);
        printf("NIF: %d\n", atual->vendas.nif);
        printf("Contacto: %d\n", atual->vendas.contacto);
        printf("Categoria: %s\n", atual->vendas.cat_categoria);
        printf("Nome do produto: %s\n", atual->vendas.nome_produto);
        printf("SKU: %d\n", atual->vendas.sku);
        printf("Quantidade: %d\n", atual->vendas.quantidade);
        printf("Pre�o: %.2f\n", atual->vendas.preco);
        printf("Data: %02d:%02d:%d\n", atual->vendas.dia, atual->vendas.mes, atual->vendas.ano);
        printf("Hora: %d:%d:%d\n", atual->vendas.hora, atual->vendas.min, atual->vendas.sec);
        printf("------------------------------------------\n\n");
        atual = atual->proximo;
        sleep(3);
    }
    sleep(5);
}

void listar_vendas_dia(Node4** lista4){
    int dia, mes, ano;
    printf("Digite a data que deseja listar as vendas (dd:mm:aaaa): ");
    scanf("%d:%d:%d", &dia, &mes, &ano);
    Node4* atual = *lista4;
    while (atual != NULL) {
        if (atual->vendas.dia == dia && atual->vendas.mes == mes && atual->vendas.ano == ano) {
            printf("Nome: %s\n", atual->vendas.nome);
            printf("NIF: %d\n", atual->vendas.nif);
            printf("Contacto: %d\n", atual->vendas.contacto);
            printf("Categoria: %s\n", atual->vendas.cat_categoria);
            printf("Nome do produto: %s\n", atual->vendas.nome_produto);
            printf("SKU: %d\n", atual->vendas.sku);
            printf("Quantidade: %d\n", atual->vendas.quantidade);
            printf("Pre�o: %.2f\n", atual->vendas.preco);
            printf("Data: %02d:%02d:%d\n", atual->vendas.dia, atual->vendas.mes, atual->vendas.ano);
            printf("------------------------------------------\n\n");
            sleep(3);
        }
        atual = atual->proximo;
    }
    sleep(5);
}

void vender(Node** lista, Node3** lista3, Node4** lista4) {
    char nome[50];
    int nif;
    int contacto;
    char cat_categoria[50];
    char nome_produto[50];
    int sku;
    int quantidade;
    float preco;
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    int sec;
    char continuar;
    char pesquisar;
    int quantvendida;
    int a;
    int skuEncontrado = 0;
    
    do {
        printf("Deseja contribuinte? (s/n): ");
        scanf(" %c", &pesquisar);

        if (pesquisar == 's') {
            printf("NIF do cliente: ");
            scanf("%d", &nif);
            Node3* cliente = *lista3;

            while (cliente != NULL) {
                if (cliente->cliente.nif == nif) {
                    strcpy(nome, cliente->cliente.nome);
                    contacto = cliente->cliente.contacto;
                    break;
                }
                cliente = cliente->proximo;
            }

            if (cliente == NULL) {
                printf("Cliente n�o encontrado!\n");
                continue;
            }
        } else {
            strcpy(nome, "anonimo");
            nif = 123456789;
            contacto = 933333333;
        }
        
		do {
		    printf("SKU do produto: ");
		    scanf("%d", &sku);
		    Node* produto = *lista;
		
		    int skuEncontrado = 0;
		
		    while (produto != NULL) {
		        if (produto->produto.sku == sku) {
		            strcpy(nome_produto, produto->produto.nome);
		            strcpy(cat_categoria, produto->produto.cat_categoria);
		            preco = produto->produto.preco;
		            skuEncontrado = 1;
		            break;
		        }
		        produto = produto->proximo;
		    }
		
		    if (skuEncontrado) {  //Verifica se o codigo inserido existe
		        a = 0; 
		    } else {
		        printf("Produto n�o encontrado. Insira outro SKU.\n");
		        a = 1; 
		    }
		} while (a != 0);

        Node* produto = *lista;
        printf("Quantidade do produto: ");
        scanf("%d", &quantidade);
        
        if (quantidade > produto->produto.quantidade) {
            printf("Quantidade insuficiente em estoque!\n");
            sleep(4);
            continue;
        }
        
		int quantidade_desconto = 0;
		int quantidade_normal = 0;
		int stock_disponivel = produto->produto.quantidade;
		
		int i=0;
		
		while(produto->produto.quantidade > 30){
			i++;
		}
		
		quantidade_normal = quantidade - i;
		quantidade_desconto = i;
		
		if(quantidade_normal <=0){
			float preco_normal = 0;	
		}
		
			float preco_desconto = preco * quantidade_desconto * 0.8; // 20% de desconto
			float preco_normal = preco * quantidade_normal;
			preco = preco_desconto + preco_normal;
		
		if (quantidade_desconto > 0) {
		    printf("Produto com desconto de 20%% nos primeiros %d itens\n", quantidade_desconto);
		}
		
		printf("Pre�o final: %f\n", preco);
		sleep(3);

        
        produto->produto.quantidade -= quantidade;

        time_t segundos;

        time(&segundos);
  
        data_hora_atual = localtime(&segundos);  
       

        Node4* novoNode = (Node4*)malloc(sizeof(Node4));
        strcpy(novoNode->vendas.nome, nome);
        novoNode->vendas.nif = nif;
        novoNode->vendas.contacto = contacto;
        strcpy(novoNode->vendas.cat_categoria, cat_categoria);
        strcpy(novoNode->vendas.nome_produto, nome_produto);
        novoNode->vendas.sku = sku;
        novoNode->vendas.quantidade = quantidade;
        novoNode->vendas.preco = preco;
        novoNode->vendas.dia = data_hora_atual->tm_mday;
        novoNode->vendas.mes = data_hora_atual->tm_mon+1;
        novoNode->vendas.ano = data_hora_atual->tm_year+1900;
        novoNode->vendas.hora = data_hora_atual->tm_hour;
        novoNode->vendas.min = data_hora_atual->tm_min;
        novoNode->vendas.sec = data_hora_atual->tm_sec;
        novoNode->proximo = NULL;

        if (*lista4 == NULL) {
            novoNode->anterior = NULL;
            *lista4 = novoNode;
        } else {
            Node4* ultimoNode = *lista4;
            while (ultimoNode->proximo != NULL) {
                ultimoNode = ultimoNode->proximo;
            }
            ultimoNode->proximo = novoNode;
            novoNode->anterior = ultimoNode;
        }

        printf("\nDeseja efetuar outra venda? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');
}

void encontrarcliente_nif(Node3** lista3){
    int nif;
    printf("Digite o NIF do cliente que deseja encontrar: ");
    scanf("%d", &nif);
    Node3* atual = *lista3;
    while (atual != NULL) {
        if (atual->cliente.nif == nif) {
            printf("Nome: %s\n", atual->cliente.nome);
            printf("NIF: %d\n", atual->cliente.nif);
            printf("Contacto: %d\n", atual->cliente.contacto);
            sleep(5);
            return;
        }
        atual = atual->proximo;
    }

    printf("Cliente n�o encontrado!\n");
    sleep(5);
}

void ordenarcliente(Node3** lista3){
    Node3* atual = *lista3;
    Node3* proximo = atual->proximo;
    Node3* temp = (Node3*)malloc(sizeof(Node3));
    
    while (atual != NULL) {
        while (proximo != NULL) {
            if (stricmp(atual->cliente.nome, proximo->cliente.nome) > 0) {
                temp->cliente = atual->cliente;
                atual->cliente = proximo->cliente;
                proximo->cliente = temp->cliente;
            }
            proximo = proximo->proximo;
        }
        
        atual = atual->proximo;
        if (atual != NULL) {
            proximo = atual->proximo;
        }
    }
    
    atual = *lista3;  // reinicia o ponteiro 'atual' para o in�cio da lista
    
    while (atual != NULL) {
        printf("Nome: %s\tNIF: %d\tContacto: %d\n", atual->cliente.nome, atual->cliente.nif, atual->cliente.contacto);
        atual = atual->proximo;
    }
    
    free(temp);
    sleep(5);
}


void remover_cliente(Node3** lista3){
    char nome[50];
    char continuar;
    
    do{
	    printf("Digite o nome do cliente que deseja remover: ");
	    scanf("%s", nome);
	    Node3* atual = *lista3;

        int encontrou_cliente = 0;
        Node3* opcoes_equivalencias[10];
        int num_equivalencias = 0;
        Node3* cliente_removido = NULL;

        while (atual != NULL) {
            if (stricmp(atual->cliente.nome, nome) == 0) {
                printf("Cliente encontrado: %s\n", atual->cliente.nome);
                encontrou_cliente = 1;
                cliente_removido = atual;
                break;
            } else if (strncasecmp(atual->cliente.nome, nome, strlen(nome)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
            }
            atual = atual->proximo;
        }

        if (encontrou_cliente) {
            printf("Avan�ando para elemina��o do cliente...\n");
            sleep(3);
            while (atual != NULL) {
		        if (strcmp(atual->cliente.nome, nome) == 0) {
		            if (atual->anterior == NULL) {
		                *lista3 = atual->proximo;
		            } else {
		                atual->anterior->proximo = atual->proximo;
		            }
		            if (atual->proximo != NULL) {
		                atual->proximo->anterior = atual->anterior;
		            }
		            free(atual);
		            printf("O cliente foi removido com sucesso!\n");
		            sleep(5);
		            return;
		        }
		        atual = atual->proximo;
	    	}    			        
        } else if (num_equivalencias > 0) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i + 1, opcoes_equivalencias[i]->cliente.nome);
            }
            printf("%d. Sair\n", num_equivalencias + 1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                cliente_removido = opcoes_equivalencias[escolha - 1];
                printf("Voc� escolheu: %s\n", cliente_removido->cliente.nome);
                atual = *lista3;
                while (atual != NULL) {
			        if (stricmp(atual->cliente.nome, cliente_removido->cliente.nome) == 0) {
			            if (atual->anterior == NULL) {
			                *lista3 = atual->proximo;
			            } else {
			                atual->anterior->proximo = atual->proximo;
			            }
			            if (atual->proximo != NULL) {
			                atual->proximo->anterior = atual->anterior;
			            }
			            free(atual);
			            printf("O cliente foi removido com sucesso!\n");
			            sleep(5);
			            return;
			        }
			        atual = atual->proximo;
			    }
    		}		    
        } else {
            printf("Nenhum cliente encontrado para: %s\n", nome);
            sleep(2);
            return;
        }
	}while (continuar == 's');
}

void adicionarcliente(Node3** lista3) {
    char nome[50];
    int nif;
    int contacto;
    char continuar;

    do {
        bool duplicate = false; // Flag to track duplicate NIF or contact
        printf("Nome do cliente: ");
        scanf("%s", nome);
        printf("NIF do cliente: ");
        scanf("%d", &nif);
        printf("Contacto do cliente: ");
        scanf("%d", &contacto);

        Node3* currentNode = *lista3;
        while (currentNode != NULL) {
            if (currentNode->cliente.nif == nif || currentNode->cliente.contacto == contacto) {
                duplicate = true; // Found a client with the same NIF or contact
                break;
            }
            currentNode = currentNode->proximo;
        }

        if (duplicate) {
            printf("Um cliente com o mesmo NIF ou contacto j� existe.\n");
            continue; // Skip adding the client and continue the loop
        }

        Node3* novoNode = (Node3*)malloc(sizeof(Node3));
        strcpy(novoNode->cliente.nome, nome);
        novoNode->cliente.nif = nif;
        novoNode->cliente.contacto = contacto;
        novoNode->proximo = NULL;

        if (*lista3 == NULL) {
            novoNode->anterior = NULL;
            *lista3 = novoNode;
        } else {
            Node3* ultimoNode = *lista3;
            while (ultimoNode->proximo != NULL) {
                ultimoNode = ultimoNode->proximo;
            }
            ultimoNode->proximo = novoNode;
            novoNode->anterior = ultimoNode;
        }

        printf("Deseja criar outra categoria? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');
}

void relatorio_inventario(Node** lista) {
    Node* atual = *lista;
    
    printf("===== Relat�rio de Invent�rio =====\n");
    while(atual != NULL){
        printf("Categoria: %s\n", atual->produto.cat_categoria);
        printf("Nome: %s\n", atual->produto.nome);
        printf("C�digo SKU: %d\n", atual->produto.sku);
        printf("Quantidade: %d\n", atual->produto.quantidade);
        printf("Pre�o: %.2f\n", atual->produto.preco);
        printf("------------------------------------------\n");
        if(atual->produto.quantidade <= 5){
            printf("Estado do produto %d: Com pouco stock\n", atual->produto.sku);
        }
        else if(atual->produto.quantidade > 5 && atual->produto.quantidade <= 20){
            printf("Estado do produto %d: Com stock m�dio\n", atual->produto.sku);
        }
        else if(atual->produto.quantidade > 20){
            printf("Estado do produto %d: Com demasiado stock\n", atual->produto.sku);
        }
        else{
            printf("Estado do produto %d: Sem stock\n", atual->produto.sku);
        }
        printf("------------------------------------------\n\n");
        atual = atual->proximo;
        sleep(3);
    }    
}

void listar_produtos_sem_stock(Node** lista) {
    Node* atual = *lista;
    int i = 0;

    while (atual != NULL) {
        if (atual->produto.quantidade == 0) {
            printf("Nome: %s\n", atual->produto.nome);
            printf("C�digo SKU: %d\n", atual->produto.sku);
            printf("Quantidade: %d\n", atual->produto.quantidade);
            printf("Pre�o: %.2f\n", atual->produto.preco);
            printf("--------------------\n");
            sleep(3);
            i++;
        }
        atual = atual->proximo;
    }

    if (i == 0) {
        printf("N�o existem produtos sem stock!\n");
        sleep(5);
    }
}

void colocar_produto_sem_stock(Node** lista) {
    char nome_produto[50];
    int continuar;

	do{
	    printf("Digite o nome do produto que deseja colocar sem stock: ");
	    scanf("%s", nome_produto);
	    Node* atual = *lista;

        int encontrou_produto = 0;
        Node* opcoes_equivalencias[10];
        int num_equivalencias = 0;
        Node* produto_editado = NULL;

        while (atual != NULL) {
            if (stricmp(atual->produto.nome, nome_produto) == 0) {
                printf("Produto encontrado: %s\n", atual->produto.nome);
                encontrou_produto = 1;
                produto_editado = atual;
                break;
            } else if (strncasecmp(atual->produto.nome, nome_produto, strlen(nome_produto)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
            }
            atual = atual->proximo;
        }

        if (encontrou_produto) {
            printf("Avan�ando retiragem de stock...\n");
            sleep(3);
            Node* atual = *lista;
				while (atual != NULL) {
			        if (stricmp(atual->produto.nome, nome_produto) == 0) {
			            atual->produto.quantidade = 0;
			            printf("O produto foi colocado sem stock com sucesso!\n");
			            sleep(5);
			            break;
        			}
        		atual = atual->proximo;
    			}            
        } else if (num_equivalencias > 0) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i + 1, opcoes_equivalencias[i]->produto.nome);
            }
            printf("%d. Sair\n", num_equivalencias + 1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                produto_editado = opcoes_equivalencias[escolha - 1];
                printf("Voc� escolheu: %s\n", produto_editado->produto.nome);
                Node* atual = *lista;
				while (atual != NULL) {
			        if (stricmp(atual->produto.nome, produto_editado->produto.nome) == 0) {
			            atual->produto.quantidade = 0;
			            printf("O produto foi colocado sem stock com sucesso!\n");
			            sleep(5);
			            break;
        			}
        		atual = atual->proximo;
    			}
    		}		    
        } else {
            printf("Nenhum produto encontrado para: %s\n", nome_produto);
            sleep(2);
            return;
        }

        printf("Deseja continuar a retirar stock de outro produto? (0 - N�o / 1 - Sim) ");
        scanf("%d", &continuar);
        getchar(); // Limpar o buffer de entrada
    } while (continuar == 1);
}

void verificar_listar_categoria_produtos(Node** lista, Node2** lista2) {
    char nome_categoria[50];
    int continuar;

    do {
        printf("Digite o nome da categoria de produtos que deseja listar: ");
        scanf("%49s", nome_categoria);
        Node* atual = *lista;

        int encontrou_produto = 0;
        Node* opcoes_equivalencias[10];
        int num_equivalencias = 0;
        Node* produto_editado = NULL;

        while (atual != NULL) {
            if (stricmp(atual->produto.cat_categoria, nome_categoria) == 0) {
                printf("Produto encontrado: %s\n", atual->produto.cat_categoria);
                encontrou_produto = 1;
                produto_editado = atual;
                break;
            } else if (strncasecmp(atual->produto.cat_categoria, nome_categoria, strlen(nome_categoria)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
            }
            atual = atual->proximo;
        }

        if (encontrou_produto) {
            printf("Avan�ando para a listagem...\n");
            listar_categoria_produtos(&produto_editado, lista2, nome_categoria);
        } else if (num_equivalencias > 0) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i + 1, opcoes_equivalencias[i]->produto.cat_categoria);
            }
            printf("%d. Sair\n", num_equivalencias + 1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                produto_editado = opcoes_equivalencias[escolha - 1];
                printf("Voc� escolheu: %s\n", produto_editado->produto.cat_categoria);
                strcpy(produto_editado->produto.cat_categoria, nome_categoria);
                listar_categoria_produtos(&produto_editado, lista2, nome_categoria);
            } else {
                return;
            }
        } else {
            printf("Nenhuma categoria encontrada para: %s\n", nome_categoria);
            sleep(2);
            return;
        }

        printf("Deseja continuar a listar outra categoria? (0 - N�o / 1 - Sim) ");
        scanf("%d", &continuar);
        getchar(); // Limpar o buffer de entrada
    } while (continuar == 1);
}

void listar_categoria_produtos(Node** produto, Node2** lista2, const char* nome_categoria) {
    Node* atual = *produto;
    Node2* secundario = *lista2;
    int i = 0, e = 0;

    // Percorre a lista de produtos e imprime os detalhes dos produtos da categoria informada
    while (atual != NULL) {
        if (stricmp(atual->produto.cat_categoria, nome_categoria) == 0) {
            printf("Nome: %s\n", atual->produto.nome);
            printf("C�digo SKU: %d\n", atual->produto.sku);
            printf("Quantidade: %d\n", atual->produto.quantidade);
            printf("Pre�o: %.2f\n", atual->produto.preco);
            printf("--------------------\n");
            sleep(3);
            i++;
        }
        atual = atual->proximo;
    }

    // Percorre a lista de categorias e verifica se existe uma correspond�ncia exata com a categoria informada
    while (secundario != NULL) {
        if (strcmp(secundario->categoria.categoria, nome_categoria) == 0) {
            e++;
            break;
        }
        secundario = secundario->proximo;
    }

    if (i == 0 && e != 0) {
        printf("A categoria existe, mas n�o tem produtos associados!\n");
        sleep(5);
    } else if (i == 0 && e == 0) {
        printf("A categoria n�o existe!\n");
        sleep(5);
    }
}


void ordenar_produtos_por_preco(Node** lista) {
    Node* atual = *lista;
    Node* proximo = atual->proximo;
    Node* temp = (Node*)malloc(sizeof(Node));
    
    while (atual != NULL) {
        while (proximo != NULL) {
            if (atual->produto.preco < proximo->produto.preco) {
                temp->produto = atual->produto;
                atual->produto = proximo->produto;
                proximo->produto = temp->produto;
            }
            proximo = proximo->proximo;
        }
        
        atual = atual->proximo;
        if (atual != NULL) {
            proximo = atual->proximo;
        }
    }
    
    atual = *lista;  // reinicia o ponteiro 'atual' para o in�cio da lista
    
    while (atual != NULL) {
        printf("Nome: %s\tCategoria: %s\tC�digo SKU: %d\tQuantidade: %d\tPre�o: %.2f\n", atual->produto.nome, atual->produto.cat_categoria, atual->produto.sku, atual->produto.quantidade, atual->produto.preco );
        atual = atual->proximo;
    }
    
    free(temp);
    sleep(5);
}

void ordenar_produtos(Node** lista) {
    Node* atual = *lista;
    Node* proximo = atual->proximo;
    Node* temp = (Node*)malloc(sizeof(Node));
    
    while (atual != NULL) {
        while (proximo != NULL) {
            if (stricmp(atual->produto.nome, proximo->produto.nome) > 0) {
                temp->produto = atual->produto;
                atual->produto = proximo->produto;
                proximo->produto = temp->produto;
            }
            proximo = proximo->proximo;
        }
        
        atual = atual->proximo;
        if (atual != NULL) {
            proximo = atual->proximo;
        }
    }
    
    atual = *lista;  // reinicia o ponteiro 'atual' para o in�cio da lista
    
    while (atual != NULL) {
        printf("Nome: %s\tCategoria: %s\tC�digo SKU: %d\tQuantidade: %d\tPre�o: %.2f\n", atual->produto.nome, atual->produto.cat_categoria, atual->produto.sku, atual->produto.quantidade, atual->produto.preco );
        atual = atual->proximo;
    }
    
    free(temp);
    sleep(5);
}

void listar_produtos(Node* lista) {
    if (lista == NULL) {
        printf("A lista de produtos esta vazia.\n");
        return;
    }

    printf("Lista de produtos:\n");

    Node* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->produto.nome);
        printf("Categoria: %s\n", atual->produto.cat_categoria);
        printf("C�digo SKU: %d\n", atual->produto.sku);
        printf("Quantidade: %d\n", atual->produto.quantidade);
        printf("Pre�o: %.2f\n", atual->produto.preco);
        printf("--------------------\n");
        sleep(3);

        atual = atual->proximo;
    }
}

void remover_produto(Node** lista) {
    char nome_produto[50];
    char continuar;

    do {
        printf("Digite o nome do produto que deseja remover: ");
        scanf("%49s", nome_produto);
        Node* atual = *lista;

        int encontrou_produto = 0;
        Node* opcoes_equivalencias[10];
        int num_equivalencias = 0;
        while (atual != NULL) {
            if (strcasecmp(atual->produto.nome, nome_produto) == 0) {
                printf("Produto encontrado: %s\n", atual->produto.nome);
                encontrou_produto = 1;
                break;
            } else if (strncasecmp(atual->produto.nome, nome_produto, strlen(nome_produto)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
            }
            atual = atual->proximo;
        }

        if (encontrou_produto) {
            printf("Avan�ando para a remo��o...\n");
            // Chame a fun��o de edi��o aqui
            Node* produto_editado = atual;

            if (atual->anterior == NULL) {
                *lista = atual->proximo;
            } else {
                atual->anterior->proximo = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            printf("O produto foi removido com sucesso!\n");
            sleep(5);
        } else if (num_equivalencias > 0) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i + 1, opcoes_equivalencias[i]->produto.nome);
            }
            printf("%d. Sair\n", num_equivalencias + 1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                Node* produto_editado = opcoes_equivalencias[escolha - 1];
                printf("Voc� escolheu: %s\n", produto_editado->produto.nome);

                if (produto_editado->anterior == NULL) {
                    *lista = produto_editado->proximo;
                } else {
                    produto_editado->anterior->proximo = produto_editado->proximo;
                }
                if (produto_editado->proximo != NULL) {
                    produto_editado->proximo->anterior = produto_editado->anterior;
                }
                free(produto_editado);
                printf("O produto foi removido com sucesso!\n");
                sleep(5);
            } else {
                return;
            }
        } else {
            printf("Nenhum produto encontrado para: %s\n", nome_produto);
            sleep(2);
            return;
        }

        printf("Deseja continuar editando produtos? (S/N) ");
        scanf(" %c", &continuar);
    } while (tolower(continuar) == 's');
}


void editar_produtos(Node** lista) {
    char nome_produto[50];
    char cat_categoria[50];
    int codigo_produto;
    int quantidade_produto;
    float preco_produto;
    char continuar;

    do {
        printf("Digite o nome do produto que deseja editar: ");
        scanf("%49s", nome_produto);
        Node* atual = *lista;

        int encontrou_produto = 0;
        Node* opcoes_equivalencias[10];
        int num_equivalencias = 0;

        while (atual != NULL) {
            if (strcasecmp(atual->produto.nome, nome_produto) == 0) {
                printf("Produto encontrado: %s\n", atual->produto.nome);
                encontrou_produto = 1;
                break;
            } else if (strncasecmp(atual->produto.nome, nome_produto, strlen(nome_produto)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
            }
            atual = atual->proximo;
        }

        if (encontrou_produto) {
            printf("Avan�ando para a edi��o...\n");
            // Chame a fun��o de edi��o aqui
            Node* produto_editado = atual;
            editar_produto(&produto_editado);
        } else if (num_equivalencias > 0) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0 ;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i + 1, opcoes_equivalencias[i]->produto.nome);
            }
            printf("%d. Sair\n", num_equivalencias + 1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                Node* produto_editado = opcoes_equivalencias[escolha - 1];
                printf("Voc� escolheu: %s\n", produto_editado->produto.nome);
                editar_produto(&produto_editado);
            } else {
                return;
            }
        } else {
            printf("Nenhum produto encontrado para: %s\n", nome_produto);
            sleep(2);
            return;
        }

        printf("Deseja continuar editando produtos? (S/N) ");
        scanf(" %c", &continuar);
    } while (tolower(continuar) == 's');
}

void editar_produto(Node** produto) {
    int opcao;
    printf("Escolha o atributo que deseja editar:\n");
    printf("1. Nome do produto\n");
    printf("2. Categoria do produto\n");
    printf("3. C�digo do produto\n");
    printf("4. Quantidade do produto\n");
    printf("5. Pre�o do produto\n");
    printf("Op��o: ");
    scanf("%d", &opcao);
    
    

    switch (opcao) {
        case 1: {
            char novo_nome_produto[50];
            printf("Digite o novo nome do produto: ");
            scanf("%49s", novo_nome_produto);
            strcpy((*produto)->produto.nome, novo_nome_produto);
            break;
        }
        case 2: {
            char nova_categoria[50];
            printf("Digite o nome da nova categoria do produto: ");
            scanf("%49s", nova_categoria);
            strcpy((*produto)->produto.cat_categoria, nova_categoria);
            break;
        }
        case 3: {
            int novo_codigo_produto;
            printf("Digite o novo c�digo do produto: ");
            scanf("%d", &novo_codigo_produto);
            (*produto)->produto.sku = novo_codigo_produto;
            break;
        }
        case 4: {
        	// Verificar limite m�ximo de produtos
            Node* limite = *produto;
            int maximo = 0;

            while (limite != NULL) {
                maximo += limite->produto.quantidade;
                limite = limite->proximo;
            }
            
            int nova_quantidade;
            printf("Digite a nova quantidade do produto: ");
            scanf("%d", &nova_quantidade);

            int quantidade_total = maximo - (*produto)->produto.quantidade + nova_quantidade;

            if (quantidade_total > 250) {
                printf("O novo valor da quantidade ultrapassa o limite m�ximo de produtos. Altera��o n�o permitida.\n");
                sleep(3);
                return;
            }

            (*produto)->produto.quantidade = nova_quantidade;
            break;
        }
        case 5: {
            float novo_preco;
            printf("Digite o novo pre�o do produto: ");
            scanf("%f", &novo_preco);
            (*produto)->produto.preco = novo_preco;
            break;
        }
        default:
            printf("Op��o inv�lida!\n");
            sleep(2);
            break;
    }

    printf("Produto editado com sucesso!\n");
}



void criar_produtos(Node** lista, Node2* lista2) {
    char nome_categoria[50];
    char nome_produto[50];
    int codigo_produto;
    int quantidade_produto;
    float preco_produto;
    char continuar = 's';
    int maximo = 0;
    
    do {
    	Node* limite = *lista;
    
	    while (limite != NULL) {
	        maximo += limite->produto.quantidade;
	        limite = limite->proximo;
	    }
	
	    if (maximo >= 250) {
	        printf("J� atingiu o m�ximo de produtos!\n");
	        sleep(3);
	        return;
	    }
    
        printf("Digite o nome da categoria em que se insere o produto: ");
        scanf("%49s", nome_categoria);
        getchar(); // Limpar o buffer de entrada

        Node2* atual = lista2;

        // Verificar se o nome da categoria procurada est� completo
        int nome_completo = 0;
        while (atual != NULL) {
            if (strcasecmp(atual->categoria.categoria, nome_categoria) == 0) {
                printf("Categoria encontrada: %s\n", atual->categoria.categoria);
                nome_completo = 1;
                break;
            }
            atual = atual->proximo;
        }

        if (nome_completo) {
            // Caso o nome esteja completo, avan�ar para a edi��o diretamente
            printf("Avan�ando para a edi��o...\n");
            // Chame a fun��o de edi��o aqui
        } else {
            int encontrou_equivalencia = 0;
            int num_equivalencias = 0;
            Node2* opcoes_equivalencias[10];

            atual = lista2;

            while (atual != NULL) {
                if (strncasecmp(atual->categoria.categoria, nome_categoria, strlen(nome_categoria)) == 0) {
                    opcoes_equivalencias[num_equivalencias] = atual;
                    num_equivalencias++;
                    encontrou_equivalencia = 1;
                }
                atual = atual->proximo;
            }

            if (encontrou_equivalencia) {
                printf("Foram encontradas as seguintes equival�ncias:\n");
                int i = 0;
                for (i; i < num_equivalencias; i++) {
                    printf("%d. %s\n", i+1, opcoes_equivalencias[i]->categoria.categoria);
                }

                printf("%d. Sair\n", num_equivalencias + 1);

                int escolha = 0;
                printf("Escolha a op��o desejada: ");
                scanf("%d", &escolha);
                getchar(); // Limpar o buffer de entrada

                if (escolha >= 1 && escolha <= num_equivalencias) {
                    atual = opcoes_equivalencias[escolha - 1];
                    printf("Voc� escolheu: %s\n", atual->categoria.categoria);
                    strcpy(nome_categoria , opcoes_equivalencias[escolha - 1]->categoria.categoria);
                } else {
                    return;
                }
            } else {
                printf("Nenhuma equival�ncia encontrada para: %s\n", nome_categoria);
                return;
            }
        }

        printf("Digite o nome do produto: ");
        scanf("%49s", nome_produto);
        getchar(); // Limpar o buffer de entrada

        Node* atual2 = *lista;

        int codigo_aproveitavel = 0;

        do {
            int codigo_existe = 0;
            printf("Digite o c�digo do produto: ");
            while (scanf("%d", &codigo_produto) != 1) {
                printf("Entrada inv�lida. Digite novamente o c�digo do produto: ");
                getchar(); // Limpar o buffer de entrada
            }
            getchar(); // Limpar o buffer de entrada

            while (atual2 != NULL) {
                if (atual2->produto.sku == codigo_produto) {
                    codigo_existe = 1;
                    break;
                }
                atual2 = atual2->proximo;
            }

            if (codigo_existe) {
                printf("Este c�digo j� existe. ");
                continue; // Volta ao in�cio do loop para solicitar novamente o c�digo
            } else {
                codigo_aproveitavel = 1;
                break;
            }
        } while (codigo_aproveitavel != 1);

        printf("Digite a quantidade do produto: ");
        while (scanf("%d", &quantidade_produto) != 1) {
            printf("Entrada inv�lida. Digite novamente a quantidade do produto: ");
            getchar(); // Limpar o buffer de entrada
        }
        getchar(); // Limpar o buffer de entrada
		
		// Verificar se a quantidade atual excede o m�ximo permitido
        if (maximo + quantidade_produto > 250) {
            printf("A quantidade do produto excede o limite m�ximo de 250. Produto n�o criado.\n");
            sleep(3);
            return;
        }
        
        printf("Digite o pre�o do produto: ");
        while (scanf("%f", &preco_produto) != 1) {
            printf("Entrada inv�lida. Digite novamente o pre�o do produto: ");
            getchar(); // Limpar o buffer de entrada
        }
        getchar(); // Limpar o buffer de entrada

        Node* novoNode = (Node*)malloc(sizeof(Node));
        strcpy(novoNode->produto.cat_categoria, nome_categoria);
        novoNode->produto.sku = codigo_produto;
        novoNode->produto.quantidade = quantidade_produto;
        novoNode->produto.preco = preco_produto;
        strcpy(novoNode->produto.nome, nome_produto);
        novoNode->proximo = NULL;

        if (*lista == NULL) {
            *lista = novoNode;
        } else {
            Node* ultimoNode = *lista;
            while (ultimoNode->proximo != NULL) {
                ultimoNode = ultimoNode->proximo;
            }
            ultimoNode->proximo = novoNode;
        }

        printf("Deseja criar outro produto? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // Limpar o buffer de entrada
    } while (continuar == 's');
}


void listar_categorias(Node2* lista){
    Node2* atual = lista;
    int indice = 1;

    // Verifica se a lista est� vazia
    if (atual == NULL) {
        printf("A lista de categorias est� vazia.\n");
        sleep(3);
        return;
    }

    printf("Lista de categorias:\n");
    
    // Percorre a lista e imprime cada categoria
    while (atual != NULL) {
        printf("%d. %s\n", indice, atual->categoria);
        atual = atual->proximo;
        indice++;
    }
    sleep(5);
}

void remover_categorias(Node2** lista) {
    char nome_categoria[50];

    printf("Digite o nome da categoria que deseja remover: ");
    scanf("%49s", nome_categoria);
    getchar(); // Limpar o buffer de entrada

    Node2* atual = *lista;
    int categoria_removida = 0;
    int encontrou_equivalencia = 0;
    int num_equivalencias = 0;
    Node2* opcoes_equivalencias[10];

    while (atual != NULL) {
        if (strcasecmp(atual->categoria.categoria, nome_categoria) == 0) {
            if (atual->anterior == NULL) {
                *lista = atual->proximo;
            } else {
                atual->anterior->proximo = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            categoria_removida = 1;
            break;
        } else if (strncasecmp(atual->categoria.categoria, nome_categoria, strlen(nome_categoria)) == 0) {
            opcoes_equivalencias[num_equivalencias] = atual;
            num_equivalencias++;
            encontrou_equivalencia = 1;
        }
        atual = atual->proximo;
    }

    if (!categoria_removida) {
        if (encontrou_equivalencia) {
            printf("Foram encontradas as seguintes equival�ncias:\n");
            int i = 0;
            for (i; i < num_equivalencias; i++) {
                printf("%d. %s\n", i+1, opcoes_equivalencias[i]->categoria.categoria);
            }

            printf("%d. Sair\n", num_equivalencias+1);

            int escolha = 0;
            printf("Escolha a op��o desejada: ");
            scanf("%d", &escolha);
            getchar(); // Limpar o buffer de entrada

            if (escolha >= 1 && escolha <= num_equivalencias) {
                atual = opcoes_equivalencias[escolha-1];
                if (atual->anterior == NULL) {
                    *lista = atual->proximo;
                } else {
                    atual->anterior->proximo = atual->proximo;
                }
                if (atual->proximo != NULL) {
                    atual->proximo->anterior = atual->anterior;
                }
                free(atual);
                categoria_removida = 1;
            } else {
                return;
            }
        }
    }

    if (categoria_removida) {
        printf("Categoria removida com sucesso!\n");
    } else {
        printf("Nenhuma categoria encontrada para: %s\n", nome_categoria);
    }
    sleep(3);
}


void editar_categoria(Node2** lista2) {
    char categoria_procurada[50];

    printf("Digite a categoria que deseja editar: ");
    scanf("%49s", categoria_procurada);
    getchar(); // Limpar o buffer de entrada

    Node2* atual = *lista2;

    // Verificar se o nome da categoria procurada est� completo
    int nome_completo = 0;
    while (atual != NULL) {
        if (strcasecmp(atual->categoria.categoria, categoria_procurada) == 0) {
            printf("Categoria encontrada: %s\n", atual->categoria.categoria);
            nome_completo = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (nome_completo) {
        // Caso o nome esteja completo, avan�ar para a edi��o diretamente
        printf("Avan�ando para a edi��o...\n");
        // Chame a fun��o de edi��o aqui
    } else {
        int encontrou_equivalencia = 0;
        int num_equivalencias = 0;
        Node2* opcoes_equivalencias[10];

        atual = *lista2;

        while (atual != NULL) {
            if (strncasecmp(atual->categoria.categoria, categoria_procurada, strlen(categoria_procurada)) == 0) {
                opcoes_equivalencias[num_equivalencias] = atual;
                num_equivalencias++;
                encontrou_equivalencia = 1;
            }
            atual = atual->proximo;
        }

        if (encontrou_equivalencia) {
                printf("Foram encontradas as seguintes equival�ncias:\n");
                int i = 0;
                for (i; i < num_equivalencias; i++) {
                    printf("%d. %s\n", i+1, opcoes_equivalencias[i]->categoria.categoria);
                }

                printf("%d. Sair\n", num_equivalencias+1);

                int escolha = 0;
                printf("Escolha a op��o desejada: ");
                scanf("%d", &escolha);
                getchar(); // Limpar o buffer de entrada

                if (escolha >= 1 && escolha <= num_equivalencias) {
                    atual = opcoes_equivalencias[escolha-1];
                    printf("Voc� escolheu: %s\n", atual->categoria.categoria);
                } else {
                    return;
                }
            }
         else {
            printf("Nenhuma equival�ncia encontrada para: %s\n", categoria_procurada);
            return;
        }
    }

    char novo_nome[50];
    printf("Digite o novo nome da categoria: ");
    scanf("%49s", novo_nome);
    getchar(); // Limpar o buffer de entrada

    // Verificar se o novo nome j� existe na lista
    Node2* verificacao = *lista2;
    while (verificacao != NULL) {
        if (strcasecmp(verificacao->categoria.categoria, novo_nome) == 0) {
            printf("O novo nome da categoria j� existe!\n");
            return;
        }
        verificacao = verificacao->proximo;
    }

    // Atualizar o nome da categoria
    strcpy(atual->categoria.categoria, novo_nome);
    printf("Categoria editada com sucesso!\n");
    sleep(3);
}


void criar_categoria(Node2** lista2) {
    char nome_categoria[50];
    char continuar;
    int criado = 0;

    do {
        printf("Digite o nome da categoria: ");
		scanf("%49s", nome_categoria);
		getchar(); // Limpar o buffer de entrada

        Node2* novoNode = (Node2*)malloc(sizeof(Node2));
		if (novoNode == NULL) {
		    printf("Erro ao alocar mem�ria.\n");
		    return;
		}

        strcpy(novoNode->categoria.categoria, nome_categoria);
        novoNode->proximo = NULL;

        // Verificar se a categoria j� existe na lista
        Node2* atual = *lista2;
        while (atual != NULL) {
            if (stricmp(atual->categoria.categoria, nome_categoria) == 0) {
                printf("A categoria j� existe!\n");
                sleep(5);
                return;
            }
            atual = atual->proximo;
            
        }

        // Adicionar o novo n� � lista
        if (*lista2 == NULL) {
            *lista2 = novoNode;
        } else {
            Node2* ultimoNode = *lista2;
            while (ultimoNode->proximo != NULL) {
                ultimoNode = ultimoNode->proximo;
            }
            ultimoNode->proximo = novoNode;
            novoNode->anterior = ultimoNode;
        }
		
		criado++;
        printf("Deseja criar outra categoria? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');
    
    if(criado == 1)
    	printf("A Categoria foi criada com sucesso!");
    else if (criado > 1)
    	printf("As Categorias foram criadas com sucesso!");
    sleep(3);
}


void inserir_no_final_produto(Node** lista, const char* cat_categoria, const char* nome, int sku, int quantidade, float preco) {
    Node* temp = *lista;
    Node* novoNode = (Node*)malloc(sizeof(Node));
    
    strcpy(novoNode->produto.cat_categoria, cat_categoria);
    strcpy(novoNode->produto.nome, nome);
    novoNode->produto.sku = sku;
    novoNode->produto.quantidade = quantidade;
    novoNode->produto.preco = preco;
    
    novoNode->proximo = NULL;
    
    if (*lista == NULL) {
        novoNode->anterior = NULL;
        *lista = novoNode;
    } else {
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNode;
        novoNode->anterior = temp;
    }
}


void inserir_no_final_categoria(Node2** lista2, const char* valor) {
    Node2* temp = *lista2;
    Node2* novoNode = (Node2*)malloc(sizeof(Node2));
    strcpy(novoNode->categoria.categoria, valor);
    novoNode->proximo = NULL;

    if (*lista2 == NULL) {
        novoNode->anterior = NULL;
        *lista2 = novoNode;
    } else {
        
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNode;
        novoNode->anterior = temp;
    }
}

void inserir_no_final_cliente(Node3** lista3, const char* nome, int nif, int contacto) {
    Node3* temp = *lista3;
    Node3* novoNode = (Node3*)malloc(sizeof(Node3));
    
    strcpy(novoNode->cliente.nome, nome);
    novoNode->cliente.nif = nif;
    novoNode->cliente.contacto = contacto;
    
    novoNode->proximo = NULL;

    if (*lista3 == NULL) {
        novoNode->anterior = NULL;
        *lista3 = novoNode;
    } else {
        
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNode;
        novoNode->anterior = temp;
    }
}

void inserir_no_final_vendas(Node4** lista4, const char* nome, int nif, int contacto, const char* cat_categoria, const char* nome_produto, int sku, int quantidade, float preco, int dia, int mes, int ano, int sec, int min, int hora) {
    Node4* temp = *lista4;
    Node4* novoNode = (Node4*)malloc(sizeof(Node4));
    
    strcpy(novoNode->vendas.nome, nome);
    novoNode->vendas.nif = nif;
    novoNode->vendas.contacto = contacto;
    strcpy(novoNode->vendas.cat_categoria, cat_categoria);
    strcpy(novoNode->vendas.nome_produto, nome_produto);
    novoNode->vendas.sku = sku;
    novoNode->vendas.quantidade = quantidade;
    novoNode->vendas.preco = preco;
    novoNode->vendas.dia = dia;
    novoNode->vendas.mes = mes;
    novoNode->vendas.ano = ano;
    novoNode->vendas.sec = sec;
    novoNode->vendas.min = min;
    novoNode->vendas.hora = hora;
    
    novoNode->proximo = NULL;

    if (*lista4 == NULL) {
        novoNode->anterior = NULL;
        *lista4 = novoNode;
    } else {
        
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNode;
        novoNode->anterior = temp;
    }
}

void ler_ficheiros_produtos(Node** lista, const char* nome_arquivo) {
    char linha[100];
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char nome[50];
    int sku;
    int quantidade;
    float preco;
    char categoria[50];
    
    while (fscanf(arquivo, "Categoria:%s\t;Produto:%s\t;SKU:%d\t;Quantidade:%d\t;Pre�o:%f\n", categoria, nome, &sku, &quantidade, &preco) == 5) {
        inserir_no_final_produto(lista, categoria, nome, sku, quantidade, preco);
    }

    fclose(arquivo);
}

void ler_ficheiros_categorias(Node2** lista2, const char* nome_arquivo){
    char linha[100];
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove a quebra de linha da string
        inserir_no_final_categoria(lista2, linha);
    }

    fclose(arquivo);
}

void ler_ficheiros_clientes(Node3** lista3, const char* nome_arquivo){
    char linha[100];
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char nome[50];
    int nif;
    int contacto;
    
    while (fscanf(arquivo, "Nome:%s\t;NIF:%d\t;Contacto:%d\n", nome, &nif, &contacto) == 3) {
        inserir_no_final_cliente(lista3, nome, nif, contacto);
    }

    fclose(arquivo);
}

void ler_ficheiros_vendas(Node4** lista4, const char* nome_arquivo){
    char linha[100];
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char nome[50];
    int nif;
    int contacto;
    char cat_categoria[50];
    char nome_produto[50];
    int sku;
    int quantidade;
    float preco;
    int dia;
	int mes;
	int ano;
	int sec;
	int min;
	int hora;
    
    while (fscanf(arquivo, "Nome:%s\t;NIF:%d\t;Contacto:%d\t;Categoria:%s\t;Produto:%s\t;SKU:%d\t;Quantidade:%d\t;Pre�o:%f\tData:%d:%d:%d\tHora:%d:%d:%d\n", nome, &nif, &contacto, cat_categoria, nome_produto, &sku, &quantidade, &preco, &dia, &mes, &ano, &sec, &min, &hora) == 14) {
        inserir_no_final_vendas(lista4, nome, nif, contacto, cat_categoria, nome_produto, sku, quantidade, preco, dia, mes, ano, sec, min, hora);
    }

    fclose(arquivo);
}


void guardar_no_ficheiro_produtos(Node* lista, const char* nome_arquivo){
    Node* temp = lista;
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (temp != NULL) {
        fprintf(arquivo, "Categoria:%s\t;Produto:%s\t;SKU:%d\t;Quantidade:%d\t;Pre�o:%f\n", temp->produto.cat_categoria, temp->produto.nome,temp->produto.sku, temp->produto.quantidade, temp->produto.preco);
        temp = temp->proximo;
    }
    fclose(arquivo);
}

void guardar_no_ficheiro_categorias(Node2* lista2, const char* nome_arquivo){
    Node2* temp = lista2;
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (temp != NULL) {
        fprintf(arquivo, "%s\n", temp->categoria.categoria);
        temp = temp->proximo;
    }

    fclose(arquivo);
}

void guardar_no_ficheiro_clientes(Node3* lista3, const char* nome_arquivo){
    Node3* temp = lista3;
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (temp != NULL) {
        fprintf(arquivo, "Nome:%s\t;NIF:%d\t;Contacto:%d\n", temp->cliente.nome, temp->cliente.nif, temp->cliente.contacto);
        temp = temp->proximo;
    }
    fclose(arquivo);
}

void guardar_no_ficheiro_vendas(Node4* lista4, const char* nome_arquivo){
    Node4* temp = lista4;
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (temp != NULL) {
        fprintf(arquivo, "Nome:%s\t;NIF:%d\t;Contacto:%d\t;Categoria:%s\t;Produto:%s\t;SKU:%d\t;Quantidade:%d\t;Pre�o:%.2f\tData:%d:%d:%d\tHora:%d:%d:%d\n", temp->vendas.nome, temp->vendas.nif, temp->vendas.contacto, temp->vendas.cat_categoria, temp->vendas.nome_produto, temp->vendas.sku, temp->vendas.quantidade, temp->vendas.preco, temp->vendas.dia, temp->vendas.mes, temp->vendas.ano, temp->vendas.sec, temp->vendas.min, temp->vendas.hora);
        temp = temp->proximo;
    }
    fclose(arquivo);
}

void gerircategorias(int *b, int *d){
	system("cls");
    printf("-------------------------------------------------");
    printf("\n1 - Adicionar Categoria");
    printf("\n2 - Editar Categoria");
    printf("\n3 - Remover Categoria");
    printf("\n4 - Listar Categorias");
    printf("\n0 - Voltar");
    printf("\n-------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",d);
}

void gerirvendas(int *b, int *a)
{
    system("cls");
    printf("------------------------------------------------");
    printf("\n1 - Produtos que mais receita do dia");
    printf("\n2 - Produtos que mais receita do mes");
    printf("\n3 - Produtos que mais receita do ano");
    printf("\n0 - Sair");
    printf("\n------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",a);
}

void vendas(int *b, int *a)
{
    system("cls");
    printf("------------------------------------------------");
    printf("\n1 - Realizar uma venda");
    printf("\n2 - Listagem de todas as vendas do dia");
    printf("\n3 - Listagem de todas as vendas");
    printf("\n4 - Listagem de venda com base nas categorias");
    printf("\n5 - Produtos que mais receita do dia e do mes");
    printf("\n0 - Sair");
    printf("\n------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",a);
}

void gerirclientes(int *b, int*c){
    system("cls");
	printf("-------------------------------------------------");
    printf("\n1 - Adicionar cliente");
    printf("\n2 - Remover cliente");
    printf("\n0 - Voltar");
    printf("\n-------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",c);
}

void clientes(int *b, int *a){
    system("cls");
    printf("-------------------------------------------------");
    printf("\n1 - Gerir clientes");
    printf("\n2 - Listagem dos clientes por ordem alfab�tica");
    printf("\n3 - Buscar cliente com NIF");
    printf("\n0 - Sair");
    printf("\n-------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",a);
}

void gerirprodutos(int *b, int*e){
    system("cls");
	printf("-------------------------------------------------");
    printf("\n1 - Adicionar produto");
    printf("\n2 - Editar produto");
    printf("\n3 - Remover produto");
    printf("\n4 - Listar produtos");
    printf("\n0 - Voltar");
    printf("\n-------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",e);
}

int produtos(int *b , int *a)
{
    system("cls");
    printf("-------------------------------------------------------------------------------");
    printf("\n1-Gerir categorias de produtos\n");
    printf("2-Gerir produtos\n");
    printf("3-Listar produtos por ordem alfab�tica do nome\n");
    printf("4-Listar produtos por ordem descendente do pre�o\n");
    printf("5-Listar categoria de produtos e respetivos produtos\n");
    printf("6-Colocar um produto sem stock\n");
    printf("7-Listar produtos sem stock\n");
    printf("8-Gerar um relat�rio de todo o invent�rio ordenado por categoria de produto\n");
    printf("0-Sair\n");
    printf("-------------------------------------------------------------------------------");
    printf("\nEscolha aqui: ");
    scanf("%d",a);
}

int Menu(int *a,int *b)
{
    system("cls");
    printf("------- Menu -------");
    printf("\n1 - Gerencia de produtos");
    printf("\n2 - Gerencia de clientes");
    printf("\n3 - Gerencia de vendas");
    printf("\n0 - Fechar Menu");
    printf("\n------- Menu -------");
    printf("\nEscolha aqui: ");
    scanf("%d",b);
}
