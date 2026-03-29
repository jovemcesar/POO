#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*
 Atividade guiada: Encapsulamento e Herança
 Tema: Estação de bombeamento

 Requisitos atendidos:
 - Classe-base AtivoCampo
 - Classes derivadas SensorNivel e BombaDosadora
 - tag e bloqueio encapsulados na base
 - Derivadas não acessam atributos private diretamente
 - Uso de protected apenas onde faz sentido
 - Função friend em SensorNivel para inspeção técnica
 - Validações de alteração de nível e vazão
 - Resumo no terminal
*/

class AtivoCampo {
private:
    string tag;       // private: identificação deve ser protegida contra alteração indevida
    bool bloqueado;   // private: estado interno controlado apenas pela própria classe/base

protected:
    bool energizado;  // protected: derivadas podem consultar/ajustar a energização quando necessário

public:
    AtivoCampo(const string& tagInicial, bool energizadoInicial = true)
        : tag(tagInicial), bloqueado(false), energizado(energizadoInicial) {}

    string getTag() const {
        return tag;
    }

    bool estaBloqueado() const {
        return bloqueado;
    }

    bool estaEnergizado() const {
        return energizado;
    }

    void bloquear() {
        bloqueado = true;
    }

    void desbloquear() {
        bloqueado = false;
    }

    void desligar() {
        energizado = false;
    }

    void ligar() {
        energizado = true;
    }

    virtual void exibirResumo() const {
        cout << "Ativo: " << tag
             << " | Energizado: " << (energizado ? "Sim" : "Nao")
             << " | Bloqueado: " << (bloqueado ? "Sim" : "Nao")
             << '\n';
    }

    virtual ~AtivoCampo() = default;
};

class SensorNivel : public AtivoCampo {
private:
    double nivelPercentual; // private: leitura do sensor deve ser alterada apenas por método validado

public:
    SensorNivel(const string& tagInicial, double nivelInicial, bool energizadoInicial = true)
        : AtivoCampo(tagInicial, energizadoInicial), nivelPercentual(0.0) {
        setNivel(nivelInicial);
    }

    bool setNivel(double novoNivel) {
        if (novoNivel < 0.0 || novoNivel > 100.0) {
            return false;
        }
        nivelPercentual = novoNivel;
        return true;
    }

    double getNivel() const {
        return nivelPercentual;
    }

    void exibirResumo() const override {
        cout << "SensorNivel [" << getTag() << "]"
             << " | Nivel: " << fixed << setprecision(1) << nivelPercentual << "%"
             << " | Energizado: " << (estaEnergizado() ? "Sim" : "Nao")
             << " | Bloqueado: " << (estaBloqueado() ? "Sim" : "Nao")
             << '\n';
    }

    friend void inspecaoTecnica(const SensorNivel& sensor);
};

class BombaDosadora : public AtivoCampo {
private:
    double vazaoLh; // private: vazão só pode ser alterada com validação

public:
    BombaDosadora(const string& tagInicial, double vazaoInicial, bool energizadoInicial = true)
        : AtivoCampo(tagInicial, energizadoInicial), vazaoLh(0.0) {
        setVazao(vazaoInicial);
    }

    bool setVazao(double novaVazao) {
        if (novaVazao < 0.0 || novaVazao > 500.0) {
            return false;
        }
        vazaoLh = novaVazao;
        return true;
    }

    double getVazao() const {
        return vazaoLh;
    }

    void exibirResumo() const override {
        cout << "BombaDosadora [" << getTag() << "]"
             << " | Vazao: " << fixed << setprecision(1) << vazaoLh << " L/h"
             << " | Energizado: " << (estaEnergizado() ? "Sim" : "Nao")
             << " | Bloqueado: " << (estaBloqueado() ? "Sim" : "Nao")
             << '\n';
    }
};

// friend: acesso técnico excepcional ao estado interno do SensorNivel
void inspecaoTecnica(const SensorNivel& sensor) {
    cout << "\n--- Inspecao Tecnica do Sensor ---\n";
    cout << "TAG: " << sensor.getTag() << '\n';
    cout << "Nivel interno: " << fixed << setprecision(1) << sensor.nivelPercentual << "%\n";
    cout << "Energizado: " << (sensor.estaEnergizado() ? "Sim" : "Nao") << '\n';
    cout << "Bloqueado: " << (sensor.estaBloqueado() ? "Sim" : "Nao") << '\n';
}

int main() {
    SensorNivel sensor("LT-101", 37.5);
    BombaDosadora bomba("P-201", 120.0);

    cout << "Estado inicial:\n";
    sensor.exibirResumo();
    bomba.exibirResumo();

    cout << "\nTestando alteracoes validas:\n";
    if (sensor.setNivel(82.3)) {
        cout << "Nivel do sensor atualizado com sucesso.\n";
    } else {
        cout << "Falha ao atualizar nivel do sensor.\n";
    }

    if (bomba.setVazao(185.0)) {
        cout << "Vazao da bomba atualizada com sucesso.\n";
    } else {
        cout << "Falha ao atualizar vazao da bomba.\n";
    }

    cout << "\nTestando alteracoes invalidas:\n";
    if (!sensor.setNivel(130.0)) {
        cout << "Valor invalido para nivel: permitido entre 0 e 100.\n";
    }

    if (!bomba.setVazao(-15.0)) {
        cout << "Valor invalido para vazao: permitido entre 0 e 500 L/h.\n";
    }

    cout << "\nAplicando bloqueio e desligamento:\n";
    sensor.bloquear();
    bomba.desligar();

    cout << "\nResumo final:\n";
    sensor.exibirResumo();
    bomba.exibirResumo();

    inspecaoTecnica(sensor);

    return 0;
}