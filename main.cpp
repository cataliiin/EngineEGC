#include <iostream>
#include <vector>
#include <cmath>
#include "Engine/Engine.h"
#include "Engine/Entities/Quad2D.h"
#include "Engine/Core/Window.h"


int main(int argc, char **argv)
{
    Engine game;

    game.init(800, 600, "Engine EGC - Quad Control", true, Color4(0.15f, 0.15f, 0.15f, 1.0f), RenderMode::MODE_3D);
    game.setTargetFPS(144);


    Quad2D *player = new Quad2D(Vec2(400.0f, 300.0f), Vec2(50.0f, 50.0f), Color4(0.2f, 0.6f, 1.0f, 1.0f));

    player->setUpdate([&](Entity2D* self, float dt) {
    auto input = game.getInput();
    float speed = 300.0f;

    if (input->isKeyDown("w")) self->transform.position.y += speed * dt;
    if (input->isKeyDown("s")) self->transform.position.y -= speed * dt;
    if (input->isKeyDown("a")) self->transform.position.x -= speed * dt;
    if (input->isKeyDown("d")) self->transform.position.x += speed * dt;

    if (input->isKeyPressed("space")) {
        self->color = self->color.a == 1.0f ? Color4(1.0f, 0.6f, 1.0f, 0.5f) : Color4(0.0f, 0.2f, 0.0f, 1.0f);
    }
    
    if (input->isKeyDown("up")) self->transform.position.y += speed * dt;
});

    game.addEntity2D(player);

    Quad2D *obstacle = new Quad2D(Vec2(200, 450), Vec2(100, 20), Color4(1, 0.3f, 0.3f, 1));
    obstacle->setZIndex(-1);
    game.addEntity2D(obstacle);

    std::cout << "Engine is running... Use WASD to move the blue square!" << std::endl;

    game.run();

    return 0;
}