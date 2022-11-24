#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "element.h"
#include "dragon.h"

int MAX_ELEMENTS = 5;
int TOTAL_ELEMENTS = 0;
int NEXT_ELEMENT_CODE = 10;
char* ELEMENTS_FILE_PATH = "./data/elements.bin";

Element* ELEMENTS;

int EndElements() {
  FILE *elementsFile = fopen(ELEMENTS_FILE_PATH, "wb");

  if (elementsFile == NULL) {
    return 1;
  }

  fwrite(ELEMENTS, sizeof(Element), MAX_ELEMENTS, elementsFile);

  fclose(elementsFile);

  return 0;
}

int ResizeElements() {
  int actualPercent = TOTAL_ELEMENTS * 100 / MAX_ELEMENTS;

  if (actualPercent > 0 && actualPercent < 40) {
    Element* ELEMENTS_COPY = (Element*) malloc(TOTAL_ELEMENTS * sizeof(Element));

    if (!ELEMENTS_COPY) {
      return 1;
    }

    int i;

    for (i = 0; i < MAX_ELEMENTS; i++) {
      if (ELEMENTS[i].code != -1) {
        ELEMENTS_COPY[i] = ELEMENTS[i];
      }
    }

    int newSize = MAX_ELEMENTS;

    while ((TOTAL_ELEMENTS * 100 / newSize) < 60) {
      newSize--;
    }
    
    ELEMENTS = (Element*) realloc(ELEMENTS, newSize * sizeof(Element));

    for (i = 0; i < TOTAL_ELEMENTS; i++) {
      ELEMENTS[i] = ELEMENTS_COPY[i];
    }
  }

  return 0;
}

Element GetBlankElement() {
  Element blankElement;

  blankElement.code = -1;
  strcpy(blankElement.name, "");
  strcpy(blankElement.vulnerability, "");

  return blankElement;
}

int InitiateElements() {
  FILE *elementsFile = fopen(ELEMENTS_FILE_PATH, "rb");

  if (elementsFile != NULL) {
    fseek(elementsFile, 0, SEEK_END);
    int totalBytes = ftell(elementsFile);
    int totalElements = totalBytes / sizeof(Element);

    ELEMENTS = (Element*) malloc(totalElements * sizeof(Element));

    if (ELEMENTS == NULL) {
      fclose(elementsFile);
      return 1;
    }

    rewind(elementsFile);
    fread(ELEMENTS, sizeof(Element), totalElements, elementsFile);
    fclose(elementsFile);

    MAX_ELEMENTS = totalElements;

    int i;

    for (i = 0; i < totalElements; i++) {
      if (ELEMENTS[i].code != -1) {
        TOTAL_ELEMENTS++;
      }
    }
  } else {
    ELEMENTS = (Element*) malloc(MAX_ELEMENTS * sizeof(Element));
  
    if (!ELEMENTS) {
      return 1;
    }

    int i;

    Element blankElement = GetBlankElement();

    for (i = 0; i < MAX_ELEMENTS; i ++) {
      ELEMENTS[i] = blankElement;
    }
  }

  return 0;
}

int GetElementsEmptyIndex() {
  int i;

  for (i = 0; i < MAX_ELEMENTS; i++) {
    if (ELEMENTS[i].code == -1) {
      return i;
    }
  }

  return -1;
}

int SaveElement(Element element) {
  int index = GetElementsEmptyIndex();

  if (index == -1) {
    return 1;
  }

  element.code = NEXT_ELEMENT_CODE;
  ELEMENTS[index] = element;

  NEXT_ELEMENT_CODE++;
  TOTAL_ELEMENTS++;

  return 0;
}

int GetMaxElements() {
  return MAX_ELEMENTS;
};

Element* GetElementByIndex(int index) {
  if (ELEMENTS[index].code == -1) {
    return NULL;
  }

  Element* element = (Element*) malloc(sizeof(Element));

  if (element) {
    *element = ELEMENTS[index];
  }

  return element;
};

Element* GetElementByCode(int code) {
  int i;

  for (i = 0; i < MAX_ELEMENTS; i++) {
    if (ELEMENTS[i].code == code) {
      Element* element = (Element*) malloc(sizeof(Element));

      if (element) {
        *element = ELEMENTS[i];
      }

      return element;
    }
  }

  return NULL;
}

int DeleteElementByCode(int code) {
  if (GetTotalDragonsByElement(code) > 0) {
    return 1;
  } 

  int i;

  for (i = 0; i < MAX_ELEMENTS; i++) {
    if (ELEMENTS[i].code == code) {
      ELEMENTS[i] = GetBlankElement();
      TOTAL_ELEMENTS--;
      int resized = ResizeElements();
      return resized == 0 ? 0 : 2;
    }
  }

  return 2;
}

int UpdateElementByCode(Element element) {
  int i;

  for (i = 0; i < MAX_ELEMENTS; i++) {
    if (ELEMENTS[i].code == element.code) {
      ELEMENTS[i] = element;
      return 0;
    }
  }

  return 1;
}
