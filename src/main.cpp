#include "constants.hpp"
#include "entities/blast_effect.hpp"
#include "entities/bullet.hpp"
#include "entities/enemy.hpp"
#include "entities/player.hpp"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>
using namespace std;

#include "sources.cpp"

int main(void) {
   SetWindowState(FLAG_MSAA_4X_HINT);
   InitWindow(WORLD_X, WORLD_Y, "MEOW");
   SetTargetFPS(60);

   Vector2 playerInitialPos = {WORLD_X/2.0 - 100, WORLD_Y/2.0 + 100};
   Vector2 enemyInitialPos = {WORLD_X/2.0 + 100, WORLD_Y/2.0 - 100};

   Player player = Player::create(playerInitialPos);
   Enemy enemy = Enemy::create(enemyInitialPos);

   bool restart = false;

   while (!WindowShouldClose()) {

      if (restart) {
         restart = false;
         player = Player::create(playerInitialPos);
         enemy = Enemy::create(enemyInitialPos);
         Bullet::clearBullets();
         BlastEffect::clearEffects();
      }

      if (player.getHealth().getHealth() <= 0 &&
          enemy.getHealth().getHealth() <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Draw!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      } else if (player.getHealth().getHealth() <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Entity Won!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      } else if (enemy.getHealth().getHealth() <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Player Won!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      }

      player.tick();
      enemy.tick(player);
      BlastEffect::tickAll();
      Bullet::tickAll(player, enemy);

      BeginDrawing();
      ClearBackground(BLACK);

      player.draw();
      enemy.draw();
      Bullet::drawAll();
      BlastEffect::drawAll();
      enemy.drawUI();
      player.drawUI();

      EndDrawing();
   }
   CloseWindow();

   return 0;
}
