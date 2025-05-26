#ifndef PACIENTE_MENU_H
#define PACIENTE_MENU_H

#include <iostream>
#include "PacienteServicio.h"

class PacienteMenu {
private:
    PacienteServicio& servicio; // referencia al servicio de pacientes

    void mostrarMenu();
    void agregarPaciente();
    void editarPaciente();
    void buscarPaciente();
    void listarPacientes();
    void mostrarPaciente(const Paciente& paciente);

public:
    // constructor que recibe el servicio a utilizar
    PacienteMenu(PacienteServicio& servicio);

    // ejecuta el menu principal del modulo actual
    void ejecutar();
};

#endif
