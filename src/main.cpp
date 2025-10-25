// code is shit

#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include <stdio.h>
#include <vector>
using namespace std;

#define FRICTION 0.85
#define ACCEL 0.6
#define WORLD_X 600
#define WORLD_Y 600
#define MAX_HEALTH 100
#define HEALTH_DRAIN 0.02
#define BALL_RADIUS 15
#define BULLET_MAXAGE 180
#define BULLET_SPEED 7
#define BULLET_RADIUS 6
#define BULLET_DAMAGE 15
#define MAX_FEAR 300
#define FIRING_COOLDOWN 60
#define BLAST_MAXAGE 10
#define BLAST_GROWTH 4

struct Bullet {
   Vector2 pos;
   Vector2 velocity;
   int age;
   void processMovement();
   bool processAge();
};

void Bullet::processMovement() {
   pos += velocity;
   pos.x = Wrap(pos.x, 0, WORLD_X);
   pos.y = Wrap(pos.y, 0, WORLD_Y);
}

bool Bullet::processAge() {
   age++;
   return age < BULLET_MAXAGE;
}

vector<Bullet> bullets;

void processBullets() {
   for (size_t i = 0; i < bullets.size(); i++) {
      bullets[i].processMovement();
      if (!bullets[i].processAge()) {
         swap(bullets[i], bullets.back());
         bullets.pop_back();
         i--;
      }
   }
}

void drawBullets() {
   for (auto &b : bullets) {
      DrawCircleV(b.pos, BULLET_RADIUS, PURPLE);
   }
}

void shootBullet(Vector2 source, Vector2 direction) {
   Bullet b = {.pos = source + direction * (1.2 * BALL_RADIUS),
               .velocity = direction * BULLET_SPEED,
               .age = 0};
   bullets.push_back(b);
}

struct BlastEffect {
   Vector2 pos;
   int age;
   bool processAge();
};

bool BlastEffect::processAge() {
   age++;
   return age < BLAST_MAXAGE;
}

vector<BlastEffect> blastEffects;

void createBlastEffect(Vector2 pos) {
   BlastEffect e = {pos, 0};
   blastEffects.push_back(e);
}

void processBlastEffects() {
   for (size_t i = 0; i < blastEffects.size(); i++) {
      if (!blastEffects[i].processAge()) {
         swap(blastEffects[i], blastEffects.back());
         blastEffects.pop_back();
         i--;
      }
   }
}

void drawBlastEffects() {
   for (auto &e : blastEffects) {
      DrawRing(e.pos, e.age * BLAST_GROWTH, e.age * BLAST_GROWTH + 5, 0, 360,
               20, PINK);
   }
}

struct Player {
   Vector2 pos;
   Vector2 velocity;
   float health;
   int firingCooldown;
   void processMovement();
   void processFiring();
   static Player create();
};

void Player::processMovement() {
   Vector2 accel = {0, 0};
   if (IsKeyDown(KEY_W)) {
      accel.y -= 1;
   }
   if (IsKeyDown(KEY_S)) {
      accel.y += 1;
   }
   if (IsKeyDown(KEY_A)) {
      accel.x -= 1;
   }
   if (IsKeyDown(KEY_D)) {
      accel.x += 1;
   }
   accel = Vector2Normalize(accel) * ACCEL;
   velocity += accel;
   velocity *= FRICTION;
   pos += velocity;
   pos.x = Wrap(pos.x, 0, WORLD_X);
   pos.y = Wrap(pos.y, 0, WORLD_Y);
}

void Player::processFiring() {
   firingCooldown = max(0, firingCooldown - 1);
   if (firingCooldown > 0)
      return;

   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 direction = Vector2Normalize(GetMousePosition() - pos);
      shootBullet(pos, direction);
      firingCooldown = FIRING_COOLDOWN;
   }
}

Player Player::create() {
   return {
       .pos = {WORLD_X / 2.0 - 100, WORLD_Y / 2.0 + 100},
       .velocity = {0, 0},
       .health = MAX_HEALTH,
   };
}

Player player = Player::create();

struct Entity {
   Vector2 pos;
   Vector2 velocity;
   float health;
   int firingCooldown;
   float fear(Vector2 dangerPos);
   void processMovement(float crrFear, Vector2 dangerPos, Vector2 playerPos);
   void processFiring(Vector2 playerPos);
   void runBrain();
   static Entity create();
};

float Entity::fear(Vector2 dangerPos) {
   float f = MAX_HEALTH - health;
   f += max(0.0f, 200 - Vector2Distance(dangerPos, pos));
   f += firingCooldown;
   f += player.health;
   f = Clamp(f, 0, MAX_FEAR);

   return f;
}

