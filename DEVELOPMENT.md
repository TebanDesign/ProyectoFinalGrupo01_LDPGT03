Aquí tienes el texto con formato Markdown:

---

## Creación de árbol de archivos para la gestión de archivos binarios

La funcionalidad para crear el árbol de archivos es de la siguiente manera:

    ```cpp
    /**
     * @brief crea un archivo binario organizado en la estructura modelo/año/mes
     *
     * @param modelo Obligatorio: Nombre del modelo (primer nivel de directorio) (eje. Pacientes)
     * @param nombreArchivo Obligatorio: Nombre del archivo a crear (eje. Pacientes.dat)
     * @param anio Opcional: Año (segundo nivel de directorio)
     * @param mes  Opcional: Mes (tercer nivel de directorio)
     * @return std::string Ruta del archivo creado
     *
     * @note Si el año es igual a 0 (valor por defecto), se omite el nivel de directorio del año
     * @note Si el mes es una cadena vacía (valor por defecto), se omite el nivel de directorio del mes
     */
    static std::string escribirArchivoBinarioOrganizado(
        const std::string& nombreArchivo,
        const std::string& modelo,
        int anio = 0,
        const std::string& mes = ""
    );
    ```

1.  Recomiendo crear una variable en el encabezado de sus servicios para la ruta del archivo. Ejemplo:
    En `PacienteServicio.h`

    ```cpp
        std::string rutaArchivo; // para almacenar la ruta completa del archivo a utilizar
    ```

2.  Importar `#include "utils/fileSistem.h"` en el lugar donde actualmente crean su archivo, generalmente en el servicio.
    En el constructor del servicio usar el método para la creación del árbol de archivos

    ```cpp
    PacienteServicio::PacienteServicio(const string& nombreArchivo) : nombreArchivo(nombreArchivo) {
        rutaArchivo = FileSistem::escribirArchivoBinarioOrganizado(nombreArchivo,"Pacientes");
        ofstream archivo(rutaArchivo, ios::binary | ios::app);
        archivo.close();
    }
    ```

3.  En cada método donde abren su archivo binario para escribir o leer deben cambiar la variable actual, la cual solo es el nombre del archivo, por la ruta completa `rutaArchivo`, que se capturó en el paso anterior.

    ```cpp
    // abrir el archivo en modo lectura/escritura
    std::fstream archivo(rutaArchivo, std::ios::binary | std::ios::in | std::ios::out);
    ```