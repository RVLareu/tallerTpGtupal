#include "Area.h"
#include "Player.h"

Player::Player(SdlTexture &texture): an(&texture), facingLeft(false), moving(false), x(300), y(300) {}

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200);
    an.render(destArea, flip);
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() {
    moving = false;
}
