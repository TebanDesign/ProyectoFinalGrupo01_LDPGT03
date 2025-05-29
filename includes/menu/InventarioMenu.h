#ifndef INVENTARIOMENU_H
#define INVENTARIOMENU_H

class InventarioServicio;

class InventarioMenu {
public:
    explicit InventarioMenu(InventarioServicio& servicio);
    void ejecutar();

private:
    InventarioServicio& inventarioServicio;
    void mostrarBannerInventario();
};

#endif