#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct registro
{
    uint16_t ID;
};
typedef struct registro Registro;
uint16_t extract_segment(uint64_t data, uint64_t start, uint64_t end);
void showIDs(FILE *f, Registro *R);
int Count_IDs(FILE *f);