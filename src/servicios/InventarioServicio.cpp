#include "servicios/InventarioServicio.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "utils/Validaciones.h"
#include "menu/MenuUtils.h"


// Función auxiliar para limpiar entrada inválida
void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/******************************************************************************
 * Constructor: Inicializa el servicio con el nombre del archivo y crea la 
 * estructura de directorios organizada usando el sistema de archivos.
 * 
 * @param nombreArchivo Nombre base del archivo (ej: "inventario.dat")
 ******************************************************************************/
InventarioServicio::InventarioServicio(const std::string& nombreArchivo) {
    try {
        // Crear estructura organizada de directorios y obtener ruta completa
        rutaArchivo = FileSistem::escribirArchivoBinarioOrganizado(
            nombreArchivo,    // Nombre del archivo
            "Inventario",     // Modelo (primer nivel de directorio)
            0,                // Año (0 = no usar nivel de año)
            ""                // Mes (vacío = no usar nivel de mes)
        );
        
        // Crear el archivo si no existe
        std::ofstream archivo(rutaArchivo, std::ios::app);
        if (archivo.is_open()) {
            archivo.close();
        }
        
        // Cargar datos existentes
        cargarDesdeArchivo();
        
    } catch (const std::exception& e) {
        // Manejo de errores en la creación de directorios/archivos
        std::cerr << "\n[ERROR] " << e.what() << std::endl;
        rutaArchivo = nombreArchivo; // Usar ruta simple como fallback
        MenuUtils::pausar();
    }
}

/******************************************************************************
 * Agregar un nuevo lote al inventario.
 * 
 * @param nuevoLote Lote a agregar. Se guarda automáticamente en archivo.
 ******************************************************************************/
void InventarioServicio::agregarLote(const Inventario& nuevoLote) {
    inventarios.push_back(nuevoLote);
    guardarEnArchivo(); // Persistir en el archivo organizado
    std::cout << "Lote agregado exitosamente.\n";
}

void InventarioServicio::mostrarInventario() const {
    std::cout << "\n=== INVENTARIO DE MEDICAMENTOS ===\n";
    std::cout << std::left << std::setw(20) << "Nombre"
              << std::setw(10) << "Codigo"
              << std::setw(15) << "Presentacion"
              << std::setw(10) << "Stock"
              << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (const auto& item : inventarios) {
        std::cout << std::left << std::setw(20) << item.getNombre()
                  << std::setw(10) << item.getCodigo()
                  << std::setw(15) << item.getPresentacion()
                  << std::setw(10) << item.getStockTotal()
                  << std::endl;
    }
}

std::vector<Inventario> InventarioServicio::buscarPorNombre(const std::string& nombre) const {
    std::vector<Inventario> resultados;
    for (const auto& item : inventarios) {
        if (item.getNombre().find(nombre) != std::string::npos) {
            resultados.push_back(item);
        }
    }
    return resultados;
}

bool InventarioServicio::existenMedicamentos() const {
    return !inventarios.empty();
}

/******************************************************************************
 * Agregar un nuevo medicamento al inventario.
 * 
 * Solicita datos al usuario, crea el medicamento y su primer lote,
 * y guarda automáticamente en el archivo organizado.
 ******************************************************************************/
void InventarioServicio::agregarMedicamento() {
    std::string nombre, codigo, unidad, presentacion;
    
    MenuUtils::mostrarTitulo("AGREGAR NUEVO MEDICAMENTO", MenuUtils::VERDE, MenuUtils::BLANCO);
    std::cout << "\nNombre: ";
    std::getline(std::cin, nombre);
    
    std::cout << "Codigo: ";
    std::getline(std::cin, codigo);
    
    std::cout << "Unidad: ";
    std::getline(std::cin, unidad);
    
    std::cout << "Presentacion: ";
    std::getline(std::cin, presentacion);
    
    Inventario nuevoMed(nombre, codigo, unidad, presentacion);
    inventarios.push_back(nuevoMed);
    
    // Agregar el primer lote automáticamente
    aumentarStock(nombre);
    
    MenuUtils::mostrarMensajeExito("Medicamento agregado exitosamente!");
    guardarEnArchivo();
}

