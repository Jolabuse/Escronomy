#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "window.h"
#include "base.h"


void opening_screen(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int * quit,int * nb_player)
{
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 75);

    SDL_Surface* image = SDL_LoadBMP("../assets/Mascotte.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect dstrect = {0, 0, window_width, window_height};
    SDL_RenderCopy(render, monImage, NULL,  &dstrect);


    SDL_Rect dstrect2={3*window_width/5,window_height/4,150,30};//initialisation du rectangle où le texte apparaîtra
    SDL_Color color_text = { 0, 0, 0 }; // établit la couleur du texte
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CLICK TO PLAY", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte); //création de la texture où on mettra la surface
    SDL_QueryTexture(texte2, NULL, NULL, &dstrect2.w, &dstrect2.h); // Blit du texte 
    SDL_RenderCopy(render,texte2, NULL, &dstrect2);
    

    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    texte = TTF_RenderText_Blended(font, "ESCRONOMY", color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    dstrect2.x=28*window_width/50;
    dstrect2.y=window_height/6;

    SDL_QueryTexture(texte2, NULL, NULL, &dstrect2.w, &dstrect2.h); // Blit du texte 
    SDL_RenderCopy(render,texte2, NULL, &dstrect2);
    
    SDL_RenderPresent(render);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
                *quit = 1;
                break;
        
        case SDL_MOUSEBUTTONDOWN:
            SDL_RenderClear(render);
            *nb_player=selection_nb_player(wind,render,window_width,window_height,quit);
            return;
        }
    }
    
        



    
}


int selection_nb_player(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int * quit)
{
    SDL_Rect r={0,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE NUMBER OF PLAYERS", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    
    SDL_SetRenderDrawColor(render,0,0,0,255);

    SDL_Surface* image = SDL_LoadBMP("../assets/button.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={0,0,window_width/2,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.y=window_height*0.55;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/2;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.y=0;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);


    SDL_RenderPresent(render);
    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;
    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    return 0;
                    break;
            
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;      // Returns mouse motion y.
            if(x<window_width/2 && y<window_height*0.45)
            {
                SDL_RenderClear(render);
                return 4;
            }
                
            if (x>window_width/2 && y<window_height*0.45)
            {
                SDL_RenderClear(render);
                return 5;
            }

            if (x<window_width/2 && y>window_height*0.55)
            {
                SDL_RenderClear(render);
                return 6;
            }

            if (x>window_width/2 && y>window_height*0.55)
            {
                SDL_RenderClear(render);
                return 7;
            }            
            break;
        }
    }

    
    return 0;

}

void game_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,char * turn)
{
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect r={window_width*0.89,window_height*0.88,130,80};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "TURN", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=window_height*0.93;
    r.x=window_width*0.93;
    texte = TTF_RenderText_Blended(font,turn,color_text);
    texte2 = SDL_CreateTextureFromSurface(render,texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    SDL_Surface* image = SDL_LoadBMP("../assets/button.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={0,0,window_width/4,window_height/3};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button2.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button1.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=0;
    r2.x=window_width/4;
    r2.h=window_height;
    r2.w=3*window_width/4;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);
}

void player_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player)
{
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);

    
    double f=7.000/nb_player;
    SDL_Surface* image = SDL_LoadBMP("../assets/button.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={0,0,window_width/4,window_height/3};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button2.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button1.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=2*window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.y=0;
    r2.x=window_width/4;
    r2.h=window_height;
    r2.w=3*window_width/4;
    SDL_RenderDrawRect(render,&r2);


    char affiche[100];

    SDL_Rect r={window_width*0.4,window_height*0.35,130,80};
    TTF_Font *font = NULL;
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 =  NULL;


    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    sprintf(affiche,"Ordinary wallet");
    texte = TTF_RenderText_Blended(font, affiche, color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    sprintf(affiche,"PEA");
    r.y=window_height*0.65;
    r.x=window_width*0.55;
    texte = TTF_RenderText_Blended(font, affiche, color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    sprintf(affiche,"Money");
    r.y=window_height*0.15;
    r.x=window_width*0.52;
    texte = TTF_RenderText_Blended(font, affiche, color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    for (int i=0;i<nb_player;i++)
    {
        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 35*f);
        TTF_SetFontStyle(font,TTF_STYLE_BOLD);
        r.y=0.05*window_height;
        sprintf(affiche,"Player %d ",joueurX[i].number+1);
        r.x = f*i*0.1*window_width+window_width*0.28;
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 =  SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);


        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 35*f*0.75);
        sprintf(affiche,"%ld$",joueurX[i].money);
        r.y = window_height*0.3;
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 =  SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);


        
        
        for (int j=0;j<2;j++)
        {
            sprintf(affiche, "Value %d$",joueurX[i].actions[j].total_value);
            r.y = window_height*0.3*j+window_height*0.5;
            texte = TTF_RenderText_Blended(font, affiche, color_text);
            texte2 =  SDL_CreateTextureFromSurface(render, texte);
            SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
            SDL_RenderCopy(render,texte2, NULL, &r);

            sprintf(affiche,"Length %d",joueurX[i].actions[j].length);
            r.y = window_height*0.3*j+window_height*0.6;
            texte = TTF_RenderText_Blended(font, affiche, color_text);
            texte2 =  SDL_CreateTextureFromSurface(render, texte);
            SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
            SDL_RenderCopy(render,texte2, NULL, &r);
        }
    }

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);


    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);
}


