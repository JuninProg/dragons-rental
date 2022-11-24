#define STR_LEN 50

typedef struct {
  int code;
  int warriorCode;
  int dragonCode;
  int paid;
  char initDate[STR_LEN];
  char endDate[STR_LEN];
} Rent;

int InitiateRents();
int SaveRent(Rent rent);
int GetMaxRents();
Rent* GetRentByIndex(int index);
Rent* GetRentByCode(int code);
int DeleteRentByCode(int code);
int GetTotalRentsByWarrior(int warriorCode);
int GetTotalRentsByDragon(int dragonCode);
int UpdateRentByCode(Rent rent);
int EndRents();
