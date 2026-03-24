#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double nivelAtual;
    string origem;

public:
    // Construtor minimo:
    // faz sentido quando o sistema conhece apenas a identificacao do sensor.
    SensorNivel(string t) {
        tag = t;
        minimo = 0.0;
        maximo = 100.0;
        nivelAtual = 0.0;
        origem = "Construtor minimo";
    }

    // Construtor completo:
    // faz sentido quando o sensor ja nasce parametrizado.
    SensorNivel(string t, double min, double max, double nivel) {
        if (min >= max) {
            throw invalid_argument("Erro: minimo deve ser menor que maximo.");
        }

        tag = t;
        minimo = min;
        maximo = max;
        nivelAtual = nivel;
        origem = "Construtor completo";
    }

    void exibirResumo() {
        cout << "\n--- SensorNivel ---" << endl;
        cout << "Origem: " << origem << endl;
        cout << "Tag: " << tag << endl;
        cout << "Faixa: " << minimo << " a " << maximo << endl;
        cout << "Nivel atual: " << nivelAtual << endl;
    }
};

class Bomba {
private:
    string tag;
    double velocidade;
    bool ligada;
    string origem;

public:
    // Construtor minimo:
    // faz sentido quando a bomba foi cadastrada, mas ainda nao configurada.
    Bomba(string t) {
        tag = t;
        velocidade = 0.0;
        ligada = false;
        origem = "Construtor minimo";
    }

    // Construtor completo:
    // faz sentido quando a bomba ja nasce com estado operacional definido.
    Bomba(string t, double vel, bool estado) {
        if (vel < 0 || vel > 100) {
            throw invalid_argument("Erro: velocidade deve estar entre 0 e 100.");
        }

        tag = t;
        velocidade = vel;
        ligada = estado;
        origem = "Construtor completo";
    }

    void exibirResumo() {
        cout << "\n--- Bomba ---" << endl;
        cout << "Origem: " << origem << endl;
        cout << "Tag: " << tag << endl;
        cout << "Velocidade: " << velocidade << "%" << endl;
        cout << "Ligada: " << (ligada ? "Sim" : "Nao") << endl;
    }
};

class ControladorTanque {
private:
    string tag;
    double kp;
    double setpoint;
    string origem;

public:
    // Construtor minimo:
    // faz sentido quando o controlador existe, mas ainda sem ajuste fino.
    ControladorTanque(string t) {
        tag = t;
        kp = 1.0;
        setpoint = 50.0;
        origem = "Construtor minimo";
    }

    // Construtor completo:
    // faz sentido quando o controlador ja nasce configurado para operar.
    ControladorTanque(string t, double ganho, double sp) {
        if (ganho <= 0) {
            throw invalid_argument("Erro: ganho proporcional deve ser positivo.");
        }

        tag = t;
        kp = ganho;
        setpoint = sp;
        origem = "Construtor completo";
    }

    void exibirResumo() {
        cout << "\n--- ControladorTanque ---" << endl;
        cout << "Origem: " << origem << endl;
        cout << "Tag: " << tag << endl;
        cout << "Kp: " << kp << endl;
        cout << "Setpoint: " << setpoint << endl;
    }
};

int main() {
    try {
        // Dois objetos de cada classe usando construtores diferentes

        SensorNivel s1("LT-101");
        SensorNivel s2("LT-102", 0, 500, 230);

        Bomba b1("B-201");
        Bomba b2("B-202", 75, true);

        ControladorTanque c1("LIC-301");
        ControladorTanque c2("LIC-302", 2.5, 80);

        // Mostrar no terminal como cada objeto nasceu
        s1.exibirResumo();
        s2.exibirResumo();

        b1.exibirResumo();
        b2.exibirResumo();

        c1.exibirResumo();
        c2.exibirResumo();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}