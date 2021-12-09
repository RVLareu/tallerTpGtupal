# Trabajo Práctico Grupal: Ajedrez Cuántico

### 2021 - 2C - Curso Veiga

</br>

* Reberendo, Manuel 100930
* Vázquez Lareu, Román - 100815

## Instrucciones de compilación
### Dependencias
- sdl2  
- cmake  

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

Dentro de la carpeta raíz, ejecutar:
```bash
cmake .
```
```bash
make
```

## Ejecución
Luego de compilar, dentro de la carpeta raiz, ejecutar:  

### Servidor
```bash
./server
```

### Cliente
```bash
./client
```


## Instrucciones del juego:
Seleccionar piezas con click izquierdo. Al hacer esto, se mostrarán los movimientos posibles en el tablero.   
Para mover una pieza seleccionada, hacer click izquierdo en el casillero a moverse.