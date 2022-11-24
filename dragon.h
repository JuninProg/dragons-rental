#define STR_LEN 50

typedef struct {
  int code;
  int elementCode;
  char name[STR_LEN];
  int age;
  float dailyValue;
  int stock;
} Dragon;

int InitiateDragons();
int SaveDragon(Dragon dragon);
int GetMaxDragons();
Dragon* GetDragonByIndex(int index);
Dragon* GetDragonByCode(int code);
int DeleteDragonByCode(int code);
int GetTotalDragonsByElement(int elementCode);
void UpdateDragonStock(int code, int value);
int UpdateDragonByCode(Dragon dragon);
int EndDragons();
