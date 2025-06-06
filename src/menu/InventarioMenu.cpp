#include "menu/InventarioMenu.h"
#include "servicios/InventarioServicio.h"
#include "menu/MenuUtils.h"
#include <iostream>
#include <vector>

using namespace std;

// Constructor que inyecta el servicio de inventario
InventarioMenu::InventarioMenu(InventarioServicio& servicio) 
    : inventarioServicio(servicio) {}  // Inicializa referencia


// Implementación del menú principal de inventario    
void InventarioMenu::ejecutar() {
    int opcion;

    // Bucle principal del menú
    do {
        // Limpiar pantalla y mostrar elementos visuales
        MenuUtils::limpiarPantalla();
        mostrarBannerInventario();  // Muestra banner superior

        // Mostrar título del módulo con colores
        MenuUtils::mostrarTitulo("GESTIÓN DE INVENTARIO", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
        cout << endl;   // Separador visual
        
        // === Menú de opciones dinámico ===
        // Opción 1: Siempre disponible
        MenuUtils::mostrarOpcion(1, "Agregar medicamento");

        // Opciones 2-6: Solo disponibles si existen medicamentos
        MenuUtils::mostrarOpcion(2, "Editar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(3, "Buscar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(4, "Listar medicamentos", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(5, "Descontar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(6, "Aumentar stock", inventarioServicio.existenMedicamentos());

        // Separador y opción para salir
        MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
        MenuUtils::mostrarOpcion(0, "Volver al menu principal");

        cout << endl;
        
        // Leer opción válida (rango 0-6)
        opcion = MenuUtils::leerOpcion(0, 6);

        // Limpiar pantalla antes de ejecutar acción
        MenuUtils::limpiarPantalla();

        // === Gestión de opciones ===
        switch (opcion) {
            case 1:
                inventarioServicio.agregarMedicamento();
                break;
            case 2:
                inventarioServicio.editarMedicamento();
                break;
            case 3:
                inventarioServicio.buscarMedicamento();
                break;
            case 4:
                inventarioServicio.listarMedicamentos();
                break;
            case 5:
                inventarioServicio.descontarMedicamento();
                break;
            case 6:
                inventarioServicio.aumentarStock();
                break;
            case 0:
                MenuUtils::mostrarMensaje("Regresando al menu principal...", MenuUtils::AMARILLO);
                MenuUtils::mostrarCargando("Cerrando modulo");
                break;
            default:
                MenuUtils::mostrarMensajeError("Opcion no valida. Intente de nuevo.");
                break;
        }

        if (opcion != 0) {
            MenuUtils::pausar();
        }

    } while (opcion != 0);
}

void InventarioMenu::mostrarBannerInventario() {
    vector<string> banner = {
        "MODULO DE INVENTARIO",
        "Gestion completa de medicamentos"
    };
    MenuUtils::mostrarCuadro(banner, MenuUtils::AZUL);
}