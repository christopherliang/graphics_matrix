#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
    screen s;

    color c;
    c.red = 50;
    c.green = 150;
    c.blue = MAX_COLOR;

    clear_screen(s);

    struct matrix *edges;
    struct matrix *transform;

    edges = new_matrix(4, 1);
    
    add_edge(edges, 0, 0, 0, 10, 20, 0);
    add_edge(edges, 10, 20, 0, 30, 60, 0);
    add_edge(edges, 30, 60, 0, 40, 10, 0);
    add_edge(edges,40,10,0,65,78,0);
    add_edge(edges, 65,78,0, 0, 0, 0);
    
    int i;
    for (i = 0;i < 200; i++) {
        scalar_mult(1.03, edges);
        draw_lines(edges,s,c);
    }
    

    display(s);
    save_extension(s, "matrix.png");

    free_matrix( transform );
    free_matrix( edges );
}  
