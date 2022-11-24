#include <stdlib.h>
#include <stdio.h>

#include "warrior.h"
#include "dragon.h"
#include "element.h"
#include "rent.h"

#define WARRIOR 1
#define ELEMENT 2
#define DRAGON 3
#define RENT 4

Warrior WarriorForm() {
  Warrior warrior;

  printf("Nome: ");
  scanf("%s", warrior.name);
  printf("Titulo: ");
  scanf("%s", warrior.title);
  printf("Reino: ");
  scanf("%s", warrior.kingdom);

  return warrior;
}

void CreateWarrior() {
  printf("----- CADASTRAR GUERREIRO -----\n");
  
  Warrior warrior = WarriorForm();

  int saved = SaveWarrior(warrior);

  if (saved != 0) {
    printf("Nao ha espaco disponivel para cadastrar Guerreiro\n");
  } else {
    printf("Guerreiro cadastrado\n");
  }
  printf("----- CADASTRAR GUERREIRO -----\n");
};

void PrintWarrior(Warrior warrior) {
  printf("Codigo: %d\n", warrior.code);
  printf("Nome: %s\n", warrior.name);
  printf("Titulo: %s\n", warrior.title);
  printf("Reino: %s\n", warrior.kingdom);
}

void ListWarriors() {
  printf("----- LISTAR GUERREIROS -----\n");
  
  int i;

  for (i = 0; i < GetMaxWarriors(); i++) {
    Warrior* warriorFound = GetWarriorByIndex(i);

    if (warriorFound) {
      PrintWarrior(*warriorFound);
      free(warriorFound);
      printf("\n");
    }
  }

  printf("----- LISTAR GUERREIROS -----\n");
}

void FindWarrior() {
  printf("----- PESQUISAR GUERREIRO -----\n");

  int code;

  printf("Digite o codigo: ");
  scanf("%d", &code);

  Warrior* warriorFound = GetWarriorByCode(code);

  if (warriorFound) {
    PrintWarrior(*warriorFound);
    free(warriorFound);
  } else {
    printf("Guerreiro nao encontrado\n");
  } 

  printf("----- PESQUISAR GUERREIRO -----\n");
}

void RemoveWarrior() {
  printf("----- REMOVER GUERREIRO -----\n");
  ListWarriors();
  printf("\n");

  int code;
  printf("Digite o codigo: ");
  scanf("%d", &code);

  int deleted = DeleteWarriorByCode(code);

  switch (deleted) {
    case 0: 
      printf("Guerreiro removido com sucesso\n");
      break;
    case 1:
      printf("Guerreiro possui uma ou mais locacoes em aberto\n");
      break;
    case 2:
      printf("Guerreiro nao encontrado\n");
      break;
  }

  printf("----- REMOVER GUERREIRO -----\n");
}

void UpdateWarrior() {
  printf("----- ATUALIZAR GUERREIRO -----\n");
  ListWarriors();
  printf("\n");

  int code;

  printf("Digite o codigo do guerreiro: ");
  scanf("%d", &code);

  Warrior warrior = WarriorForm();
  warrior.code = code;

  int updated = UpdateWarriorByCode(warrior);

  if (updated == 0) {
    printf("Guerreiro atualizado com sucesso\n");
  } else {
    printf("Nao foi possivel atualizar guerreiro\n");
  }

  printf("----- ATUALIZAR GUERREIRO -----\n");
}


Element ElementForm() {
  Element element;

  printf("Nome: ");
  scanf("%s", element.name);
  printf("Vulnerabilidade: ");
  scanf("%s", element.vulnerability);

  return element;
}

void CreateElement() {
  printf("----- CADASTRAR ELEMENTO -----\n");

  Element element = ElementForm(); 

  int saved = SaveElement(element);

  if (saved == 1) {
    printf("Nao foi possivel cadastrar Elemento\n");
  } else {
    printf("Elemento cadastrado\n");
  }

  printf("----- CADASTRAR ELEMENTO -----\n");
};

void PrintElement(Element element) {
  printf("Codigo: %d\n", element.code);
  printf("Nome: %s\n", element.name);
  printf("Vulnerabilidade: %s\n", element.vulnerability);
}

