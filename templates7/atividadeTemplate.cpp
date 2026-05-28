#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Item {
public:
    string name;
    string type;
    int value;

    Item() : name("Vazio"), type("Nenhum"), value(0) {}
    Item(string n, string t, int v) : name(n), type(t), value(v) {}

    void imprimir() const {
        cout << "[" << name << " | Tipo: " << type << " | Bônus: " << value << "]";
    }
};

template <typename T>
class Inventario {
private:
    vector<T> dados;

public:
    void inserir(T item) {
        dados.push_back(item);
    }

    int tamanho() const {
        return dados.size();
    }

    bool estaVazio() const {
        return dados.empty();
    }

    T buscar(int id) {
        if (id >= 0 && id < dados.size()) {
            return dados[id];
        }
        return T();
    }

    void listar() {
        if (dados.empty()) {
            cout << "(Inventário Vazio)\n";
            return;
        }
        for (int i = 0; i < dados.size(); i++) {
            cout << i << " - ";
            dados[i].imprimir();
            cout << "\n";
        }
    }
};

class Personagem {
public:
    string nome;
    int vidaMax;
    int vidaAtual;
    int ataqueBase;
    bool estaDefendendo;

    Inventario<Item> meuInventario;

    Item itemAtaqueEquipado;
    Item itemDefesaEquipado;

    Personagem(string n, int v, int atq) : nome(n), vidaMax(v), vidaAtual(v), ataqueBase(atq), estaDefendendo(false) {}

    void resetarVida() {
        vidaAtual = vidaMax;
        estaDefendendo = false;
    }

    void selecionarItensJogador() {
        itemAtaqueEquipado = Item(); 
        itemDefesaEquipado = Item();

        if (meuInventario.estaVazio()) {
            cout << nome << " não possui itens no inventário.\n";
            return;
        }

        cout << "\n--- Inventário de " << nome << " ---\n";
        meuInventario.listar();
        
        int escolha;
        cout << "Escolha o ID do item para equipar (ou -1 para nenhum): ";
        cin >> escolha;

        if (escolha >= 0 && escolha < meuInventario.tamanho()) {
            Item selecionado = meuInventario.buscar(escolha);
            if (selecionado.type == "Ataque") {
                itemAtaqueEquipado = selecionado;
                cout << "Item " << selecionado.name << " equipado como Arma!\n";
            } else if (selecionado.type == "Defesa") {
                itemDefesaEquipado = selecionado;
                cout << "Item " << selecionado.name << " equipado como Escudo!\n";
            }
        } else {
            cout << "Nenhum item equipado.\n";
        }
    }

    void selecionarItensAutomatico() {
        itemAtaqueEquipado = Item();
        itemDefesaEquipado = Item();

        if (meuInventario.estaVazio()) {
            return;
        }

        for (int i = 0; i < meuInventario.tamanho(); i++) {
            Item atual = meuInventario.buscar(i);
            if (atual.type == "Ataque" && atual.value > itemAtaqueEquipado.value) {
                itemAtaqueEquipado = atual;
            } else if (atual.type == "Defesa" && atual.value > itemDefesaEquipado.value) {
                itemDefesaEquipado = atual;
            }
        }

        if (itemAtaqueEquipado.value > 0) {
            cout << nome << " equipou automaticamente: " << itemAtaqueEquipado.name << "\n";
        }
        if (itemDefesaEquipado.value > 0) {
            cout << nome << " equipou automaticamente: " << itemDefesaEquipado.name << "\n";
        }
    }

    int decidirAcao() {
        int chanceDefender = 0;
        double proporcaoVida = (double)vidaAtual / vidaMax;

        if (proporcaoVida <= 0.10) {
            chanceDefender = 75;
        } else if (proporcaoVida <= 0.25) {
            chanceDefender = 60;
        } else if (proporcaoVida <= 0.50) {
            chanceDefender = 50;
        }

        int rolagem = rand() % 100;
        if (rolagem < chanceDefender) {
            estaDefendendo = true;
            return 2; 
        }
        return 1; 
    }