int choose_player_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit)
{

    window_card(wind,render,window_width,window_height);
    SDL_Rect r={window_width*0.35,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE PLAYER", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    int size,size1;


    if(nb_player > 5)
    {
        size=3;
    }
    else
    {
        size=2;
    }
    size1=size;

    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_Surface* image = SDL_LoadBMP("../assets/button.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width/4,0,window_width/size*0.75,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);


    r2.x = 0.75*window_width/size+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 5)
    {
        r2.x = 0.75*2*window_width/size+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    r2.y=window_height*0.55;
    r2.x=window_width/4;
    

    if(nb_player%2 == 1)
    {
        size1++;
        r2.w=window_width/size1*0.75;
    }

    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x = 0.75*window_width/size1+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 4)
    {
        r2.x = 2*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    if(nb_player==7)
    {
        r2.x = 3*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    button_info(wind,render,window_width,window_height);

    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
            *quit = 1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//player
                {
                    return 11;
                }
                if(y<2*window_height/3)//firms
                {
                    return 12;
                }
                else//game
                {
                    return 10;
                }
                
            }
            else
            {
                if(y<window_height*0.45)
                {
                    if(x < 0.75*window_width/size+window_width*0.25)
                        return 1;
                    if(nb_player>5)
                    {
                        if(x < 2*0.75*window_width/size+window_width*0.25)
                            return 2;
                        return 3;
                    }
                    return 2;
                }
                else
                {
                    if(nb_player < 6)
                    {
                        if(x < 0.75*window_width/size1+window_width*0.25)
                            return 3;
                        if(nb_player!=4)
                        {
                            if(x < 2*0.75*window_width/size1+window_width*0.25)
                                return 4;
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 5;
                            //info
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        else
                        {
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 4;
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        
                    }
                    else
                    {
                         if(x < 0.75*window_width/size1+window_width*0.25)
                            return 4;
                        if (x < 2*0.75*window_width/size1+window_width*0.25)
                        {
                            return 5;
                        }
                        if(nb_player==6)
                        {
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 6;
                            //info
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        else
                        {
                            if(x < 3*0.75*window_width/size1+window_width*0.25)
                                return 6;
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 7;
                            
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        
                    }
                    
                   
                }
                
            }
            

        }
    }
    return 0;
}


void button_info(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_Surface* image = SDL_LoadBMP("../assets/button3.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width*0.95,window_height*0.91,window_width/20,window_width/20};
    SDL_RenderCopy(render,monImage,NULL,&r2);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
}

void window_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Surface* image = NULL;
    SDL_Texture* monImage = NULL;
    SDL_Rect r2={0,0,window_width/4,window_height/3};
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button2.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button1.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=2*window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=0;
    r2.x=window_width/4;
    r2.h=window_height;
    r2.w=3*window_width/4;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);

    
}

void window_scan(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_RenderClear(render);
    window_card(wind,render,window_width,window_height);
    SDL_Rect r={window_width*0.4,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "SCAN YOU CARD", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    button_info(wind,render,window_width,window_height);

    SDL_RenderPresent(render);


    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}


int select_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit)
{
    
    return 0;
}

void play_cards(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit,list_entreprise * firms)
{
    int player=choose_player_card(wind,render,window_width,window_height,nb_player,quit);

    int scan=0,x,y;

    if(player < 8)
    {
        window_scan(wind,render,window_width,window_height);
        SDL_Event event;
        while (!*quit && !scan )
        {
            scan=select_card(wind,render,window_width,window_height,joueurX,nb_player,quit);
            SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
            switch (event.type)
            {
                case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;      // Returns mouse motion x.
                    y = event.motion.y;
                    if(x<window_width/4)
                    {
                        if(y<window_height/3)//player
                        {
                            info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return;
                        }
                        
                        if(y<2*window_height/3)//firms
                        {
                            
                            firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                            return;
                        }
                        else//game
                        {
                            return;
                        }
                        
                    }
                    else
                    {
                        if(x > window_width*0.95 && y >window_height*0.91)
                        {
                            info_card(wind,render,window_width,window_height,quit);
                            window_scan(wind,render,window_width,window_height);
                        }
                            
                    }
                    
                    break; 
            }
        }

    }
    else
    {
        switch (player)
        {
        case 10://game
            return;
        case 11:
            info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
            return;
        case 12:
            firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
            return;
        }
    }
}

int translate(char* s)
{
    int n=0;
    char* int_c="0123456789";
    for(int i=0;s[i]!='\0';i++)
    {
        for(int j=0;j<10;j++)
        {
            if(s[i]==int_c[j])
            {
                n=n*10+j;
            }
        }
    }
    return n;
}

void info_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int *quit)
{
    SDL_Rect r={window_width*0.5,0.05*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);  
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL ;
    SDL_RenderClear(render);
    char* s=qr();
    int n=translate(s);
    switch (n)
    {
    case 1:
        texte = TTF_RenderText_Blended(font, "Draw !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You got the right to draw", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "another card, your refusal", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "isn’t accepted. Do it.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 2:
        texte = TTF_RenderText_Blended(font, "Discard", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You must give up", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "on one of your cards.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        r.x=0.5*window_width;
        texte = TTF_RenderText_Blended(font, " Sorry.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
    
    case 3:
        texte = TTF_RenderText_Blended(font, "Steal!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You sneaky bastard, you can", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, " take a card of any other player,", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        r.x=0.4*window_width;
        texte = TTF_RenderText_Blended(font, "you got the choice.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 4:
        texte = TTF_RenderText_Blended(font, "Jackpot", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Little or big, a win is", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, " a win, it's the same with ", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "money you get X$", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
 
    case 5:
        texte = TTF_RenderText_Blended(font, "Scammed !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Are you sad? Today you", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "gotta pay hehehe X$.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "What are ya gonna do =D", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 6:
        texte = TTF_RenderText_Blended(font, "Hold-up !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Gime gime gime, u can", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "take the action of another", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "player without his permission!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 7:
        texte = TTF_RenderText_Blended(font, "Reverse Day !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Today is a weird day, if you win", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "money, you lose money, if you", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "lose money, you win money. Have Fun!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 8:
        texte = TTF_RenderText_Blended(font, "Freeze !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You can’t take any money", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "of your account anymore.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "At least for now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 9:
        texte = TTF_RenderText_Blended(font, "Negate Attack", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Use this card when someone use", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "a card effect to block", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "it and destroy his card.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 10:
        texte = TTF_RenderText_Blended(font, "Stonk !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project of the company in", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "question will get better", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "than it is right now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 11:
        texte = TTF_RenderText_Blended(font, "Not Stonk !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project of the company", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "in question will get worse", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "than it is right now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 12:
        texte = TTF_RenderText_Blended(font, "Liquidation", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You can take down", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "a company. A beautiful", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "One hit KO!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
 
    case 13:
        texte = TTF_RenderText_Blended(font, "Interestonk", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The interest of", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "this project will", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "rise a lot.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 14:
        texte = TTF_RenderText_Blended(font, "Not interestonk", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The interest of", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "this project will", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "fall a lot.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 15:
        texte = TTF_RenderText_Blended(font, "Go Vacation", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "you can go", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "go the Bahamas ", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "right now gtfo !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

        case 16:
        texte = TTF_RenderText_Blended(font, "Crunch", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "A wonderfull biscuit", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "cracks in your mouth,", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "irresistible taste !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 17:
        texte = TTF_RenderText_Blended(font, "Mission failed", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project in question", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "will become a failure", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 18:
        texte = TTF_RenderText_Blended(font, "Yes! We did it!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project in question", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "will become a success.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
    }


    SDL_RenderPresent(render);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    SDL_Event event;

    time_t t_launch,t_counter;

    t_launch=time(NULL);
    t_counter=time(NULL);

    while(!*quit && difftime(t_counter,t_launch) < 7)
    {
        t_counter=time(NULL);
        SDL_WaitEventTimeout(&event,3);
        switch (event.type)
        {
            case SDL_QUIT://on appuie sur la croix
                *quit = 1;
                break;
        }
    }
}


void info_player(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, Player* joueurX, int nb_player,int *quit,list_entreprise * firms)
{
    player_window(wind,render,window_width,window_height,joueurX,nb_player);

    SDL_RenderPresent(render);

    int x,y;

    SDL_Event event;


    while (!*quit )
        {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
            case SDL_QUIT://on appuie sur la croix
                *quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;      // Returns mouse motion x.
                y = event.motion.y;
                if(x<window_width/4)
                {
                    if(y<window_height/3)//card
                    {
                        play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                        return;
                    }
                    if(y<2*window_height/3)//firms
                    {
                        firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                        return;
                    }
                    else//game
                    {
                        return;
                    }
                    
                }
                
            break; 
        }
    }


}

void window_firm(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_RenderClear(render);
    SDL_Surface* image = NULL;
    SDL_Texture* monImage = NULL;
    SDL_Rect r2={0,0,window_width/4,window_height/3};

    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button1.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=2*window_height/3;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    image = SDL_LoadBMP("../assets/button2.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    r2.y=0;
    r2.x=window_width/4;
    r2.h=window_height;
    r2.w=3*window_width/4;


    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
}


void firm_screen(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms)
{
    int cpt=0,cpt2=0;
    char affiche[100];
    SDL_Surface* image = NULL;
    SDL_Texture* monImage = NULL;
    SDL_Rect r2={0,0,window_width/4,window_height/3};

    window_firm(wind,render,window_width,window_height);

    image = SDL_LoadBMP("../assets/button2.bmp");
    monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_SetRenderDrawColor(render,0,0,0,255);

    r2.h=window_height*0.4;
    r2.w=0.73*window_width/5;

    for(int i=0;i<10;i++)
    {
        if(i>4)
        {
            r2.y=0.55*window_height;
            if(cpt>4)
                cpt=0;
        }
        else
            r2.y=0.05*window_height;
        
        r2.x=window_width*0.27+cpt*0.7*window_width/5;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
        cpt++;
    }

    SDL_Rect r={window_width*0.3,0.05*window_height,150,30};
    TTF_Font *font = NULL;
    SDL_Color color_text = { 255, 255, 255 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL ;
    
    cpt=0;

    list_entreprise* temp=firms;
    while(temp!=NULL)
    {
        if(cpt2>4)
        {
            r.y=0.65*window_height;
            if(cpt>4)
                cpt=0;
        }
        else
            r.y=0.15*window_height;
        
        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 40);  
        TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
        texte = TTF_RenderText_Blended(font, temp->val->name, color_text);
        r.x=window_width*0.3+cpt*0.7*window_width/5;
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);


        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 35);
        if(cpt2>4)
        {
            r.y=0.75*window_height;
        }
        else
            r.y=0.25*window_height;
        texte = TTF_RenderText_Blended(font, "NB ACTIONS", color_text);
        r.x=window_width*0.28+cpt*0.72*window_width/5;
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);


        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 35);
        if(cpt2>4)
        {
            r.y=0.85*window_height;
        }
        else
            r.y=0.35*window_height;
        sprintf(affiche,"%d",temp->val->number_act);
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        r.x=window_width*0.33+cpt*0.72*window_width/5;
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        temp=temp->next;
        cpt++;
        cpt2++;
    }

    SDL_RenderPresent(render);
    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
}


void firm_project(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firm)
{
    window_firm(wind,render,window_width,window_height);
    
    SDL_Point* points=malloc((firm->val->turn)*sizeof(SDL_Point));
    for(int i=0;i<firm->val->turn;i++)
    {
        points[i].x=i*0.7*window_width/4+window_width*0.4;
        points[i].y=0.5*window_height-(firm->val->project_state[i])*150+300;
    }
    
    

    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    

    SDL_RenderDrawLines(render, points,firm->val->turn);

    for(int i=0;i<firm->val->turn;i++)
    {
        points[i].x=points[i].x+1;
        points[i].y=points[i].y+1;
    }

    SDL_RenderDrawLines(render, points,firm->val->turn);
    
    SDL_Rect r={window_width*0.6,0.05*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, firm->val->name, color_text);
    SDL_Texture *texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 30);

    r.x=window_width*0.26;
    r.y=0.5*window_height-(0)*150+300;
    texte = TTF_RenderText_Blended(font, "VERY BAD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=0.5*window_height-(1)*150+300;
    texte = TTF_RenderText_Blended(font, "BAD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=0.5*window_height-(2)*150+300;
    texte = TTF_RenderText_Blended(font, "OK", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=0.5*window_height-(3)*150+300;
    texte = TTF_RenderText_Blended(font, "GOOD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=0.5*window_height-(4)*150+300;
    texte = TTF_RenderText_Blended(font, "VERY GOOD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    r.x=window_width*0.38;
    r.y=window_height*0.5-350;
    r.w=window_width*0.6;
    r.h=window_height*0.8;
    SDL_RenderDrawRect(render,&r);


    SDL_Point p1={window_width*0.4,0.5*window_height-(4)*150+300},p2={window_width*0.4,0.5*window_height+300};
    SDL_RenderDrawLine(render,p1.x,p1.y,p2.x,p2.y);
    p1.y=window_height/2;
    p2.y=window_height/2;
    p2.x=3*0.7*window_width/(4)+window_width*0.4;
    SDL_RenderDrawLine(render,p1.x,p1.y,p2.x,p2.y);

    char affiche[2];

    r.y=window_height*0.51;

    for(int i=0;i<firm->val->turn;i++)
    {
        r.x=i*0.7*window_width/4+window_width*0.4;
        sprintf(affiche,"%d",i+1);
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

    }

    back_button(wind,render,window_width,window_height);

    SDL_RenderPresent(render);
    
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);
}


void back_button(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_Surface* image = SDL_LoadBMP("../assets/buttonback.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width*0.95,window_height*0.91,window_width/20,window_width/20};
    SDL_RenderCopy(render,monImage,NULL,&r2);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
}


void firm_info(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player)
{
    int click;
    SDL_Event event;
    int x,y;
    int firm_nb;
    list_entreprise* temp;

    while (!*quit)
    {
        firm_screen(wind,render,window_width,window_height,firms);
        click=0;

        while (!*quit && !click)
        {
            SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
            switch (event.type)
            {
                case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;      // Returns mouse motion x.
                    y = event.motion.y;
                    if(x < window_width*0.25)
                    {
                        if(y < window_height/3)
                        {
                            info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return;
                        }
                        if(y < 2*window_height/3)
                        {
                            play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return;
                        }
                        return;//game
                    }
                    if(y > window_height*0.05)
                    {
                        if(y < window_height*0.4+window_height*0.05)
                        {
                            if(x > window_width*0.27 && x < window_width*0.27+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=0;
                            }
                            if (x > window_width*0.27+0.7*window_width/5 && x < window_width*0.27+0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=1;
                            }
                            if (x > window_width*0.27+2*0.7*window_width/5 && x < window_width*0.27+2*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=2;
                            }
                            if (x > window_width*0.27+3*0.7*window_width/5 && x < window_width*0.27+3*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=3;
                            }
                            if (x > window_width*0.27+4*0.7*window_width/5 && x < window_width*0.27+4*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=4;
                            }
                        }
                        

                    
                        if(y > window_height*0.55 && y < window_height*0.4+window_height*0.55)
                        {
                            if(x > window_width*0.27 && x < window_width*0.27+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=5;
                            }
                            if (x > window_width*0.27+0.7*window_width/5 && x < window_width*0.27+0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=6;
                            }
                            if (x > window_width*0.27+2*0.7*window_width/5 && x < window_width*0.27+2*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=7;
                            }
                            if (x > window_width*0.27+3*0.7*window_width/5 && x < window_width*0.27+3*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=8;
                            }
                            if (x > window_width*0.27+4*0.7*window_width/5 && x < window_width*0.27+4*0.7*window_width/5+0.73*window_width/5)
                            {
                                click=1;
                                firm_nb=9;
                            }
                        }
                    }
                    break;
            }
        }

        temp=firms;
        for(int i=0;i<firm_nb;i++)
        {
            temp=temp->next;
        }

        firm_project(wind,render,window_width,window_height,temp);
        while (!*quit && click)
        {
            SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
            switch (event.type)
            {
                case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;      // Returns mouse motion x.
                    y = event.motion.y;
                    if(x < window_width*0.25)
                    {
                        if(y < window_height/3)
                        {
                            info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return;
                        }
                        if(y < 2*window_height/3)
                        {
                            play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return;
                        }
                        return;//game
                    }
                    if(x > window_width*0.95 && y>window_height*0.91)
                    {
                        click=0;
                    }
                    break;
            }
        }

    }
    
}


void window_spin(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,Player* joueurX,int nb_player, int player,char* turn)
{
    SDL_Rect r={window_width*0.4,0.5*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;
    char affiche[9];

    game_window(wind,render,window_width,window_height,turn);
    r.x=window_width*0.4;
    r.y=0.45*window_height;
    texte = TTF_RenderText_Blended(font, "SPIN THE WHEEL", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.x=window_width*0.525;
    r.y=0.6*window_height;
    texte=TTF_RenderText_Blended(font, "& CLICK", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    sprintf(affiche,"Joueur %d",joueurX[player].number+1);
    r.x=window_width*0.525;
    r.y=0.3*window_height;
    texte=TTF_RenderText_Blended(font, affiche, color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    SDL_RenderPresent(render);
}

int detect_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player,char* turn,int player)
{
    SDL_RenderClear(render);
    SDL_Rect r={window_width*0.3,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "Click on the result", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.x=0;
    r.y=0;
    r.w=window_width/3;
    r.h=window_height*0.45;
    SDL_SetRenderDrawColor(render,207,35,52,255);//red
    SDL_RenderFillRect(render,&r);
    
    r.x=window_width/3;
    SDL_SetRenderDrawColor(render,0,0,0,255);//black
    SDL_RenderFillRect(render,&r);

    r.x=2*window_width/3;
    SDL_SetRenderDrawColor(render,26,173,31,255);//green
    SDL_RenderFillRect(render,&r);

    r.y=window_height*0.55;

    r.x=0;
    SDL_SetRenderDrawColor(render,255, 223, 0,255);//yellow
    SDL_RenderFillRect(render,&r);
    
    r.x=window_width/3;
    SDL_SetRenderDrawColor(render,255,255,255,255);//white
    SDL_RenderFillRect(render,&r);

    r.x=2*window_width/3;
    SDL_SetRenderDrawColor(render,27,1,155,255);//blue
    SDL_RenderFillRect(render,&r);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    SDL_RenderPresent(render);

    SDL_Event event;
    int x,y;

    while(!*quit)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            *quit=1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(y< window_height*0.45)
            {
                if(x<window_width/3)//red
                {
                    if(joueurX[player].money>299)
                        joueurX[player].money-=300;
                    else
                        joueurX[player].money=0;
                    return 1;
                }
                if(x<2*window_width/3)//black
                {
                    if(joueurX[player].money>999)
                        joueurX[player].money-=1000;
                    else
                        joueurX[player].money=0;
                    return 2;
                }
                joueurX[player].money+=300;//green
                return 3;
            }
            if(y > window_height *0.55)
            {
                if(x<window_width/3)//yellow
                {
                    joueurX[player].money+=1000;
                    return 4;
                }
                if(x<2*window_width/3)//white
                {
                    return 5;
                }
                //blue
                return 6;
            }
        }
    }


    return 0;
}

void spin(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,list_entreprise* firms,int *quit,Player* joueurX,int nb_player,char* turn)
{

    

    SDL_Event event;
    int click,x,y;
    
    for(int i=0;i<nb_player;i++)
    {
        
        window_spin(wind,render,window_width,window_height,quit,joueurX,nb_player,i,turn);

        click=0;
        while (!*quit && !click)
        {
            SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
            switch (event.type)
            {
                case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;      // Returns mouse motion x.
                    y = event.motion.y;
                    if(x<window_width/4)
                    {
                        if(y < window_height/3)
                        {
                            play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            window_spin(wind,render,window_width,window_height,quit,joueurX,nb_player,i,turn);
                        }
                        else
                        {
                            if(y < 2*window_height/3)
                            {
                                firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                                window_spin(wind,render,window_width,window_height,quit,joueurX,nb_player,i,turn);
                            }
                            else
                            {
                                info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                                window_spin(wind,render,window_width,window_height,quit,joueurX,nb_player,i,turn);
                            }
                            
                        }
                        
                    }
                    else
                    {
                        click=1;
                    }
                    break;  
            }
        }
        
        int color=detect_wheel(wind,render,window_width,window_height,firms,quit,joueurX,nb_player,turn,i);
        switch (color)
        {
        case 0:
            return;
        case 1:
            red_wheel(wind,render,window_width,window_height,joueurX[i],*quit);
            break;
        case 2:
            black_wheel(wind,render,window_width,window_height,joueurX[i],*quit);
            break;
        case 3:
            green_wheel(wind,render,window_width,window_height,joueurX[i],*quit);
            break;
        case 4:
            yellow_wheel(wind,render,window_width,window_height,joueurX[i],*quit);
            break;
        case 5:
            white_wheel(wind,render,window_width,window_height,*quit);
            break;
        case 6:
            blue_wheel(wind,render,window_width,window_height,*quit);
            break;
        }
        
    }


}

void window_yellow_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 255, 223, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU JUST WON", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 150);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.385;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "1000$", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}

void window_black_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 255, 255, 255 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU JUST LOST", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 150);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.385;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "1000$", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}

void window_green_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 58, 137, 35, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 255, 255, 255 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU JUST EARN", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 150);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.395;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "300$", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}


void window_white_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU CAN DRAW", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 130);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.26;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "1 WHITE CARD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}

void window_blue_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 27, 1, 155, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 255, 255, 255 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU CAN DRAW", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 130);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.28;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "1 BLUE CARD", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}

void window_red_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height)
{
    SDL_SetRenderDrawColor(render, 165, 38, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    


    SDL_Rect r={window_width*0.3,0.3*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "YOU JUST LOST", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);



    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 150);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD); 
    r.x= window_width*0.395;
    r.y=0.5*window_height;
    texte = TTF_RenderText_Blended(font, "300$", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

}

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture * t){
    if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();
}

int window_announce(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player* joueurX,Entreprise entreprise,char* turn,int i,int* quit,list_entreprise* firms,int nb_player)
{
    game_window(wind,render,window_width,window_height,turn);

    char affiche[6];
    
    SDL_Rect r={window_width*0.4,0.2*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL;

    texte = TTF_RenderText_Blended(font, "Do annyone want to buy or sell", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.y=0.3*window_height;
    r.x=0.5*window_width;
    texte = TTF_RenderText_Blended(font, entreprise.name, color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.x=0.6*window_width;
    sprintf(affiche,"%d/%d",i+1,entreprise.number_act);
    texte = TTF_RenderText_Blended(font, affiche, color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    r.x=0.45*window_width;
    r.y=0.6*window_height;
    texte = TTF_RenderText_Blended(font, "YES", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderDrawRect(render,&r);

    font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    r.x=0.75*window_width;
    r.y=0.6*window_height;
    texte = TTF_RenderText_Blended(font, "NO", color_text);
    texte2 = SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderDrawRect(render,&r);


    SDL_Event event;
    int x,y,h,w;
    h=r.h;
    w=r.w;
    SDL_RenderPresent(render);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    while (!*quit )
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
            case SDL_QUIT://on appuie sur la croix
                *quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;      // Returns mouse motion x.
                y = event.motion.y;
                if(x<window_width/4)
                {
                    if(y < window_height/3)
                    {
                        play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                        return window_announce(wind,render,window_width,window_height,joueurX,entreprise,turn,i,quit,firms,nb_player);
                    }
                    else
                    {
                        if(y < 2*window_height/3)
                        {
                            firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                            return window_announce(wind,render,window_width,window_height,joueurX,entreprise,turn,i,quit,firms,nb_player);
                        }
                        else
                        {
                            info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                            return window_announce(wind,render,window_width,window_height,joueurX,entreprise,turn,i,quit,firms,nb_player);
                        }
                        
                    }
                    
                }
                else
                {
                    if(y > 0.6*window_height && y<0.6*window_height+h)
                    {
                        if(x > 0.45*window_width && x < 0.45*window_width+w)
                            return 1;
                        if(x > 0.75*window_width && x < 0.75*window_width+w)
                            return 0;
                    }
                }
                break;
        }
    }
    return 0;


    

}

int select_buyer(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms)
{
    game_window(wind,render,window_width,window_height,turn);
    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_Rect r={window_width*0.35,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE BUYER", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    int size,size1;


    if(nb_player > 5)
    {
        size=3;
    }
    else
    {
        size=2;
    }
    size1=size;

    SDL_Surface* image = SDL_LoadBMP("../assets/button1.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width/4,0,window_width/size*0.75,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);


    r2.x = 0.75*window_width/size+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 5)
    {
        r2.x = 0.75*2*window_width/size+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    r2.y=window_height*0.55;
    r2.x=window_width/4;
    

    if(nb_player%2 == 1)
    {
        size1++;
        r2.w=window_width/size1*0.75;
    }

    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x = 0.75*window_width/size1+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 4)
    {
        r2.x = 2*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    if(nb_player==7)
    {
        r2.x = 3*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }


    SDL_RenderPresent(render);
    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
            *quit = 1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//cards
                {
                    play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                if(y<2*window_height/3)//firms
                {
                    firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                else//player
                {
                    info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                
            }
            else
            {
                if(y<window_height*0.45)
                {
                    if(x < 0.75*window_width/size+window_width*0.25)
                        return 1;
                    if(nb_player>5)
                    {
                        if(x < 2*0.75*window_width/size+window_width*0.25)
                            return 2;
                        return 3;
                    }
                    return 2;
                }
                else
                {
                    if(nb_player < 6)
                    {
                        if(x < 0.75*window_width/size1+window_width*0.25)
                            return 3;
                        if(nb_player!=4)
                        {
                            if(x < 2*0.75*window_width/size1+window_width*0.25)
                                return 4;
                            
                            return 5;
                            
                        }
                        else
                        {
                            return 4;
                            
                        }
                        
                    }
                    else
                    {
                         if(x < 0.75*window_width/size1+window_width*0.25)
                            return 4;
                        if (x < 2*0.75*window_width/size1+window_width*0.25)
                        {
                            return 5;
                        }
                        if(nb_player==6)
                        {
                            return 6;

                        }
                        else
                        {
                            if(x < 3*0.75*window_width/size1+window_width*0.25)
                                return 6;
                            
                            return 7;
                            
                        }
                        
                    }
                    
                   
                }
                
            }
            

        }
    }
    return 0;
}

void amount_window(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int n,char* turn)
{
    game_window(wind,render,window_width,window_height,turn);
    SDL_Rect r={window_width*0.37,0.01*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "ENTER THE AMOUNT", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    char affiche[10];

    r.x=window_width*0.34;
    r.y=0.15*window_height;
    r.h=0.2*window_height;
    r.w=0.6*window_width;
    SDL_RenderFillRect(render,&r);
    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_RenderDrawRect(render,&r);

    int nb_size=0,n_cop=n;
    while(n_cop!=0)
    {
        nb_size++;
        n_cop/=10;
    }
    if(nb_size==0)
        nb_size=1;
    r.w=window_height*0.2*nb_size;
    r.x=window_width*0.94-r.w;
    
    sprintf(affiche,"%d$",n);
    texte = TTF_RenderText_Blended(font, affiche, color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_RenderCopy(render,texte2, NULL, &r);

    r.w=(window_width-window_width*0.25)/3;
    r.h=(window_height-window_height*0.35)/4;

    for(int i=0;i<3;i++)
    {
        sprintf(affiche,"%d",i+1);
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 =  SDL_CreateTextureFromSurface(render, texte);
        r.x=i*r.w+window_width*0.25;
        r.y=window_height*0.35;
        SDL_RenderCopy(render,texte2, NULL, &r);
        SDL_RenderDrawRect(render,&r);

        sprintf(affiche,"%d",i+4);
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 =  SDL_CreateTextureFromSurface(render, texte);
        r.x=i*r.w+window_width*0.25;
        r.y=r.h+window_height*0.35;
        SDL_RenderCopy(render,texte2, NULL, &r);
        SDL_RenderDrawRect(render,&r);

        sprintf(affiche,"%d",i+7);
        texte = TTF_RenderText_Blended(font, affiche, color_text);
        texte2 =  SDL_CreateTextureFromSurface(render, texte);
        r.x=i*r.w+window_width*0.25;
        r.y=2*r.h+window_height*0.35;
        SDL_RenderCopy(render,texte2, NULL, &r);
        SDL_RenderDrawRect(render,&r);

    }

    r.y=3*r.h+window_height*0.35;

    texte = TTF_RenderText_Blended(font, "SUPPR", color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    r.x=window_width*0.25;
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderDrawRect(render,&r);

    texte = TTF_RenderText_Blended(font, "0", color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    r.x=r.w+window_width*0.25;
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderDrawRect(render,&r);

    texte = TTF_RenderText_Blended(font, "ENTER", color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    r.x=2*r.w+window_width*0.25;
    SDL_RenderCopy(render,texte2, NULL, &r);
    SDL_RenderDrawRect(render,&r);

    SDL_RenderPresent(render);
    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);
}

int select_amount(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int player)
{
    int n=0;
    int click=0;
    int nw=1;

    int x,y;

    SDL_Event event;

    while(!*quit && !click)
    {
        if(nw)
        {
            amount_window(wind,render,window_width,window_height,n,turn);
            nw=0;
        }
        SDL_WaitEventTimeout(&event,30000000);
        switch(event.type)
        {
            case SDL_QUIT:
                *quit=1;
                return 0;
            case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//cards
                {
                    play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    nw=1;
                    break;
                }
                if(y<2*window_height/3)//firms
                {
                    firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                    nw=1;
                    break;
                }
                else//player
                {
                    info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    nw=1;
                    break;
                }
                
            }
            else
            {
                if(y > window_height*0.35)
                {
                    if(y < (window_height-window_height*0.35)/4+window_height*0.35)
                    {
                        if(x < (window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+1;
                            nw=1;
                            break;
                        }
                        if(x < 2*(window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+2;
                            nw=1;
                            break;
                        }
                        else
                        {
                            n=n*10+3;
                            nw=1;
                            break;
                        }
                        
                    }
                    if(y < 2*(window_height-window_height*0.35)/4+window_height*0.35)
                    {
                        if(x < (window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+4;
                            nw=1;
                            break;
                        }
                        if(x < 2*(window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+5;
                            nw=1;
                            break;
                        }
                        else
                        {
                            n=n*10+6;
                            nw=1;
                            break;
                        }
                        
                    }
                    if(y < 3*(window_height-window_height*0.35)/4+window_height*0.35)
                    {
                        if(x < (window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+7;
                            nw=1;
                            break;
                        }
                        if(x < 2*(window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+8;
                            nw=1;
                            break;
                        }
                        else
                        {
                            n=n*10+9;
                            nw=1;
                            break;
                        }
                        
                    }
                    else
                    {
                        if(x < (window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n/10;
                            nw=1;
                            break;
                        }
                        if(x < 2*(window_width-window_width*0.25)/3 + window_width*0.24)
                        {
                            n=n*10+0;
                            nw=1;
                            break;
                        }
                        else
                        {
                            click=1;
                            break;
                        }
                        
                    }
                }
            }
            break;
        }
        if(n > joueurX[player].money)
        {
            n=joueurX[player].money;
        }
    }
    return n;
    
    



}

int select_wallet(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int nb)
{
    game_window(wind,render,window_width,window_height,turn);

    SDL_Rect r={window_width*0.25,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 75);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE YOUR WALLET", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    
    SDL_SetRenderDrawColor(render,0,0,0,255);

    SDL_Surface* image = SDL_LoadBMP("../assets/button1.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width*0.25,0,0.75*window_width,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.y=window_height*0.55;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;

    SDL_Event event;

    

    while(!*quit)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *quit=1;
                return 0;
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;      // Returns mouse motion x.
                y = event.motion.y;
                if(x<window_width/4)
                {
                    if(y<window_height/3)//cards
                    {
                        play_cards(wind,render,window_width,window_height,joueurX,nb,quit,firms);
                        return select_wallet(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb);
                    }
                    if(y<2*window_height/3)//firms
                    {
                        firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb);
                        return select_wallet(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb);
                    }
                    else//player
                    {
                        info_player(wind,render,window_width,window_height,joueurX,nb,quit,firms);
                        return select_wallet(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb);
                    }
                
                }
                else
                {
                    if(y < window_height*0.45)
                        return 0;
                    if(y > window_height*0.55)
                        return 1;
                }
                break;
        }
    }
    return 0;
}

void window_locked(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,char* turn, Player* joueurX,list_entreprise* firms,int nb,time_t t_launch,time_t t_counter)
{
    game_window(wind,render,window_width,window_height,turn);

    SDL_Rect r={window_width*0.3,0.4*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 75);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "THIS ACTION", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    
    r.y=0.6*window_height;
    texte = TTF_RenderText_Blended(font, "IS LOCKED", color_text);
    texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);
    

    SDL_RenderPresent(render);



    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;


    t_launch=time(NULL);
    t_counter=time(NULL);

    SDL_Event event;

    while(!*quit && difftime(t_counter,t_launch) < 3)
    {
        t_counter=time(NULL);
        SDL_WaitEventTimeout(&event,0);
        switch(event.type)
        {
            case SDL_QUIT:
                *quit=1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;      // Returns mouse motion x.
                y = event.motion.y;
                if(x<window_width/4)
                {
                    if(y<window_height/3)//cards
                    {
                        play_cards(wind,render,window_width,window_height,joueurX,nb,quit,firms);
                        window_locked(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb,time(NULL),t_counter);
                        break;
                        
                    }
                    if(y<2*window_height/3)//firms
                    {
                        firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb);
                        window_locked(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb,time(NULL),t_counter);
                        break;
                    }
                    else//player
                    {
                        info_player(wind,render,window_width,window_height,joueurX,nb,quit,firms);
                        window_locked(wind,render,window_width,window_height,quit,turn,joueurX,firms,nb,time(NULL),t_counter);
                        break;
                    }
                
                }
        }
    }
}

int select_seller(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,char* turn, Player* joueurX,list_entreprise* firms)
{
    game_window(wind,render,window_width,window_height,turn);
    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_Rect r={window_width*0.35,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE SELLER", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    int size,size1;


    if(nb_player > 5)
    {
        size=3;
    }
    else
    {
        size=2;
    }
    size1=size;

    SDL_Surface* image = SDL_LoadBMP("../assets/button1.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width/4,0,window_width/size*0.75,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);


    r2.x = 0.75*window_width/size+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 5)
    {
        r2.x = 0.75*2*window_width/size+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    r2.y=window_height*0.55;
    r2.x=window_width/4;
    

    if(nb_player%2 == 1)
    {
        size1++;
        r2.w=window_width/size1*0.75;
    }

    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x = 0.75*window_width/size1+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 4)
    {
        r2.x = 2*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    if(nb_player==7)
    {
        r2.x = 3*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }


    SDL_RenderPresent(render);
    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
            *quit = 1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//cards
                {
                    play_cards(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                if(y<2*window_height/3)//firms
                {
                    firm_info(wind,render,window_width,window_height,firms,quit,joueurX,nb_player);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                else//player
                {
                    info_player(wind,render,window_width,window_height,joueurX,nb_player,quit,firms);
                    return(select_buyer(wind,render,window_width,window_height,nb_player,quit,turn,joueurX,firms));
                }
                
            }
            else
            {
                if(y<window_height*0.45)
                {
                    if(x < 0.75*window_width/size+window_width*0.25)
                        return 1;
                    if(nb_player>5)
                    {
                        if(x < 2*0.75*window_width/size+window_width*0.25)
                            return 2;
                        return 3;
                    }
                    return 2;
                }
                else
                {
                    if(nb_player < 6)
                    {
                        if(x < 0.75*window_width/size1+window_width*0.25)
                            return 3;
                        if(nb_player!=4)
                        {
                            if(x < 2*0.75*window_width/size1+window_width*0.25)
                                return 4;
                            
                            return 5;
                            
                        }
                        else
                        {
                            return 4;
                            
                        }
                        
                    }
                    else
                    {
                         if(x < 0.75*window_width/size1+window_width*0.25)
                            return 4;
                        if (x < 2*0.75*window_width/size1+window_width*0.25)
                        {
                            return 5;
                        }
                        if(nb_player==6)
                        {
                            return 6;

                        }
                        else
                        {
                            if(x < 3*0.75*window_width/size1+window_width*0.25)
                                return 6;
                            
                            return 7;
                            
                        }
                        
                    }
                    
                   
                }
                
            }
            

        }
    }
    return 0;
}


void play_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int *quit,Player* joueurX, int player,int nb_player,list_entreprise* firms)
{
    int target;
    SDL_Rect r={window_width*0.5,0.05*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);  
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);  
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = NULL;
    SDL_Texture *texte2 = NULL ;

    SDL_Event event;

    time_t t_launch,t_counter;

    SDL_RenderClear(render);
    char* s=qr();
    int n=translate(s);
    switch (n)
    {
    case 1:
        texte = TTF_RenderText_Blended(font, "Draw !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You got the right to draw", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "another card, your refusal", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "isn’t accepted. Do it.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 2:
        texte = TTF_RenderText_Blended(font, "Discard", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You must give up", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "on one of your cards.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        r.x=0.5*window_width;
        texte = TTF_RenderText_Blended(font, " Sorry.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
    
    case 3:
        texte = TTF_RenderText_Blended(font, "Steal!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You sneaky bastard, you can", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, " take a card of any other player,", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        r.x=0.4*window_width;
        texte = TTF_RenderText_Blended(font, "you got the choice.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 4:
        texte = TTF_RenderText_Blended(font, "Jackpot", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Little or big, a win is", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, " a win, it's the same with ", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "money you get 500$", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        if(joueurX[player].money<0 && joueurX[player].money>=-500)
            joueurX[player].money=0;
        else
            joueurX[player].money+=500;
        break;
 
    case 5:
        texte = TTF_RenderText_Blended(font, "Scammed !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Are you sad? Today you", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "gotta pay hehehe 500$.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "What are ya gonna do =D", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        
        if(joueurX[player].money>0 && joueurX[player].money<=500)
            joueurX[player].money=0;
        else
            joueurX[player].money-=500;
        break;

    case 6:
        texte = TTF_RenderText_Blended(font, "Hold-up !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Gime gime gime, u can", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "take the action of another", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "player without his permission!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        SDL_RenderPresent(render);

        t_launch=time(NULL);
        t_counter=time(NULL);

        while(!*quit && difftime(t_counter,t_launch) < 7)
        {
            t_counter=time(NULL);
            SDL_WaitEventTimeout(&event,3);
            switch (event.type)
            {
                case SDL_QUIT://on appuie sur la croix
                    *quit = 1;
                    break;
            }
        }

        do
        {
            target=choose_target_card(wind,render,window_width,window_height,nb_player,quit);
        } while (target == player);
        
        int f=select_firm(wind,render,window_width,window_height,nb_player,quit,joueurX,firms);
        list_entreprise* temp=firms;
        for(int i=0;i<f;i++)
        {
            temp=temp->next;
        }
        int p=find_act(target,(*temp->val));

        if(p!=temp->val->number_act)
        {
            int p2=select_wallet(wind,render,window_width,window_height,quit,"1",joueurX,firms,nb_player);

            transfer_act(&(joueurX[target].actions[p]),&(joueurX[target].actions[p2]),&(temp->val->actions[p]));
            SDL_RenderClear(render);
            texte = TTF_RenderText_Blended(font, "MISSION SUCCESS", color_text);
            texte2 = SDL_CreateTextureFromSurface(render, texte);
            SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
            SDL_RenderCopy(render,texte2, NULL, &r);
        }
        else
        {
            SDL_RenderClear(render);
            texte = TTF_RenderText_Blended(font, "MISSION FAILED", color_text);
            texte2 = SDL_CreateTextureFromSurface(render, texte);
            SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
            SDL_RenderCopy(render,texte2, NULL, &r);
        }
        
        

        break;

    case 7:
        texte = TTF_RenderText_Blended(font, "Reverse Day !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Today is a weird day, if you win", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "money, you lose money, if you", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "lose money, you win money. Have Fun!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        for(int i=0;i<nb_player;i++)
        {
            joueurX[i].money=-joueurX[i].money;
        }
        break;

    case 8:
        texte = TTF_RenderText_Blended(font, "Freeze !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You can’t take any money", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "of your account anymore.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "At least for now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        joueurX[player].freeze=1;
        break;

    case 9:
        texte = TTF_RenderText_Blended(font, "Negate Attack", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "Use this card when someone use", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "a card effect to block", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "it and destroy his card.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 10:
        texte = TTF_RenderText_Blended(font, "Stonk !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project of the company in", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "question will get better", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "than it is right now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 11:
        texte = TTF_RenderText_Blended(font, "Not Stonk !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project of the company", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "in question will get worse", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "than it is right now.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 12:
        texte = TTF_RenderText_Blended(font, "Liquidation", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "You can take down", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "a company. A beautiful", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "One hit KO!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
 
    case 13:
        texte = TTF_RenderText_Blended(font, "Interestonk", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The interest of", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "this project will", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "rise a lot.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 14:
        texte = TTF_RenderText_Blended(font, "Not interestonk", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The interest of", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "this project will", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "fall a lot.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 15:
        texte = TTF_RenderText_Blended(font, "Go Vacation", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "you can go", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "go the Bahamas ", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "right now gtfo !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

        case 16:
        texte = TTF_RenderText_Blended(font, "Crunch", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "A wonderfull biscuit", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "cracks in your mouth,", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.6;
        texte = TTF_RenderText_Blended(font, "irresistible taste !", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 17:
        texte = TTF_RenderText_Blended(font, "Mission failed", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project in question", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "will become a failure", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;

    case 18:
        texte = TTF_RenderText_Blended(font, "Yes! We did it!", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 60);  
        r.y=window_height*0.4;
        r.x=0.35*window_width;
        texte = TTF_RenderText_Blended(font, "The project in question", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);

        r.y=window_height*0.5;
        texte = TTF_RenderText_Blended(font, "will become a success.", color_text);
        texte2 = SDL_CreateTextureFromSurface(render, texte);
        SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
        SDL_RenderCopy(render,texte2, NULL, &r);
        break;
    }


    SDL_RenderPresent(render);

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    

    t_launch=time(NULL);
    t_counter=time(NULL);

    while(!*quit && difftime(t_counter,t_launch) < 7)
    {
        t_counter=time(NULL);
        SDL_WaitEventTimeout(&event,3);
        switch (event.type)
        {
            case SDL_QUIT://on appuie sur la croix
                *quit = 1;
                break;
        }
    }
}

void reverse_day(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit,Player* players)
{
    for(int i=0;i<nb_player;i++)
    {
        if(players[i].money<0)
        {
            players[i].money=-players[i].money;
        }
    }
}

int choose_target_card(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit)
{

    window_card(wind,render,window_width,window_height);
    SDL_Rect r={window_width*0.35,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE TARGET", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);

    int size,size1;


    if(nb_player > 5)
    {
        size=3;
    }
    else
    {
        size=2;
    }
    size1=size;

    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_Surface* image = SDL_LoadBMP("../assets/button.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width/4,0,window_width/size*0.75,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);


    r2.x = 0.75*window_width/size+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 5)
    {
        r2.x = 0.75*2*window_width/size+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    r2.y=window_height*0.55;
    r2.x=window_width/4;
    

    if(nb_player%2 == 1)
    {
        size1++;
        r2.w=window_width/size1*0.75;
    }

    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x = 0.75*window_width/size1+window_width*0.25;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    if(nb_player > 4)
    {
        r2.x = 2*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    if(nb_player==7)
    {
        r2.x = 3*0.75*window_width/size1+window_width*0.25;
        SDL_RenderCopy(render,monImage,NULL,&r2);
        SDL_RenderDrawRect(render,&r2);
    }

    button_info(wind,render,window_width,window_height);

    SDL_RenderPresent(render);

    SDL_SetRenderDrawColor(render,255,255,255,255);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(monImage);
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texte2);
    TTF_CloseFont(font);

    int x,y;

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
            *quit = 1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//player
                {
                    return 11;
                }
                if(y<2*window_height/3)//firms
                {
                    return 12;
                }
                else//game
                {
                    return 10;
                }
                
            }
            else
            {
                if(y<window_height*0.45)
                {
                    if(x < 0.75*window_width/size+window_width*0.25)
                        return 1;
                    if(nb_player>5)
                    {
                        if(x < 2*0.75*window_width/size+window_width*0.25)
                            return 2;
                        return 3;
                    }
                    return 2;
                }
                else
                {
                    if(nb_player < 6)
                    {
                        if(x < 0.75*window_width/size1+window_width*0.25)
                            return 3;
                        if(nb_player!=4)
                        {
                            if(x < 2*0.75*window_width/size1+window_width*0.25)
                                return 4;
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 5;
                            //info
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        else
                        {
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 4;
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        
                    }
                    else
                    {
                         if(x < 0.75*window_width/size1+window_width*0.25)
                            return 4;
                        if (x < 2*0.75*window_width/size1+window_width*0.25)
                        {
                            return 5;
                        }
                        if(nb_player==6)
                        {
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 6;
                            //info
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        else
                        {
                            if(x < 3*0.75*window_width/size1+window_width*0.25)
                                return 6;
                            if(x < window_width*0.95 && y < window_height*0.91)
                                return 7;
                            
                            window_scan(wind,render,window_width,window_height);
                            info_card(wind,render,window_width,window_height,quit);
                            return choose_player_card(wind,render,window_width,window_height,nb_player,quit);
                        }
                        
                    }
                    
                   
                }
                
            }
            

        }
    }
    return 0;
}



int select_firm(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height, int nb_player,int *quit, Player* joueurX,list_entreprise* firms)
{
    window_card(wind,render,window_width,window_height);
    SDL_SetRenderDrawColor(render,0,0,0,255);
    SDL_Rect r={window_width*0.35,0.45*window_height,150,30};
    TTF_Font *font = TTF_OpenFont("../assets/font/ComicNeue-Light.ttf", 100);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    SDL_Color color_text = { 0, 0, 0 };
    SDL_Surface *texte = TTF_RenderText_Blended(font, "CHOOSE THE FIRM", color_text);
    SDL_Texture *texte2 =  SDL_CreateTextureFromSurface(render, texte);
    SDL_QueryTexture(texte2, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(render,texte2, NULL, &r);


    SDL_Surface* image = SDL_LoadBMP("../assets/button1.bmp");
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(render,image);
    SDL_Rect r2={window_width/4,0,0.75*window_width/5,window_height*0.45};
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+2*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+3*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+4*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.y=0.55*window_height;
    r2.x=window_width/4;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+2*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+3*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    r2.x=window_width/4+4*0.75*window_width/5;
    SDL_RenderCopy(render,monImage,NULL,&r2);
    SDL_RenderDrawRect(render,&r2);

    SDL_RenderPresent(render);

    int x,y;

    SDL_Event event;
    while (!*quit)
    {
        SDL_WaitEvent(&event);//mise en attente d'un événement de la fenêtre
        switch (event.type)
        {
        case SDL_QUIT://on appuie sur la croix
            *quit = 1;
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;      // Returns mouse motion x.
            y = event.motion.y;
            if(x<window_width/4)
            {
                if(y<window_height/3)//player
                {
                    return 11;
                }
                if(y<2*window_height/3)//firms
                {
                    return 12;
                }
                else//game
                {
                    return 10;
                }
                
            }
            else
            {
                if(y < 0.45*window_height)
                {
                    if(x<window_width/4+0.75*window_width/5)
                        return 0;
                    if(x<window_width/4+2*0.75*window_width/5)
                        return 1;
                    if(x<window_width/4+3*0.75*window_width/5)
                        return 2;
                    if(x<window_width/4+4*0.75*window_width/5)
                        return 3;
                  return 4;
                }
                if(y > 0.55*window_height)
                {
                    if(x<window_width/4+0.75*window_width/5)
                        return 5;
                    if(x<window_width/4+2*0.75*window_width/5)
                        return 6;
                    if(x<window_width/4+3*0.75*window_width/5)
                        return 7;
                    if(x<window_width/4+4*0.75*window_width/5)
                        return 8;
                  return 9;
                }
            }
            break;
        }
    }
    return 0;

}