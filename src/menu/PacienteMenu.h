#pragma once
#include "PacienteServicio.h"

class PacienteMenu {
private:
    PacienteServicio& servicio;
    
    // para mostrar informacion
    void mostrarBannerPacientes();
    void mostrarPacienteDetallado(const Paciente& paciente);

public:
    // constructor que recibe el servicio a utilizar
    PacienteMenu(PacienteServicio& servicio);
    
    void ejecutar();
    void mostrarMenu();
    void agregarPaciente();
    void editarPaciente();
    void buscarPaciente();
    void listarPacientes();
    void mostrarPaciente(const Paciente& paciente);
};