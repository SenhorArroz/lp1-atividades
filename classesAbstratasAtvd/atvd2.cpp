#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class TipoDocumento { PDF, WORD, EXCEL };
enum class EspecieDocumento { DESPACHO, DECLARACAO, CERTIFICADO };

string tipoToString(TipoDocumento tipo) {
    switch(tipo) {
        case TipoDocumento::PDF: return "PDF";
        case TipoDocumento::WORD: return "Word";
        case TipoDocumento::EXCEL: return "Excel";
        default: return "Desconhecido";
    }
}

string especieToString(EspecieDocumento especie) {
    switch(especie) {
        case EspecieDocumento::DESPACHO: return "Despacho";
        case EspecieDocumento::DECLARACAO: return "Declaracao";
        case EspecieDocumento::CERTIFICADO: return "Certificado";
        default: return "Desconhecida";
    }
}

class Setor {
private:
    string nome;
public:
    Setor(string n) : nome(n) {}
    string getNome() const { return nome; }
};

class EntidadeAuditavel {
protected:
    vector<string> historicoAcoes;

public:
    virtual ~EntidadeAuditavel() = default;

    void registrarAcao(const string& acao) {
        historicoAcoes.push_back(acao);
    }

    void exibirHistorico() const {
        for (const string& acao : historicoAcoes) {
            cout << "  - " << acao << endl;
        }
    }
    virtual void exibirDetalhes() const = 0; 
};

class Documento : public EntidadeAuditavel {
private:
    string titulo;
    TipoDocumento tipo;
    EspecieDocumento especie;
    vector<Setor> assinaturas;

public:
    Documento(string tit, TipoDocumento t, EspecieDocumento e) 
        : titulo(tit), tipo(t), especie(e) {
        registrarAcao("Documento criado: " + titulo);
    }

    void assinar(const Setor& setor) {
        assinaturas.push_back(setor);
        registrarAcao("Documento assinado pelo setor: " + setor.getNome());
    }

    void exibirDetalhes() const override {
        cout << "[Documento] " << titulo 
             << " | Tipo: " << tipoToString(tipo) 
             << " | Especie: " << especieToString(especie) << endl;
        
        if (!assinaturas.empty()) {
            cout << "  Assinaturas: ";
            for (const auto& s : assinaturas) cout << s.getNome() << " | ";
            cout << endl;
        }
    }
};

class Processo : public EntidadeAuditavel {
private:
    int numero;
    Setor* setorAtual;
    vector<Documento> documentos;

public:
    Processo(int num, Setor* setorInicial) : numero(num), setorAtual(setorInicial) {
        registrarAcao("Processo " + to_string(numero) + " iniciado no setor " + setorInicial->getNome());
    }

    void movimentarPara(Setor* novoSetor) {
        string setorAntigo = setorAtual->getNome();
        setorAtual = novoSetor;
        registrarAcao("Movimentado do setor " + setorAntigo + " para " + novoSetor->getNome());
    }

    void adicionarDocumento(const Documento& doc) {
        documentos.push_back(doc);
        registrarAcao("Documento adicionado no setor " + setorAtual->getNome());
    }

    void exibirDetalhes() const override {
        cout << "\n=== PROCESSO " << numero << " ===" << endl;
        cout << "Setor Atual: " << setorAtual->getNome() << endl;
        cout << "Documentos anexados: " << documentos.size() << endl;
        cout << "--- Historico do Processo ---" << endl;
        exibirHistorico();
    }
};

int main() {
    Setor rh("Recursos Humanos");
    Setor ti("Tecnologia da Informacao");
    Setor diretoria("Diretoria Executiva");

    cout << "--- Documento Avulso ---" << endl;
    Documento declaracaoAvulsa("Declaracao de Ferias - Joao", TipoDocumento::PDF, EspecieDocumento::DECLARACAO);
    declaracaoAvulsa.assinar(rh);
    declaracaoAvulsa.exibirDetalhes();
    declaracaoAvulsa.exibirHistorico();

    Processo proc(2023001, &ti);

    Documento reqEquipamento("Requisicao de Notebook", TipoDocumento::WORD, EspecieDocumento::DESPACHO);
    reqEquipamento.assinar(ti);
    proc.adicionarDocumento(reqEquipamento);
    proc.movimentarPara(&diretoria);

    Documento certAprovacao("Certificado de Compra", TipoDocumento::PDF, EspecieDocumento::CERTIFICADO);
    certAprovacao.assinar(ti);
    certAprovacao.assinar(diretoria);
    proc.adicionarDocumento(certAprovacao);

    proc.exibirDetalhes();

    return 0;
}