/*
NOTE: 
isConnected and isConnectedx is identical. 
One is print statement to check if the algorithm is working.

Same for calculatePtsAndRisks and calculatePtsAndRisksx
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
struct LinkedList{
    int data;
    struct LinkedList *next;
};

struct Points{
    int pts;
    int index;
    int type;
};
typedef struct LinkedList *node;
typedef struct Points *P;

int getRandInput(int m){
    //rand() % (max + 1 min) + min;
    return rand() % (75+ 1 -25) + 25;
}

node createNode(){
   node temp;
   temp = (node)malloc(sizeof(struct LinkedList));
   temp->next = NULL;
   return temp;
}

node addNode(node head, int value){
   
   node temp, p;
   temp = createNode();
   temp->data = value;
   
   if(head == NULL){
      head = temp;
   }else{
      p = head;
      while(p->next != NULL){
         p = p->next;
      }
      p->next = temp;
   }
   return head;
}

void display(int *ptr, int m){
    for(int i =0 ; i < m; i++){
        for(int j = 0; j < m; j++){
            
            if (j ==0)
                fprintf(stderr, "|");
            fprintf(stderr, "%2d |", *(ptr + i*m + j));
            if (j == m - 1)
                fprintf(stderr, "\n");
        }
        for(int j = 0; j < 2*m; j++){
            fprintf(stderr, "ー");
            if (j == 2*m - 1)
                fprintf(stderr, "\n");
        }
    }
    return;
}

void displayx(char *ptr, int m){
    for(int i =0 ; i < m; i++){
        for(int j = 0; j < m; j++){
            
            if (j ==0)
                fprintf(stderr, "|");
            fprintf(stderr, "%2c |", *(ptr + i*m + j));
            if (j == m - 1)
                fprintf(stderr, "\n");
        }
        for(int j = 0; j < 2*m; j++){
            fprintf(stderr, "ー");
            if (j == 2*m - 1)
                fprintf(stderr, "\n");
        }
    }
    return;
}

void isConnectedx(int *grid, int m, int index, int i, int *pts, int flag){
    /*
    diagnal has higher "direction point"

    ______________
    | 4 | 2 | 3 |
    --------------
    | 1 |N/A|N/A|
    --------------
    |N/A|N/A|N/A|
    
    
    if adjacent is cell is occupied by opponent, the pts will be -1
    */
    int check = 0;
    
    switch(i){
        case 1:
            if (flag == 0){
                if(grid[index + 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - 1] == 1){
                *pts = *pts + 1;
                return isConnectedx(grid, m, index-m, 1, pts, 1);
            }else if(grid[index - 1] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;
        case 2:
            if (flag == 0){
                if(grid[index + m] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - m] == 1){
                *pts = *pts + 1;
                return isConnectedx(grid, m, index-m, 2, pts, 1);
            }else if(grid[index - m] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;

        case 3:
            if (flag == 0){
                if(grid[index + m - 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                    //fprintf(stderr, "peke at %d\n" , index);
                }
            }
            if(grid[index - m + 1] == 1){
                *pts = *pts + 1;
                return isConnectedx(grid, m, index-m, 3, pts, 1);
            }else if(grid[index - m + 1] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;

        case 4:
            if (flag == 0){
                if(grid[index + m + 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - m - 1] == 1){
                *pts = *pts + 1;
                return isConnectedx(grid, m, index-m, 4, pts, 1);
            }else if(grid[index - m - 1] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;
    }
    return;
}

void isConnected(int *grid, int m, int index, int i, int *pts, int flag){
    /*
    diagnal has higher "direction point"

    ______________
    | 4 | 2 | 3 |
    --------------
    | 1 |N/A|N/A|
    --------------
    |N/A|N/A|N/A|
    
    
    if adjacent is cell is occupied by opponent, the pts will be -1
    */
    int check = 0;
    
    switch(i){
        case 1:
            if (flag == 0){
                if(grid[index + 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - 1] == 1){
                *pts = *pts + 1;
                return isConnected(grid, m, index-1, 1, pts, 1);
            }else if(grid[index - 1] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;
        case 2:
            if (flag == 0){
                if(grid[index + m] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - m] == 1){
                *pts = *pts + 1;
                return isConnected(grid, m, index-m, 2, pts, 1);
            }else if(grid[index - m] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;

        case 3:
            if (flag == 0){
                if(grid[index + m - 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                    //fprintf(stderr, "peke at %d\n" , index);
                }
            }
            if(grid[index - m + 1] == 1){
                *pts = *pts + 1;
                return isConnected(grid, m, index-m+1, 3, pts, 1);
            }else if(grid[index - m + 1] == 2){
                *pts = *pts - 1;
                //fprintf(stderr, "peke2 at %d\n" , index);
                if (check == 1){
                    *pts = -1;
                }
            }
            break;

        case 4:
            if (flag == 0){
                if(grid[index + m + 1] == 2){
                    *pts = *pts - 1;
                    check = 1;
                }
            }
            if(grid[index - m - 1] == 1){
                *pts = *pts + 1;
                return isConnected(grid, m, index-m-1, 4, pts, 1);
            }else if(grid[index - m - 1] == 2){
                *pts = *pts - 1;
                if (check == 1){
                    *pts = -1;
                }
            }
            break;
    }
    return;
}

P calculatePtsAndRisks(int* grid, int m, node p_mine, node p2){
    P PtsAndRisks = NULL;
    PtsAndRisks = malloc(50);
    int pts = 0;
    int inRow = 0;
    //nt* grid = (int *) malloc(m * m * sizeof(int));
    for(int i =0 ; i < m*m; i ++)
        grid[i] = 0;

    while (p_mine != NULL){
        //fprintf(stderr, "%d\n", p_mine->data);
        grid[p_mine->data] = 1;
        p_mine = p_mine->next;
    }
    while (p2 != NULL){
        //fprintf(stderr, "%d\n", p2->data);
        grid[p2->data] = 2;
        p2 = p2->next;
    }


    fprintf(stderr, "\n\n-------------------------------------------------\n\n");
    display(grid, m);
    fprintf(stderr, "\n-------------------------------------------------\n\n\n");
    
    for(int index = 0; index < m*m; index++){
        if(grid[index] == 1){

            for (int i = 1; i < 5 ; i++){
                inRow = 0;

                isConnected(grid,m, index, i, &inRow, 0);
                if(index == 72){
                    //fprintf(stderr, "INDEX 72, pts; %d in %d direction\n", inRow,i);                    PtsAndRisks->pts = pts;
                    
                }
                //fprintf(stderr, "ptr at index = %d at %d\n", inRow, index);
                if (pts < inRow){
                    pts = inRow;
                    fprintf(stderr, "MAX created ptr at index = %d at %d in %d direction\n", pts, index, i);                    PtsAndRisks->pts = pts;
                    PtsAndRisks->index = index;
                    PtsAndRisks->type = i;
                    PtsAndRisks->pts = pts;
                }else if(pts == inRow){
                    //fprintf(stderr, "MAX created ptr at index = %d at %d in %d direction\n", pts, index, i);
                    if (i > PtsAndRisks->type){
                        //fprintf(stderr, "REPLACE\n");
                        PtsAndRisks->index = index;
                        PtsAndRisks->type = i;
                        PtsAndRisks->pts = pts;
                    }
                    
                }

            }
        }
    }
    fprintf(stderr, "-----------------------------------------\n");
    return PtsAndRisks;
}


P calculatePtsAndRisksx(int* grid, int m, node p_mine, node p2){
    P PtsAndRisks = NULL;
    PtsAndRisks = malloc(50);
    int pts = 0;
    int inRow = 0;
    //nt* grid = (int *) malloc(m * m * sizeof(int));
    for(int i =0 ; i < m*m; i ++)
        grid[i] = 0;

    while (p_mine != NULL){
        //fprintf(stderr, "%d\n", p_mine->data);
        grid[p_mine->data] = 1;
        p_mine = p_mine->next;
    }
    //fprintf(stderr, "--------\n");
    while (p2 != NULL){
        //fprintf(stderr, "%d\n\n", p2->data);
        grid[p2->data] = 2;
        p2 = p2->next;
    }


    //fprintf(stderr, "-------------------------------------------------\n\n");
    //display(grid, m);
    //fprintf(stderr, "-------------------------------------------------\n\n\n");
    
    for(int index = 0; index < m*m; index++){
        if(grid[index] == 1){
            //isConnected(grid,m, index, 1, &inRow);
            //fprintf(stderr, "ptr at index = %d at %d\n", inRow, index);
            for (int i = 1; i < 5 ; i++){
                inRow = 0;

                isConnected(grid,m, index, i, &inRow, 0);
                //fprintf(stderr, "ptr at index = %d at %d\n", inRow, index);
                if (pts < inRow){
                    pts = inRow;
                    //fprintf(stderr, "MAX created ptr at index = %d at %d in %d direction\n", pts, index, i);                    PtsAndRisks->pts = pts;
                    PtsAndRisks->index = index;
                    PtsAndRisks->type = i;
                    PtsAndRisks->pts = pts;
                }else if(pts == inRow){
                    //fprintf(stderr, "MAX created ptr at index = %d at %d in %d direction\n", pts, index, i);
                    if (i > PtsAndRisks->type){
                        //fprintf(stderr, "REPLACE\n");
                        PtsAndRisks->index = index;
                        PtsAndRisks->type = i;
                        PtsAndRisks->pts = pts;
                    }
                    
                }

            }
        }
    }
    //fprintf(stderr, "-----------------------------------------\n");
    return PtsAndRisks;
}

int main(int argc, char **argv) {

    int risk = 0;
    int points = 0;

    node p_mine = NULL;
    node p_opponent = NULL;
    P temp_mine = NULL;
    P temp_opponent = NULL;

    int rank, num_tasks;
    rank = 0;
    num_tasks = 1;

    if (argc != 3) {
        if (rank == 0) {
            fprintf(stderr, "%s <m> <k>\n", argv[0]);
            fprintf(stderr, "Sample program for FIVE IN A ROW\n");
            fprintf(stderr, "<m>: grid dimension (an mxm grid is created)\n");
            exit(1);
        }
    }

    int m, num_steps;
    m = atoi(argv[1]);
    assert(m > 2);
    assert(m <= 10000);

    num_steps = atoi(argv[2]);
    assert(num_steps > 2);
    assert(num_steps <= 10);
    if (rank == 0) {
        fprintf(stderr, "Using m: %d and k: %d\n", m, num_steps);
    }

    /* Linearizing 2D grids to 1D using row-major ordering */
    /* grid[i][j] would be grid[i*n+j] */
    char *grid_output;
    int *grid_next;
    
    grid_output = (char *) malloc(m * m * sizeof(char));
    assert(grid_output != 0);

    grid_next = (int *) malloc(m * m * sizeof(int));
    assert(grid_next != 0);

    /* static initalization, so that we can verify output */
    /* using very simple initialization right now */
    for (int i=0; i<m; i++) {
        for (int j=0; j<m; j++) {
            grid_output[i*m+j] = '*';
            grid_next[i*m+j] = 0;
        }
    }


    for(int i = 0; i < num_steps; i++){
        int insert = 0;
        fprintf(stderr, "\n------------------------------------------------\n");
        fprintf(stderr, "Iteration start\n");
        for(int j = 0; j < 100; j ++){
            //if(grid_next[j] != 0)
                //fprintf(stderr, "TESTING: %d\n", j);
        }
        int opponent = getRandInput(m);
        do{
            opponent = getRandInput(m);
        }while(grid_next[opponent]!=0);
        p_opponent = addNode(p_opponent, opponent);

        fprintf(stderr, "Opponent placed (random) at %d <- Input should be here!\n\n", opponent);

        temp_mine = calculatePtsAndRisksx(grid_next, m, p_mine, p_opponent);
        temp_opponent = calculatePtsAndRisks(grid_next, m, p_opponent, p_mine);
        if(temp_opponent->pts >= 4){
            fprintf(stderr, "User (random) wins\n");
            fprintf(stderr, "Bye\nFinal Output\n");
            break;
        }
        fprintf(stderr, "CHECKPOINT 1 (before my trun) : myPoint %d and Opponent's pts %d\n", temp_mine->pts, temp_opponent->pts);

        if(((temp_mine->pts) > (temp_opponent->pts)) || (1 > (temp_opponent->pts))) {
            //attacking move
            fprintf(stderr, "ATTACKING\n");
            if(temp_mine->pts > 1){

                int flag = 0;
                
                if(temp_mine->type == 1){
                    if((grid_next[temp_mine->index + 1]) == 2){
                        //if the right of right-end is 2 or right of right-end is ob
                        if(grid_next[temp_mine->index - temp_mine->pts - 1] != 2)
                            insert = temp_mine->index - temp_mine->pts - 1;
                        else
                            flag = 1;
                        

                    }else if(grid_next[temp_mine->index - temp_mine->pts - 1] == 2){
                        if(grid_next[temp_mine->index + 1] != 2)
                            insert = temp_mine->index + 1;
                        else
                            flag = 1;
                        
                    }else{
                        if((temp_mine->index % m) > 6)
                            insert = temp_mine->index - temp_mine->pts - 1;
                        else
                            insert = temp_mine->index + 1;
                    }
                }else if(temp_mine->type == 2){
                    if(grid_next[temp_mine->index + m] == 2){
                        if(grid_next[temp_mine->index - m * temp_mine->pts - m] != 2)
                            insert = temp_mine->index - m * temp_mine->pts - m;
                        else
                            flag = 1;
                        
                        
                    }else if(grid_next[temp_mine->index - m * temp_mine->pts - m] == 2){
                        if(grid_next[temp_mine->index + m ] != 2)
                            insert = temp_mine->index + m;
                        else
                            flag = 1;
                        
                    }else{
                        if((temp_mine->index / m) > 6)
                            insert = temp_mine->index - m * temp_mine->pts - m;
                        else
                            insert = temp_mine->index + m;
                        
                    }      
                }else if(temp_mine->type == 3){
                    if(grid_next[temp_mine->index + m - 1] == 2){
                        if(grid_next[temp_mine->index - m * temp_mine->pts + 1 * temp_mine->pts - m +1] != 2)
                            insert = temp_mine->index - m * temp_mine->pts + 1 * temp_mine->pts - m +1;
                        else
                            flag = 1;
                        
                    }else if(grid_next[temp_mine->index - m * temp_mine->pts + 1 * temp_mine->pts - m + 1] == 2){
                        if (grid_next[temp_mine->index + m - 1] != 2)
                            insert = temp_mine->index + m - 1;
                        else
                            flag = 1;
                        
                    }else{
                        if((temp_mine->index > (2* m / 3))&&((temp_mine->index % m )< (m / 3)))
                            insert = temp_mine->index - m * temp_mine->pts + 1 * temp_mine->pts - m +1;
                        else
                            insert = temp_mine->index + m - 1;
                        
                    }
                }else if(temp_mine->type == 4){
                    if(grid_next[temp_mine->index + m + 1] == 2){
                        if(grid_next[temp_mine->index - m * temp_mine->pts - 1 * temp_mine->pts - m - 1] != 2)
                            insert = temp_mine->index - m * temp_mine->pts - 1 * temp_mine->pts - m - 1;
                        else
                            flag = 1;
                        
                    }else if(grid_next[temp_mine->index - m * temp_mine->pts - 1 * temp_mine->pts - m - 1] == 2){
                        if(grid_next[temp_mine->index + m + 1] != 2)
                            insert = temp_mine->index + m + 1;
                        else
                            flag = 1;
                        
                    }else{
                        if((temp_mine->index > (2* m / 3))&&((temp_mine->index % m )> (2* m / 3)))
                            insert = temp_mine->index - m * temp_mine->pts - 1 * temp_mine->pts - m - 1;
                        else
                            insert = temp_mine->index + m + 1;
                    
                    }
                }

                if (flag == 1){

                    int rnd = getRandInput(m);
                    do{
                        rnd = getRandInput(m);
                    }while(grid_next[rnd]!=0);

                    p_mine = addNode(p_mine, rnd);
                    fprintf(stderr, "INSERT INTO %d (RANDOM)\n", rnd);
                }else{
                    p_mine = addNode(p_mine, insert);
                    fprintf(stderr, "INSERT INTO %d\n", insert);
                }


            }else{
                int attack_move = m/4*m + 3;
                do{
                    attack_move++;
                }while(grid_next[attack_move]!=0);
                p_mine = addNode(p_mine, attack_move);
                fprintf(stderr, "INSERT INTO %d\n", attack_move);
            }
        }else{
            int insert_d = 0;
            fprintf(stderr, "DEFENSIVE at %d, attacked by %d type by %d pts\n", temp_opponent->index, temp_opponent->type, temp_opponent->pts);
            if(temp_opponent->type == 1){
                //fprintf(stderr, "L\n");
                if(grid_next[temp_opponent->index + 1] == 2){
                    insert_d =temp_opponent->index - temp_opponent->pts - 1;
                }else if(grid_next[temp_opponent->index - temp_opponent->pts - 1] == 2){
                    insert_d =temp_opponent->index + 1;
                }else{
                    insert_d =temp_opponent->index - temp_opponent->pts - 1;
                }
            }else if(temp_opponent->type == 2){
                //fprintf(stderr, "L\n");
                if(grid_next[temp_opponent->index + m] == 2){
                    insert_d = temp_opponent->index - m * temp_opponent->pts - m;
                }else if(grid_next[temp_opponent->index - m * temp_opponent->pts - m] == 2){
                    insert_d =temp_opponent->index + m;
                }else{
                    insert_d =temp_opponent->index - m * temp_opponent->pts - 1*m;
                }      
            }else if(temp_opponent->type == 3){
                //fprintf(stderr, "L\n");
                if(grid_next[temp_opponent->index + m - 1] == 2){
                    insert_d =temp_opponent->index - m * temp_opponent->pts + 1 * temp_opponent->pts - m +1;
                }else if(grid_next[temp_opponent->index - m * temp_opponent->pts + 1 * temp_opponent->pts] == 2){
                    insert_d =temp_opponent->index + m - 1;
                }else{
                    insert_d =temp_opponent->index - m * temp_opponent->pts + 1 * temp_opponent->pts - m + 1;
                }
            }else if(temp_opponent->type == 4){
                //printf(stderr, "L\n");
                if(grid_next[temp_opponent->index + m + 1] == 2){
                    insert_d =temp_opponent->index - m * temp_opponent->pts - 1 * temp_opponent->pts - m - 1;
                }else if(grid_next[temp_opponent->index - 1 * temp_opponent->pts - 1 * temp_opponent->pts] == 2){
                    insert_d =temp_opponent->index + m + 1;
                }else{
                    insert_d =temp_opponent->index - (m * temp_opponent->pts )- (1 * (temp_opponent->pts))-m-1;
                }
            }

            p_mine = addNode(p_mine, insert_d);
            fprintf(stderr, "Insert %d as a defensive move\n", insert_d);

        }

        fprintf(stderr, "CHECKPOINT 1 (AFTER move) : myPoint %d and Opponent's pts %d\n", (calculatePtsAndRisksx(grid_next, m, p_mine, p_opponent))->pts, (calculatePtsAndRisksx(grid_next, m, p_opponent, p_mine))->pts);
        if((calculatePtsAndRisksx(grid_next, m, p_mine, p_opponent)->pts) >= 4){
            fprintf(stderr, "AI wins\n");
            fprintf(stderr, "Bye\nFinal Output\n");
            break;
        }
    }

    while(p_opponent != NULL){
        grid_output[p_opponent->data] = 'X';
        p_opponent = p_opponent->next;
    }

    while(p_mine != NULL){
        grid_output[p_mine->data] = 'O';
        p_mine = p_mine->next;
    }

    displayx(grid_output, m);
    return 0;
}
