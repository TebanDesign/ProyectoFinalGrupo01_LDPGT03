#include "modelos/Inventario.h"
#include "utils/Validaciones.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// =================== Clase Lote ===================

Lote::Lote() : cantidad(0), precioUnitario(0.0) {}

Lote::Lote(int cantidad, const std::string& fechaVencimiento, 
           float precioUnitario, const std::string& fechaIngreso)
    : cantidad(cantidad), fechaVencimiento(fechaVencimiento),
      precioUnitario(precioUnitario), fechaIngreso(fechaIngreso) {}

int Lote::getCantidad() const { return cantidad; }
std::string Lote::getFechaVencimiento() const { return fechaVencimiento; }
std::string Lote::getFechaIngreso() const { return fechaIngreso; }
float Lote::getPrecioUnitario() const { return precioUnitario; }

void Lote::setCantidad(int cantidad) { this->cantidad = cantidad; }
void Lote::setFechaVencimiento(const std::string& fecha) { this->fechaVencimiento = fecha; }
void Lote::setFechaIngreso(const std::string& fecha) { this->fechaIngreso = fecha; }
void Lote::setPrecioUnitario(float precio) { this->precioUnitario = precio; }

bool Lote::estaVencido() const {
    if (fechaVencimiento.empty()) return false;
    
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int diaActual = now->tm_mday;
    int mesActual = now->tm_mon + 1;
    int anioActual = now->tm_year + 1900;

    // Asumiendo formato DD/MM/AAAA
    int diaLote = std::stoi(fechaVencimiento.substr(0, 2));
    int mesLote = std::stoi(fechaVencimiento.substr(3, 2));
    int anioLote = std::stoi(fechaVencimiento.substr(6, 4));

    if (anioLote < anioActual) return true;
    if (anioLote == anioActual && mesLote < mesActual) return true;
    if (anioLote == anioActual && mesLote == mesActual && diaLote < diaActual) return true;

    return false;
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

void Inventario::mostrarLotes() const {
    std::cout << "\nLotes para: " << nombre << " (" << codigo << ")\n";
    std::cout << std::left << std::setw(15) << "Cantidad"
              << std::setw(15) << "Precio"
              << std::setw(15) << "Ingreso"
              << std::setw(15) << "Vencimiento"
              << std::setw(10) << "Vencido" << "\n";
    std::cout << std::string(70, '-') << "\n";

    for (const auto& lote : lotes) {
        std::cout << std::left << std::setw(15) << lote.getCantidad()
                  << std::setw(15) << std::fixed << std::setprecision(2) << lote.getPrecioUnitario()
                  << std::setw(15) << lote.getFechaIngreso()
                  << std::setw(15) << lote.getFechaVencimiento()
                  << std::setw(10) << (lote.estaVencido() ? "Sí" : "No") << "\n";
    }
}