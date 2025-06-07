#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <vector>
#include <algorithm>
#include "utils/Validaciones.h"

// Clase que representa un lote específico de un producto en inventario
class Lote {
private:
    int cantidad;                   // Unidades disponibles en el lote
    std::string fechaVencimiento;   // Fecha de caducidad 
    std::string fechaIngreso;       // Fecha de ingreso al inventario
    float precioUnitario;           // Precio por unidad del producto
    std::string numeroLote;         // Identificador único del lote

public:
    // Constructores
    Lote();  // Constructor por defecto
    Lote(int cantidad, const std::string& fechaVencimiento, 
         float precioUnitario, const std::string& fechaIngreso,
         const std::string& numeroLote);  // Constructor parametrizado

    // === Getters (accesores) ===
    int getCantidad() const;                  // Obtiene la cantidad disponible
    std::string getFechaVencimiento() const;  // Obtiene fecha de vencimiento
    std::string getFechaIngreso() const;      // Obtiene fecha de ingreso
    float getPrecioUnitario() const;          // Obtiene precio por unidad
    std::string getNumeroLote() const;        // Obtiene número de lote
    bool estaVencido() const;                 // Verifica si el lote está vencido (comparando con fecha actual)

    // === Setters (mutadores) ===
    void setCantidad(int cantidad);                     // Actualiza la cantidad
    void setFechaVencimiento(const std::string& fecha); // Modifica fecha vencimiento
    void setFechaIngreso(const std::string& fecha);     // Modifica fecha ingreso
    void setPrecioUnitario(float precio);               // Actualiza precio unitario
    void setNumeroLote(const std::string& lote);        // Cambia número de lote
};

// Clase que representa un producto en el inventario con sus lotes asociados
class Inventario {
private:
    std::string nombre;         // Nombre del producto (ej: "Paracetamol")
    std::string codigo;         // Código único identificador (ej: "PCTM-500")
    std::string unidad;         // Unidad de medida (ej: "mg", "ml", "unidades")
    std::string presentacion;   // Formato de presentación (ej: "Tabletas", "Jarabe")
    std::vector<Lote> lotes;    // Lista de lotes asociados al producto

public:
    // Constructores
    Inventario();  // Constructor por defecto
    Inventario(const std::string& nombre, const std::string& codigo, 
               const std::string& unidad, const std::string& presentacion);  // Constructor parametrizado

    // === Getters (accesores) ===
    std::string getNombre() const;         // Obtiene nombre del producto
    std::string getCodigo() const;         // Obtiene código identificador
    std::string getUnidad() const;         // Obtiene unidad de medida
    std::string getPresentacion() const;   // Obtiene presentación
    std::vector<Lote>& getLotes();         // Referencia mutable a los lotes (para modificaciones)
    const std::vector<Lote>& getLotes() const; // Referencia constante (solo lectura)
    int getStockTotal() const;             // Calcula stock sumando todos los lotes
    Lote* buscarLotePorNumero(const std::string& numeroLote); // Busca lote por su número (devuelve nullptr si no existe)

    // === Setters (mutadores) ===
    void setNombre(const std::string& nombre);        // Actualiza nombre
    void setCodigo(const std::string& codigo);        // Actualiza código
    void setUnidad(const std::string& unidad);        // Cambia unidad de medida
    void setPresentacion(const std::string& presentacion); // Modifica presentación

    // === Operaciones de inventario ===
    void agregarLote(const Lote& lote);  // Añade un nuevo lote al producto
    bool descontarDeLote(const std::string& numeroLote, int cantidad); // Reduce cantidad de un lote específico
    void mostrarLotes() const;  // Muestra información de todos los lotes (para interfaz)
    
    // Políticas de gestión de inventario
    bool descontarPEPS(int cantidad);  // Primero en Entrar, Primero en Salir
    bool descontarUEPS(int cantidad);  // Último en Entrar, Primero en Salir
};

#endif