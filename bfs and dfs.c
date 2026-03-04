#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int M_left;    
    int C_left;    
    int boat;      
    int depth;
} State;

typedef struct Node {
    State state;
    struct Node* parent;
} Node;

Node* queue[MAX];
int front = 0, rear = 0;


int visited[4][4][2];


int moves[5][2] = {
    {2,0},{0,2},{1,1},{1,0},{0,1}
};

// ---------------- BFS Queue Operations ----------------
void enqueue(Node* n) { queue[rear++] = n; }
Node* dequeue() { return queue[front++]; }
int isEmpty() { return front == rear; }


int isValid(State s) {
    if (s.M_left < 0 || s.M_left > 3 || s.C_left < 0 || s.C_left > 3) return 0;

    int M_right = 3 - s.M_left;
    int C_right = 3 - s.C_left;

    if ((s.M_left > 0 && s.M_left < s.C_left)) return 0;
    if ((M_right > 0 && M_right < C_right)) return 0;
    return 1;
}


int isGoal(State s) {
    return (s.M_left == 0 && s.C_left == 0 && s.boat == 1);
}


void printSolution(Node* n) {
    if (n == NULL) return;
    printSolution(n->parent);
    printf("M_left=%d, C_left=%d, Boat=%s\n",
           n->state.M_left, n->state.C_left,
           n->state.boat ? "Right" : "Left");
}

// ---------------- BFS Implementation ----------------
void BFS() {
    printf("\nBFS Solution:\n");

       for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
            for(int k=0;k<=1;k++)
                visited[i][j][k] = 0;

    Node* start = (Node*)malloc(sizeof(Node));
    start->state.M_left = 3;
    start->state.C_left = 3;
    start->state.boat = 0;
    start->parent = NULL;

    enqueue(start);
    visited[3][3][0] = 1;

    while(!isEmpty()) {
        Node* current = dequeue();

        if(isGoal(current->state)) {
            printSolution(current);
            printf("Goal found by BFS!\n");
            return;
        }

        for(int i=0;i<5;i++) {
            State next = current->state;

            if(current->state.boat == 0) { 
                next.M_left -= moves[i][0];
                next.C_left -= moves[i][1];
                next.boat = 1;
            } else { 
                next.M_left += moves[i][0];
                next.C_left += moves[i][1];
                next.boat = 0;
            }

            if(isValid(next) && !visited[next.M_left][next.C_left][next.boat]) {
                Node* child = (Node*)malloc(sizeof(Node));
                child->state = next;
                child->parent = current;
                enqueue(child);
                visited[next.M_left][next.C_left][next.boat] = 1;
            }
        }
    }
}

// ---------------- DFS Implementation ----------------
int dfsFound = 0;
void DFSUtil(Node* n) {
    if(dfsFound) return;

    if(isGoal(n->state)) {
        printSolution(n);
        printf("Goal found by DFS!\n");
        dfsFound = 1;
        return;
    }

    for(int i=0;i<5;i++) {
        State next = n->state;

        if(n->state.boat == 0) { 
            next.M_left -= moves[i][0];
            next.C_left -= moves[i][1];
            next.boat = 1;
        } else { 
            next.M_left += moves[i][0];
            next.C_left += moves[i][1];
            next.boat = 0;
        }

        if(isValid(next) && !visited[next.M_left][next.C_left][next.boat]) {
            Node* child = (Node*)malloc(sizeof(Node));
            child->state = next;
            child->parent = n;
            visited[next.M_left][next.C_left][next.boat] = 1;
            DFSUtil(child);
        }
    }
}

void DFS() {
    printf("\nDFS Solution:\n");


    for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
            for(int k=0;k<=1;k++)
                visited[i][j][k] = 0;

    dfsFound = 0;
    Node* start = (Node*)malloc(sizeof(Node));
    start->state.M_left = 3;
    start->state.C_left = 3;
    start->state.boat = 0;
    start->parent = NULL;

    visited[3][3][0] = 1;
    DFSUtil(start);
}


int main() {
    BFS();
    DFS();
    return 0;
}