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
    
    /**
    * @brief Muestra un banner o cabecera visual en la consola.
    * Esta funcion muestra el nombre de la aplicacion
    */
    void mostrarBanner();

    /**
     * @brief Muestra mensajes de salida o de despedida en la consola.
     */
    void mostrarSalida();

public:
    MainMenu(PacienteMenu* pacienteMenu, CitasMenu* citasMenu, TratamientoMenu* tratamientoMenu, InventarioMenu* inventarioMenu);
    
    /**
     * @brief Ejecuta el flujo principal de la aplicacion.
     * Esta funcion orquesta las diferentes operaciones del programa,
     * gestionando el bucle del menu principal, la interacción del usuario
     * y la llamada a otras funciones según la lógica de la aplicacion.
     */
    void ejecutar();

    /// @brief Muestra las opciones del menu principal al usuario.
    /// Presenta una lista numerada o con viñetas de las acciones disponibles
    /// para que el usuario pueda interactuar con el programa.
    void mostrarMenuPrincipal();

    /// @brief Limpia la pantalla de la consola.
    /// Esta funcion elimina todo el texto y la salida previa de la consola,
    /// proporcionando una interfaz de usuario mas limpia y organizada,
    /// especialmente util antes de mostrar un nuevo menu o informacion.
    void limpiarPantalla();

    /// @brief Solicita al usuario una confirmacion para cerrar la sesion o salir del programa.
    /// @return `true` si el usuario confirma que desea cerrar la sesion o salir,
    ///         `false` en caso contrario.
    /// Esta funcion es util para prevenir cierres accidentales y asegurar que el usuario
    /// realmente desea terminar la ejecucion de la aplicacion.
    bool confirmarCerrarSesion();
};