#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>


typedef struct Player{
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
    Vec2 dims;
} Player;
int main()
{
    bun2dInit(1, 100, 100, 800, 800, "Platformer");

    Pixel color = {140,255,255,255};
    Player player = {{0,0},{0,0},{0,0},{2,5}};

    while (bun2dTick())
    {
        bun2dClear();
        // Input
        if(bun2dKey(KEY_D) == BUN2D_PRESS){
           player.acc.x += 0.2; 
        }

        if(bun2dKey(KEY_A) == BUN2D_PRESS){
           player.acc.x -= 0.2; 
        }
        if(bun2dKey(KEY_S) == BUN2D_PRESS){
        }

        if(bun2dKey(KEY_W) == BUN2D_PRESS){
        }
        updatePlayer(&player);
        bun2dRect(player.pos.x, player.pos.y, player.dims.x, player.dims.y, color);

    }
}
void updatePlayer(Player* player){
    player->vel.x += player->acc.x;
    player->vel.y += player->acc.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    player->acc.x = 0;
    player->acc.y = 0; 
}
