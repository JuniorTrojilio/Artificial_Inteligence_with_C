#define MAX 100
#include <stdio.h>
#include<string.h>

//estrutura do banco de dados do vôo (db)
struct FL
{
    char from[20];
    char to[20];
    int distance;
    char skip; //Usado para restaurar
};

struct FL flight[MAX]; //Matriz da estrutura db

int f_pos = 0; //Numero de entradas no db do vôo
int find_pos = 0; //Indice para procura no db do vôo

int tos = 0; //topo da pilha

struct stack 
{
    char from[20];
    char to[20];
};

struct stack bt_stack[MAX]; //pilha para restaurar

int main(void){

    char from[20], to[20];
    setup();


    return 0;
}

void setup(){
    assert_flight("New York","Chicago",1000);
    assert_flight("Chicago","Denver",1000);
    assert_flight("New York","Toronto",800);
    assert_flight("New York","Denver",1900);
    assert_flight("Toronto","Calgary",1500);
    assert_flight("Toronto","Los Angeles",1800);
    assert_flight("Toronto","Chicago",500);
    assert_flight("Denver","Urbana",1000);
    assert_flight("Denver","Houston",1500);
    assert_flight("Houston","Los Angeles",1500);
    assert_flight("Denver","Los Angeles",1000);
}

//coloca dados no db do vôo
void assert_flight(char from[20], char to[20], int dist) {
    if(f_pos < MAX){
       strcpy(flight[f_pos].from, from);
       strcpy(flight[f_pos].to, to);
       flight[f_pos].distance = dist;
       flight[f_pos].skip = 0;
       f_pos++;
    }else printf("O banco de dados do vôo está cheio.");
}

int match(char from[20], char to[20]){
    register int t;

    for(t = f_pos-1; t > -1 ; t--){
        if(!strcmp(flight[t].from, from) && !strcmp(flight[t].to, to)) 
            return flight[t].distance;

        return 0; //Não achou
    }
}

float find(char from[20], char anywhere[20]){
    find_pos = 0;
    while (find_pos < f_pos){
        if (!strcmp(flight[find_pos].from, from) && !flight[find_pos].skip){
            strcpy(anywhere, flight[find_pos].to);
            flight[find_pos].skip = 1;
            return flight[find_pos].distance;     
            }
        find_pos++;
    }
    return 0;
}