#define _POSIX_C_SOURCE 200809L
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>

typedef struct s_map{char **grid;int **dp;int rows;int cols;char empty;char obst;char full;}t_map;

typedef struct s_sq{int size;int row;int col;}t_sq;

static int line_len(char *s){int i=0;while(s[i]&&s[i]!='\n')i++;return i;}

static int min3(int a,int b,int c){if(a>b)a=b;if(a>c)a=c;return a;}

static void free_map(t_map *m){
int i=0;
if(m->grid){i=0;while(i<m->rows){free(m->grid[i]);i++;}free(m->grid);m->grid=NULL;}
if(m->dp){i=0;while(i<m->rows){free(m->dp[i]);i++;}free(m->dp);m->dp=NULL;}}

static int parse_header(FILE *fp,t_map *m){
if(fscanf(fp,"%d %c %c %c ",&m->rows,&m->empty,&m->obst,&m->full)!=4)return 0;
if(m->rows<=0)return 0;
if(m->empty==m->obst||m->empty==m->full||m->obst==m->full)return 0;
return 1;}


static int valid_line_chars(char *line,t_map *m){
int i=0;
while(line[i]&&line[i]!='\n')
{if(line[i]!=m->empty&&line[i]!=m->obst)return 0;
i++;}
return 1;}

static int read_map(FILE *fp,t_map *m){
char *line=NULL;size_t n=0;ssize_t len;int i=0,l;
m->grid=(char**)malloc(sizeof(char*)*m->rows);if(!m->grid)return 0;
while(i<m->rows){len=getline(&line,&n,fp);
if(len<=0||line[len-1]!='\n'){free(line);m->rows=i;free_map(m);return 0;}
m->grid[i]=line;line=NULL;n=0;
l=line_len(m->grid[i]);
if(i==0){m->cols=l;if(m->cols<=0){free_map(m);return 0;}}
if(l!=m->cols||!valid_line_chars(m->grid[i],m)){free_map(m);return 0;}
i++;}
free(line);
return 1;}

static int init_dp(t_map *m){
int i=0,j=0;
m->dp=(int**)malloc(sizeof(int*)*m->rows);if(!m->dp)return 0;
while(i<m->rows){m->dp[i]=(int*)calloc(m->cols,sizeof(int));
if(!m->dp[i]){
j=0;while(j<i){free(m->dp[j]);j++;}free(m->dp);m->dp=NULL;return 0;}
i++;}return 1;}

//--------------comeso aqui
static t_sq find_best_square(t_map *m){
t_sq sq={0,0,0};int i=0,j;
while(i<m->rows){j=0;
while(j<m->cols){
if(m->grid[i][j]==m->obst)m->dp[i][j]=0;
else if(i==0||j==0)m->dp[i][j]=1;
else m->dp[i][j]=1+min3(m->dp[i-1][j],m->dp[i][j-1],m->dp[i-1][j-1]);
if(m->dp[i][j]>sq.size){sq.size=m->dp[i][j];sq.row=i;sq.col=j;}j++;}i++;}
return sq;}

static void fill_square(t_map *m,t_sq sq){
int r0,c0,i,j;
if(sq.size<=0)return;
r0=sq.row-sq.size+1;c0=sq.col-sq.size+1;
i=r0;
while(i<=sq.row){j=c0;
while(j<=sq.col){m->grid[i][j]=m->full;j++;}i++;}
}

static void solve_bsq(t_map *m){t_sq sq;if(!init_dp(m))return;sq=find_best_square(m);fill_square(m,sq);}

static void print_map(t_map *m){int i=0;while(i<m->rows){
fputs(m->grid[i],stdout);i++;}}

static void process_map(FILE *fp){
t_map m={0};
m.grid=NULL;m.dp=NULL;m.rows=0;m.cols=0;m.empty=0;m.obst=0;m.full=0;
if(!parse_header(fp,&m)||!read_map(fp,&m)){fprintf(stderr,"map error\n");free_map(&m);return;}
solve_bsq(&m);print_map(&m);free_map(&m);
}

static void process_file(char *name){
FILE *fp=fopen(name,"r");
if(!fp){fprintf(stderr,"map error\n");return;}
process_map(fp);fclose(fp);
}

int main(int ac,char **av){
int i=1;
if(ac==1)process_map(stdin);
else{while(i<ac){process_file(av[i]);
if(i<ac-1)fputs("\n",stdout);
i++;}}return 0;}

