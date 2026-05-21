#include <iostream>
#include <list>
using namespace std;

class Autenticacao {
    public:
        virtual void autenticar() = 0;
};

class LoginSenha : public Autenticacao{
    private: 
        string login;
        string senha;
    public:
        LoginSenha(string login, string senha){
            this->login = login;
            this->senha = senha;
        }

        void autenticar() override {
            if(login.size() < 4 || senha.size() < 8){
                cout << "Falha na autenticacao" << endl;
            }
            else{
                cout << "Autenticado com Login e Senha" << endl;
            }
        }
};

class GoogleAuth : public Autenticacao{
    private: 
        string email;
    public:
        GoogleAuth(string email){
            this->email = email;
        }
        void autenticar() override {
            if(email.find("@gmail.com") != string::npos){
                cout << "Autenticado com Google" << endl;
            }
            else{
                cout << "Falha na autenticacao" << endl;
            }
        }
};

class QRCodeAuth : public Autenticacao{
    private: 
        string codigo;
    public:
        QRCodeAuth(string codigo){
            this->codigo = codigo;
        }
        void autenticar() override {
            if(codigo == "QR12345"){
                cout << "Autenticado com QR Code" << endl;
            }
            else{
                cout << "Falha na autenticacao" << endl;
            }
        }
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