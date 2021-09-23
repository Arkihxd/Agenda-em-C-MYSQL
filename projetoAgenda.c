#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

void main(void)
{
	MYSQL conexao;
	MYSQL_RES *resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD *campos;
	int op, opbusca, opcao, opalterar, opexcluir;
	char nome[50], enderecoemail[50], estado[50];
	int telefone, cpf, cep, numero, cod_estado, cod_cidade, cod_endereco, cod_contato, cod_email, cod_telefone;
	char rua[50], bairro[50], cidade[50];
	char str[200];
	char nomebusca[50], emailbusca[50], enderecobusca[50];
	char query[200];
	int conta;
	char nomealterar[50];
	int enderecoalterar, alterarcodigo;
	int excluircodigo;

	mysql_init(&conexao);
	if (mysql_real_connect(&conexao, "url", "root", "senha", "agenda", 3132, NULL, 0))
	{
		printf("conectado com sucesso!\n");

		for (; op != 10;)
		{
			printf("1 - Cadastrar Contato");
			printf("\n2 - Buscar Contato");
			printf("\n3 -  Altearar Contato");
			printf("\n4 -  Excluir Contato");
			printf("\n5 - Sair do Programa");
			scanf("%i", &op);
			__fpurge(stdin);

			if (op == 1)
			{
				printf("1-Cadastrar estado\n2-Cadastrar cidade\n3-Cadastrar Endereco\n4- Cadastrar contato\n5-Cadastrar Telefone\n6-Cadastrar email\n");
				scanf("%i", &opcao);
				__fpurge(stdin);
				if (opcao == 1)
				{ // Cadastro estado

					printf("Nome de estado: ");
					gets(estado);
					__fpurge(stdin);
					printf("Codigo do estado: ");
					scanf("%i", &cod_estado);
					__fpurge(stdin);

					sprintf(str, "insert into Estado(cod_estado, estado) values(%i,\"%s\");", cod_estado, estado);

					printf("%s", str);

					mysql_query(&conexao, str);
				}

				else if (opcao == 2)
				{ //Cadastro cidade

					printf("Nome da cidade: ");
					gets(cidade);
					__fpurge(stdin);
					printf("Codigo da cidade: ");
					scanf("%i", &cod_cidade);
					__fpurge(stdin);
					sprintf(str, "insert into Cidade(cidade, cod_cidade) values('%s', %i);", cidade, cod_cidade);

					mysql_query(&conexao, str);
				}

				else if (opcao == 3)
				{

					printf("Nome da rua: ");
					gets(rua);
					__fpurge(stdin);

					printf("Nome do bairro: ");
					gets(bairro);
					__fpurge(stdin);

					printf("Numero da casa: ");
					scanf("%i", &numero);
					__fpurge(stdin);

					printf("Cep: ");
					scanf("%i", &cep);
					__fpurge(stdin);

					printf("Codigo do endereco: ");
					scanf("%i", &cod_endereco);
					__fpurge(stdin);

					sprintf(str, "insert into Endereco(rua, bairro, numero, cep, cod_endereco) values('%s', '%s', %i,%i,%i);", rua, bairro, numero, cep, cod_endereco);

					mysql_query(&conexao, str);
				}

				else if (opcao == 4)
				{

					printf("Nome: ");
					gets(nome);
					__fpurge(stdin);
					printf("Codigo de pessoa: ");
					scanf("%i", &cod_contato);
					__fpurge(stdin);

					sprintf(str, "insert into Contato(nome, cod_contato) values('%s', %i);", nome, cod_contato);

					mysql_query(&conexao, str);
				}

				else if (opcao == 5)
				{

					printf("Numero telefonico");
					scanf("%i", &telefone);
					__fpurge(stdin);
					printf("Codigo de telefone: ");
					scanf("%i", &cod_telefone);
					__fpurge(stdin);

					sprintf(str, "insert into Telefone(telefone, cod_telefone) values(%i, %i);", telefone, cod_telefone);

					mysql_query(&conexao, str);
				}

				else if (opcao == 6)
				{

					printf("Email");
					gets(enderecoemail);
					__fpurge(stdin);
					printf("Codigo de email: ");
					scanf("%i", &cod_email);
					__fpurge(stdin);

					sprintf(str, "insert into Email(enderecoemail, cod_email) values('%s', %i);", enderecoemail, cod_email);

					mysql_query(&conexao, str);
				}
			}

			else if (op == 2)
			{
				printf("Selecione um tipo de Busca");
				printf("1 - Nome");
				printf("\n2 - Email");
				printf("\n3 -  Endereco");
				printf("\n4 -  Voltar parao  Menu");
				scanf("%i", &opbusca);

				if (opbusca == 1)
				{ // NOME
					printf("Digite o nome: ");
					gets(nomebusca);
					sprintf(query, "Select * from Contato inner join Endereco inner join Contato_Endereco inner join Cidade inner join Estado inner join Email inner join Telefone where Contato.nome='%s'", nomebusca);
				}

				else if (opbusca == 2)
				{ //EMAIl
					printf("Digite o nome: ");
					gets(emailbusca);

					sprintf(query, "Select * from Contato inner join Endereco inner join Contato_Endereco inner join Cidade inner join Estado inner join Email inner join Telefone where Email.endereco='%s'", emailbusca);
				}

				else if (opbusca == 3)
				{ //ENDERECO
					printf("Digite o nome: ");
					gets(enderecobusca);
					sprintf(query, "Select * from Contato inner join Endereco inner join Contato_Endereco inner join Cidade inner join Estado inner join Email inner join Telefone where Endereco.rua='%s'", enderecobusca);
				}
				else if (opbusca == 4)
				{
					main();
				}

				if (mysql_query(&conexao, query))
					printf("Erro: %s\n", mysql_error(&conexao));
				else
				{
					resp = mysql_store_result(&conexao); //recebe a consulta
					if (resp)							 //se houver consulta
					{
						//passa os dados dos campos para a variável campos
						//escreve na tela os nomes dos campos dando
						//um tab somente
						campos = mysql_fetch_fields(resp);
						for (conta = 0; conta < mysql_num_fields(resp); conta++)
						{
							printf("%s", (campos[conta]).name);
							if (mysql_num_fields(resp) > 1)
								printf("\t");
						}

						printf("\n");

						//enquanto retonrnar registros, conta até o
						//número de colunas que a tabela tem e escreve na
						//tela com um tab, depois pula a linha e tenta
						//pegar outro registro
						while ((linhas = mysql_fetch_row(resp)) != NULL)
						{
							for (conta = 0; conta < mysql_num_fields(resp); conta++)
								printf("%s\t", linhas[conta]);
							printf("\n");
						}
					}
					mysql_free_result(resp); //limpa a variável do resultado: resp
				}
			}

			else if (op == 3)
			{ // ALTEARAR
				printf("Selecione uma opcao");
				printf("1 - Alterar Contato");
				printf("\n2 - Voltar parao  Menu");
				scanf("%i", &opalterar);

				if (opalterar == 1)
				{

					printf("\nDigite o codigo do contato a ser alterado: ");
					scanf("%i", &alterarcodigo);

					printf("\nDigite o novo nome do contato: ");
					gets(nomealterar);

					printf("\nCodigo de um endereco ja existente: ");
					scanf("%i", &enderecoalterar);

					sprintf(str, "UPDATE Contato SET nome = '%s' where codigocontato=%i;", nome, alterarcodigo);
					sprintf(str, "UPDATE Contato SET codigoendereco = %i where codigocontato=%i;", enderecoalterar, alterarcodigo);
				}

				else if (opalterar == 2)
				{
					main();
				}
			}

			else if (op == 4)
			{ // EXCLUIR
				printf("Selecione uma opcao");
				printf("1 - Excluir um contato");
				printf("\n2 - Voltar parao  Menu");
				scanf("%i", &opexcluir);

				if (opexcluir == 1)
				{
					printf("\nDigite o codigo do contato a ser excluido: ");
					scanf("%i", &excluircodigo);

					sprintf(str, "DELETE FROM Email where codigocontato=%i;", excluircodigo);
					mysql_query(&conexao, str);
					sprintf(str, "DELETE FROM Telefone where codigocontato=%i;", excluircodigo);
					mysql_query(&conexao, str);
					sprintf(str, "DELETE FROM Contato where codigocontato=%i;", excluircodigo);
					mysql_query(&conexao, str);
				}

				else if (opexcluir == 2)
				{
					main();
				}
			}
		}
	}
	else
	{
		printf("Falha de conexao\n");
		printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
	}
}