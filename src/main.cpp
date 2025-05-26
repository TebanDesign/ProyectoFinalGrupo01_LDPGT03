#include <memory>
#include <windows.h>

#include "MainMenu.h"
#include "PacienteMenu.h"
#include "CitasMenu.h"
#include "PacienteServicio.h"
#include "constantes.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 1. crear los servicios
    PacienteServicio pacienteServicio("pacientes.dat");
    
    // 2. crear los menus con sus respectivos servicios
    PacienteMenu pacienteMenu(pacienteServicio);
    CitasMenu citasMenu;
    
    // 3. crear el menu principal e inyectar los submodulos
    MainMenu mainMenu(&pacienteMenu, &citasMenu);
    
    // 4. ejecutar el menu hprincipal
    
   mainMenu.limpiarPantalla();
   mainMenu.ejecutar();
    
    return 0;
}

/*
como agregar un nuevo submodulo en el futuro:
1. Crear el servicio correspondiente (ej: CitaService)
2. Crear el menu correspondiente (ej: CitaMenu)
3. modificar el main para:
   - crear el servicio
   - crear el menu
   - pasarlo al MainMenu (ampliando su constructor)
4. Modificar MainMenu.h/.cpp para:
   - agregar el nuevo miembro unique_ptr
   - agregar la opcion en el menuprincipal
   - manejar la ejecucion del nuevo módulo
*/