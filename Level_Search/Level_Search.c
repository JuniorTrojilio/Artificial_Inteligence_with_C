#define MAX 100
#include<string.h>
#include<stdio.h>
#include<locale.h>

/*Struct que armazena os dados do v�o (database)*/
struct FL{
	char from[20];
	char to[20];
	int distance;
	char skip;   /*ponto de restaura��o determina se j� foi visitado ou n�o este n�*/
};

struct FL flight[MAX];  /*Matriz que determina a struct*/

int f_pos = 0;  /*numero de entradas no db do v�o*/
int find_pos = 0; /*indice para procura no database do v�o*/
int tos = 0; /*topo da pilha*/

struct stack {
	char from[20];
	char to[20];
	int dist;
};

struct stack bt_stack[MAX]; /*pilha p/ restaurar*/

assert_flight(char *from, char *to, int dist) {
	if (f_pos < MAX) {
		strcpy(flight[f_pos].from, from); /*strcpy copia o conteudo do argumento from para a variavel flight.from que esta dentro da struct FL*/
		strcpy(flight[f_pos].to, to); /*strcpy copia o conteudo do argumento to para a variavel flight.to que esta dentro da struct FL*/
		flight[f_pos].distance = dist; /*adiciona a dist�ncia contida no argumento dist para flight.dist*/
		flight[f_pos].skip = 0; /*seta o n�vel da struct (n�) como zero (n�o visitado) */
		f_pos++;
	}
	else printf("O banco de dados est� cheio.\n");
}


setup() { /*Preenche a struct completa com os dados do V�o*/
	assert_flight("New York", "Chicago", 1000);
	assert_flight("Chicago", "Denver", 1000);
	assert_flight("New York", "Toronto", 800);
	assert_flight("New York", "Denver", 1900);
	assert_flight("Toronto", "Calgary", 1500);
	assert_flight("Toronto", "Los Angeles", 1800);
	assert_flight("Toronto", "Chicago", 500);
	assert_flight("Denver", "Urbana", 1000);
	assert_flight("Denver", "Houston", 1500);
	assert_flight("Houston", "Los Angeles", 1500);
	assert_flight("Denver", "Los Angeles", 1000);
}

/*Se houver conex�o entre origem  e destino retornar� a dist�ncia do v�o, se n�o houver retorna 0*/
int match(char *from, char *to) {
	register int t;
	for (t = f_pos-1; t >-1; t--) /*t pega a posi��o atual do f_pos - 1 que estar� com o numero de entradas do banco e faz um loop for at� o 1*/
		if (!strcmp(flight[t].from, from) && !strcmp(flight[t].to, to)) return flight[t].distance; /*compara flight.from com from e flight.to com to */
			 /*se from <> from e to <> to ent�o retorna flight.distance no n�vel = t*/

	return 0; /*N�o encontrou*/
}
/*executa uma busca*/
int find(char *from, char *anywhere){
	find_pos = 0;
	while (find_pos < f_pos) { /*enquanto o indice de procura for menor que o indice atual de preenchimento da base ela procurar� as cidades que n�o tem conex�es e setar� flight.skip = 1*/
		if (!strcmp(flight[find_pos].from, from) && !flight[find_pos].skip) {
			strcpy(anywhere, flight[find_pos].to);
			flight[find_pos].skip = 1;
			return flight[find_pos].distance;
		}
		find_pos++;
	}
	return 0;
}

/*rotinas de pilha*/
push(char *from, char *to, int *dist){
	if (tos < MAX) {
		strcpy(bt_stack[tos].from, from);
		strcpy(bt_stack[tos].to, to);
		bt_stack[tos].dist = dist;
		tos++;
	}
	else printf("Pilha cheia.\n");
}
/*rotinas de pilha*/
pop(char *from, char *to, int *dist){
	if (tos > 0) {
		tos--;
		strcpy(from, bt_stack[tos].from);
		strcpy(to, bt_stack[tos].to);
		*dist = bt_stack[tos].dist;
	}
	else printf("underflow da pilha. \n");
}

/*determina se h� uma rota entre a origem e o destino*/
isflight(char* from, char* to) {
	int d, temp, dist;
	char anywhere[20];

	while (dist = find(from, anywhere)) {
		if (d = match(anywhere, to)) {
			push(from, to, dist);
			push(anywhere, to, d);
			return;
		}
	}

	if (dist = find(from, anywhere)) {
		push(from,to, dist);
		isflight(anywhere, to);
	}
	else if (tos > 0) {
		pop(from, to, &dist);
		isflight(from, to);
	}
}

/*mostra ao usu�rio a rota e a dist�ncia*/
route(char *to) {
	int dist = 0, t = 0;
	while (t < tos) {
		printf("%s --> ", bt_stack[t].from);
		dist += bt_stack[t].dist;
		t++;
	}
	printf("%s\n", to);
	printf("Dist�ncia: %d milhas", dist);
}


int main(void) {
	setlocale(LC_ALL,""); /*define o idioma padr�o do sistema operacional*/
	setup();
	isflight("New York", "Los Angeles");
	route("Los Angeles");
	return 0;
}