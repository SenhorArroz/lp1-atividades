#include <iostream>
#include <list>
using namespace std;

class Produto
{
private:
    string nome = "Produto";
    int preco = 20;

public:
    Produto(string n, int p) : nome(n), preco(p) {}
    virtual void showInfo()
    {
        cout << "nome: " << nome << " | preco: " << preco/100 << " | " << endl;
    }
    void setNome(string nomeS) { nome = nomeS; }
    void setPreco(int precoS) { preco = precoS; }
};

class ProdutoLimpeza : public Produto
{
private:
    string tipoUso;

public:
    ProdutoLimpeza(string n, int p, string uso) : Produto(n, p), tipoUso(uso) {}
    void showInfo() override
    {
        Produto::showInfo();
        cout << "Tipo uso: " << tipoUso << endl;
    }
    void setTipoUso(string tipo) { tipoUso = tipo; }
};
class ProdutoAlimenticio : public Produto
{
private:
    string validade = "20/12/2012";

public:
    ProdutoAlimenticio(string n, int p, string val) : Produto(n, p), validade(val) {}
    void showInfo() override
    {
        Produto::showInfo();
        cout << "Validade: " << validade;
    }
    void setValidade(string val) { validade = val; }
};

class ProdutoEletronico : public Produto
{
private:
    string voltagem = "220V";
    string garantia = "Até 2077";

public:
    ProdutoEletronico(string n, int p, string volt, string gar) : Produto(n, p), voltagem(volt), garantia(gar) {}
    void setVoltagem(string volt) { voltagem = volt; }
    void setGarantia(string garant) { garantia = garant; }
    void showInfo() override
    {
        Produto::showInfo();
        cout << "voltagem: " << voltagem << " | garantia: " << garantia << endl;
    }
};

int main()
{
    list<Produto *> produtosCadastrados;
    cout << "Iniciando sistema..." << endl;
    cout << "--------------------" << endl;
    cout << "Bem vindo ao Cash Flow, seu sistema de gerenciamento de produtos" << endl;
    bool condition = true;
    do
    {
        int opc = 0;
        cout << "-====- Cash Flow -====-" << endl;
        cout << "Escolha uma opcao:" << endl;
        cout << "1 - Adicionar produto" << endl;
        cout << "2 - Exibir produtos" << endl;
        cout << "3 - Sair do sistema" << endl;
        cout << "-----------------------" << endl;
        cin >> opc;
        switch (opc)
        {

        case 1:
        {
            int tipo = 0;

            cout << "tipo do produto:" << endl;
            cout << "1- limpeza" << endl;
            cout << "2- alimenticio" << endl;
            cout << "3- eletronico" << endl;
            cout << "escolha: ";
            cin >> tipo;
            if (tipo == 1)
            {
                string nome = "f";
                int preco = 0;
                string tipoUso = "";
                cout << "nome do produto: " << endl;
                cin >> nome;

                cout << "preco do produto (em centavos): ";
                cin >> preco;

                cout << "tipo de uso do produto: ";
                cin >> tipoUso;
                produtosCadastrados.push_back(new ProdutoLimpeza(nome, preco, tipoUso));
            }
            else if (tipo == 2)
            {
                string nome = "f";
                int preco = 0;
                string validade = "";
                cout << "nome do produto: " << endl;
                cin >> nome;

                cout << "preco do produto (em centavos): ";
                cin >> preco;

                cout << "validade do produto: ";
                cin >> validade;
                produtosCadastrados.push_back(new ProdutoAlimenticio(nome, preco, validade));
            }
            else if (tipo == 3)
            {
                string nome = "f";
                int preco = 0;
                string voltagem = "";
                string garantia = "";
                cout << "nome do produto: " << endl;
                cin >> nome;

                cout << "preco do produto (em centavos): ";
                cin >> preco;

                cout << "voltagem do produto: ";
                cin >> voltagem;

                cout << "garantia do produto: ";
                cin >> garantia;
                produtosCadastrados.push_back(new ProdutoEletronico(nome, preco, voltagem, garantia));
            }
            else
            {
                cout << "comando inválido";
            }
            break;
        }

        case 2:
            cout << "-------------" << endl;
            cout << "Lista de produtos: " << endl;
            for (Produto *p : produtosCadastrados)
            {
                p->showInfo();
                cout << endl;
            }
            break;
        case 3:
            for (Produto *p : produtosCadastrados)
            {
                delete p;
            }
            produtosCadastrados.clear();

            cout << "Finalizando sistema...";
            condition = false;
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            break;
        }

    } while (condition);

    return 0;
}
