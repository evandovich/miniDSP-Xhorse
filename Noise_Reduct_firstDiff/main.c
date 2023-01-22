/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.09.05
// Module Name      : Noise_Reduction_First_Difference
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise performance of continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: First Difference
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIGNAL_LENGTH 320                      //define symbol statement to rep signal length


extern double waveform_1kHz_15kHz[SIGNAL_LENGTH];                            // Import signal data
double OUTPUT_SIGNAL[SIGNAL_LENGTH];


//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: first_diff_calc
// Description:
//              Perform First difference computation. Applied as a noise cancellation method
//              Outputs signal in a column-wise format
//////////////////////////////////////////////////////////////////////////////////////////////////
void first_diff_calc( double *signal_source_arr,double *sig_output_arr, int sig_length);

int main()
{
      first_diff_calc( &waveform_1kHz_15kHz[0],&OUTPUT_SIGNAL[0],SIGNAL_LENGTH);


        FILE *input_sig_fileptr, *output_sig_fileptr;

        input_sig_fileptr = fopen("Raw_signal.dat","w"); // 'fopen' open a file if the file exist it opens if not, it will create the file
        output_sig_fileptr = fopen("Differencing_sig.dat","w");

         for(int i=0; i<SIGNAL_LENGTH; i++)
        {
            fprintf(input_sig_fileptr,"\n%f",waveform_1kHz_15kHz[i]); // write signal data to file column-wise
        }


  for(int i=0; i<SIGNAL_LENGTH; i++)
        {
            fprintf(output_sig_fileptr,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }


        printf("\nSuccess!!! File saved in directory\n");

        fclose(input_sig_fileptr);
        fclose(output_sig_fileptr);

         return 0;
}


void first_diff_calc( double *signal_source_arr,double *sig_output_arr, int sig_length)
{
    for (int i=0;i<sig_length;i++)
    {       //First Differencing calculation
        sig_output_arr[i]=signal_source_arr[i]-signal_source_arr[i-1];
    }
}
