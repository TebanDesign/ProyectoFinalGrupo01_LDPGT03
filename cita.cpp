// Descripción: Implementación de funciones para gestionar citas

#include "cita.h"
#include "encriptador.h"
#include "paciente.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

// Verifica si una cadena está vacía o solo contiene espacios
bool campoVacio(const string& str) {
    for (char ch : str) {
        if (!isspace(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return str.empty() || true;
}

// Verifica si ya existe una cita en la misma fecha y hora
bool citaExiste(const string& fecha, const string& hora) {
    ifstream bin("citas.dat", ios::binary);
    if (!bin.is_open()) return false;

    while (bin.peek() != EOF) {
        size_t lenDui, lenFecha, lenHora, lenMotivo;
        bin.read(reinterpret_cast<char*>(&lenDui), sizeof(size_t));
        bin.seekg(lenDui, ios::cur);
        bin.read(reinterpret_cast<char*>(&lenFecha), sizeof(size_t));
        string f(lenFecha, ' ');
        bin.read(&f[0], lenFecha);
        bin.read(reinterpret_cast<char*>(&lenHora), sizeof(size_t));
        string h(lenHora, ' ');
        bin.read(&h[0], lenHora);
        bin.read(reinterpret_cast<char*>(&lenMotivo), sizeof(size_t));
        bin.seekg(lenMotivo, ios::cur);

        if (f == fecha && h == hora) {
            bin.close();
            return true;
        }
    }
    bin.close();
    return false;
}

// Valida que la fecha ingresada no esté en el pasado
bool fechaEsValida(const string& fechaStr) {
    if (fechaStr.length() != 10) return false;

    int dia, mes, anio;
    if (sscanf(fechaStr.c_str(), "%d/%d/%d", &dia, &mes, &anio) != 3)
        return false;

    time_t t = time(nullptr);
    tm* hoy = localtime(&t);

    tm fechaIngresada = {};
    fechaIngresada.tm_mday = dia;
    fechaIngresada.tm_mon = mes - 1;
    fechaIngresada.tm_year = anio - 1900;

    time_t tiempoIngresado = mktime(&fechaIngresada);
    return difftime(tiempoIngresado, t) >= 0;
}

// Valida el formato de la hora (hh:mm)
bool horaEsValida(const string& horaStr) {
    if (horaStr.length() != 5 || horaStr[2] != ':') return false;
    int hora, minuto;
    if (sscanf(horaStr.c_str(), "%d:%d", &hora, &minuto) != 2) return false;
    return hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59;
}

void agendarCita() {
    Cita c;
    cout << "\n=== Agendar Cita ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Ingresar y validar DUI
    do {
        cout << "DUI del paciente: ";
        getline(cin, c.idPaciente);
        c.idPaciente.erase(remove(c.idPaciente.begin(), c.idPaciente.end(), ' '), c.idPaciente.end());

        if (campoVacio(c.idPaciente)) {
            cout << "El DUI no puede estar vacío.\n";
        }
    } while (campoVacio(c.idPaciente));

    // Verificar si el paciente está registrado
    if (!existeId(c.idPaciente)) {
        cout << "El paciente no está registrado. ¿Desea registrarlo? (s/n): ";
        string respuesta;
        getline(cin, respuesta);
        if (respuesta == "s" || respuesta == "S") {
            cout << "No puede registrar desde esta sección. Use la opción 1 para registrar pacientes.\n";
            return;
        } else {
            cout << "No se puede continuar sin registrar el paciente.\n";
            return;
        }
    }

    // Ingresar y validar fecha
    do {
        cout << "Fecha (dd/mm/aaaa): ";
        getline(cin, c.fecha);
        if (campoVacio(c.fecha)) {
            cout << "La fecha no puede estar vacía.\n";
        } else if (!fechaEsValida(c.fecha)) {
            cout << "La fecha no puede estar en el pasado o tiene un formato inválido.\n";
            c.fecha = "";
        }
    } while (campoVacio(c.fecha));

    // Ingresar y validar hora
    do {
        cout << "Hora (hh:mm): ";
        getline(cin, c.hora);
        if (campoVacio(c.hora)) {
            cout << "La hora no puede estar vacía.\n";
        } else if (!horaEsValida(c.hora)) {
            cout << "Formato de hora inválido. Debe ser hh:mm (24 horas).\n";
            c.hora = "";
        }
    } while (campoVacio(c.hora));

    // Verificar conflicto de citas
    if (citaExiste(c.fecha, c.hora)) {
        cout << "Ya existe una cita en esa fecha y hora.\n";
        return;
    }

    // Ingresar y validar motivo
    do {
        cout << "Motivo: ";
        getline(cin, c.motivo);
        if (campoVacio(c.motivo)) {
            cout << "El motivo no puede estar vacío.\n";
        }
    } while (campoVacio(c.motivo));

    ofstream bin("citas.dat", ios::binary | ios::app);
    if (!bin.is_open()) {
        cerr << "Error al guardar en archivo binario.\n";
        return;
    }

    string motivoCifrado = encriptar(c.motivo);
    size_t lenDui = c.idPaciente.size();
    size_t lenFecha = c.fecha.size();
    size_t lenHora = c.hora.size();
    size_t lenMotivo = motivoCifrado.size();

    bin.write(reinterpret_cast<const char*>(&lenDui), sizeof(size_t));
    bin.write(c.idPaciente.c_str(), lenDui);
    bin.write(reinterpret_cast<const char*>(&lenFecha), sizeof(size_t));
    bin.write(c.fecha.c_str(), lenFecha);
    bin.write(reinterpret_cast<const char*>(&lenHora), sizeof(size_t));
    bin.write(c.hora.c_str(), lenHora);
    bin.write(reinterpret_cast<const char*>(&lenMotivo), sizeof(size_t));
    bin.write(motivoCifrado.c_str(), lenMotivo);

    bin.close();
    cout << "Cita registrada exitosamente.\n";
}

void mostrarCitas() {
    ifstream bin("citas.dat", ios::binary);
    if (!bin.is_open()) {
        cerr << "No se pudo abrir el archivo de citas.\n";
        return;
    }

    cout << "\n=== Lista de Citas ===\n";
    while (bin.peek() != EOF) {
        size_t lenDui, lenFecha, lenHora, lenMotivo;
        bin.read(reinterpret_cast<char*>(&lenDui), sizeof(size_t));
        string dui(lenDui, ' ');
        bin.read(&dui[0], lenDui);

        bin.read(reinterpret_cast<char*>(&lenFecha), sizeof(size_t));
        string fecha(lenFecha, ' ');
        bin.read(&fecha[0], lenFecha);

        bin.read(reinterpret_cast<char*>(&lenHora), sizeof(size_t));
        string hora(lenHora, ' ');
        bin.read(&hora[0], lenHora);

        bin.read(reinterpret_cast<char*>(&lenMotivo), sizeof(size_t));
        string motivo(lenMotivo, ' ');
        bin.read(&motivo[0], lenMotivo);

        cout << "Paciente DUI: " << dui
             << "\nFecha: " << fecha
             << "\nHora: " << hora
             << "\nMotivo: " << desencriptar(motivo)
             << "\n----------------------\n";
    }
    bin.close();
}
