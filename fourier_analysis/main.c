/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.08.23
// Module Name      : Signal_fourier_analysis
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program computes the frequency spectrum information of a continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: DFT
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_FILE_NAME 25



//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: dft_signal_calc
// Description:
//              This function obtains a data signal and performs Discrete Fourier Transform
//              i.e. Convert time domain signal to frequency domain signal
//
//////////////////////////////////////////////////////////////////////////////////////////////////
    double INPUT_SIG_ARR[5000];

    void dft_signal_calc(double *signal_source_arr,
                         double *sig_output_real_arr,
                         double *sig_output_imx_arr,
                         int sig_Length
                         );

int main()
{
    FILE *fptr1, *fptr2, *fptr3;
    char filename[MAX_FILE_NAME];
    double num;
    int SIG_LENGTH = 0;

    /* Get file name from user. The file should be either in current folder.
       In case file is in a different destination, complete path should be provided */
    printf("Enter file name: ");
    fgets(filename, 25, stdin);
    filename[strlen(filename)-1] = '\0';

    /* Open the file and Check if file exists  */
    if ((fptr1 = fopen(filename, "r")) == NULL)          //run a statement until a condition is met or true
      {
        printf("\nCould not locate file %s.", filename);
        printf("\nMake sure the file name and destination address is correct");

        return 0;
      }

    printf("File %s loaded successfully\n ",filename);

    while (fscanf(fptr1, "%lf",&num) != EOF)
    {

        INPUT_SIG_ARR[SIG_LENGTH] = num;
        SIG_LENGTH +=1;
    }

    double OUTPUT_REAL[SIG_LENGTH/2];
    double OUTPUT_IMX[SIG_LENGTH/2];

    dft_signal_calc(&INPUT_SIG_ARR[0], &OUTPUT_REAL[0], &OUTPUT_IMX[0], SIG_LENGTH );

     fptr2 = fopen("output_Real_sig.dat", "w");
     fptr3 = fopen("output_Imx_sig.dat", "w");

      for(int i=0;i<SIG_LENGTH/2;i++)
    {
        fprintf(fptr2,"\n%f",OUTPUT_REAL[i]);
        fprintf(fptr3,"\n%f",OUTPUT_IMX[i]);
    }

     fclose(fptr1);
     fclose(fptr2);
     fclose(fptr3);

        return 0;
}

 void dft_signal_calc(double *signal_source_arr, double *sig_output_real_arr, double *sig_output_imx_arr, int sig_Length )
{
    int i,j,k;
    double PI = 3.14159265359;
    for(j = 0; j<sig_Length/2; j++)
    {
        sig_output_real_arr[j] =0;
        sig_output_imx_arr[j] =0;

    }
    // Main DFT algorithm
    for(k = 0;k<sig_Length/2;k++)
    {
        for(i=0;i<sig_Length;i++)
        {
            sig_output_real_arr[k] = sig_output_real_arr[k] + signal_source_arr[i]*cos(2*PI*k*i/sig_Length);
            sig_output_imx_arr[k] = sig_output_imx_arr[k] - signal_source_arr[i]*sin(2*PI*k*i/sig_Length);
        }
    }
}