void ListElements() {
  printf("----- LISTAR ELEMENTOS -----\n");
  
  int i;

  for (i = 0; i < GetMaxElements(); i++) {
    Element* elementFound = GetElementByIndex(i);

    if (elementFound) {
      PrintElement(*elementFound);
      free(elementFound);
    }
  }

  printf("----- LISTAR ELEMENTOS -----\n");
}

void FindElement() {
  printf("----- PESQUISAR ELEMENTO -----\n");

  int code;

  printf("Digite o codigo: ");
  scanf("%d", &code);

  Element* elementFound = GetElementByCode(code);

  if (elementFound) {
    PrintElement(*elementFound);
    free(elementFound);
  } else {
    printf("Elemento nao encontrado\n");
  } 

  printf("----- PESQUISAR ELEMENTO -----\n");
}

void RemoveElement() {
  printf("----- REMOVER ELEMENTO -----\n");
  ListElements();
  printf("\n");

  int code;
  printf("Digite o codigo: ");
  scanf("%d", &code);

  int deleted = DeleteElementByCode(code);

  switch (deleted) {
    case 1:
      printf("Elemento esta em uso por um ou mais dragoes\n");
      break;
    case 2:
      printf("Elemento nao encontrado\n");
      break;
    case 0:
      printf("Elemento removido com sucesso\n");
      break;     
  }

  printf("----- REMOVER ELEMENTO -----\n");
};

void UpdateElement() {
  printf("----- ATUALIZAR ELEMENTO -----\n");
  ListElements();
  printf("\n");

  int code;

  printf("Digite o codigo do elemento: ");
  scanf("%d", &code);

  Element element = ElementForm();
  element.code = code;

  int updated = UpdateElementByCode(element);

  if (updated == 0) {
    printf("Elemento atualizado com sucesso\n");
  } else {
    printf("Nao foi possivel atualizar elemento\n");
  }

  printf("----- ATUALIZAR ELEMENTO -----\n");
}



Dragon DragonForm() {
  Dragon dragon;

  printf("Nome: ");
  scanf("%s", dragon.name);
  printf("Idade: ");
  scanf("%d", &dragon.age);
  printf("Valor diario: ");
  scanf("%f", &dragon.dailyValue);
  printf("Quantidade em estoque: ");
  scanf("%d", &dragon.stock);

  return dragon;
}

void CreateDragon() {
  printf("----- CADASTRAR DRAGAO -----\n");
  
  Dragon dragon = DragonForm();

  printf("Codigo do elemento: ");
  scanf("%d", &dragon.elementCode);

  int saved = SaveDragon(dragon);

  switch (saved) {
    case 1:
      printf("Deve haver ao menos um Drago no estoque\n");
      break;
    case 2:
      printf("Nao ha espaco disponivel para cadastrar Dragao\n");
      break;
    case 3:
      printf("Elemento nao encontrado pelo codigo passado\n");
      break;
    case 0:
      printf("Dragao cadastrado\n");
      break;
  }

  printf("----- CADASTRAR DRAGAO -----\n");
};

void PrintDragon(Dragon dragon) {
  printf("Codigo: %d\n", dragon.code);
  printf("Codigo do elemento: %d\n", dragon.elementCode);
  printf("Nome: %s\n", dragon.name);
  printf("Idade: %d\n", dragon.age);
  printf("Valor diario: %2.f\n", dragon.dailyValue);
  printf("Quantidade em estoque: %d\n", dragon.stock);
}

void ListDragons() {
  printf("----- LISTAR DRAGOES -----\n");
  
  int i;

  for (i = 0; i < GetMaxDragons(); i++) {
    Dragon* dragonFound = GetDragonByIndex(i);

    if (dragonFound) {
      PrintDragon(*dragonFound);
      free(dragonFound);
    }
  }

  printf("----- LISTAR DRAGOES -----\n");
}

