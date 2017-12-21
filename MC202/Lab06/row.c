#include "row.h"
#include "bstree.h"

/*decide qual o lado para o qual o no deve ir*/
int checaLado(const int year,const int month, const int day,const int hour,const int minute,Btree *arv){
    /*caso o ano do no a ser colocado seja menor que o no em questao vai para esquerda*/
	if( year < arv->ano){
		return 1;
	}
    /*caso o ano do no a ser colocado seja maior que o no em questao vai para direita*/
	else if (year > arv->ano){
		return 0;
	}
	//ano é o mesmo
	else{
	/*repete para o mes*/
		if(month < arv->mes){
			return 1;
		}
		else if(month > arv->mes){
			return 0;
		}
		//mes é o mesmo
		else{
		/*repete para o dia*/
			if(day < arv->dia){
				return 1;
			}
			else if(day >  arv->dia){
				return 0;
			}
			//dia é o mesmo
			else{
			/*repete para a hora*/
				if(hour < arv->hora){
					return 1;
				}
				else if(hour > arv->hora){
					return 0;
				}
				//hora é a mesma
				else{
                    /*repete para o minuto*/
					if (minute <= arv->minuto){
						return 1;
					}
					else{
						return 0;
					}
				}
			}
		}
	}
}

/*recebe o char e a arvore e a partir do char decide qual comando fazer*/
void whatToDo(const char com,Btree *arv){
	int year, month, day, hour,minute;
	int lat, log, ar;
	/*recebe as variaveis para inserir novo no*/
	if( com == 'i'){
		scanf("%d %d %d %d %d",&year,&month,&day,&hour,&minute);
		scanf("%d %d %d",&lat,&log,&ar);
		arv = colocaArvore(year, month,day,hour,minute,arv, lat,log,ar);
	}
	/*recebe informacoes para atualizar um no ja existente*/
	else if (com == 'a'){
		scanf("%d %d %d %d %d",&year,&month,&day,&hour,&minute);
		scanf("%d %d %d",&lat,&log,&ar);
		procuraNo(year,month,day,hour,minute,arv,lat,log,ar);
	}
	/*recebe os dados do no a ser retirado pelo seu predecessor*/
	else if(com == 'p'){
		scanf("%d %d %d %d %d",&year,&month,&day,&hour,&minute);
		achaNo(year, month, day, hour, minute, arv,1,arv,1);
	}
	/*recebe os dados do no a ser retirado pelo seu sucessor*/
	else if(com == 's'){
		scanf("%d %d %d %d %d",&year,&month,&day,&hour,&minute);
		achaNo(year, month, day, hour, minute, arv,0,arv,0);
	}
}


/*encontra o no a ser atualizado e o atualiza*/
void procuraNo(const int year,const int month,const int day,const int hour,const int minute,Btree* arv,const int lat,const int log,const int ar){
	if (arv == NULL){
		//printf("\nNao tem no igual!!");
		return;
	}
	//encontrou o no
	else if(year == arv->ano && month == arv->mes && day == arv->dia && hour == arv->hora && minute == arv->minuto){
		arv->latitude = lat;
		arv->longitude = log;
		arv->area = ar;
		return;
	}
	//anda para a esquerda
	else if(checaLado(year,month,day,hour,minute,arv) == 1){
		procuraNo(year,month,day,hour,minute,arv->proxEsq,lat,log,ar);
	}
	//anda para a direita
	else{
		procuraNo(year,month,day,hour,minute,arv->proxDir,lat,log,ar);
	}
}
