#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Device_Type
{
    uint64_t cpu;
    uint64_t sensor;
    uint64_t actuator;
    uint64_t concentrator;
};

struct registro
{
    struct Device_Type device;
    uint64_t ID;
    uint64_t LLDC;
    uint64_t U_L_D_ID;

};
typedef struct registro Registro;
uint64_t extract_segment(uint64_t data, uint64_t start, uint64_t end);
uint16_t extract_segment16(uint64_t data, uint64_t start, uint64_t end);
void showIDs(FILE *f, Registro *R);
int Count_IDs(FILE *f);
int countDevices(FILE *f);
int busqueda_binaria(Registro *R, int size_struct, uint64_t ID)
void getRegister(int *id, Registro *R, int *size_struct);