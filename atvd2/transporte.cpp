#include <iostream>
#include <vector>
#include <stdexcept>

// Por que o código viola o LSP?

// O código viola o LSP porque a classe CarroEletrico altera a premissa da classe base Carro. 
// Quando a função prepararViagem recebe um objeto do tipo Carro, ela espera que o método abastecer() funcione normalmente.

// Ao passar um CarroEletrico que lança uma exceção (runtime_error), o programa quebra. Em termos técnicos: 
// a subclasse enfraquece as pós-condições e altera o comportamento esperado da classe pai, tornando a substituição perigosa.

using namespace std;

class Veiculo {
public:
    virtual void preparar() = 0;
    virtual ~Veiculo() {}
};

class CarroCombustivel : public Veiculo {
public:
    void abastecer() {
        cout << "Carro abastecido com gasolina." << endl;
    }

    void preparar() override {
        abastecer();
    }
};

class CarroEletrico : public Veiculo {
public:
    void carregarBateria() {
        cout << "Bateria carregada com eletricidade." << endl;
    }

    void preparar() override {
        carregarBateria();
    }
};

void prepararViagem(Veiculo& veiculo) {
    veiculo.preparar();
}

int main() {
    CarroCombustivel meuCarro;
    CarroEletrico meuTesla;

    prepararViagem(meuCarro);
    prepararViagem(meuTesla);

    return 0;
}