#include "examen_lib.h"

uint16_t extract_segment(uint64_t data, uint64_t start, uint64_t end) {
    uint64_t mask = ((1 << (end - start + 1)) - 1) << start; // Máscara con unos (1s) en la posición del segmento deseado
    uint64_t segment = (data & mask) >> start;     // Aplicar la máscara y desplazar el segmento al LSB
    return (uint16_t)segment; //Conversión explícita de tipo 
}
int Count_IDs(FILE *f) { //funcion para contar la cantidad de ID y poder hacer la estructura de manera dinamica
    uint64_t camp;
    uint16_t LLDC; // lower level device count
    int count = 0; 
    while (fread(&camp, sizeof(uint64_t), 1, f)) {
        LLDC = extract_segment(camp, 32, 47);
        fseek(f, LLDC * sizeof(uint16_t), SEEK_CUR);
        count++;
    }
    rewind(f); // Reposiciona el puntero del fichero al inicio
    return count;
}

void showIDs(FILE *f, Registro *R){
    uint64_t camp;
    uint16_t LLDC;
    int count=0; 
    while (fread(&camp, sizeof(uint64_t), 1, f)!=0)
    {
        R[count].ID = extract_segment(camp, 48, 63);
        LLDC = extract_segment(camp, 16, 31);
        fseek(f, LLDC*sizeof(uint16_t), SEEK_CUR);
        count++;
    }
    rewind(f);
    printf("\n\n ID's \n\n");
    for (int i = 0; i < count; i++)
    {
        printf("\n ID : %u", R[i].ID);
    }
}