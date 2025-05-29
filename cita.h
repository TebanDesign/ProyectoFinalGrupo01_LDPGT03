// Descripción: Declaración de funciones para gestionar citas
#ifndef CITA_H
#define CITA_H

#include <string>

struct Cita {
    std::string idPaciente; // DUI del paciente
    std::string fecha;
    std::string hora;
    std::string motivo;
};

void agendarCita();
void mostrarCitas();

#endif