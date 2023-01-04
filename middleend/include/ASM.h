//! @file ASM.h

#ifndef   ASM_H
#define   ASM_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/stack.h"
#include "../include/common.h"

//-----------------------------------------------------------------------------

#define lscan(...) sscanf (Asm->Cur_line.begin_line, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define SUCCESS_READ 1
#define EMPTY_LINE   0

//-----------------------------------------------------------------------------

enum CMD_INFO
{
    N(SUPPORTED_CMD) = 19,
    LM(MAX_LEN)      = 20,
};

//-----------------------------------------------------------------------------

enum LABEL_INFO
{
    SZ(LABEL_INIT)   = 50,
    SG(LABEL_OFFSET) = 1,
    PAR_INCREASE     = 40,
};

//-----------------------------------------------------------------------------

typedef struct Asm_info
{
    FILE   *file_in;
    FILE   *code_file;
    int     code_signature;
    bool    double_pass;
} Asm_info;

//-----------------------------------------------------------------------------

typedef struct Command
{
    bool  flag; // is_label
    int   mask;
    int   code;
} Command;

//-----------------------------------------------------------------------------

typedef struct Argument
{
    bool   flag; //
    double value; // union value {
                //   double d_value;
                //   int i_value;
                //   }
    char   reg_sym;
    int    amount;
} Argument;

//-----------------------------------------------------------------------------

typedef struct Code_array
{
    char *array;
    int   size;
    int   capacity;

    FILE *dmp_file;
} Code_array;

//-----------------------------------------------------------------------------

typedef struct Label_array
{
    int *array;
    int  size;
    int  capacity;

    FILE *dmp_file;
} Label_array;

//-----------------------------------------------------------------------------

typedef struct Assembler
{
    Asm_info    Info;
    Line        Cur_line;
    int         cur_pos;
    int         offset;
    Code_array  Code;
    Label_array Label;
} Assembler;

//-----------------------------------------------------------------------------

int  assembler_ctor (Assembler *Asm);

int  asm_info_ctor  (Asm_info *Info);

void assembling     (Assembler *Asm);

void parse_text     (Assembler *Asm, Line *Text, File *File_input);

void parse_line     (Assembler *Asm, Command *Cmd, Argument *Arg);

void parse_label    (Assembler *Asm, Argument *Arg);

void search_label   (Assembler *Asm, Argument *Arg);

void parse_cmd      (Assembler *Asm, Command *Cmd, Argument *Arg);

void parse_arg      (Assembler *Asm, Command *Cmd, Argument *Arg);

void write_in_code  (Assembler *Asm, Command Cmd,  Argument Arg);

void write_in_arg   (Assembler *Asm, Command Cmd,  Argument Arg);

void write_in_label (Assembler *Asm, Argument Arg);

void assembler_dtor (Assembler *Asm);

void asm_info_dtor  (Asm_info * Info);

void write_res_sums (Assembler *Asm);

void asm_dump       (Assembler *Asm);

//-----------------------------------------------------------------------------

#endif //ASM_H
