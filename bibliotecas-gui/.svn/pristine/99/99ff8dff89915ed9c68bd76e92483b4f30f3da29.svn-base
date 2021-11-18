#include "gamescene.h"

GameScene::GameScene()
{
    this->addItem(&worm);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_D:
            worm.moveRight();
            break;
        case Qt::Key_A:
            worm.moveLeft();
            break;
        default:
            break;
    }
}
