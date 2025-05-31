// Descripción: Implementación de funciones para gestionar tratamientos

#include "tratamiento.h"
#include "inventario.h"
#include "utils/encriptador.h"
#include "servicios/PacienteServicio.h"
#include "servicios/InventarioServicio.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

// Función auxiliar para mostrar detalles de un medicamento
void mostrarDetalleMedicamento(InventarioServicio& inventarioServicio, const string& nombreMedicamento) {
    auto medicamentos = inventarioServicio.buscarPorNombre(nombreMedicamento);
    if (medicamentos.empty()) {
        cout << "  - No se encontró información del medicamento\n";
        return;
    }
    
    const Inventario& med = medicamentos[0];
    cout << "  - Medicamento: " << med.getNombre() 
         << " (" << med.getPresentacion() << ")\n";
    cout << "  - Stock total: " << med.getStockTotal() << " " << med.getUnidad() << "\n";
    cout << "  - Lotes disponibles:\n";
    
    for (const auto& lote : med.getLotes()) {
        cout << "    * Lote: " << lote.getNumeroLote()
             << " | Cant: " << lote.getCantidad()
             << " | Vence: " << lote.getFechaVencimiento()
             << (lote.estaVencido() ? " (VENCIDO)" : "") << "\n";
    }
}

void registrarTratamiento(InventarioServicio& inventarioServicio) {
    PacienteServicio pacienteServicio("pacientes.dat");
    Tratamiento t;

    cout << "\n=== REGISTRAR NUEVO TRATAMIENTO ===\n";
    
    // Validar paciente
    bool existePaciente = false;
    do {
        cout << "DUI del paciente: ";
        getline(cin, t.duiPaciente);
        
        // Verificar si el paciente existe
        existePaciente = !pacienteServicio.buscarPorDui(t.duiPaciente).getDui().empty();
        
        if (!existePaciente) {
            cout << "  [ERROR] Paciente no encontrado. Intente con un DUI válido.\n";
        }
    } while (!existePaciente);

    // Validar medicamento
    bool medicamentoValido = false;
    do {
        cout << "Medicamento: ";
        getline(cin, t.medicamento);
        
        auto resultados = inventarioServicio.buscarPorNombre(t.medicamento);
        medicamentoValido = !resultados.empty();
        
        if (!medicamentoValido) {
            cout << "  [ERROR] Medicamento no encontrado. Intente nuevamente.\n";
        } else {
            // Mostrar detalles del medicamento
            mostrarDetalleMedicamento(inventarioServicio, t.medicamento);
        }
    } while (!medicamentoValido);

    // Validar dosis
    bool dosisValida = false;
    int cantidadADescontar = 0;
    do {
        cout << "Dosis (ej: 2): ";
        getline(cin, t.dosis);
        
        try {
            cantidadADescontar = stoi(t.dosis);
            if (cantidadADescontar > 0) {
                dosisValida = true;
            } else {
                cout << "  [ERROR] La dosis debe ser un número positivo.\n";
            }
        } catch (...) {
            cout << "  [ERROR] La dosis debe ser un número válido.\n";
        }
    } while (!dosisValida);

    cout << "Período (ej: Cada 8 horas por 7 días): ";
    getline(cin, t.periodo);

    // Descontar medicamento del inventario usando política PEPS
    cout << "\n[INFO] Descontando " << cantidadADescontar 
         << " unidades de '" << t.medicamento << "'...\n";
    
    if (!inventarioServicio.descontarMedicamento(t.medicamento, cantidadADescontar)) {
        cout << "  [ERROR] No se pudo completar el descuento. Verifique el stock disponible.\n";
        return;
    }
    
    cout << "  [ÉXITO] Medicamento descontado correctamente del inventario.\n";

    // Guardar tratamiento en archivo binario
    ofstream archivo("tratamientos.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        string dosisCifrada = encriptar(t.dosis);

        // Escribir longitudes y datos
        auto escribirCampo = [&archivo](const string& campo) {
            size_t len = campo.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
            archivo.write(campo.c_str(), len);
        };
        
        escribirCampo(t.duiPaciente);
        escribirCampo(t.medicamento);
        escribirCampo(dosisCifrada);
        escribirCampo(t.periodo);

        archivo.close();
        cout << "\n[ÉXITO] Tratamiento registrado exitosamente.\n";
    } else {
        cerr << "  [ERROR] No se pudo abrir el archivo de tratamientos.\n";
    }
}

void mostrarTratamientos() {
    ifstream archivo("tratamientos.dat", ios::binary);
    if (!archivo.is_open()) {
        cerr << "  [ERROR] No se pudo abrir el archivo de tratamientos.\n";
        return;
    }

    cout << "\n=== LISTA DE TRATAMIENTOS REGISTRADOS ===\n";
    
    // Función para leer campos
    auto leerCampo = [&archivo]() -> string {
        size_t len = 0;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        
        if (archivo.eof()) return "";
        
        string campo(len, ' ');
        archivo.read(&campo[0], len);
        return campo;
    };

    int contador = 0;
    while (true) {
        string dui = leerCampo();
        if (dui.empty()) break;
        
        string medicamento = leerCampo();
        string dosisCifrada = leerCampo();
        string periodo = leerCampo();
        
        cout << "\nTratamiento #" << ++contador << "\n";
        cout << "---------------------------------\n";
        cout << "Paciente DUI: " << dui << "\n";
        cout << "Medicamento: " << medicamento << "\n";
        cout << "Dosis: " << desencriptar(dosisCifrada) << "\n";
        cout << "Período: " << periodo << "\n";
    }
    
    if (contador == 0) {
        cout << "  No hay tratamientos registrados.\n";
    } else {
        cout << "\nTotal de tratamientos: " << contador << "\n";
    }
    
    archivo.close();
}

void editarTratamiento(InventarioServicio& inventarioServicio) {
    cout << "\n=== EDITAR TRATAMIENTO ===\n";
    
    // Primero mostramos todos los tratamientos
    mostrarTratamientos();
    
    // Implementación pendiente
    cout << "\nFuncionalidad de edición de tratamientos estará disponible en la próxima versión.\n";
}

void menuTratamientos(InventarioServicio& inventarioServicio) {
    int opcion;
    do {
        cout << "\n=== MENÚ DE GESTIÓN DE TRATAMIENTOS ===\n";
        cout << "1. Registrar nuevo tratamiento\n";
        cout << "2. Mostrar todos los tratamientos\n";
        cout << "3. Editar tratamiento existente\n";
        cout << "0. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                registrarTratamiento(inventarioServicio);
                break;
            case 2:
                mostrarTratamientos();
                break;
            case 3:
                editarTratamiento(inventarioServicio);
                break;
            case 0:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }
        
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
        }
    } while (opcion != 0);
}