#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "nmglobal.h"
#include "nbench_mt.h"
#include "hardware.h"

#define MAX_FUNC 9

int g_func_index = 0;
double g_itercount_array[9];
char * func_name [] = {
    "NUMERIC SORT",      //INT
    "FP EMULATION",      //INT
    "IDEA",              //INT
    "HUFFMAN",           //INT
    "FOURIER",           //FLOAT
    "LU DECOMPOSITION",  //FLOAT
    "STRING SORT",       //MEM
    "BITFIELD",          //MEM
    "ASSIGNMENT",        //MEM
};


void load(void* arg) 
{
    (*funcpointer[g_func_index])(arg);
}

void run_threads(int count, int time);
void calculate_index();

int main(int argc, char * argv[])
{
    int i=0;
    int count = 1;
    int duration_per_algorithm = 30; //default 30 second
    int func_to_run = -1;
    if (argc >= 3) {
        count = atoi(argv[1]);
        duration_per_algorithm = atoi(argv[2]);
        if (argc > 3) {
            func_to_run = atoi(argv[3]);
            if (!(func_to_run>=0 && func_to_run<MAX_FUNC)) {
                fprintf(stderr, "Specified algorithm should be in 0~%d\n", MAX_FUNC-1);
                fprintf(stderr, "Usage: %s [thread count] [duration per algorithm] {specified algorithm 0~%d}\n", argv[0], MAX_FUNC-1);
                return 1;
            }
        }
    }
    else
    {
        fprintf(stderr, "Invalid parameters\n");
        fprintf(stderr, "Usage: %s [thread count] [duration per algorithm] {specified algorithm 0~%d}\n", argv[0], MAX_FUNC-1);
        return 1;
    }

    //print header
    fprintf(stderr, "=====================  Benchmark  ======================\n");
    fprintf(stderr, "%-20s: %d\n", "Number of Threads", count);
    fprintf(stderr, "---------------------  Progress   ----------------------\n");
    fprintf(stderr, "%-20s: %-16s: %-16s\n", "Algorithm", "Iterations/sec", "Time Elapse");
    fprintf(stderr, "--------------------------------------------------------\n");
    //begin to run test
    if (func_to_run>=0 && func_to_run<MAX_FUNC) {
        g_func_index = func_to_run;
        run_threads(count, duration_per_algorithm);
    } else {
        for (i=0; i<MAX_FUNC; i++) {
            g_func_index = i;
            run_threads(count, duration_per_algorithm);
        }
        calculate_index();
    }
    //print CPU info
    fprintf(stderr, "--------------------- CPU INFO -------------------------\n");
    hardware(0, NULL);

    fprintf(stderr, "========================================================\n\n");

    return 0;
}

void run_threads(int count, int time)
{
    int i = 0;
    pthread_t *t = NULL;
    LoadStruct *s = NULL;
    t = (pthread_t *)malloc(sizeof(pthread_t)*count);
    s = (LoadStruct*)malloc(sizeof(LoadStruct)*count);  
    //set parameters to algorithm methods
    for(i=0; i<count; i++)
    {
        LoadStruct* p = s+i;
        p->request_secs=time;
        p->adjust = 1; //don't do adjustment
        p->itercount= 0;
        //"DoNumSort",   
        if (g_func_index == 0)
        {
            p->arraysize=NUMARRAYSIZE;
            p->numarrays = 1;
            p->loops = 2;
        }
        //"DoEmFloat",   
        else if (g_func_index == 1)
        {
            p->arraysize=EMFARRAYSIZE;;
            p->numarrays = 1024;
            p->loops = 2;
        }
        //"DoIDEA",      
        else if (g_func_index == 2)
        {
            p->arraysize=IDEAARRAYSIZE;
            p->numarrays = 200L;
            p->loops = 2;
        }
        //"DoHuffman",   
        else if (g_func_index == 3)
        {
            p->arraysize=HUFFARRAYSIZE;
            p->numarrays = 200L;
            p->loops = 100L;
        }
        //"DoFourier",   
        else if (g_func_index == 4)
        {
            p->arraysize=811L;
            p->numarrays = 200L;
            p->loops = 2;
        }
        else if (g_func_index == 5)
        {
            p->numarrays = 10L;
        }
        //"DoStringSort",
        else if (g_func_index == 6)
        {
            p->arraysize=STRINGARRAYSIZE;
            p->numarrays = 1;
            p->loops = 2;
        }
        //"DoBitops",    
        else if (g_func_index == 7)
        {
            p->arraysize=1000L;
            //p->numarrays = 1000L;
            p->loops = 2;
        }
        //"DoAssign",    
        else if (g_func_index == 8)
        {
            p->arraysize=811;
            p->numarrays = 100L;
            p->loops = 2;
        }
    }

    ulong elapsed;          /* Elapsed ticks */
    elapsed = StartStopwatch();

    for(i=0; i<count; i++)
    {
        if (0 != pthread_create(t+i, NULL, load, (void*)(s+i)))
        {
            printf("error!!\n");
            return -1;
        }
    }
    for (i=0; i<count; i++)
    {
        pthread_join(*(t+i), NULL);
    }
    elapsed = StopStopwatch(elapsed);
    double sum = 0.0;
    for (i=0; i<count; i++)
    {
        LoadStruct* p = s+i;
        sum += p->itercount;
    }
    g_itercount_array[g_func_index] = sum/(elapsed*1.0/1000000);
    fprintf(stderr, "%-20s: %16.3f: %16.3f\n", func_name[g_func_index], sum/(elapsed*1.0/1000000), elapsed*1.0/1000000);
    free(t);
    free(s);
}


void calculate_index()
{
    double int_index = 1.0;
    double fp_index = 1.0;
    double mem_index = 1.0;
    double overall_index = 1.0;
    int i = 0;
    

    for (i = 0; i<MAX_FUNC; i++) {
        if (i>=0 && i<=3)
        {
            int_index = int_index*(g_itercount_array[i]/lx_bindex[i]);
        }
        else if (i>=4 && i<=5)
        {
            fp_index = fp_index*(g_itercount_array[i]/lx_bindex[i]);
        }
        else
        {
            mem_index = mem_index*(g_itercount_array[i]/lx_bindex[i]);
        }
        overall_index = overall_index*(g_itercount_array[i]/lx_bindex[i]);
    }
    fprintf(stderr, "----------------------   INDEX   -----------------------\n");
    fprintf(stderr, "%-20s: %16.3f\n", "INTEGER INDEX", pow(int_index, (double)1.0/4));
    fprintf(stderr, "%-20s: %16.3f\n", "FLOATING-POINT INDEX", pow(fp_index, (double)1.0/2));
    fprintf(stderr, "%-20s: %16.3f\n", "MEMORY INDEX", pow(mem_index, (double)1.0/3));
    fprintf(stderr, "%-20s: %16.3f\n", "OVERALL INDEX", pow(overall_index, (double)1.0/9));
}
