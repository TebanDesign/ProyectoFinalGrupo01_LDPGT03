#ifndef CITA_MENU_H
#define CITA_MENU_H

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

#endif
