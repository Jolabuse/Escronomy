#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include "base.h"
#include "window.h"
#include <time.h>



void PEA(Player* players, int nb)// set PEA
{
    for (int i=0;i<nb;i++)
    {
        players[i].actions[1].locked=0;//unlock them
    }
}

void project_evolution(list_entreprise** firms)//set the evolution of the projects
{
    int random;
    if(*firms!=NULL)
    {
        random=rand()%3;// we take a random
        if((*firms)->val->turn==0)//if it's the first turn of this action you set it with 1,2,3
        {
            (*firms)->val->project_state[(*firms)->val->turn]=random+1;
        }
        else
        {
            (*firms)->val->project_state[(*firms)->val->turn]=(*firms)->val->project_state[((*firms)->val->turn)-1]+(random-1);
        }//we do -1,0,+1
        project_evolution(&((*firms)->next));// for each firm
    }
}

int project_stagne(Entreprise* firm)
{
    if(firm->turn<2)
        return 0;
    else
    {
        if((firm->project_state[(firm->turn)-1]<=1 && firm->project_state[(firm->turn)]<=1) || (firm->project_state[(firm->turn)-1]>=3 && firm->project_state[(firm->turn)]>=3))
            return 1;
    }
    return 0;
}

int new_project(Entreprise* firm)
{
    int r=0;
    if(firm->turn>0)
    {
        if(firm->project_state[firm->turn]==0 || firm->project_state[firm->turn]==4 || firm->turn>3 || project_stagne(firm)==1)
        {
            if (firm->project_state[firm->turn]>2 || firm->turn>3)
            {
                r=2;
            }
            for(int i=0;i<firm->turn;i++)
            {
                firm->project_state[i]=6;
            }
            firm->turn=0;
            if (firm->turn>2)
                    printf("hi %s\n",firm->name);
            if(r==0)
                r=1;
        }
    }
    return r;
}

void project_action(list_entreprise* firms,Player* players, int nb)
{
    int r_np;
    list_entreprise* temp=firms;
    while(temp!=NULL)
    {
        r_np=new_project(temp->val);
        switch (r_np)
        {
        case 1:
            for(int i=0;i<temp->val->number_act;i++)
            {
                if(temp->val->actions[i].type==0)
                    temp->val->actions[i].value=temp->val->actions[i].value/2;
            }
            break;
        case 2:
            temp->val->number_act++;
            temp->val->actions[temp->val->number_act-1].type=0;
            temp->val->actions[temp->val->number_act-1].durability=0;
            temp->val->actions[temp->val->number_act-1].firm=temp->val->number;
            temp->val->actions[temp->val->number_act-1].interest=0;
            temp->val->actions[temp->val->number_act-1].value=temp->val->actions[temp->val->number_act-2].value;
            temp->val->actions[temp->val->number_act-1].owner.player=nb;
            temp->val->actions[temp->val->number_act-1].owner.portefeuille=2;
            break;
        default:
            temp->val->turn++;
        }
        temp=temp->next;
    }
}

void decrease_number_firm(list_entreprise** firms,int deleted)
{
    list_entreprise* temp=*firms;
    while(temp!=NULL)
    {
        if(temp->val->number>deleted)
        {
            temp->val->number--;
        }
        temp=temp->next;
    }
}

void delete_entreprise(list_entreprise* l,Entreprise* e)
{
    list_entreprise* temp=l;
    list_entreprise* memory;
    if (temp!=NULL)
    {
        if(temp->val->number!=e->number)
        {
            while(temp->next!=NULL && temp->next->val->number!=e->number)
            {
                temp=temp->next;
            }
            if (temp->next!=NULL)
            {
                memory=temp->next;
                temp->next=temp->next->next;

            }
        }
        else
        {
            memory=l;
            l=l->next;
        }
        l->length--;
        free(memory->val->actions);
        free(memory->val->name);
        free(memory->val->project_state);
        free(memory->val);
        free(memory);
    }
}



