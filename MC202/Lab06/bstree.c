#include "bstree.h"
#include "row.h"

/*coloca recusirvamente um novo no na arvore*/
Btree *colocaArvore(const int year, const int month, const int day, const int hour, const int minute, Btree *arv, const int lat,const int log, const int ar){
	//coloca o novo no
	if(arv == NULL){
		arv = (Btree*)malloc(sizeof(Btree));
		arv->ano = year; arv->mes = month; arv->dia = day;
		arv->hora = hour; arv->minuto = minute;
		arv->latitude = lat; arv->longitude = log; arv->area = ar;
		arv->proxEsq = NULL;
		arv->proxDir = NULL;
	}
	//anda para esquerda
	else if(checaLado(year,month,day,hour,minute,arv) == 1){
		arv->proxEsq = colocaArvore(year,month,day,hour,minute,arv->proxEsq,lat,log,ar);
	}
	//anda para direita
	else{
		arv->proxDir = colocaArvore(year,month,day,hour,minute,arv->proxDir,lat,log,ar);
	}
	return arv;
}

/*imprime os elementos da arvore em pre ordem*/
void printPreOrdem(Btree *no){
	if(no != NULL){
		printf("\n%d %d %d %d %d",no->ano,no->mes,no->dia,no->hora,no->minuto);
		printf(" %d %d %d",no->latitude,no->longitude,no->area);
		printPreOrdem(no->proxEsq);
		printPreOrdem(no->proxDir);
	}
}
/*encontra o no que deve ser apagado e o apaga*/
void achaNo(const int year, const int month, const int day, const int hour, const int minute, Btree *arv, const int pors,Btree *noAnt, const int dir){
	/*noAnt guarda o no anterior e dir guarda a direcao tomada para se atingir o novo no*/
	if (arv == NULL){
		//printf("\nNao tem no igual!!");
		return;
	}
	//encontrou o no
	else if(year == arv->ano && month == arv->mes && day == arv->dia && hour == arv->hora && minute == arv->minuto){
		if (pors == 1){
		//ha elemento na esquerda
			if(arv->proxEsq != NULL)
				trocaComPredecessor(arv,arv->proxEsq);
				//nao ha elemento na esquerda
			else{
                //checa se ha elemento a direita
                //caso nao tenha apenas apaga
				if (arv->proxDir == NULL){
					if (dir == 1) noAnt->proxEsq = NULL;
					else noAnt->proxDir = NULL;
				}
				//caso tenha remove o no e
				else{
					arv = arv->proxDir;
					if(dir == 1) noAnt->proxEsq = arv;
					else noAnt->proxDir = arv;
				}
			}
		}
		else{
			if(arv->proxDir != NULL)
				trocaComSucessor(arv,arv->proxDir);
			else{
				if(arv->proxEsq == NULL){
					if (dir == 1) noAnt->proxEsq = NULL;
					else noAnt->proxDir = NULL;
				}
				else{
					arv = arv->proxEsq;
					if(dir == 1) noAnt->proxEsq = arv;
					else noAnt->proxDir = arv;
				}
			}
		}
		return;
	}
	//anda para a esquerda
	else if(checaLado(year,month,day,hour,minute,arv) == 1){
		achaNo(year,month,day,hour,minute,arv->proxEsq,pors,arv, 1);
	}
	//anda para direita
	else{
		achaNo(year,month,day,hour,minute,arv->proxDir,pors,arv, 0);
	}
}
/*apaga um no com o seu predecessor*/
void trocaComPredecessor(Btree *root, Btree *temp){
	Btree *aux = temp;
	//se nao ninguem a direita
	if(temp->proxDir == NULL){
		root->ano = temp->ano;
        root->mes = temp->mes;
        root->dia = temp->dia;
        root->hora = temp->hora;
        root->minuto = temp->minuto;
        root->latitude = temp->latitude;
        root->longitude = temp->longitude;
        root->area = temp->area;
        root->proxEsq = temp->proxEsq;
        return;
	}
	//tem alguem a direita
	else{
        //atinge o no mais a direita
		while(temp->proxDir){
            aux = temp;
            temp = temp->proxDir;
        }
        root->ano = temp->ano;
        root->mes = temp->mes;
        root->dia = temp->dia;
        root->hora = temp->hora;
        root->minuto = temp->minuto;
        root->latitude = temp->latitude;
        root->longitude = temp->longitude;
        root->area = temp->area;
        //checa se no no mais a direita existe alguem a esquerda
        //se houver os troca de lugar e apaga o mais a direita
		if(temp->proxEsq != NULL){
			aux->proxDir = temp->proxEsq;
		}
		//caso nao haja so apaga
		else{
			aux->proxDir = NULL;
		}
	}

}
/*apaga no com o seu sucessor*/
void trocaComSucessor(Btree* root, Btree *temp){
	Btree *aux = temp;
	//nao ha ninguem a esquerda
	if (temp->proxEsq == NULL){
		root->ano = temp->ano;
		root->mes = temp->mes;
		root->dia = temp->dia;
		root->hora = temp->hora;
		root->minuto = temp->minuto;
		root->latitude = temp->latitude;
		root->longitude = temp->longitude;
		root->area = temp->area;
		root->proxDir = temp->proxDir;
		return;
	}
	//ha alguem a esquerda
	else{
        //atinge o no mais a esquerda
		while(temp->proxEsq){
			aux = temp;
			temp = temp->proxEsq;
		}
		root->ano = temp->ano;
		root->mes = temp->mes;
		root->dia = temp->dia;
		root->hora = temp->hora;
		root->minuto = temp->minuto;
		root->latitude = temp->latitude;
		root->longitude = temp->longitude;
		root->area = temp->area;
		//checa se no no mais a esquerda existe alguem a direita
        //se houver os troca de lugar e apaga o mais a esquerda
		if(temp->proxDir != NULL){
			aux->proxEsq = temp->proxDir;
		}
		//se nao houver so apaga
		else{
			aux->proxEsq = NULL;
		}
	}
}



