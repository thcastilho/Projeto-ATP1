#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* =======================
======== CLIENTES ========
========================*/

typedef enum e_status
{
    INATIVO,
    ATIVO,
}STATUS;

typedef struct s_clientes
{
    int cpf;
    char nome[50];
    char email[50];
    char telefone[15];
    STATUS statusCliente;
}CLIENTES;

/*=======================
========= FILMES ========
=======================*/

typedef enum e_genero
{
    AVENTURA,
    COMEDIA,
    DRAMA,
    TERROR,
    ACAO,
    ROMANCE,
}GENERO;

typedef enum e_classificacao
{
    LIVRE,
    MAIS10,
    MAIS12,
    MAIS14,
    MAIS16,
    MAIS18,
}CLASSIFICACAO;

typedef struct s_filme
{
    int codigo;
    char nome[50];
    GENERO genFilme;
    CLASSIFICACAO clasFilme;
}FILMES;

/*============================
============ PLANOS ==========
============================*/

typedef struct s_planobasico
{
    int nFilmes;
    float precoBase;
    float precoExtra;
}BASICO;

typedef struct s_planopremium
{
    float precoBase;
}PREMIUM;

typedef enum u_plano
{
    BASIC,
    PREMIERE,
}PLANOS;

/*=============================
=========== CONTRATOS =========
=============================*/

typedef struct s_debito
{
    int agencia;
    int conta;
}DEBITO;

typedef struct s_credito
{
    int cartao;
}CREDITO;

typedef union u_pagamento
{
    DEBITO debito;
    CREDITO credito;
}PAGAMENTOS;

typedef struct s_contrato
{
    int cpf;
    PLANOS plano;
    int diaContrat;
    int mesContrat;
    int diaCancel;
    int mesCancel;
    int opcaoPagamento;
    PAGAMENTOS pagamento;
}CONTRATOS;

/*==============================
============ HISTORICO =========
==============================*/

typedef struct s_historico
{
    int codFilme;
    int dia;
    int mes;
}HISTORICOS; 

/*==============================
========== PROTOTIPOS ==========
==============================*/

int cadastraCliente(CLIENTES* vetClientes, int* contaClientes, int maxClientes);
void cadastraFilme(FILMES* vetFilmes, int* contaFilmes, int* codFilme, int maxFilmes);
void cadastraPlanoBasico(BASICO* pBasico);
void cadastraPlanoPremium(PREMIUM* pPremium);
int cadastraContrato(CONTRATOS* vetContratos, CLIENTES* vetClientes, int* contaClientes, int maxClientes, int* contaContratos, int* mes);
int carregaFilme(CLIENTES* vetClientes, int* contaClientes, FILMES* vetFilmes, int* contaFilmes, CONTRATOS* vetContratos, int* contaContratos, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium, int* mes);
float faturaCliente(int* guardaPlano, int* linha, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium);
void cancelaContrato(CONTRATOS* vetContratos, int* contaContratos, CLIENTES* vetClientes, int* contaClientes, int *mes, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium);
void gerarFatura(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes, int* mes, int maxClientes, CONTRATOS* vetContratos, int* contaContratos, BASICO* pBasico, PREMIUM* pPremium);
void listaDados(CLIENTES* vetClientes, int* contaClientes);
void listaHistorico(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes);
void excedentes(CLIENTES* vetClientes, int* contaClientes, CONTRATOS* vetContratos, int* contaContratos, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium);
void frequencia(FILMES* vetFilmes, int* contaFilmes, HISTORICOS matHistoricos[][30], int* contaClientes, int colunas);
void auxiliaSugestao(FILMES* vetFilmes, int* contaFilmes, HISTORICOS matHistoricos[][30], int colunas, int* maisAssistido, int* guardaPosicao, int* assistiuTudo);
void recomendaFilme(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes);

/*==============================
============= PRINCIPAL ========
==============================*/

