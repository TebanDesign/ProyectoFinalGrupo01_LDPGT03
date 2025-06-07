// citasmenu.cpp: Este archivo de implementación contiene las definiciones de los métodos de la clase CitasMenu.

#include "menu/CitasMenu.h"       
#include "menu/MenuUtils.h"       
#include "utils/Validaciones.h"   
#include "modelos/Cita.h"         
#include "modelos/Tratamiento.h"  
#include <iostream>               
#include <iomanip>               
#include <vector>                 
#include <limits>                 


// Constructor de la clase CitasMenu.
// Inicializa el objeto servicio con el nombre del archivo de datos de citas.
CitasMenu::CitasMenu() : servicio("citas.dat") {}

// Método principal para ejecutar el menú de gestión de citas.
// Muestra el menú, lee la opción del usuario y ejecuta la acción correspondiente.
void CitasMenu::ejecutar() {
    int opcion;
    do {
        mostrarMenu(); // Muestra las opciones del menú.
        int minOpcion = 1;
        int maxOpcion = 5; // La opción 5 (salir) siempre está disponible.

        opcion = MenuUtils::leerOpcion(minOpcion, maxOpcion); // Lee la opción del usuario dentro del rango válido.

        switch(opcion) {
            case 1: // Opción para agregar una nueva cita.
                MenuUtils::limpiarPantalla(); // Limpia la consola.
                agregarCita();                // Llama al método para agregar cita.
                MenuUtils::pausar();          // Pausa la ejecución hasta que el usuario presione una tecla.
                break;
            case 2: // Opción para listar todas las citas.
                if (servicio.archivoTieneDatos()) { // Solo si hay citas registradas.
                    MenuUtils::limpiarPantalla();
                    listarCitas();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("Debe agregar citas primero."); // Mensaje de advertencia.
                    MenuUtils::pausar();
                }
                break;
            case 3: // Opción para editar una cita.
                if (servicio.archivoTieneDatos()) { // Solo si hay citas registradas.
                    MenuUtils::limpiarPantalla();
                    editarCitaMenu();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("No hay citas para editar.");
                    MenuUtils::pausar();
                }
                break;
            case 4: // Opción para buscar citas por DUI.
                if (servicio.archivoTieneDatos()) { // Solo si hay citas registradas.
                    MenuUtils::limpiarPantalla();
                    buscarCitas();
                    MenuUtils::pausar();
                } else {
                    MenuUtils::mostrarMensajeAdvertencia("No hay citas para buscar.");
                    MenuUtils::pausar();
                }
                break;
            case 5: // Opción para regresar al menú principal.
                MenuUtils::mostrarMensaje("Regresando al menú principal...", MenuUtils::AMARILLO);
                MenuUtils::mostrarCargando("Cerrando módulo"); // Simula un proceso de carga.
                break;
            default: // En caso de que se ingrese una opción válida numéricamente pero deshabilitada lógicamente.
                     // Aunque leerOpcion debería evitar esto, es un buen fallback.
                MenuUtils::mostrarMensajeError("Opción no disponible en este momento. Intente de nuevo.");
                MenuUtils::pausar();
                break;
        }
    } while (opcion != 5); // Continúa el bucle hasta que el usuario elija regresar (opción 5).
}

// Muestra las opciones del menú de citas en la consola.
void CitasMenu::mostrarMenu() {
    MenuUtils::limpiarPantalla(); // Limpia la pantalla antes de mostrar el menú.
    mostrarBanner();             // Muestra el banner del módulo.
    MenuUtils::mostrarTitulo("GESTIÓN DE CITAS", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO); // Título del menú.
    std::cout << "\n";

    // Muestra las opciones. Algunas opciones se habilitan solo si hay datos.
    MenuUtils::mostrarOpcion(1, "Agregar nueva cita");
    // Las opciones 2, 3 y 4 se muestran deshabilitadas si no hay datos, pero son elegibles para 'leerOpcion'
    MenuUtils::mostrarOpcion(2, "Listar todas las citas", servicio.archivoTieneDatos());
    MenuUtils::mostrarOpcion(3, "Editar cita", servicio.archivoTieneDatos());
    MenuUtils::mostrarOpcion(4, "Buscar citas por DUI", servicio.archivoTieneDatos());
    MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS); // Separador visual.
    MenuUtils::mostrarOpcion(5, "Regresar al menú principal");
}

