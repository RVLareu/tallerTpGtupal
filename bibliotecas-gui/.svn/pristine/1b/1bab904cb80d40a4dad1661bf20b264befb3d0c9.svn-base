project(qt5-demo)
cmake_minimum_required(VERSION 3.8)
# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej4/src a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/src)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        src/mainwindow.ui
)

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

add_executable(step-4
  src/gamescene.cpp
  src/mainwindow.cpp
  src/worm.cpp
  src/main.cpp
  assets/resources.qrc
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(step-4 Qt5::Widgets Qt5::Core)