    int calcularDanoAleatorio() {
        int danoMaximo = ataqueBase + itemAtaqueEquipado.value;
        return (rand() % danoMaximo) + 1;
    }

    void receberDano(int danoInimigo) {
        int defesaTotal = itemDefesaEquipado.value;

        if (estaDefendendo) {
            cout << nome << " estava defendendo! O escudo absorveu mais dano.\n";
            defesaTotal += 15; 
            estaDefendendo = false; 
        }

        int danoFinal = danoInimigo - defesaTotal;
        if (danoFinal < 1) danoFinal = 1;

        vidaAtual -= danoFinal;
        cout << nome << " recebeu " << danoFinal << " de dano! (Vida: " << (vidaAtual < 0 ? 0 : vidaAtual) << ")\n";
    }

    bool estaVivo() {
        return vidaAtual > 0;
    }
};

void executarTurno(Personagem& atacante, Personagem& defensor) {
    if (defensor.estaDefendendo) {
        defensor.estaDefendendo = false;
    }

    int acao = atacante.decidirAcao();

    if (acao == 1) {
        cout << atacante.nome << " avança para atacar!\n";
        defensor.receberDano(atacante.calcularDanoAleatorio());
    } else {
        cout << atacante.nome << " decidiu se defender neste turno!\n";
    }
}

void realizarCombate(Personagem& p1, Personagem& p2) {
    p1.resetarVida();
    p2.resetarVida();

    cout << "\n--- O COMBATE COMEÇOU ---\n";
    p1.selecionarItensJogador();
    p2.selecionarItensAutomatico();

    cout << "\n--- QUE COMECEM OS TURNOS ---\n";
    int turno = 1;

    while (p1.estaVivo() && p2.estaVivo()) {
        cout << "\n[Turno " << turno << "]\n";
        
        executarTurno(p1, p2);
        if (!p2.estaVivo()) break;

        executarTurno(p2, p1);
        turno++;
    }

    Personagem* vencedor = p1.estaVivo() ? &p1 : &p2;
    cout << "\n-----------------------------------------\n";
    cout << "  " << vencedor->nome << " VENCEU O COMBATE!!!\n";
    cout << "-----------------------------------------\n";

    int sorteio = rand() % 6;
    Item itemGanho;
    
    switch (sorteio) {
        case 0: itemGanho = Item("Espada de Bronze", "Ataque", 10); break;
        case 1: itemGanho = Item("Machado de Guerra", "Ataque", 18); break;
        case 2: itemGanho = Item("Lança Reluzente", "Ataque", 25); break;
        case 3: itemGanho = Item("Escudo de Madeira", "Defesa", 5); break;
        case 4: itemGanho = Item("Escudo de Ferro", "Defesa", 12); break;
        case 5: itemGanho = Item("Escudo Rúnico", "Defesa", 20); break;
    }

    cout << vencedor->nome << " ganhou um item: ";
    itemGanho.imprimir();
    cout << " (Adicionado ao inventário)\n";

    vencedor->meuInventario.inserir(itemGanho);
}

int main() {
    srand(time(0));

    Personagem jogador1("Guerreiro A", 100, 20);
    Personagem jogador2("Guerreiro B", 100, 20);

    char continuar = 's';
    int rodada = 1;

    while (continuar == 's' || continuar == 'S') {
        cout << "\n-----------------------------------------\n";
        cout << "            RODADA DE COMBATE " << rodada << "\n";
        cout << "-----------------------------------------\n";

        realizarCombate(jogador1, jogador2);

        cout << "\nDesejam jogar mais uma rodada de combate? (s/n): ";
        cin >> continuar;
        rodada++;
    }

    cout << "\nJogo encerrado. Obrigado por jogar!\n";
    return 0;
}