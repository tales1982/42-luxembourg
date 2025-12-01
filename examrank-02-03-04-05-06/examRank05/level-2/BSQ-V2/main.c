#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>

typedef struct s_map {int rows;int cols;char empty;char obstacle;char full;char **grid;} t_map;

typedef struct s_square {int size;int row;int col;} t_square;

int ft_strlen(char *str){int len;len=0;while(str[len])len++;return(len);}

int is_printable(char c){return(c>=32&&c<=126);}

int parse_first_line(char *line,t_map *map){int len;int i;int num;len=ft_strlen(line);if(len<5||line[len-1]!='\n')return(0);map->full=line[len-2];map->obstacle=line[len-3];map->empty=line[len-4];if(!is_printable(map->empty)||!is_printable(map->obstacle)||!is_printable(map->full))return(0);if(map->empty==map->obstacle||map->empty==map->full||map->obstacle==map->full)return(0);num=0;i=0;while(i<len-4){if(line[i]<'0'||line[i]>'9')return(0);num=num*10+(line[i]-'0');i++;}if(num<=0)return(0);map->rows=num;return(1);}

t_map *read_map(FILE *file){t_map *map;char *line;size_t len;ssize_t read;int i;map=malloc(sizeof(t_map));if(!map)return(NULL);line=NULL;len=0;read=getline(&line,&len,file);if(read==-1||!parse_first_line(line,map)){free(line);free(map);return(NULL);}free(line);map->grid=malloc(sizeof(char*)*map->rows);if(!map->grid){free(map);return(NULL);}map->cols=0;i=0;while(i<map->rows){line=NULL;len=0;read=getline(&line,&len,file);if(read==-1){free(line);while(i>0)free(map->grid[--i]);free(map->grid);free(map);return(NULL);}if(line[read-1]=='\n')line[read-1]='\0';else{free(line);while(i>0)free(map->grid[--i]);free(map->grid);free(map);return(NULL);}if(map->cols==0)map->cols=ft_strlen(line);else if(ft_strlen(line)!=map->cols){free(line);while(i>0)free(map->grid[--i]);free(map->grid);free(map);return(NULL);}map->grid[i]=line;i++;}return(map);}

int validate_map(t_map *map){int i;int j;if(!map||map->rows<=0||map->cols<=0)return(0);i=0;while(i<map->rows){j=0;while(j<map->cols){if(map->grid[i][j]!=map->empty&&map->grid[i][j]!=map->obstacle)return(0);j++;}i++;}return(1);}

void free_map(t_map *map){int i;if(!map)return;if(map->grid){i=0;while(i<map->rows){free(map->grid[i]);i++;}free(map->grid);}free(map);}

int min_of_three(int a, int b, int c){int min;min=a;if(b<min)min=b;if(c<min)min=c;return (min);}

t_square find_largest_square(t_map *map){int **dp;t_square best;int i;int j;best.size=0;best.row=0;best.col=0;dp=malloc(sizeof(int*)*map->rows);if(!dp)return(best);i=0;while(i<map->rows){dp[i]=calloc(map->cols,sizeof(int));if(!dp[i]){while(i>0)free(dp[--i]);free(dp);return(best);}i++;}i=0;while(i<map->rows){j=0;while(j<map->cols){if(map->grid[i][j]==map->empty){if(i==0||j==0)dp[i][j]=1;else dp[i][j]=min_of_three(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1;if(dp[i][j]>best.size){best.size=dp[i][j];best.row=i-dp[i][j]+1;best.col=j-dp[i][j]+1;}}else dp[i][j]=0;j++;}i++;}i=0;while(i<map->rows){free(dp[i]);i++;}free(dp);return(best);}

void fill_square(t_map *map,t_square square){int i;int j;i=square.row;while(i<square.row+square.size){j=square.col;while(j<square.col+square.size){map->grid[i][j]=map->full;j++;}i++;}}

void print_map(t_map *map){int i;i=0;while(i<map->rows){fprintf(stdout,"%s\n",map->grid[i]);i++;}}

void print_error(char *message){fprintf(stdout, "Error: %s\n", message);}

void process_map(FILE *file){t_map *map;t_square square;map=read_map(file);if(!map){print_error("invalid map");return;}if(!validate_map(map)){print_error("invalid map");free_map(map);return;}square=find_largest_square(map);if(square.size>0)fill_square(map,square);print_map(map);free_map(map);}

int main(int argc,char **argv){FILE *file;if(argc==1){process_map(stdin);}else if(argc==2){file=fopen(argv[1],"r");if(!file){print_error("could not open file");return(1);}process_map(file);fclose(file);}else{print_error("invalid number of arguments");return(1);}return(0);}
