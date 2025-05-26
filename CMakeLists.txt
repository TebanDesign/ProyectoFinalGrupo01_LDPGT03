# version minima de CMAKE
cmake_minimum_required(VERSION 3.10)

# se define el nombre del proyecto
project(ClinicaDentalRP LANGUAGES CXX)

# se especifica la cercion de c++
# esta config es compatible con la version isntalada (gcc versión 10.3.0 (tdm64-1))
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# directorio de salida para los ejecutables y librerias
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# aqui incluimos FTXUI y su CMakeLists.txt para cuando se compile nuestro proyecto
add_subdirectory(extern/ftxui)
# aqui agregar mas librerias externas

# crea el ejecutable
add_executable(ClinicaDentalRP)

# definicion de los archivos para el ejecutable
# se usa target_sources con PRIVATE para encapsular las fuentes dentro del destino
target_sources(ClinicaDentalRP PRIVATE
    
# entrada a la aplicacion
    src/main.cpp

    # Menu
    src/menu/CitasMenu.cpp
    src/menu/MainMenu.cpp
    src/menu/PacienteMenu.cpp

    # modelos POO
    src/modelos/cita.cpp
    src/modelos/inventario.cpp
    src/modelos/Paciente.cpp
    src/modelos/tratamiento.cpp

    # servicios
    src/servicios/PacienteServicio.cpp

    # utils
    src/utils/CalcularEdad.cpp
    src/utils/encriptador.cpp
    src/utils/Validaciones.cpp
)

# se agregan los directorios a incluir para que  el compilador pueda encontrar tus archivos de encabezado (.h)
# se usa target_include_directories con PUBLIC para que acceda a otras sub carpetas si las hay
target_include_directories(ClinicaDentalRP PUBLIC

    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/includes/menu     
    ${PROJECT_SOURCE_DIR}/includes/modelos   
    ${PROJECT_SOURCE_DIR}/includes/servicios 
    ${PROJECT_SOURCE_DIR}/includes/utils    
)

