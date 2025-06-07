![Ingeniería en Desarrollo de Software](https://github.com/user-attachments/assets/00de7ae6-c2e0-43fe-ab7c-dd6b595b68a8)

# 🦷 Proyecto Clínica Dental "Ratoncito Pérez"

Sistema de gestión clínica desarrollado en **C++** como parte del curso de **Lógica de Programación** en la **Universidad de El Salvador**, Facultad Multidisciplinaria de Occidente.

---

## 🎯 Objetivo

Desarrollar una aplicación de consola que permita gestionar los diferentes aspectos de una clínica dental: pacientes, citas, tratamientos y medicamentos. El sistema utiliza estructuras de datos, algoritmos y archivos binarios para almacenamiento persistente.

---

## ⚙️ Tecnologías Utilizadas

- **Lenguaje:** C++
- **Compilador:** TDM-GCC 64 bits
- **Archivos:** Binarios `.dat`
- **Control de versiones:** Git / GitHub

---

## 🧩 Funcionalidades Principales

- 🔐 **Inicio de sesión seguro**
- 👥 **Gestión de pacientes** (registro, búsqueda, edición)
- 💊 **Gestión de inventario** (medicamentos, cantidades, precios)
- 🦷 **Gestión de tratamientos** (asignación y control)
- 📅 **Gestión de citas** (agenda con validación de horarios)
- 📊 **Reportes** (visualización de datos almacenados)

---

## 🧑‍🤝‍🧑 Equipo de Desarrollo

| Nombre                           | Módulo                    |
|---------------------------------|---------------------------|
| Franklin Esteban Pérez Fuentes   | Login                     |
| Héctor Danilo Benítez Ortéz     | Gestión de Inventario     |
| Rafael Armando Ibañez Diego      | Gestión de Pacientes      |
| Luis Daniel Contreras Rivera     | Gestión de Citas          |
| Eileen Marisol Reyes Rodríguez   | Gestión de Tratamientos   |

---

## 🖥️ Cómo Ejecutar el Proyecto

### ✔️ Requisitos

- [Visual Studio Code](https://code.visualstudio.com/)
- Extensiones: [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- Compilador: [TDM-GCC 64](https://jmeubank.github.io/tdm-gcc/)
- Sistema operativo: Windows

### 🔧 Compilación desde VS Code

1. Asegúrate de tener el entorno de tareas (`tasks.json`) y configuración de depuración (`launch.json`) dentro de la carpeta `.vscode`.  
2. Presiona `Ctrl+Shift+B` para compilar.  
3. Ejecuta la tarea `Compilar_Ejecutar_ClinicaDentalRP`.  
4. **Si usas un compilador diferente a TDM-GCC**, ve al archivo `tasks.json`, línea 7, donde está:  
   ```
   "command": "C:\\TDM-GCC-64\\bin\\g++.exe", // Ruta del compilador gcc/g++
   ```
   y modifica la ruta para que apunte al compilador que tengas instalado.
---

### 📁 Estructura del Proyecto

```plaintext
📂 .vscode/
├── tasks.json
├── launch.json

📂 bin/                    → Ejecutables generados
📂 Data_ClinicaDentalRP/   → Archivos binarios
│   ├── Citas/
│   ├── Inventario/
│   └── Pacientes/
📂 includes/               → Archivos .h organizados por módulos
│   ├── menu/
│   ├── modelos/
│   └── servicios/
📂 src/                    → Código fuente C++
│   ├── menu/
│   ├── modelos/
│   ├── servicios/
│   ├── utils/
│   └── main.cpp
📂 utils/                  → Utilidades adicionales
.gitignore
README.md
DEVELOPMENT.md
```

## 🧪 Estado del Proyecto

✅ Versión final estable  
📅 Ciclo I / 2025  
📚 Asignatura: Lógica de Programación GT03

---

## 📄 Licencia

Distribuido bajo la licencia [MIT](LICENSE).
