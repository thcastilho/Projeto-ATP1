# Projeto
## Sistema de Streaming

Uma empresa de streaming de filmes está contratando você para desenvolver uma parte de seu sistema. Segue abaixo as especificações que você deve seguir para desenvolver o sistema solicitado. 

## Entidades
Inicialmente, é necessário entender as entidades envolvidas no processo, as quais são descritas abaixo:

- **Cliente:** Um cliente é uma pessoa que possui um **CPF** (chave de busca), **nome**, **e-mail**, **telefone** e **status** (ativo ou inativo). O telefone segue o formato: 19-9-XXXX-XXXX. Para facilitar, supõe-se que é possível cadastrar no **máximo 10 clientes**.   

- **Filme:** Um filme é descrito pelas seguintes características: um **código único** (chave de busca), **nome**, **gênero** e **classificação**. Os gêneros possíveis são: *aventura (0)*, *comedia (1)*, *drama (2)*, *terror (3)*, *ação (4)* e *romance (5)*. As classificações possíveis são: *livre (0)*, *+10 (1)*, *+12 (2)*, *+14 (3)*, *+16 (4)* e *+18 (5)*. Para facilitar, supõe-se que é possível cadastrar no **máximo 10 filmes**. O código deverá ser gerado automaticamente (auto incremento) e começará na numeração 1001.

- **Planos:** Existem dois tipos: **Básico** e **Premium**. O plano básico é descrito pelas seguintes características: **Quantidade de filmes** que o cliente pode assistir por mês, **valor base do plano** e **valor excedente** por filme adicional assistido (acima da quantidade que o cliente tem direito). O plano premium é descrito pela seguinte característica: **valor base do plano**.

- **Contrato**: Um contrato é descrito pelas seguintes características: **CPF do cliente** relacionado ao contrato (chave de busca), **tipo do plano contratado** (básico (0) ou premium (1)), **data da contratação**, **data do cancelamento** e **tipo de pagamento** (débito (0) ou crédito (1)). Caso o tipo de pagamento seja crédito armazena-se o **número do cartão de crédito**; caso seja débito armazena-se o **número da agência** e o **número da conta** para débito automático. As datas são compotas por dia e mês (exibir para o usuário no formato dia/mês). Enquanto o contrato não é cancelado a data de cancelamento fica em 00/00. Para facilitar, supõe-se que **cada cliente pode ter apenas 1 contrato**.

- **Histórico Mensal:** O sistema deverá armazenar, para cada cliente, seu histórico mensal de filmes assistidos. Assim, haverá uma matriz 10X30 em que cada célula da matriz armazena o **código do filme** assistido, assim como a **data** em que o cliente assistiu ao filme (note que cada linha representa um cliente). Para facilitar, supõe-se que um cliente irá assistir ao no **máximo 30 filmes** no mês (por isso a matriz é 10X30).
## Funcionalidades
O seu sistema disponibiliza as seguintes funcionalidades:

- O sistema é sempre inicializado no mês de janeiro. Para facilitar, supõe-se que todas as operações são realizadas dentro do mesmo ano.

- Toda leitura e verificação de **tipo de plano**, **tipo de pagamento**, **gênero**, **classificação**,**dia** ou **opção dentre 0 ou 1** são repetidas até que o usuário informe um valor válido

- **Cadastrar Cliente:** cadastra um cliente. Sempre que o cliente é cadastrado seu status é colocado como ativo.

- **Cadastrar filme:** cadastra um filme. Lembre-se que o código (chave de busca) será auto incremento, como acima descrito. Não esqueça de validar as entradas para gênero e classificação até o usuário informar um valor válido.

- **Cadastrar plano Básico:** cadastra os dados referente ao plano básico. 

- **Cadastrar plano Premium:** cadastra os dados referente ao plano premium.

- **Cadastrar contrato:** insere uma nova assinatura no sistema. É necessário que o cliente já tenha sido cadastrado e não possua um contrato **(fazer validação)**. Lembre-se que no momento da contratação a data de cancelamento fica em 00/00.

