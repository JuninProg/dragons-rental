#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "rent.h"
#include "dragon.h"
#include "warrior.h"

int MAX_RENTS = 5;
int TOTAL_RENTS = 0;
int NEXT_RENT_CODE = 30;
char* RENTS_FILE_PATH = "./data/rents.bin";

Rent* RENTS;

Rent GetBlankRent() {
  Rent blankRent;

  blankRent.code = -1;
  blankRent.warriorCode = -1;
  blankRent.dragonCode = -1;
  blankRent.paid = 0;
  strcpy(blankRent.initDate, "");
  strcpy(blankRent.endDate, "");

  return blankRent;
}

int EndRents() {
 FILE *rentsFile = fopen(RENTS_FILE_PATH, "wb");

  if (rentsFile != NULL) {
    fwrite(RENTS, sizeof(Rent), MAX_RENTS, rentsFile);
    fclose(rentsFile);
  }

  free(RENTS);

  return 0;
}

int ResizeRents() {
 int actualPercent = TOTAL_RENTS * 100 / MAX_RENTS;

  if (actualPercent > 0 && actualPercent < 40) {
    int newSize = MAX_RENTS;

    while ((TOTAL_RENTS * 100 / newSize) < 60) {
      newSize--;
    }

    // deixo buracos no meu array de locacoes
    Rent* newRents = (Rent*) malloc(newSize * sizeof(Rent));

    if (!newRents) {
      return 1;
    }

    int i;

    for (i = 0; i < newSize; i++) {
      newRents[i] = GetBlankRent();
    }

    int newIndex = 0;

    for (i = 0; i < MAX_RENTS; i++) {
      if (RENTS[i].code != -1) {
        newRents[newIndex] = RENTS[i];
        newIndex++;
      }
    }

    free(RENTS);

    RENTS = newRents;
    MAX_RENTS = newSize;
  }

  return 0;
}

int InitiateRents() {
 FILE *rentsFile = fopen(RENTS_FILE_PATH, "rb");

  if (rentsFile != NULL) {
    fseek(rentsFile, 0, SEEK_END);
    int totalBytes = ftell(rentsFile);
    int totalRents = totalBytes / sizeof(Rent);

    RENTS = (Rent*) malloc(totalRents * sizeof(Rent));

    if (RENTS == NULL) {
      fclose(rentsFile);
      return 1;
    }

    rewind(rentsFile);
    fread(RENTS, sizeof(Rent), totalRents, rentsFile);
    fclose(rentsFile);

    MAX_RENTS = totalRents;

    int i;

    Rent lastRent;

    for (i = 0; i < totalRents; i++) {
      if (RENTS[i].code != -1) {
        TOTAL_RENTS++;
        lastRent = RENTS[i];
      }
    }

    NEXT_RENT_CODE = TOTAL_RENTS > 0 ? lastRent.code + 1 : NEXT_RENT_CODE;
  } else {
    RENTS = (Rent*) malloc(MAX_RENTS * sizeof(Rent));
  
    if (!RENTS) {
      return 1;
    }

    int i;

    Rent blankRent = GetBlankRent();

    for (i = 0; i < MAX_RENTS; i ++) {
      RENTS[i] = blankRent;
    }
  }

  return 0;
}

int GetRentsEmptyIndex() {
  int i;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].code == -1) {
      return i;
    }
  }

  return -1;
}

int SaveRent(Rent rent) {
  int index = GetRentsEmptyIndex();

  if (index == -1) {
    Rent* newRents = (Rent*) realloc(RENTS, (MAX_RENTS + 1) * sizeof(Rent));

    if (!newRents) {
      return 1;
    }

    RENTS = newRents;
    MAX_RENTS++;

    index = MAX_RENTS - 1;
  }

  Dragon* dragonFound = GetDragonByCode(rent.dragonCode);

  if (!dragonFound) {
    return 2;
  }

  Warrior* warriorFound = GetWarriorByCode(rent.warriorCode);

  if (!warriorFound) {
    return 3;
  }
  free(warriorFound);

  if (dragonFound->stock == 0) {
    return 4;
  }

  rent.code = NEXT_RENT_CODE;
  RENTS[index] = rent;

  NEXT_RENT_CODE++;
  TOTAL_RENTS++;
  UpdateDragonStock(dragonFound->code, -1);
  free(dragonFound);

  return 0;
}

int GetMaxRents() {
  return MAX_RENTS;
};

Rent* GetRentByIndex(int index) {
  if (RENTS[index].code == -1) {
    return NULL;
  }

  Rent* rent = (Rent*) malloc(sizeof(Rent));

  if (rent) {
    *rent = RENTS[index];
  }

  return rent;
};

Rent* GetRentByCode(int code) {
  int i;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].code == code) {
      Rent* rent = (Rent*) malloc(sizeof(Rent));

      if (rent) {
        *rent = RENTS[i];
      }

      return rent;
    }
  }

  return NULL;
}

int DeleteRentByCode(int code) {
  int i;

  int rentIndex = -1;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].code == code) {
      rentIndex = i;
      break;
    }
  }

  if (rentIndex != -1) {
    Dragon* dragonFound = GetDragonByCode(RENTS[rentIndex].dragonCode);

    if (dragonFound) {      
      UpdateDragonStock(dragonFound->code, 1);
      free(dragonFound);
    }

    RENTS[rentIndex] = GetBlankRent();
    TOTAL_RENTS--;
    return ResizeRents();
  }

  return 1;
}

int GetTotalRentsByWarrior(int warriorCode) {
  int i;

  int total = 0;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].warriorCode == warriorCode) {
      total++;
    }
  }

  return total;
}

int GetTotalRentsByDragon(int dragonCode) {
  int i;

  int total = 0;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].dragonCode == dragonCode) {
      total++;
    }
  }

  return total;
}

int UpdateRentByCode(Rent rent) {
  int i;

  for (i = 0; i < MAX_RENTS; i++) {
    if (RENTS[i].code == rent.code) {
      int IDENTIFIERS[] = { RENTS[i].warriorCode, RENTS[i].dragonCode };
      RENTS[i] = rent;
      RENTS[i].warriorCode = IDENTIFIERS[0];
      RENTS[i].dragonCode = IDENTIFIERS[1];
      return 0;
    }
  }

  return 1;
}
