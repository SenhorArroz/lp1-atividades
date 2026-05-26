#include <iostream>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

class IControlavel
{
public:
    virtual void ligar() = 0;
    virtual void desligar() = 0;
    virtual ~IControlavel() = default;
};

class IRelatavel
{
public:
    virtual void gerarRelatorio() = 0;
    virtual ~IRelatavel() = default;
};

class IAtualizavel
{
public:
    virtual void atualizarFirmware() = 0;
    virtual ~IAtualizavel() = default;
};


class RoboAspirador : public IControlavel
{
private:
    void esperar(int tempo)
    {
        int segundos = 0;
        while (segundos != tempo)
        {
            this_thread::sleep_for(std::chrono::seconds(1));
            segundos++;
            cout << "." << endl;
        }
    }

    bool RandDef()
    {
        random_device rd;
        mt19937 gerador(rd());
        bernoulli_distribution distribuicao(0.5);
        return distribuicao(gerador);
    }

    void Limpar()
    {
        cout << "Limpando..." << endl;
        cout << "..........." << endl;
        cout << "...Limpo..." << endl;
    }

    void ProcurarLimpeza()
    {
        do
        {
            cout << "Procurando..." << endl;
            esperar(5);
        } while (RandDef());
        Limpar();
    }

public:
    void ligar() override
    {
        cout << "Ligando..." << endl;
        cout << "..........." << endl;
        cout << "...Ligado.." << endl;
    }

    void desligar() override
    {
        cout << "Desligando..." << endl;
        cout << "..........." << endl;
        cout << "...Desligado.." << endl;
    }

    void funcionar()
    {
        ligar();
        ProcurarLimpeza();
        desligar();
    }
};

class Lampada : public IControlavel
{
private:
    bool ligado = false;

public:
    void ligar() override
    {
        cout << "Ligando..." << endl;
        cout << "..........." << endl;
        cout << "...Ligado.." << endl;
        ligado = true;
    }

    void desligar() override
    {
        cout << "Desligando..." << endl;
        cout << "..........." << endl;
        cout << "...Desligando.." << endl;
        ligado = false;
    }

    void funcionar()
    {
        bool funcionando = true;
        do
        {
            int opc = 0;
            cout << "\n[Lâmpada] O que queres fazer?" << endl;
            cout << "1 - para ligar" << endl;
            cout << "2 - para desligar" << endl;
            cout << "3 - voltar pro menu" << endl;
            cin >> opc;
            
            if (opc == 1)
            {
                if (ligado) cout << "Já está ligado" << endl;
                else ligar();
            }
            else if (opc == 2)
            {
                if (!ligado) cout << "Já está desligado" << endl;
                else desligar();
            }
            else if (opc == 3)
            {
                funcionando = false;
            }
            else
            {
                cout << "Quebraste a lâmpada, man!" << endl;
                funcionando = false;
            }

        } while (funcionando);
    }
};

class CafeteiraInteligente : public IControlavel
{
private:
    void esperar(int tempo)
    {
        for(int i = 0; i < tempo; i++)
        {
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "~ coando ~" << endl;
        }
    }

public:
    void ligar() override
    {
        cout << "Aquecendo a água..." << endl;
    }

    void desligar() override
    {
        cout << "Cafeteira em stand-by." << endl;
    }

    void funcionar()
    {
        cout << "\nIniciando preparo do café..." << endl;
        ligar();
        esperar(3);
        cout << "..........." << endl;
        cout << "Café pronto! Cuidado para não queimares a língua, man!" << endl;
        desligar();
    }
};

class ArCondicionado : public IControlavel, public IAtualizavel
{
private:
    bool ligado = false;
    int temperatura = 24;

public:
    void ligar() override
    {
        cout << "Ar Condicionado ligado. Clima de montanha ativado!" << endl;
        ligado = true;
    }

    void desligar() override
    {
        cout << "Ar Condicionado desligado. Voltando para o calor do deserto." << endl;
        ligado = false;
    }

    void atualizarFirmware() override
    {
        cout << "Baixando atualização de ventilação..." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        cout << "Firmware atualizado! Agora gela até a alma." << endl;
    }

    void funcionar()
    {
        bool funcionando = true;
        do
        {
            int opc = 0;
            cout << "\n[Ar Condicionado | Status: " << (ligado ? "ON" : "OFF") << " | Temp: " << temperatura << "C]" << endl;
            cout << "1 - Ligar/Desligar" << endl;
            cout << "2 - Diminuir Temperatura" << endl;
            cout << "3 - Aumentar Temperatura" << endl;
            cout << "4 - Atualizar Firmware" << endl;
            cout << "5 - Voltar pro menu" << endl;
            cin >> opc;

            if (opc == 1)
            {
                if (ligado) desligar();
                else ligar();
            }
            else if (opc == 2)
            {
                if(ligado) { temperatura--; cout << "Esfriando para " << temperatura << "C" << endl; }
                else { cout << "Liga o aparelho primeiro, man!" << endl; }
            }
            else if (opc == 3)
            {
                if(ligado) { temperatura++; cout << "Aquecendo para " << temperatura << "C" << endl; }
                else { cout << "Liga o aparelho primeiro, man!" << endl; }
            }
            else if (opc == 4)
            {
                atualizarFirmware();
            }
            else if (opc == 5)
            {
                funcionando = false;
            }
            else
            {
                cout << "Carregaste no botão errado e partiste o comando." << endl;
                funcionando = false;
            }
        } while (funcionando);
    }
};

