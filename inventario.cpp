#include "modelos/Inventario.h"
#include "utils/Validaciones.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

// =================== Implementación de la Clase Lote ===================

// Constructor por defecto
Lote::Lote() : cantidad(0), precioUnitario(0.0) {}

// Constructor parametrizado
Lote::Lote(int cantidad, const std::string& fechaVencimiento, 
           float precioUnitario, const std::string& fechaIngreso,
           const std::string& numeroLote)
    : cantidad(cantidad), fechaVencimiento(fechaVencimiento),
      precioUnitario(precioUnitario), fechaIngreso(fechaIngreso),
      numeroLote(numeroLote) {}

// --- Getters ---
int Lote::getCantidad() const { return cantidad; }
std::string Lote::getFechaVencimiento() const { return fechaVencimiento; }
std::string Lote::getFechaIngreso() const { return fechaIngreso; }
float Lote::getPrecioUnitario() const { return precioUnitario; }
std::string Lote::getNumeroLote() const { return numeroLote; }

// --- Setters ---
void Lote::setCantidad(int cantidad) { this->cantidad = cantidad; }
void Lote::setFechaVencimiento(const std::string& fecha) { this->fechaVencimiento = fecha; }
void Lote::setFechaIngreso(const std::string& fecha) { this->fechaIngreso = fecha; }
void Lote::setPrecioUnitario(float precio) { this->precioUnitario = precio; }
void Lote::setNumeroLote(const std::string& lote) { this->numeroLote = lote; }

// Verifica si el lote está vencido usando utilidades de validación
bool Lote::estaVencido() const {
    if (fechaVencimiento.empty()) return false; // Si no hay fecha, no está vencido
    return Validaciones::estaVencido(fechaVencimiento);
}

// =================== Implementación de la Clase Inventario ===================

// Constructor por defecto
Inventario::Inventario() : nombre(""), codigo(""), unidad(""), presentacion("") {}

// Constructor parametrizado
Inventario::Inventario(const std::string& nombre, const std::string& codigo, 
                       const std::string& unidad, const std::string& presentacion)
    : nombre(nombre), codigo(codigo), unidad(unidad), presentacion(presentacion) {}

// --- Getters ---
std::string Inventario::getNombre() const { return nombre; }
std::string Inventario::getCodigo() const { return codigo; }
std::string Inventario::getUnidad() const { return unidad; }
std::string Inventario::getPresentacion() const { return presentacion; }
std::vector<Lote>& Inventario::getLotes() { return lotes; }
const std::vector<Lote>& Inventario::getLotes() const { return lotes; }

// --- Setters ---
void Inventario::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Inventario::setCodigo(const std::string& codigo) { this->codigo = codigo; }
void Inventario::setUnidad(const std::string& unidad) { this->unidad = unidad; }
void Inventario::setPresentacion(const std::string& presentacion) { this->presentacion = presentacion; }

// Agrega un nuevo lote al inventario
void Inventario::agregarLote(const Lote& lote) {
    lotes.push_back(lote);
}

// Calcula el stock total sumando las cantidades de todos los lotes
int Inventario::getStockTotal() const {
    int total = 0;
    for (const auto& lote : lotes) {
        total += lote.getCantidad();
    }
    return total;
}

// Busca un lote por su número de identificación
Lote* Inventario::buscarLotePorNumero(const std::string& numeroLote) {
    for (auto& lote : lotes) {
        if (lote.getNumeroLote() == numeroLote) {
            return &lote; // Devuelve puntero al lote encontrado
        }
    }
    return nullptr; // Lote no encontrado
}

// Descuenta cantidad específica de un lote identificado por su número
bool Inventario::descontarDeLote(const std::string& numeroLote, int cantidad) {
    Lote* lote = buscarLotePorNumero(numeroLote);
    if (!lote) return false; // Lote no encontrado
    
    // Verifica que haya suficiente stock en el lote
    if (lote->getCantidad() >= cantidad) {
        lote->setCantidad(lote->getCantidad() - cantidad);
        return true;
    }
    return false; // Stock insuficiente
}

// Implementa política PEPS (Primero en Entrar, Primero en Salir)
bool Inventario::descontarPEPS(int cantidad) {
    // Ordenar por fecha de ingreso (más antiguos primero)
    std::sort(lotes.begin(), lotes.end(), [](const Lote& a, const Lote& b) {
        return Validaciones::compararFechas(a.getFechaIngreso(), b.getFechaIngreso()) < 0;
    });
    
    int cantidadRestante = cantidad;
    // Itera por los lotes en orden de antigüedad
    for (auto& lote : lotes) {
        if (cantidadRestante <= 0) break; // Se completó el descuento
        
        int disponible = lote.getCantidad();
        if (disponible > 0) {
            // Calcula cuánto descontar de este lote
            int aDescontar = std::min(cantidadRestante, disponible);
            lote.setCantidad(disponible - aDescontar);
            cantidadRestante -= aDescontar;
        }
    }
    
    return cantidadRestante == 0; // True si se descontó todo
}

// Implementa política UEPS (Último en Entrar, Primero en Salir)
bool Inventario::descontarUEPS(int cantidad) {
    // Ordenar por fecha de ingreso (más recientes primero)
    std::sort(lotes.begin(), lotes.end(), [](const Lote& a, const Lote& b) {
        return Validaciones::compararFechas(a.getFechaIngreso(), b.getFechaIngreso()) > 0;
    });
    
    int cantidadRestante = cantidad;
    // Itera por los lotes en orden inverso (más recientes primero)
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

// Muestra todos los lotes en formato de tabla
void Inventario::mostrarLotes() const {
    // Encabezado de la tabla
    std::cout << "\nLotes para: " << nombre << " (" << codigo << ")\n";
    std::cout << std::left << std::setw(10) << "Lote"
              << std::setw(10) << "Cantidad"
              << std::setw(15) << "Precio"
              << std::setw(15) << "Ingreso"
              << std::setw(15) << "Vencimiento"
              << std::setw(10) << "Vencido" << "\n";
    std::cout << std::string(75, '-') << "\n";

    // Detalle de cada lote
    for (const auto& lote : lotes) {
        std::cout << std::left << std::setw(10) << lote.getNumeroLote()
                  << std::setw(10) << lote.getCantidad()
                  << std::setw(15) << std::fixed << std::setprecision(2) << lote.getPrecioUnitario()
                  << std::setw(15) << lote.getFechaIngreso()
                  << std::setw(15) << lote.getFechaVencimiento()
                  << std::setw(10) << (lote.estaVencido() ? "Sí" : "No") << "\n";
    }
}