int main(void)
{
    //CONSTANTES
    const int maxClientes = 10; //max clientes cadastrados
    const int maxFilmes = 10; //max filmes cadastrados
    const int colunas = 30; //max filmes q um usuario pode assistir no mes

    //VETORES E MATRIZES DE CADASTRO
    CLIENTES vetClientes[maxClientes];
    FILMES vetFilmes[maxFilmes];
    CONTRATOS vetContratos[maxClientes];
    HISTORICOS matHistoricos[maxClientes][colunas];

    //PLANOS
    BASICO pBasico;
    PREMIUM pPremium;

    //CONTADORES
    int contaClientes = 0;
    int contaFilmes = 0;
    int contaContratos = 0;
    int mes = 1;

    //codigo inicial do filme p/ somar de um em um
    int codFilme = 1001;

    //AUXILIARES
    int opcao, verifica;

    //CONTADORES
    int i, j;

    //ZERAR A MATRIZ, pois vai ajudar a analisar a quantidade de filmes assistidos
    for (i = 0; i < maxClientes; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            matHistoricos[i][j].codFilme = 0;
        }
    }


    /*=======================
    ===== MENU PRINCIPAL ====
    =========================
    1) Cadastro de cliente
    2) Cadastro de filme
    3) Cadastrar plano basico
    4) Cadastrar plano premium
    5) Cadastrar contrato
    6) Carregar filme
    7) Cancelar contrato
    8) Gerar fatura
    9) Listar os dados de um cliente
    10) Listar o historico de um cliente
    11) Listar clientes que excederam a cota mensal
    12) Frequncia de um dado filme
    13) Recomendar filme
    0) Sair */

    do
    {
        //printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {
                verifica = cadastraCliente(vetClientes, &contaClientes, maxClientes);
                if (verifica == 0)
                {
                    printf("ERRO: CPF do cliente ja cadastrado\n");
                }
                if (verifica == 1)
                {
                    printf("Cliente cadastrado com sucesso\n");
                }
                if (verifica == 2)
                {
                    printf("ERRO: Numero maximo de clientes no sistema atingido\n");
                }
                
                break;
            }

            case 2:
            {
                cadastraFilme(vetFilmes, &contaFilmes, &codFilme, maxFilmes);

                break;
            }

            case 3:
            {
                cadastraPlanoBasico(&pBasico);

                break;
            }

            case 4:
            {
                cadastraPlanoPremium(&pPremium);

                break;
            }

            case 5:
            {
                verifica = cadastraContrato(vetContratos, vetClientes, &contaClientes, maxClientes, &contaContratos, &mes);
                if (verifica == 0)
                {
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                }
                if (verifica == 1)
                {
                    printf("ERRO: Cliente com contrato existente\n");
                }
                if (verifica == 2)
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                }
                if (verifica == 3)
                {
                    printf("Contrato cadastrado com sucesso\n");
                }
                if (verifica == 4)
                {
                    printf("ERRO: Numero maximo de contratos no sistema atingido\n");
                }
            
                break;
            }

            case 6:
            {
                verifica = carregaFilme(vetClientes, &contaClientes, vetFilmes, &contaFilmes, vetContratos, &contaContratos, matHistoricos, colunas, &pBasico, &pPremium, &mes);
                if (verifica == 0)
                {
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                }
                if (verifica == 1)
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                }
                if (verifica == 2)
                {
                    printf("ERRO: Cliente nao ativo\n");
                }
                if (verifica == 3)
                {
                    printf("ERRO: Filme nao encontrado\n");
                }
                if (verifica == 4)
                {
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                }
                if (verifica == 5)
                {
                    printf("ERRO: Taxa adicional negada\n");
                }
                if (verifica == 6)
                {
                    printf("Filme carregado com sucesso\n");
                }

                break;
            }
            case 7:
            {
                cancelaContrato(vetContratos, &contaContratos, vetClientes, &contaClientes, &mes, matHistoricos, colunas, &pBasico, &pPremium);
            
                break;
            }
            case 8:
            {
                gerarFatura(vetClientes, &contaClientes, matHistoricos, colunas, vetFilmes, &contaFilmes, &mes, maxClientes, vetContratos, &contaContratos, &pBasico, &pPremium);
            
                break;
            }
            case 9:
            {
                listaDados(vetClientes, &contaClientes);
            
                break;
            }
            case 10:
            {
                listaHistorico(vetClientes, &contaClientes, matHistoricos, colunas, vetFilmes, &contaFilmes);
            
                break;
            }
            case 11:
            {
                excedentes(vetClientes, &contaClientes, vetContratos, &contaContratos, matHistoricos, colunas, &pBasico, &pPremium);
            
                break;
            }
            case 12:
            {
                frequencia(vetFilmes, &contaFilmes, matHistoricos, &contaClientes, colunas);
            
                break;
            }
            case 13:
            {
                recomendaFilme(vetClientes, &contaClientes, matHistoricos, colunas, vetFilmes, &contaFilmes);
            
                break;
            }
            case 0:
            {
                printf("Finalizando programa...");
            
                break;
            }
            default: 
            {
                printf("ERRO: Opcao invalida\n");

                break;
            }
        }

    } while (opcao != 0);
    
}

/*=================================
============ SUBROTINAS ===========
=================================*/

int cadastraCliente(CLIENTES* vetClientes, int* contaClientes, int maxClientes)
{
    int i;
    int guardaCPF;

    if ((*contaClientes) >= maxClientes)
    {
        return 2; // numero maximo de clientes 
    }
    
    //printf("CPF: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
    {
        if (guardaCPF == vetClientes[i].cpf)
        {
            return 0; //cpf do cliente ja cadastrado
        }
    }

    vetClientes[(*contaClientes)].cpf = guardaCPF;

    //printf("Nome: ");
    scanf(" %[^\n]%*c", vetClientes[(*contaClientes)].nome);

    //printf("Email: ");
    scanf(" %s", vetClientes[(*contaClientes)].email);

    //printf("Telefone: ");
    scanf(" %s", vetClientes[(*contaClientes)].telefone);

    vetClientes[(*contaClientes)].statusCliente = INATIVO;

    (*contaClientes)++;

    return 1; //cliente cadastrado com sucesso
}

