#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

typedef struct PhysicsComponent{
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
    Vec2 dims;
} PhysicsComponent;

typedef struct Player{
    PhysicsComponent rigidBody;
} Player;

int main()
{
    bun2dInit(1, 800, 800, 800, 800, "Platformer");

    Pixel color = {140,255,255,255};
    Player player = {{{0,0},{0,0},{0,0},{2,5}}};

    while (bun2dTick())
    {
        bun2dClear();
        // Input
        if(bun2dKey(KEY_D) == BUN2D_PRESS){
           player.rigidBody.acc.x += 0.2; 
        }

        if(bun2dKey(KEY_A) == BUN2D_PRESS){
           player.rigidBody.acc.x -= 0.2; 
        }
        if(bun2dKey(KEY_S) == BUN2D_PRESS){
        }

        if(bun2dKey(KEY_W) == BUN2D_PRESS){
        }
        updatePhysicsComponent(&player.rigidBody);
        bun2dRect(player.rigidBody.pos.x, player.rigidBody.pos.y, player.rigidBody.dims.x, player.rigidBody.dims.y, color);

    }
}
void updatePhysicsComponent(PhysicsComponent* comp){
    comp->vel.x += comp->acc.x;
    comp->vel.y += comp->acc.y;

    comp->pos.x += comp->vel.x;
    comp->pos.y += comp->vel.y;

    comp->acc.x = 0;
    comp->acc.y = 0; 
}
