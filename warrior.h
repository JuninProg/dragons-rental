#define STR_LEN 50

typedef struct {
  int code;
  char name[STR_LEN];
  char kingdom[STR_LEN];
  char title[STR_LEN];
} Warrior;

int InitiateWarriors();
int SaveWarrior(Warrior warrior);
int GetMaxWarriors();
Warrior* GetWarriorByIndex(int index);
Warrior* GetWarriorByCode(int code);
int DeleteWarriorByCode(int code);
int UpdateWarriorByCode(Warrior warrior);
int EndWarriors();
