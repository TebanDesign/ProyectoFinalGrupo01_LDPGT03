#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <vector>

class Lote {
private:
    int cantidad;
    std::string fechaVencimiento;
    std::string fechaIngreso;
    float precioUnitario;

public:
    Lote();
    Lote(int cantidad, const std::string& fechaVencimiento, float precioUnitario, const std::string& fechaIngreso);

    // Getters
    int getCantidad() const;
    std::string getFechaVencimiento() const;
    std::string getFechaIngreso() const;
    float getPrecioUnitario() const;
    bool estaVencido() const;

    // Setters
    void setCantidad(int cantidad);
    void setFechaVencimiento(const std::string& fecha);
    void setFechaIngreso(const std::string& fecha);
    void setPrecioUnitario(float precio);
};

class Inventario {
private:
    std::string nombre;
    std::string codigo;
    std::string unidad;
    std::string presentacion;
    std::vector<Lote> lotes;

public:
    Inventario();
    Inventario(const std::string& nombre, const std::string& codigo, 
               const std::string& unidad, const std::string& presentacion);

    // Getters
    std::string getNombre() const;
    std::string getCodigo() const;
    std::string getUnidad() const;
    std::string getPresentacion() const;
    std::vector<Lote>& getLotes();
    const std::vector<Lote>& getLotes() const;
    int getStockTotal() const;

    // Setters
    void setNombre(const std::string& nombre);
    void setCodigo(const std::string& codigo);
    void setUnidad(const std::string& unidad);
    void setPresentacion(const std::string& presentacion);

    void agregarLote(const Lote& lote);
    void mostrarLotes() const;
};

#endif