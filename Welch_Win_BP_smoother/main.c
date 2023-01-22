/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.12.15
// Module Name      : Smoother:Welch_windowed_Band_Pass_Filter
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program improves signal content by filtering out unwanted frequency components
//                  : of a continuous-Time/Analog signal. Signal can be real or complex waveform obtained from
//                  : time domain devices such as Oscilloscope, Digitizer or audio capture devices.
//                  : Notable computation: Welch Window, Band Pass filter kernel
//
// Revision         : V2.0
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double INPUT_SIG_ARR[5000];

//////////////////////////////////////////////////////////////////////////////////////////////////
// Function: lp_Wel_window_ftr
// Description:
//               Computers the Welch windowed Truncated sinc for Start and Stop band Filter kernel
//
// Function: hp_Wel_window_ftr
// Description:
//              Transforms the Stop band frequency filter to high pass filter
//
// Function: br_Wel_window_ftr
// Description:
//              constructs band reject filter kernel
//
// Function: bp_Wel_window_ftr
// Description:
//              Transform band reject filter kernel to Band Pass
//              Perform Band Pass signal filtration via convolution
//
// Function: print_state_bandpass
// Description:
//              Gets input from the user: Start and Stop band frequencies
//              Computes the normalized cut-off frequency for the Kernel
//
//////////////////////////////////////////////////////////////////////////////////////////////////

    void lp_Wel_window_ftr(double *fltr_kernel_dest_arr, double cutoff_freq, int filt_length);

    void hp_Wel_window_ftr(double *stop_band_dest_arr, int filt_length);

    void br_Wel_window_ftr(double *H_fltr_kernel_dest_arr,
                           double *L_fltr_kernel_dest_arr,
                           double *fltr_kernel_buff_arr,
                           int filt_length);

    void bp_Wel_window_ftr(double *sig_source_arr,
                       double *sig_dest_arr,
                       double *fltr_kernel_buff_arr,
                       int filt_length,
                       int input_sig_length);

void print_state_bandpass(double samp_rate,
                          double filt_cutoff,
                          double high_filt_cutoff,
                          double Cut_off_bin[])
{
            printf("\n Enter Sampling rate of Input Signal : ");
            scanf("%lf",&samp_rate);
            printf("\n Enter Filter Lower cut off Frequency : ");
            scanf("%lf",&filt_cutoff);
            printf("\n Enter Filter High cut off Frequency : ");
            scanf("%lf",&high_filt_cutoff);

            Cut_off_bin[0] = (filt_cutoff/(samp_rate/2))*0.5;
            Cut_off_bin[1] = (high_filt_cutoff/(samp_rate/2))*0.5;
       // return Cut_off_bin;
}

int main()
{
    FILE *fptr1, *fptr2;
    double num;
    double samp_rate = 0;
    double filt_cutoff = 0;
    double high_filt_cutoff = 0;
    double start_stop_freq[2];
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
          double LOW_FREQ_FIL_KERNEL[IMP_LENGTH];
          double HIGH_FREQ_FIL_KERNEL[IMP_LENGTH];
          double FILTER_BUFFER_ARR[IMP_LENGTH];

            printf("\n***********Band Reject Filter******************");
            print_state_bandpass(samp_rate,filt_cutoff, high_filt_cutoff,start_stop_freq );

          lp_Wel_window_ftr(&LOW_FREQ_FIL_KERNEL[0],start_stop_freq[0], IMP_LENGTH);
          lp_Wel_window_ftr(&HIGH_FREQ_FIL_KERNEL[0],start_stop_freq[1], IMP_LENGTH);
          hp_Wel_window_ftr(&HIGH_FREQ_FIL_KERNEL[0], IMP_LENGTH);
          br_Wel_window_ftr(&HIGH_FREQ_FIL_KERNEL[0],&LOW_FREQ_FIL_KERNEL[0], &FILTER_BUFFER_ARR[0], IMP_LENGTH);
          bp_Wel_window_ftr(&INPUT_SIG_ARR[0], &OUTPUT_SIGNAL[0], &FILTER_BUFFER_ARR[0], IMP_LENGTH, SIG_LENGTH);

        fptr2 = fopen("High_Pass_filtered_signal.dat","w");
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



void lp_Wel_window_ftr(double *fltr_kernel_dest_arr, double cutoff_freq, int filt_length)

{
  // Welch windowed filter
for (int i =0; i<filt_length; i++){
    if(i - filt_length/2 == 0){
        fltr_kernel_dest_arr[i] = 2* M_PI* cutoff_freq;         //M_PI (predefined maths constant (3.14159265359))
    }
    if(i - filt_length /2 != 0){
     fltr_kernel_dest_arr[i] = sin(2*M_PI*cutoff_freq*(i-filt_length/2))/(i-filt_length/2);
   fltr_kernel_dest_arr[i] = fltr_kernel_dest_arr[i]*(1-(pow((i-(filt_length /2)/filt_length /2),2)));

    }
}

}

void hp_Wel_window_ftr(double *stop_band_dest_arr, int filt_length)
{

                for (int i = 0; i<filt_length; i++)
                {
                    stop_band_dest_arr[i] = -(stop_band_dest_arr[i]);
                }
                stop_band_dest_arr[filt_length/2] = stop_band_dest_arr[filt_length/2]+1;

                }

void br_Wel_window_ftr(double *H_fltr_kernel_dest_arr,
                      double *L_fltr_kernel_dest_arr,
                      double *fltr_kernel_buff_arr,
                      int filt_length
                      )
{
                    for(int i = 0; i<filt_length;i++){
                    fltr_kernel_buff_arr[i] = L_fltr_kernel_dest_arr[i] + H_fltr_kernel_dest_arr[i] ;//band reject filter kernel
                }

}

void bp_Wel_window_ftr(double *sig_source_arr,
                       double *sig_dest_arr,
                       double *fltr_kernel_buff_arr,
                       int filt_length,
                       int input_sig_length)
{
    //Change band reject filter into bandpass filter using spectral inversion
                for(int i=0; i<filt_length; i++){
                    fltr_kernel_buff_arr[i] = -(fltr_kernel_buff_arr[i]);
                }
                fltr_kernel_buff_arr[filt_length/2] = fltr_kernel_buff_arr[filt_length/2]+1;

                //convolve the input signal and the filter kernel
                for(int j =filt_length;j<input_sig_length;j++){
                    sig_dest_arr[j] = 0;
                    for(int i = 0;i<filt_length;i++){
                        sig_dest_arr[j] = sig_dest_arr[j]+sig_source_arr[j-i]*fltr_kernel_buff_arr[i];
                    }
                }
}
