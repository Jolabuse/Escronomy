#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void ActionMissing(Act_obl* action, int numAc, int nomBac);
int nb_player();
void PEA(Player* players, int nb);
void project_evolution(list_entreprise** firms);
int new_project(Entreprise* firm);
int project_stagne(Entreprise* firm);
void project_action(list_entreprise* firms,Player* players, int nb);
void decrease_number_firm(list_entreprise** firms,int deleted);
void delete_entreprise(list_entreprise* l,Entreprise* e);
void crash_5(list_entreprise** firms,Player* players,int nb);
long add_value(list_act_obl* l);
long value(Portefeuille p);
void remove_list_act_obl(Portefeuille* p,Act_obl* a);
void taxes(Player* joueurX,int nb);
void interest(Player* joueurX, int nj);
void add_end_obligation(list_act_obl** firms,list_act_obl* e);
void transfer_act(Portefeuille* p1,Portefeuille* p2,Act_obl* a);
void DeadPlayer(Player* Joueurx, int *nj,int nD);
void faillite(Player* joueurx,int* nb,int n1);
void MoneyFlow(Player* joueurx, Entreprise entreprise, int maxdeTune, int n1, int n2,int p1,int p2,int nb);
void Dividende(Player* joueurx,list_entreprise* l);
int owner_act(Player* joueurx, Entreprise firm,int n1);
void modify_act(Entreprise* firm,int price);
void Achat(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player* joueurX,Entreprise entreprise,char* turn,int* quit,list_entreprise* firms,int* nb);
void global_achat(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,Player* joueurX,list_entreprise* firms,int* nb,char* turn);
void add_end_firm(list_entreprise** firms,list_entreprise* e);
list_entreprise* new_e(int s,int i,char* nam,int nb);
char* name_set(int i);
int secteur(int i);
void disp_portefeuille(Portefeuille p);
void disp_player(Player* joueurX,int nb);
void Disp_project(list_entreprise* listentreprise);
void increment_turn(list_entreprise** firms);
void disp_entreprise(list_entreprise* firms);
void game(Player* joueurx,list_entreprise** firms,int* nb, SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit);
void red_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit);
void black_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit);
void green_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit);
void yellow_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit);
void white_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int quit);
void blue_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int quit);
int is_int(char c);
char* qr();
void free_list_e(list_entreprise* e);
int find_act(int n,Entreprise firm);
void defreeze(Player* joueurX,int nb_player);


#endif // BASE_H_INCLUDED
