#ifndef __WORM_H__
#define __WORM_H__

#include "Animation.h"

class Player {
public:
    Player(SdlTexture &texture);
    ~Player();
    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif // __WORM_H__