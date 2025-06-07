// citasmenu.h: Este archivo de cabecera define la interfaz de la clase CitasMenu.

#ifndef CITASMENU_H 
#define CITASMENU_H

#include "servicios/CitaServicio.h" 
#include "tratamiento.h"            

// Declaración de la clase CitasMenu.
// Esta clase gestiona el menú y las operaciones relacionadas con las citas en la interfaz de usuario.
class CitasMenu {
private:
    CitaServicio servicio; // Instancia de CitaServicio para manejar la persistencia de citas.

    // Métodos privados que implementan las funcionalidades del menú.
    void mostrarMenu();    // Muestra las opciones del menú de citas.
    void mostrarBanner();  // Muestra un banner específico para el módulo de citas.
    void agregarCita();    // Permite al usuario agregar una nueva cita.
    void listarCitas();    // Lista todas las citas registradas.
    void editarCitaMenu(); // Proporciona la interfaz para editar una cita existente.
    void buscarCitas();    // Permite buscar citas por el DUI de un paciente.

public:
    // Constructor de la clase CitasMenu.
    CitasMenu();
    // Método principal para ejecutar el menú de citas y controlar el flujo de la aplicación.
    void ejecutar();
};

#endif 