void cadastraFilme(FILMES* vetFilmes, int* contaFilmes, int* codFilme, int maxFilmes)
{
    int guardaGenero, guardaClassif;
    int valido;

    if ((*contaFilmes) >= maxFilmes)
    {
        printf("ERRO: Numero maximo de filmes no sistema atingido\n");
        return;
    }
    
    //printf("Nome do filme: ");
    scanf(" %[^\n]%*c", vetFilmes[(*contaFilmes)].nome);

    do
    {
        valido = 0;
        //printf("Genero: ");
        scanf("%d", &guardaGenero);

        if ((guardaGenero < 0) || (guardaGenero > 5))
        {
            valido = 1;
            printf("ERRO: Genero invalido\n");
        }
    } while (valido == 1);

    do
    {
        valido = 0;
        //printf("Classificacao: ");
        scanf("%d", &guardaClassif);

        if ((guardaClassif < 0 ) || (guardaClassif > 5))
        {
            valido = 1;
            printf("ERRO: Classificao invalida\n");
        }
    } while (valido == 1);

    vetFilmes[(*contaFilmes)].codigo = (*codFilme);
    vetFilmes[(*contaFilmes)].genFilme = guardaGenero;
    vetFilmes[(*contaFilmes)].clasFilme = guardaClassif;

    (*contaFilmes)++;
    (*codFilme)++;

    printf("Filme cadastrado com sucesso\n");
}

void cadastraPlanoBasico(BASICO* pBasico)
{
    //printf("Numero de filmes: ");
    scanf("%d", &pBasico->nFilmes);

    //printf("Valor base: ");
    scanf("%f", &pBasico->precoBase);

    //printf("Valor extra: ");
    scanf("%f", &pBasico->precoExtra);

    printf("Plano Basico cadastrado com sucesso\n");
}

void cadastraPlanoPremium(PREMIUM* pPremium)
{
    //printf("Preco Base: ");
    scanf("%f", &pPremium->precoBase);

    printf("Plano Premium cadastrado com sucesso\n");
}

int cadastraContrato(CONTRATOS* vetContratos, CLIENTES* vetClientes, int* contaClientes, int maxClientes, int* contaContratos, int* mes)
{
    int i, j, guardaCPF, valido=0;
    int guardaDia, guardaPlano, guardaPagamento, guardaAgencia, guardaConta, guardaCartao;

    if ((*contaContratos) >= maxClientes)
    {
        return 4; //numero maximo de contratos atingido
    }
    
    if ((*contaClientes) == 0)
    {
        return 0; //nenhum cliente cadastrado
    }

    //printf("CPF do cliente: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
    {
        if (guardaCPF == vetClientes[i].cpf)
        {
            valido = 1;
            for (j = 0; j < (*contaContratos); j++)
            {
                if (guardaCPF == vetContratos[j].cpf)
                {
                    return 1; //cliente com contrato existente
                }
            }
            vetClientes[i].statusCliente = ATIVO;
            break;
        }
    }

    if (valido == 0)
    {
        return 2; //cliente nao cadastrado
    }


    valido = 0;

    do
    {
        //printf("Plano: ");
        scanf("%d", &guardaPlano);
        
        if ((guardaPlano == 0) || (guardaPlano == 1))
        {
            valido = 1;
        }
        else printf("ERRO: Tipo de plano invalido\n");

    } while (valido != 1);

    valido = 0;

    do
    {
        //printf("Tipo de pagamento: ");
        scanf("%d", &guardaPagamento);

        if ((guardaPagamento == 0) || (guardaPagamento == 1))
        {
            valido = 1;
        }
        else printf("ERRO: Tipo de pagamento invalido\n");
    
    } while (valido != 1);
    
    valido = 0;

    if (guardaPagamento == 0)
    {
        //printf("Agencia: ");
        scanf("%d", &guardaAgencia);

        //printf("Conta: ");
        scanf("%d", &guardaConta);
    }
    else if (guardaPagamento == 1)
    {
        //printf("Cartao: ");
        scanf("%d", &guardaCartao);
    }

    do
    {
        //printf("Dia da contratacao: ");
        scanf("%d", &guardaDia);

        if ((guardaDia >= 1) && (guardaDia <= 31))
        {
            valido = 1;
        }
        else printf("ERRO: Dia invalido\n");

    } while (valido != 1);

    vetContratos[(*contaContratos)].cpf = guardaCPF;
    vetContratos[(*contaContratos)].diaContrat = guardaDia;
    vetContratos[(*contaContratos)].opcaoPagamento = guardaPagamento;
    if (guardaPagamento == 0)
        {
            vetContratos[(*contaContratos)].pagamento.debito.agencia = guardaAgencia;
            vetContratos[(*contaContratos)].pagamento.debito.conta = guardaConta;
        }
    else if (guardaPagamento == 1)
        {
            vetContratos[(*contaContratos)].pagamento.credito.cartao = guardaCartao;
        }
    vetContratos[(*contaContratos)].plano = guardaPlano;
    vetContratos[(*contaContratos)].diaCancel = 00;
    vetContratos[(*contaContratos)].mesCancel = 00;
    vetContratos[(*contaContratos)].mesContrat = (*mes);

    (*contaContratos)++;

    return 3; //contrato cadastrado com sucesso
}

