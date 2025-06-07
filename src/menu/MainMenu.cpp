#include <limits>
#include "menu/MainMenu.h"
#include "menu/MenuUtils.h"
#include "menu/PacienteMenu.h"
#include "menu/CitasMenu.h"
#include "menu/TratamientoMenu.h"
#include "menu/InventarioMenu.h"
#include "servicios/LoginService.h"

// Constructor del menú principal, recibe punteros a los submenús y los convierte en smart pointers
MainMenu::MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, TratamientoMenu* tratamientoMenu, InventarioMenu* inventarioMenu) {
    this->pacienteMenu = std::unique_ptr<PacienteMenu>(pacienteMenu);
    this->citasMenu = std::unique_ptr<CitasMenu>(citasMenu);
    this->tratamientoMenu = std::unique_ptr<TratamientoMenu>(tratamientoMenu);
    this->inventarioMenu = std::unique_ptr<InventarioMenu>(inventarioMenu);
}

// Ejecuta el menú principal del sistema
void MainMenu::ejecutar() {
    int opcion;
    do {
        mostrarMenuPrincipal(); // Muestra el menú
        opcion = MenuUtils::leerOpcion(0, 5); // Lee opción válida entre 0 y 5

        switch(opcion) {
            case 1:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de pacientes");
                pacienteMenu->ejecutar(); // Llama al submenú de pacientes
                break;
            case 2:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de citas");
                citasMenu->ejecutar(); // Llama al submenú de citas
                break;
            case 3:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de tratamientos");
                tratamientoMenu->ejecutar(); // Llama al submenú de tratamientos
                break;
            case 4:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de inventario");
                inventarioMenu->ejecutar(); // Llama al submenú de inventario
                break;
            case 5:
                // Solicita confirmación para cerrar sesión
                if (confirmarCerrarSesion()) {
                    LoginService::cerrarSesion();
                    return; // Sale del menú principal (regresa al login)
                }
                break;
            case 0:
                mostrarSalida(); // Muestra mensaje de salida del sistema
                break;
        }
    } while(opcion != 0); // Repite mientras no se seleccione "Salir"
}

// Muestra el menú principal con las opciones disponibles
void MainMenu::mostrarMenuPrincipal() {
    MenuUtils::limpiarPantalla();
    
    mostrarBanner(); // Muestra el banner decorativo
    
    // Título del sistema
    MenuUtils::mostrarTitulo("SISTEMA DE GESTIÓN DENTAL", MenuUtils::AZUL, MenuUtils::BLANCO);
    MenuUtils::mostrarSubtitulo("RATONCITO PÉREZ", MenuUtils::CYAN);
    
    std::cout << "\n";
    
    // Opciones de navegación
    MenuUtils::mostrarOpcion(1, "Gestión de Pacientes");
    MenuUtils::mostrarOpcion(2, "Gestión de Citas");
    MenuUtils::mostrarOpcion(3, "Gestión de Tratamientos");
    MenuUtils::mostrarOpcion(4, "Gestión de Inventario");
    
    MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
    MenuUtils::mostrarOpcion(5, "Cerrar Sesión");
    MenuUtils::mostrarOpcion(0, "Salir del Sistema");
    
    std::cout << "\n";
}

// Muestra un banner decorativo al inicio del menú
void MainMenu::mostrarBanner() {
    std::vector<std::string> banner = {
        "   +======================================+",
        "   |                                      |",
        "   |          SISTEMA DE GESTIÓN          |",
        "   |                                      |",
        "   |          RATONCITO PEREZ             |",
        "   |                                      |",
        "   +======================================+"
    };
    
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::CYAN);
    for (const auto& linea : banner) {
        MenuUtils::centrarTexto(linea); // Centra cada línea del banner
    }
    MenuUtils::restaurarColor(); // Restaura colores originales
}

// Muestra un mensaje de despedida cuando el usuario decide salir del sistema
void MainMenu::mostrarSalida() {
    MenuUtils::limpiarPantalla();
    
    std::vector<std::string> despedida = {
        "",
        "Gracias por usar nuestro sistema!",
        "",
        "Sistema de Gestion Dental",
        "Ratoncito Perez",
        "",
        "Version 1.0 - 2025",
        ""
    };
    
    MenuUtils::mostrarCuadro(despedida, MenuUtils::VERDE); // Muestra cuadro con mensaje

    MenuUtils::mostrarMensaje("\nSaliendo del sistema", MenuUtils::AMARILLO);
    MenuUtils::mostrarCargando("Cerrando"); // Simula proceso de salida
    
    std::cout << "\n";
    MenuUtils::pausar(); // Espera confirmación del usuario
    MenuUtils::limpiarPantalla(); // Limpia la pantalla al final
}

// Limpia la pantalla, compatible con Windows y sistemas tipo Unix
void MainMenu::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Solicita al usuario confirmación para cerrar sesión
bool MainMenu::confirmarCerrarSesion() {
    MenuUtils::limpiarPantalla();
    MenuUtils::mostrarTitulo("CERRAR SESIÓN", MenuUtils::ROJO, MenuUtils::BLANCO);
    std::cout << "\n";

    MenuUtils::mostrarMensajeAdvertencia("¿Está seguro que desea cerrar la sesión actual?");
    std::cout << "\n";

    // Opciones de confirmación
    MenuUtils::mostrarOpcion(1, "Sí, cerrar sesión");
    MenuUtils::mostrarOpcion(2, "No, volver al menú");
    
    int confirmacion = MenuUtils::leerOpcion(1, 2); // Lee opción entre 1 y 2
    return (confirmacion == 1); // Devuelve true si seleccionó cerrar sesión
}
