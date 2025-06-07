#pragma once
#include "PacienteServicio.h"

class PacienteMenu {
private:
    PacienteServicio& servicio;
    
    /**
     * @brief Muestra un banner del modulo actual
     */
    void mostrarBannerPacientes();

        /**
     * @brief Listado Pacientes
     * @details Muestra en una tabla el listado de los paciente
     */
    void mostrarPacienteDetallado(const Paciente& paciente);

public:
    // constructor que recibe el servicio a utilizar
    PacienteMenu(PacienteServicio& servicio);

    /**
     * @brief Inicia la ejecucion del menu principal de pacinetes.
     */
    void ejecutar();

    /**
     * @brief Opciones Menu pacientes.
     *
     * Presenta las diferentes acciones que el usuario puede realizar
     * dentro del sistema, como agregar, editar, buscar o listar pacientes.
     */
    void mostrarMenu();

    /**
     * @brief Permite al usuario agregar un nuevo paciente al sistema.
     *
     * Solicita los datos necesarios del paciente, los valida
     * y los guarda en la estructura de almacenamiento
     */
    void agregarPaciente();

    /**
     * @brief Permite al usuario editar los datos de un paciente existente.
     *
     * Solicita un identificador para buscar al paciente, y si lo encuentra,
     * permite modificar sus atributos.
     */
    void editarPaciente();

    /**
     * @brief Permite al usuario buscar y mostrar la información de un paciente especifico.
     *
     * Solicita un criterio de búsqueda
     * y muestra los detalles del paciente encontrado.
     */
    void buscarPaciente();

    /**
     * @brief Muestra una lista de todos los pacientes registrados en el sistema.
     *
     * Itera sobre la colección de pacientes y presenta un resumen de cada uno.
     */
    void listarPacientes();

    /**
     * @brief Muestra en detalle la información de un paciente individual.
     * @param paciente Objeto Paciente constante por referencia que contiene los datos a mostrar.
     *
     * Presenta todos los atributos de un objeto Paciente dado en un formato legible.
     */
    void mostrarPaciente(const Paciente& paciente);
};