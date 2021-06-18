#include <bits/stdc++.h>
#define x 100
using namespace std;
FILE* cliArquivo = 0;
FILE* proArquivo = 0;
FILE* venArquivo = 0;
///////////////////////////////////
struct endereco
{
    char rua[x], cidade[x], estado[x];
    int numero;
};

struct data
{
    int dia, mes, ano;
};
struct produto
{
    int cod, quant;
    double preco;
    char descricao[x];
    struct produto *ant;
    struct produto *prox;
};
struct cliente
{
    char cpf[x], nome[x], telefone[x];
    struct endereco ender;
    struct data dat;
    struct cliente *ant;
    struct cliente *prox;
};

struct venda
{
    int quant;
    char *cpf_C;
    int *cod_P;
    struct  venda *ant;
    struct  venda *prox;
};

typedef struct venda noptr_venda;
typedef struct produto noptr_prod;
typedef struct cliente noptr_cli;
//////////////////////////////////////////////////////////////////////////////
void alterar_cliente (int op, noptr_cli **clientes, noptr_prod *produtos, noptr_venda *vendas);
void alterar_Produto (int op, noptr_cli *clientes, noptr_prod **produtos, noptr_venda *vendas);
void alterar_Venda (noptr_cli *clientes, noptr_prod **produtos, noptr_venda **vendas);
void cadastrarCliente(noptr_cli **inicio);
void cadastrarProduto(noptr_prod **inicio);
void cadastrarVenda(noptr_venda **inicio_v, noptr_prod **inicio_p, noptr_cli *inicio_c);
noptr_cli* cria_novoCliente(char cpf[], char nome[],int dia[], int mes[], int ano[], char telefone[], char rua[], int numero, char cidade[], char estado[]);
noptr_prod* cria_novoProduto(int codigo, double pre, int quantidade, char descri[]);
noptr_venda* cria_novoVenda(int quant, char *cpf, int *cod);
void insere_listaCliente(noptr_cli **inifunc, char cpf[], char nome[],int dia, int mes, int ano, char telefone[], char rua[], int numero, char cidade[], char estado[]);
void insere_listaProduto(noptr_prod **inifunc, int codigo, double pre, int quantidade, char descricao[]);
void insere_listaVenda(noptr_venda **inifunc, int quant, char *cpf, int *cod);
void remover_cliente(noptr_cli **inifunc, noptr_venda *vendas);
void remover_produtos(noptr_prod **produtos, noptr_venda *vendas);
void remover_venda(noptr_venda **inifunc, noptr_prod **produtos);
void consultar_cliente (int op, noptr_cli *clientes, noptr_prod *produtos, noptr_venda *vendas);
void consultar_Produto(int op, noptr_cli *clientes, noptr_prod *produtos, noptr_venda *vendas);
void consultar_venda (int op, noptr_venda *vendas);
int menu();
int menuClientes();
int menuClientesAlterar();
int menuClientesConsultar();
int menuProdutos();
int menuProdutosAlterar();
int menuProdutosConsultar();
int menuVendas();
int menuVendasAlterar();
int menuVendasConsultar();
void tirarespaco(char str[]);
void colocarespaco(char str[]);
void zera_str(char str[]);
void salvar(noptr_cli *clientes, noptr_prod *produtos, noptr_venda **vendas)
{
    cliente auxcv;
    produto auxpv;
    venda auxvv;
    noptr_cli *auxc = clientes;
    int cont1=0;
    if (auxc)
    {
        cont1++;
        while(auxc->prox)
        {
            auxc = auxc->prox;
            cont1++;
        }
    }
    cliArquivo = fopen("clientes.txt","r+");
    if (cliArquivo)
    {
        fclose(cliArquivo);
        remove("clientes.txt");
    }
    cliArquivo = fopen("clientes.txt","a+");
    auxc = clientes;
    fprintf(cliArquivo, "%d\n", cont1);
    while (auxc)
    {
        zera_str(auxcv.cpf);
        zera_str(auxcv.nome);
        zera_str(auxcv.telefone);
        zera_str(auxcv.ender.rua);
        zera_str(auxcv.ender.cidade);
        zera_str(auxcv.ender.estado);
        strcpy(auxcv.cpf,auxc->cpf);
        tirarespaco(auxcv.cpf);
        strcpy(auxcv.nome,auxc->nome);
        tirarespaco(auxcv.nome);
        strcpy(auxcv.telefone,auxc->telefone);
        tirarespaco(auxcv.telefone);
        auxcv.dat.dia=auxc->dat.dia;
        auxcv.dat.mes=auxc->dat.mes;
        auxcv.dat.ano=auxc->dat.ano;
        strcpy(auxcv.ender.rua,auxc->ender.rua);
        tirarespaco(auxcv.ender.rua);
        auxcv.ender.numero=auxc->ender.numero;
        strcpy(auxcv.ender.cidade,auxc->ender.cidade);
        tirarespaco(auxcv.ender.cidade);
        strcpy(auxcv.ender.estado,auxc->ender.estado);
        tirarespaco(auxcv.ender.estado);
        fprintf(cliArquivo, "%s %s %s %d %d %d %s %d %s %s\n", auxcv.cpf, auxcv.nome, auxcv.telefone, auxcv.dat.dia, auxcv.dat.mes, auxcv.dat.ano, auxcv.ender.rua, auxcv.ender.numero, auxcv.ender.cidade, auxcv.ender.estado);
        auxc=auxc->prox;
    }
    fclose(cliArquivo);
    ///////////
    noptr_prod *auxp = produtos;
    int cont2=0;
    if (auxp)
    {
        cont2++;
        while(auxp->prox)
        {
            auxp = auxp->prox;
            cont2++;
        }
    }
    proArquivo = fopen("produtos.txt","r+");
    if (proArquivo)
    {
        fclose(proArquivo);
        remove("produtos.txt");
    }
    proArquivo = fopen("produtos.txt","a+");
    auxp = produtos;
    fprintf(proArquivo, "%d\n", cont2);
    noptr_venda *auxv;
    while (auxp)
    {
        auxpv.cod=auxp->cod;
        zera_str(auxpv.descricao);
        strcpy(auxpv.descricao,auxp->descricao);
        tirarespaco(auxpv.descricao);
        auxpv.preco=auxp->preco;
        auxpv.quant=auxp->quant;
        auxv = *vendas;
        while (auxv)
        {
            if ((*auxv->cod_P)==auxpv.cod)
            {
                auxpv.quant+=auxv->quant;
            }
            auxv=auxv->prox;
        }
        fprintf(proArquivo, "%d %s %lf %d\n", auxpv.cod, auxpv.descricao, auxpv.preco, auxpv.quant);
        auxp=auxp->prox;
    }
    fclose(proArquivo);
    ///////////
    int cont3=0;
    auxv = *vendas;
    if (auxv)
    {
        cont3++;
        while(auxv->prox)
        {
            auxv = auxv->prox;
            cont3++;
        }
    }
    venArquivo = fopen("vendas.txt","r+");
    if (venArquivo)
    {
        fclose(venArquivo);
        remove("vendas.txt");
    }
    venArquivo = fopen("vendas.txt","a+");
    auxv = *vendas;
    fprintf(venArquivo, "%d\n", cont3);
    char cpf[x];
    zera_str(cpf);
    while (auxv)
    {
        auxvv.cod_P=auxv->cod_P;
        strcpy(cpf,auxv->cpf_C);
        tirarespaco(cpf);
        auxvv.quant=auxv->quant;
        fprintf(venArquivo, "%d %s %d\n", *auxvv.cod_P, cpf, auxvv.quant);
        auxv=auxv->prox;
    }
    fclose(venArquivo);
};
void recuperar(noptr_cli **clientes, noptr_prod **produtos, noptr_venda **vendas)
{
    cliente auxcv;
    int cont1, cont2, cont3, i;
    cliArquivo = fopen("clientes.txt","r+");
    if (cliArquivo==NULL)
    {
        cout<<"\nArquivo clientes.txt nao encontrado";
    }
    else
    {
        fscanf(cliArquivo, "%d", &cont1);
        i=0;
        while (i<cont1)
        {
            zera_str(auxcv.cpf);
            zera_str(auxcv.nome);
            zera_str(auxcv.telefone);
            zera_str(auxcv.ender.rua);
            zera_str(auxcv.ender.cidade);
            zera_str(auxcv.ender.estado);
            fscanf(cliArquivo, "%s %s %s %d %d %d %s %d %s %s", &auxcv.cpf[0], &auxcv.nome[0], &auxcv.telefone[0], &auxcv.dat.dia, &auxcv.dat.mes, &auxcv.dat.ano, &auxcv.ender.rua[0], &auxcv.ender.numero, &auxcv.ender.cidade[0], &auxcv.ender.estado[0]);
            colocarespaco(auxcv.nome);
            colocarespaco(auxcv.ender.rua);
            colocarespaco(auxcv.ender.cidade);
            colocarespaco(auxcv.ender.estado);
            insere_listaCliente(&(*clientes), auxcv.cpf, auxcv.nome,  auxcv.dat.dia, auxcv.dat.mes, auxcv.dat.ano, auxcv.telefone, auxcv.ender.rua, auxcv.ender.numero, auxcv.ender.cidade, auxcv.ender.estado);
            i++;
        }
    }
    fclose(cliArquivo);
    ///////////
    produto auxpv;
    proArquivo = fopen("produtos.txt","r+");
    if (proArquivo==NULL)
    {
        cout<<"\nArquivo produtos.txt nao encontrado";
    }
    else
    {
        fscanf(proArquivo, "%d", &cont2);
        i=0;
        while (i<cont2)
        {
            zera_str(auxpv.descricao);
            fscanf(proArquivo, "%d %s %lf %d", &auxpv.cod, &auxpv.descricao[0], &auxpv.preco, &auxpv.quant);
            colocarespaco(auxpv.descricao);
            insere_listaProduto(&(*produtos), auxpv.cod, auxpv.preco, auxpv.quant, auxpv.descricao);
            i++;
        }
    }
    fclose(proArquivo);
    ///////////
    venArquivo = fopen("vendas.txt","r+");
    if (venArquivo==NULL)
    {
        cout<<"\nArquivo vendas.txt nao encontrado";
    }
    else
    {
        fscanf(venArquivo, "%d", &cont3);
        i=0;
        int cod;
        char cpf[x];
        venda a;
        noptr_cli *c;
        noptr_prod *p;
        while (i<cont3)
        {
            c = *clientes;
            zera_str(cpf);
            fscanf(venArquivo, "%d %s %d",&cod, cpf, &a.quant);
            if (c)
            {
                while(c->prox && strcmp(c->cpf, cpf)==1)
                {
                    c = c->prox;
                }
                if (strcmp(c->cpf,cpf)==0)
                    a.cpf_C=c->cpf;
            }
            p = *produtos;
            if (p)
            {
                while(p->prox && p->cod < cod)
                {
                    p = p->prox;
                }
                if (p->cod == cod)
                {
                    a.cod_P=&(p->cod);
                }
                if(p->quant >= a.quant)
                {
                    p->quant-=a.quant;
                }
            }
            insere_listaVenda(&(*vendas), a.quant, a.cpf_C, a.cod_P);
            i++;
        }
    }
    fclose(venArquivo);
};
//////////////////////////////////////////////////////////////////////////////

