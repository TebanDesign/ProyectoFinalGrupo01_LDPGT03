// cita.h: Este archivo de cabecera define la interfaz de la clase Cita.

#ifndef CITA_H 
#define CITA_H

#include <string> 

// Declaración de la clase Cita.
class Cita {
private:
    // Miembros de datos privados que representan los atributos de una cita.
    std::string duiPaciente;
    std::string nombrePaciente;
    std::string telefonoPaciente;
    std::string tratamiento; 
    std::string fecha;
    std::string hora;
    std::string motivo;

public:
    Cita();
    // Constructor con parámetros para inicializar todos los campos de una cita.
    Cita(const std::string& duiPaciente, const std::string& nombrePaciente, const std::string& telefonoPaciente, const std::string& tratamiento, const std::string& fecha, const std::string& hora, const std::string& motivo);

    // --- Getters (Métodos para obtener los valores de los atributos) ---
    std::string getDuiPaciente() const;
    std::string getNombrePaciente() const;
    std::string getTelefonoPaciente() const;
    std::string getTratamiento() const;
    std::string getFecha() const;
    std::string getHora() const;
    std::string getMotivo() const;

    // --- Setters (Métodos para modificar los valores de los atributos) ---
    void setDuiPaciente(const std::string& dui);
    void setNombrePaciente(const std::string& nombre);
    void setTelefonoPaciente(const std::string& telefono);
    void setTratamiento(const std::string& trat);
    void setFecha(const std::string& fec);
    void setHora(const std::string& h);
    void setMotivo(const std::string& m);

    // Método para convertir los datos de la cita a una cadena de texto.
    std::string toString() const;
};

#endif 