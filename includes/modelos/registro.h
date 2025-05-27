// Descripción: Clase base abstracta para registros binarios en el sistema

#ifndef REGISTRO_H
#define REGISTRO_H

class Registro {
public:
    virtual void registrar() = 0;
    virtual void mostrar() const = 0;
    virtual void editar() = 0;
    virtual void eliminar() = 0;
    virtual ~Registro() = default;
};

#endif