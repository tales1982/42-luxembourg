#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int indice(int larg,int i,int j){return i*larg+j;}

int main(int qtd,char**arg){
    int larg,alt,iter,i,j,t,x=0,y=0,caneta=0,viz,di,dj;
    char *tab=NULL,*prox=NULL,c,*tmp;
    if(qtd!=4)return 1;
    larg=atoi(arg[1]);alt=atoi(arg[2]);iter=atoi(arg[3]);
    if(larg<=0||alt<=0||iter<0)return 1;
    tab=(char*)malloc((size_t)larg*alt);
    prox=(char*)malloc((size_t)larg*alt);
    if(!tab||!prox){free(tab);free(prox);return 1;}
    for(i=0;i<alt;i++)for(j=0;j<larg;j++)tab[indice(larg,i,j)]=0;
    while(read(0,&c,1)==1){
        int comando_valido=1;
        if(c=='w'){if(y>0)y--;else comando_valido=0;}
        else if(c=='s'){if(y<alt-1)y++;else comando_valido=0;}
        else if(c=='a'){if(x>0)x--;else comando_valido=0;}
        else if(c=='d'){if(x<larg-1)x++;else comando_valido=0;}
        else if(c=='x'){caneta=!caneta;}
        else comando_valido=0;
        if(caneta&&comando_valido)tab[indice(larg,y,x)]=1;
    }
    for(t=0;t<iter;t++){
        for(i=0;i<alt;i++){
            for(j=0;j<larg;j++){
                viz=0;
                for(di=-1;di<=1;di++)
                    for(dj=-1;dj<=1;dj++)
                        if((di||dj)&&i+di>=0&&i+di<alt&&j+dj>=0&&j+dj<larg)
                            viz+=tab[indice(larg,i+di,j+dj)];
                prox[indice(larg,i,j)]=(tab[indice(larg,i,j)]?(viz==2||viz==3):(viz==3));
            }
        }
        tmp=tab;tab=prox;prox=tmp;
    }
    for(i=0;i<alt;i++){
        for(j=0;j<larg;j++)
            putchar(tab[indice(larg,i,j)]?'0':' ');
        putchar('\n');
    }
    free(tab);free(prox);
    return 0;
}
