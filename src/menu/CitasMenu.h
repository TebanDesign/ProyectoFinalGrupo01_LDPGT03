#pragma once
#include <iostream>

class CitasMenu {
private:
    void mostrarMenu();
    void agregarCita();
    void editarCita();
    void listarCitas();

public:
    CitasMenu();
    void ejecutar();
};

