#ifndef CITASMENU_H
#define CITASMENU_H

#include "servicios/CitaServicio.h"

class CitasMenu {
private:
    CitaServicio servicio;

    void mostrarMenu();
    void mostrarBanner();
    void agregarCita();
    void listarCitas();
    void editarCitaMenu();
    void buscarCitas();

public:
    CitasMenu();
    void ejecutar();
};

#endif