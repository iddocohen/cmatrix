#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* The value one want to store in the matrix.
 * I believe you mentioned you wanted double based values but in theory you could put anything here and it will compile accordingly.
*/

#define SCALER double

/*
Storing it as a flat array of size 16. It will look the following:

A 4x4 matrix
      | 0    1    2   3 |
mat = | 4    5    6   7 |
      | 8    9   10  11 |
      | 12   13  14  15 |

For example, mat[5] will return value 5 from the above array.

*/
typedef struct mat4 {
	SCALER mat[16];
} mat4;


/*  Init matrix via memset. 
 */
void mat4Init(mat4* out) 
{
	memset(out->mat, 0, sizeof(SCALER) * 16);
}


/* Multiplication of two matrixs.
 * As we store everything as a flat array it is easy to do now multiplication of two matrixs. .
 * I also believe it is the fastest way possible.
 */ 
void mat4Multiply(mat4* out, const mat4* M1, const mat4* M2)
{
	SCALER mat[16];

	const SCALER *m1 = M1->mat, *m2 = M2->mat;

	mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];


	memcpy(out->mat, mat, sizeof(SCALER)*16);
}

/* Copy matrix into another matrix 
 *
 */

void mat4Copy(mat4* out, const mat4* in)
{
	assert(out != in && "You have tried to self-assign!!");

	memcpy(out->mat, in->mat, sizeof(SCALER)*16);
}

/* Checking Matrix if it is equal to identity. 
 * As it is flat array, it is easy to do and is fast.
 */

int mat4IsIdentity(const mat4* in) 
{
	SCALER identity [] = { 	1.0f, 0.0f, 0.0f, 0.0f,
	                        0.0f, 1.0f, 0.0f, 0.0f,
	                        0.0f, 0.0f, 1.0f, 0.0f,
	                        0.0f, 0.0f, 0.0f, 1.0f
                         };

	return (memcmp(identity, in->mat, sizeof(SCALER) * 16) == 0);
}

/* Alter value of Matrix in a given position.
 */

void mat4AddValueByPos(mat4 *out, int row, int col, SCALER value)
{
   out->mat[(row * 4) + col] = value;
}

/* Alter value of Matrix when flat.
 */

void mat4AddValueByIndex(mat4 *out, int index, SCALER value)
{
   out->mat[index] = value;
}

/* Printing matrix in a "known" format.
 */

void mat4Print(mat4* out)
{
    for (int z = 0; z < 4; ++z) {
        for (int x = 0; x < 4; ++x) {
            printf("[%d,%d]=%f ", z, x, out->mat[(z*4) + x]);
        }
        printf("\n");
    }
}

int main (void) 
{
    // Creating new matrix
    mat4 m1;

    // Init the new matrix with 0
    mat4Init(&m1);   

    // Buffer for getline
    char *line = NULL;
    size_t size;

    // Creating a token array to split the string in given tokens.
    char tokens[] = " ,";

    // The first command to check for.
    char command[] = "newMatrix";

    if (getline(&line, &size, stdin) > -1) {
        
        // Spliting the string in tokens to check each.
        char *pch = strtok(line,tokens);    

        int i = 0;
        while (pch != NULL) {
            // Checking if first token of the string is the right command
            if (i == 0 && strcmp(pch,command) != 0) {
               printf("First command is not right\n");
               return 1;
            } else {
               // TODO: Not checking if pch can really be converted to a given SCALER. Even worse, I assuming it is a float here. Needs to be done a bit better.
               mat4AddValueByIndex(&m1, i-1,atof(pch));
            }
            i++;
            pch = strtok(NULL, tokens);
        } 
        free(pch);
    }
    free(line);
    mat4Print(&m1);
    return 0;
}

int exampleCheckingMathAbove (void) 
{
    mat4 m1;
    mat4Init(&m1);   

    /* Creating a identity matrix to double check the math above.
	     |  1   0   0   0 |
	 M = |  0   1   0   0 |
	     |  0   0   1   0 |
	     |  0   0   0   1 |
	*/
    mat4AddValueByPos(&m1, 0, 0, 1.0f); 
    mat4AddValueByPos(&m1, 1, 1, 1.0f); 
    mat4AddValueByPos(&m1, 2, 2, 1.0f); 
    mat4AddValueByPos(&m1, 3, 3, 1.0f); 

    if (mat4IsIdentity(&m1)) {
        printf("Got it\n");
    } else {
        printf("Not Identity\n");
    }   

    mat4Print(&m1);
    return 0;
}
