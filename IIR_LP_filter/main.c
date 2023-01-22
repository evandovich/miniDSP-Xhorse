/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.12.27
// Module Name      : Infinite_Impulse_Response_LowPass_filter
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program improves signal content by filtering out unwanted High frequency components
//                  : of a continuous-Time/Analog signal. Signal can be real or complex waveform obtained from
//                  : time domain devices such as Oscilloscope, Digitizer or audio capture devices.
//                  : Notable computation: IIR single Pole Low Pass Filter
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
// Function: recur_window_ftr
// Description:
//              This function obtains a data signal and performs single pole Low PAss IIR filteration
//
//////////////////////////////////////////////////////////////////////////////////////////////////
    double INPUT_SIG_ARR[5000];

  void recur_window_ftr(double *sig_source_arr, double *sig_dest_arr, int input_sig_length);

int main()
{
    FILE *fptr1, *fptr2;
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
        printf("\nMake sure the file name and destination address is correct\n");

        return 0;
      }

    printf("File %s loaded successfully\n ",filename);

    while (fscanf(fptr1, "%lf",&num) != EOF)
    {

        INPUT_SIG_ARR[SIG_LENGTH] = num;
        SIG_LENGTH +=1;
    }
    int  IMP_LENGTH = SIG_LENGTH/5;
    double IIR_OUTPUT_SIGNAL[SIG_LENGTH-IMP_LENGTH];

     printf("\n***********Single Pole Recursive Low Pass Filter******************");
            recur_window_ftr(&INPUT_SIG_ARR[0], &IIR_OUTPUT_SIGNAL[0],SIG_LENGTH);

     fptr2 = fopen("IIR_LowPass_filtered_signal.dat","w");
        for(int i = 0; i<SIG_LENGTH;i++){
        if(i > IMP_LENGTH){
            fprintf(fptr2,"\n%lf",IIR_OUTPUT_SIGNAL[i]);
        }
        }
        printf("\nSuccess!!! File saved in directory\n");

     fclose(fptr1);
     fclose(fptr2);

        return 0;
}

 void recur_window_ftr(double *sig_source_arr, double *sig_dest_arr, int input_sig_length)
{
   const float a0 = 0.15, b1 = 0.85;             // Filter parameters
    int j=0;
                 sig_dest_arr[j] = 0;

                for(j =0;j<input_sig_length;j++){
                     sig_dest_arr[j] = a0*sig_source_arr[j]+b1*sig_dest_arr[j-1];
                    }

}

