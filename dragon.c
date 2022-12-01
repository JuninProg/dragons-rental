#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dragon.h"
#include "element.h"
#include "rent.h"

int MAX_DRAGONS = 5;
int TOTAL_DRAGONS = 0;
int NEXT_DRAGON_CODE = 20;
char* DRAGONS_FILE_PATH = "./data/dragons.bin";

Dragon* DRAGONS;

Dragon GetBlankDragon() {
  Dragon blankDragon;

  blankDragon.code = -1;
  blankDragon.elementCode = -1;
  strcpy(blankDragon.name, "");
  blankDragon.age = 0;
  blankDragon.dailyValue = 0;
  blankDragon.stock = 0;

  return blankDragon;
}

int EndDragons() {
  FILE *dragonsFile = fopen(DRAGONS_FILE_PATH, "wb");

  if (dragonsFile != NULL) {
    fwrite(DRAGONS, sizeof(Dragon), MAX_DRAGONS, dragonsFile);
    fclose(dragonsFile);
  }

  free(DRAGONS);

  return 0;
}

int ResizeDragons() {
   int actualPercent = TOTAL_DRAGONS * 100 / MAX_DRAGONS;

  if (actualPercent > 0 && actualPercent < 40) {
    int newSize = MAX_DRAGONS;

    while ((TOTAL_DRAGONS * 100 / newSize) < 60) {
      newSize--;
    }

    Dragon* newDragons = (Dragon*) malloc(newSize * sizeof(Dragon));

    if (!newDragons) {
      return 1;
    }

    int i;

    for (i = 0; i < newSize; i++) {
      newDragons[i] = GetBlankDragon();
    }

    int newIndex = 0;

    for (i = 0; i < MAX_DRAGONS; i++) {
      if (DRAGONS[i].code != -1) {
        newDragons[newIndex] = DRAGONS[i];
        newIndex++;
      }
    }

    free(DRAGONS);

    DRAGONS = newDragons;
    MAX_DRAGONS = newSize;
  }

  return 0;
}

int InitiateDragons() {
  FILE *dragonsFile = fopen(DRAGONS_FILE_PATH, "rb");

  if (dragonsFile != NULL) {
    fseek(dragonsFile, 0, SEEK_END);
    int totalBytes = ftell(dragonsFile);
    int totalDragons = totalBytes / sizeof(Dragon);

    DRAGONS = (Dragon*) malloc(totalDragons * sizeof(Dragon));

    if (DRAGONS == NULL) {
      fclose(dragonsFile);
      return 1;
    }

    rewind(dragonsFile);
    fread(DRAGONS, sizeof(Dragon), totalDragons, dragonsFile);
    fclose(dragonsFile);

    MAX_DRAGONS = totalDragons;

    int i;

    Dragon lastDragon;

    for (i = 0; i < totalDragons; i++) {
      if (DRAGONS[i].code != -1) {
        TOTAL_DRAGONS++;
        lastDragon = DRAGONS[i];
      }
    }

    NEXT_DRAGON_CODE = TOTAL_DRAGONS > 0 ? lastDragon.code + 1 : NEXT_DRAGON_CODE;
  } else {
    DRAGONS = (Dragon*) malloc(MAX_DRAGONS * sizeof(Dragon));
  
    if (!DRAGONS) {
      return 1;
    }

    int i;

    Dragon blankDragon = GetBlankDragon();

    for (i = 0; i < MAX_DRAGONS; i ++) {
      DRAGONS[i] = blankDragon;
    }
  }

  return 0;
}

int GetDragonsEmptyIndex() {
  int i;

  for (i = 0; i < MAX_DRAGONS; i++) {
    if (DRAGONS[i].code == -1) {
      return i;
    }
  }

  return -1;
}

int SaveDragon(Dragon dragon) {
  if (dragon.stock < 1) {
    return 1;
  }

  int index = GetDragonsEmptyIndex();

  if (index == -1) {
    Dragon* newDragons = (Dragon*) realloc(DRAGONS, (MAX_DRAGONS + 1) * sizeof(Dragon));

    if (!newDragons) {
      return 2;
    }

    DRAGONS = newDragons;
    MAX_DRAGONS++;

    index = MAX_DRAGONS - 1;
  }

  Element* elementFound = GetElementByCode(dragon.elementCode);

  if (!elementFound) {
    return 3;
  }
  free(elementFound);

  dragon.code = NEXT_DRAGON_CODE;
  DRAGONS[index] = dragon;

  NEXT_DRAGON_CODE++;
  TOTAL_DRAGONS++;

  return 0;
}

int GetMaxDragons() {
  return MAX_DRAGONS;
};

Dragon* GetDragonByIndex(int index) {
  if (DRAGONS[index].code == -1) {
    return NULL;
  }

  Dragon* dragon = (Dragon*) malloc(sizeof(Dragon));

  if (dragon) {
    *dragon = DRAGONS[index];
  }

  return dragon;
};

Dragon* GetDragonByCode(int code) {
  int i;

  for (i = 0; i < MAX_DRAGONS; i++) {
    if (DRAGONS[i].code == code) {
      Dragon* dragon = (Dragon*) malloc(sizeof(Dragon));

      if (dragon) {
        *dragon = DRAGONS[i];
      }

      return dragon;
    }
  }

  return NULL;
}

int DeleteDragonByCode(int code) {
  if (GetTotalRentsByDragon(code) > 0) {
    return 1;
  }

  int i;

  for (i = 0; i < MAX_DRAGONS; i++) {
    if (DRAGONS[i].code == code) {
      DRAGONS[i] = GetBlankDragon();
      TOTAL_DRAGONS--;
      int resized = ResizeDragons();
      return resized == 0 ? 0 : 2;    
    }
  }

  return 2;
}

int GetTotalDragonsByElement(int elementCode) {
  int i;

  int total = 0;

  for (i = 0; i < MAX_DRAGONS; i++) {
    if (DRAGONS[i].elementCode == elementCode) {
      total++;
    }
  }

  return total;
}

void UpdateDragonStock(int code, int value) {
  int index = -1;

  int i;

  for (i = 0; i < MAX_DRAGONS; i ++) {
    if (DRAGONS[i].code == code) {
      index = i;
      break;
    }
  }

  DRAGONS[index].stock += value;
}

int UpdateDragonByCode(Dragon dragon) {
  int i;

  for (i = 0; i < MAX_DRAGONS; i++) {
    if (DRAGONS[i].code == dragon.code) {
      int elementCode = DRAGONS[i].elementCode;
      DRAGONS[i] = dragon;
      DRAGONS[i].elementCode = elementCode;
      return 0;
    }
  }

  return 1;
}
