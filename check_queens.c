////////////////////////////////////////////////////////////////////////////////
// Main File:        check_queens
// This File:        check_queens
// Other Files:      none
// Semester:         CS 354 SPRING 2019
//           
// Author:           Monica Schmidt
// Email:            meschmidt6@wisc.edu
// CS Login:         monicas
//           
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//           
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//           
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   
 
char *COMMA = ",";
  
/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {	
        char *line = NULL;  
        size_t len = 0;  
        if (getline(&line, &len, fp) == -1) {  
                printf("Error in reading the file\n");  
                exit(1);  
        }  
           
        char *token = NULL; 
        token = strtok(line, COMMA);
        *rows = atoi(token); 
           
        token = strtok(NULL, COMMA); 
        *cols = atoi(token);
}
/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other in the horizontal.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * cols: number of columns
 * curcol: the current column in the iteration
 * currow: the current row in the iteration
*/
int check_horizontal(int **board, int cols, int curcol, int currow){
	for(int i = 0; i < cols; i++){
		//Skips over the current col 
		if(curcol == i){
 
		}else{
			//Checks to see if there is another 1 in the row
			if(*(*(board + currow) + i) == 1){
				return 1;
			}
		}
	}
	return 0;
}

/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other in the vertical.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * rows: number of rows
 * curcol: the current column in the iteration
 * currow: the current row in the iteration
*/
 int check_vertical(int **board, int rows, int curcol, int currow){
	 for(int i = 0; i < rows; i++){
		//Skips over the current row
                if(currow == i){

                }else{
			//Checks to see if there is another 1 in the col
                        if(*(*(board + i) + curcol) == 1){
                                return 1;
                        }
                }
        }
	return 0;
}

/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other in the diagonal.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 * curcol: the current column in the iteration
 * currow: the current row in the iteration
*/
int check_diagonal(int **board, int rows, int cols, int curcol, int currow){
	//Starts at the next row after the current row because all rows before
	//were already checked
	for(int i = currow + 1; i < rows; i++){
		int nextCol = (curcol + (i - currow));
		int prevCol = (curcol - (i - currow));
		//Checks if the previous col and next col are within bounds
		//Also check to see if the next col or previous col have a 1
		if(((nextCol < cols) && (*(*(board + i) + nextCol) == 1))
		       || ((prevCol >= 0) && (*(*(board + i) + prevCol) == 1))){
				return 1;
                	}
        	}
	return 0;
}

/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns 
*/
int check_queens(int **board, int rows, int cols) { 
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			//Checks for 1s
			if(*(*(board + i) + j) == 1){
				
				int hoz = check_horizontal(board,cols,j,i);
				
				//Returns 1 at the first instance of pair of 1s
				if(hoz  == 1){
                                        return 1;
                                }

				int vert = check_vertical(board,rows,j,i);
				
				//Returns 1 at the first instance of pair of 1s
				if(vert == 1){
                                        return 1;
                                }
				
				int diag = check_diagonal(board,rows,cols,j,i);	
				
				//Returns 1 at the first instance of pair of 1s
				if(diag == 1){
					return 1;
				}	
			}
		}
	}
        return 0;
}     

/* PARTIALLY COMPLETED:
 * This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {        
        //Checks if number of command-line arguments is correct.
        if (argc != 2){
		printf("Usage: ./check_queens <input_filename>\n");
		exit(1);
	}

        //Open the file and check if it opened successfully.
        FILE *fp = fopen(*(argv + 1), "r");
        if (fp == NULL) {
                printf("Cannot open file for reading\n");
                exit(1);
        }

        //Declare local variables.
        int rows, cols;
	int *r = &rows;//points to rows to change its value within functions
	int *c = &cols;//points to cols to change its value within functions
        
	// Call get_dimensions to retrieve the board dimensions.
	get_dimensions(fp, r, c);


        //Dynamically allocate a 2D array of dimensions retrieved above.
	int **board = malloc(sizeof(int*)*rows);

	//Checks to see if the board is NULL
	if(!board){
		printf("Not enough space in memory\n");
		exit(1);
	}else{
		for (int i = 0; i < rows; i++){
			*(board+i) = malloc(sizeof(int)*cols);
			//Checks to see if the array cols are NULL	
			if(!(*(board + i))){	
                        	printf("Not enough space in memory\n");
                        	exit(1);
				
			}
		}
	}

        //Read the file line by line.
        //Tokenize each line wrt comma to store the values in your 2D array.
        char *line = NULL;
        size_t len = 0;
        char *token = NULL;
        for (int i = 0; i < rows; i++) {
                if (getline(&line, &len, fp) == -1) {
                        printf("Error while reading the file\n");
                        exit(1);        
                }

                token = strtok(line, COMMA);
                for (int j = 0; j < cols; j++) {
                        //Complete the line of code below
                        //to initialize your 2D array.
                       *(*(board + i) + j) = atoi(token);
                        token = strtok(NULL, COMMA);    
                }
        }
        //Call the function check_queens and print the appropriate
        //output depending on the function's return value.
        int check = check_queens(board,rows,cols);
	
	if(check == 1){
		printf("true\n");
	}else{
		printf("false\n");
	}
        

        //Free all dynamically allocated memory.
	for(int i = 0; i < rows; i++){
		free(*(board + i));
	}

	free(board);

        //Close the file.
        if (fclose(fp) != 0) {
                printf("Error while closing the file\n");
                exit(1);        
        }

        return 0;


} 