void crash_5(list_entreprise** firms,Player* players,int nb)
{
    list_act_obl* temp2;
    int random=rand()%(*firms)->length;
    list_entreprise* temp=(*firms);
    for (int i=0;i<random;i++)
        temp=temp->next;
    for (int i=0;i<nb;i++)
    {
        for (int j=0;j<2;j++)
        {
            if (players[i].actions[j].content!=NULL)
            {
                while(players[i].actions[j].content->val->firm==random)
                {
                    players[i].actions[j].length--;
                    players[i].actions[j].total_value=players[i].actions[j].total_value-players[i].actions[j].content->val->value;
                    players[i].actions[j].content=players[i].actions[j].content->next;
                }
                temp2=players[i].actions[j].content->next;
                while (temp2!=NULL)
                {
                    if(temp2->next!=NULL)
                    {
                       if (temp2->next->val->firm==random)
                        {
                            players[i].actions[j].length--;
                            players[i].actions[j].total_value=players[i].actions[j].total_value-temp2->val->value;
                            temp2->next=temp2->next->next;
                        }
                    }
                    temp2=temp2->next;

                }
            }
        }

    }
    printf("\nThe firm %s just crashed and burn\n\n",temp->val->name);
    delete_entreprise(*firms,temp->val);
    decrease_number_firm(firms,random);

}

long add_value(list_act_obl* l)
{
    if (l!=NULL)
        return l->val->value+add_value(l->next);
    return 0;
}

long value(Portefeuille p)
{
    return add_value(p.content);
}

void taxes(Player* joueurX,int nb)
{
    for (int i=0;i<nb;i++)
    {
        joueurX[i].actions[0].total_value = joueurX[i].actions[0].total_value - (3/100)*joueurX[i].actions[0].total_value;
    }
}

void remove_list_act_obl(Portefeuille* p,Act_obl* a)
{
    list_act_obl* temp=p->content;
    list_act_obl* memory;
    if (temp!=NULL)
    {
        if(temp->val->firm!=a->firm && temp->val->type!=a->type)
        {
            while(temp->next!=NULL && (temp->next->val->firm!=a->firm || temp->next->val->type!=a->type))
            {
                temp=temp->next;
            }
            if (temp->next!=NULL)
            {
                memory=temp->next;
                temp->next=temp->next->next;
            }
        }
        else
        {
            memory=p->content;
            p->content=p->content->next;
        }
        free(memory);
    }
}

void interest(Player* joueurX, int nj)
{
    int i,tot=0;
    for (i=0; i<nj; i++)
    {
        list_act_obl* temp = joueurX[i].actions[0].content;
        while (temp != NULL){
            if (temp->val->type == 1)
            {
                if(temp->val->durability>0)
                    tot = tot + temp->val->interest;
                else
                {
                    joueurX[temp->val->owner.player].actions[0].length--;
                    joueurX[temp->val->owner.player].actions[0].total_value=joueurX[temp->val->owner.player].actions[0].total_value-temp->val->value;
                    remove_list_act_obl(&joueurX[temp->val->owner.player].actions[0],temp->val);
                }
            }
            temp = temp->next;
        }
         joueurX[i].money+=tot;
    }
}

void Dividende(Player* joueurx,list_entreprise* l)
{
    list_entreprise* listdesentreprises=l;
    int petitdividende = 42;
    while(listdesentreprises!=NULL){
        for(int j=0;j<listdesentreprises->val->number_act;j++)
        {
            if (listdesentreprises->val->project_state[l->val->turn]>2)
            {
                if (listdesentreprises->val->project_state[l->val->turn]==4)
                {
                    if(listdesentreprises->val->actions[j].type==0)
                        joueurx[listdesentreprises->val->actions[j].owner.player].actions[listdesentreprises->val->actions[j].owner.portefeuille].total_value += 2*petitdividende;
                }
                else
                {
                    if(listdesentreprises->val->actions[j].type==0)
                        joueurx[listdesentreprises->val->actions[j].owner.player].actions[listdesentreprises->val->actions[j].owner.portefeuille].total_value += petitdividende;
                }
            }
        }
        listdesentreprises = listdesentreprises->next;
    }
}