void Entity::processMovement(float crrFear, Vector2 dangerPos, Vector2 playerPos) {
   Vector2 accel = {0, 0};
   accel += Vector2Normalize(playerPos - pos) * (MAX_FEAR - crrFear);
   accel += Vector2Normalize(pos - dangerPos) * crrFear;
   accel = Vector2Normalize(accel) * ACCEL;
   velocity += accel;
   velocity *= FRICTION;
   pos += velocity;
   pos.x = Wrap(pos.x, 0, WORLD_X);
   pos.y = Wrap(pos.y, 0, WORLD_Y);
}

void Entity::processFiring(Vector2 playerPos) {
   firingCooldown = max(0, firingCooldown - 1);
   if (firingCooldown > 0)
      return;

   firingCooldown = FIRING_COOLDOWN;
   shootBullet(pos, Vector2Normalize(playerPos - pos));
}

void Entity::runBrain() {
   Vector2 playerPos = player.pos;
   float playerDist = Vector2DistanceSqr(player.pos, pos);
   for (float dx = -WORLD_X; dx <= WORLD_X + 1; dx += WORLD_X) {
      for (float dy = -WORLD_Y; dy <= WORLD_Y + 1; dy += WORLD_Y) {
         Vector2 newPos = player.pos + (Vector2){dx, dy};
         float dist = Vector2DistanceSqr(pos, newPos);
         if (dist < playerDist) {
            playerDist = dist;
            playerPos = newPos;
         }
      }
   }
   Vector2 dangerPos = playerPos;
   float dangerDist = playerDist;
   for (auto &b : bullets) {
      for (float dx = -WORLD_X; dx <= WORLD_X + 1; dx += WORLD_X) {
         for (float dy = -WORLD_Y; dy <= WORLD_Y + 1; dy += WORLD_Y) {
            Vector2 newPos = b.pos + (Vector2){dx, dy};
            float dist = Vector2DistanceSqr(pos, newPos);
            if (dist < dangerDist) {
               dangerDist = dist;
               dangerPos = newPos;
            }
         }
      }
   }
   float f = fear(dangerPos);
   printf("fear: %.2f\n", f);
   processMovement(f, dangerPos, playerPos);
   processFiring(playerPos);
}

Entity Entity::create() {
   return {
       .pos = {WORLD_X / 2.0 + 100, WORLD_Y / 2.0 - 100},
       .velocity = {0, 0},
       .health = MAX_HEALTH,
   };
}

Entity entity = Entity::create();

void processCollisions() {
   const float threshold = pow(BALL_RADIUS + BULLET_RADIUS, 2);
   for (size_t i = 0; i < bullets.size(); i++) {
      if (Vector2DistanceSqr(bullets[i].pos, player.pos) <= threshold) {
         player.health -= BULLET_DAMAGE;
         createBlastEffect(bullets[i].pos);
         swap(bullets[i], bullets.back());
         bullets.pop_back();
      } else if (Vector2DistanceSqr(bullets[i].pos, entity.pos) <= threshold) {
         entity.health -= BULLET_DAMAGE;
         createBlastEffect(bullets[i].pos);
         swap(bullets[i], bullets.back());
         bullets.pop_back();
      }
   }
}

int main(void) {
   SetWindowState(FLAG_MSAA_4X_HINT);
   InitWindow(WORLD_X, WORLD_Y, "MEOW");
   SetTargetFPS(60);

   bool restart = false;

   while (!WindowShouldClose()) {

      if (restart) {
         restart = false;
         player = Player::create();
         entity = Entity::create();
         bullets.clear();
         blastEffects.clear();
      }

      if (player.health <= 0 && entity.health <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Draw!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      } else if (player.health <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Entity Won!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      } else if (entity.health <= 0) {
         BeginDrawing();
         ClearBackground(BLACK);
         DrawText("Player Won!", 200, 200, 40, PINK);
         restart = GuiButton({200, 300, 200, 50}, "RESTART");
         EndDrawing();
         continue;
      }

      player.processMovement();
      player.processFiring();
      entity.runBrain();
      processBullets();
      processCollisions();
      processBlastEffects();

      player.health -= HEALTH_DRAIN;
      entity.health -= HEALTH_DRAIN;

      BeginDrawing();
      ClearBackground(BLACK);
      DrawCircleV(player.pos, BALL_RADIUS, BLUE);
      DrawCircleV(entity.pos, BALL_RADIUS, RED);
      drawBullets();
      drawBlastEffects();
      DrawRectangleLinesEx({10, WORLD_Y - 50, 300, 40}, 2, WHITE);
      DrawRectangle(15, WORLD_Y - 45, player.health / (float)MAX_HEALTH * 290,
                    30, GREEN);
      DrawRectangleLinesEx({WORLD_X - 310, 10, 300, 40}, 2, RED);
      DrawRectangle(WORLD_X - 305, 15, entity.health / (float)MAX_HEALTH * 290,
                    30, PINK);
      DrawCircleSector(GetMousePosition() + (Vector2){20, 20}, 15, 0,
                       360.0 * player.firingCooldown / FIRING_COOLDOWN, 10,
                       GRAY);
      EndDrawing();
   }
   CloseWindow();

   return 0;
}
