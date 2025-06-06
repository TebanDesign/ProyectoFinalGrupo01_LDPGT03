#ifndef INVENTARIOMENU_H  // Guardia de inclusión (previene múltiples inclusiones)
#define INVENTARIOMENU_H

// Declaración adelantada (evita incluir el header completo)
class InventarioServicio;

// Clase para gestionar el menú de operaciones de inventario
class InventarioMenu {
public:
    // Constructor explícito que recibe una referencia al servicio de inventario
    // (Inyección de dependencia)
    explicit InventarioMenu(InventarioServicio& servicio);

    // Punto de entrada principal para iniciar el menú de inventario
    void ejecutar();

private:
    // Referencia al servicio que maneja la lógica de negocio del inventario
    InventarioServicio& inventarioServicio;
    
    // Muestra el banner/encabezado del menú de inventario
    void mostrarBannerInventario();
};

#endif