void MoneyFlow(Player* joueurx, Entreprise entreprise, int maxdeTune, int n1, int n2,int p1,int p2,int nb)
{
    if (n1 != nb && n2 != nb){                            //Jn1 Achete une action a jn2
        joueurx[n1].money -= maxdeTune;
        joueurx[n1].actions[p1].total_value += maxdeTune;
        joueurx[n1].actions[p1].length += 1;
        joueurx[n2].money += maxdeTune;
        joueurx[n2].actions[p2].total_value -= maxdeTune;
        joueurx[n2].actions[p2].length -= 1;
    }
    if (n1 != nb && n2 == nb){                            //Jn1 Achete une action
        joueurx[n1].money -= maxdeTune;
        joueurx[n1].actions[p1].total_value += maxdeTune;
        joueurx[n1].actions[p1].length += 1;
    }
}

int owner_act(Player* joueurx, Entreprise firm,int n1)
{
    for (int i=0;i<firm.number_act;i++)
    {
        if (firm.actions[i].owner.player==n1)
            return i;
    }
    return firm.number_act+1;
}

void modify_act(Entreprise* firm,int price)
{
    for (int i=0;i<firm->number_act;i++)
    {
        if(firm->actions[i].type==0)
        {
            firm->actions[i].value=price;
        }
    }
}

void add_end_obligation(list_act_obl** firms,list_act_obl* e)
{
    if(*firms == NULL)
        *firms=e;
    else
        add_end_obligation(&((*firms)->next),e);
}

void transfer_act(Portefeuille* p1,Portefeuille* p2,Act_obl* a)
{
    list_act_obl* temp=p1->content;
    list_act_obl* memory;
    if (temp!=NULL)
    {
        if(temp->val->firm!=a->firm && temp->val->type!=a->type)
        {
            while(temp->next!=NULL && (temp->next->val->firm!=a->firm || temp->next->val->type!=a->type))
            {
                temp=temp->next;
            }
            if (temp->next!=NULL)
            {
                memory=temp->next;
                temp->next=temp->next->next;
            }
        }
        else
        {
            memory=p1->content;
            p1->content=p1->content->next;
        }
        add_end_obligation(&p2->content,memory);
    }
}

void DeadPlayer(Player* Joueurx, int *nj,int nD)
{
    for(int i=nD; i<*nj-1; i++)
    {
        Joueurx[i+1].number=i;
        Joueurx[i]=Joueurx[i+1];
    }
    *nj -= 1;
}

void faillite(Player* joueurx,int* nb,int n1)
{
    list_act_obl* temp;
    for (int i=0;i<2;i++)
    {
        temp=joueurx[n1].actions[i].content;
        for(int j=0;j<joueurx[n1].actions[i].length;j++)
        {
            if (temp->val->type==0)
            {
                temp->val->owner.player=*nb;
                temp->val->owner.portefeuille=2;
            }
            else
            {
                remove_list_act_obl(&joueurx[n1].actions[i],temp->val);
            }
            temp=temp->next;
        }
    }
    DeadPlayer(joueurx,nb,n1);
}

int find_act(int n,Entreprise firm)
{
    for(int i=0;i<firm.number_act;i++)
    {
        if(firm.actions[i].owner.player==n)
            return i;
    }
    return firm.number_act;

}

