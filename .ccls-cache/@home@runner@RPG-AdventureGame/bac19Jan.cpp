#include <iostream>

class Character {
protected:
  int health;
  int minDamage;
  int maxDamage;
  int minDefence;
  int maxDefence;
  int defence;
  int damage;

public:
  Character() {}

  Character(int maxhealth, int damage, int defence) {
    this->health = maxhealth;
    this->damage = (rand() % (maxDamage - minDamage + 1)) + minDamage;
    this->defence = (rand() % (maxDefence - minDefence + 1)) + minDefence;
  }

  int getHealth() { return health; }

  int getDamage() { return damage; }

  void attack(Character *character) { character->health -= damage; }

  void takeDamage(int damage, Character *character) {
    damage -= character->defence;
    if(damage < 0){
      damage = 0;
    }
    health -= damage;  
  }

  bool isAlive() {
    if (health > 0) {
      return true;
    }
    return false;
  }

  ~Character() {}
};

class Player : public Character {
public:
  int heal;

public:
  Player() {
    health = 50;
    damage = 10;
    heal = 5;
    defence = 5;
  }

  void healCharacter() { health += heal; }

  ~Player() {
    std::cout << "Player is dead" << std::endl;
    std::cout << "Game over" << std::endl;
  }
};

class Enemy : public Character {
public:
  Enemy() {
  }

  Enemy(int maxHealth, int damage, int defence) : Character(maxHealth, damage, defence){

  }

  ~Enemy() {
    std::cout << "Enemy is dead" << std::endl;
  }
};

class Game {
private:
  Player *player = new Player();
  int level = 1;
  Enemy **enemy = new Enemy *[6];
  int enemyHealth = 25;
  int enemyDamage;
  int enemyDefence;

public:
  void start() {
    for(int i = 0; i < 6; i++){
      level += i;
      for(int j = 0; j < level; j++){
        enemyHealth += 25;
        enemyDamage += (rand() % (10 - 5 + 1)) + 5;
        enemyDefence += (rand() % (10 - 5 + 1)) + 5;

        enemy[j] = new Enemy(enemyHealth, enemyDamage, enemyDefence);
        playLevel(enemy[j]);
      }
        if(!player->isAlive()){
          std::cout << "Game over" << std::endl;
          delete player;
          break;
        }
    }
  }

  void playLevel(Enemy *enemy) {
    char keyPressed;

    while (player->isAlive()) {
      std::cout << "Player press 'a' to attack or 'h' to heal" << std::endl;
      std::cin >> keyPressed;
      if (keyPressed == 'a') {
        attack(player, enemy, "Player", "Enemy");
      } else if (keyPressed == 'h') {
        player->healCharacter();
        std::cout << "Player healed by " << player->heal << std::endl;
        std::cout << "Player health: " << player->getHealth() << std::endl;
      } else {
        std::cout << "Invalid input" << std::endl;
        continue;
      }

      if (enemy->isAlive()) {
        attack(enemy, player, "Enemy", "Player");
      } else {
        break;
      }
    }

    if (!enemy->isAlive()) {
      delete enemy;
    }
  }

  void attack(Character *currentCharacter, Character *opponentCharacter,
              std::string currentCharacterName,
              std::string opponentCharacterName) {
    currentCharacter->attack(opponentCharacter);
    std::cout << currentCharacterName << " attacks " << opponentCharacterName
              << " deals " << currentCharacter->getDamage() << " damage"
              << std::endl;
    std::cout << opponentCharacterName
              << " health: " << opponentCharacter->getHealth() << std::endl;
  }
};
/*class GameLevel {
public:
  int noOfEnemies;
  int playerAdditionalHealth;
  int playerAdditionalDamage;
  int playerAdditionalDefence;
};*/

int main() {
  Game gameManager;

  gameManager.start();
}