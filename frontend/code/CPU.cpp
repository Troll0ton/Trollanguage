#include "../include/CPU.h"

//-----------------------------------------------------------------------------

int main (int argc, char *argv[])
{
    Processor Cpu = { 0 };

    if(processor_ctor (&Cpu) == E(CTOR))
    {
        return E(CPU);
    }

    read_code_file (&Cpu);

    cpu_dump (&Cpu);

    handle_cmds (&Cpu);

    processor_dtor (&Cpu);

    return 0;
}

//-----------------------------------------------------------------------------

int processor_ctor (Processor *Cpu)
{
    Cpu->Info = { 0 };

    Cpu->Stk = { 0 };
    stack_ctor (&Cpu->Stk, SZ(STACK_INIT));

    Cpu->Stk_call = { 0 };
    stack_ctor (&Cpu->Stk_call, SZ(STACK_INIT));

    Cpu->regs = (double*) calloc (N(REGS), sizeof (double));
    Cpu->ram  = (double*) calloc (SZ(RAM), sizeof (double));

    if(Cpu->regs == NULL || Cpu->ram == NULL)
    {
        return E(CTOR);
    }

    return (cpu_info_ctor (&Cpu->Info));
}

//-----------------------------------------------------------------------------

int cpu_info_ctor (Cpu_info *Info)
{
    Info->code_file = fopen ("../files/code.bin",   "rb");
    Info->file_out  = fopen ("../dump/log.txt",     "w+");

    if(Info->code_file == NULL ||
       Info->file_out  == NULL   )
    {
        return E(CTOR);
    }

    return 0;
}

//-----------------------------------------------------------------------------

void processor_dtor (Processor *Cpu)
{
    stack_dtor (&Cpu->Stk);
    stack_dtor (&Cpu->Stk_call);

    free (Cpu->regs);
    free (Cpu->ram);
    free (Cpu->code);

    cpu_info_dtor (&Cpu->Info);
}

//-----------------------------------------------------------------------------

void cpu_info_dtor (Cpu_info *Info)
{
    fclose (Info->code_file);
    fclose (Info->file_out);
}

//-----------------------------------------------------------------------------

void read_code_file (Processor *Cpu)
{
    double code_signature = 0;
    double res_sum        = 0;

    fread (&res_sum,        sizeof(char), ARG_OFFSET, Cpu->Info.code_file);
    fread (&code_signature, sizeof(char), ARG_OFFSET, Cpu->Info.code_file);

    Cpu->code_size = res_sum;

    if(code_signature == SIGNATURE)
    {
        Cpu->code = (char*) calloc (Cpu->code_size, sizeof (char));

        *(elem_t*)(Cpu->code) = res_sum;
        *(elem_t*)(Cpu->code + ARG_OFFSET) = code_signature;

        if(Cpu->code == NULL)
        {
            printf ("__________|ERROR - NULL pointer code|__________\n");
        }

        fread (Cpu->code + SG(CODE_OFFSET), sizeof(char), Cpu->code_size - SG(CODE_OFFSET), Cpu->Info.code_file);
    }

    else
    {
        printf ("__________|WRONG SIGNATURE!|__________\n");
    }
}

//-----------------------------------------------------------------------------

//

void handle_cmds (Processor *Cpu)
{
    for(int curr_pos = 2 * ARG_OFFSET; curr_pos < Cpu->code_size; curr_pos++)
    {
        int     curr_cmd   = Cpu->code[curr_pos];
        int     offset     = 0;
        double  pop_value  = 0;
        double  arg_value  = 0;
        double *curr_arg   = &pop_value;

        if(curr_cmd & MASK_REG)
        {
            curr_arg = Cpu->regs + (int) *(elem_t*)(Cpu->code + curr_pos + CMD_OFFSET);
            arg_value += *curr_arg;

            offset += ARG_OFFSET;
        }

        if(curr_cmd & MASK_IMM)
        {
            curr_arg = (elem_t*)(Cpu->code + curr_pos + offset + CMD_OFFSET);
            arg_value += *curr_arg;

            offset += ARG_OFFSET;
        }

        if(curr_cmd & MASK_RAM)
        {
            curr_arg = Cpu->ram + (int) arg_value;
            arg_value = *curr_arg;
        }

        curr_pos += offset;

        execute_cmd (curr_cmd, curr_arg, arg_value, &curr_pos, Cpu);

        if(Cpu->F(STOP)) break;
    }
}

//-----------------------------------------------------------------------------

bool is_equal (double a, double b)
{
    const double EPS = 1e-1;

    return (a - b < EPS && a - b > -EPS);
}

//-----------------------------------------------------------------------------

void execute_cmd (int curr_cmd,  double    *curr_arg, double arg_value,
                  int *curr_ptr, Processor *Cpu                        )
{
    int curr_pos = *curr_ptr;

    curr_cmd &= MASK_CMD;

    #define CMD_DEF(cmd, name, code, ...) \
        case cmd:                         \
        {                                 \
            code                          \
            __VA_ARGS__                   \
            break;                        \
        }

    switch(curr_cmd)
    {
        #include "../include/codegen.h"

        default:
            printf ("?%d \n", curr_cmd);
            break;
    }

    #undef CMD_DEF

    stack_dumps (&Cpu->Stk, Cpu->Info.file_out);

    *curr_ptr = curr_pos;
}

//-----------------------------------------------------------------------------

void cpu_dump (Processor *Cpu)
{
    FILE *code_dmp_file = fopen ("../dump/code_cpu_dump.txt", "w+");

    fprintf (code_dmp_file, "%d - size, %x - signature\n", (int) *(elem_t*)(Cpu->code + 0),
                                                           (int) *(elem_t*)(Cpu->code + ARG_OFFSET));
    int i = 1;

    for(int curr_pos = SG(CODE_OFFSET); curr_pos < Cpu->code_size; curr_pos++)
    {
        char curr_cmd = Cpu->code[curr_pos];
        int  offset   = 0;

        fprintf (code_dmp_file, "%06d || %d\n", i++, (int) Cpu->code[curr_pos]);

        if(curr_cmd & MASK_REG)
        {
            fprintf (code_dmp_file, "%06d || %lg\n", i++, *(elem_t*)(Cpu->code + curr_pos + CMD_OFFSET));

            offset += ARG_OFFSET;
        }

        if(curr_cmd & MASK_IMM)
        {
            fprintf (code_dmp_file, "%06d || %lg\n", i++, *(elem_t*)(Cpu->code + curr_pos + CMD_OFFSET + offset));

            offset += ARG_OFFSET;
        }

        curr_pos += offset;
    }

    fclose (code_dmp_file);
}

//-----------------------------------------------------------------------------
