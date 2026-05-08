#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Personagem {
protected:
    string nome;
    int hp, hpMax;
    int mp, mpMax;

public:
    Personagem(string n, int h, int m) : nome(n), hpMax(h), hp(h), mpMax(m), mp(m) {}

    virtual ~Personagem() {}

    void recuperarStatus() {
        hp = min(hpMax, hp + (int)(hpMax * 0.1));
        mp = min(mpMax, mp + (int)(mpMax * 0.1));
    }

    string getNome() { return nome; }
    int getHp() { return hp; }
    int getMp() { return mp; }

    void receberDano(int dano) {
        hp -= dano;
        if (hp < 0) hp = 0;
    }

    virtual void ataqueSimples(Personagem* alvo) = 0;
    virtual void ataqueEspecial(Personagem* alvo) = 0;

    void mostrarStatus() {
        cout << "[" << nome << "] HP: " << hp << "/" << hpMax << " | MP: " << mp << "/" << mpMax << endl;
    }
};

class Guerreiro : public Personagem {
public:
    Guerreiro(string n) : Personagem(n, 200, 50) {}

    void ataqueSimples(Personagem* alvo) override {
        cout << nome << " atacou com a Espada!" << endl;
        alvo->receberDano(20);
    }

    void ataqueEspecial(Personagem* alvo) override {
        int custo = mpMax * 0.15;
        if (mp >= custo) {
            mp -= custo;
            cout << nome << " usou Corte Dimensional!" << endl;
            alvo->receberDano(50);
        } else {
            cout << "MP insuficiente! Tentando ataque simples..." << endl;
            ataqueSimples(alvo);
        }
    }
};

class Mago : public Personagem {
public:
    Mago(string n) : Personagem(n, 100, 200) {}

    void ataqueSimples(Personagem* alvo) override {
        cout << nome << " lancou Magia!" << endl;
        alvo->receberDano(15);
    }

    void ataqueEspecial(Personagem* alvo) override {
        int custo = mpMax * 0.15;
        if (mp >= custo) {
            mp -= custo;
            cout << nome << " lancou Magia Suprema!" << endl;
            alvo->receberDano(60);
        } else {
            cout << "MP insuficiente!" << endl;
            ataqueSimples(alvo);
        }
    }
};

class Arqueiro : public Personagem {
public:
    Arqueiro(string n) : Personagem(n, 150, 100) {}

    void ataqueSimples(Personagem* alvo) override {
        cout << nome << " lancou Flecha!" << endl;
        alvo->receberDano(25);
    }

    void ataqueEspecial(Personagem* alvo) override {
        int custo = mpMax * 0.15;
        if (mp >= custo) {
            mp -= custo;
            cout << nome << " usou Flecha Perfurante!" << endl;
            alvo->receberDano(45);
        } else {
            cout << "MP insuficiente!" << endl;
            ataqueSimples(alvo);
        }
    }
};

int main() {
    vector<Personagem*> jogadores;
    
    jogadores.push_back(new Guerreiro("Guerreiro Arthur"));
    jogadores.push_back(new Mago("Mago Merlin"));
    jogadores.push_back(new Arqueiro("Arqueiro Robin"));

    cout << "--- INICIO DA BATALHA ---" << endl;

    bool jogoAtivo = true;
    int turno = 0;

    while (jogoAtivo) {
        Personagem* atacante = jogadores[turno % jogadores.size()];
        Personagem* defensor = jogadores[(turno + 1) % jogadores.size()];

        if (atacante->getHp() > 0) {
            atacante->recuperarStatus();
            
            cout << "\n-----------------------------" << endl;
            cout << "Turno de: " << atacante->getNome() << endl;
            atacante->mostrarStatus();
            cout << "Alvo: " << defensor->getNome() << " (HP: " << defensor->getHp() << ")" << endl;
            
            cout << "Escolha o ataque: 1- Simples | 2- Especial: ";
            int opc;
            cin >> opc;

            if (opc == 2) atacante->ataqueEspecial(defensor);
            else atacante->ataqueSimples(defensor);

            if (defensor->getHp() <= 0) {
                cout << "\n!!! " << defensor->getNome() << " foi derrotado! !!!" << endl;
                jogoAtivo = false;
            }
        }
        turno++;
    }

    for (Personagem* p : jogadores) {
        delete p;
    }

    return 0;
}