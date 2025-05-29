#include <memory>
#include <windows.h>

#include "menu/MainMenu.h"
#include "menu/PacienteMenu.h"
#include "menu/CitasMenu.h"
#include "menu/InventarioMenu.h"
#include "menu/MenuUtils.h"

#include "servicios/PacienteServicio.h"
#include "servicios/InventarioServicio.h"

#include "utils/constantes.h"

int main() {
    
    MenuUtils::configurarConsola();
    
    try {
        // 1. crear los servicios
        PacienteServicio pacienteServicio("pacientes.dat");
        InventarioServicio inventarioServicio("inventario.dat");
        
        // 2. crear los menus con sus respectivos servicios
        PacienteMenu pacienteMenu(pacienteServicio);
        CitasMenu citasMenu;
        InventarioMenu inventarioMenu(inventarioServicio);

        // 3. crear el menu principal e inyectar los submodulos
        MainMenu mainMenu(&pacienteMenu, &citasMenu, &inventarioMenu);
        
        // 4. ejecutar el menu principal
        mainMenu.limpiarPantalla();
        mainMenu.ejecutar();
        
    } catch (const std::exception& e) {
        MenuUtils::mostrarMensajeError("Error crítico en el sistema: " + std::string(e.what()));
        MenuUtils::pausar();
    }
    
    // restaurar config original antes de salir
    MenuUtils::restaurarColor();
    
    return 0;
}