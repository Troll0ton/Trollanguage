//! @file CPU.h

#ifndef   CPU_H
#define   CPU_H

//-----------------------------------------------------------------------------

#include "../include/stack.h"
#include "../include/common.h"
#include <math.h>

//-----------------------------------------------------------------------------

#define Struct Processor
#define Name   Cpu

//-----------------------------------------------------------------------------

enum CPU_INFO
{
    SZ(STACK_INIT) = 2,
};

//-----------------------------------------------------------------------------

enum REG_INFO
{
    N(REGS) = 5,
};

//-----------------------------------------------------------------------------

enum RAM_INFO
{
    SZ(RAM) = 300,
};

//-----------------------------------------------------------------------------

typedef struct Cpu_info
{
    FILE *code_file;
    FILE *file_out;
} Cpu_info;

//-----------------------------------------------------------------------------

typedef struct Processor
{
    Cpu_info Info;
    double  *regs;
    double  *ram;
    char    *code;
    bool     F(STOP);
    int      code_size;
    Stack    Stk;
    Stack    Stk_call;
} Processor;

//-----------------------------------------------------------------------------

int  processor_ctor  (Processor *Cpu);

int  cpu_info_ctor   (Cpu_info *Info);

void processor_dtor  (Processor *Cpu);

void cpu_info_dtor   (Cpu_info *Info);

void read_code_file  (Processor *Cpu);

void handle_cmds     (Processor *Cpu);

bool is_equal        (double a, double b);

void execute_cmd     (int curr_cmd,  double    *curr_arg, double arg_value,
                      int *curr_ptr, Processor *Cpu                        );


void cpu_dump        (Processor *Cpu);

//-----------------------------------------------------------------------------

#endif //CPU_H
