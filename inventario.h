#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <functional>


// Estructura para representar un medicamento
struct Medicamento {
    std::string nombre;
    int cantidad;
    float precio;
};

// Declaraciones de funciones

// Agrega un nuevo medicamento al archivo
void agregarMedicamento();

// Muestra todos los medicamentos en inventario
void mostrarInventario();

// Edita los datos de un medicamento existente
void editarMedicamento();

// Busca un medicamento por nombre y guarda el resultado en la estructura proporcionada
bool buscarMedicamento(const std::string& nombreBuscado, Medicamento& encontrado);

// Descuenta unidades de un medicamento si hay suficiente stock
bool descontarMedicamento(const std::string& nombreBuscado, int cantidadSolicitada);

// Aumenta el stock de un medicamento
bool agregarStock(const std::string& nombreBuscado, int cantidadAgregar);

// Valida el nombre de un medicamento
bool validarNombre(const std::string& nombre);

// Limpia el buffer de entrada para evitar errores al leer
void limpiarBuffer();

/*

// Procesa un medicamento por nombre con una acción personalizada (versión simplificada)
bool procesarMedicamentoPorNombre(const std::string& nombreBuscado, std::function<void(std::string&, int&, float&, size_t)> accion);

// Versión extendida usada en funciones como editar y descontar
bool procesarMedicamentoPorNombre(const std::string& nombreBuscado, std::function<void(std::fstream&, std::streampos, std::string&, int&, float&, size_t)> accion);

*/

bool procesarMedicamentoPorNombre(const std::string& nombreBuscado, std::function<void(std::fstream&, std::streampos, std::string&, int&, float&, size_t)> accion);

#endif