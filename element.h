#define STR_LEN 50

typedef struct {
  int code;
  char name[STR_LEN];
  char vulnerability[STR_LEN];
} Element;

int InitiateElements();
int SaveElement(Element element);
int GetMaxElements();
Element* GetElementByIndex(int index);
Element* GetElementByCode(int code);
int DeleteElementByCode(int code);
int UpdateElementByCode(Element element);
int EndElements();