int main()
{
    int op, op1, op2, op3, op4, op5, op6, op7, op9;
    noptr_cli *clientes = NULL;
    noptr_prod *produtos = NULL;
    noptr_venda *vendas = NULL;
    cout<<"Digite 1 para recuperar: ";
    cin>>op;
    if (op==1)
        recuperar(&clientes, &produtos, &vendas);
    do
    {
        op = menu();
        switch(op)
        {
        case 1:
            system("cls");
            do
            {
                op1 = menuClientes();
                switch(op1)
                {
                case 1:
                    system("cls");
                    cadastrarCliente(&clientes);
                    break;
                case 2:
                    system("cls");
                    remover_cliente(&clientes, vendas);
                    break;
                case 3:
                    system("cls");
                    do
                    {
                        op2 = menuClientesAlterar();
                        alterar_cliente(op2, &clientes, produtos, vendas);
                    }
                    while(op2 != 0);
                    break;
                case 4:
                    system("cls");
                    do
                    {
                        op3 = menuClientesConsultar();
                        consultar_cliente(op3, clientes, produtos, vendas);
                    }
                    while(op3 != 0);
                    break;
                }
            }
            while(op1!=0);
            break;

        case 2:
            system("cls");
            do
            {
                op4 = menuProdutos();
                switch(op4)
                {
                case 1:
                    system("cls");
                    cadastrarProduto(&produtos);
                    break;
                case 2:
                    system("cls");
                    remover_produtos(&produtos, vendas);
                    break;
                case 3:
                    system("cls");
                    do
                    {
                        op5 = menuProdutosAlterar();
                        alterar_Produto(op5, clientes, &produtos, vendas);
                    }
                    while(op5 != 0);
                    break;
                case 4:
                    system("cls");
                    do
                    {
                        op6 = menuProdutosConsultar();
                        consultar_Produto(op6, clientes, produtos, vendas);
                    }
                    while(op6 != 0);
                    break;
                }
            }
            while(op4!=0);
            break;
        case 3:
            system("cls");
            do
            {
                op7 = menuVendas();
                switch(op7)
                {
                case 1:
                    system("cls");
                    cadastrarVenda(&vendas, &produtos, clientes);
                    break;
                case 2:
                    system("cls");
                    remover_venda(&vendas, &produtos);
                    break;
                case 3:
                    system("cls");
                    alterar_Venda (clientes, &produtos, &vendas);
                    break;
                case 4:
                    system("cls");
                    do
                    {
                        op9 = menuVendasConsultar();
                        consultar_venda(op9, vendas);
                    }
                    while(op9 != 0);
                    break;
                }
            }
            while(op7 != 0);
            break;
        }
    }
    while(op!=0);
    salvar(clientes, produtos, &vendas);
    return 0;
}

