#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "window.h"
#include "Struct.h"
#include "base.h"







int main(int argc, char *argv[])
{
    int nb_player=0;
    SDL_Init(SDL_INIT_VIDEO); // initialisation de la sdl video
    TTF_Init();
    SDL_Window *wind=SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 800, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    // création de la fenêtre, attribution du nom, positionin width, position in length, width of window, length of windows
    if(wind == NULL){
        SDL_Log("EREUR > %s\n", SDL_GetError());
        clean_resources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }//vide la variable si pb

    SDL_Renderer *render=SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);//création rendu
    if(render == NULL){
        SDL_Log("EREUR > %s\n", SDL_GetError());
        clean_resources(wind, NULL, NULL);
        exit(EXIT_FAILURE);
    }//vide window s'il y a eu un pb

    ///TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 75);

    SDL_SetRenderDrawColor(render, 255,255,255,0);// couleur blanc


    int window_width,window_height;
    SDL_GetWindowSize(wind,&window_width,&window_height);//we get the window_size

    int quit=0;
    opening_screen(wind,render,window_width,window_height,&quit,&nb_player);//launch screen

 
    Player* players=malloc((nb_player+1)*sizeof(Player));//malloc our players with the nb_player
    list_entreprise* firms=NULL;
    list_entreprise* e;


    for (int i=0;i<nb_player+1;i++)
    {
        players[i].actions=malloc(3*sizeof(Portefeuille));
        players[i].number=i;
        players[i].money=1500;
        players[i].freeze=0;//the wallet isn't freeze
        for(int j=0;j<3;j++)
        {
            if (j!=2)//for the two first
            {
                players[i].actions[j].locked=j;// 1 will be locked and 0 no
                players[i].actions[j].type=j;
            }
            else
            {
                players[i].actions[j].locked=0;
                players[i].actions[j].type=0;

            }
            players[i].actions[j].length=0;
            players[i].actions[j].total_value=0;
            players[i].actions[j].content=NULL;
        }
    }


    for(int i=0;i<10;i++)//we initialize 10 firms
    {
        e=new_e(secteur(i),i,name_set(i),nb_player);
        add_end_firm(&firms,e);
    }


    /*game(players,&firms,&nb_player,wind,render,window_width,window_height,&quit);//we start the */
    
    



    

    free_list_e(firms);//bunch of frees
    for (int i=0;i<=nb_player+1;i++)
    {
        for(int j=0;j<3;j++)
        {
            free(players[i].actions[j].content);
        }
        free(players[i].actions);
    }
    free(players);


    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(wind);
    TTF_Quit();
    SDL_Quit();
    return 0;
}