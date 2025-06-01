#pragma once

#include <string>

class TratamientoMenu {
public:
    void ejecutar();

private:
    void registrar();
    void buscar();
    void editar();
    void eliminar();
    void listarPorPaciente();  // reutiliza buscar
};