void FindDragon() {
  printf("----- PESQUISAR DRAGAO -----\n");

  int code;

  printf("Digite o codigo: ");
  scanf("%d", &code);

  Dragon* dragonFound = GetDragonByCode(code);

  if (dragonFound) {
    PrintDragon(*dragonFound);
    free(dragonFound);
  } else {
    printf("Dragao nao encontrado\n");
  } 

  printf("----- PESQUISAR DRAGAO -----\n");
}

void RemoveDragon() {
  printf("----- REMOVER DRAGAO -----\n");
  ListDragons();
  printf("\n");

  int code;
  printf("Digite o codigo: ");
  scanf("%d", &code);

  int deleted = DeleteDragonByCode(code);

  switch (deleted) {
    case 1:
      printf("Dragao esta locado por um ou mais guerreiros\n");
      break;
    case 2:
      printf("Dragao nao encontrado\n");
      break;
    case 0:
      printf("Dragao removido com sucesso\n");
      break;
  }

  printf("----- REMOVER DRAGAO -----\n");
}

void UpdateDragon() {
  printf("----- ATUALIZAR DRAGAO -----\n");
  ListDragons();
  printf("\n");

  int code;

  printf("Digite o codigo do dragao: ");
  scanf("%d", &code);

  Dragon dragon = DragonForm();
  dragon.code = code;

  int updated = UpdateDragonByCode(dragon);

  if (updated == 0) {
    printf("Dragao atualizado com sucesso\n");
  } else {
    printf("Nao foi possivel atualizar dragao\n");
  }

  printf("----- ATUALIZAR DRAGAO -----\n");
}



Rent RentForm() {
  Rent rent;

  printf("Esta pago 1 - sim ou 0 - nao: ");
  scanf("%d", &rent.paid);
  printf("Digite a data de inicio formato DD/MM/AAAA: ");
  scanf("%s", rent.initDate);
  printf("Digite a data de fime formato DD/MM/AAAA: ");
  scanf("%s", rent.endDate);

  return rent;
}

void CreateRent() {
  printf("----- CADASTRAR LOCACAO -----\n");
  
  Rent rent = RentForm();

  printf("Codigo do dragao: ");
  scanf("%d", &rent.dragonCode);
  printf("Codigo do guerreiro: ");
  scanf("%d", &rent.warriorCode);

  int saved = SaveRent(rent);

  switch (saved) {
    case 1:
      printf("Nao ha espaco disponivel para cadastrar locacao\n");
      break;
    case 2:
      printf("Dragao nao encontrado pelo codigo passado\n");
      break;
    case 3:
      printf("Guerreiro nao encontrado pelo codigo passado\n");
      break;
    case 4:
      printf("Nao ha estoque disponivel para locar esse dragao\n");
      break;
    case 0:
      printf("Locacao cadastrada com sucesso\n");
      break;
  }

  printf("----- CADASTRAR LOCACAO -----\n");
};

void PrintRent(Rent rent) {
  printf("Codigo: %d\n", rent.code);
  printf("Codigo do dragao: %d\n", rent.dragonCode);
  printf("Codigo do guerreiro: %d\n", rent.warriorCode);
  printf("Pago 1 - sim ou 0 - nao: %d\n", rent.paid);
  printf("Data de inicio: %s\n", rent.initDate);
  printf("Data de fim: %s\n", rent.endDate);
}

void ListRents() {
  printf("----- LISTAR LOCACOES -----\n");
  
  int i;

  for (i = 0; i < GetMaxRents(); i++) {
    Rent* rentFound = GetRentByIndex(i);

    if (rentFound) {
      PrintRent(*rentFound);
      free(rentFound);
    }
  }

  printf("----- LISTAR LOCACOES -----\n");
}

void FindRent() {
  printf("----- PESQUISAR LOCACAO -----\n");

  int code;

  printf("Digite o codigo: ");
  scanf("%d", &code);

  Rent* rentFound = GetRentByCode(code);

  if (rentFound) {
    PrintRent(*rentFound);
    free(rentFound);
  } else {
    printf("Locacao nao encontrada\n");
  } 

  printf("----- PESQUISAR LOCACAO -----\n");
}

