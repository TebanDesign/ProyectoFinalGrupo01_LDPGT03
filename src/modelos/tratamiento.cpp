// Descripción: Implementación de funciones para gestionar tratamientos

#include "tratamiento.h"
#include "inventario.h"
#include "encriptador.h"
#include "PacienteServicio.h"
#include <iostream>
#include <fstream>
#include <limits>

// cambio en esta linea de codigo

using namespace std;

void registrarTratamiento() {
    PacienteServicio pacienteServicio("pacientes.dat");
    Tratamiento t;

    bool existePaciente = pacienteServicio.buscarPorDui(t.duiPaciente).getDui().empty();

    cout << "\n=== Registrar Tratamiento ===\n";
    do {
        cout << "DUI del paciente: ";
        getline(cin, t.duiPaciente);
        if (!existePaciente) {
            cout << "Paciente no encontrado. Intente con un DUI válido.\n";
        }
    } while (!existePaciente);

    cout << "Medicamento: ";
    getline(cin, t.medicamento);
    cout << "Dosis (ej: 2): ";
    getline(cin, t.dosis);
    cout << "Período: ";
    getline(cin, t.periodo);

    // Descontar medicamento del inventario
    int cantidadADescontar = stoi(t.dosis); // suponiendo que la dosis es un número
    cout << "[Depuración] Intentando descontar " << cantidadADescontar << " del medicamento '" << t.medicamento << "'...\n";
    if (!descontarMedicamento(t.medicamento, cantidadADescontar)) {
        cout << "Error: El medicamento no fue encontrado o no hay suficiente stock.\n";
    } else {
        cout << "[Depuración] Medicamento actualizado correctamente en inventario.\n";
    }

    ofstream archivo("tratamientos.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        string dosisCifrada = encriptar(t.dosis);

        size_t lenDui = t.duiPaciente.size();
        size_t lenMedicamento = t.medicamento.size();
        size_t lenDosis = dosisCifrada.size();
        size_t lenPeriodo = t.periodo.size();

        archivo.write((char*)&lenDui, sizeof(size_t));
        archivo.write(t.duiPaciente.c_str(), lenDui);
        archivo.write((char*)&lenMedicamento, sizeof(size_t));
        archivo.write(t.medicamento.c_str(), lenMedicamento);
        archivo.write((char*)&lenDosis, sizeof(size_t));
        archivo.write(dosisCifrada.c_str(), lenDosis);
        archivo.write((char*)&lenPeriodo, sizeof(size_t));
        archivo.write(t.periodo.c_str(), lenPeriodo);

        archivo.close();
        cout << "Tratamiento registrado exitosamente.\n";
    } else {
        cerr << "Error al abrir el archivo de tratamientos.\n";
    }
}

void mostrarTratamientos() {
    ifstream archivo("tratamientos.dat", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de tratamientos.\n";
        return;
    }

    cout << "\n=== Lista de Tratamientos ===\n";
    while (archivo.peek() != EOF) {
        size_t lenDui, lenMedicamento, lenDosis, lenPeriodo;
        archivo.read((char*)&lenDui, sizeof(size_t));
        if (archivo.eof()) break;
        string dui(lenDui, ' ');
        archivo.read(&dui[0], lenDui);

        archivo.read((char*)&lenMedicamento, sizeof(size_t));
        string medicamento(lenMedicamento, ' ');
        archivo.read(&medicamento[0], lenMedicamento);

        archivo.read((char*)&lenDosis, sizeof(size_t));
        string dosis(lenDosis, ' ');
        archivo.read(&dosis[0], lenDosis);

        archivo.read((char*)&lenPeriodo, sizeof(size_t));
        string periodo(lenPeriodo, ' ');
        archivo.read(&periodo[0], lenPeriodo);

        cout << "Paciente DUI: " << dui
             << "\nMedicamento: " << medicamento
             << "\nDosis: " << desencriptar(dosis)
             << "\nPeríodo: " << periodo
             << "\n----------------------\n";
    }
    archivo.close();
}

void editarTratamiento() {
    cout << "\nFuncionalidad de edición de tratamientos pendiente de implementación.\n";
}