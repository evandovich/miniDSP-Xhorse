/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.10.22
// Module Name      : Signal_Amplifier
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program performs amplification of continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: Signal Amplification
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIGNAL_LENGTH 320                      //define symbol statement to rep signal length


extern double waveform_1kHz_15kHz[SIGNAL_LENGTH];                            // Import signal data
int  IMP_LENGTH = SIGNAL_LENGTH/5;




//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: linear_amp
// Description:
//              Performs amplification of signal
//              Outputs signal in a column-wise format
//////////////////////////////////////////////////////////////////////////////////////////////////
void linear_amp(double *signal_source_arr,
                     double *signal_output_arr,
                     double *imp_response_arr,
                     int sig_Length,
                     double attn_amp_fac);

int main()
{

        FILE *input_sig_fileptr, *output_ampsig_fileptr;
        double OUTPUT_SIGNAL[SIGNAL_LENGTH+IMP_LENGTH];
        double AMP_RESPONSE[IMP_LENGTH];
        double amp_per;
        double amp_val;

        printf("\n Enter signal Amplification percentage : ");
            scanf("%lf",&amp_per);
            amp_val = (amp_per/100)+1;

        linear_amp(&waveform_1kHz_15kHz[0], &OUTPUT_SIGNAL[0], &AMP_RESPONSE[0],SIGNAL_LENGTH, amp_val);

        input_sig_fileptr = fopen("Raw_signal.dat","w");
        output_ampsig_fileptr = fopen("Amplified_signal.dat","w");

         for(int i=0; i<SIGNAL_LENGTH; i++)
        {
            fprintf(input_sig_fileptr,"\n%f",waveform_1kHz_15kHz[i]);
        }

       for(int i=0; i<SIGNAL_LENGTH+IMP_LENGTH; i++)
        {
            fprintf(output_ampsig_fileptr,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }

        fclose(input_sig_fileptr);
        fclose(output_ampsig_fileptr);

        printf("\nSuccess!!! File saved in directory\n");

         return 0;
}



void linear_amp( double *signal_source_arr,
                      double *signal_output_arr,
                      double *imp_response_arr,
                      int sig_Length,
                      double attn_amp_fac)
{
    //signal amplification via convolution
    int i,j,imp_respnse_length;
    imp_respnse_length = sig_Length/5;

    for (int k=0;k<imp_respnse_length;k++)
        {
            imp_response_arr[k] = 0;
            if (k == 1)
            {
                imp_response_arr[k] = attn_amp_fac;

            }

        }

    for (i=0;i<sig_Length+imp_respnse_length;i++)
    {
        signal_output_arr[i] =0;
    }
    for (i=0;i<sig_Length;i++)
    {
        for (j=0;j<imp_respnse_length;j++)
        {
            signal_output_arr[i+j] += signal_source_arr[i]*imp_response_arr[j];
        }
    }
}
