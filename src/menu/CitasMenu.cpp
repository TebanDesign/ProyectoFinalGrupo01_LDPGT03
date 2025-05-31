#include "menu/CitasMenu.h"
#include "menu/MenuUtils.h"
#include "utils/Validaciones.h"
#include "modelos/Cita.h"
#include <iostream>
#include <iomanip>
#include <vector>

CitasMenu::CitasMenu() : servicio("citas.dat") {}

void CitasMenu::ejecutar() {
    int opcion;
    do {
        mostrarMenu();
        int maxOpcion = servicio.archivoTieneDatos() ? 5 : 2;
        opcion = MenuUtils::leerOpcion(1, maxOpcion);

        switch(opcion) {
            case 1:
                MenuUtils::limpiarPantalla();
                agregarCita();
                MenuUtils::pausar();
                break;
            case 2:
                if (servicio.archivoTieneDatos()) {
                    MenuUtils::limpiarPantalla();
                    listarCitas();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("Debe agregar citas primero.");
                    MenuUtils::pausar();
                }
                break;
            case 3:
                if (servicio.archivoTieneDatos()) {
                    MenuUtils::limpiarPantalla();
                    editarCitaMenu();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("No hay citas para editar.");
                    MenuUtils::pausar();
                }
                break;
            case 4:
                if (servicio.archivoTieneDatos()) {
                    MenuUtils::limpiarPantalla();
                    buscarCitas();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("No hay citas para buscar.");
                    MenuUtils::pausar();
                }
                break;
            case 5:
                MenuUtils::mostrarMensaje("Regresando al menú principal...", MenuUtils::AMARILLO);
                MenuUtils::mostrarCargando("Cerrando módulo");
                break;
        }
    } while (opcion != 5);
}

void CitasMenu::mostrarMenu() {
    MenuUtils::limpiarPantalla();
    mostrarBanner();
    MenuUtils::mostrarTitulo("GESTIÓN DE CITAS", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
    std::cout << "\n";

    MenuUtils::mostrarOpcion(1, "Agregar nueva cita");
    MenuUtils::mostrarOpcion(2, "Listar todas las citas", servicio.archivoTieneDatos());
    MenuUtils::mostrarOpcion(3, "Editar cita", servicio.archivoTieneDatos());
    MenuUtils::mostrarOpcion(4, "Buscar citas por DUI", servicio.archivoTieneDatos());
    MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
    MenuUtils::mostrarOpcion(5, "Regresar al menú principal");
}

void CitasMenu::mostrarBanner() {
    std::vector<std::string> banner = {
        "MODULO DE CITAS",
        "Registro y gestión de citas"
    };
    MenuUtils::mostrarCuadro(banner, MenuUtils::AZUL);
}

void CitasMenu::agregarCita() {
    MenuUtils::mostrarTitulo("AGREGAR NUEVA CITA", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);

    std::string dui, nombre, telefono, tratamiento, fecha, hora, motivo;

    MenuUtils::mostrarMensaje("Ingrese los datos de la cita:", MenuUtils::CYAN);
    std::cout << "\n";

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "DUI del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, dui);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nombre del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nombre);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Número de teléfono: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, telefono);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Tratamiento: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, tratamiento);

    do {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        std::cout << "Fecha (DD/MM/AAAA): ";
        MenuUtils::restaurarColor();
        std::getline(std::cin >> std::ws, fecha);
        if (!Validaciones::validarFecha(fecha)) {
            MenuUtils::mostrarMensajeError("Fecha inválida.");
        }
    } while (!Validaciones::validarFecha(fecha));

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Hora (HH:MM AM/PM): ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, hora);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Motivo de la cita: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, motivo);

    Cita cita(dui, nombre, telefono, tratamiento, fecha, hora, motivo);
    MenuUtils::mostrarCargando("Guardando cita");

    if (servicio.agregarCita(cita)) {
        MenuUtils::mostrarMensajeExito("Cita agregada exitosamente!");
    } else {
        MenuUtils::mostrarMensajeError("Error al guardar la cita.");
    }
}

