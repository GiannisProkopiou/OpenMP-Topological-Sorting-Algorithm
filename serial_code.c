#include "linked_list.c"
#include <string.h>
#include <sys/time.h>


typedef struct graph_node {
    int inc_degree;
    node_t * out_nodes;

} graph_node;



int n_rows, n_columns, n_edges; //number of rows and cols of the matrix and the nodes


void printMatrix(int matrix[][n_columns]) {

    int i, j;

    for(i=0;i<n_rows;i++) {
        for(j=0;j<n_columns;j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


node_t * kahn(graph_node *arr) {
    node_t * S = NULL;

    int i;
    for (i=1;i<=n_columns;i++) {
        if(arr[i].inc_degree == 0) {
          S = push(S, i);
        }
    }

    node_t * L = NULL;


    while(S != NULL) {
        // int last = remove_last(S); // 5 7 
        node_t removed = remove_last(S); // 5 7
        int last = removed.val;
        S = removed.next;

        L = push(L, last); // 3

        node_t * out_node = arr[last].out_nodes;
        while(out_node != NULL)
        {
            arr[out_node->val].inc_degree--;
            if(arr[out_node->val].inc_degree == 0) {
                S = push(S, out_node->val);
            }
            out_node = out_node->next;
        }
    }

    // check for edges
    for(i=1;i<=n_columns;i++) {
        if(arr[i].inc_degree != 0) {
            printf("Has cycle!\n");
            return NULL;
        }
    }

    return L;
}



int main() {

    FILE* f = fopen("dag.txt", "r");

    char *line_buf = NULL;
    size_t line_buf_size = 0;

    getline(&line_buf, &line_buf_size, f);

    while(line_buf[0] == '%') {
        getline(&line_buf, &line_buf_size, f);
    }

    sscanf(line_buf, "%d %d %d", &n_rows, &n_columns, &n_edges);


    graph_node arr[n_columns+1];

    int i;

    for(i=1;i<=n_rows;i++) {
        arr[i] = (graph_node) { .inc_degree = 0, .out_nodes = NULL };
    }

    for(i=1; i<=n_edges; i++) {
        int node_out, node_in;
        fscanf(f, "%d %d\n", &node_out, &node_in);

        arr[node_out].out_nodes = push(arr[node_out].out_nodes, node_in);
        arr[node_in].inc_degree++;
    }

    fclose(f);

    // print_list(S);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    node_t * L = kahn(arr);

    gettimeofday(&end, NULL);


    double delta = (end.tv_sec - start.tv_sec) - (start.tv_usec- end.tv_usec)/1E6;

    printf("%f\n", delta);
    // printMatrix(matrix);


    f = fopen("output.txt", "w");

    while(L != NULL) {
        fprintf(f, "%d\n", L->val);
        L = L->next;
    }

    fclose(f);

    return 0;
}