void Achat(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player* joueurX,Entreprise entreprise,char* turn,int* quit,list_entreprise* firms,int* nb)
{
    int choice,n1,price,n2,p1,p2,find;
    for (int i=0;i<entreprise.number_act;i++)
    {
        choice=window_announce(wind,render,window_width,window_height,joueurX,entreprise,turn,i,quit,firms,*nb);
        if (choice == 0){
            return;
        }
        if (choice == 1){
            n1=select_buyer(wind,render,window_width,window_height,*nb,quit,turn,joueurX,firms);
            n1--;
            if(!joueurX[n1].freeze)
            {
                price=select_amount(wind,render,window_width,window_height,*nb,quit,turn,joueurX,firms,n1);
                n2=entreprise.actions[i].owner.player;
                p1=select_wallet(wind,render,window_width,window_height,quit,turn,joueurX,firms,*nb);
                do
                {
                    n2=select_seller(wind,render,window_width,window_height,*nb,quit,turn,joueurX,firms);
                    n2--;
                    if(n2==n1)
                        n2=*nb;
                    find=find_act(n2,entreprise);
                } while (find == entreprise.number_act);
                
                p2=entreprise.actions[find].owner.portefeuille;
                if(joueurX[n2].actions[p2].locked==0)
                {
                    MoneyFlow(joueurX, entreprise, price, n1, n2,p1,p2,*nb);
                    modify_act(&entreprise,price);
                    entreprise.actions[i].owner.portefeuille=p1;
                    entreprise.actions[i].owner.player=n1;
                    transfer_act(&joueurX[n1].actions[p1],&joueurX[n2].actions[p2],&entreprise.actions[i]);
                }
                else
                {
                    window_locked(wind,render,window_width,window_height,quit,turn,joueurX,firms,*nb,time(NULL),time(NULL));
                }
            }
        }
            
    }
}

void global_achat(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit,Player* joueurX,list_entreprise* firms,int* nb,char* turn)
{
    list_entreprise* temp=firms;
    while(temp!=NULL)
    {
        Achat(wind,render,window_width,window_height,joueurX,*(temp->val),turn,quit,firms,nb);
        temp=temp->next;
    }
    for(int i=0;i<*nb;i++)
    {
        //defreeze(joueurX,*nb);
        if(joueurX[i].money<=0)
            faillite(joueurX,nb,i);
    }
}

void add_end_firm(list_entreprise** firms,list_entreprise* e)
{
    if((*firms) == NULL)
    {
        (*firms)=e;
    }
    else
        add_end_firm(&((*firms)->next),e);
}

list_entreprise* new_e(int s,int i,char* nam,int nb)
{
    list_entreprise* e=malloc(sizeof(list_entreprise));
    e->val=malloc(sizeof(Entreprise));
    e->next=NULL;
    e->val->turn=0;
    e->val->secteur=s;
    e->val->number=i;
    e->val->name=nam;
    e->val->number_act=1;
    e->val->project_state=malloc(10*sizeof(int));
    e->val->actions=malloc(4*sizeof(Act_obl));
    e->val->actions[0].type=3;
    e->length=10;
    
    for(int j=0;j<e->val->number_act;j++)
    {
        e->val->actions[j].type=0;
        e->val->actions[j].value=300;
        e->val->actions[j].durability=0;
        e->val->actions[j].firm=i;
        e->val->actions[j].owner.player=nb;
        e->val->actions[j].owner.portefeuille=2;
        e->val->actions[j].interest=0;
    }
    return e;

}

void free_list_e(list_entreprise* e)
{
    if(e!=NULL)
    {
        free_list_e(e->next);
        free(e->val->actions);
        free(e->val->name);
        free(e->val->project_state);
        free(e->val);
    }
    free(e);
    
    
}

char* name_set(int i)
{
    switch (i)
    {
    case 0:
        return "Cora";
    case 1:
        return "Total";
    case 2:
        return "Citroen";
    case 3:
        return "Renault";
    case 4:
        return "Auchan";
    case 5:
        return "Signal";
    case 6:
        return "Maped";
    case 7:
        return "FDJ";
    case 8:
        return "Peugeot";
    case 9:
        return "Carrefour";
    case 10:
        return "Bic";
    }
    return "Prout";
}

int secteur(int i)
{
    if(i<2)
        return 0;
        else
        {
            if(i<5)
                return 1;
            else
            {
                if (i<7)
                {
                   return 2;
                }
                else
                    return 3;
            }
        }
}

void Disp_project(list_entreprise* listentreprise)
{
    list_entreprise* temp=listentreprise;
    while(temp!=NULL)
    {
        printf("Entreprise %s : %d\n", temp->val->name,temp->val->project_state[temp->val->turn]);
        temp=temp->next;
    }
}

