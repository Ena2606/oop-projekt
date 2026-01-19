#include "character.h"

static const int FRAME_W = 56;
static const int FRAME_H = 56;

static const float MOVE_SPEED = 200.f;
static const float JUMP_FORCE = -520.f;
static const float GRAVITY = 900.f;

Character1::Character1(const std::string& path)
    : currentState(AnimationState::Idle),
    frameTime(0.12f),
    elapsedTime(0.f),
    currentFrame(0),
    velocity(0.f, 0.f),
    onGround(false),
    facingRight(true),
    dyingFlag(false)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    loadAnimations();
    sprite.setTextureRect(idleFrames[0]);

    float desiredHeight = 80.f;
    float scaleY = desiredHeight / 56.f;
    float scaleX = scaleY;
    sprite.setScale(scaleX, scaleY);


}


void Character1::loadAnimations()
{
    for (int i = 0; i < 4; i++)
        idleFrames.emplace_back(i * FRAME_W, 0, FRAME_W, FRAME_H);

    for (int i = 0; i < 10; i++)
        backflipFrames.emplace_back(i * FRAME_W, FRAME_H, FRAME_W, FRAME_H);

    for (int i = 0; i < 7; i++)
        dyingFrames.emplace_back(i * FRAME_W, 2 * FRAME_H, FRAME_W, FRAME_H);

    for (int i = 0; i < 6; i++)
        moveRFrames.emplace_back(i * FRAME_W, 3 * FRAME_H, FRAME_W, FRAME_H);
    for (int i = 0; i < 6; i++)
        moveLFrames.emplace_back(i * FRAME_W, 4 * FRAME_H, FRAME_W, FRAME_H);

    for (int i = 0; i < 7; i++)
        jumpRFrames.emplace_back(i * FRAME_W, 5 * FRAME_H, FRAME_W, FRAME_H);
    for (int i = 0; i < 7; i++)
        jumpLFrames.emplace_back(i * FRAME_W, 6 * FRAME_H, FRAME_W, FRAME_H);
}

void Character1::setState(AnimationState state)
{
    if (currentState != state)
    {
        currentState = state;
        currentFrame = 0;
        elapsedTime = 0.f;
    }
}

void Character1::moveLeft()
{
    if (dyingFlag) return;
    velocity.x = -MOVE_SPEED;
    facingRight = false;
    if (onGround) setState(AnimationState::MovingL);
}

void Character1::moveRight()
{
    if (dyingFlag) return;
    velocity.x = MOVE_SPEED;
    facingRight = true;
    if (onGround) setState(AnimationState::MovingR);
}


void Character1::stop()
{
    if (dyingFlag) return;
    velocity.x = 0;
    if (onGround) setState(AnimationState::Idle);
}
void Character1::jump()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::Idle);
    }
}

void Character1::jumpLeft()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::JumpL);
    }
}void Character1::jumpRight()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::JumpR);
    }
}
void Character1::backflip()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::Backflip);
    }
}
void Character1::dying()
{
    onGround = false;
    velocity = { 0.f, 0.f };
    setState(AnimationState::Dying);
    dyingFlag = true;
}


void Character1::applyGravity(float dt)
{
    velocity.y += GRAVITY * dt;
}

void Character1::resolveCollisions(
    const std::vector<sf::FloatRect>& colliders,
    float dt)
{
    onGround = false;

    sf::FloatRect bounds = sprite.getGlobalBounds();

    for (const auto& c : colliders)
    {
        if (!bounds.intersects(c)) continue;

        float dxLeft = (bounds.left + bounds.width) - c.left;
        float dxRight = (c.left + c.width) - bounds.left;
        float dyTop = (bounds.top + bounds.height) - c.top;
        float dyBottom = (c.top + c.height) - bounds.top;

        float minX = std::min(dxLeft, dxRight);
        float minY = std::min(dyTop, dyBottom);

        //Vertical collision////////////

        if (minY < minX)
        {
            if (dyTop < dyBottom)
            {
                sprite.setPosition(bounds.left, c.top - bounds.height);
                velocity.y = 0.f;
                onGround = true;
            }
            else
            {
                sprite.setPosition(bounds.left, c.top + c.height);
                velocity.y = 0.f;
            }
        }
        ////////Horizontal collision/////////
        else
        {
            if (dxLeft < dxRight)
            {
                sprite.setPosition(c.left - bounds.width, bounds.top);
            }
            else
            {
                sprite.setPosition(c.left + c.width, bounds.top);
            }
            velocity.x = 0.f;
        }

        bounds = sprite.getGlobalBounds();
    }

}

sf::Vector2f Character1::getPosition() const {
    return sprite.getPosition();
}

void Character1::update(float dt)
{
    applyGravity(dt);
    sprite.move(velocity * dt);
    updateAnimation(dt);
    updateDirection();
}

void Character1::updateAnimation(float dt)
{
    elapsedTime += dt;
    if (elapsedTime < frameTime) return;
    elapsedTime = 0.f;

    const std::vector<sf::IntRect>* frames = nullptr;

    switch (currentState)
    {
    case AnimationState::Idle: frames = &idleFrames; break;
    case AnimationState::MovingL: frames = &moveLFrames; break;
    case AnimationState::MovingR: frames = &moveRFrames; break;

    case AnimationState::JumpL: frames = &jumpLFrames; break;
    case AnimationState::JumpR: frames = &jumpRFrames; break;
    case AnimationState::Backflip: frames = &backflipFrames; break;
    case AnimationState::Dying: frames = &dyingFrames; break;
    }

    if (currentState == AnimationState::Dying) {
        if (currentFrame < frames->size() - 1)
            currentFrame++;
    }
    else {
        currentFrame = (currentFrame + 1) % frames->size();
    }
    sprite.setTextureRect((*frames)[currentFrame]);
}
void Character1::updateDirection() {}

