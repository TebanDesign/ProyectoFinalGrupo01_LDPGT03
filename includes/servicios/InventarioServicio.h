#ifndef INVENTARIOSERVICIO_H
#define INVENTARIOSERVICIO_H

#include <string>
#include <vector>
#include "Inventario.h"
#include "utils/fileSistem.h"  // Incluir el nuevo sistema de archivos

class InventarioServicio {
private:
    std::string rutaArchivo;  // Almacenará la ruta completa organizada
    std::vector<Inventario> inventarios;


public:
    // Constructor ahora recibe solo el nombre base del archivo
    InventarioServicio(const std::string& nombreArchivo);

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
    void aumentarStock();
    void aumentarStock(const std::string& nombreMedicamento);  // Cambiado a pública
    void descontarMedicamento();  // Nueva función sin parámetros
    bool descontarMedicamento(const std::string& medicamento, int cantidad);

    // Nuevos métodos para gestión de archivos
    void cargarDesdeArchivo();
    void guardarEnArchivo() const;
};

#endif