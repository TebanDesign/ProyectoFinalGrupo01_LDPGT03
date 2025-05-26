#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>

#include "menu/PacienteMenu.h"
#include "menu/MenuUtils.h"
#include "utils/Validaciones.h"

using namespace std;

    PacienteMenu::PacienteMenu(PacienteServicio& servicio) : servicio(servicio) {}

    void PacienteMenu::ejecutar() {
        int opcion;
        do {
            mostrarMenu();
            
            // Determinar rango de opciones válidas
            int maxOpcion = servicio.archivoTieneDatos() ? 5 : 5;
            opcion = MenuUtils::leerOpcion(1, maxOpcion);

            switch(opcion) {
                case 1:
                    MenuUtils::limpiarPantalla();
                    agregarPaciente();
                    MenuUtils::pausar();
                    break;
                case 2:
                    if (servicio.archivoTieneDatos()) {
                        MenuUtils::limpiarPantalla();
                        editarPaciente();
                        MenuUtils::pausar();
                    } else {
                        MenuUtils::mostrarMensajeAdvertencia("Debe agregar pacientes primero");
                        MenuUtils::pausar();
                    }
                    break;
                case 3:
                    if (servicio.archivoTieneDatos()) {
                        MenuUtils::limpiarPantalla();
                        buscarPaciente();
                        MenuUtils::pausar();
                    } else {
                        MenuUtils::mostrarMensajeAdvertencia("Debe agregar pacientes primero");
                        MenuUtils::pausar();
                    }
                    break;
                case 4:
                    if (servicio.archivoTieneDatos()) {
                        MenuUtils::limpiarPantalla();
                        listarPacientes();
                        MenuUtils::pausar();
                    } else {
                        MenuUtils::mostrarMensajeAdvertencia("Debe agregar pacientes primero");
                        MenuUtils::pausar();
                    }
                    break;
                case 5:
                    MenuUtils::mostrarMensaje("Regresando al menú principal...", MenuUtils::AMARILLO);
                    MenuUtils::mostrarCargando("Cerrando módulo");
                    break;
            }
        } while(opcion != 5);
    }

    void PacienteMenu::mostrarMenu() {
        MenuUtils::limpiarPantalla();
        
        // Banner del módulo
        mostrarBannerPacientes();
        
        MenuUtils::mostrarTitulo("GESTIÓN DE PACIENTES", MenuUtils::VERDE_OSCURO, MenuUtils::BLANCO);
        
        std::cout << "\n";
        
        // Opciones siempre disponibles
        MenuUtils::mostrarOpcion(1, "Agregar nuevo paciente");
        
        // Opciones que requieren datos
        bool hayDatos = servicio.archivoTieneDatos();
        MenuUtils::mostrarOpcion(2, "Editar paciente existente", hayDatos);
        MenuUtils::mostrarOpcion(3, "Buscar paciente por DUI", hayDatos);
        MenuUtils::mostrarOpcion(4, "Listar todos los pacientes", hayDatos);
        
        MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
        MenuUtils::mostrarOpcion(5, "Regresar al menú principal");
        
        std::cout << "\n";
    }

    void PacienteMenu::mostrarBannerPacientes() {
        std::vector<std::string> banner = {
            "MODULO DE PACIENTES",
            "Gestion completa de pacientes"
        };
        
        MenuUtils::mostrarCuadro(banner, MenuUtils::VERDE);
    }

    void PacienteMenu::agregarPaciente() {
        MenuUtils::mostrarTitulo("AGREGAR NUEVO PACIENTE", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
        
        string nombre, dui, fechaNacimiento, genero, comentarios;

        // Obtener nombre
        MenuUtils::mostrarMensaje("Ingrese los datos del paciente:", MenuUtils::CYAN);
        std::cout << "\n";
        
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        cout << "Nombre completo: ";
        MenuUtils::restaurarColor();
        getline(cin, nombre);

        // Obtener y validar DUI
        do {
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "DUI (00000000-0): ";
            MenuUtils::restaurarColor();
            getline(cin, dui);
            
            if (!Validaciones::validarDUI(dui)) {
                MenuUtils::mostrarMensajeError("DUI inválido. Use el formato 00000000-0");
            }
        } while (!Validaciones::validarDUI(dui));

        // Obtener y validar género
        do {
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Género (M/F): ";
            MenuUtils::restaurarColor();
            getline(cin, genero);
            
            if (!genero.empty()) {
                string generoLower = genero;
                transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);
                
                if (generoLower == "m" || generoLower == "f") {
                    genero = generoLower;
                    break;
                } else {
                    MenuUtils::mostrarMensajeError("Entrada inválida. Ingrese 'M' o 'F'");
                }
            }
        } while (true);

        // Obtener y validar fecha
        do {
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Fecha de nacimiento (DD/MM/AAAA): ";
            MenuUtils::restaurarColor();
            getline(cin, fechaNacimiento);
            
            if (fechaNacimiento.empty()) {
                MenuUtils::mostrarMensajeError("La fecha de nacimiento es obligatoria");
            } else if (!Validaciones::validarFecha(fechaNacimiento)) {
                MenuUtils::mostrarMensajeError("Fecha inválida. Use el formato DD/MM/AAAA");
            }
        } while (fechaNacimiento.empty() || !Validaciones::validarFecha(fechaNacimiento));
        
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        cout << "Comentarios sobre salud: ";
        MenuUtils::restaurarColor();
        getline(cin, comentarios);

        Paciente nuevo(nombre, dui, genero, fechaNacimiento, comentarios);

        MenuUtils::mostrarCargando("Guardando paciente");
        
        if (servicio.agregarPaciente(nuevo)) {
            MenuUtils::mostrarMensajeExito("Paciente agregado exitosamente!");
        } else {
            MenuUtils::mostrarMensajeError("Ya existe un paciente con ese DUI");
        }
    }

    void PacienteMenu::editarPaciente() {
        MenuUtils::mostrarTitulo("EDITAR PACIENTE", MenuUtils::AMARILLO_OSCURO, MenuUtils::NEGRO);

        string duiOriginal;
        Paciente actual;

        try {
            while(actual.getDui().empty()) {
                MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
                cout << "Ingrese el DUI del paciente a editar: ";
                MenuUtils::restaurarColor();
                getline(cin, duiOriginal);
                
                actual = servicio.buscarPorDui(duiOriginal);

                if(actual.getDui().empty()) {
                    MenuUtils::mostrarMensajeError("Paciente no encontrado. Intente de nuevo.");
                }
            }

            MenuUtils::mostrarMensajeExito("Paciente encontrado:");
            std::cout << "\n";
            mostrarPacienteDetallado(actual);
            
            MenuUtils::mostrarSeparador('=', 50, MenuUtils::CYAN);
            MenuUtils::mostrarMensaje("Deje vacio para no cambiar el campo", MenuUtils::AMARILLO);
            std::cout << "\n";

            string nombre, genero, fechaNacimiento, comentarios;

            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Nuevo nombre: ";
            MenuUtils::restaurarColor();
            getline(cin, nombre);
            if (!nombre.empty()) actual.setNombre(nombre);

            // Validación de género mejorada
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Nuevo género (M/F): ";
            MenuUtils::restaurarColor();
            getline(cin, genero);

            if (!genero.empty()) {
                string generoLower = genero;
                transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

                while (generoLower != "m" && generoLower != "f") {
                    MenuUtils::mostrarMensajeError("Género inválido");
                    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
                    cout << "Género (M/F) o vacío para no cambiar: ";
                    MenuUtils::restaurarColor();
                    getline(cin, genero);
                    
                    if (genero.empty()) break;
                    
                    generoLower = genero;
                    transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);
                }

                if (!genero.empty()) {
                    actual.setGenero(generoLower);
                }
            }

            // Validación de fecha mejorada
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Nueva fecha de nacimiento (DD/MM/AAAA): ";
            MenuUtils::restaurarColor();
            getline(cin, fechaNacimiento);

            if (!fechaNacimiento.empty()) {
                while (!Validaciones::validarFecha(fechaNacimiento)) {
                    MenuUtils::mostrarMensajeError("Fecha inválida");
                    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
                    cout << "Fecha (DD/MM/AAAA) o vacío para no cambiar: ";
                    MenuUtils::restaurarColor();
                    getline(cin, fechaNacimiento);
                    
                    if (fechaNacimiento.empty()) break;
                }
                
                if (!fechaNacimiento.empty()) {
                    actual.setFechaNacimiento(fechaNacimiento);
                }
            }

            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
            cout << "Nuevos comentarios: ";
            MenuUtils::restaurarColor();
            getline(cin, comentarios);
            if (!comentarios.empty()) actual.setComentariosSalud(comentarios);

            MenuUtils::mostrarCargando("Actualizando paciente");

            if (servicio.editarPaciente(duiOriginal, actual)) {
                MenuUtils::mostrarMensajeExito("Paciente actualizado exitosamente!");
            } else {
                MenuUtils::mostrarMensajeError("Error al actualizar el paciente");
            }
        } catch (const exception& e) {
            MenuUtils::mostrarMensajeError("Error: " + string(e.what()));
        }
    }

    void PacienteMenu::buscarPaciente() {
        MenuUtils::mostrarTitulo("BUSCAR PACIENTE", MenuUtils::CYAN_OSCURO, MenuUtils::BLANCO);

        string dui;
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        cout << "Ingrese el DUI del paciente: ";
        MenuUtils::restaurarColor();
        getline(cin, dui);

        MenuUtils::mostrarCargando("Buscando paciente");

        try {
            Paciente encontrado = servicio.buscarPorDui(dui);
            
            MenuUtils::mostrarMensajeExito("Paciente encontrado!");
            std::cout << "\n";
            mostrarPacienteDetallado(encontrado);
            
        } catch (const exception& e) {
            MenuUtils::mostrarMensajeError("Paciente no encontrado");
        }
    }

    void PacienteMenu::listarPacientes() {
        MenuUtils::mostrarTitulo("LISTADO DE PACIENTES", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

        try {
            vector<Paciente> pacientes = servicio.obtenerTodosLosPacientes();
            
            if (pacientes.empty()) {
                MenuUtils::mostrarMensajeAdvertencia("No hay pacientes registrados");
                return;
            }

            MenuUtils::mostrarMensaje("Total de pacientes: " + to_string(pacientes.size()), MenuUtils::CYAN);
            MenuUtils::mostrarSeparador('=', 100, MenuUtils::GRIS);

            // Encabezados de la tabla
            MenuUtils::cambiarColor(MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
            cout << left << setw(25) << " NOMBRE" << setw(12) << " DUI" << setw(10) << " GÉNERO" 
                << setw(12) << " FECHA NAC." << setw(6) << " EDAD" << " COMENTARIOS" << endl;
            MenuUtils::restaurarColor();
            
            MenuUtils::mostrarSeparador('-', 100, MenuUtils::GRIS);

            // Datos de los pacientes
            for (size_t i = 0; i < pacientes.size(); i++) {
                const auto& paciente = pacientes[i];
                
                // Alternar colores para mejor legibilidad
                if (i % 2 == 0) {
                    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO_OSCURO);
                } else {
                    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
                }
                
                cout << left << setw(25) << paciente.getNombre().substr(0, 22) + (paciente.getNombre().length() > 22 ? "..." : "")
                    << setw(12) << paciente.getDui()
                    << setw(10) << (paciente.getGenero() == "m" ? "Masculino" : "Femenino")
                    << setw(12) << paciente.getFechaNacimiento()
                    << setw(6) << paciente.getEdad()
                    << paciente.getComentariosSalud().substr(0, 30) + (paciente.getComentariosSalud().length() > 30 ? "..." : "") << endl;
            }
            
            MenuUtils::restaurarColor();
            MenuUtils::mostrarSeparador('=', 100, MenuUtils::GRIS);
            
        } catch (const exception& e) {
            MenuUtils::mostrarMensajeError("Error al cargar pacientes: " + string(e.what()));
        }
    }

    void PacienteMenu::mostrarPaciente(const Paciente& paciente) {
        mostrarPacienteDetallado(paciente);
    }

    void PacienteMenu::mostrarPacienteDetallado(const Paciente& paciente) {
        
        std::string generoDisplay =  paciente.getGenero() == "m" ? "Masculino" : "Femenino";

        std::vector<std::string> infoPaciente = {
            "INFORMACION DEL PACIENTE",
            "",
            "Nombre: " + paciente.getNombre(),
            "DUI: " + paciente.getDui(),
            "Genero: " + generoDisplay,
            "Fecha Nac.: " + paciente.getFechaNacimiento(),
            "Edad: " + paciente.getEdad() + " anos",
            "Comentarios: " + paciente.getComentariosSalud()
        };
        
        MenuUtils::mostrarCuadro(infoPaciente, MenuUtils::VERDE);
    }