void increment_turn(list_entreprise** firms)
{
    list_entreprise* temp=*firms;
    while(temp!=NULL)
    {
        temp->val->turn++;
        temp=temp->next;
    }
}

void disp_entreprise(list_entreprise* firms)
{
    list_entreprise* temp=firms;
    while(temp!=NULL)
    {
        printf("\nEntreprise %d : %s :\n-secteur : %d\n-number act : %d\n-turn : %d\n-project_state : %d\n",temp->val->number,temp->val->name,temp->val->secteur,temp->val->number_act,temp->val->turn,temp->val->project_state[temp->val->turn]);
        temp=temp->next;
    }
}

void disp_portefeuille(Portefeuille p)
{
    printf("\nPortefeuille %d:\n-Value : %d\n-Number of actions : %d\n",p.type,p.total_value,p.length);
}

void disp_player(Player* joueurX,int nb)
{
    for (int i=0;i<nb;i++)
    {
        printf("\nPlayer %d :\n-Money : %ld\n",joueurX[i].number+1,joueurX[i].money);
        for (int j=0;j<2;j++)
        {
            disp_portefeuille(joueurX[i].actions[j]);
        }
    }
}



void game(Player* joueurx,list_entreprise** firms,int* nb, SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int *quit)
{
    list_entreprise* e;
    char turn[2];
    for(int t=0;t<10;t++)
    {
        sprintf(turn,"%d",t);
        spin(wind,render,window_width, window_height, *firms, quit, joueurx,*nb,turn);
        if (t==4)
        {
            crash_5(firms,joueurx,*nb);
            e=new_e(secteur(10),9,name_set(10),*nb);
            add_end_firm(firms,e);
            PEA(joueurx,*nb);
        }
        global_achat(wind,render,window_width,window_height,quit,joueurx,*firms,nb,turn);
        project_evolution(firms);
        Dividende(joueurx,*firms);
        taxes(joueurx,*nb);
        interest(joueurx,*nb);
        project_action(*firms,joueurx,*nb);
        reverse_day(wind,render,window_width,window_height,nb,quit,joueurx);
    }
}


void red_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;

    if(joueur.money>300)
    {
        joueur.money-=300;
    }
    else
    {
        joueur.money=0;
    }
    window_red_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}


void black_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;

    if(joueur.money>1000)
    {
        joueur.money-=1000;
    }
    else
    {
        joueur.money=0;
    }
    window_black_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}

void green_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;

    
    joueur.money+=300;

    window_green_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}

void yellow_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,Player joueur,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;

    
    joueur.money+=1000;

    window_yellow_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}

void white_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;


    window_white_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}

void blue_wheel(SDL_Window * wind, SDL_Renderer *render,int window_width,int window_height,int quit)
{
    time_t t_launch,t_counter;
    SDL_Event event;


    window_blue_wheel(wind,render,window_width,window_height);
    t_launch=time(NULL);
    t_counter=time(NULL);

    while (difftime(t_counter,t_launch) < 3 && !quit)
    {
        SDL_WaitEventTimeout(&event,0);
        t_counter=time(NULL);
    }
    
}

int is_int(char c)
{
    char* s="1234567890";
    for(int i=0;i<10;i++)
    {
        if(c==s[i])
            return 1;
    }
    return 0;
}


char* qr()
{
    system("python qr.py");
    FILE* fic=fopen("qr.txt","r");
    char* str=malloc(2*sizeof(char));
    char c;
    for (int i = 0; i < 2; i++)
    {
        fscanf(fic,"%c",&c);
    }
    
    fscanf(fic,"%c",&str[0]);
    fscanf(fic,"%c",&c);
    if(is_int(c))
    {
        str=realloc(str,3*sizeof(char));
        str[1]=c;
        str[2]='\0';
        fclose(fic);
        return str;
    }
    str[1]='\0';
    fclose(fic);
    return str;
    
}

void defreeze(Player* joueurX,int nb_player)
{
    for(int i=0;i<nb_player;i++)
    {
        if(joueurX[i].freeze)
            joueurX[i].freeze=0;
    }
}