// Muestra el banner del módulo de citas.
void CitasMenu::mostrarBanner() {
    std::vector<std::string> banner = {
        "MODULO DE CITAS",
        "Registro y gestión de citas"
    };
    MenuUtils::mostrarCuadro(banner, MenuUtils::AZUL); // Muestra el banner dentro de un cuadro con color.
}

// Permite al usuario agregar una nueva cita.
void CitasMenu::agregarCita() {
    MenuUtils::mostrarTitulo("AGREGAR NUEVA CITA", MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);

    std::string dui, nombre, telefono, fecha, hora, motivo;
    // El campo 'tratamiento' en la Cita se inicializará vacío ya que se rellenará dinámicamente al listar.
    std::string tratamientoAsociadoEnCita = ""; // Lo inicializamos vacío.

    MenuUtils::mostrarMensaje("Ingrese los datos de la cita:", MenuUtils::CYAN);
    std::cout << "\n";

    // Solicitar DUI del paciente
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "DUI del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, dui);

    // Solicitar nombre del paciente
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nombre del paciente: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nombre);

    // Solicitar número de teléfono
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Número de teléfono: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, telefono);

    // Validar y solicitar la fecha
    do {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        std::cout << "Fecha (DD/MM/AAAA): ";
        MenuUtils::restaurarColor();
        std::getline(std::cin >> std::ws, fecha);
        if (!Validaciones::validarFecha(fecha)) {
            MenuUtils::mostrarMensajeError("Fecha inválida. Formato esperado DD/MM/AAAA.");
        }
    } while (!Validaciones::validarFecha(fecha));

    // Solicitar la hora
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Hora (HH:MM AM/PM): ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, hora);

    // Solicitar el motivo de la cita
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Motivo de la cita: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, motivo);

    // Crea un objeto Cita con los datos ingresados.
    // El campo 'tratamiento' se pasa vacío aquí, ya que se llenará al listar dinámicamente.
    Cita cita(dui, nombre, telefono, tratamientoAsociadoEnCita, fecha, hora, motivo);
    MenuUtils::mostrarCargando("Guardando cita"); // Muestra un mensaje de carga.

    // Intenta agregar la cita utilizando el servicio.
    if (servicio.agregarCita(cita)) {
        MenuUtils::mostrarMensajeExito("Cita agregada exitosamente!"); // Mensaje de éxito.
    } else {
        MenuUtils::mostrarMensajeError("Error al guardar la cita."); // Mensaje de error.
    }
}

// Muestra una lista formateada de todas las citas registradas.
void CitasMenu::listarCitas() {
    MenuUtils::mostrarTitulo("LISTADO DE CITAS", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    auto citas = servicio.obtenerTodasLasCitas(); // Obtiene todas las citas desde el servicio.
    if (citas.empty()) {
        MenuUtils::mostrarMensajeAdvertencia("No hay citas registradas."); // Mensaje si no hay citas.
        return;
    }

    MenuUtils::mostrarMensaje("Total de citas: " + std::to_string(citas.size()), MenuUtils::CYAN);
    MenuUtils::mostrarSeparador('=', 155, MenuUtils::GRIS); // Ancho ajustado para el tratamiento
    MenuUtils::cambiarColor(MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
    // Encabezados de la tabla de citas.
    std::cout << std::left << std::setw(15) << "DUI"
              << std::setw(25) << "Nombre"
              << std::setw(15) << "Teléfono"
              << std::setw(30) << "Tratamiento Asociado" // Nuevo encabezado más ancho
              << std::setw(15) << "Fecha"
              << std::setw(10) << "Hora"
              << "Motivo" << std::endl;
    MenuUtils::restaurarColor();
    MenuUtils::mostrarSeparador('-', 155, MenuUtils::GRIS); // Ajustar ancho

    
    std::vector<Tratamiento> todosLosTratamientos = cargarTratamientosDesdeArchivo();

    // Itera sobre cada cita y la imprime en un formato tabular.
    for (size_t i = 0; i < citas.size(); ++i) {
        const auto& c = citas[i];

        // Obtener el tratamiento asociado al DUI de la cita
        std::string tratamientoMostrado = "-"; // Valor por defecto si no se encuentra tratamiento

        // Buscar el primer tratamiento "Activo" para el DUI del paciente
        for (const auto& t : todosLosTratamientos) {
            if (t.getDUI() == c.getDuiPaciente() && t.getEstado() == "Activo") {
                tratamientoMostrado = t.getMedicamento() + " (" + t.getDosis() + ")"; // Combinar medicamento y dosis
                break; // Tomar el primer tratamiento activo encontrado
            }
        }

        // Alterna colores de fondo para las filas para mejor legibilidad.
        if (i % 2 == 0)
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO_OSCURO);
        else
            MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);

        std::cout << std::left << std::setw(15) << c.getDuiPaciente()
                  << std::setw(25) << c.getNombrePaciente()
                  << std::setw(15) << c.getTelefonoPaciente()
                  << std::setw(30) << tratamientoMostrado // Mostrar el tratamiento obtenido o el guion
                  << std::setw(15) << c.getFecha()
                  << std::setw(10) << c.getHora()
                  << c.getMotivo() << std::endl;
    }

    MenuUtils::restaurarColor(); // Restaura los colores de la consola.
    MenuUtils::mostrarSeparador('=', 155, MenuUtils::GRIS); // Ajustar ancho
}

