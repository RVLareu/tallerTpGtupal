# Conectar eventos usando Automoc

QT provee una herramienta **moc** (meta object compiler) que traduce las macros de QT en código C++. Una de las macros más usadas es la de `signals:` y `slots:`, que permite un manejo más automático de las señales de nuestra aplicación.

En este ejemplo vemos como usamos el *moc* para compilar un ejemplo similar al ej-3, pero en vez de usar una función `connectEvents` nombramos nuestros métodos como `on_<object>_<signal>()` para indicar que esa función es un slot que se conecta a esa señal. Esta conexión se hace de forma automática.

Para que se realice la conexión, debemos agregar la macro `Q_OBJECT` a nuestra clase, como también agregar el include `moc_<nombreClase>.cpp` al archivo `.cpp` de nuestro widget.

En el CMakeLists agregamos `set (CMAKE_AUTOMOC on)` (preferentemente luego de hacer los includes de `ui`

Gracias @AgustinLeguizamon por colaborar en el armado del ejemplo
