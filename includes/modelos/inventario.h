#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>

struct Medicamento {
    std::string nombre;
    int cantidad;
    float precio;
};

void agregarMedicamento();
void mostrarInventario();
void editarMedicamento();
bool buscarMedicamento(const std::string& nombre, Medicamento& encontrado);
bool descontarMedicamento(const std::string& nombre, int cantidadSolicitada);

#endif