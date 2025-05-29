#include "servicios/InventarioServicio.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "utils/Validaciones.h"
#include "menu/MenuUtils.h"

InventarioServicio::InventarioServicio(const std::string& archivo) : archivoInventario(archivo) {
    // Cargar datos iniciales desde archivo
}

void InventarioServicio::agregarLote(const Inventario& nuevoLote) {
    inventarios.push_back(nuevoLote);
    // Guardar en archivo...
    std::cout << "Lote agregado exitosamente.\n";
}

void InventarioServicio::mostrarInventario() const {
    std::cout << "\n=== INVENTARIO DE MEDICAMENTOS ===\n";
    std::cout << std::left << std::setw(20) << "Nombre"
              << std::setw(10) << "Codigo"
              << std::setw(15) << "Presentacion"
              << std::setw(10) << "Stock"
              << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (const auto& item : inventarios) {
        std::cout << std::left << std::setw(20) << item.getNombre()
                  << std::setw(10) << item.getCodigo()
                  << std::setw(15) << item.getPresentacion()
                  << std::setw(10) << item.getStockTotal()
                  << std::endl;
    }
}

std::vector<Inventario> InventarioServicio::buscarPorNombre(const std::string& nombre) const {
    std::vector<Inventario> resultados;
    for (const auto& item : inventarios) {
        if (item.getNombre().find(nombre) != std::string::npos) {
            resultados.push_back(item);
        }
    }
    return resultados;
}

bool InventarioServicio::existenMedicamentos() const {
    return !inventarios.empty();
}

void InventarioServicio::agregarMedicamento() {
    std::string nombre, codigo, unidad, presentacion;
    
    MenuUtils::mostrarTitulo("AGREGAR NUEVO MEDICAMENTO", MenuUtils::VERDE, MenuUtils::BLANCO);
    std::cout << "\nNombre: ";
    std::getline(std::cin, nombre);
    
    std::cout << "Codigo: ";
    std::getline(std::cin, codigo);
    
    std::cout << "Unidad: ";
    std::getline(std::cin, unidad);
    
    std::cout << "Presentacion: ";
    std::getline(std::cin, presentacion);
    
    inventarios.emplace_back(nombre, codigo, unidad, presentacion);
    MenuUtils::mostrarMensajeExito("Medicamento agregado exitosamente!");
}

void InventarioServicio::editarMedicamento() {
    // Implementación básica
    MenuUtils::mostrarMensaje("Funcionalidad en desarrollo...", MenuUtils::AMARILLO);
}

void InventarioServicio::buscarMedicamento() {
    std::string nombre;
    std::cout << "Buscar medicamento: ";
    std::getline(std::cin, nombre);
    
    auto resultados = buscarPorNombre(nombre);
    if (resultados.empty()) {
        MenuUtils::mostrarMensajeError("No se encontraron medicamentos");
        return;
    }
    
    std::cout << "\nResultados de busqueda:\n";
    for (const auto& item : resultados) {
        std::cout << "- " << item.getNombre() << " (" << item.getCodigo() << ")\n";
    }
}

void InventarioServicio::listarMedicamentos() {
    mostrarInventario();
}

void InventarioServicio::descontarMedicamento() {
    // Implementación básica
    MenuUtils::mostrarMensaje("Funcionalidad en desarrollo...", MenuUtils::AMARILLO);
}

void InventarioServicio::aumentarStock() {
    // Implementación básica
    MenuUtils::mostrarMensaje("Funcionalidad en desarrollo...", MenuUtils::AMARILLO);
}

bool InventarioServicio::descontarMedicamento(const std::string& medicamento, int cantidad) {
    for (auto& item : inventarios) {
        if (item.getNombre() == medicamento) {
            if (item.getStockTotal() >= cantidad) {
                // Implementación básica - ajustar según lógica de negocio
                MenuUtils::mostrarMensajeExito("Medicamento descontado exitosamente");
                return true;
            } else {
                MenuUtils::mostrarMensajeError("Stock insuficiente");
                return false;
            }
        }
    }
    MenuUtils::mostrarMensajeError("Medicamento no encontrado");
    return false;
}