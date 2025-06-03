#pragma once

#include <string>

// Clase de menú que gestiona las opciones relacionadas a tratamientos
class TratamientoMenu {
public:
    void ejecutar(); // Lanza el menú principal de tratamientos

private:
    void registrar();           // Registra un nuevo tratamiento
    void buscar();              // Muestra tratamientos por DUI
    void editar();              // Edita un tratamiento existente
};