int carregaFilme(CLIENTES* vetClientes, int* contaClientes, FILMES* vetFilmes, int* contaFilmes, CONTRATOS* vetContratos, int* contaContratos, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium, int* mes)
{
    int i, j; // contadores
    int guardaCPF, guardaDia, guardaCod, guardaPosicao, guardaColuna; // guarda variavel
    int sValido=0, achouCPF=0, existeFilme=0, escolhaValida=0, temEspaco=0; // controladores 
    int op; // opcao de filtro (gen ou classif)
    int filtro; // opcao NO filtro (1, 2, 3...)
    int pagarExtra; // quer pagar extra?

    //========== ve se existem clientes ===========
    if ((*contaClientes) == 0)
        {
            return 0;//ERRO: Nenhum cliente cadastrado
        }

    //======== ve se o cliente existe ========
    
    //printf("CPF do cliente: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
        {
            if (guardaCPF == vetClientes[i].cpf)
            {
                achouCPF = 1;
                guardaPosicao = i;
                break;
            }
        }
    if (achouCPF == 0)
    {
        return 1; // cliente nao cadastrado
    }

    //============= ve se o cliente tem espaco na matriz ===========
    for (i = 0; i < colunas; i++)
    {
        if (matHistoricos[guardaPosicao][i].codFilme == 0)
        {
            temEspaco = 1;
            break;
        }
    }

    if (temEspaco == 0)
    {
        return 4; // n tem espaco na matriz
    }

    //======== ve se o cliente ta ativo ==========
    if (vetClientes[guardaPosicao].statusCliente == ATIVO)
    {
        sValido = 1;
    }

    if (sValido == 0)
    {
        return 2; // cliente nao ativo
    }

    //=============== verifica dia ============
    do
    {
        //printf("Dia: ");
        scanf("%d", &guardaDia);

        if ((guardaDia >= 1) && (guardaDia <= 31))
        {
            escolhaValida = 1;
        }
        else printf("ERRO: Dia invalido\n");

    } while (escolhaValida != 1);

    escolhaValida = 0;

    // ========= verifica filtro =========
    do
    {
        //printf("Opcao de filtro (0 ou 1): ");
        scanf("%d", &op);

        if ((op == 0) || (op == 1))
        {
            escolhaValida = 1;
        }
        else printf("ERRO: Escolha invalida\n");

    } while (escolhaValida != 1);

    escolhaValida = 0;

    //verifica filtro
    do
    {
        //printf("Opcao NO filtro (0 a 5): ");
        scanf("%d", &filtro);

        if((filtro >= 0) && (filtro <= 5)) 
        {
            escolhaValida = 1;
        }
        else printf("ERRO: Escolha invalida\n");

    } while (escolhaValida != 1);

    if (op == 0) //por genero
    {
        for (i = 0; i < (*contaFilmes); i++)
        {
            if (vetFilmes[i].genFilme == filtro)
            {
                printf("Codigo: %d\n", vetFilmes[i].codigo);
                printf("Nome: %s\n", vetFilmes[i].nome);
            }
        }
    }
    else //por classificacao
    {
        for (i = 0; i < (*contaFilmes); i++)
        {
            if (vetFilmes[i].clasFilme == filtro)
            {
                printf("Codigo: %d\n", vetFilmes[i].codigo);
                printf("Nome: %s\n", vetFilmes[i].nome);
            }
        }
    }
    //verifica filme 

    //printf("Codigo do filme: ");
    scanf("%d", &guardaCod);
    for (i = 0; i < (*contaFilmes); i++)
    {
        if (guardaCod == vetFilmes[i].codigo)
        {
            existeFilme = 1;
            break;
        }
    }

    if (existeFilme == 0)
    {
        return 3; // filme nao encontrado
    }

    escolhaValida = 0;

    //VERIFICA CONTRATO
    for (i = 0; i < (*contaContratos); i++)
    {
        if (vetClientes[guardaPosicao].cpf == vetContratos[i].cpf)
        {
            if (vetContratos[i].plano == 0)
            {
                for (j = 0; j < colunas; j++)
                {
                    if (matHistoricos[guardaPosicao][j].codFilme == 0) //TA VAZIO
                    {
                        guardaColuna = j;
                        break;
                    }
                }
                
                if (guardaColuna + 1 > pBasico->nFilmes) //ULTRAPASSOU O LIMITE DO PLANO; +1 pois a primeira coluna é 0
                {
                    do
                    {
                        //printf("Deseja assistir por um valor adicional? ");
                        scanf("%d", &pagarExtra);

                        if ((pagarExtra == 0) || (pagarExtra == 1))
                        {
                            escolhaValida = 1;
                        }
                        else printf("ERRO: Escolha invalida\n");

                    } while (escolhaValida != 1);

                    if (pagarExtra == 0) // nao pagar extra
                    {
                        return 5; // taxa adicional negada
                    }
                    else
                    {
                        matHistoricos[guardaPosicao][guardaColuna].codFilme = guardaCod;
                        matHistoricos[guardaPosicao][guardaColuna].dia = guardaDia;
                        matHistoricos[guardaPosicao][guardaColuna].mes = (*mes);
                        return 6; //filme carregado com sucesso
                    }
                }
                else
                {
                    matHistoricos[guardaPosicao][guardaColuna].codFilme = guardaCod;
                    matHistoricos[guardaPosicao][guardaColuna].dia = guardaDia;
                    matHistoricos[guardaPosicao][guardaColuna].mes = (*mes);
                    return 6; //filme carregado com sucesso
                }
            }
            else // plano premium
            {
                for (j = 0; j < colunas; j++)
                {
                    if (matHistoricos[guardaPosicao][j].codFilme == 0) //TA VAZIO
                    {
                        temEspaco = 1;
                        guardaColuna = j;
                        break;
                    }
                }

                if (temEspaco == 0)
                {
                    return 4; //numero maximo de filmes no sistema atingido
                }

                matHistoricos[guardaPosicao][guardaColuna].codFilme = guardaCod;
                matHistoricos[guardaPosicao][guardaColuna].dia = guardaDia;
                matHistoricos[guardaPosicao][guardaColuna].mes = (*mes);
                
                return 6; //filme carregado com sucesso
            }
            break;
        }
    }
    return -1; //warning run.codes
}

