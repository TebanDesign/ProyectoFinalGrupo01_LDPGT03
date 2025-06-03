#include "menu/InventarioMenu.h"
#include "servicios/InventarioServicio.h"
#include "menu/MenuUtils.h"
#include <iostream>
#include <vector>

using namespace std;

InventarioMenu::InventarioMenu(InventarioServicio& servicio) : inventarioServicio(servicio) {}

void InventarioMenu::ejecutar() {
    int opcion;

    do {
        MenuUtils::limpiarPantalla();
        mostrarBannerInventario();

        MenuUtils::mostrarTitulo("GESTIÓN DE INVENTARIO", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
        cout << endl;

        MenuUtils::mostrarOpcion(1, "Agregar medicamento");
        MenuUtils::mostrarOpcion(2, "Editar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(3, "Buscar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(4, "Listar medicamentos", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(5, "Descontar medicamento", inventarioServicio.existenMedicamentos());
        MenuUtils::mostrarOpcion(6, "Aumentar stock", inventarioServicio.existenMedicamentos());

        MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
        MenuUtils::mostrarOpcion(0, "Volver al menu principal");

        cout << endl;
        opcion = MenuUtils::leerOpcion(0, 6);

        MenuUtils::limpiarPantalla();

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