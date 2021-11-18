project(qt5-demo)

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej3/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        ui/Greeter.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)

add_executable(greeter-automoc
  src/Greeter.cpp
  src/main.cpp
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(greeter-automoc Qt5::Widgets)