float faturaCliente(int* guardaPlano, int* linha, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium)
{
    int i, numeroFilmes=0;

    if ((*guardaPlano) == 0) // basico
    {
        for (i = 0; i < colunas; i++)
        {
            if (matHistoricos[(*linha)][i].codFilme != 0)
            {
                numeroFilmes++;
            }
        }

        if (numeroFilmes <= pBasico->nFilmes)
        {
            return (pBasico->precoBase);
        }
        else 
        {
            return (pBasico->precoBase + ((numeroFilmes - pBasico->nFilmes)*pBasico->precoExtra));
        }
    }
    else // premium
    {
        return (pPremium->precoBase);
    }
}

void cancelaContrato(CONTRATOS* vetContratos, int* contaContratos, CLIENTES* vetClientes, int* contaClientes, int *mes, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium)
{
    int i; // contadores
    int guardaPlano, guardaCPF, guardaPosicao, guardaData, guardaCliente; //guarda variavel
    int existeCliente=0, diaValido=0; //controladores

    if (*contaContratos == 0)
    {
        printf("ERRO: Nenhum contrato cadastrado no sistema\n");
        return;
    }

    //printf("CPF do cliente: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
    {
        if (guardaCPF == vetClientes[i].cpf)
        {
            if (vetClientes[i].statusCliente == INATIVO)
            {
                printf("ERRO: Cliente inativo\n");
                return;
            }
        }
    }

    for (i = 0; i < (*contaContratos); i++)
    {
        if (guardaCPF == vetContratos[i].cpf)
        {
            guardaPosicao = i;
            existeCliente = 1;
            break;
        }
    }

    if (existeCliente == 0)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }

    for (i = 0; i < (*contaClientes); i++)
    {
        if (vetContratos[guardaPosicao].cpf == vetClientes[i].cpf)
        {
            if (vetClientes[i].statusCliente == ATIVO)
            {
                guardaCliente = i;
            }
            break;
        }
    }

    do
    {
        //printf("Data de cancelamento: ");
        scanf("%d", &guardaData);

        if((guardaData >= 1) && (guardaData <= 31))
        {
            if ((*mes) > (vetContratos[guardaPosicao].mesContrat))
            {
                break;
            }
            else if (guardaData >= vetContratos[guardaPosicao].diaContrat)
                {
                    diaValido = 1;
                }
                else 
                {
                    printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                    return;
                }
        }
        else printf("ERRO: Dia invalido\n");

    } while (diaValido != 1);

    guardaPlano = vetContratos[guardaPosicao].plano;
    vetContratos[guardaPosicao].diaCancel = guardaData;
    vetContratos[guardaPosicao].mesCancel = (*mes);
    vetClientes[guardaCliente].statusCliente = INATIVO;

    printf("Valor devido: %.2f\n", faturaCliente(&guardaPlano, &guardaCliente, matHistoricos, colunas, pBasico, pPremium));
    printf("Cancelamento feito com sucesso\n");

    
    for (i = guardaPosicao; i < (*contaContratos); i++)
    {
        vetContratos[i] = vetContratos[i + 1];
    }
    (*contaContratos)--;

}

