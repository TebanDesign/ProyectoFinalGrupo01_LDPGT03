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