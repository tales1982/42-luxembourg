#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_PRINTABLE(c) ((c)>=32 && (c)<=126)

typedef struct{int n,w; char e,o,f; char **m;} M;

int min3(int a,int b,int c){return a<b?(a<c?a:c):(b<c?b:c);}

M* read_map(char *fn){
    FILE *fp=fn?fopen(fn,"r"):stdin;
    if(!fp) return NULL;
    M *m=malloc(sizeof(M));
    if(!m){
        if(fn) fclose(fp);
        return NULL;
    }
    if(fscanf(fp,"%d %c %c %c\n",&m->n,&m->e,&m->o,&m->f)!=4 ||
       m->n<=0 || m->e==m->o || m->e==m->f || m->o==m->f ||
       !IS_PRINTABLE(m->e) || !IS_PRINTABLE(m->o) || !IS_PRINTABLE(m->f)){
        if(fn) fclose(fp);
        free(m);
        return NULL;
    }
    m->m=malloc(m->n*sizeof(char*));
    if(!m->m){
        if(fn) fclose(fp);
        free(m);
        return NULL;
    }
    for(int i=0;i<m->n;i++){
        char *line=NULL; size_t len=0;
        if(getline(&line,&len,fp)==-1){
            while(i--) free(m->m[i]);
            free(m->m); free(m);
            if(fn) fclose(fp);
            return NULL;
        }
        int ll=strlen(line); if(ll && line[ll-1]=='\n') line[--ll]='\0';
        if(ll==0){
            while(i--) free(m->m[i]);
            free(line); free(m->m); free(m);
            if(fn) fclose(fp);
            return NULL;
        }
        if(i==0) m->w=ll;
        else if(ll!=m->w){
            while(i--) free(m->m[i]);
            free(line); free(m->m); free(m);
            if(fn) fclose(fp);
            return NULL;
        }
        for(int j=0;j<ll;j++) if(line[j]!=m->e && line[j]!=m->o){
            while(i--) free(m->m[i]);
            free(line); free(m->m); free(m);
            if(fn) fclose(fp);
            return NULL;
        }
        m->m[i]=line;
    }
    char *extra=NULL; size_t len=0;
    if(getline(&extra,&len,fp)!=-1){
        free(extra);
        for(int i=0;i<m->n;i++) free(m->m[i]);
        free(m->m); free(m);
        if(fn) fclose(fp);
        return NULL;
    }
    if(fn) fclose(fp);
    return m;
}

void solve(M *m){
    int **d=malloc(m->n*sizeof(int*)), ms=0, bi=0, bj=0;
    for(int i=0;i<m->n;i++){ d[i]=calloc(m->w,sizeof(int)); }
    for(int i=0;i<m->n;i++)
        for(int j=0;j<m->w;j++)
            if(m->m[i][j]!=m->o){
                d[i][j]=(i&&j)?min3(d[i-1][j],d[i][j-1],d[i-1][j-1])+1:1;
                if(d[i][j]>ms){ ms=d[i][j]; bi=i; bj=j; }
            }
    for(int i=bi-ms+1;i<=bi;i++)
        for(int j=bj-ms+1;j<=bj;j++)
            m->m[i][j]=m->f;
    for(int i=0;i<m->n;i++){ free(d[i]); }
    free(d);
}

void print_map(M *m){ for(int i=0;i<m->n;i++) puts(m->m[i]); }
void free_map(M *m){ if(!m) return; for(int i=0;i<m->n;i++) free(m->m[i]); free(m->m); free(m); }
void process(char *f){ M *m=read_map(f); if(!m){ fprintf(stderr,"map error\n"); return; } solve(m); print_map(m); free_map(m); }

int main(int c,char **v){
    if(c==1) process(NULL);
    else for(int i=1;i<c;i++){ if(i>1) puts(""); process(v[i]); }
    return 0;
}

