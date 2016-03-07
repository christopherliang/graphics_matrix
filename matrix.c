#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
 */
struct matrix *new_matrix(int rows, int cols) {
    double **tmp;
    int i;
    struct matrix *m;

    tmp = (double **)malloc(rows * sizeof(double *));
    for (i=0;i<rows;i++) {
        tmp[i]=(double *)malloc(cols * sizeof(double));
    }

    m=(struct matrix *)malloc(sizeof(struct matrix));
    m->m=tmp;
    m->rows = rows;
    m->cols = cols;
    m->lastcol = 0;

    return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
 */
void free_matrix(struct matrix *m) {

    int i;
    for (i=0;i<m->rows;i++) {
        free(m->m[i]);
    }
    free(m->m);
    free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

    int i;
    for (i=0;i<m->rows;i++) {
        m->m[i] = realloc(m->m[i],newcols*sizeof(double));
    }
    m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
 */
void print_matrix(struct matrix *m) {
    int r,c;
    printf("Matrix Print:\n|");
    for (r = 0;r < m->rows;r++) {
        for (c = 0;c < m->cols;c++) {
            printf("%f ",m->m[r][c]);
        }
        printf("|\n| ");
    }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
 */
void ident(struct matrix *m) {
    int msize = m->cols;
    int r,c;
    for (r = 0; r < msize; r++) {
        for (c = 0; c < msize; c++) {
            if (r == c) {
                m -> m[r][c] = 1;
            } else {
                m -> m[r][c] = 0;                             
            }
        }
    }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
struct matrix *m 
Returns: 

multiply each element of m by x
 */
void scalar_mult(double x, struct matrix *m) {
    int r,c;
    for (r = 0;r < m->rows;r++) {
        for (c = 0;c < m->cols;c++) {
            m -> m[r][c] *= x;
        }
    }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
struct matrix *b 
Returns: 

a*b -> b
 */
void matrix_mult(struct matrix *a, struct matrix *b) {
    struct matrix *ret;
    ret = new_matrix(a->rows, b->lastcol);
    ret -> lastcol = b -> lastcol;
    int common = a->rows;
    int r, c, z;      
    for (c = 0; c < b -> lastcol; b++){
        for (r = 0; r < a -> lastcol; a++){
            int s = 0;
            for(z = 0; z < common; z++){
                s += a -> m[r][z] * b -> m[z][r];
            }
            ret -> m[r][c] = s;
        }
    }
    copy_matrix(ret, b);
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
struct matrix *b 
Returns: 

copy matrix a to matrix b
 */
void copy_matrix(struct matrix *a, struct matrix *b) {

    int r, c;

    for (r=0; r < a->rows; r++) 
        for (c=0; c < a->cols; c++)  
            b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
int y
int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
    struct matrix *t;
    t = new_matrix(4,4);
    ident(t);
    t -> m[0][3] = x;
    t -> m[1][3] = y;
    t -> m[2][3] = z;
    return t;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
int y
int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
    struct matrix *s; 
    s = new_matrix(4,4); 
    ident(s);
    s -> m[0][0] = x;
    s -> m[1][1] = y;
    s -> m[2][2] = z;
    return s;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
    struct matrix *rX; 
    rX = new_matrix(4,4); 
    ident(rX);
    double radius = M_PI * theta / 180;
    rX -> m[1][1] = cos(radius);
    rX -> m[1][2] = -1 * sin(radius);
    rX -> m[2][1] = sin(radius);
    rX -> m[2][2] = cos(radius);
    return rX;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
    struct matrix *rY; 
    rY = new_matrix(4,4); 
    ident(rY);

    double radius = M_PI * theta / 180;
    rY -> m[0][0] = cos(radius);
    rY -> m[0][2] = -1 * sin(radius);
    rY -> m[2][0] = sin(radius);
    rY -> m[2][2] = cos(radius);

    return rY;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
    struct matrix *rZ; 
    rZ = new_matrix(4,4); 
    ident(rZ);

    double radius = theta * M_PI / 180;
    rZ -> m[0][0] = cos(radius);
    rZ -> m[0][1] = -1 * sin(radius);
    rZ->m[1][0] = sin(radius);
    rZ->m[1][1] = cos(radius);

    return rZ;
}
