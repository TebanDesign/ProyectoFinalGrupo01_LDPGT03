#pragma once
#include <memory>

// Forward declarations
class PacienteMenu;
class CitasMenu;

class MainMenu {
private:
    std::unique_ptr<PacienteMenu> pacienteMenu;
    std::unique_ptr<CitasMenu> citasMenu;
    
    // Métodos privados para la presentación
    void mostrarBanner();
    void mostrarSalida();

public:
    MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu);
    
    void ejecutar();
    void mostrarMenuPrincipal();
    void limpiarPantalla();
};