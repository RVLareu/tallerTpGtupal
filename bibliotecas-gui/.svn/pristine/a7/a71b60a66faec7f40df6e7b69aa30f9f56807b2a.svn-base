#include "worm.h"

Worm::Worm(): currentPixmap(0), flipImage(false)
{
    QImage img;
    /**
     * Qt nos brinda la posibilidad de manejar recursos de forma
     * portable (independiente del sistema operativo) utilizando un QResource.
     *
     * El path de la imagen será resuelta por qt en base al archivo qrc.
     */
    img.load(":worm_walk.png");
    // Asumo que cada sprite es cuadrado, por lo que puedo tener una idea cuantos frames
    // hay haciendo la división de estas dos dimensiones
    int imageCount = img.height() / img.width();
    int sideLength = img.width();

    for (int i = 0; i < imageCount; i++)
    {
        // Extraigo los frames individuales y los guardo en una lista
        // QPixmap QPixmap::copy(int x, int y, int width, int height) const
        QImage subImage = img.copy(0, i * sideLength, sideLength, sideLength);
        pixmaps.push_back(QPixmap::fromImage(subImage));
    }
    // Muestro en la pantalla el frame seleccionado
    this->setPixmap(pixmaps.at(0));
}

void Worm::update()
{
    currentPixmap++;
    // Muevo al personaje desde el centro de la ventana
    this->setOffset({xOffset, 0});
    const QPixmap &current = pixmaps.at(currentPixmap % pixmaps.size());
    if (flipImage){
        // Espejo la imagen para dibujar una animación de movimiento hacia la derecha
        this->setPixmap(current.transformed(QTransform().scale(-1, 1)));
    } else {
        this->setPixmap(current);
    }
}

void Worm::moveRight()
{
    this->xOffset += 5;
    flipImage = true;
    this->update();
}

void Worm::moveLeft()
{
    this->xOffset -= 5;
    flipImage = false;
    this->update();
}
