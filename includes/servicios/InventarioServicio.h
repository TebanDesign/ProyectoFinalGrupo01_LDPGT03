#ifndef INVENTARIOSERVICIO_H
#define INVENTARIOSERVICIO_H

#include <string>
#include <vector>
#include "Inventario.h"
#include "utils/fileSistem.h"  // Incluir el nuevo sistema de archivos

// Clase que gestiona la lógica de negocio y persistencia del inventario
class InventarioServicio {
private:
    std::string rutaArchivo;     // Ruta completa del archivo de almacenamiento
    std::vector<Inventario> inventarios;  // Datos de inventario en memoria

public:
    // Constructor - Recibe nombre base del archivo y construye la ruta completa
    // (La ruta completa se determina usando utilidades del sistema)
    InventarioServicio(const std::string& nombreArchivo);

    // === Operaciones básicas de inventario ===
    void agregarLote(const Inventario& nuevoLote);  // Añade un nuevo producto al inventario
    void mostrarInventario() const;                 // Muestra todo el inventario (consola)
    std::vector<Inventario> buscarPorNombre(const std::string& nombreBuscado) const; // Búsqueda por coincidencia parcial

        // === Operaciones para el menú de usuario ===
    bool existenMedicamentos() const;  // Verifica si hay productos registrados
    void agregarMedicamento();         // Flujo completo para añadir nuevo producto
    void editarMedicamento();          // Interfaz para modificar producto existente
    void buscarMedicamento();          // UI para búsqueda interactiva
    void listarMedicamentos();         // Muestra lista completa formateada
    void aumentarStock();              // Interfaz para incrementar stock
    
    // === Operaciones de gestión de stock ===
    void aumentarStock(const std::string& nombreMedicamento);  // Incrementa stock de producto específico
    void descontarMedicamento();       // Interfaz para reducir stock (menú)
    bool descontarMedicamento(const std::string& medicamento, int cantidad); // Lógica de reducción de stock

    // Nuevos métodos para gestión de archivos
    void cargarDesdeArchivo();
    void guardarEnArchivo() const;
};

#endif