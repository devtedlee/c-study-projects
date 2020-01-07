#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "character_deserializer.h"

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* char_file;
    char buffer[512] = { 0, };
    char* buffer_p = buffer;
    char temp_buffer[51];
    version_t version;
    char* token;
    size_t i;
    
    char_file = fopen(filename, "r");
    fgets(buffer, sizeof(buffer), char_file);
    
    version = get_version(buffer_p);

    if (version == VERSION_INVALID) {
        return FALSE;
    }

    switch (version) {
    case VERSION_1:
        token = strtok(buffer, DELIM_V_1);
        while (token != NULL) {
            if (strcmp("id", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                sprintf(temp_buffer, "player_%s", token);
                strcpy(out_character->name, temp_buffer);
            } else if (strcmp("lvl", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->level = atoui(token);
            } else if (strcmp("str", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->strength = atoui(token);
            } else if (strcmp("dex", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->dexterity = atoui(token);
            } else if (strcmp("intel", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->intelligence = atoui(token);
            } else if (strcmp("def", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->armour = atoui(token);
            } else if (strcmp("hp", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->health = atoui(token);
            } else if (strcmp("mp", token) == 0) {
                token = strtok(NULL, DELIM_V_1);
                out_character->mana = atoui(token);
            } else {
                assert(0);
                return FALSE;
            }

            token = strtok(NULL, DELIM_V_1);
        }

        out_character->evasion = out_character->dexterity / 2;
        out_character->leadership = out_character->level / 10;
        out_character->elemental_resistance.fire = out_character->armour / 12;
        out_character->elemental_resistance.cold = out_character->armour / 12;
        out_character->elemental_resistance.lightning = out_character->armour / 12;
        out_character->minion_count = 0;

        break;
    case VERSION_2:
        fgets(buffer, sizeof(buffer), char_file);

        token = strtok(buffer, DELIM_COMMA);
        strncpy(out_character->name, token, NAME_LEN);
        out_character->name[50] = '\0';

        token = strtok(NULL, DELIM_COMMA);
        out_character->level = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->strength = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->dexterity = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->intelligence = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->armour = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->evasion = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->elemental_resistance.fire = atoui(token) / 3;

        token = strtok(NULL, DELIM_COMMA);
        out_character->health = atoui(token);

        token = strtok(NULL, DELIM_COMMA);
        out_character->mana = atoui(token);

        out_character->leadership = out_character->level / 10;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        out_character->minion_count = 0;

        break;
    case VERSION_3:
        fgets(buffer, sizeof(buffer), char_file);

        trim(buffer_p);

        token = strtok(buffer, DELIM_VERTICAL_BAR);
        strncpy(out_character->name, token, NAME_LEN);
        out_character->name[50] = '\0';

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->level = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->health = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->mana = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->strength = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->dexterity = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->intelligence = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->armour = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->evasion = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->elemental_resistance.fire = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->elemental_resistance.cold = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->elemental_resistance.lightning = atoui(token);

        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->leadership = atoui(token);
        
        token = strtok(NULL, DELIM_VERTICAL_BAR);
        out_character->minion_count = atoui(token);
        
        if (out_character->minion_count > 0) {
            fgets(buffer, sizeof(buffer), char_file);

            for (i = 0; i < out_character->minion_count; i++) {
                fgets(buffer, sizeof(buffer), char_file);
                trim(buffer_p);
                token = strtok(buffer, DELIM_VERTICAL_BAR);
                strncpy(out_character->minions[i].name, token, NAME_LEN);
                out_character->minions[i].name[50] = '\0';

                token = strtok(NULL, DELIM_VERTICAL_BAR);
                out_character->minions[i].health = atoui(token);

                token = strtok(NULL, DELIM_VERTICAL_BAR);
                out_character->minions[i].strength = atoui(token);

                token = strtok(NULL, DELIM_VERTICAL_BAR);
                out_character->minions[i].defence = atoui(token);
            }
        }

        break;
    default:
        return FALSE;
    }

    fclose(char_file);
    return version;
}

version_t get_version(char* buffer)
{
    while (*buffer != '\0') {
        if (*buffer == ':') {
            return VERSION_1;
        } else if (*buffer == ',') {
            return VERSION_2;
        } else if (*buffer == '|') {
            return VERSION_3;
        }

        ++buffer;
    }

    assert(0);
    return VERSION_INVALID;
}

void trim(char* str)
{
    while (*str != '\0') {
        if (*str == ' ' || *str == '\n') {
            strcpy(str, str + 1);
            --str;
        }

        ++str;
    }
}

unsigned int atoui(char* str)
{
    int number = 0;

    while (*str != '\0') {
        number = number * 10 + *str - '0';
        
        ++str;
    }

    return (unsigned int)number;
}