void Character1::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Character1::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Character1::getBounds() const
{
    return sprite.getGlobalBounds();
}



///////////////////////////////////////////////////////////////////////////////////////////


Character2::Character2(const std::string& path)
    : currentState(AnimationState::Idle),
    frameTime(0.12f),
    elapsedTime(0.f),
    currentFrame(0),
    velocity(0.f, 0.f),
    onGround(false),
    facingRight(true),
    dyingFlag(false)

{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    loadAnimations();
    sprite.setTextureRect(idleFrames[0]);

    float desiredHeight = 80.f;
    float scaleY = desiredHeight / 56.f;
    float scaleX = scaleY;
    sprite.setScale(scaleX, scaleY);

}

void Character2::loadAnimations()
{
    for (int i = 0; i < 4; i++)
        idleFrames.emplace_back(i * FRAME_W, 0, FRAME_W, 56);

    for (int i = 0; i < 7; i++)
        dyingFrames.emplace_back(i * FRAME_W, 1 * 56, FRAME_W, 56);

    for (int i = 0; i < 6; i++)
        moveRFrames.emplace_back(i * FRAME_W, 2 * 56, FRAME_W, 56);
    for (int i = 0; i < 6; i++)
        moveLFrames.emplace_back(i * FRAME_W, 3 * 56, FRAME_W, 56);

    for (int i = 0; i < 7; i++)
        jumpRFrames.emplace_back(i * FRAME_W, 4 * 56, FRAME_W, 56);
    for (int i = 0; i < 7; i++)
        jumpLFrames.emplace_back(i * FRAME_W, 5 * 56, FRAME_W, 56);
}

void Character2::setState(AnimationState state)
{
    if (currentState != state)
    {
        currentState = state;
        currentFrame = 0;
        elapsedTime = 0.f;
    }
}

void Character2::moveLeft()
{
    if (dyingFlag) return;
    velocity.x = -MOVE_SPEED;
    facingRight = false;
    if (onGround) setState(AnimationState::MovingL);
}

void Character2::moveRight()
{
    if (dyingFlag) return;
    velocity.x = MOVE_SPEED;
    facingRight = true;
    if (onGround) setState(AnimationState::MovingR);
}


void Character2::stop()
{
    if (dyingFlag) return;
    velocity.x = 0;
    if (onGround) setState(AnimationState::Idle);
}
void Character2::jump()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::Idle);
    }
}

void Character2::jumpLeft()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::JumpL);
    }
}void Character2::jumpRight()
{
    if (dyingFlag) return;
    if (onGround)
    {
        velocity.y = JUMP_FORCE;
        onGround = false;
        setState(AnimationState::JumpR);
    }
}
void Character2::dying()
{
    onGround = false;
    velocity = { 0.f, 0.f };
    setState(AnimationState::Dying);
    dyingFlag = true;
}

void Character2::applyGravity(float dt)
{
    velocity.y += GRAVITY * dt;
}

void Character2::resolveCollisions(
    const std::vector<sf::FloatRect>& colliders,
    float dt)
{
    onGround = false;

    sf::FloatRect bounds = sprite.getGlobalBounds();

    for (const auto& c : colliders)
    {
        if (!bounds.intersects(c)) continue;

        float dxLeft = (bounds.left + bounds.width) - c.left;
        float dxRight = (c.left + c.width) - bounds.left;
        float dyTop = (bounds.top + bounds.height) - c.top;
        float dyBottom = (c.top + c.height) - bounds.top;

        float minX = std::min(dxLeft, dxRight);
        float minY = std::min(dyTop, dyBottom);

        if (minY < minX)
        {
            if (dyTop < dyBottom)
            {
                sprite.setPosition(bounds.left, c.top - bounds.height);
                velocity.y = 0.f;
                onGround = true;
            }
            else
            {
                sprite.setPosition(bounds.left, c.top + c.height);
                velocity.y = 0.f;
            }
        }
        else
        {
            if (dxLeft < dxRight)
            {
                sprite.setPosition(c.left - bounds.width, bounds.top);
            }
            else
            {
                sprite.setPosition(c.left + c.width, bounds.top);
            }
            velocity.x = 0.f;
        }

        bounds = sprite.getGlobalBounds();
    }
}


void Character2::update(float dt)
{
    applyGravity(dt);
    sprite.move(velocity * dt);
    updateAnimation(dt);
    updateDirection();
}

void Character2::updateAnimation(float dt)
{
    elapsedTime += dt;
    if (elapsedTime < frameTime) return;
    elapsedTime = 0.f;

    const std::vector<sf::IntRect>* frames = nullptr;

    switch (currentState)
    {
    case AnimationState::Idle: frames = &idleFrames; break;
    case AnimationState::MovingL: frames = &moveLFrames; break;
    case AnimationState::MovingR: frames = &moveRFrames; break;
    case AnimationState::JumpL: frames = &jumpLFrames; break;
    case AnimationState::JumpR: frames = &jumpRFrames; break;
    case AnimationState::Dying: frames = &dyingFrames; break;
    }
    if (currentState == AnimationState::Dying) {
        if (currentFrame < frames->size() - 1)
            currentFrame++;
    }
    else {
        currentFrame = (currentFrame + 1) % frames->size();
    }
    sprite.setTextureRect((*frames)[currentFrame]);
}
void Character2::updateDirection() {}

void Character2::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Character2::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}
sf::Vector2f Character2::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Character2::getBounds() const
{
    return sprite.getGlobalBounds();
}