// Permite al usuario editar una cita existente.
void CitasMenu::editarCitaMenu() {
    MenuUtils::mostrarTitulo("EDITAR CITA", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    std::string duiOriginal, fechaOriginal, horaOriginal;

    std::cout << "\nIngrese los datos de la cita a editar (para identificarla):\n";

    // Solicitar DUI, fecha y hora originales para identificar la cita.
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "DUI del paciente (original): ";
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

    // Buscar la cita original para obtener los datos actuales.
    // Usamos el metodo buscarCita del servicio que retorna un objeto Cita
    Cita citaOriginal = servicio.buscarCita(duiOriginal, fechaOriginal, horaOriginal);

    // Asumimos que un DUI vacío en el objeto Cita retornado significa que no se encontró.
    if (citaOriginal.getDuiPaciente().empty()) {
        MenuUtils::mostrarMensajeError("No se encontró una cita con los datos proporcionados.");
        return;
    }

    std::cout << "\nCita encontrada. Ingrese los nuevos datos:\n";

    std::string nuevoDui = citaOriginal.getDuiPaciente(); // Inicializamos con el valor actual
    std::string nuevoNombre = citaOriginal.getNombrePaciente();
    std::string nuevoTelefono = citaOriginal.getTelefonoPaciente();
    std::string nuevaFecha = citaOriginal.getFecha();
    std::string nuevaHora = citaOriginal.getHora();
    std::string nuevoMotivo = citaOriginal.getMotivo();
    std::string tratamientoActualCita = citaOriginal.getTratamiento(); // Se mantiene como estaba en la cita original


    // Recopilar nuevos datos, usando los originales como valor por defecto si el usuario deja en blanco
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo DUI del paciente [" << citaOriginal.getDuiPaciente() << "]: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoDui);
    if (nuevoDui.empty()) {
        nuevoDui = citaOriginal.getDuiPaciente();
    }

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo nombre del paciente [" << citaOriginal.getNombrePaciente() << "]: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoNombre);
    if (nuevoNombre.empty()) {
        nuevoNombre = citaOriginal.getNombrePaciente();
    }

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo número de teléfono [" << citaOriginal.getTelefonoPaciente() << "]: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoTelefono);
    if (nuevoTelefono.empty()) {
        nuevoTelefono = citaOriginal.getTelefonoPaciente();
    }


    std::string nuevaFechaStr;
    do {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
        std::cout << "Nueva fecha (DD/MM/AAAA) [" << citaOriginal.getFecha() << "]: ";
        MenuUtils::restaurarColor();
        std::getline(std::cin >> std::ws, nuevaFechaStr);
        if (nuevaFechaStr.empty()) {
            nuevaFecha = citaOriginal.getFecha();
            break; // Salir del bucle si no se ingresa nada y se mantiene la fecha actual.
        }
        if (!Validaciones::validarFecha(nuevaFechaStr)) {
            MenuUtils::mostrarMensajeError("Fecha inválida. Formato esperado DD/MM/AAAA.");
        } else {
            nuevaFecha = nuevaFechaStr;
        }
    } while (!Validaciones::validarFecha(nuevaFechaStr) && !nuevaFechaStr.empty());


    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nueva hora (HH:MM AM/PM) [" << citaOriginal.getHora() << "]: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevaHora);
    if (nuevaHora.empty()) {
        nuevaHora = citaOriginal.getHora();
    }

    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Nuevo motivo de la cita [" << citaOriginal.getMotivo() << "]: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, nuevoMotivo);
    if (nuevoMotivo.empty()) {
        nuevoMotivo = citaOriginal.getMotivo();
    }

    // Crea un nuevo objeto Cita con los datos actualizados.
    // Se incluye el tratamientoActualCita para mantenerlo en el objeto Cita
    Cita citaActualizada(nuevoDui, nuevoNombre, nuevoTelefono, tratamientoActualCita, nuevaFecha, nuevaHora, nuevoMotivo);

    MenuUtils::mostrarCargando("Actualizando cita");
    // Llama al servicio para editar la cita con los nuevos datos.
    // La firma ahora espera (duiOriginal, fechaOriginal, horaOriginal, citaActualizada)
    if (servicio.editarCita(duiOriginal, fechaOriginal, horaOriginal, citaActualizada)) {
        MenuUtils::mostrarMensajeExito("Cita actualizada exitosamente!");
    } else {
        MenuUtils::mostrarMensajeError("Error al actualizar la cita o no se encontró la cita original.");
    }
}

