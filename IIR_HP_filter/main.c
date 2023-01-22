/////////////////////////////////////////////////////////////////////////////////////////////////
// File: MINILITE2.0V_Cprogram.c
//  Copyright 2021 State Key Lab for MIMO communications.
// Author           : Evans Baidoo
// Email            : ebaidoo2@hhu.edu.cn
// Create Date      : 2021.12.27
// Module Name      : Infinite_Impulse_Response_HighPass_filter
// Project Name     : miniDSP Xhorse
// Target Device    :
// Description      : This program improves signal content by filtering out unwanted low frequency components
//                  : of a continuous-Time/Analog signal. Signal can be real or complex waveform obtained from
//                  : time domain devices such as Oscilloscope, Digitizer or audio capture devices.
//                  : Notable computation: IIR single Pole High Pass Filter
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
// Function: recur_high_window_ftr
// Description:
//              This function obtains a data signal and performs single pole IIR HighPass filteration
//
//////////////////////////////////////////////////////////////////////////////////////////////////
    double INPUT_SIG_ARR[5000];

  void recur_high_window_ftr(double *sig_source_arr, double *sig_dest_arr, int input_sig_length);

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

      printf("\n***********Single Pole Recursive High Pass Filter******************");
            recur_high_window_ftr(&INPUT_SIG_ARR[0], &IIR_OUTPUT_SIGNAL[0],SIG_LENGTH);

     fptr2 = fopen("IIR_HighPass_filtered_signal.dat","w");
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

void recur_high_window_ftr(double *sig_source_arr, double *sig_dest_arr, int input_sig_length)
{
    float a0 = 0.93, a1 = -0.93, b1 = 0.85;
    int j;
                 sig_dest_arr[j] = 0;

                    for(j =0;j<input_sig_length;j++){
                        sig_dest_arr[j] = a0*sig_source_arr[j]+a1*sig_source_arr[j-1]+b1*sig_dest_arr[j-1];
                    }

}

