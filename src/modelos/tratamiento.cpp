// Descripción: Implementación de la clase Tratamiento con herencia de Registro

#include "Tratamiento.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

Tratamiento::Tratamiento(string dui, string med, string dos, string frec,
                         string dur, string obs, string est)
    : duiPaciente(dui), medicamento(med), dosis(dos), frecuencia(frec),
      duracion(dur), observaciones(obs), estado(est) {}

void Tratamiento::registrar() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n=== Registrar Tratamiento ===\n";
    cout << "DUI del paciente: "; getline(cin, duiPaciente);
    cout << "Medicamento: "; getline(cin, medicamento);
    cout << "Dosis: "; getline(cin, dosis);
    cout << "Frecuencia: "; getline(cin, frecuencia);
    cout << "Duración: "; getline(cin, duracion);
    cout << "Observaciones: "; getline(cin, observaciones);
    cout << "Estado: "; getline(cin, estado);

    ofstream archivo("./output/tratamientos.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        auto writeStr = [&](const string& str) {
            size_t len = str.size();
            archivo.write((char*)&len, sizeof(size_t));
            archivo.write(str.c_str(), len);
        };

        writeStr(duiPaciente);
        writeStr(medicamento);
        writeStr(dosis);
        writeStr(frecuencia);
        writeStr(duracion);
        writeStr(observaciones);
        writeStr(estado);

        archivo.close();
        cout << "Tratamiento registrado correctamente.\n";
    }
}

void Tratamiento::mostrar() const {
    cout << "\nDUI: " << duiPaciente
         << "\nMedicamento: " << medicamento
         << "\nDosis: " << dosis
         << "\nFrecuencia: " << frecuencia
         << "\nDuración: " << duracion
         << "\nObservaciones: " << observaciones
         << "\nEstado: " << estado << "\n----------------------\n";
}

void Tratamiento::editar() {
    string input;
    cout << "\n=== Editar Tratamiento ===\n";
    cout << "Nueva dosis (actual: " << dosis << "): "; getline(cin, input); if (!input.empty()) dosis = input;
    cout << "Nueva frecuencia (actual: " << frecuencia << "): "; getline(cin, input); if (!input.empty()) frecuencia = input;
    cout << "Nueva duración (actual: " << duracion << "): "; getline(cin, input); if (!input.empty()) duracion = input;
    cout << "Nuevas observaciones: "; getline(cin, input); if (!input.empty()) observaciones = input;
    cout << "Nuevo estado: "; getline(cin, input); if (!input.empty()) estado = input;
}

void Tratamiento::eliminar() {
    estado = "Eliminado";
}

bool Tratamiento::coincideCon(const string& dui, const string& med) const {
    return duiPaciente == dui && medicamento == med;
}

string Tratamiento::getDUI() const { return duiPaciente; }
string Tratamiento::getMedicamento() const { return medicamento; }
string Tratamiento::getEstado() const { return estado; }
string Tratamiento::getDosis() const { return dosis; }
string Tratamiento::getFrecuencia() const { return frecuencia; }
string Tratamiento::getDuracion() const { return duracion; }
string Tratamiento::getObservaciones() const { return observaciones; }

// ================= FUNCIONES COMPLEMENTARIAS ===================

void editarTratamientoEnArchivo(const string& dui, const string& med) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    bool encontrado = false;
    ofstream archivo("./output/tratamientos.dat", ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para editar.";
        return;
    }
    for (auto& t : lista) {
        if (t.coincideCon(dui, med)) {
            encontrado = true;
            t.editar();
        }
    }
    for (const auto& t : lista) {
        auto writeStr = [&](const string& str) {
            size_t len = str.size();
            archivo.write((char*)&len, sizeof(size_t));
            archivo.write(str.c_str(), len);
        };
        writeStr(t.getDUI());
        writeStr(t.getMedicamento());
        writeStr(t.getDosis());
        writeStr(t.getFrecuencia());
        writeStr(t.getDuracion());
        writeStr(t.getObservaciones());
        writeStr(t.getEstado());
    }
    archivo.close();
    if (encontrado) cout << "Tratamiento editado exitosamente.";
    else cout << "Tratamiento no encontrado.";
}

void eliminarTratamientoEnArchivo(const string& dui, const string& med) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    bool encontrado = false;
    ofstream archivo("./output/tratamientos.dat", ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para eliminar.";
        return;
    }
    for (auto& t : lista) {
        if (t.coincideCon(dui, med)) {
            encontrado = true;
            t.eliminar();
        }
    }
    for (const auto& t : lista) {
        auto writeStr = [&](const string& str) {
            size_t len = str.size();
            archivo.write((char*)&len, sizeof(size_t));
            archivo.write(str.c_str(), len);
        };
        writeStr(t.getDUI());
        writeStr(t.getMedicamento());
        writeStr(t.getDosis());
        writeStr(t.getFrecuencia());
        writeStr(t.getDuracion());
        writeStr(t.getObservaciones());
        writeStr(t.getEstado());
    }
    archivo.close();
    if (encontrado) cout << "Tratamiento marcado como eliminado.";
    else cout << "Tratamiento no encontrado.";
}

vector<Tratamiento> cargarTratamientosDesdeArchivo() {
    ifstream archivo("./output/tratamientos.dat", ios::binary);
    vector<Tratamiento> lista;
    if (!archivo.is_open()) return lista;

    auto readStr = [&](string& str) {
        size_t len;
        archivo.read((char*)&len, sizeof(size_t));
        str.resize(len);
        archivo.read(&str[0], len);
    };

    while (archivo.peek() != EOF) {
        string dui, med, dos, frec, dur, obs, est;
        readStr(dui);
        readStr(med);
        readStr(dos);
        readStr(frec);
        readStr(dur);
        readStr(obs);
        readStr(est);
        lista.emplace_back(dui, med, dos, frec, dur, obs, est);
    }
    archivo.close();
    return lista;
}

void mostrarTratamientosPorDUI(const string& dui) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    cout << "\n=== Tratamientos para paciente: " << dui << " ===\n";
    if (lista.empty()) cout << "Tratamiento no encontrado.";
    else {
        for (const auto& t : lista) {
            if (t.getDUI() == dui && t.getEstado() != "Eliminado") {
                t.mostrar();
            }
        }
    }
}