- **Carregar filme:** essa opção simula a escolha de um cliente por um filme que deseja assistir. Inicialmente é necessário informar o CPF do cliente e dia do carregamento (fazer validação até o usuário informar um dia válido).  É necessário que o cliente esteja ativo **(fazer validação)**. O cliente pode informar se deseja ver a lista de filmes disponíveis por gênero(0) ou classificação (1) (a escolha entre gênero ou classificação se repete até que o usuário informe um valor valido (0 ou 1)). Após isso o cliente pode escolher que desejar assistir (código do filme **(fazer validação)**) (obviamente nenhum filme será carregado, basta informar após a escolha “filme carregado com sucesso”). Um filme só poderá ser carregado a depender do histórico e tipo de plano do cliente. Para os clientes do plano premium não há limite de filmes por mês (cliente assiste quantos filmes quiser, restrito a no **máximo 30** (tamanho da matriz) nesse caso). No caso do cliente básico, há um limite (especificado no cadastro do plano básico). Se o limite já estiver excedido, deve-se perguntar ao mesmo se ele deseja assistir pagando-se um valor extra a ser adicionado na fatura (não ou sim, 0 ou 1) (valor esse também informado no cadastro do plano básico)(a escolha se repete até que o usuário informe uma escolha válida). Se ele informar que sim o filme é carregado; caso contrário, não. Sempre que um filme for carregado atualiza-se a **matriz de histórico mensal** do cliente (descrita no início do texto).

- **Cancelar contrato:** cancela um contrato. Para realizar a baixa, atualiza-se a data de cancelamento (dia a ser informado). É necessário verificar se o contrato informado existe **(fazer validação)**. É necessário também que o cliente do contrato esteja ativo **(fazer validação)**, assim como também garantir que a data de cancelamento é posterior a data de contratação **(fazer validação)**. Para que um contrato seja cancelado é necessário informar ao cliente o valor devido até a data do cancelamento e modificar seu status para inativo. Em relação ao valor devido, pode-se usar a mesma função da opção gerar fatura (abaixo descrita).

- **Gerar fatura:** Sempre que essa opção for executada, o usuário informa se é para gerar uma fatura específica (vide cancelar contrato) ou a fatura de todos os clientes (0 ou 1, respectivamente) (a escolha se repete até o usuário informar uma escolha válida). Se for uma fatura específica, informa-se o código do cliente **(fazer validação)** e lista-se o nome dos filmes assistidos pelo mesmo, assim como a data em que o filme foi assistido e o valor devido. Se a opção por todas as faturas for selecionada, lista-se, para cada cliente, o código do mesmo, seu nome e o valor devido. Se o cliente tiver assinatura premium o valor devido é o valor do plano. Se o cliente tiver assinatura básica é necessário verificar quantos filmes adicionais ele assistiu no mês e somar, ao valor base do plano, um valor extra por cada filme. Caso a opção escolhida tenha sido a **“gerar as faturas para todos os clientes cadastrados”**, o contador de mês é incrementado e zera-se o histórico de todos os clientes.

- **Listar os dados de um dado cliente:** o usuário informa o CPF **(fazer validação)** e, na sequência, exibe suas informações (nome, e-mail, telefone e status).

- **Listar o histórico de uma dado cliente:** o usuário informa o CPF **(fazer validação)** e, na sequência, exibe-se o status do cliente e a lista com os nomes dos filmes assistidos, juntamente com a data do carregamento.

- **Listar clientes que excederam a cota mensal:** exibe-se uma lista com os clientes ativos, seus CPFS, nomes e os limites excedentes dos clientes que possuem assinatura básica e que excederam a cota mensal prevista no plano.

- **Frequência de um dado filme:** o usuário informa o código de um filme **(fazer validação)** e a sua frequência é exibida.

- **Recomendar filme:** recomenda um filme para um dado cliente. Inicialmente informa-se o CPF **(fazer validação)**, sendo que o mesmo deverá estar ativo **(fazer validação)**. Para que a recomendação seja realizada, busca-se pelo gênero que o cliente mais assistiu no mês. Na sequência, recomenda-se os demais filmes não assistidos daquele gênero pelo cliente. Caso o cliente não tenha assistido nenhum filme ou já tenha assistido a todos os filmes do gênero mais frequente, informa-se que não é possível fazer a recomendação. Em caso de empate, informa-se os filmes não assistidos dos gêneros que empataram.

- **Sair:** encerra o programa.

## Observações
- Para especificar os tipos de dados é necessário utilizar **struct**, **union** (pelo menos 1) e **enum** (pelo menos 1).
- Para cada opção, implementar uma ou mais funções. Utilize, sempre que puder, passagem por parâmetros (evitando assim, o uso de variáveis globais).
- Todo mês, por padrão dentro do sistema, possui 31 dias.
- O main **apenas** gerencia o menu e as chamadas e os retornos das funções.
- Em relação as strings, sempre declarem as mesma com uma posição a mais, uma vez que internamente o C usa um caractere especial para delimitar fim de string. Exemplo: telefone, que tem formato 19-9-XXXX-XXXX, deve ter tamanho 15 e não 14. Para padronizar, as strings que não tem formato definido devem ser declaradas com tamanho 50.
- Evite ao máximo o uso de variáveis globais.

