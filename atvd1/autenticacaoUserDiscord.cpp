#include <list>
#include <iostream>
using namespace std;

class Autenticacao
{
public:
    virtual void autenticar() = 0;
};

class LoginSenha : public Autenticacao
{
private:
    string nome;
    string senha;

public:
    LoginSenha(string n, string s) : nome(n), senha(s) {}
    void autenticar() override
    {
        if (nome.size() < 4)
        {
            cout << "Falha na autenticação" << endl;
            return;
        }
        if (senha.size() < 8)
        {
            cout << "Falha na autenticação" << endl;
            return;
        }
        cout << "Autenticado" << endl;
    }
};

class GoogleAuth : public Autenticacao
{
private:
    string email;
    string validate = "@gmail.com";

public:
    GoogleAuth(string e) : email(e) {}
    void autenticar() override
    {
        if (email.find(validate) == string::npos)
        {
            cout << "Falha na autenticação" << endl;
            return;
        }
        cout << "Autenticado" << endl;
    }
    ~GoogleAuth();
};

class QRCodeAuth : public Autenticacao
{
private:
    string codigo;
    string validate = "QR12345";
public:
    QRCodeAuth(string c) : codigo(c) {}
    // validar se é igual a QR12345
    void autenticar() override{
        if(codigo != validate){
            cout << "Falha na autenticação" << endl;
            return;
        }
        cout << "Autenticado" << endl;
    }
    ~QRCodeAuth();
};

int main()
{
    list<Autenticacao*> tentativas;
    int opc = 0;
    bool rodando = true;

    do {
        cout << "\n--- SISTEMA DE AUTENTICACAO ---" << endl;
        cout << "1 - Login por Senha" << endl;
        cout << "2 - Login por Google" << endl;
        cout << "3 - Login por QR Code" << endl;
        cout << "4 - Ver logs e Sair" << endl;
        cout << "Escolha: ";
        cin >> opc;

        switch (opc) {
            case 1: {
                string n, s;
                cout << "Nome: "; cin >> n;
                cout << "Senha: "; cin >> s;
                tentativas.push_back(new LoginSenha(n, s));
                tentativas.back()->autenticar();
                break;
            }
            case 2: {
                string e;
                cout << "Email: "; cin >> e;
                tentativas.push_back(new GoogleAuth(e));
                tentativas.back()->autenticar();
                break;
            }
            case 3: {
                string c;
                cout << "Codigo QR: "; cin >> c;
                tentativas.push_back(new QRCodeAuth(c));
                tentativas.back()->autenticar();
                break;
            }
            case 4: {
                cout << "\nLimpando memoria e encerrando..." << endl;
                // Percorre a lista para deletar cada objeto criado com 'new'
                for (Autenticacao* a : tentativas) {
                    delete a;
                }
                tentativas.clear();
                rodando = false;
                break;
            }
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while (rodando);
    return 0;
}