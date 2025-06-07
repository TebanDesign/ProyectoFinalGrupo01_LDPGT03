#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class Paciente {
private:
    std::string nombre;
    std::string dui;
    std::string genero;
    std::string fechaNacimiento;
    std::string edad; // se calcula a partir de la fecha de nacimiento (dd/MM/yyyy)
    std::string comentariosSalud;

public:
    // constructor por defecto
    Paciente();
    
    // constructor con parametros
    Paciente(
            std::string& nombre,
            std::string& dui, 
            std::string& genero,
            std::string& fechaNacimiento,
            std::string& comentarios
        );
    
    // getters
    std::string getNombre() const;
    std::string getDui() const;
    std::string getGenero() const;
    std::string getFechaNacimiento() const;
    std::string getEdad() const;
    std::string getComentariosSalud() const;
    
    // setters
    void setNombre(const std::string& nombre);
    void setDui(const std::string& dui);
    void setGenero(const std::string& genero);
    void setFechaNacimiento(const std::string& fechaNacimiento);
    void setComentariosSalud(const std::string& comentarios);

};

#endif
