/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
// Copyright 2021 State Key Lab for MIMO communications.
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.09.25
// Module Name      : Noise_Reduction_Exponential_Smoothing
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise performance of a continuous-Time/Analog signal. Signal can be real or
//                  : complex communication signal obtained from time domain devices such as Oscilloscope, Digitizer
//                  : or audio capture devices.
//                  : Notable computation: Exponential Smoothening
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: calc_signal_mean
// Description:
//              Computes the signal average
//
// Function: exponential_smooth_calc
// Description:
//              Computes the exponential smoothing of the signal
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    double calc_signal_mean(double *signal_source_arr, int sig_length);
    void exponential_smooth_calc( double *signal_source_arr,double *sig_output_arr, double mean, int sig_length);

int main()
{
    FILE *fptr1, *fptr2;
    double num;
    int SIG_LENGTH = 0;

     if ((fptr1 = fopen("C:\\Users\\Evandovich\\waveform_input.txt","r")) == NULL){
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
          double MEAN = calc_signal_mean(&INPUT_SIG_ARR[0], SIG_LENGTH);
          exponential_smooth_calc(&INPUT_SIG_ARR[0],&OUTPUT_SIGNAL[0], MEAN, SIG_LENGTH);

            fptr2 = fopen("Exponential_smooth.dat","w");
            for(int i=0; i<SIG_LENGTH; i++)
        {
            fprintf(fptr2,"\n%f",OUTPUT_SIGNAL[i]); // write signal data into created file vertically
        }
         printf("\nSuccess!!! File saved in directory\n");

     fclose(fptr1);
     fclose(fptr2);

        return 0;
}


double calc_signal_mean(double *signal_source_arr, int sig_length)
{
    double _mean = 0.0;
    for (int i =0;i<sig_length;i++)
    {
        _mean = _mean + signal_source_arr[i];

    }
    _mean = _mean/(double)sig_length;
    return _mean;
}


    void exponential_smooth_calc( double *signal_source_arr,double *sig_output_arr, double mean, int sig_length)
{
    const float alpha = 0.3;
    double calc_signal_mean(double *signal_source_arr, int sig_length);
     sig_output_arr[0] = mean;
    for (int i=0;i<sig_length-1;i++)
    {   //Exponential smoothing calculation
        sig_output_arr[i+1]= sig_output_arr[i] + alpha*(signal_source_arr[i]-sig_output_arr[i]);

    }
}