void InventarioServicio::editarMedicamento() {
    if (inventarios.empty()) {
        MenuUtils::mostrarMensajeError("No hay medicamentos registrados.");
        return;
    }

    MenuUtils::mostrarTitulo("EDITAR MEDICAMENTO", MenuUtils::AZUL, MenuUtils::BLANCO);
    
    // Paso 1: Mostrar lista de medicamentos disponibles
    std::cout << "\nMedicamentos disponibles:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < inventarios.size(); i++) {
        std::cout << (i + 1) << ". " << inventarios[i].getNombre() 
                  << " (" << inventarios[i].getCodigo() << ")\n";
    }
    
    // Paso 2: Seleccionar medicamento a editar
    int opcion;
    std::cout << "\nSeleccione el medicamento a editar (0 para cancelar): ";
    std::cin >> opcion;
    std::cin.ignore();
    
    if (opcion < 1 || opcion > inventarios.size()) {
        MenuUtils::mostrarMensaje("Operación cancelada.", MenuUtils::AMARILLO);
        return;
    }
    
    Inventario& medicamento = inventarios[opcion - 1];
    
    // Paso 3: Mostrar datos actuales
    std::cout << "\nDatos actuales del medicamento:\n";
    std::cout << "--------------------------------\n";
    std::cout << "1. Nombre: " << medicamento.getNombre() << "\n";
    std::cout << "2. Código: " << medicamento.getCodigo() << "\n";
    std::cout << "3. Unidad: " << medicamento.getUnidad() << "\n";
    std::cout << "4. Presentación: " << medicamento.getPresentacion() << "\n";
    
    // Paso 4: Seleccionar campo a modificar
    std::cout << "\nSeleccione el campo a modificar (0 para terminar): ";
    int campo;
    std::cin >> campo;
    std::cin.ignore();
    
    while (campo != 0) {
        std::string nuevoValor;
        
        switch (campo) {
            case 1:
                std::cout << "Nuevo nombre: ";
                std::getline(std::cin, nuevoValor);
                medicamento.setNombre(nuevoValor);
                break;
            case 2:
                std::cout << "Nuevo código: ";
                std::getline(std::cin, nuevoValor);
                medicamento.setCodigo(nuevoValor);
                break;
            case 3:
                std::cout << "Nueva unidad: ";
                std::getline(std::cin, nuevoValor);
                medicamento.setUnidad(nuevoValor);
                break;
            case 4:
                std::cout << "Nueva presentación: ";
                std::getline(std::cin, nuevoValor);
                medicamento.setPresentacion(nuevoValor);
                break;
            default:
                MenuUtils::mostrarMensajeError("Opción inválida.");
                break;
        }
        
        if (campo >= 1 && campo <= 4) {
            MenuUtils::mostrarMensajeExito("Campo actualizado correctamente!");
        }
        
        std::cout << "\nSeleccione otro campo a modificar (0 para terminar): ";
        std::cin >> campo;
        std::cin.ignore();
    }
    
    MenuUtils::mostrarMensajeExito("Medicamento actualizado exitosamente!");
    guardarEnArchivo();
}

void InventarioServicio::buscarMedicamento() {
    std::string nombre;
    std::cout << "Buscar medicamento: ";
    std::getline(std::cin, nombre);
    
    auto resultados = buscarPorNombre(nombre);
    if (resultados.empty()) {
        MenuUtils::mostrarMensajeError("No se encontraron medicamentos");
        return;
    }
    
    std::cout << "\nResultados de busqueda:\n";
    for (const auto& item : resultados) {
        std::cout << "- " << item.getNombre() << " (" << item.getCodigo() << ")\n";
    }
}

void InventarioServicio::listarMedicamentos() {
    mostrarInventario();
}

void InventarioServicio::aumentarStock() {
    if (inventarios.empty()) {
        MenuUtils::mostrarMensajeError("No hay medicamentos registrados.");
        return;
    }

    std::string nombre;
    std::cout << "Ingrese el nombre del medicamento: ";
    std::getline(std::cin, nombre);
    
    aumentarStock(nombre);
    guardarEnArchivo();
}

/******************************************************************************
 * Aumentar el stock de un medicamento existente.
 * 
 * @param nombreMedicamento Nombre del medicamento a actualizar.
 * Agrega un nuevo lote y guarda en el archivo organizado.
 ******************************************************************************/
void InventarioServicio::aumentarStock(const std::string& nombreMedicamento) {
    auto it = std::find_if(inventarios.begin(), inventarios.end(), 
        [&](const Inventario& med) { return med.getNombre() == nombreMedicamento; });
    
    if (it == inventarios.end()) {
        MenuUtils::mostrarMensajeError("Medicamento no encontrado.");
        return;
    }
    
    Inventario& medicamento = *it;
    
    std::string numeroLote, fechaIngreso, fechaVencimiento;
    int cantidad;
    float precio;
    
    std::cout << "\n=== NUEVO LOTE ===";
    std::cout << "\nNumero de lote: ";
    std::getline(std::cin, numeroLote);
    
    do {
        std::cout << "Fecha de ingreso (DD/MM/AAAA): ";
        std::getline(std::cin, fechaIngreso);
    } while (!Validaciones::validarFecha(fechaIngreso));
    
    do {
        std::cout << "Fecha de vencimiento (DD/MM/AAAA): ";
        std::getline(std::cin, fechaVencimiento);
    } while (!Validaciones::validarFecha(fechaVencimiento));
    
    std::cout << "Precio unitario: ";
    std::cin >> precio;
    std::cin.ignore();
    
    std::cout << "Cantidad: ";
    std::cin >> cantidad;
    std::cin.ignore();
    
    Lote nuevoLote(cantidad, fechaVencimiento, precio, fechaIngreso, numeroLote);
    medicamento.agregarLote(nuevoLote);
    
    guardarEnArchivo();
    MenuUtils::mostrarMensajeExito("Lote agregado exitosamente!");
    
}

