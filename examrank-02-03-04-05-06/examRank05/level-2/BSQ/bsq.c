#define _POSIX_C_SOURCE 200809L
#include "bsq.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------- utils ---------- */
static void free_map(t_map *m){
    if(!m||!m->g) return;
    for(int r=0;r<m->h;r++) free(m->g[r]);
    free(m->g); m->g=NULL;
}
static int parse_header(FILE *fp, t_el *el){
    if (fscanf(fp,"%d %c %c %c\n",&el->n,&el->e,&el->o,&el->f)!=4) return -1;
    if (el->n<=0) return -1;
    if (el->e==el->o || el->e==el->f || el->o==el->f) return -1;
    return 0;
}
static int read_map(FILE *fp, t_map *m){
    char *line=NULL; size_t cap=0; ssize_t len; int w=-1;
    m->g = (char**)malloc((size_t)m->el.n*sizeof(char*)); if(!m->g) return -1;
    for(int i=0;i<m->el.n;i++) m->g[i]=NULL;
    for(int r=0;r<m->el.n;r++){
        len=getline(&line,&cap,fp); if(len<0) { free(line); return -1; }
        if(len==0 || line[len-1]!='\n'){ free(line); return -1; }
        len--; /* remove '\n' */
        if (w == -1)
    w = (int)len;
if (len != w || w <= 0) {
    free(line);
    return -1;
}

        m->g[r]=(char*)malloc((size_t)w); if(!m->g[r]){ free(line); return -1; }
        for(int c=0;c<w;c++){
            char ch=line[c];
            if(ch!=m->el.e && ch!=m->el.o){ free(line); return -1; }
            m->g[r][c]=ch;
        }
        m->h=r+1;
    }
    free(line); m->w=w;
    return (m->h>0 && m->w>0) ? 0 : -1;
}
static int min3(int a,int b,int c){ if(a>b)a=b; if(a>c)a=c; return a; }

/* ---------- solve & print ---------- */
static void solve_and_print(t_map *m){
    int *prev=(int*)calloc((size_t)m->w,sizeof(int));
    int *curr=(int*)calloc((size_t)m->w,sizeof(int));
    int bestS=0,bestT=0,bestL=0;
    for(int r=0;r<m->h;r++){
        for(int c=0;c<m->w;c++){
            if(m->g[r][c]==m->el.o) curr[c]=0;
            else{
                curr[c]=(r==0||c==0)?1:1+min3(prev[c],curr[c-1],prev[c-1]);
                int s=curr[c], t=r-s+1, l=c-s+1;
                if(s>bestS || (s==bestS && (t<bestT || (t==bestT && l<bestL)))){
                    bestS=s; bestT=t; bestL=l;
                }
            }
        }
        int *tmp=prev; prev=curr; curr=tmp;
        for(int i=0;i<m->w;i++) curr[i]=0;
    }
    free(prev); free(curr);
    if(bestS>0)
        for(int i=0;i<bestS;i++) for(int j=0;j<bestS;j++)
            m->g[bestT+i][bestL+j]=m->el.f;
    for(int r=0;r<m->h;r++){ /* imprime solução */
        /* m->g[r] não tem '\n' embutido */
        for(int c=0;c<m->w;c++) fputc(m->g[r][c], stdout);
        fputc('\n', stdout);
    }
}

/* ---------- runner ---------- */
int run_file(FILE *fp){
    t_map m; m.g=NULL; m.w=m.h=0;
    if(parse_header(fp,&m.el)==-1) { free_map(&m); return -1; }
    if(read_map(fp,&m)==-1)        { free_map(&m); return -1; }
    solve_and_print(&m);
    free_map(&m);
    return 0;
}
int run_path(char *path){
    FILE *fp=fopen(path,"r"); if(!fp) return -1;
    int r=run_file(fp); fclose(fp); return r;
}

/* ---------- main ---------- */
int main(int ac,char **av){
    if(ac==1){
        if(run_file(stdin)==-1) fprintf(stderr,"map error\n");
        return 0;
    }
    for(int i=1;i<ac;i++){
        if(run_path(av[i])==-1) fprintf(stderr,"map error\n");
        /* regra: cada resultado (ou erro) termina com \n: 
           - sucesso: já imprimimos linhas com '\n'
           - erro: a linha acima já imprime '\n' no stderr */
    }
    return 0;
}

