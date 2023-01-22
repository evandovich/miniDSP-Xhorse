/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.09.15
// Module Name      : Noise_Reduction_Moving_Average
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise performance of a continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: Moving Average of signal
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: moving_average_calc
// Description:
//              Computes a fixed bin of Moving average of the signal
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    void moving_average_calc( double *signal_source_arr,double *sig_output_arr, int sig_length);

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
          moving_average_calc(&INPUT_SIG_ARR[0],&OUTPUT_SIGNAL[0],SIG_LENGTH);

            fptr2 = fopen("Moving_average_sig.dat","w");
            for(int i=0; i<SIG_LENGTH; i++)
        {
            fprintf(fptr2,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }
         printf("\nSuccess!!! File saved in directory\n");

     fclose(fptr1);
     fclose(fptr2);

        return 0;
}

//Moving Average smoothing calculation: Five point
void moving_average_calc( double *signal_source_arr,double *sig_output_arr, int sig_length)
{
    int points = 5;
    for (int i=0;i<sig_length-points;i++)
    {       //Moving Average smoothing calculation: Five point
        sig_output_arr[i]=(signal_source_arr[i]+signal_source_arr[i+1]+signal_source_arr[i+2]+ signal_source_arr[i+3]+ signal_source_arr[i+4])/points;
    }
}

