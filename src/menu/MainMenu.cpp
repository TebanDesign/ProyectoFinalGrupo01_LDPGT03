#include "MainMenu.h"
#include "PacienteMenu.h"
#include "CitasMenu.h"
// #include "CitasMenu.cpp"
// #include "CitaMenu.h"  // para cuando agreguemos nuevos submodulos
// #include "MedicamentoMenu.h"
#include <limits>

MainMenu::MainMenu( PacienteMenu* pacienteMenu,
                    CitasMenu* citasMenu){
    this->pacienteMenu = std::unique_ptr<PacienteMenu>(pacienteMenu);
    this->citasMenu = std::unique_ptr<CitasMenu>(citasMenu);
    // inicializar otros menus cuando existan:
    // this->medicamentoMenu = std::unique_ptr<MedicamentoMenu>(medicamentoMenu);
}

void MainMenu::ejecutar() {

    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcion) {
            case 1:
                limpiarPantalla();
                pacienteMenu -> ejecutar();
                break;
            case 2:
                limpiarPantalla();
                citasMenu -> ejecutar();
                break;
            /*
            //ejemplo de como agregar un nuevo submodulo:
            case 3:
                limpiarPantalla();
                medicamentoMenu->ejecutar();
                break;
            */
            case 0:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while(opcion != 0);
}

void MainMenu::mostrarMenuPrincipal() {
    limpiarPantalla();
    std::cout << "\n=================================" << std::endl;
    std::cout << "\n=== SISTEMA DE GESTION DENTAL ===" << std::endl;
    std::cout << "\n===      RATONCITO PEREZ      ===" << std::endl;
    std::cout << "\n=================================" << std::endl;

    std::cout << "1. Gestión de Pacientes" << std::endl;
    std::cout << "2. Gestión de Citas" << std::endl;
    // std::cout << "3. Gestión de Medicamentos" << std::endl;      // Para nuevos módulos
    // std::cout << "4. Gestión de Nombre_Modulo" << std::endl;      // Para nuevos módulos
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void MainMenu::limpiarPantalla() {
    // Sistema portable para limpiar pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}