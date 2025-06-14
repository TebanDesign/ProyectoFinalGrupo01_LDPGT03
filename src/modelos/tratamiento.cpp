#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "modelos/tratamiento.h"
#include "menu/MenuUtils.h"
#include <ctime>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;

std::string obtenerRutaArchivoTratamientos() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    std::string ruta = "Data_ClinicaDentalRP/Tratamientos/" +
        std::to_string(year) + "/" +
        (month < 10 ? "0" : "") + std::to_string(month) + "/" +
        (day < 10 ? "0" : "") + std::to_string(day);

    fs::create_directories(ruta);  // Asegura que la carpeta exista
    return ruta + "/tratamientos.dat";
}

// Constructor
Tratamiento::Tratamiento(string dui, string med, string dos, string frec,
                         string dur, string obs, string est)
    : duiPaciente(dui), medicamento(med), dosis(dos), frecuencia(frec),
      duracion(dur), observaciones(obs), estado(est) {}

// Registro de nuevo tratamiento
void Tratamiento::registrar() {
    MenuUtils::mostrarTitulo("Registrar Tratamiento", MenuUtils::MAGENTA);
    cout << "DUI del paciente: "; getline(cin, duiPaciente);
    cout << "Medicamento: "; getline(cin, medicamento);
    cout << "Dosis: "; getline(cin, dosis);
    cout << "Frecuencia: "; getline(cin, frecuencia);
    cout << "Duración: "; getline(cin, duracion);
    cout << "Observaciones: "; getline(cin, observaciones);
    cout << "Estado: "; getline(cin, estado);

    ofstream archivo(obtenerRutaArchivoTratamientos(), ios::binary | ios::app);
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
        MenuUtils::mostrarMensaje("Tratamiento registrado correctamente.", MenuUtils::VERDE);
    } else {
        MenuUtils::mostrarMensajeError("No se pudo abrir el archivo para guardar el tratamiento.");
    }
}

// Mostrar tratamiento
void Tratamiento::mostrar() const {
    MenuUtils::mostrarSubtitulo("Tratamiento", MenuUtils::CYAN);
    cout << "DUI: " << duiPaciente
         << "\nMedicamento: " << medicamento
         << "\nDosis: " << dosis
         << "\nFrecuencia: " << frecuencia
         << "\nDuración: " << duracion
         << "\nObservaciones: " << observaciones
         << "\nEstado: " << estado << "\n----------------------\n";
}

// Editar tratamiento (solo si se ingresan nuevos valores)
void Tratamiento::editar() {
    string input;
    MenuUtils::mostrarTitulo("Editar Tratamiento", MenuUtils::MAGENTA);
    cout << "Nueva dosis (actual: " << dosis << "): ";
    getline(cin, input);
    if (!input.empty()) dosis = input;

    cout << "Nueva frecuencia (actual: " << frecuencia << "): ";
    getline(cin, input);
    if (!input.empty()) frecuencia = input;

    cout << "Nueva duración (actual: " << duracion << "): ";
    getline(cin, input);
    if (!input.empty()) duracion = input;

    cout << "Nuevas observaciones (actual: " << observaciones << "): ";
    getline(cin, input);
    if (!input.empty()) observaciones = input;

    cout << "Nuevo estado (actual: " << estado << "): ";
    getline(cin, input);
    if (!input.empty()) estado = input;
    MenuUtils::mostrarMensaje("Tratamiento actualizado.", MenuUtils::VERDE);
}

// Eliminar tratamiento (cambia el estado)
void Tratamiento::eliminar() {
    estado = "Eliminado";
    MenuUtils::mostrarMensaje("Tratamiento marcado como eliminado.", MenuUtils::ROJO);
}

// Comparar tratamiento por DUI y Medicamento
bool Tratamiento::coincideCon(const string& dui, const string& med) const {
    return duiPaciente == dui && medicamento == med;
}

// Getters
string Tratamiento::getDUI() const { return duiPaciente; }
string Tratamiento::getMedicamento() const { return medicamento; }
string Tratamiento::getEstado() const { return estado; }
string Tratamiento::getDosis() const { return dosis; }
string Tratamiento::getFrecuencia() const { return frecuencia; }
string Tratamiento::getDuracion() const { return duracion; }
string Tratamiento::getObservaciones() const { return observaciones; }

// Funciones de archivo

// Buscar y editar tratamiento en archivo
void editarTratamientoEnArchivo(const string& dui, const string& med) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    bool encontrado = false;
    ofstream archivo(obtenerRutaArchivoTratamientos(), ios::binary | ios::trunc);

    if (!archivo.is_open()) {
        MenuUtils::mostrarMensajeError("No se pudo abrir el archivo para editar.");
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
    if (encontrado) MenuUtils::mostrarMensaje("Tratamiento editado exitosamente.", MenuUtils::VERDE);
    else MenuUtils::mostrarMensaje("Tratamiento no encontrado.", MenuUtils::ROJO);
}

// Buscar y marcar como eliminado
void eliminarTratamientoEnArchivo(const string& dui, const string& med) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    bool encontrado = false;
    ofstream archivo(obtenerRutaArchivoTratamientos(), ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        MenuUtils::mostrarMensajeError("No se pudo abrir el archivo para eliminar.");
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
    if (encontrado) MenuUtils::mostrarMensaje("Tratamiento eliminado correctamente.", MenuUtils::ROJO);
    else MenuUtils::mostrarMensaje("Tratamiento no encontrado.", MenuUtils::ROJO);
}

// Leer tratamientos desde archivo
vector<Tratamiento> cargarTratamientosDesdeArchivo() {
    vector<Tratamiento> lista;

    for (const auto& p : fs::recursive_directory_iterator("Data_ClinicaDentalRP/Tratamientos")) {
        if (p.path().filename() == "tratamientos.dat") {
            ifstream archivo(p.path().string(), ios::binary);
            if (!archivo.is_open()) continue;

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
        }
    }

    return lista;
}

// Mostrar tratamientos activos por paciente
void mostrarTratamientosPorDUI(const string& dui) {
    vector<Tratamiento> lista = cargarTratamientosDesdeArchivo();
    MenuUtils::mostrarTitulo("Tratamientos del paciente: " + dui, MenuUtils::CYAN);
    for (const auto& t : lista) {
        if (t.getDUI() == dui && t.getEstado() != "Eliminado") {
            t.mostrar();
        }
    }
}