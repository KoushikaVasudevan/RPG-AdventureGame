#include <iostream>

//enum SpecialItem {Map, Sword, Armour, Shield, MagicPotion, Bow, Axe};

enum SpecialAbility {PathFinder, CriticalDamage, LifeSteal, HealthRegeneration, RangedDamage, Blocker, GroundSlash};

class Character {
public:
  int maxHealth;
  int health;
  int damage;
  int defence;
  SpecialAbility *specialAbilities;

protected:
  std::string characterName;
  int specialItemIndex = 0;
  int specialAbilityIndex = 0;
  bool rangedDamageTriggered = false;
  bool blockerTriggered = false;

public:
  Character() {
    specialAbilities = new SpecialAbility[6];
  }

  Character(int mh, int dam, int def, std::string name)
  {
    maxHealth = mh;
    health = maxHealth;
    damage = dam;
    defence = def;
    characterName = name;
  }  

  int getHealth() { return health; }

  int getDamage() { return damage; }

  void printStats() { std::cout << "Health: " << health << std::endl; }

  void addSpecialAbility(SpecialAbility specialAbility){
    specialAbilities[specialAbilityIndex] = specialAbility;
  
    specialAbilityIndex++;
  }

  void attack(Character *opponent) {
    int randDamage = (rand() % (damage + 1));

    for (int i = 0; i < specialAbilityIndex; i++) {
      switch (specialAbilities[i]) {

      case CriticalDamage: {
        if (rand() % 10 < 1) {
          std::cout << "Critical Damage Triggered!" << std::endl;

          randDamage = randDamage * 2;

          std::cout << "Damage: " << randDamage << std::endl;
        }
        break;
      }

      case LifeSteal: {
        if (rand() % 10 < 1) {
          std::cout << "Life Steal Triggered!" << std::endl;

          health = health + 10;

          std::cout << "health: " << health << std::endl;
        }
        break;
      }

      case HealthRegeneration: {
        if (rand() % 10 < 1) {
          std::cout << "Health Regeneration Triggered!" << std::endl;

          health = maxHealth;

          std::cout << "health: " << health << std::endl;
          health = maxHealth;
        }
        break;
      }

      case RangedDamage: {
        rangedDamageTriggered = (rand() % 10 < 1);
        break;
      }

      case GroundSlash:{
        if (rand() % 10 < 5) {
          std::cout << "Ground Slash Triggered!" << std::endl;
          randDamage = randDamage * 2;
        }
      }
      default:{
        break;
      }
      }
    }

    std::cout << characterName << " attacks " << opponent->characterName
              << " deals " << randDamage << " damage" << std::endl;

    opponent->takeDamage(randDamage);
  }

  void takeDamage(int damage) {

    int randDefence = (rand() % (defence + 1));
    
    if (rangedDamageTriggered) {
      std::cout << "Ranged Damage Triggered!" << std::endl;
      std::cout << "Player takes 0 damage" << std::endl;
      rangedDamageTriggered = false;
      return;
    }

    for (int i = 0; i < specialAbilityIndex; i++) {
      if((specialAbilities[i] == Blocker) && (rand() % 10 < 1)) {
        std::cout << "Blocker Triggered!" << std::endl;
        std::cout << "Player takes 0 damage" << std::endl;
        damage = 0;
        break;
      }
    }

    damage -= randDefence;
    if (damage < 0) {
      damage = 0;
    }
    std::cout << characterName << " defends by " << randDefence << " defence"
              << std::endl;
    health -= damage;
  }

  bool isAlive() {
    if (health > 0) {
      return true;
    }
    return false;
  }

  virtual
  ~Character() {
    delete[] specialAbilities;
  }
};

class Player : public Character {
public:
  int heal = 5;

public:
  Player(int maxHealth, int damage, int defence, std::string characterName) : Character(maxHealth, damage, defence, characterName) {
  }

  void healPlayer() { health += heal; }

  ~Player() {
    std::cout << "Player is dead" << std::endl;
    std::cout << "GAME OVER!" << std::endl;
  }
};

class Enemy : public Character {
public:
  bool isBossEnemy;

public:
  Enemy(int maxHealth, int damage, int defence, std::string characterName) : Character(maxHealth, damage, defence, characterName) {
  }

  ~Enemy() {
    if(isBossEnemy){
      std::cout << "Congratulations! You have defeated Mighty Murlocs" << std::endl;
      std::cout << "GAME OVER!" << std::endl;
    }
    else{
      std::cout << "Enemy is dead" << std::endl;
    }
  }
};

class GameLevel {
public:
  int noOfEnemies;
  int playerNextLevelHealth;
  int playerNextLevelDamage;
  int playerNextLevelDefence;
  SpecialAbility specialAbility;
  std::string specialItem;

public:
  GameLevel() {}
  GameLevel(int noOfEnemies, int playerNextLevelHealth,
            int playerNextLevelDamage, int playerNextLevelDefence,
            SpecialAbility specialAbility, std::string specialItem) {
    this->noOfEnemies = noOfEnemies;
    this->playerNextLevelHealth = playerNextLevelHealth;
    this->playerNextLevelDamage = playerNextLevelDamage;
    this->playerNextLevelDefence = playerNextLevelDefence;
    this->specialAbility = specialAbility;
    this->specialItem = specialItem;
  }

  ~GameLevel() {}
};

