#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <memory> // Para std::unique_ptr

// forward declarations (en lugar de incluir todos los headers)
class PacienteMenu;
class CitasMenu;
// class MedicamentoMenu;

class MainMenu {
private:
    // punteros inteligentes a los submodulos
    std::unique_ptr<PacienteMenu> pacienteMenu;
    std::unique_ptr<CitasMenu> citasMenu;
    // std::unique_ptr<MedicamentoMenu> medicamentoMenu;

    void mostrarMenuPrincipal();
    
    public:
    // constructor que recibe las dependencias necesarias
    MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu);
    // para agregar mas submodulos, ampliar el constructor:
    // MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, MedicamentoMenu* medicamentoMenu);
    
    void limpiarPantalla();
    
    // ejecuta el menu principal
    void ejecutar();
};

#endif
