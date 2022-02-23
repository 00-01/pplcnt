#ifdef SILENT
    #define PRINTF(...) ((void) 0)
#else
    #define PRINTF printf
#endif  /* DEBUG */

#define STACK_SIZE           (1024*6) //This is for PE0   (Master)
#define SLAVE_STACK_SIZE     (1024) //This is for PE1-7 (Slaves)

#define MAX_OUT_BB 30
#define NON_MAX_THRES 70
#define MAX_BB 10

#define SCORE_THR (FIX2FP(0.73,7))