class FechaduraInteligente : public IControlavel, public IRelatavel
{
private:
    bool trancado = true;
    int vezesAberta = 0;

public:
    void ligar() override // Trancar a porta
    {
        cout << "Fechadura TRANCADA. Ninguém entra!" << endl;
        trancado = true;
    }

    void desligar() override // Destrancar a porta
    {
        cout << "Fechadura DESTRAVADA. Podes entrar!" << endl;
        trancado = false;
        vezesAberta++;
    }

    void gerarRelatorio() override
    {
        cout << "\n--- RELATÓRIO DA PORTA ---" << endl;
        cout << "A porta foi aberta " << vezesAberta << " vezes hoje." << endl;
        cout << "--------------------------\n" << endl;
    }

    void funcionar()
    {
        bool funcionando = true;
        do
        {
            int opc = 0;
            cout << "\n[Fechadura] O que desejas fazer?" << endl;
            cout << "1 - Destrancar a porta" << endl;
            cout << "2 - Trancar a porta" << endl;
            cout << "3 - Ver relatório de acessos" << endl;
            cout << "4 - Voltar pro menu" << endl;
            cin >> opc;

            if (opc == 1)
            {
                if(!trancado) cout << "Já está destrancada, man!" << endl;
                else desligar();
            }
            else if (opc == 2)
            {
                if(trancado) cout << "Já está trancada, man!" << endl;
                else ligar();
            }
            else if (opc == 3)
            {
                gerarRelatorio();
            }
            else if (opc == 4)
            {
                funcionando = false;
            }
            else
            {
                cout << "Entrada inválida!" << endl;
            }
        } while (funcionando);
    }
};

class SensorDeClima : public IControlavel, public IRelatavel
{
private:
    bool ligado = false;

    float lerTemperatura() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<float> dis(15.0, 40.0);
        return dis(gen);
    }

    float lerUmidade() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<float> dis(30.0, 90.0);
        return dis(gen);
    }

public:
    void ligar() override
    {
        cout << "Iniciando sensores atmosféricos..." << endl;
        cout << "Sensor de Clima ONLINE. Lendo os ventos..." << endl;
        ligado = true;
    }

    void desligar() override
    {
        cout << "Sensor de Clima OFFLINE. Olha pela janela para saberes se vai chover." << endl;
        ligado = false;
    }

    void gerarRelatorio() override
    {
        if (!ligado) {
            cout << "O sensor está desligado, man! Liga-o primeiro." << endl;
            return;
        }
        cout << "\n--- RELATÓRIO CLIMÁTICO ---" << endl;
        cout << "Temperatura atual: " << lerTemperatura() << " C" << endl;
        cout << "Umidade do ar: " << lerUmidade() << " %" << endl;
        cout << "Previsão: Pode ser que chova, ou faça sol. 50% de chance." << endl;
        cout << "---------------------------\n" << endl;
    }

    void funcionar()
    {
        bool funcionando = true;
        do
        {
            int opc = 0;
            cout << "\n[Sensor de Clima | Status: " << (ligado ? "ON" : "OFF") << "]" << endl;
            cout << "1 - Ligar/Desligar" << endl;
            cout << "2 - Gerar Relatório do Clima" << endl;
            cout << "3 - Voltar pro menu" << endl;
            cin >> opc;

            if (opc == 1)
            {
                if (ligado) desligar();
                else ligar();
            }
            else if (opc == 2)
            {
                gerarRelatorio();
            }
            else if (opc == 3)
            {
                funcionando = false;
            }
            else
            {
                cout << "Deu curto-circuito no barómetro! Opção inválida." << endl;
            }
        } while (funcionando);
    }
};


int main()
{
    RoboAspirador robo;
    Lampada luz;
    CafeteiraInteligente cafeteira;
    ArCondicionado ar;
    FechaduraInteligente porta;
    SensorDeClima clima;

    bool painelLigado = true;

    cout << "======================================" << endl;
    cout << "  BEM-VINDO AO SEU SMART HOME HUB" << endl;
    cout << "======================================" << endl;

    while (painelLigado)
    {
        int escolha = 0;
        cout << "\nQual aparelho queres testar?" << endl;
        cout << "1 - Robô Aspirador" << endl;
        cout << "2 - Lâmpada" << endl;
        cout << "3 - Cafeteira Inteligente" << endl;
        cout << "4 - Ar Condicionado" << endl;
        cout << "5 - Fechadura Inteligente" << endl;
        cout << "6 - Sensor de Clima" << endl;
        cout << "0 - Desligar tudo e sair" << endl;
        cout << "-> ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            robo.funcionar();
            break;
        case 2:
            luz.funcionar();
            break;
        case 3:
            cafeteira.funcionar();
            break;
        case 4:
            ar.funcionar();
            break;
        case 5:
            porta.funcionar();
            break;
        case 6:
            clima.funcionar();
            break;
        case 0:
            cout << "Desligando a casa toda... Adeus!" << endl;
            painelLigado = false;
            break;
        default:
            cout << "Opção inválida, tenta de novo!" << endl;
            break;
        }
    }

    return 0;
}