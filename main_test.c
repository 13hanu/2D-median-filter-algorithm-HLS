
#include <stdio.h>
#include "MedianFilter.h"
//#include "MedianFilter.c"



void CSV_Import(IMG_ARR_T Image_with_Noise, char filename[]) {
  // open file
  FILE *Import_Data;
  Import_Data = fopen(filename, "r");

  // check file opened
  if (Import_Data == NULL) {
    return;
  }

  int temp = 0;
  for (int i = 0; i < IMAGE_ROWS; i++) {
    for (int j = 0; j < IMAGE_COLUMNS; j++) {
      fscanf(Import_Data, "%d,", &temp);
      Image_with_Noise[i][j] = temp;
    }
    // move to next line
    fscanf(Import_Data, "\n");
  }
  fclose(Import_Data);
}

void Validate_output(IMG_ARR_T Actual, IMG_ARR_T Expected) {
  int no_of_mismatches = 0;
  for (int i_row = 0; i_row < IMAGE_ROWS; i_row++) {
    for (int j_col = 0; j_col < IMAGE_COLUMNS; j_col++) {
      if (Actual[i_row][j_col] != Expected[i_row][j_col]) {
        printf("\n Mismatch Act[%d][%d] = %d Vs Exp[%d][%d] = %d", i_row, j_col,
               Actual[i_row][j_col], i_row, j_col, Expected[i_row][j_col]);
        no_of_mismatches++;
      } else {
      }
    }
  }
  if (no_of_mismatches == 0) {
    printf("\n Validation success b/w Actual Vs Expected\n");
  } else {
    printf("\n [Error] Validation unsuccessfull, no. of mismatches = %d\n",
           no_of_mismatches);
  }
}

IMG_ARR_T Image_with_Noise;
IMG_ARR_T Clean_Image;

int main() {

  IMG_ARR_T Filtered_Image;

  CSV_Import(Image_with_Noise, "noisy.csv");
  CSV_Import(Clean_Image, "clean.csv");

  TwoD_MedianFilter(Image_with_Noise, Filtered_Image);
  Validate_output(Filtered_Image, Clean_Image);
}
