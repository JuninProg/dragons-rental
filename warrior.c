#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "warrior.h"
#include "rent.h"

int MAX_WARRIORS = 2;
int TOTAL_WARRIORS = 0;
int NEXT_WARRIOR_CODE = 1;
char* WARRIORS_FILE_PATH = "./data/warriors.bin";

Warrior* WARRIORS;

Warrior GetBlankWarrior() {
  Warrior blankWarrior;

  blankWarrior.code = -1;
  strcpy(blankWarrior.name, "");
  strcpy(blankWarrior.title, "");
  strcpy(blankWarrior.kingdom, "");

  return blankWarrior;
}

int EndWarriors() {
  FILE *warriorsFile = fopen(WARRIORS_FILE_PATH, "wb");

  if (warriorsFile != NULL) {
    fwrite(WARRIORS, sizeof(Warrior), MAX_WARRIORS, warriorsFile);
    fclose(warriorsFile);
  }

  free(WARRIORS);

  return 0;
}

int ResizeWarriors() {
  int actualPercent = TOTAL_WARRIORS * 100 / MAX_WARRIORS;

  if (actualPercent > 0 && actualPercent < 40) {
    int newSize = MAX_WARRIORS;

    while ((TOTAL_WARRIORS * 100 / newSize) < 60) {
      newSize--;
    }

    // deixo buracos no meu array de guerreiros
    Warrior* newWarriors = (Warrior*) malloc(newSize * sizeof(Warrior));

    if (!newWarriors) {
      return 1;
    }

    int i;

    for (i = 0; i < newSize; i++) {
      newWarriors[i] = GetBlankWarrior();
    }

    int newIndex = 0;

    for (i = 0; i < MAX_WARRIORS; i++) {
      if (WARRIORS[i].code != -1) {
        newWarriors[newIndex] = WARRIORS[i];
        newIndex++;
      }
    }

    free(WARRIORS);

    WARRIORS = newWarriors;
    MAX_WARRIORS = newSize;
    
    // TODO: precisa desse free?
    // free(newWarriors);
  }

  return 0;
}

int InitiateWarriors() {
  FILE *warriorsFile = fopen(WARRIORS_FILE_PATH, "rb");

  if (warriorsFile != NULL) {
    fseek(warriorsFile, 0, SEEK_END);
    int totalBytes = ftell(warriorsFile);
    int totalWarriors = totalBytes / sizeof(Warrior);

    WARRIORS = (Warrior*) malloc(totalWarriors * sizeof(Warrior));

    if (WARRIORS == NULL) {
      fclose(warriorsFile);
      return 1;
    }

    rewind(warriorsFile);
    fread(WARRIORS, sizeof(Warrior), totalWarriors, warriorsFile);
    fclose(warriorsFile);

    MAX_WARRIORS = totalWarriors;

    int i;

    Warrior lastWarrior;

    for (i = 0; i < totalWarriors; i++) {
      if (WARRIORS[i].code != -1) {
        TOTAL_WARRIORS++;
        lastWarrior = WARRIORS[i];
      }
    }

    NEXT_WARRIOR_CODE = TOTAL_WARRIORS > 0 ? lastWarrior.code + 1 : NEXT_WARRIOR_CODE;
  } else {
    WARRIORS = (Warrior*) malloc(MAX_WARRIORS * sizeof(Warrior));
  
    if (!WARRIORS) {
      return 1;
    }

    int i;

    Warrior blankWarrior = GetBlankWarrior();

    for (i = 0; i < MAX_WARRIORS; i ++) {
      WARRIORS[i] = blankWarrior;
    }
  }

  return 0;
}

int GetWarriorsEmptyIndex() {
  int i;

  for (i = 0; i < MAX_WARRIORS; i++) {
    if (WARRIORS[i].code == -1) {
      return i;
    }
  }

  return -1;
}

int SaveWarrior(Warrior warrior) {
  int index = GetWarriorsEmptyIndex();

  if (index == -1) {
    Warrior* newWarriors = (Warrior*) realloc(WARRIORS, (MAX_WARRIORS + 1) * sizeof(Warrior));

    if (!newWarriors) {
      return 1;
    }

    // TODO: precisa desse free para liberar o endereço antigo?
    // free(WARRIORS);

    WARRIORS = newWarriors;
    MAX_WARRIORS++;

    index = MAX_WARRIORS - 1;

    // TODO: ou precisa desse free para liberar de newWarriors?
    // free(newWarriors);
  }

  warrior.code = NEXT_WARRIOR_CODE;
  WARRIORS[index] = warrior;

  NEXT_WARRIOR_CODE++;
  TOTAL_WARRIORS++;

  return 0;
}

int GetMaxWarriors() {
  return MAX_WARRIORS;
};

Warrior* GetWarriorByIndex(int index) {
  if (WARRIORS[index].code == -1) {
    return NULL;
  }

  Warrior* warrior = (Warrior*) malloc(sizeof(Warrior));

  if (warrior) {
    *warrior = WARRIORS[index];
  }

  return warrior;
};

Warrior* GetWarriorByCode(int code) {
  int i;

  for (i = 0; i < MAX_WARRIORS; i++) {
    if (WARRIORS[i].code == code) {
      Warrior* warrior = (Warrior*) malloc(sizeof(Warrior));

      if (warrior) {
        *warrior = WARRIORS[i];
      }

      return warrior;
    }
  }

  return NULL;
}

int DeleteWarriorByCode(int code) {
  if (GetTotalRentsByWarrior(code) > 0) {
    return 1;
  }

  int i;

  for (i = 0; i < MAX_WARRIORS; i++) {
    if (WARRIORS[i].code == code) {
      WARRIORS[i] = GetBlankWarrior();
      TOTAL_WARRIORS--;
      int resized = ResizeWarriors();
      return resized == 0 ? 0 : 2;
    }
  }

  return 2;
}

int UpdateWarriorByCode(Warrior warrior) {
  int i;

  for (i = 0; i < MAX_WARRIORS; i++) {
    if (WARRIORS[i].code == warrior.code) {
      WARRIORS[i] = warrior;
      return 0;
    }
  }

  return 1;
}
