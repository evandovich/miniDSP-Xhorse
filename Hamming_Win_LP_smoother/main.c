/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.11.12
// Module Name      : Smoother:Hamming_windowed_LowPass_Filter
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program reduces noise impartation by removing high frequency components
//                  : of a continuous-Time/Analog signal. Signal can be real or complex waveform obtained from
//                  : time domain devices such as Oscilloscope, Digitizer or audio capture devices.
//                  : Notable computation: Hamming Window, Low Pass filter kernel
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: lp_Hamwindow_ftr
// Description:
//               Computers the Hamming windowed low pass Filter kernel
//
// Function: print_statement
// Description:
//              Gets input from the user
//              Computes the normalized cut-off frequency for the Kernel
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    void lp_Hamwindow_ftr(double *sig_source_arr,
                       double *sig_dest_arr,
                       double *fltr_kernel_dest_arr,
                       double cutoff_freq,
                       int filt_length,
                       int input_sig_length);


    double print_statement(double s_rate, double f_cutoff)
{
            double Cut_off_frequency;
            printf("\n Enter Sampling rate of Input Signal : ");
            scanf("%lf",&s_rate);
            printf("\n Enter Filter cut off Frequency : ");
            scanf("%lf",&f_cutoff);

        return Cut_off_frequency = (f_cutoff/(s_rate/2))*0.5;
}

int main()
{
    FILE *fptr1, *fptr2;
    double num;
    double samp_rate = 0;
    double filt_cutoff = 0;
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
          int  IMP_LENGTH = SIG_LENGTH/5;
          double OUTPUT_SIGNAL[SIG_LENGTH-IMP_LENGTH];
          double FILTER_KERNEL[IMP_LENGTH];

          double Cut_off_freq = print_statement(samp_rate,filt_cutoff);
          lp_Hamwindow_ftr(&INPUT_SIG_ARR[0], &OUTPUT_SIGNAL[0], &FILTER_KERNEL[0],Cut_off_freq, IMP_LENGTH, SIG_LENGTH);

        fptr2 = fopen("filtered_signal.dat","w");
        for(int i = 0; i<SIG_LENGTH;i++)
            {
        if(i > IMP_LENGTH){
            fprintf(fptr2,"\n%lf",OUTPUT_SIGNAL[i]);
                }
                }
         printf("\nSuccess!!! File saved in directory\n");

     fclose(fptr1);
     fclose(fptr2);

        return 0;
}



void lp_Hamwindow_ftr(double *sig_source_arr,
                      double *sig_dest_arr,
                      double *fltr_kernel_dest_arr,
                      double cutoff_freq,int filt_length,
                      int input_sig_length
                           )

{
double a = 0.54;
double b = 0.46;   //filter constant parameters

for (int i =0; i<filt_length; i++){
    if(i - filt_length/2 == 0){
        fltr_kernel_dest_arr[i] = 2* M_PI* cutoff_freq;         //M_PI (predefined maths constant (3.14159265359))
    }
    if(i - filt_length /2 != 0){
    fltr_kernel_dest_arr[i] = sin(2*M_PI*cutoff_freq*(i-filt_length/2))/(i-filt_length/2);
    fltr_kernel_dest_arr[i] = fltr_kernel_dest_arr[i]*(a-b*cos(2*M_PI*i/filt_length));   //Hamming windowed
    }
}


//convolve the input signal and filter kernel
for(int j =filt_length; j<input_sig_length; j++)
{
    sig_dest_arr[j] = 0;
    for (int i = 0; i<filt_length;i++){
        sig_dest_arr[j] = sig_dest_arr[j]+ sig_source_arr[j-i]*fltr_kernel_dest_arr[i];
    }
}
}
