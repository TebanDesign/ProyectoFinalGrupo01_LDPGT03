#pragma once
#include <memory>

// Forward declarations
class PacienteMenu;
class CitasMenu;
class TratamientoMenu;
class InventarioMenu;

class MainMenu {
private:
    std::unique_ptr<PacienteMenu> pacienteMenu;
    std::unique_ptr<CitasMenu> citasMenu;
    std::unique_ptr<TratamientoMenu> tratamientoMenu;
    std::unique_ptr<InventarioMenu> inventarioMenu; 
    
    // Métodos privados para la presentación
    void mostrarBanner();
    void mostrarSalida();

public:
    MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, TratamientoMenu* tratamientoMenu, InventarioMenu* inventarioMenu);
    
    void ejecutar();
    void mostrarMenuPrincipal();
    void limpiarPantalla();
};