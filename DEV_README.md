Here's your content formatted with Markdown for better readability:

---

# Instalación y Configuración de CMake

## 1. Descargar CMake

Descarga el instalador o los binarios de CMake desde su sitio oficial:
[https://cmake.org/download/](https://cmake.org/download/)

---

## 2. Descargar Ninja

Descarga la última versión de los binarios de Ninja desde GitHub:
[https://github.com/ninja-build/ninja/releases](https://github.com/ninja-build/ninja/releases)

Una vez descargado, **descomprime** el archivo y coloca el ejecutable `ninja.exe` en la siguiente ruta o en donde instalaste CMake :
`C:\Program Files\CMake\bin`

---

## 3. Configurar Variable de Entorno

Crea una **nueva variable de sistema** con el nombre `CMAKE_GENERATOR` y asigna como valor la ruta donde colocaste `ninja.exe`.

---

## 4. Proceso de Build

Navega hasta la **raíz de tu proyecto** y luego crea una carpeta llamada `build`. Ingresa a esa carpeta y ejecuta los siguientes comandos, uno después del otro:

```bash
cmake ..
```

```bash
cmake --build .
```

---
---

# Instalación y Configuración de FTXUI

Para integrar FTXUI en tu proyecto, sigue estos pasos:

## 1. Descargar FTXUI

Para asegurar una versión estable y evitar incompatibilidades por cambios continuos, descarga el proyecto FTXUI como un archivo ZIP desde el siguiente enlace:

* **[https://github.com/ArthurSonzogni/FTXUI](https://github.com/ArthurSonzogni/FTXUI)**

## 2. Descomprimir y Renombrar

Una vez descargado, **descomprime** el archivo ZIP. Luego, mueve la carpeta resultante a tu directorio `extern` y **renómbrala** a `ftxui`.

## 3. Actualizar `CMakeLists.txt`

Debes incluir FTXUI en tu configuración de CMake. Abre tu archivo `CMakeLists.txt` y añade la siguiente línea:

```cmake
add_subdirectory(extern/ftxui)
```

Asegúrate de colocar esta línea **antes** de la siguiente instrucción en tu `CMakeLists.txt`:

```cmake
add_executable(ClinicaDentalRP)
```