// Permite buscar y mostrar citas por el DUI del paciente.
void CitasMenu::buscarCitas() {
    MenuUtils::mostrarTitulo("BUSCAR CITAS POR DUI", MenuUtils::MAGENTA_OSCURO, MenuUtils::BLANCO);

    std::string duiABuscar;
    MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::BLANCO);
    std::cout << "Ingrese el DUI del paciente a buscar: ";
    MenuUtils::restaurarColor();
    std::getline(std::cin >> std::ws, duiABuscar);

    auto resultados = servicio.buscarCitasPorDui(duiABuscar); // Obtiene citas que coinciden con el DUI.

    std::cout << "\nResultados de la búsqueda para el DUI: " << duiABuscar << "\n";

    if (resultados.empty()) {
        MenuUtils::mostrarMensajeAdvertencia("No se encontraron citas para ese DUI."); // Mensaje si no hay resultados.
    } else {
        MenuUtils::mostrarMensaje("Se encontraron " + std::to_string(resultados.size()) + " citas.", MenuUtils::CYAN);
        MenuUtils::mostrarSeparador('=', 155, MenuUtils::GRIS); // Aumentar ancho
        MenuUtils::cambiarColor(MenuUtils::AZUL_OSCURO, MenuUtils::BLANCO);
        // Encabezados de la tabla de resultados de búsqueda.
        std::cout << std::left << std::setw(15) << "DUI"
                  << std::setw(25) << "Nombre"
                  << std::setw(15) << "Teléfono"
                  << std::setw(30) << "Tratamiento Asociado" // Nuevo encabezado
                  << std::setw(15) << "Fecha"
                  << std::setw(10) << "Hora"
                  << "Motivo" << std::endl;
        MenuUtils::restaurarColor();
        MenuUtils::mostrarSeparador('-', 155, MenuUtils::GRIS); // Ajustar ancho

        std::vector<Tratamiento> todosLosTratamientos = cargarTratamientosDesdeArchivo();

        // Imprime cada cita encontrada en formato tabular.
        for (const auto& cita : resultados) {
            std::string tratamientoMostrado = "-"; // Valor por defecto
            for (const auto& t : todosLosTratamientos) {
                if (t.getDUI() == cita.getDuiPaciente() && t.getEstado() == "Activo") {
                    tratamientoMostrado = t.getMedicamento() + " (" + t.getDosis() + ")";
                    break;
                }
            }

            std::cout << std::left << std::setw(15) << cita.getDuiPaciente()
                      << std::setw(25) << cita.getNombrePaciente()
                      << std::setw(15) << cita.getTelefonoPaciente()
                      << std::setw(30) << tratamientoMostrado // Mostrar el tratamiento obtenido o el guion
                      << std::setw(15) << cita.getFecha()
                      << std::setw(10) << cita.getHora()
                      << cita.getMotivo() << std::endl;
        }
        MenuUtils::mostrarSeparador('=', 155, MenuUtils::GRIS); // Ajustar ancho
    }
}