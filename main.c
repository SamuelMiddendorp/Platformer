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

typedef struct Platform{
    Vec2 pos;
    Vec2 dims;
    Pixel color;
} Platform;

typedef struct Player{
    PhysicsComponent rigidBody;
} Player;

void collisionSystem(Platform** toCheck, PhysicsComponent* p);

const int maxPlatforms = 100;

int main()
{
    bun2dInit(1, 800, 800, 800, 800, "Platformer");
    Pixel color = {140,255,255,255};
    Player player = {{{0,0},{0,0},{0,0},{20,50},false}};
    Platform* platforms = malloc(sizeof(Platform) * maxPlatforms);

    Platform p = {{50,20}, {100,50}, {255,100,100,255}};
    platforms[0] = p;


    while (bun2dTick()) {
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
                player.rigidBody.acc.y += 20;
            }
        }
        updatePhysicsComponent(&player.rigidBody);
        collisionSystem(&platforms, &player.rigidBody);
        bun2dFillRect(player.rigidBody.pos.x, player.rigidBody.pos.y, player.rigidBody.dims.x, player.rigidBody.dims.y, color);
        for(int i = 0; i < 1; i++){
            Platform p = platforms[i];
            bun2dFillRect(p.pos.x, p.pos.y, p.dims.x, p.dims.y, p.color);
        }
    }
}

void collisionSystem(Platform** toCheck, PhysicsComponent* p){
    for(int i = 0; i < 1; i++){
        Platform* plat = toCheck[i];
        if((p->pos.x <= plat->pos.x + plat->dims.x)
        && (p->pos.x + p->dims.x >= plat->pos.x) 
        && (p->pos.y <= plat->pos.y + plat->dims.y)
        && (p->pos.y + p->dims.y >= plat->pos.y))
        {
            if(p->pos.y <= plat->pos.y + plat->dims.y){
                p->pos.y = plat->pos.y + plat->dims.y;
                p->onGround = true;
            }
        }
    }
}
void updatePhysicsComponent(PhysicsComponent* comp){
    if(!comp->onGround){
        comp->acc.y -= 0.1;
    }

    comp->vel.x += comp->acc.x;
    comp->vel.y += comp->acc.y;

    comp->vel.x *= 0.9;
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
