#include "bstree.h"
#include "row.h"



int main(){
    //iniciando variaveis
	Btree *arv;
	arv = NULL;
	int n,year, month, day, hour,minute;
	int lat, log, ar;
	//recebendo a quantidade de nos
	scanf("%d",&n);
	int i;
	//recebendo as informacoes e colocandos os nos
	for (i = 0; i < n; i++){
		scanf("%d %d %d %d %d",&year,&month,&day,&hour,&minute);
		scanf("%d %d %d",&lat,&log,&ar);
		arv = colocaArvore(year, month,day,hour,minute,arv, lat,log,ar);
	}
	//recebendo a quantidade de mudancas a se fazer
	scanf("%d",&n);
	char com;
	//recebendo e fazendo de acordo com o comando
	for(i = 0; i < 2*n; i++){
        scanf("%c",&com);
        whatToDo(com,arv);
	}
	//imprimindo a arvore final
	printPreOrdem(arv);
}

