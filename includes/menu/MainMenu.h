#pragma once
#include <memory>

// Forward declarations
class PacienteMenu;
class CitasMenu;
class TratamientoMenu;

class MainMenu {
private:
    std::unique_ptr<PacienteMenu> pacienteMenu;
    std::unique_ptr<CitasMenu> citasMenu;
    std::unique_ptr<TratamientoMenu> tratamientoMenu;
    
    // Métodos privados para la presentación
    void mostrarBanner();
    void mostrarSalida();

public:
    MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, TratamientoMenu* tratamientoMenu);
    
    void ejecutar();
    void mostrarMenuPrincipal();
    void limpiarPantalla();
};