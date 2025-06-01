#include <limits>
#include "menu/MainMenu.h"
#include "menu/MenuUtils.h"
#include "menu/PacienteMenu.h"
#include "menu/CitasMenu.h"
#include "menu/TratamientoMenu.h"
#include "menu/InventarioMenu.h"
#include "servicios/LoginService.h"

MainMenu::MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, TratamientoMenu* tratamientoMenu, InventarioMenu* inventarioMenu) {
    this->pacienteMenu = std::unique_ptr<PacienteMenu>(pacienteMenu);
    this->citasMenu = std::unique_ptr<CitasMenu>(citasMenu);
    this->tratamientoMenu = std::unique_ptr<TratamientoMenu>(tratamientoMenu);
    this->inventarioMenu = std::unique_ptr<InventarioMenu>(inventarioMenu);
}

void MainMenu::ejecutar() {
    
    int opcion;
    do {
        mostrarMenuPrincipal();
        opcion = MenuUtils::leerOpcion(0, 5);

        switch(opcion) {
            case 1:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de pacientes");
                pacienteMenu->ejecutar();
                break;
            case 2:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de citas");
                citasMenu->ejecutar();
                break;
            case 3:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de tratamientos");
                tratamientoMenu->ejecutar();
                break;
            case 4:
                MenuUtils::limpiarPantalla();
                MenuUtils::mostrarCargando("Cargando módulo de inventario");
                inventarioMenu->ejecutar();
                break;
            case 5:
                if (confirmarCerrarSesion()) {
                    LoginService::cerrarSesion();
                    return; // Sale del menú principal para volver al login
                }
                break;
            case 0:
                mostrarSalida();
                break;
        }
    } while(opcion != 0);
}

void MainMenu::mostrarMenuPrincipal() {
    MenuUtils::limpiarPantalla();
    
    // logo/banner principal
    mostrarBanner();
    
    // titulo principal
    MenuUtils::mostrarTitulo("SISTEMA DE GESTIÓN DENTAL", MenuUtils::AZUL, MenuUtils::BLANCO);
    MenuUtils::mostrarSubtitulo("RATONCITO PÉREZ", MenuUtils::CYAN);
    
    std::cout << "\n";
    
    // opciones del menu
    MenuUtils::mostrarOpcion(1, "Gestión de Pacientes");
    MenuUtils::mostrarOpcion(2, "Gestión de Citas");
    MenuUtils::mostrarOpcion(3, "Gestión de Tratamientos");
    MenuUtils::mostrarOpcion(4, "Gestión de Inventario");
    
    MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
    MenuUtils::mostrarOpcion(5, "Cerrar Sesión");
    MenuUtils::mostrarOpcion(0, "Salir del Sistema");
    
    std::cout << "\n";
}

// muestra el banner al entrar al sistema 
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
        MenuUtils::centrarTexto(linea);
    }
    MenuUtils::restaurarColor();
}

// muestra en pantalla un mensaje de salida del sistema
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
    
    MenuUtils::mostrarCuadro(despedida, MenuUtils::VERDE);
    
    MenuUtils::mostrarMensaje("\nSaliendo del sistema", MenuUtils::AMARILLO);
    MenuUtils::mostrarCargando("Cerrando");
    
    std::cout << "\n";
    MenuUtils::pausar();
    MenuUtils::limpiarPantalla();
}

// limpia la pantalla, sirve para windows, linux y macos
void MainMenu::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// metod que solicita la confirmacion para cerrara la sesion
bool MainMenu::confirmarCerrarSesion() {

    MenuUtils::limpiarPantalla();
    MenuUtils::mostrarTitulo("CERRAR SESIÓN", MenuUtils::ROJO, MenuUtils::BLANCO);
    
    MenuUtils::mostrarSubtitulo("¿Está seguro que desea cerrar la sesión actual?", MenuUtils::AMARILLO);
    MenuUtils::mostrarOpcion(1, "Sí, cerrar sesión");
    MenuUtils::mostrarOpcion(2, "No, volver al menú");
    
    int confirmacion = MenuUtils::leerOpcion(1, 2);
    return (confirmacion == 1);
}