void CitasMenu::listarCitas() {
    MenuUtils::mostrarTitulo("LISTADO DE CITAS", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    auto citas = servicio.obtenerTodasLasCitas();
    if (citas.empty()) {
        MenuUtils::mostrarMensajeAdvertencia("No hay citas registradas.");
        return;
    }

    MenuUtils::mostrarMensaje("Total de citas: " + std::to_string(citas.size()), MenuUtils::CYAN);
    MenuUtils::mostrarSeparador('=', 140, MenuUtils::GRIS);
    MenuUtils::cambiarColor(MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
    std::cout << std::left << std::setw(15) << "DUI"
              << std::setw(25) << "Nombre"
              << std::setw(15) << "Teléfono"
              << std::setw(25) << "Tratamiento"
              << std::setw(15) << "Fecha"
              << std::setw(10) << "Hora"
              << "Motivo" << std::endl;
    MenuUtils::restaurarColor();
    MenuUtils::mostrarSeparador('-', 140, MenuUtils::GRIS);

    for (size_t i = 0; i < citas.size(); ++i) {
        const auto& c = citas[i];
        if (i % 2 == 0)
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO_OSCURO);
        else
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);

        std::cout << std::left << std::setw(15) << c.getDuiPaciente()
                  << std::setw(25) << c.getNombrePaciente()
                  << std::setw(15) << c.getTelefonoPaciente()
                  << std::setw(25) << c.getTratamiento()
                  << std::setw(15) << c.getFecha()
                  << std::setw(10) << c.getHora()
                  << c.getMotivo() << std::endl;
    }

    MenuUtils::restaurarColor();
    MenuUtils::mostrarSeparador('=', 140, MenuUtils::GRIS);
}

void CitasMenu::editarCitaMenu() {
    MenuUtils::mostrarTitulo("EDITAR CITA", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    std::string duiOriginal, fechaOriginal, horaOriginal;
    std::string nuevoNombre, nuevoTelefono, nuevoTratamiento, nuevaFecha, nuevaHora, nuevoMotivo;

    std::cout << "\nIngrese los datos de la cita a editar (para identificarla):\n";

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "DUI del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, duiOriginal);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Fecha original (DD/MM/AAAA): ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, fechaOriginal);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Hora original (HH:MM AM/PM): ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, horaOriginal);

    std::cout << "\nIngrese los nuevos datos de la cita:\n";

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo nombre del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoNombre);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo número de teléfono: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoTelefono);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo tratamiento: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoTratamiento);

    std::string nuevaFechaStr;
    do {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        std::cout << "Nueva fecha (DD/MM/AAAA): ";
        MenuUtils::restaurarColor();
        std::getline(std::cin >> std::ws, nuevaFechaStr);
        if (!Validaciones::validarFecha(nuevaFechaStr)) {
            MenuUtils::mostrarMensajeError("Fecha inválida.");
        } else {
            nuevaFecha = nuevaFechaStr;
        }
    } while (!Validaciones::validarFecha(nuevaFechaStr));

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nueva hora (HH:MM AM/PM): ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevaHora);

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo motivo de la cita: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoMotivo);

    MenuUtils::mostrarCargando("Actualizando cita");
    if (servicio.editarCita(duiOriginal, fechaOriginal, horaOriginal, nuevoNombre, nuevoTelefono, nuevoTratamiento, nuevaFecha, nuevaHora, nuevoMotivo)) {
        MenuUtils::mostrarMensajeExito("Cita actualizada exitosamente!");
    } else {
        MenuUtils::mostrarMensajeError("No se encontró la cita para editar.");
    }
}

void CitasMenu::buscarCitas() {
    MenuUtils::mostrarTitulo("BUSCAR CITAS POR DUI", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    std::string duiABuscar;
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Ingrese el DUI del paciente a buscar: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, duiABuscar);

    auto resultados = servicio.buscarCitasPorDui(duiABuscar);

    std::cout << "\nResultados de la búsqueda para el DUI: " << duiABuscar << "\n";

    if (resultados.empty()) {
        MenuUtils::mostrarMensajeAdvertencia("No se encontraron citas para ese DUI.");
    } else {
        MenuUtils::mostrarMensaje("Se encontraron " + std::to_string(resultados.size()) + " citas.", MenuUtils::CYAN);
        MenuUtils::mostrarSeparador('=', 140, MenuUtils::GRIS);
        MenuUtils::cambiarColor(MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
        std::cout << std::left << std::setw(15) << "DUI"
                  << std::setw(25) << "Nombre"
                  << std::setw(15) << "Teléfono"
                  << std::setw(25) << "Tratamiento"
                  << std::setw(15) << "Fecha"
                  << std::setw(10) << "Hora"
                  << "Motivo" << std::endl;
        MenuUtils::restaurarColor();
        MenuUtils::mostrarSeparador('-', 140, MenuUtils::GRIS);
        for (const auto& cita : resultados) {
            std::cout << std::left << std::setw(15) << cita.getDuiPaciente()
                      << std::setw(25) << cita.getNombrePaciente()
                      << std::setw(15) << cita.getTelefonoPaciente()
                      << std::setw(25) << cita.getTratamiento()
                      << std::setw(15) << cita.getFecha()
                      << std::setw(10) << cita.getHora()
                      << cita.getMotivo() << std::endl;
        }
        MenuUtils::mostrarSeparador('=', 140, MenuUtils::GRIS);
    }
}