void InventarioServicio::descontarMedicamento() {
    if (inventarios.empty()) {
        MenuUtils::mostrarMensajeError("No hay medicamentos registrados.");
        return;
    }

    std::string nombre;
    int cantidad;
    
    std::cout << "\n=== DESCONTAR MEDICAMENTO ===\n";
    std::cout << "Nombre del medicamento: ";
    std::getline(std::cin, nombre);
    
    std::cout << "Cantidad a descontar: ";
    std::cin >> cantidad;
    std::cin.ignore();
    
    if (descontarMedicamento(nombre, cantidad)) {

        guardarEnArchivo();
        MenuUtils::mostrarMensajeExito("Medicamento descontado exitosamente!");
        
    } else {
        MenuUtils::mostrarMensajeError("No se pudo descontar el medicamento");
    }
}

/******************************************************************************
 * Descontar cantidad de un medicamento (versión con parámetros).
 * 
 * @param medicamento Nombre del medicamento
 * @param cantidad Cantidad a descontar
 * @return true si se pudo descontar, false en caso contrario
 * Guarda automáticamente en el archivo organizado si tiene éxito.
 ******************************************************************************/
bool InventarioServicio::descontarMedicamento(const std::string& medicamento, int cantidad) {
    auto it = std::find_if(inventarios.begin(), inventarios.end(), 
        [&](const Inventario& med) { return med.getNombre() == medicamento; });
    
    if (it == inventarios.end()) {
        MenuUtils::mostrarMensajeError("Medicamento no encontrado.");
        return false;
    }
    
    Inventario& inv = *it;
    bool exito = inv.descontarPEPS(cantidad);
    
    if (exito) {
        guardarEnArchivo(); // Guardar solo si fue exitoso
    }
    return inv.descontarPEPS(cantidad);
    
}

/******************************************************************************
 * Cargar datos desde el archivo CSV organizado en la estructura de directorios.
 * 
 * Lee y parsea el archivo CSV, cargando medicamentos y sus lotes en memoria.
 ******************************************************************************/
void InventarioServicio::cargarDesdeArchivo() {
    std::ifstream archivo(rutaArchivo); // Usar ruta completa
    if (!archivo.is_open()) {
        std::cout << "Creando nuevo archivo de inventario..." << std::endl;
        return;
    }

    inventarios.clear();
    std::string linea;
    
    // Leer encabezados
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string nombre, codigo, unidad, presentacion;
        
        std::getline(ss, nombre, ',');
        std::getline(ss, codigo, ',');
        std::getline(ss, unidad, ',');
        std::getline(ss, presentacion, ',');
        
        Inventario nuevoMed(nombre, codigo, unidad, presentacion);
        
        // Leer lotes si existen
        std::string loteInfo;
        while (std::getline(ss, loteInfo, ';')) {
            std::istringstream loteSs(loteInfo);
            std::string numeroLote, cantidad, precio, fechaIngreso, fechaVencimiento;
            
            std::getline(loteSs, numeroLote, '|');
            std::getline(loteSs, cantidad, '|');
            std::getline(loteSs, precio, '|');
            std::getline(loteSs, fechaIngreso, '|');
            std::getline(loteSs, fechaVencimiento, '|');
            
            if (!numeroLote.empty()) {
                Lote nuevoLote(
                    std::stoi(cantidad),
                    fechaVencimiento,
                    std::stof(precio),
                    fechaIngreso,
                    numeroLote
                );
                nuevoMed.agregarLote(nuevoLote);
            }
        }
        
        inventarios.push_back(nuevoMed);
    }
    archivo.close();
}

/******************************************************************************
 * Guardar datos en el archivo CSV organizado en la estructura de directorios.
 * 
 * Escribe todos los medicamentos y sus lotes en formato CSV en el archivo.
 ******************************************************************************/
void InventarioServicio::guardarEnArchivo() const {
    std::ofstream archivo(rutaArchivo); // Usar ruta completa
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar: " << rutaArchivo << std::endl;
        return;
    }

    // Escribir encabezados
    archivo << "Nombre,Codigo,Unidad,Presentacion,Lotes\n";
    
    for (const auto& item : inventarios) {
        archivo << item.getNombre() << ","
                << item.getCodigo() << ","
                << item.getUnidad() << ","
                << item.getPresentacion() << ",";
        
        // Escribir lotes
        for (const auto& lote : item.getLotes()) {
            archivo << lote.getNumeroLote() << "|"
                    << lote.getCantidad() << "|"
                    << lote.getPrecioUnitario() << "|"
                    << lote.getFechaIngreso() << "|"
                    << lote.getFechaVencimiento() << ";";
        }
        
        archivo << "\n";
    }
    archivo.close();
}