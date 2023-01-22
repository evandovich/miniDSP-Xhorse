/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
// Copyright 2021 State Key Lab for MIMO communications.
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.09.15
// Module Name      : Noise_Reduction_Recursive_Moving_Average
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise performance of a continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: Recursive Moving Average of signal
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: recur_moving_average_calc
// Description:
//              Computes an iterative bin of Moving averages of the signal
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    void recur_moving_average_calc ( double *signal_source_arr,double *sig_output_arr, int sig_length);

int main()
{
    FILE *fptr1, *fptr2;
    double num;
    int SIG_LENGTH = 0;

     if ((fptr1 = fopen("C:\\Users\\Evandovich\\raw_signal.txt","r")) == NULL){
       printf("Error! opening file\n");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
    printf("File loaded successfully\n ");

    while (fscanf(fptr1, "%lf",&num) != EOF)
    {

        INPUT_SIG_ARR[SIG_LENGTH] = num;
        SIG_LENGTH +=1;
    }
          double OUTPUT_SIGNAL[SIG_LENGTH];
          recur_moving_average_calc(&INPUT_SIG_ARR[0],&OUTPUT_SIGNAL[0],SIG_LENGTH);

            fptr2 = fopen("Recur_Moving_avg_sig.dat","w");
            for(int i=0; i<SIG_LENGTH; i++)
        {
            fprintf(fptr2,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }
         printf("\nSuccess!!! File saved in directory\n");

     fclose(fptr1);
     fclose(fptr2);

        return 0;
}


void recur_moving_average_calc ( double *signal_source_arr,double *sig_output_arr, int sig_length)
{
    int bins, p, q, i=0;
    printf("\n\n Enter the number of points for averaging :");
                scanf("%d",&bins);
    p = (bins-1)/2;
    q = p + 1;
    sig_output_arr[i] = 0;
    for (i=0;i<sig_length-p;i++)
    {   // Recursive Moving average filter
        sig_output_arr[i]=sig_output_arr[i-1]+ signal_source_arr[i+p]-signal_source_arr[i-q];
    }
}

