#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct
{
    int player;
    int portefeuille;
}Owner;


typedef struct
{
    int type;//0 action 1 obligation
    long int value;//valeur de l'action/obligation
    int durability; // pour obligations
    int firm;//quelle entreprise
    int interest;//int�r�t
    Owner owner;//6 jamais vendu
}Act_obl;

typedef struct
{
    int secteur;
    char* name;//
    int number;// son num�ro d'identification
    int number_act;//nombre d'action en vente
    int* project_state;//0 echec total, 1 echec, 2 stable, 3 r�ussite, 4 r�ussite totale
    int turn;
    Act_obl* actions;
}Entreprise;

typedef struct Element
{
    Act_obl* val;
    struct Element* next;
}list_act_obl;


typedef struct
{
    int type;//0 ordinaire 1 PEA
    list_act_obl* content;
    int length;
    int total_value;
    int locked;//0 non 1 oui
}Portefeuille;

typedef struct l_e
{
    Entreprise* val;
    struct l_e* next;
    int length;
}list_entreprise;

typedef struct
{
    int number;
    Portefeuille* actions;
    int freeze;
    long money;
}Player;

#endif // STRUCT_H_INCLUDED
