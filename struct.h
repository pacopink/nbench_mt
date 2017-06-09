
typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* # of seconds requested */
        double sortspersec;     /* # of sort iterations per sec */
        ushort numarrays;       /* # of arrays */
        ulong arraysize;        /* # of elements in array */
} SortStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* # of seconds requested */
        double bitopspersec;    /* # of bitfield ops per sec */
        ulong bitoparraysize;           /* Total # of bitfield ops */
        ulong bitfieldarraysize;        /* Bit field array size */
} BitOpStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* # of seconds requested */
        ulong arraysize;        /* Size of array */
        ulong loops;            /* Loops per iterations */
        double emflops;         /* Results */
} EmFloatStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* # of requested seconds */
        ulong arraysize;        /* Size of coeff. arrays */
        double fflops;          /* Results */
} FourierStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong numarrays;        /* # of arrays */
        double iterspersec;     /* Results */
} AssignStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong arraysize;        /* Size of array */
        ulong loops;            /* # of times to convert */
        double iterspersec;     /* Results */
} IDEAStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong arraysize;        /* Size of array */
        ulong loops;            /* # of times to compress/decompress */
        double iterspersec;     /* Results */
} HuffStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong loops;            /* # of times to learn */
        double iterspersec;     /* Results */
} NNetStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong numarrays;        /* # of arrays */
        double iterspersec;     /* Results */
} LUStruct;

typedef struct {
        int adjust;             /* Set adjust code */
        ulong request_secs;     /* Requested # of seconds */
        ulong numarrays;        /* # of arrays */
        ulong arraysize;
        ulong loops;
        ulong itercount;     /* Results */
} LoadStruct;

