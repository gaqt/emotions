
# Actions
Possible actions the entity can take

1. move
   - towards player
   - away from danger (player and bullets)
   - consumes 0.001*velocity health/frame
2. fire
   - 60 frames cooldown
   - consumes 1 health
   - deals 15 health damage
<!-- 3. block -->
<!--    - 60 frames cooldown -->
<!--    - consumes 0.02 health/frame -->
<!--    - blocks all damage -->

# Sensors
Input sources for the entity

1. current health
2. distance vector to the nearest danger source
3. distance vector to player
4. current fire cooldown
5. current block cooldown
6. player health

# Emotions
Emotions that dictate the entity's behaviour

- fear
   - inversely correlated to sensors 1, 2
   - correlated to sensors 4, 5, 6
   - intensifies defensive strategies

