#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AtuadorLinha {
protected:
    string tag;
    string descricao;

public:
    AtuadorLinha(string tag, string descricao)
        : tag(std::move(tag)), descricao(std::move(descricao)) {}

    virtual ~AtuadorLinha() = default;

    // Virtual para permitir polimorfismo dinamico: quando o programa usa
    // ponteiros da classe-base, a implementacao chamada depende do tipo real.
    virtual void aplicarReferenciaPercentual(double percentual) = 0;
    virtual void exibirResumo() const = 0;
};

class MotorEsteira : public AtuadorLinha {
private:
    double velocidadeMaxMpm;
    double referenciaPercentual;
    double velocidadeAtualMpm;

public:
    MotorEsteira(string tag, string descricao, double velocidadeMaxMpm)
        : AtuadorLinha(std::move(tag), std::move(descricao)),
          velocidadeMaxMpm(max(0.0, velocidadeMaxMpm)),
          referenciaPercentual(0.0),
          velocidadeAtualMpm(0.0) {}

    void aplicarReferenciaPercentual(double percentual) override {
        referenciaPercentual = clamp(percentual, 0.0, 100.0);
        velocidadeAtualMpm = (referenciaPercentual / 100.0) * velocidadeMaxMpm;
    }

    void exibirResumo() const override {
        cout << fixed << setprecision(2);
        cout << "[MotorEsteira] " << tag << " - " << descricao
             << " | Referencia: " << referenciaPercentual << "%"
             << " | Velocidade: " << velocidadeAtualMpm << " m/min"
             << " | Capacidade maxima: " << velocidadeMaxMpm << " m/min\n";
    }
};

class ValvulaDosagem : public AtuadorLinha {
private:
    double vazaoMaxLh;
    double referenciaPercentual;
    double aberturaAtualPercentual;
    double vazaoAtualLh;

public:
    ValvulaDosagem(string tag, string descricao, double vazaoMaxLh)
        : AtuadorLinha(std::move(tag), std::move(descricao)),
          vazaoMaxLh(max(0.0, vazaoMaxLh)),
          referenciaPercentual(0.0),
          aberturaAtualPercentual(0.0),
          vazaoAtualLh(0.0) {}

    void aplicarReferenciaPercentual(double percentual) override {
        referenciaPercentual = clamp(percentual, 0.0, 100.0);
        aberturaAtualPercentual = referenciaPercentual;
        vazaoAtualLh = (aberturaAtualPercentual / 100.0) * vazaoMaxLh;
    }

    void exibirResumo() const override {
        cout << fixed << setprecision(2);
        cout << "[ValvulaDosagem] " << tag << " - " << descricao
             << " | Referencia: " << referenciaPercentual << "%"
             << " | Abertura: " << aberturaAtualPercentual << "%"
             << " | Vazao: " << vazaoAtualLh << " L/h"
             << " | Vazao maxima: " << vazaoMaxLh << " L/h\n";
    }
};

int main() {
    MotorEsteira esteiraEntrada("ME-101", "Esteira principal de garrafas", 32.0);
    ValvulaDosagem valvulaXarope("VD-201", "Valvula de xarope concentrado", 180.0);
    MotorEsteira esteiraSaida("ME-102", "Esteira de saida para rotulagem", 28.0);
    ValvulaDosagem valvulaAditivo("VD-202", "Valvula de aditivo alimentar", 95.0);

    vector<AtuadorLinha*> atuadores = {
        &esteiraEntrada,
        &valvulaXarope,
        &esteiraSaida,
        &valvulaAditivo
    };

    const double comandoComum = 62.5;

    cout << "Aplicando referencia comum de " << comandoComum
         << "% para todos os atuadores...\n\n";

    for (AtuadorLinha* atuador : atuadores) {
        atuador->aplicarReferenciaPercentual(comandoComum);
    }

    cout << "Resumo final dos equipamentos:\n";
    for (const AtuadorLinha* atuador : atuadores) {
        atuador->exibirResumo();
    }

    return 0;
}