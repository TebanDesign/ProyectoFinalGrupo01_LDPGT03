// Descripción: Implementación de funciones para gestionar citas

#include "cita.h"
#include "encriptador.h"
#include "PacienteServicio.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void agendarCita() {
    PacienteServicio pacienteServicio("pacientes.dat");
    Cita c;
    // c.idPaciente => DUI paciente
    bool existePaciente = pacienteServicio.buscarPorDui(c.idPaciente).getDui().empty();

    cout << "\n=== Agendar Cita ===\n";
    do {
        cout << "DUI del paciente: ";
        getline(cin, c.idPaciente);
        if (existePaciente) {
            cout << "Paciente no encontrado. Intente con un DUI válido.\n";
        }
    } while (existePaciente);

    cout << "Fecha (dd/mm/aaaa): ";
    getline(cin, c.fecha);
    cout << "Hora (hh:mm): ";
    getline(cin, c.hora);
    cout << "Motivo: ";
    getline(cin, c.motivo);

    ofstream bin("citas.dat", ios::binary | ios::app);
    if (bin.is_open()) {
        string motivoCifrado = encriptar(c.motivo);
        size_t lenDui = c.idPaciente.size();
        size_t lenFecha = c.fecha.size();
        size_t lenHora = c.hora.size();
        size_t lenMotivo = motivoCifrado.size();

        bin.write((char*)&lenDui, sizeof(size_t));
        bin.write(c.idPaciente.c_str(), lenDui);
        bin.write((char*)&lenFecha, sizeof(size_t));
        bin.write(c.fecha.c_str(), lenFecha);
        bin.write((char*)&lenHora, sizeof(size_t));
        bin.write(c.hora.c_str(), lenHora);
        bin.write((char*)&lenMotivo, sizeof(size_t));
        bin.write(motivoCifrado.c_str(), lenMotivo);

        bin.close();
        cout << "Cita registrada exitosamente.\n";
    } else {
        cerr << "Error al guardar en archivo binario.\n";
    }
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
        bin.read((char*)&lenDui, sizeof(size_t));
        string dui(lenDui, ' ');
        bin.read(&dui[0], lenDui);

        bin.read((char*)&lenFecha, sizeof(size_t));
        string fecha(lenFecha, ' ');
        bin.read(&fecha[0], lenFecha);

        bin.read((char*)&lenHora, sizeof(size_t));
        string hora(lenHora, ' ');
        bin.read(&hora[0], lenHora);

        bin.read((char*)&lenMotivo, sizeof(size_t));
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
