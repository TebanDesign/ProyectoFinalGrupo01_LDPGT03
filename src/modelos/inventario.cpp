#include "modelos/Inventario.h"
#include "utils/Validaciones.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

// =================== Clase Lote ===================

Lote::Lote() : cantidad(0), precioUnitario(0.0) {}

Lote::Lote(int cantidad, const std::string& fechaVencimiento, 
           float precioUnitario, const std::string& fechaIngreso,
           const std::string& numeroLote)
    : cantidad(cantidad), fechaVencimiento(fechaVencimiento),
      precioUnitario(precioUnitario), fechaIngreso(fechaIngreso),
      numeroLote(numeroLote) {}

int Lote::getCantidad() const { return cantidad; }
std::string Lote::getFechaVencimiento() const { return fechaVencimiento; }
std::string Lote::getFechaIngreso() const { return fechaIngreso; }
float Lote::getPrecioUnitario() const { return precioUnitario; }
std::string Lote::getNumeroLote() const { return numeroLote; }

void Lote::setCantidad(int cantidad) { this->cantidad = cantidad; }
void Lote::setFechaVencimiento(const std::string& fecha) { this->fechaVencimiento = fecha; }
void Lote::setFechaIngreso(const std::string& fecha) { this->fechaIngreso = fecha; }
void Lote::setPrecioUnitario(float precio) { this->precioUnitario = precio; }
void Lote::setNumeroLote(const std::string& lote) { this->numeroLote = lote; }

bool Lote::estaVencido() const {
    if (fechaVencimiento.empty()) return false;
    return Validaciones::estaVencido(fechaVencimiento);
}

// =================== Clase Inventario ===================

Inventario::Inventario() : nombre(""), codigo(""), unidad(""), presentacion("") {}

Inventario::Inventario(const std::string& nombre, const std::string& codigo, 
                       const std::string& unidad, const std::string& presentacion)
    : nombre(nombre), codigo(codigo), unidad(unidad), presentacion(presentacion) {}

std::string Inventario::getNombre() const { return nombre; }
std::string Inventario::getCodigo() const { return codigo; }
std::string Inventario::getUnidad() const { return unidad; }
std::string Inventario::getPresentacion() const { return presentacion; }
std::vector<Lote>& Inventario::getLotes() { return lotes; }
const std::vector<Lote>& Inventario::getLotes() const { return lotes; }

void Inventario::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Inventario::setCodigo(const std::string& codigo) { this->codigo = codigo; }
void Inventario::setUnidad(const std::string& unidad) { this->unidad = unidad; }
void Inventario::setPresentacion(const std::string& presentacion) { this->presentacion = presentacion; }

void Inventario::agregarLote(const Lote& lote) {
    lotes.push_back(lote);
}

int Inventario::getStockTotal() const {
    int total = 0;
    for (const auto& lote : lotes) {
        total += lote.getCantidad();
    }
    return total;
}

Lote* Inventario::buscarLotePorNumero(const std::string& numeroLote) {
    for (auto& lote : lotes) {
        if (lote.getNumeroLote() == numeroLote) {
            return &lote;
        }
    }
    return nullptr;
}

bool Inventario::descontarDeLote(const std::string& numeroLote, int cantidad) {
    Lote* lote = buscarLotePorNumero(numeroLote);
    if (!lote) return false;
    
    if (lote->getCantidad() >= cantidad) {
        lote->setCantidad(lote->getCantidad() - cantidad);
        return true;
    }
    return false;
}

bool Inventario::descontarPEPS(int cantidad) {
    // Ordenar por fecha de ingreso (más antiguos primero)
    std::sort(lotes.begin(), lotes.end(), [](const Lote& a, const Lote& b) {
        return Validaciones::compararFechas(a.getFechaIngreso(), b.getFechaIngreso()) < 0;
    });
    
    int cantidadRestante = cantidad;
    for (auto& lote : lotes) {
        if (cantidadRestante <= 0) break;
        
        int disponible = lote.getCantidad();
        if (disponible > 0) {
            int aDescontar = std::min(cantidadRestante, disponible);
            lote.setCantidad(disponible - aDescontar);
            cantidadRestante -= aDescontar;
        }
    }
    
    return cantidadRestante == 0;
}

bool Inventario::descontarUEPS(int cantidad) {
    // Ordenar por fecha de ingreso (más recientes primero)
    std::sort(lotes.begin(), lotes.end(), [](const Lote& a, const Lote& b) {
        return Validaciones::compararFechas(a.getFechaIngreso(), b.getFechaIngreso()) > 0;
    });
    
    int cantidadRestante = cantidad;
    for (auto& lote : lotes) {
        if (cantidadRestante <= 0) break;
        
        int disponible = lote.getCantidad();
        if (disponible > 0) {
            int aDescontar = std::min(cantidadRestante, disponible);
            lote.setCantidad(disponible - aDescontar);
            cantidadRestante -= aDescontar;
        }
    }
    
    return cantidadRestante == 0;
}

void Inventario::mostrarLotes() const {
    std::cout << "\nLotes para: " << nombre << " (" << codigo << ")\n";
    std::cout << std::left << std::setw(10) << "Lote"
              << std::setw(10) << "Cantidad"
              << std::setw(15) << "Precio"
              << std::setw(15) << "Ingreso"
              << std::setw(15) << "Vencimiento"
              << std::setw(10) << "Vencido" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& lote : lotes) {
        std::cout << std::left << std::setw(10) << lote.getNumeroLote()
                  << std::setw(10) << lote.getCantidad()
                  << std::setw(15) << std::fixed << std::setprecision(2) << lote.getPrecioUnitario()
                  << std::setw(15) << lote.getFechaIngreso()
                  << std::setw(15) << lote.getFechaVencimiento()
                  << std::setw(10) << (lote.estaVencido() ? "Sí" : "No") << "\n";
    }
}