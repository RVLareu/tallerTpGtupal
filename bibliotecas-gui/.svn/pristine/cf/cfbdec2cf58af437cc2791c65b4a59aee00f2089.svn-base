#ifndef WORM_H
#define WORM_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QPixmap>

class Worm : public QGraphicsPixmapItem
{
public:
    Worm();
    virtual ~Worm() = default;
    void update();
    void moveRight();
    void moveLeft();

private:
    QList<QPixmap> pixmaps;
    int currentPixmap;
    bool flipImage;
    qreal xOffset = 0;
};

#endif // WORM_H
