// citas.cpp: Este archivo de implementación contiene las definiciones de los métodos de la clase Cita.

#include "modelos/Cita.h"
#include <iostream> 
#include <string>   

// Constructor por defecto de la clase Cita.
// Inicializa todos los miembros de datos de tipo string a cadenas vacías.
Cita::Cita() : duiPaciente(""), nombrePaciente(""), telefonoPaciente(""), tratamiento(""), fecha(""), hora(""), motivo("") {}

// Constructor con todos los campos para inicializar un objeto Cita.
// Utiliza una lista de inicializadores para asignar los valores pasados a los miembros de datos correspondientes.
Cita::Cita(const std::string& duiPaciente,
           const std::string& nombrePaciente,
           const std::string& telefonoPaciente,
           const std::string& tratamiento, 
           const std::string& fecha,
           const std::string& hora,
           const std::string& motivo)
    : duiPaciente(duiPaciente),
      nombrePaciente(nombrePaciente),
      telefonoPaciente(telefonoPaciente),
      tratamiento(tratamiento),
      fecha(fecha),
      hora(hora),
      motivo(motivo) {}

// Getters 

// Retorna el DUI del paciente.
std::string Cita::getDuiPaciente() const { return duiPaciente; }
// Retorna el nombre del paciente.
std::string Cita::getNombrePaciente() const { return nombrePaciente; }
// Retorna el número de teléfono del paciente.
std::string Cita::getTelefonoPaciente() const { return telefonoPaciente; }
// Retorna el tratamiento de la cita.
std::string Cita::getTratamiento() const { return tratamiento; }
// Retorna la fecha de la cita.
std::string Cita::getFecha() const { return fecha; }
// Retorna la hora de la cita.
std::string Cita::getHora() const { return hora; }
// Retorna el motivo de la cita.
std::string Cita::getMotivo() const { return motivo; }

// Setters 

// Establece el DUI del paciente.
void Cita::setDuiPaciente(const std::string& dui) { duiPaciente = dui; }
// Establece el nombre del paciente.
void Cita::setNombrePaciente(const std::string& nombre) { nombrePaciente = nombre; }
// Establece el número de teléfono del paciente.
void Cita::setTelefonoPaciente(const std::string& telefono) { telefonoPaciente = telefono; }
// Establece el tratamiento de la cita.
void Cita::setTratamiento(const std::string& trat) { tratamiento = trat; }
// Establece la fecha de la cita.
void Cita::setFecha(const std::string& fec) { fecha = fec; }
// Establece la hora de la cita.
void Cita::setHora(const std::string& h) { hora = h; }
// Establece el motivo de la cita.
void Cita::setMotivo(const std::string& m) { motivo = m; }

// Método para convertir la información de la cita a una cadena de texto.
// Es útil para guardar los datos de la cita en un archivo, utilizando '|' como delimitador.
std::string Cita::toString() const {
    return duiPaciente + "|" + nombrePaciente + "|" + telefonoPaciente + "|" + tratamiento + "|" + fecha + "|" + hora + "|" + motivo;
}