void alterar_cliente (int op, noptr_cli **clientes, noptr_prod *produtos, noptr_venda *vendas)
{
    noptr_cli *p;
    switch (op)
    {
    case 1:
    {
        char cpf[x];
        cout<<"\nDigite o cpf:  ";
        setbuf(stdin, NULL);
        gets(cpf);
        p = *clientes;
        if (p)
        {
            while(p->prox && strcmp(cpf,p->cpf)==1)
            {
                p = p->prox;
            }
            if(strcmp(p->cpf,cpf)!=0)
                cout<<"\nCliente nao encontrado!";
            else
            {
                system ("cls");
                cout<<"\nDigite o novo nome: ";
                setbuf(stdin, NULL);
                gets(p->nome);
                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 2:
    {
        char cpf[x];
        int erro;
        cout<<"\nDigite o cpf:  ";
        setbuf(stdin, NULL);
        gets(cpf);
        p = *clientes;
        if (p)
        {
            while(p->prox && strcmp(p->cpf,cpf)==1)
            {
                p = p->prox;
            }
            if(strcmp(p->cpf,cpf)!=0)
                cout<<"\nCliente nao encontrado!";
            else
            {
                system ("cls");
                cout<<"\nNova data de Nascimento: DD/MM/YYYY\n";

                //Verifica se o dia esta entre 1 e 30
                do
                {
                    setbuf(stdin, NULL);
                    cin>>p->dat.dia;
                    if (p->dat.dia<1||p->dat.dia>30)
                    {
                        erro=1;
                        cout<<"\nDia invalido! Tente de novo: ";
                    }
                    else
                    {
                        erro=0;
                        system("cls");
                        cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<p->dat.dia<<"/";
                    }
                }
                while (erro==1);
                //------------------------------------


                //Verifica se o mês esta entre 1 e 12
                do
                {
                    setbuf(stdin, NULL);
                    cin>>p->dat.mes;
                    if (p->dat.mes<1||p->dat.mes>12)
                    {
                        erro=1;
                        cout<<"\nMes invalido! Tente de novo: ";
                        cout<<p->dat.dia<<"/";
                    }
                    else
                    {
                        erro=0;
                        system("cls");
                        cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<p->dat.dia<<"/"<<p->dat.mes<<"/";
                    }
                }
                while (erro==1);
                //------------------------------------


                //Verifica se o ano esta entre 1850 e 2019
                do
                {
                    setbuf(stdin, NULL);
                    cin>>p->dat.ano;
                    if (p->dat.ano<1850||p->dat.ano>2019)
                    {
                        erro=1;
                        cout<<"\nAno invalido! Tente de novo: ";
                        cout<<p->dat.dia<<"/"<<p->dat.mes<<"/";
                    }
                    else
                    {
                        erro=0;
                        system("cls");
                        cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<p->dat.dia<<"/"<<p->dat.mes<<"/"<<p->dat.ano;
                    }
                }
                while (erro==1);
                //------------------------------------

            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 3:
    {

        char cpf[x];
        cout<<"\nDigite o cpf:  ";
        setbuf(stdin, NULL);
        gets(cpf);
        p = *clientes;
        if (p)
        {
            while(p->prox && strcmp(p->cpf,cpf)==1)
            {
                p = p->prox;
            }
            if(strcmp(p->cpf,cpf)!=0)
                cout<<"\nCliente nao encontrado!";
            else
            {
                system ("cls");
                cout<<"\nNovo endereco: ";
                cout<<"\nDigite a rua: ";
                setbuf(stdin, NULL);
                gets(p->ender.rua);

                cout<<"\nDigite o numero: ";
                cin>>p->ender.numero;

                cout<<"\nDigite a cidade: ";
                setbuf(stdin, NULL);
                gets(p->ender.cidade);

                cout<<"\nDigite o estado: ";
                setbuf(stdin, NULL);
                gets(p->ender.estado);

            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 4:
    {

        char cpf[x];
        cout<<"\nDigite o cpf:  ";
        setbuf(stdin, NULL);
        gets(cpf);
        p = *clientes;
        if (p)
        {
            while(p->prox && strcmp(p->cpf,cpf)==1)
            {
                p = p->prox;
            }
            if(strcmp(p->cpf,cpf)!=0)
                cout<<"\nCliente nao encontrado!";
            else
            {
                system ("cls");

                cout<<"\nDigite o novo telefone: ";
                setbuf(stdin, NULL);
                gets(p->telefone);
                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    }
}

void alterar_Produto (int op, noptr_cli *clientes, noptr_prod **produtos, noptr_venda *vendas)
{
    noptr_prod *p;
    switch (op)
    {
    case 1:
    {
        int cod;
        cout<<"\nDigite o codigo:  ";
        cin>>cod;
        p = *produtos;
        if (p)
        {
            while(p->prox && p->cod < cod)
            {
                p = p->prox;
            }
            if(p->cod != cod)
                cout<<"\nProduto nao encontrado!";
            else
            {
                system ("cls");
                cout<<"\nDigite a nova decricao: ";
                setbuf(stdin, NULL);
                gets(p->descricao);

                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 2:
    {
        int cod;
        cout<<"\nDigite o codigo:  ";
        cin>>cod;
        p = *produtos;
        if (p)
        {
            while(p->prox && p->cod < cod)
            {
                p = p->prox;
            }
            if(p->cod != cod)
                cout<<"\nProduto nao encontrado!";
            else
            {
                system ("cls");

                cout<<"\nDigite a nova quantidade estocada: ";
                cin>>p->quant;
                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";

    }
    break;
    case 3:
    {

        int cod;
        cout<<"\nDigite o codigo:  ";
        cin>>cod;
        p = *produtos;
        if (p)
        {
            while(p->prox && p->cod < cod)
            {
                p = p->prox;
            }
            if(p->cod != cod)
                cout<<"\nProduto nao encontrado!";
            else
            {
                system ("cls");

                cout<<"\nDigite o novo preco: ";
                scanf("%lf",&p->preco);
                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    }
}

void alterar_Venda (noptr_cli *clientes, noptr_prod **produtos, noptr_venda **vendas)
{
    noptr_venda *v ;
    noptr_prod *p, *p1;
    int cod, flag = 0;
    char cpf[x];
    cout<<"\nDigite o cpf da venda:  ";
    setbuf(stdin, NULL);
    gets(cpf);
    v = *vendas;
    while(v && v->prox && strcmp(v->cpf_C,cpf)==1)
    {
        v = v->prox;
    }
    if (v)
    {
        if(strcmp(v->cpf_C,cpf)!=0)
        {
            cout<<"\nCliente ainda nao realizou uma venda!";
        }
        else
        {
            cout<<"\nDigite o codigo do produto que sera alterado:  ";
            cin>>cod;
            v = *vendas;
            if (v)
            {
                while(v->prox && cod > *v->cod_P)
                {
                    v = v->prox;
                }
                if(*v->cod_P != cod)
                {
                    flag = 1;
                    cout<<"\nVenda nao encontrada!";
                }
                else
                {
                    p1 = *produtos;
                    if (p1)//manda a quantidade do produto q vai ser alterada para o produto
                    {
                        while(p1->prox && p1->cod < cod)
                        {
                            p1 = p1->prox;
                        }
                        if (p1->cod != cod)
                        {
                            flag = 1;
                            cout<<"\nCodigo invalido!!\n";
                        }
                        else
                        {
                            p1->quant += v->quant;
                        }
                        if(flag == 1)
                            cout<<"\nDigite novamente!!\n";
                    }
                    else
                    {
                        cout<<"Lista de produtos vazia!";
                        return;
                    }

                    p = *produtos;
                    cout<<"\nDigite o codigo do produto desejado: ";
                    cin>>cod;
                    if (p)
                    {
                        while(p->prox && p->cod < cod)
                        {
                            p = p->prox;
                        }
                        if (p->cod != cod)
                        {
                            flag = 1;
                            cout<<"\nCodigo invalido!!\n";
                        }
                        else
                        {
                            v->cod_P=&(p->cod);
                            cout<<"\nDigite a quantidade desejada: ";
                            int quant;
                            cin>>quant;
                            if(p->quant < quant)
                            {
                                flag = 1;
                                cout<<"\nNao possui a quantidade desejada: \n";
                            }
                            else
                            {
                                v->quant=quant;
                                p->quant -= v->quant;
                            }
                        }
                        if(flag == 1)
                            cout<<"\nDigite novamente!!\n";
                    }
                    else
                    {
                        cout<<"\nLista de produtos vazia!";
                        return;
                    }
                    v = v->prox;
                }
            }
        }
    }
    else
        cout<<"\nNao existem vendas cadastradas!";
}
void cadastrarCliente(noptr_cli **inicio)
{
    struct cliente a;
    int erro;
    cout<<"\nDigite o cpf:  ";
    setbuf(stdin, NULL);
    gets(a.cpf);
    noptr_cli *p = *inicio;
    if (p)
    {
        while(p->prox && strcmp(a.cpf,p->cpf)==1)
        {
            p = p->prox;
        }
        if(strcmp(p->cpf,a.cpf)!=0)
            erro=0;
        else
        {
            erro=1;
            system ("cls");
            cout<<"CPF ja cadastrado!";
        }
    }
    else
        erro=0;
    if (erro!=1)
    {
        cout<<"\nDigite o nome: ";
        setbuf(stdin, NULL);
        gets(a.nome);
        cout<<"\nData de Nascimento: DD/MM/YYYY\n";

        //Verifica se o dia esta entre 1 e 30
        do
        {
            setbuf(stdin, NULL);
            cin>>a.dat.dia;
            if (a.dat.dia<1||a.dat.dia>30)
            {
                erro=1;
                cout<<"\nDia invalido! Tente de novo: ";
            }
            else
            {
                erro=0;
                system("cls");
                cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<a.dat.dia<<"/";
            }
        }
        while (erro==1);
        //------------------------------------


        //Verifica se o mês esta entre 1 e 12
        do
        {
            setbuf(stdin, NULL);
            cin>>a.dat.mes;
            if (a.dat.mes<1||a.dat.mes>12)
            {
                erro=1;
                cout<<"\nMes invalido! Tente de novo: ";
                cout<<a.dat.dia<<"/";
            }
            else
            {
                erro=0;
                system("cls");
                cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<a.dat.dia<<"/"<<a.dat.mes<<"/";
            }
        }
        while (erro==1);
        //------------------------------------


        //Verifica se o ano esta entre 1850 e 2019
        do
        {
            setbuf(stdin, NULL);
            cin>>a.dat.ano;
            if (a.dat.ano<1850||a.dat.ano>2019)
            {
                erro=1;
                cout<<"\nAno invalido! Tente de novo: ";
                cout<<a.dat.dia<<"/"<<a.dat.mes<<"/";
            }
            else
            {
                erro=0;
                system("cls");
                cout<<"\nData de Nascimento: DD/MM/YYYY\n"<<a.dat.dia<<"/"<<a.dat.mes<<"/"<<a.dat.ano;
            }
        }
        while (erro==1);
        //------------------------------------

        cout<<"\nDigite o telefone: ";
        setbuf(stdin, NULL);
        gets(a.telefone);

        cout<<"\nEndereco: ";
        cout<<"\nDigite a rua: ";
        setbuf(stdin, NULL);
        gets(a.ender.rua);

        cout<<"\nDigite o numero: ";
        cin>>a.ender.numero;

        cout<<"\nDigite a cidade: ";
        setbuf(stdin, NULL);
        gets(a.ender.cidade);

        cout<<"\nDigite o estado: ";
        setbuf(stdin, NULL);
        gets(a.ender.estado);
        insere_listaCliente(&(*inicio), a.cpf, a.nome, a.dat.dia, a.dat.mes, a.dat.ano, a.telefone, a.ender.rua, a.ender.numero, a.ender.cidade, a.ender.estado);
    }
}
void cadastrarProduto(noptr_prod **inicio)
{
    struct produto a;
    int erro=0;
    cout<<"\nDigite o codigo do produto: ";
    cin>>a.cod;
    noptr_prod *p = *inicio;
    if (p)
    {
        while(p->prox && p->cod < a.cod && erro == 0)
        {
            if(p->cod != a.cod)
                erro=0;
            else
                erro=1;
            if (erro==0)
                p = p->prox;
        }
        if(p->cod != a.cod)
            erro=0;
        else
            erro=1;
    }
    else
        erro=0;
    if (erro!=1)
    {
        cout<<"\nDigite a descricao: ";
        setbuf(stdin, NULL);
        gets(a.descricao);

        cout<<"\nDigite o preco: ";
        scanf("%lf",&a.preco);

        cout<<"\nDigite a quantidade estocada: ";
        cin>>a.quant;
        insere_listaProduto(&(*inicio), a.cod, a.preco, a.quant, a.descricao);
    }
    else
        cout<<"Produto ja cadastrado";
}
void cadastrarVenda(noptr_venda **inicio_v, noptr_prod **inicio_p, noptr_cli *inicio_c)
{
    struct venda a;
    noptr_cli *c;
    noptr_prod *p;
    char cpf[x];
    int cod;
    c = inicio_c;
    p = *inicio_p;
    cout<<"\nDigite o cpf: ";
    setbuf(stdin, NULL);
    gets(cpf);
    if (c)
    {
        while(c->prox && strcmp(cpf, c->cpf)==1)
        {
            c = c->prox;
        }
        if (strcmp(c->cpf,cpf)!=0)
        {
            cout<<"\nCliente invalido!!\n";
            return;
        }
        else
            a.cpf_C=c->cpf;
    }
    else
    {
        cout<<"Lista de clientes vazia!";
        return;
    }
    cout<<"\nDigite o codigo do produto: ";
    cin>>cod;
    if (p)
    {
        while(p->prox && p->cod < cod)
        {
            p = p->prox;
        }
        if (p->cod != cod)
        {
            cout<<"\nCodigo invalido!!\n";
        }
        else
        {
            a.cod_P=&(p->cod);
            cout<<"\nDigite a quantidade desejada: ";
            cin>>a.quant;
            if(p->quant < a.quant || a.quant <= 0)
            {
                cout<<"\nQuantidade invalida!!\n";
            }
            else
            {
                noptr_venda *v = *inicio_v;
                while (v && strcmp(a.cpf_C, v->cpf_C)==1&& a.cod_P>v->cod_P)
                {
                    v=v->prox;
                }
                if (v && strcmp(a.cpf_C, v->cpf_C)==0&& *a.cod_P==*v->cod_P)
                {
                    v->quant+=a.quant;
                    p->quant-=a.quant;
                }
                else
                {
                    p->quant-=a.quant;
                    insere_listaVenda(&(*inicio_v), a.quant, a.cpf_C, a.cod_P);
                }
            }
        }
    }
    else
    {
        cout<<"Lista de produtos vazia!";
        return;
    }
}
noptr_prod* cria_novoProduto(int codigo, double pre, int quantidade, char descri[])
{
    noptr_prod *novo;
    novo=(struct produto *) malloc(sizeof(noptr_prod));
    if(!novo)
    {
        printf("\nSem Memoria!!!");
        exit(0);
    }
    novo->cod = codigo;
    novo->preco = pre;
    novo->quant = quantidade;
    strcpy(novo->descricao,descri);
    novo->prox = NULL;
    novo->ant= NULL;
    return novo;
}
noptr_cli* cria_novoCliente(char cpf[], char nome[],int dia, int mes, int ano, char telefone[], char rua[], int numero, char cidade[], char estado[])
{
    noptr_cli *novo;
    novo=(struct cliente *) malloc(sizeof(noptr_cli));
    if(!novo)
    {
        printf("\nSem Memoria!!!");
        exit(0);
    }
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    novo->dat.dia = dia;
    novo->dat.mes = mes;
    novo->dat.ano = ano;
    strcpy(novo->telefone, telefone);
    strcpy(novo->ender.rua, rua);
    novo->ender.numero = numero;
    strcpy(novo->ender.cidade, cidade);
    strcpy(novo->ender.estado,estado);
    novo->prox = NULL;
    novo->ant= NULL;

    return novo;
}
noptr_venda* cria_novoVenda(int quant, char *cpf, int *cod)
{
    noptr_venda *novo;
    novo=(struct venda *) malloc(sizeof(noptr_venda));
    if(!novo)
    {
        printf("\nSem Memoria!!!");
        exit(0);
    }
    novo->cod_P=cod;
    novo->cpf_C=cpf;
    novo->quant=quant;
    novo->prox = NULL;
    novo->ant= NULL;
    return novo;
}
void insere_listaCliente(noptr_cli **inifunc, char cpf[], char nome[],int dia, int mes, int ano, char telefone[], char rua[], int numero, char cidade[], char estado[])
{
    if(*inifunc==NULL)
    {
        *inifunc = cria_novoCliente(cpf,nome,dia,mes,ano,telefone,rua,numero,cidade,estado);
    }
    else
    {
        noptr_cli *novo, *p = *inifunc;
        novo = cria_novoCliente(cpf,nome,dia,mes,ano,telefone,rua,numero,cidade,estado);
        while(p->prox && strcmp(cpf,p->cpf)==1)
        {
            p = p->prox;
        }
        if(p == *inifunc && strcmp(p->cpf, cpf)==1)//o cod eh menor q todos
        {
            p->ant = novo;
            novo->prox = p;
            *inifunc = novo;
        }
        else if(!p->prox && strcmp(p->cpf, cpf)==-1)//o cod eh maior que todos da lista
        {
            p->prox = novo;
            novo->ant = p;
        }
        else//o cod vai entrar no meio da lista
        {
            novo->ant = p->ant;
            novo->prox = p;
            p->ant = novo;
            novo->ant->prox = novo;
        }

    }
}
void insere_listaProduto(noptr_prod **inifunc, int codigo, double pre, int quantidade, char descricao[])
{
    if(*inifunc==NULL)
    {
        *inifunc = cria_novoProduto(codigo,pre,quantidade,descricao);
    }
    else
    {
        noptr_prod *p = *inifunc, *novo;
        while(p->prox && codigo > p->cod)
        {
            p = p->prox;
        }
        if(p)
        {
            if(p->cod != codigo)
            {
                novo = cria_novoProduto(codigo,pre,quantidade,descricao);
                if(p == *inifunc && p->cod > codigo)//o cod eh menor q todos
                {
                    p->ant = novo;
                    novo->prox = p;
                    *inifunc = novo;
                }
                else if(!p->prox && p->cod < codigo)//o cod eh maior que todos da lista
                {
                    p->prox = novo;
                    novo->ant = p;
                }
                else//o cod vai entrar no meio da lista
                {
                    novo->ant = p->ant;
                    novo->prox = p;
                    p->ant = novo;
                    novo->ant->prox = novo;
                }
            }
        }
        else
        {
            cout<<"Produto ja castrado! ";
        }
    }
}
void insere_listaVenda(noptr_venda **inifunc, int quant, char *cpf, int *cod)
{
    if(*inifunc==NULL)
    {
        *inifunc = cria_novoVenda(quant, cpf, cod);
    }
    else
    {
        noptr_venda *p = *inifunc;
        while(p->prox && cod > p->cod_P)
        {
            p = p->prox;
        }
        if(p)
        {

            noptr_venda *novo = cria_novoVenda(quant, cpf, cod);
            p = *inifunc;
            while(p->prox && strcmp(cpf,p->cpf_C)==1)
            {
                p = p->prox;
            }
            if(p == *inifunc && strcmp(p->cpf_C, cpf)==1)//o cod eh menor q todos
            {
                p->ant = novo;
                novo->prox = p;
                *inifunc = novo;
            }
            else if(!p->prox && strcmp(p->cpf_C, cpf)==-1)//o cod eh maior que todos da lista
            {
                p->prox = novo;
                novo->ant = p;
            }
            else//o cod vai entrar no meio da lista
            {
                if (p->prox && p->ant)
                {
                    novo->ant = p->ant;
                    novo->prox = p;
                    p->ant = novo;
                    novo->ant->prox = novo;
                }
                else
                {
                    p->ant = novo;
                    novo->prox = p;
                    *inifunc = novo;
                }
            }
        }
    };
}
void remover_cliente(noptr_cli **inifunc, noptr_venda *vendas)
{
    if (*inifunc==NULL)
    {
        cout<<"Lista vazia!";
        return;
    }
    else
    {
        char cpf[x];
        cout<<"Insira um CPF para remover: ";
        setbuf(stdin, NULL);
        gets(cpf);
        noptr_venda *v = vendas;
        while (v && v->prox && strcmp(v->cpf_C, cpf)==1)
        {
            v = v->prox;
        }
        if (v)
        {
            if(strcmp(v->cpf_C, cpf)==0)
            {
                cout<<"\nCPF cadastrado em uma venda!\nNao foi possivel remover!\n";
                return;
            }
        }
        noptr_cli *p = *inifunc, *ant;
        while (p && p->prox && (strcmp(p->cpf, cpf)!= 0) && (strcmp(p->cpf, cpf)!= 1))
        {
            ant=p;
            p=p->prox;
        }
        if (strcmp(p->cpf, cpf) == 0)
        {
            if (p && p->ant) //retira do fim/meio
            {
                ant->prox=p->prox;
                system("cls");
                printf ("%s removido!\n", cpf);
                free(p);
                if (ant->prox) //se tiver no meio ele faz isso
                {
                    p=ant->prox;
                    p->ant=ant;
                }
            }
            else if (p && !p->ant) //retira do inicio
            {
                *inifunc=p->prox;
                free(p);
                p=*inifunc;
                if (p)
                {
                    p->ant=NULL;
                }
                system("cls");
                printf ("%s removido!\n", cpf);
            }
        }
        else
        {
            system("cls");
            printf ("%s nao encontrado!\n", cpf);
        }
    }
}

void remover_produtos(noptr_prod **produtos, noptr_venda *vendas)
{
    noptr_prod *p;
    p = *produtos;
    if(*produtos==NULL)
    {
        printf("\nLista Vazia!!!");
    }
    else
    {
        int cod1;
        cout<<"___________________\n";
        cout<<"Digite o codigo do produto a ser removido: ";
        cin>>cod1;
        noptr_venda *v = vendas;
        while (v && *v->cod_P!=cod1)
        {
            v=v->prox;
        }
        if (v && *v->cod_P==cod1)
        {
            cout<<"\nProduto cadastrado em uma venda!";
        }
        else
        {
            while(p && p->cod != cod1)
            {
                p = p->prox;
            }
            if(p)
            {
                if(!p->ant && !p->prox)
                {
                    *produtos = NULL;
                }
                else if(!p->ant)
                {
                    *produtos = p->prox;
                    p->prox->ant = NULL;
                }
                else if(!p->prox)
                {
                    p->ant->prox = NULL;
                }
                else
                {
                    p->prox->ant = p->ant;
                    p->ant->prox = p->prox;
                }
                free(p);
                cout<<"Produto removido!";
            }
            else
                cout<<"\nNao possui esse produto no cadastro!!\n";
        }
    }
}

void remover_venda(noptr_venda **inifunc, noptr_prod **produtos)
{
    noptr_prod *p1 = *produtos;
    if (*inifunc==NULL)
    {
        cout<<"Lista vazia!";
        return;
    }
    else
    {
        char cpf[x];
        int cod, flag=0;
        cout<<"Insira um CPF e um codigo:\nCPF: ";
        setbuf(stdin, NULL);
        gets(cpf);
        cout<<"Codigo: ";
        cin>>cod;
        noptr_venda *v = *inifunc;
        while (v && flag==0)
        {
            if (strcmp(cpf, v->cpf_C)==0 && *v->cod_P == cod)
                flag=1;
            if (flag!=1)
                v = v->prox;
        }
        if (v)
        {
            if(strcmp(v->cpf_C, cpf)==0)
            {
                noptr_venda *ant=NULL; //SÓ DEFINO PRA NULL PRA TIRAR UM WARNING DE DESINICIALIZADO DO COMPILADOR
                do
                {
                    if (*v->cod_P==cod)
                    {
                        if (p1)
                        {

                            while(p1->prox && p1->cod < cod)
                            {
                                p1 = p1->prox;
                            }
                            if (p1->cod == cod)
                            {
                                p1->quant += v->quant;
                            }
                        }
                        if (v && v->ant && v->prox)
                        {
                            ant->prox=v->prox;
                            system("cls");
                            printf ("Venda com CPF: %s Codigo: %d foi removida!\n", cpf, cod);
                            free(v);
                            if (ant->prox) //se tiver no meio ele faz isso
                            {
                                v=ant->prox;
                                v->ant=ant;
                            }
                            return;
                        }
                        else if (v && v->ant && !v->prox)
                        {
                            v->ant->prox=NULL;
                            free(v);
                            printf ("Venda com CPF: %s Codigo: %d foi removida!\n", cpf, cod);
                            return;
                        }
                        else if (v && !v->ant) //retira do inicio
                        {
                            *inifunc=v->prox;
                            free(v);
                            v=*inifunc;
                            if (v)
                            {
                                (v)->ant=NULL;
                            }
                            system("cls");
                            printf ("Venda com CPF: %s Codigo: %d foi removida!\n", cpf, cod);
                            return;
                        }
                    }
                    else if (v->prox)
                    {
                        if(strcmp(v->prox->cpf_C, cpf)==0)
                        {
                            flag=1;
                            v=v->prox;
                        }
                        else
                            flag=0;
                    }
                }
                while (flag==1);
                system("cls");
                cout<<"Venda nao encontrada!";
                return;
            }
        }
        else
        {
            system("cls");
            cout<<"Venda nao encontrada!";
            return;
        }
    }
}
void consultar_cliente (int op, noptr_cli *clientes, noptr_prod *produtos, noptr_venda *vendas)
{
    noptr_cli *p;
    int cont;
    switch (op)
    {
    case 1:
    {
        if(clientes==NULL)
        {
            printf("\nLista Vazia!!!");
            return;
        }
        p = clientes;
        cout<<"\n_____________\n";
        cout<<"\tClientes:";
        cout<<"\n_____________\n";
        while(p)
        {
            cout<<"\nCPF: ";
            puts(p->cpf);
            cout<<"Nome: ";
            puts(p->nome);
            cout<<"Data de nascimento: "<<p->dat.dia<<"/"<<p->dat.mes<<"/"<<p->dat.ano<<endl;
            cout<<"\nTelefone: ";
            puts(p->telefone);
            cout<<"Rua: ";
            puts(p->ender.rua);
            cout<<"Numero: "<<p->ender.numero<<endl;
            cout<<"\nCidade: ";
            puts(p->ender.cidade);
            cout<<"Estado: ";
            puts(p->ender.estado);
            cout<<"\n_____________\n";
            p = p->prox;
        }
    }
    break;
    case 2:
    {
        char cpf[x];
        cout<<"\nDigite o cpf:  ";
        setbuf(stdin, NULL);
        gets(cpf);
        p = clientes;
        if (p)
        {
            while(p->prox && strcmp(cpf, p->cpf)==1)
            {
                p = p->prox;
            }
            if(strcmp(p->cpf,cpf)!=0)
                cout<<"\nCliente nao encontrado!";
            else
            {
                system ("cls");
                cout<<"\nCPF: ";
                puts(p->cpf);
                cout<<"\nNome: ";
                puts(p->nome);
                cout<<"\nData de nascimento: "<<p->dat.dia<<"/"<<p->dat.mes<<"/"<<p->dat.ano;
                cout<<"\nTelefone: ";
                puts(p->telefone);
                cout<<"\nRua: ";
                puts(p->ender.rua);
                cout<<"\nNumero: "<<p->ender.numero;
                cout<<"\nCidade: ";
                puts(p->ender.cidade);
                cout<<"\nEstado: ";
                puts(p->ender.estado);
                cout<<"\n_____________\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 3:
    {
        noptr_cli *p = clientes;
        cont=0;
        if (p)
        {
            while(p->prox)
            {
                p = p->prox;
                cont++;
            }
            cont++;
            printf("Existem atualmente %d clientes cadastrados!", cont);
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 4:
    {
        noptr_venda *v = vendas;
        noptr_prod *p;
        cont=0;
        float valor;
        cout<<"Informe um valor: ";
        scanf("%f", &valor);
        if (v)
        {
            noptr_cli *c = clientes;
            float acm;
            while(c)
            {
                v = vendas;
                acm=0;
                while (v)
                {
                    if (strcmp(v->cpf_C, c->cpf)==0)
                    {
                        p=produtos;
                        while (p && *v->cod_P != p->cod)
                        {
                            p=p->prox;
                        }
                        if (*v->cod_P == p->cod)
                        {
                            acm+=((v->quant) * (p->preco));
                        }
                    }
                    v=v->prox;
                }
                c=c->prox;
                if (acm>valor)
                    cont++;
            }
            printf("Existem atualmente %d clientes que compraram acima de %.2f!", cont, valor);
        }
        else
            cout<<"\nLista Vazia!";
        if (cont==0)
            cout<<"\nNao existem clientes que compraram acima de "<< valor;
    }
    break;

    }
}

void consultar_Produto(int op, noptr_cli *clientes, noptr_prod *produtos, noptr_venda *vendas)
{
    noptr_prod *p;
    switch (op)
    {
    case 1:
    {
        if(produtos==NULL)
        {
            printf("\nLista Vazia!!!");
            return;
        }
        p = produtos;
        cout<<"\n_____\n";
        cout<<"\tProdutos:";
        cout<<"\n_____\n";
        while(p)
        {
            printf("\nCodigo: %d\n", p->cod);
            printf("Preco: %.2lf\n",p->preco);
            printf("Quantidade: %d\n", p->quant);
            cout<<"Descricao: ";
            puts(p->descricao);
            cout<<"\n_____\n";
            p = p->prox;
        }
    }
    break;
    case 2:
    {
        int cod;
        cout<<"\nDigite o codigo:  ";
        cin>>cod;
        p = produtos;
        if (p)
        {
            while(p->prox && p->cod < cod)
            {
                p = p->prox;
            }
            if(p->cod != cod)
                cout<<"\nProduto nao encontrado!";
            else
            {
                system ("cls");
                printf("\nCodigo: %d\n", p->cod);
                printf("Preco: %.2lf\n",p->preco);
                printf("Quantidade: %d\n", p->quant);
                cout<<"Descricao: ";
                puts(p->descricao);
                cout<<"\n_____\n";
            }
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 3:
    {
        noptr_prod *p = produtos;
        int cont=0;
        if (p)
        {
            while(p->prox)
            {
                p = p->prox;
                cont++;
            }
            cont++;
            printf("Existem atualmente %d produtos cadastrados!", cont);
        }
        else
            cout<<"\nLista Vazia!";
    }
    break;
    case 4:
    {
        noptr_prod *produt = produtos;
        noptr_prod *p;
        int cont=0;
        int valor;
        cout<<"Informe uma quantidade: ";
        scanf("%d", &valor);
        if (produt)
        {
            p = produtos;
            while(p)
            {
                if (p->quant < valor)
                {
                    cont++;
                    printf("\nCodigo: %d\n", p->cod);
                    printf("Preco: %.2lf\n",p->preco);
                    printf("Quantidade: %d\n", p->quant);
                    cout<<"Descricao: ";
                    puts(p->descricao);
                    cout<<"\n_____\n";
                }
                p = p->prox;
            }
            if (cont!=0)
                printf("\n\nExistem atualmente %d produtos que estam abaixo de %d no estoque!", cont, valor);
        }
        else
            cout<<"\nLista Vazia!";
        if (cont==0)
            cout<<"\nNao existem produtos abaixo de "<< valor;
    }
    break;

    }
}

void consultar_venda (int op, noptr_venda *vendas)
{
    switch (op)
    {
    case 1:
    {
        if(vendas==NULL)
        {
            printf("\nLista Vazia!!!");
            return;
        }

        noptr_venda *p;
        p = vendas;
        cout<<"\n_____________\n";
        cout<<"\tVendas:";
        cout<<"\n_____________\n";
        while(p)
        {
            cout<<"CPF: ";
            puts(p->cpf_C);
            printf("\nCodigo: %d\n", *p->cod_P);
            printf("Quantidade: %d\n", p->quant);
            cout<<"\n_____________\n";
            p = p->prox;
        }
    }
    break;

    case 2:
    {
        char cpf[x];
        cout<<"Informe o CPF para listar as vendas: ";
        setbuf(stdin, NULL);
        gets(cpf);
        noptr_venda *v = vendas;
        if (v)
        {
            while(v->prox && strcmp(cpf, v->cpf_C)==1)
            {
                v = v->prox;
            }
            if(strcmp(v->cpf_C,cpf)!=0)
                cout<<"\nCliente nao encontrado nas vendas!";
            else
            {
                v = vendas;
                cout<<"\n_____________\n";
                cout<<"\tVendas:";
                cout<<"\n_____________\n";
                while(v)
                {
                    if (strcmp(v->cpf_C,cpf)==0)
                    {
                        cout<<"CPF: ";
                        puts(v->cpf_C);
                        printf("\nCodigo: %d\n", *v->cod_P);
                        printf("Quantidade: %d\n", v->quant);
                        cout<<"\n_____________\n";
                    }
                    v = v->prox;
                }
            }
        }
        else
            cout<<"\nLista vazia!";

    }
    break;

    case 3:
    {
        int cont=0;
        noptr_venda *v = vendas;
        if (v)
        {
            while(v->prox)
            {
                v = v->prox;
                cont++;
            }
            cont++;
            cout<<"\nNumero de vendas: "<<cont;

        }
        else
        {
            cout<<"\nLista Vazia!";
        }

    }
    break;
    }
}
int menu()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tMenu";
    cout<<"\n___________________\n";
    cout<<"1 -> Clientes\n";
    cout<<"2 -> Produtos\n";
    cout<<"3 -> Vendas\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Sair";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuClientes()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tMenu de Clientes";
    cout<<"\n___________________\n";
    cout<<"1 -> Cadastrar\n";
    cout<<"2 -> Remover\n";
    cout<<"3 -> Alterar\n";
    cout<<"4 -> Consultar\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuClientesAlterar()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tAlterar";
    cout<<"\n___________________\n";
    cout<<"1 -> Nome\n";
    cout<<"2 -> Data de Nascimento\n";
    cout<<"3 -> Endereco\n";
    cout<<"4 -> Telefone\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuClientesConsultar()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tConsultar";
    cout<<"\n___________________\n";
    cout<<"1 -> Listar todos os clientes\n";
    cout<<"2 -> Cliente especifico\n";
    cout<<"3 -> Numero de clientes cadastrados\n";
    cout<<"4 -> Quantidade de clientes que compraram acima de um valor determinado\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuProdutos()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tMenu de Produtos";
    cout<<"\n___________________\n";
    cout<<"1 -> Cadastrar\n";
    cout<<"2 -> Remover\n";
    cout<<"3 -> Alterar\n";
    cout<<"4 -> Consultar\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuProdutosAlterar()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tAlterar";
    cout<<"\n___________________\n";
    cout<<"1 -> Descricao\n";
    cout<<"2 -> Quantidade em estoque\n";
    cout<<"3 -> Preco\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuProdutosConsultar()
{
    int op;
    cout<<"\n_______\n";
    cout<<"\tConsultar";
    cout<<"\n_______\n";
    cout<<"1 -> Listar todos os produtos\n";
    cout<<"2 -> Produduto especifico\n";
    cout<<"3 -> Numero de produtos cadastrados\n";
    cout<<"4 -> Produtos com quantidade abaixo do valor especificado\n";
    cout<<"\n_______\n";
    cout<<"0 -> Voltar";
    cout<<"\n_______\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuVendas()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tMenu de Vendas";
    cout<<"\n___________________\n";
    cout<<"1 -> Cadastrar\n";
    cout<<"2 -> Remover\n";
    cout<<"3 -> Alterar\n";
    cout<<"4 -> Consultar\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}
int menuVendasConsultar()
{
    int op;
    cout<<"\n___________________\n";
    cout<<"\tConsultar";
    cout<<"\n___________________\n";
    cout<<"1 -> Listar todas as vendas\n";
    cout<<"2 -> Venda efetuada\n";
    cout<<"3 -> Quantidade de vendas\n";
    cout<<"\n___________________\n";
    cout<<"0 -> Voltar";
    cout<<"\n___________________\n";
    cout<<"Digite uma opcao: ";
    scanf("%d", &op);
    system("cls");
    return op;
}

void tirarespaco (char str[])
{
    for(unsigned aux = 0; aux < strlen(str); aux++)
    {
        if(str[aux] == ' ')
        {
            str[aux] = toupper(str[aux+1]);
            for(unsigned aux1=aux+1; aux1 < strlen(str); aux1++)
            {
                str[aux1] = str[aux1+1];
            }
        }
    }
}
void colocarespaco (char str[])
{
    char straux[100];
    int k;
    int j;
    for(unsigned i=0; i<strlen(str); i++)
    {
        if(str[i]>40 && str[i]<91)
        {
            if (i!=0)
            {
                j=i;
                for (int l =0; l<100; l++)
                    straux[l]='\0';
                k=0;
                while(str[j]!='\0')
                {
                    straux[k]=str[j];
                    j++;
                    k++;
                }
                str[i]=' ';
                k=0;
                i++;
                j=i;
                while(straux[k]!='\0')
                {
                    str[j]=straux[k];
                    k++;
                    j++;
                }
            }
        }
        if (i==0)
            str[i]=toupper(str[i]);
    }
}
void zera_str(char str[])
{
    for (int i=0; i<100; i++)
        str[i]='\0';
};
