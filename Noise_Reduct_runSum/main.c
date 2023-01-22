/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.09.05
// Module Name      : Noise_Reduction_Running_Sum
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise performance of continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: Running Sum
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
// Function: calc_running_sum
// Description:
//              Perform Running sum computation. Can be used as a smoothing algorithm
//              Outputs signal in a column-wise format
//////////////////////////////////////////////////////////////////////////////////////////////////
void calc_running_sum( double *signal_source_arr,double *signal_output_arr, int signal_source_length);

int main()
{
      calc_running_sum( &waveform_1kHz_15kHz[0],&OUTPUT_SIGNAL[0],SIGNAL_LENGTH);


        FILE *input_sig_fileptr, *output_sig_fileptr;

        input_sig_fileptr = fopen("Raw_signal.dat","w"); // 'fopen' open a file if the file exist it opens if not, it will create the file
        output_sig_fileptr = fopen("Running_Sum_Smooth_sig.dat","w");

         for(int i=0; i<SIGNAL_LENGTH; i++)
        {
            fprintf(input_sig_fileptr,"\n%f",waveform_1kHz_15kHz[i]); // write signal data to file column-wise
        }
        fclose(input_sig_fileptr);

  for(int i=0; i<SIGNAL_LENGTH; i++)
        {
            fprintf(output_sig_fileptr,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }
        fclose(output_sig_fileptr);

        printf("\nSuccess!!! File saved in directory\n");

         return 0;
}



void calc_running_sum( double *signal_source_arr,double *signal_output_arr, int signal_source_length)
{
    for (int i=0;i<signal_source_length;i++)
    {                //Running sum computation
                     signal_output_arr[i]=signal_source_arr[i]+signal_output_arr[i-1];
    }
}
