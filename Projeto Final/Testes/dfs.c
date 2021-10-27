#include <stdio.h>
#include <stdlib.h>

/*
 * This code has been written by Leto II Atreides on Youtube. All credits go to him.
 * I just typed the code from the video and uploaded it to GitHub.
 */
char** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
enum terrain {
	empty,
	wall,
	goal,
	crumb
};
void print_maze();
void alloc_maze()
{
	maze = malloc(rows * sizeof(char*));
	
	int i;
	for (i = 0; i < rows; ++i){
		maze[i] = malloc(cols * sizeof(char*));
	}
}
void alloc_visited()
	visited = malloc(rows * sizeof(int*));
		visited[i] = malloc(cols * sizeof(int*));
void get_maze(char* file_name)
	char c;
	char rows_s[3] = { '\0' };
	char cols_s[3] = { '\0' };
	int rows_i = 0;
	int cols_i = 0;
	int swap = 0;
	FILE* maze_file = fopen(file_name, "r");
	if (maze_file) {
		while ((c = getc(maze_file)) != EOF) {
			if (c == '\n') {
				break;
			} else if (c == ','){
				swap = 1;
			} else if (!swap) {
				rows_s[rows_i] = c;
				rows_i++;
			} else {
				cols_s[cols_i] = c;
				cols_i++;
			}
		}
	} else {
		printf("No such file!");
		return;
	rows = atoi(rows_s);
	cols = atoi(cols_s);
	alloc_maze();
	int i=-1,j;
    
    /* if ((c = getc(maze_file)) == '\n') {
            printf("\n%d\n",i);
        } */
    char *line=(char*)calloc(cols+2,sizeof(char));
    //fgets(line,cols+20,maze_file);
	for (i = 0; i < rows; i++) {
        fgets(line,cols+2,maze_file);
        printf("%s",line);
        //printf("\n%d:",i);
		for (j = 0; j < cols; j++) {
            //sscanf(line,"%c",&maze[i][j]);
            //printf("%s",&maze[i][j]);
			/* if ((c = getc(maze_file)) == '\n') {
                printf("enter");
				c = getc(maze_file);//printf("%d,%d\n",rows,cols);
            //c = getc(maze_file);
			maze[i][j] = c;
            
			if (c =='s') {
				start_row = i;
				start_col = j;
			} */
        
        /* if ((c = getc(maze_file)) == '\n') {
        //printf("\n");
    print_maze();
	fclose(maze_file);
void print_maze()
	int i, j;
			printf("%d", maze(conversion(i,j,l,c)));
		printf("\n");
	}	
	printf("\n");
void init_visited()
	alloc_visited();
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (maze[i][j] == -1) {
				visited[i][j] = 1;
			} 
			else {
				visited[i][j] = 0;
    for (i = 0; i < rows; ++i) {
			printf("%d", visited[i][j]);
    printf("\n");
}	
void add_crumbs()
			if (maze[i][j] != 's' && visited[i][j] == crumb) {
				maze[i][j] = '.';
int dfs(int row, int col)
	int* current = &visited[row][col];
	if (*current == goal){
		return 1;
	if (*current == empty) {
		*current = crumb;
		if (dfs(row, col - 1)){
			*current = crumb;
			return 1;
		} 
		if (dfs(row + 1, col)){
		if (dfs(row, col + 1)){
			return 1;		
		if (dfs(row - 1, col)){
	return 0;
int main() {
	get_maze("maze.txt");
	init_visited();
	print_maze();
	if (!dfs(start_row, start_col)) {
		printf("No path to the goal could be found.\n");
		add_crumbs();
		print_maze();
