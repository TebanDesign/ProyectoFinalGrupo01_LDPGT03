#ifndef INVENTARIOSERVICIO_H
#define INVENTARIOSERVICIO_H

#include <string>
#include <vector>
#include "Inventario.h"

class InventarioServicio {
private:
    std::string archivoInventario;
    std::vector<Inventario> inventarios;

public:
    InventarioServicio(const std::string& archivo);

    // Métodos básicos
    void agregarLote(const Inventario& nuevoLote);
    void mostrarInventario() const;
    std::vector<Inventario> buscarPorNombre(const std::string& nombreBuscado) const;

    // Métodos para el menú
    bool existenMedicamentos() const;
    void agregarMedicamento();
    void editarMedicamento();
    void buscarMedicamento();
    void listarMedicamentos();
    void descontarMedicamento();
    void aumentarStock();
    
    // Función añadida para tratamiento
    bool descontarMedicamento(const std::string& medicamento, int cantidad);
};

#endif