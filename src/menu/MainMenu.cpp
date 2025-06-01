#include <limits>
#include "menu/MainMenu.h"
#include "menu/MenuUtils.h"
#include "menu/PacienteMenu.h"
#include "menu/CitasMenu.h"
#include "menu/TratamientoMenu.h"
#include "menu/InventarioMenu.h"


// #include "MedicamentoMenu.h" // para cuando agreguemos nuevos submodulos

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
        opcion = MenuUtils::leerOpcion(0, 4);

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
    // MenuUtils::mostrarOpcion(3, "Gestión de Medicamentos", false); // ejemplo para agregar nueva opcion
    
    MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
    MenuUtils::mostrarOpcion(0, "Salir del Sistema");
    
    std::cout << "\n";
}

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

void MainMenu::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
