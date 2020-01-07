#include <stdio.h>

#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define TRUE (1)
#define FALSE (0)

#define DELIM_V_1 (",:")
#define DELIM_COMMA (",")
#define DELIM_VERTICAL_BAR ("|")

enum {
    NAME_LEN = 51,
    MINION_LEN = 3
};

typedef enum version {
    VERSION_INVALID = 0,
    VERSION_1 = 1,
    VERSION_2 = 2,
    VERSION_3 = 3
} version_t;

typedef struct {
    char name[NAME_LEN];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    char name[NAME_LEN];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    elemental_resistance_t elemental_resistance;
    size_t minion_count;
    minion_t minions[MINION_LEN];
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

version_t get_version(char* buffer);

void trim(char* str);

unsigned int atoui(char* str);

#endif /* CHARACTER_DESERIALIZER_H */
