/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
// Copyright 2021 State Key Lab for MIMO communications.
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.10.12
// Module Name      : Signal_Restoration_by_Inverse_Discrete_Fourier_Transform
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise and performs signal information restoration in the frequency spectrum
//                  : of a continuous-Time/Analog signal. Signal can be real or complex waveform obtained from
//                  : time domain devices such as Oscilloscope, Digitizer or audio capture devices.
//                  : Notable computation: Inverse Discrete Fourier Transform
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: dft_signal_calc
// Description:
//              Transforms the signal from time domain to frequency domain
//
// Function: exponential_smooth_calc
// Description:
//              Computes the exponential smoothing of the signal
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    void dft_signal_calc(double *signal_source_arr,
                         double *sig_output_real_arr,
                         double *sig_output_imx_arr,
                         int sig_Length );

    void idft_sig_restore_calc(double *idft_output_arr,
                               double *sig_input_real_arr,
                               double *sig_input_imx_arr,
                               int sig_Length );

int main()
{
    FILE *fptr1, *fptr2;
    double num;
    int SIG_LENGTH = 0;

     if ((fptr1 = fopen("C:\\Users\\Evandovich\\Desktop\\White_Noise.txt","r")) == NULL){
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
          double OUTPUT_REAL[SIG_LENGTH/2];
          double OUTPUT_IMX[SIG_LENGTH/2];
          dft_signal_calc(&INPUT_SIG_ARR[0], &OUTPUT_REAL[0], &OUTPUT_IMX[0], SIG_LENGTH );
          idft_sig_restore_calc(&OUTPUT_SIGNAL[0], &OUTPUT_REAL[0], &OUTPUT_IMX[0], SIG_LENGTH );

            fptr2 = fopen("Signal_Restoration.dat","w");
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


void idft_sig_restore_calc(double *idft_output_arr, double *sig_input_real_arr, double *sig_input_imx_arr, int sig_Length )
{
    int i,j,amp;
    double PI = 3.14159265359;

     printf("\n\n Enter the Noise Amplitude (Hz) to cut-off :");
                scanf("%d",&amp);
        //signal restoration
        for(int jj = 0; jj<sig_Length/2; jj++)
        {
            if(sig_input_real_arr[jj]<amp)
            {
               sig_input_real_arr[jj] = 0;
            }
            if(sig_input_imx_arr[jj]<amp)
            {
               sig_input_imx_arr[jj] = 0;
            }

        }

    for(j = 0; j<sig_Length/2; j++)
        {
            sig_input_real_arr[j] = sig_input_real_arr[j]/(sig_Length/2);
            sig_input_imx_arr[j] = -sig_input_imx_arr[j]/(sig_Length/2);
        }
     sig_input_real_arr[0]= sig_input_real_arr[0]/2;
     sig_input_imx_arr[0] = -sig_input_imx_arr[0]/2;

       for(i = 0;i<sig_Length;i++)
    {
         idft_output_arr[i]=0;

    }
    for(int k=0;k<sig_Length/2;k++)
    {
        for (i=0;i<sig_Length;i++)
       {        //  IDFT
            idft_output_arr[i] = idft_output_arr[i] + sig_input_real_arr[k]*cos(2*PI*k*i/sig_Length);
            idft_output_arr[i] = idft_output_arr[i] + sig_input_imx_arr[k]*sin(2*PI*k*i/sig_Length);
        }
    }

}
