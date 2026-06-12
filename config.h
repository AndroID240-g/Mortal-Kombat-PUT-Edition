#ifndef CONFIG_H
#define CONFIG_H

const int MAX_PLAYER_HP = 100;
const float GRAVITY = 1500.f;
const float JUMP_VELOCITY = -700.f;
const float GROUND_HEIGHT = 880.f;
const float PLAYER_SPEED = 400.f; 

// Nowe parametryzacje dla wymagań projektu (Punkt 15)
const int ATTACK_DAMAGE = 10;           // Obrażenia od jednego ciosu (zamiast 1)
const int APTECZKA_HEAL_AMOUNT = 20;    // Ilość leczenia
const int APTECZKA_SPAWN_CHANCE = 1000; // Szansa na spawn (1 na 1000 klatek)
const float APTECZKA_ROTATION_SPEED = 90.f; // Rotacja: 90 stopni na sekundę

#endif