## Observações sobre a correção:

*  É necessário passar nos casos de teste. Contudo, a nota não será baseada apenas nos casos de teste. Os códigos serão comparados em termo de similaridade, será checado se o mesmo contempla as especificações recomendadas e será avaliada também a qualidade de abstração da solução proposta.

## Menu de Opções:

1  Cadastro de Cliente

2  Cadastrar Filme

3  Cadastrar plano básico

4 Cadastrar plano premium

5  Cadastrar contrato

6  Carregar filme

7  Cancelar contrato

8  Gerar fatura

9  Listar os dados de um dado cliente

10 Listar o histórico de uma dado cliente

11  Listar clientes que excederam a cota mensal

12  Frequência de um dado filme

13 Recomendar filme

0 Sair

## Controle de fluxo:

#### Entradas
As entradas podem ser feitas utilizando:
```c
scanf("%d", &x);   // para inteiros
scanf("%u", &x);   // para enumerações
scanf("%f", &x);   // para pontos flutuantes
scanf(" %s", s);   // para strings sem espaços
scanf(" %[^\n]%*c", s);   // para strings com espaços
```
* * *
### IMPORTANTE:
**Qualquer discrepância entre as saídas abaixo e as saídas dos casos de testes, por favor, enviei um e-mail informando a discordância para os monitores:**  pedro.potenza@unesp.br  e  joao.rodrigues-martins@unesp.br
* * *
#### 1 - Cadastrar Cliente
Verifica a quantidades de clientes cadastrados
```c
printf("ERRO: Numero maximo de clientes no sistema atingido\n");
```
Verifica se cliente ja foi cadastrado
```c
printf("ERRO: CPF do cliente ja cadastrado\n");
```
Em caso de sucesso:
```c
printf("Cliente cadastrado com sucesso\n");
```
* * *
#### 2 - Cadastrar Filme
Verifica a quantidades de filmes cadastrados
```c
printf("ERRO: Numero maximo de filmes no sistema atingido\n");
```
Verifica o gênero informado
```c
printf("ERRO: Genero invalido\n");
```
Verifica a classificação informada
```c
printf("ERRO: Classificao invalida\n");
```
Em caso de sucesso:
```c
printf("Filme cadastrado com sucesso\n");
```
* * *
#### 3 - Cadastrar Plano Básico 
Cadastro do plano básico 
```c
printf("Plano Basico cadastrado com sucesso\n");
```
* * *
#### 4 - Cadastrar Plano Premium
Cadastro do plano premium
```c
printf("Plano Premium cadastrado com sucesso\n");
```
* * *
#### 5 - Cadastrar Contrato
Verifica a quantidades de contratos cadastrados
```c
printf("ERRO: Numero maximo de contratos no sistema atingido\n");
```
Verifica o plano informada
```c
printf("ERRO: Tipo de plano invalido\n");
```
Verifica o tipo de pagamento informada
```c
printf("ERRO: Tipo de pagamento invalido\n");
```
Verifica o dia informado
```c
printf("ERRO: Dia invalido\n");
```
Verifica a quantidade de clientes cadastrados
```c
printf("ERRO: Nenhum cliente cadastrado no sistema\n");;
```
Verifica o cliente informado
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Verifica contrato do cliente
```c
printf("ERRO: Cliente com contrato existente\n");
```
Em caso de sucesso
```c
printf("Contrato cadastrado com sucesso\n");
```
* * *
#### 6 - Carregar Filme
Verifica a quantidades de clientes no sistema
```c
printf("ERRO: Nenhum cliente cadastrado no sistema\n");
```
Verifica a quantidades de filmes carregados
```c
printf("ERRO: Numero maximo de filmes no sistema atingido\n");
```
Verifica o filme informado 
```c
printf("ERRO: Filme nao encontrado\n");
```
Verifica o cliente informado
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Verifica o estado do cliente informado
```c
printf("ERRO: Cliente nao ativo\n");
```
Verifica o dia informado
```c
printf("ERRO: Dia invalido\n");
```
Verifica a opção informada (entre gênero ou classificação e a escolha seguinte)
```c
printf("ERRO: Escolha invalida\n");
```
Taxa adicional negada
```c
printf("ERRO: Taxa adicional negada\n");
```
Em caso de sucesso
```c
printf("Filme carregado com sucesso\n");
```
* * *
#### 7 - Cancelar Contrato
Verifica a quantidades de contratos
```c
printf("ERRO: Nenhum contrato cadastrado no sistema\n");
```
Verifica o cliente
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Verifica o estado do cliente
```c
printf("ERRO: Cliente inativo\n");
```
Verifica o dia informado
```c
printf("ERRO: Dia invalido\n");
printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
```
Em caso de sucesso
```c
printf("Valor devido: %.2f\n",x);
printf("Cancelamento feito com sucesso\n");
```
* * *
#### 8 - Gerar Fatura
Verifica a quantidades de contratos
```c
printf("ERRO: Nenhum contrato cadastrado no sistema\n");
```
Verifica a escolha entre fatura específica ou de todos os clientes
```c
printf("ERRO: Escolha invalida\n");
```
Verifica o cliente
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Verifica o contrato do cliente
```c
printf("ERRO: Cliente nao possui contrato\n");
```
Em caso de sucesso (cliente específico)
```c
printf("Nome: %s\n", nome); //nome do filme
printf("Data: %d/%d\n", dia, mes); //data do carregamento
printf("Valor devido: %.2f\n", x);
```
Em caso de sucesso (todos os clientes)
```c
printf("CPF: %d\n", cpf);
printf("Nome: %s\n", nome); //nome do cliente
printf("Valor devido: %.2f\n", x);
printf("Mes vigente apos a fatura: %d\n", x);
```
***
#### 9 - Listar Dados do Cliente
Verifica a quantidades de clientes
```c
printf("ERRO: Nenhum cliente cadastrado no sistema\n");
```
Verifica o cliente
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Em caso de sucesso
```c
printf("Nome: %s\n", nome);
printf("Email: %s\n", email);
printf("Telefone: %s\n", telefone);
printf("Status: %d\n", estado);
```
***
#### 10 - Lista Histórico de um Cliente
Verifica a quantidades de clientes
```c
printf("ERRO: Nenhum cliente cadastrado no sistema\n");
```
Verifica o cliente
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Cliente não assistiu nenhum filme
```c
printf("ERRO: Nenhum filme assistido\n");
```
Em caso de sucesso
```c
printf("Estado: Ativo\n"); ou printf("Estado: Inativo\n");
printf("Codigo: %d\n",codigo); //codigo do filme
printf("Nome: %s\n",nome); //nome do filme
printf("Genero: %s\n", genero);//escrito por extenso (exemplo: aventura, comedia, ...)
printf("Classificacao: %s\n", classificacao); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
printf("Data do carregamento: %d/%d\n\n",dia, mes);
```
***
#### 11 - Lista Clientes Excedentes da Cota Mensal
Nenhum cliente excedendo a cota
```c
printf("ERRO: Nenhum cliente excedente\n");
```
Em caso de sucesso
```c
printf("CPF: %d\n", cpf);
printf("Nome: %s\n",nome);
printf("Valor excedente: %.2f\n\n",excesso);
```
***
#### 12 - Frequência de um Filme
Verifica a quantidade de filmes no sistema
```c
printf("ERRO: Nenhum filme cadastrado no sistema\n");
```
Verifica o filme
```c
printf("ERRO: Codigo invalido\n");
```
Nenhum filme assistido
```c
printf("ERRO: Nenhum filme assistido\n");
```
Em caso de sucesso
```c
printf("Frequencia: %.2f%%\n",x);
```
***
#### 13 - Recomendar Filme
Verifica a quantidades de clientes
```c
printf("ERRO: Nenhum cliente cadastrado no sistema\n");
```
Verifica o cliente
```c
printf("ERRO: Cliente nao cadastrado\n");
```
Verifica o estado do cliente cliente
```c
printf("ERRO: Cliente nao ativo\n");
```
Verifica se o cliente assistiu todos os filmes do gênero
```c
printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
```
Verifica se nenhum filme foi assistido
```c
printf("ERRO: Nenhum filme assistido\n");
```
Em caso de sucesso
```c
printf("Codigo: %d\n",codigo);

printf("Nome: %s\n",nome);
printf("Genero: %s\n", genero);//escrito por extenso (exemplo: aventura, comedia, ...)
printf("Classificacao: %s\n", classificacao); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
```
***
#### 0 - Sair
Finaliza o programa
```c
printf("Finalizando programa...");
```
***
#### Qualquer outro número
Mensagem de erro
```c
printf("ERRO: Opcao invalida\n");
```
***
