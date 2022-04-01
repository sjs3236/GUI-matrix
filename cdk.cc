/*
 * Filename            cdk.cc
 * Date                11/22/2020
 * Author             Junsik Seo
 * Email              jxs161930@utdallas.edu
 * Version             1.0
 * Copyright           2020, All Rights Reserved
 *
 * Description:
 *
 *      Build and display a small text based GUI matrix using curses
 *      and the CDK. It takes vector striong from binio function
 */

#include <iostream>
#include <vector>
#include "cdk.h"
#include "header.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contetns"

using namespace std;

vector<string> binio();

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // CDK uses offset 1 and C/C++ use offset 0.  Therefore, we create one more 
  // slot than necessary and ignore the value at location 0.
  const char 		*rowTitles[MATRIX_ROWS+1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_COLS+1] = {"IGNORE", "a", "b", "c"};
  int		colWidths[MATRIX_COLS+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_COLS+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  vector<string> result=binio();
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, result[0].c_str());
  setCDKMatrixCell(myMatrix, 1, 2, result[1].c_str());
  setCDKMatrixCell(myMatrix, 1, 3, result[2].c_str());
  setCDKMatrixCell(myMatrix, 2, 1, result[3].c_str());
  setCDKMatrixCell(myMatrix, 2, 2, result[4].c_str());
  setCDKMatrixCell(myMatrix, 3, 1, result[5].c_str());
  setCDKMatrixCell(myMatrix, 3, 2, result[6].c_str());
  setCDKMatrixCell(myMatrix, 4, 1, result[7].c_str());
  setCDKMatrixCell(myMatrix, 4, 2, result[8].c_str());
  setCDKMatrixCell(myMatrix, 5, 1, result[9].c_str());
  setCDKMatrixCell(myMatrix, 5, 2, result[10].c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */


  char exit_key;
    cin>>exit_key;
  // Cleanup screen
  endCDK();
}