class Game {
private:
  int levelCount = 6;

  // initializing one object of Player class
  Player *player = new Player(50, 10, 5, "Player");

  // initializing many objects of Game Level class
  GameLevel *levels = new GameLevel[levelCount];

public:
  void start() {

    levels[0] = GameLevel(1, 0, 0, 0, PathFinder, "Map");
    levels[1] = GameLevel(2, 5, 5, 5, CriticalDamage, "Sword");
    levels[2] = GameLevel(3, 10, 5, 5, LifeSteal, "Armour");
    levels[3] = GameLevel(4, 15, 5, 5, Blocker, "Shield");
    levels[4] = GameLevel(5, 20, 5, 5, HealthRegeneration, "MagicPotion");
    levels[5] = GameLevel(1, 25, 5, 5, RangedDamage, "Bow");

    player->specialAbilities = new SpecialAbility[levelCount];
    
    std::cout << "A darkness was spreading across the realms in the mystical land of Aldora. Shadows crept and monsters emerged, threatening the peaceful existence of its inhabitants. The only hope rested upon a lone warrior - Veera, who was armed with a blade and had a heart full of courage." << std::endl;

    std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    
    for (int i = 0; i < levelCount; i++) {
      std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Game Level " << i + 1 << "\n" << std::endl;
      
      playLevel(levels[i], i);

      if (!player->isAlive()) {
        delete player;
        break;
      }
    }
  }

  void playLevel(GameLevel level, int levelIndex) {
    player->maxHealth += level.playerNextLevelHealth;
    player->health = player->maxHealth;
    player->damage += level.playerNextLevelDamage;
    player->defence += level.playerNextLevelDefence;

    player->addSpecialAbility(level.specialAbility);

    switch(levelIndex) {
      case 0:{
        std::cout << " - The Forest of Whispers" << std::endl;
        std::cout << "The Shadow Stalker, lurks in the shadows, stalking the paths of the forest." << std::endl;
        std::cout << "Veera finds a " << levels[levelIndex].specialItem << ", and he discovers safe trails to navigate the dreaded forest!" << std::endl;
        break;
      }
      case 1:{
        std::cout << " - The Cursed Mines" << std::endl;
        std::cout << "Deep in the treacherous cursed mines, awaited the ferocious cave crawlers." << std::endl;
        std::cout << "Veera unearths a " << levels[levelIndex].specialItem <<  ", and prepares to destroy the cave crawlers." << std::endl;
        break;
      }
      case 2:{
        std::cout << " - The Frozen peaks" << std::endl;
        std::cout << "Scaling the heights of the frozen peaks, roamed the mighty frost wraiths." << std::endl;
        std::cout << "Hidden in the ice carvern, Veera finds an " << levels[levelIndex].specialItem << " helping him take less damage from the frost wraiths." << std::endl;
        break;
      }
      case 3:{
        std::cout << " - The Labyrinth of Shadows" << std::endl;
        std::cout << "This land is dominated by the dementors - souless creatures ." << std::endl;
        std::cout << "In the heart of the Maze, Veera discovers a " << levels[levelIndex].specialItem << ", helping him block attacks from the dementors ! " << std::endl;
        break;
      }
      case 4:{
        std::cout << " - The Blazing Inferno" << std::endl;
        std::cout << "In the scorching Blazing Inferno, The Azrul - guardians of evil awaited the warrior's arrival." << std::endl;
        std::cout << "Veera discovers the " << levels[levelIndex].specialItem << ", which helps heal his burns caused by the fiery inferno." << std::endl;
        break;
      }
      case 5:{
        std::cout << " - The Citadel" << std::endl;
        std::cout
        << "The FINAL BATTLE, with the mighty Murlocs - deadliest monster of Aldora!"
        << std::endl;
        std::cout << "Veera finds a " << levels[levelIndex].specialItem << ", which helps him with stealth attacks. " << std::endl;
        break;
      }
    }

    if (levelIndex == 5) {
      Enemy *enemy = new Enemy(75, 10, 5, "Enemy");
      enemy->isBossEnemy = true;
      enemy->specialAbilities = new SpecialAbility[2];
      enemy->addSpecialAbility(GroundSlash);
      enemy->addSpecialAbility(HealthRegeneration);
      fightEnemy(enemy);
    }

    else {
      for (int i = 0; i < level.noOfEnemies; i++) {
        Enemy *enemy = new Enemy(25, 10, 5, "Enemy");
        enemy->isBossEnemy = false;
        std::cout << std::endl << "Fight with Enemy " << i + 1 << std::endl;
        fightEnemy(enemy);
      }
    }
  }

  void fightEnemy(Enemy *enemy) {
    char keyPressed;

    std::cout << "\nPlayer Stats:\n ";
    player->printStats();

    std::cout << "\n\nEnemy Stats: \n";
    enemy->printStats();

    while (player->isAlive()) {
      std::cout << "\nPlayer press 'a' to attack or 'h' to heal" << std::endl;
      std::cin >> keyPressed;
      if (keyPressed == 'a') {
        attack(player, enemy, "Player", "Enemy ");
      } else if (keyPressed == 'h') {
        player->healPlayer();
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

    std::cout << opponentCharacterName
              << " health: " << opponentCharacter->getHealth() << std::endl;
  }

  ~Game() {
    delete[] levels;
  }
};

int main() {
  Game gameManager;

  gameManager.start();
}