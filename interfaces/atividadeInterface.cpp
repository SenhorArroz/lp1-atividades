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

// Aparelhos

class RoboAspirador : public IControlavel
{
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

        bool valor_aleatorio = distribuicao(gerador);

        return valor_aleatorio;
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
        cout << "...Desligando.." << endl;
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
            cout << "Você quer ligar ou desligar?" << endl;
            cout << "1 - para ligar" << endl;
            cout << "2 - para desligar" << endl;
            cin >> opc;
            if (opc == 1)
            {
                if (ligado)
                {
                    cout << "Já está ligado" << endl;
                }
                else
                {
                    ligado = true;
                }
            }
            if (opc == 2)
            {
                if (!ligado)
                {
                    cout << "Já está desligado" << endl;
                }
                else
                {
                    ligado = false;
                }
            }
            else
            {
                cout << "Quebrou a lâmpada, man!";
                funcionando = false;
            }

        } while (funcionando);
    }
};

class SensorDeClima : public IControlavel, public IRelatavel
{
};

int main()
{
    cout << "Hello World";

    return 0;
}