void RemoveRent() {
  printf("----- REMOVER LOCACAO -----\n");
  ListRents();
  printf("\n");

  int code;
  printf("Digite o codigo: ");
  scanf("%d", &code);

  int deleted = DeleteRentByCode(code);

  if (deleted == 0) {
    printf("Locacao removida com sucesso\n");
  } else {
    printf("Locacao nao encontrada\n");
  }

  printf("----- REMOVER LOCACAO -----\n");
}

void UpdateRent() {
  printf("----- ATUALIZAR LOCACAO -----\n");
  ListRents();
  printf("\n");
  
  int code;

  printf("Digite o codigo da locacao: ");
  scanf("%d", &code);

  Rent rent = RentForm();
  rent.code = code;

  int updated = UpdateRentByCode(rent);

  if (updated == 0) {
    printf("Locacao atualizado com sucesso\n");
  } else {
    printf("Nao foi possivel atualizar locacao\n");
  }

  printf("----- ATUALIZAR LOCACAO -----\n");
}



int ShowMenu() {
  printf("MENU PRINCIPAL:\n");
  printf("0. Sair\n");
  printf("1. Guerreiros\n");
  printf("2. Dragoes\n");
  printf("3. Elementos de dragoes\n");
  printf("4. Locacoes\n");
  printf("\n");

  int option;
  printf("Digite uma opcao: ");
  scanf("%d", &option);

  return option;
}

void ShowSubmenu(int entity) {
  int option;

  do {
    printf("Submenu:\n");
    printf("0. Sair\n");
    printf("1. Cadastrar\n");
    printf("2. Listar\n");
    printf("3. Alterar\n");
    printf("4. Pesquisar\n");
    printf("5. Excluir\n");
    printf("\n");

    printf("Digite uma opcao: ");
    scanf("%d", &option);
    printf("\n");

    switch (option) {
      case 1:
        switch (entity) {
          case 1:
            CreateWarrior();
            break;
          case 2:
            CreateElement();
            break;
          case 3:
            CreateDragon();
            break;
          case 4:
            CreateRent();
            break;
        }
        break;
      case 2:
        switch (entity) {
          case 1:
            ListWarriors();
            break;
          case 2:
            ListElements();
            break;
          case 3:
            ListDragons();
            break;
          case 4:
            ListRents();
            break;
        }
        break;
      case 3:
        switch (entity) {
          case 1:
            UpdateWarrior();
            break;
          case 2:
            UpdateElement();
            break;
          case 3:
            UpdateDragon();
            break; 
          case 4:
            UpdateRent();
            break;
        }
        break;
      case 4:
        switch (entity) {
          case 1:
            FindWarrior();
            break;
          case 2:
            FindElement();
            break;
          case 3:
            FindDragon();
            break;
          case 4:
            FindRent();
            break;
        }
        break;
      case 5:
        switch (entity) {
          case 1:
            RemoveWarrior();
            break;
          case 2:
            RemoveElement();
            break;
          case 3:
            RemoveDragon();
            break;
          case 4:
            RemoveRent();
            break;
        }
        break;
    }
    printf("\n");
  } while (option != 0);
}

int main() {
  int start = InitiateWarriors() + InitiateDragons() + InitiateElements() + InitiateRents();

  if (start > 0) {
    return 0;
  }

  int option, subOption;

  do {
    option = ShowMenu();

    switch (option) {
      case 1:
        printf("\n");
        printf("----- GUERREIROS -----\n");
        ShowSubmenu(WARRIOR);
        break;
      case 2:
        printf("\n");
        printf("----- DRAGOES -----\n");
        ShowSubmenu(DRAGON);
        break;
      case 3:
        printf("\n");
        printf("----- ELEMENTOS DE DRAGOES -----\n");
        ShowSubmenu(ELEMENT);
        break;
      case 4:
        printf("\n");
        printf("----- LOCACOES -----\n");
        ShowSubmenu(RENT);
        break;
    }
  } while (option != 0);

  int finished = EndWarriors() + EndRents() + EndElements() + EndDragons();

  if (finished != 0) {
    return 1;
  }

  return 0;
}
