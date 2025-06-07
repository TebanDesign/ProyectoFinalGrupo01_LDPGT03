#ifndef PACIENTE_SERVICE_H
#define PACIENTE_SERVICE_H

#include "Paciente.h"
#include <vector>
#include <string>
#include <fstream>

class PacienteServicio {
private:
    std::string nombreArchivo;  //nombre del archivo binario
    std::string rutaArchivo; // para almacenar la ruta completa del archivo a utilizar

    /**
     * @brief Busca la posicion de un paciente en el archivo binario por su numero de DUI.
     * @param dui El numero de DUI del paciente a buscar.
     * @return La posición donde se encuentra el registro del paciente.
     * Retorna -1 si el paciente con el DUI especificado no es encontrado.
     */
    long buscarPosicionPorDui(const std::string& dui);

    /**
     * @brief Serializa (escribe) un objeto Paciente en un archivo binario.
     * @param archivo Referencia al flujo del archivo binario abierto en modo de escritura.
     * @param paciente Objeto Paciente constante por referencia a serializar.
     * @return true si la serialización fue exitosa, false en caso contrario.
     */
    bool serializarPaciente(std::fstream& archivo, const Paciente& paciente);

    /**
     * @brief Deserializa (lee) un objeto Paciente de un archivo binario.
     * @param archivo Referencia al flujo del archivo binario abierto en modo de lectura.
     * @return Un objeto Paciente con los datos leidos del archivo.
     */
    Paciente deserializarPaciente(std::ifstream& archivo);
    /**
     * @brief Lee una cadena de texto desde un archivo binario.
     * @param archivo Referencia al flujo del archivo binario abierto en modo de lectura.
     * @return La cadena de texto leida del archivo.
     */
    std::string leerString(std::ifstream& archivo);

    /**
     * @brief Escribe una cadena de texto en un archivo binario.
     * @param archivo Referencia al flujo del archivo binario abierto en modo de escritura.
     * @param texto La cadena de texto a escribir.
     */
    void escribirString(std::fstream& archivo, std::string& texto);


public:
    // constructor que recibe el nombre del archivo a utilizar
    PacienteServicio(const std::string& nombreArchivo);
    
    /**
     * @brief Agrega un nuevo paciente al sistema.
     * @param paciente Objeto Paciente constante por referencia a agregar.
     * @return true si el paciente fue agregado exitosamente, false si ya existe un paciente con el mismo DUI.
     */
    bool agregarPaciente(const Paciente& paciente);

    /**
     * @brief Edita la informacion de un paciente existente.
     * @param duiOriginal El DUI original del paciente a editar.
     * @param pacienteActualizado Objeto Paciente constante por referencia con la nueva información.
     * @return true si el paciente fue editado exitosamente, false si no se encontro el paciente original.
     */
    bool editarPaciente(const std::string& duiOriginal, const Paciente& pacienteActualizado);

    /**
     * @brief Busca y retorna un paciente por su numero de DUI.
     * @param duiPaciente El numero de DUI del paciente a buscar.
     * @return Un objeto Paciente si es encontrado. Retorna un objeto Paciente con un estado "vacío" o predeterminado
     * si el paciente no es encontrado.
     */
    Paciente buscarPorDui(const std::string& duiPaciente);

    /**
     * @brief Obtiene una lista de todos los pacientes registrados en el sistema.
     * @return Un vector de objetos Paciente que contiene todos los pacientes.
     */
    std::vector<Paciente> obtenerTodosLosPacientes();

    /**
     * @brief Verifica si el archivo de datos de pacientes contiene informacion.
     * @return true si el archivo tiene datos (su tamaño es mayor a 0), false en caso contrario.
     */
    bool archivoTieneDatos(); 
};

#endif
