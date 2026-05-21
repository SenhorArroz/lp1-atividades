#include <iostream>
#include <string>

using namespace std;

class Conta {
private:
    int numero;
    string titulo;
    double saldo;

public:
    Conta(int num, string tit, double sal){
        numero = num;
        titulo = tit;
        saldo = sal;
    }

    Conta& operator+=(double valor) {
        if (valor > 0) {
            saldo += valor;
        }
        return *this; 
    }

    Conta operator-(double valor) const {
        if (valor > saldo) {
            cout << "Saldo insuficiente para realizar a transferencia/saque." << endl;
            return Conta(numero, titulo, saldo);
        }
        return Conta(numero, titulo, saldo - valor);
    }

    friend ostream& operator<<(ostream& os, const Conta& c) {
        os << "Numero: " << c.numero 
           << " | Titular: " << c.titulo 
           << " | Saldo: R$" << c.saldo;
        return os;
    }
};

int main() {
        Conta contaOrigem(1001, "Maria Silva", 1000.00);
        cout << "--- Estado Inicial ---" << endl;
        cout << contaOrigem << endl;

        contaOrigem += 500.00;
        cout << "\n--- Apos Deposito de R$500 ---" << endl;
        cout << contaOrigem << endl;

        contaOrigem = contaOrigem - 200.00;
        cout << "\n--- Apos Transferencia de R$200 ---" << endl;
        cout << contaOrigem << endl;

        cout << "\n--- Tentando transferir R$2000 ---" << endl;
        contaOrigem = contaOrigem - 2000.00; 

    return 0;
}