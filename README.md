# Trabajo Práctico Grupal: Ajedrez Cuántico

### 2021 - 2C - Curso Veiga

</br>

* Reberendo, Manuel 100930
* Vázquez Lareu, Román - 100815

## Instrucciones de compilación e instalación
### Dependencias
- sdl2  
- cmake 
- make
- compilador de c++ 11

Instalación con *apt*:
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-gfx-dev
```
```bash
sudo apt install build-essential
```
```bash
sudo apt install cmake
```

### Compilación

Crear una carpeta build dentro de la carpeta raíz:
```bash
mkdir build
```  

Dentro de la carpeta raíz, ejecutar:
```bash
cmake ..
```
```bash
make
```
Esto compilará los ejecutables `server` y `client`. 

### Instalación
En la carpeta raíz, marcar el archivo `install.sh` como ejecutable:
```bash
sudo chmod +x install.sh
```
Y por último, ejecutarlo:
```bash
sudo ./install.sh
```


## Ejecución
Luego de compilar e instalar, ya pueden ejecutarse tanto el servidor como el cliente de la siguiente manera:  

### Servidor
```bash
quantum-chess-server <HOST> <SERVICE>
```

### Cliente
```bash
quantum-chess-client <HOST> <SERVICE>
```  

donde `<HOST>` y `<SERVICE>` son el host y servicio del servidor a ejecutar / conectarse.

## Instrucciones del juego:
Seleccionar piezas con click izquierdo. Al hacer esto, se mostrarán los movimientos posibles en el tablero.   
Para mover una pieza seleccionada, hacer click izquierdo en el casillero a moverse.
Si se hace doble click sobre la misma pieza, se marca la pieza para hacer un split, y las próximas dos selecciones serán los casilleros en los que se hará el split.
Si se hace click derecho en una pieza en superposición, se marcará para hacer un merge, para lo cual se tendrá que hacer otro click derecho con otra pieza que sea instancia de esta misma, y luego seleccionar con click izquierdo un casillero de los posibles para hacer el merge.