#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Struct.h"


void opening_screen(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int * quit, int* nb_player);
int selection_nb_player(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int * quit);
void game_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,char * turn);
void player_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurx, int nb_player);
int choose_player_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit);
void button_info(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_scan(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
int select_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit);
void play_cards(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit,list_entreprise * firms);
void info_player(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit,list_entreprise * firms);
void window_firm(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void firm_screen(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms);
void firm_project(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firm);
void back_button(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void firm_info(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player);
int detect_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player,char* turn,int player);
void spin(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player,char* turn);
void window_spin(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,Player* joueurX,int nb_player, int player,char* turn);
void window_yellow_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_black_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_green_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_white_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_blue_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void window_red_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height);
void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture * t);
int translate(char* s);
void info_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int *quit);
int window_announce(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player* joueurX,Entreprise entreprise,char* turn,int i,int* quit,list_entreprise* firms,int nb_player);
int select_buyer(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms);
void amount_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int n,char* turn);
int select_amount(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int player);
int select_wallet(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int nb);
void window_locked(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int nb,time_t t_launch,time_t t_counter);
int select_seller(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms);
int select_firm(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit, Player* joueurX,list_entreprise* firms);
int choose_target_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit);
void reverse_day(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,Player* players);


#endif