void gerarFatura(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes, int* mes, int maxClientes, CONTRATOS* vetContratos, int* contaContratos, BASICO* pBasico, PREMIUM* pPremium)
{
    int i, j; // contadores
    int opcao;
    int opcaoValida = 0, existe = 0; // controladores
    int guardaCPF, guardaPosicao, guardaPlano; // guarda variavel
    
    do
    {
        //printf("Opcao (especifica ou geral): ");
        scanf("%d", &opcao);

        if ((opcao == 0) || (opcao == 1))
        {
            opcaoValida = 1;
        }
        else printf("ERRO: Escolha invalida\n");

    } while (opcaoValida != 1);

    if (opcao == 0) // especifica
    {
        if ((*contaClientes) == 0)
        {
            printf("ERRO: Nenhum cliente cadastrado no sistema\n");
            return;
        }
        
        //printf("CPF do cliente: ");
        scanf("%d", &guardaCPF);

        for (i = 0; i < (*contaClientes); i++)
        {
            if (guardaCPF == vetClientes[i].cpf)
            {
                existe = 1;
                if (vetClientes[i].statusCliente == INATIVO)
                {
                    printf("ERRO: Cliente nao possui contrato\n");
                    return;
                }
                else
                {
                    guardaPosicao = i;
                    break;
                }
            }
        }

        if (existe == 0)
        {
            printf("ERRO: Cliente nao cadastrado\n");
            return;
        }

        for (i = 0; i < colunas; i++)
        {
            for (j = 0; j < (*contaFilmes); j++)
            {
                if (matHistoricos[guardaPosicao][i].codFilme == vetFilmes[j].codigo)
                {
                    printf("Nome: %s\n", vetFilmes[j].nome);
                    printf("Data: %d/%d\n", matHistoricos[guardaPosicao][i].dia, matHistoricos[guardaPosicao][i].mes);
                }
            }
        }

        for (i = 0; i < (*contaContratos); i++)
        {
            if (vetClientes[guardaPosicao].cpf == vetContratos[i].cpf)
            {
                guardaPlano = vetContratos[i].plano;
                break;
            }
        }
        printf("Valor devido: %.2f\n", faturaCliente(&guardaPlano, &guardaPosicao, matHistoricos, colunas, pBasico, pPremium));
    }

    if(opcao == 1)
    {
        for (i = 0; i < (*contaClientes); i++)
        {
            if (vetClientes[i].statusCliente == ATIVO)
            {
                printf("CPF: %d\n", vetClientes[i].cpf);
                printf("Nome: %s\n", vetClientes[i].nome);

                for (j = 0; j < (*contaContratos); j++)
                {
                    if (vetClientes[i].cpf == vetContratos[j].cpf)
                    {
                        guardaPlano = vetContratos[j].plano;
                        break;
                    }
                }
                printf("Valor devido: %.2f\n", faturaCliente(&guardaPlano, &i, matHistoricos, colunas, pBasico, pPremium));
            }
        }

        printf("Mes vigente apos a fatura: %d\n", (*mes)+1);

        (*mes)++; //soma mes
        for (i = 0; i < maxClientes; i++) //zera o historico
        {
            for (j = 0; j < colunas; j++)
            {
                matHistoricos[i][j].codFilme = 0;
            }
        }
    }
    
}

