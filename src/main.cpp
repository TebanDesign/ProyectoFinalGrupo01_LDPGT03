#include <memory>
#include <windows.h>

#include "menu/MainMenu.h"
#include "menu/PacienteMenu.h"
#include "menu/CitasMenu.h"
#include "menu/TratamientoMenu.h"
#include "menu/InventarioMenu.h"
#include "menu/MenuUtils.h"

#include "servicios/PacienteServicio.h"
#include "servicios/InventarioServicio.h"
#include "servicios/LoginService.h"// 🔐 Login agregado

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
        
        TratamientoMenu tratamientoMenu;
        
        // 3. crear el menu principal e inyectar los submodulos
        MainMenu mainMenu(&pacienteMenu, &citasMenu, &tratamientoMenu, &inventarioMenu);
        

        while (true) {

            // Login antes de cada sesión
            if (LoginService::iniciarSesion()) {
                // si el login es existoso
                // 4. ejecutar el menu principal
                mainMenu.limpiarPantalla();
                mainMenu.ejecutar();
            }

            // Cuando regrese del menú principal, verificar si la sesión sigue activa
            // Si no está activa, significa que se cerró sesión y debe volver al login
            if (!LoginService::esSesionActiva()) {
                continue; // Vuelve al inicio del bucle (pantalla de login)
            } else {
                // Si la sesión sigue activa pero salió del menú, significa que eligió "Salir del Sistema"
                break; // Sale del programa completamente
            }
        }
    } catch (const std::exception& e) {
        MenuUtils::mostrarMensajeError("Error crítico en el sistema: " + std::string(e.what()));
        MenuUtils::pausar();
    }

    MenuUtils::restaurarColor();
    return 0;
}



/*
como agregar un nuevo submodulo con modelo/servicio/menu:
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
