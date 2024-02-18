#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>
#include <stdbool.h>

typedef struct PhysicsComponent{
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
    Vec2 dims;
    bool onGround;
} PhysicsComponent;

typedef struct Player{
    PhysicsComponent rigidBody;
} Player;

int main()
{
    bun2dInit(1, 800, 800, 800, 800, "Platformer");

    Pixel color = {140,255,255,255};
    Player player = {{{0,0},{0,0},{0,0},{20,50},false}};

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
        if(bun2dKey(KEY_W) > 0){
            if(player.rigidBody.onGround){
                player.rigidBody.acc.y += 4;
            }
        }
        player.rigidBody.acc.y -= 0.1;
        updatePhysicsComponent(&player.rigidBody);
        bun2dRect(player.rigidBody.pos.x, player.rigidBody.pos.y, player.rigidBody.dims.x, player.rigidBody.dims.y, color);
    }
}

void collisionSystem(PhysicsComponent** toCheck, PhysicsComponent p){
    
}
void updatePhysicsComponent(PhysicsComponent* comp){
    comp->vel.x += comp->acc.x;
    comp->vel.y += comp->acc.y;

    // Gravity

    comp->pos.x += comp->vel.x;
    comp->pos.y += comp->vel.y;

    comp->acc.x = 0;
    comp->acc.y = 0; 

    if(comp->pos.x > 800 - comp->dims.x){
        comp->pos.x = 800 - comp->dims.x;
    }
    if(comp->pos.x < 0 ){
        comp->pos.x = 0;
    }
    if(comp->pos.y <= 0){
        comp->onGround = true;
        comp->pos.y = 0;
    }
    else{
        comp->onGround = false;
    }
}