void listaDados(CLIENTES* vetClientes, int* contaClientes)
{
    int i, guardaCPF, existe=0;
    
    if ((*contaClientes) == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    
    //printf("CPF: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
    {
        if (guardaCPF == vetClientes[i].cpf)
        {
            existe = 1;

            printf("Nome: %s\n", vetClientes[i].nome);
            printf("Email: %s\n", vetClientes[i].email);
            printf("Telefone: %s\n", vetClientes[i].telefone);
            printf("Status: %d\n", vetClientes[i].statusCliente);

            return;
        }
    }

    if (existe == 0)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
}

void listaHistorico(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes)
{
    int i, j, guardaCPF, guardaPosicao;
    int existe = 0;

    if ((*contaClientes) == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    //printf("CPF: ");
    scanf("%d", &guardaCPF);

    for (i = 0;  i < (*contaClientes); i++)
    {
        if (guardaCPF == vetClientes[i].cpf)
        {
            existe = 1;
            guardaPosicao = i;
            break;
        }
    }

    if (existe == 0)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }

    if (vetClientes[guardaPosicao].statusCliente == INATIVO)
    {
        printf("Estado: Inativo\n");
    }
    else printf("Estado: Ativo\n");

    if (matHistoricos[guardaPosicao][0].codFilme == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }

    for (i = 0; i < colunas; i++)
    {
        if (matHistoricos[guardaPosicao][i].codFilme != 0)
        {
            printf("Codigo: %d\n", matHistoricos[guardaPosicao][i].codFilme);
            for (j = 0; j < (*contaFilmes); j++)
            {
                if (matHistoricos[guardaPosicao][i].codFilme == vetFilmes[j].codigo)
                {
                    printf("Nome: %s\n", vetFilmes[j].nome);
                    switch(vetFilmes[j].genFilme)
                    {
                        case AVENTURA:
                        {
                            printf("Genero: aventura\n");
                            break;
                        }
                        case COMEDIA:
                        {
                            printf("Genero: comedia\n");
                            break;
                        }
                        case DRAMA:
                        {
                            printf("Genero: drama\n");
                            break;
                        }
                        case TERROR:
                        {
                            printf("Genero: terror\n");
                            break;
                        }
                        case ACAO:
                        {
                            printf("Genero: acao\n");
                            break;
                        }
                        case ROMANCE:
                        {
                            printf("Genero: romance\n");
                            break;
                        }
                    }
                    switch(vetFilmes[j].clasFilme)
                    {
                        case LIVRE: 
                        {
                            printf("Classificacao: livre\n");
                            break;
                        }
                        case MAIS10:
                        {
                            printf("Classificacao: +10\n");
                            break;
                        }
                        case MAIS12:
                        {
                            printf("Classificacao: +12\n");
                            break;
                        }
                        case MAIS14:
                        {
                            printf("Classificacao: +14\n");
                            break;
                        }
                        case MAIS16:
                        {
                            printf("Classificacao: +16\n");
                            break;
                        }
                        case MAIS18:
                        {
                            printf("Classificacao: +18\n");
                            break;
                        }
                    }
                    printf("Data do carregamento: %d/%d\n\n", matHistoricos[guardaPosicao][i].dia, matHistoricos[guardaPosicao][i].mes);
                }
            }
        }
    }
}

void excedentes(CLIENTES* vetClientes, int* contaClientes, CONTRATOS* vetContratos, int* contaContratos, HISTORICOS matHistoricos[][30], int colunas, BASICO* pBasico, PREMIUM* pPremium)
{
    int i, j, guardaPlano;
    int existe = 0;
    float valor;

    for (i = 0; i < (*contaClientes); i++)
    {
        for (j = 0; j < (*contaContratos); j++)
        {
            if (vetClientes[i].cpf == vetContratos[j].cpf)
            {
                guardaPlano = vetContratos[j].plano;
                break;
            }
        }
        if (guardaPlano == BASIC)
        {
            valor = faturaCliente(&guardaPlano, &i, matHistoricos, colunas, pBasico, pPremium);

            if (valor > pBasico->precoBase)
            {
                existe = 1;
                printf("CPF: %d\n", vetClientes[i].cpf);
                printf("Nome: %s\n", vetClientes[i].nome);
                printf("Valor excedente: %.2f\n\n", (valor - pBasico->precoBase));
            }
        }
    }

    if (existe == 0)
    {
        printf("ERRO: Nenhum cliente excedente\n");
    }
}

void frequencia(FILMES* vetFilmes, int* contaFilmes, HISTORICOS matHistoricos[][30], int* contaClientes, int colunas)
{
    int i, j, guardaFilme, existe = 0, assistiu = 0;
    int contador=0; //conta a quantidade 
    
    if ((*contaFilmes) == 0)
    {
        printf("ERRO: Nenhum filme cadastrado no sistema\n");
        return;
    }

    //printf("Codigo do filme: ");
    scanf("%d", &guardaFilme);

    for (i = 0; i < (*contaFilmes); i++)
    {
        if (guardaFilme == vetFilmes[i].codigo)
        {
            existe = 1;
        }
    }

    if (existe == 0)
    {
        printf("ERRO: Codigo invalido\n");
        return;
    }

    for (i = 0; i < (*contaClientes); i++)
    {
        for (j = 0; j < colunas; j++)
        {
            if (matHistoricos[i][j].codFilme == guardaFilme)
            {
                contador++;
            }
            if (matHistoricos[i][j].codFilme != 0)
            {
                assistiu++;
            }
        }
    }

    if (assistiu == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }

    printf("Frequencia: %.2f%%\n", ( ((float)(contador) / assistiu) * 100 ));
}

void recomendaFilme(CLIENTES* vetClientes, int* contaClientes, HISTORICOS matHistoricos[][30], int colunas, FILMES* vetFilmes, int* contaFilmes)
{
    int i, j, guardaCPF, guardaPosicao;
    int existe = 0, ativo = 0, assistiu = 0;
    const int generos = 6;
    int vetGenero[generos]; //pra ver o genero mais assistido

    int maisAssistido;
    int assistiuTudo = 1; //CONSIDERA Q ELE JA ASSISTIU TODOS OS FILMES DO GENERO
    
    for (i = 0; i < generos; i++)
    {
        vetGenero[i] = 0;
    }

    if ((*contaClientes) == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    //printf("CPF: ");
    scanf("%d", &guardaCPF);

    for (i = 0; i < (*contaClientes); i++)
    {

        if (guardaCPF == vetClientes[i].cpf)
        {
            existe = 1;
            guardaPosicao = i;
            if (vetClientes[i].statusCliente == ATIVO)
            {
                ativo = 1;
            }
            break;
        }
    }

    if (existe == 0)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }

    if (ativo == 0)
    {
        printf("ERRO: Cliente nao ativo\n");
        return;
    }

    for (i = 0; i < colunas; i++)
    {
        if (matHistoricos[guardaPosicao][i].codFilme != 0)
        {
            assistiu = 1;
            for (j = 0; j < (*contaFilmes); j++)
            {
                if (matHistoricos[guardaPosicao][i].codFilme == vetFilmes[j].codigo)
                {
                    switch(vetFilmes[j].genFilme)
                    {
                        case AVENTURA:
                        {
                            vetGenero[0]++;
                            break;
                        }
                        case COMEDIA:
                        {
                            vetGenero[1]++;
                            break;
                        }
                        case DRAMA:
                        {
                            vetGenero[2]++;
                            break;
                        }
                        case TERROR:
                        {
                            vetGenero[3]++;
                            break;
                        }
                        case ACAO:
                        {
                            vetGenero[4]++;
                            break;
                        }
                        case ROMANCE:
                        {
                            vetGenero[5]++;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (assistiu == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }

    maisAssistido = 0;
    for (i = 0; i < generos; i++)
    {    
        if (vetGenero[i] > maisAssistido)
        {
            maisAssistido = i;
        }
    }
    auxiliaSugestao(vetFilmes, contaFilmes, matHistoricos, colunas, &maisAssistido, &guardaPosicao, &assistiuTudo);

    for (i = 0; i < generos; i++)
    {
        if ((vetGenero[i] == vetGenero[maisAssistido]) && (i != maisAssistido))
        {
            auxiliaSugestao(vetFilmes, contaFilmes, matHistoricos, colunas, &i, &guardaPosicao, &assistiuTudo);
        }
    }

    if (assistiuTudo == 1)
    {
        printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
    }
}

void auxiliaSugestao(FILMES* vetFilmes, int* contaFilmes, HISTORICOS matHistoricos[][30], int colunas, int* maisAssistido, int* guardaPosicao, int* assistiuTudo)
{
    int i, j;
    
    const int maxMovies = 10; // so acontece se todos os filmes forem do mesmo genero, mas é bom pq vai QUE
    int assistidos[maxMovies]; //pra ver quais filmes assistiu 
    int nAssistidos = 0;
    int jaAssistiu;
    
    for (i = 0; i < (*contaFilmes); i++)
    {
        if (vetFilmes[i].genFilme == (*maisAssistido)) // se o filme é do genero mais assistido
        {
            for (j = 0; j < colunas; j++)
            {
                if (matHistoricos[(*guardaPosicao)][j].codFilme == vetFilmes[i].codigo) //se ele assistiu tal fime
                {
                    assistidos[nAssistidos] = vetFilmes[i].codigo; //salvo no vetor de assistidos
                    nAssistidos++;
                }
            }
        }
    }

    for (i = 0; i < (*contaFilmes); i++) // PARA CADA FILME 
    {
        if (vetFilmes[i].genFilme == (*maisAssistido)) // SE O GENERO FOR O MAIS ASSISTIDO 
        {
            for (j = 0; j < nAssistidos; j++) // VEJO SE O FILME TA NO VETOR DE ASSISTIDOS 
            {
                jaAssistiu = 0; // CONSIDERO QUE NAO TA 
                if (vetFilmes[i].codigo == assistidos[j]) // SE TA 
                {
                    jaAssistiu = 1; // ENTAO ASSISTIU 
                    break; //PARO DE PROCURAR
                }
            }

            if (jaAssistiu == 0)// NAO ASSISTIU 
            {
                (*assistiuTudo) = 0; //NAO ASSISTIU TODOS
                printf("Codigo: %d\n", vetFilmes[i].codigo);
                printf("Nome: %s\n", vetFilmes[i].nome);
                switch(vetFilmes[i].genFilme)
                {
                    case AVENTURA:
                    {
                        printf("Genero: aventura\n");
                        break;
                    }
                    case COMEDIA:
                    {
                        printf("Genero: comedia\n");
                        break;
                    }
                    case DRAMA:
                    {
                        printf("Genero: drama\n");
                        break;
                    }
                    case TERROR:
                    {
                        printf("Genero: terror\n");
                        break;
                    }
                    case ACAO:
                    {
                        printf("Genero: acao\n");
                        break;
                    }
                    case ROMANCE:
                    {
                        printf("Genero: romance\n");
                        break;
                    }
                }
                switch(vetFilmes[i].clasFilme)
                {
                    case LIVRE: 
                    {
                        printf("Classificacao: livre\n");
                        break;
                    }
                    case MAIS10:
                    {
                        printf("Classificacao: +10\n");
                        break;
                    }
                    case MAIS12:
                    {
                        printf("Classificacao: +12\n");
                        break;
                    }
                    case MAIS14:
                    {
                        printf("Classificacao: +14\n");
                        break;
                    }
                    case MAIS16:
                    {
                        printf("Classificacao: +16\n");
                        break;
                    }
                    case MAIS18:
                    {
                        printf("Classificacao: +18\n");
                        break;
                    }
                }
            }
        }
    }
}