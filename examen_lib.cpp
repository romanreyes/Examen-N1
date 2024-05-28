#include "examen_lib.h"

uint64_t extract_segment(uint64_t data, uint64_t start, uint64_t end) {
    uint64_t mask = ((1 << (end - start + 1)) - 1) << start; // Máscara con unos (1s) en la posición del segmento deseado
    uint64_t segment = (data & mask) >> start;     // Aplicar la máscara y desplazar el segmento al LSB
    return segment;
}
uint16_t extract_segment16(uint64_t data, uint64_t start, uint64_t end) {
    uint64_t mask = ((1 << (end - start + 1)) - 1) << start; // Máscara con unos (1s) en la posición del segmento deseado
    uint64_t segment = (data & mask) >> start;     // Aplicar la máscara y desplazar el segmento al LSB
    return (uint16_t)segment; //Conversión explícita de tipo 
}

int Count_IDs(FILE *f) { //funcion para contar la cantidad de ID y poder hacer la estructura de manera dinamica
    uint64_t camp;
    uint16_t LLDC; // lower level device count
    int count = 0; 
    while (fread(&camp, sizeof(uint64_t), 1, f)) {
        LLDC = extract_segment16(camp, 32, 47);
        fseek(f, LLDC * sizeof(uint16_t), SEEK_CUR);
        count++;
    }
    rewind(f); // Reposiciona el puntero del fichero al inicio
    return count;
}

void showIDs(FILE *f, Registro *R){
    uint64_t camp;
    uint64_t LLDC;
    int count=0; 
    while (fread(&camp, sizeof(uint64_t), 1, f))
    {
        R[count].ID = extract_segment16(camp, 48, 63);
        LLDC = extract_segment16(camp, 16, 31);
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

int countDevices(FILE *f){
    uint64_t device_count=0;
    uint64_t camp;
    uint64_t div;
    uint16_t LLDC;
    while (fread(&camp, sizeof(uint64_t), 1, f)){
        div = extract_segment(camp, 24, 25);
        LLDC = extract_segment(camp, 32, 47);
        if( div == 0 || div==3){
            device_count+= (uint64_t)LLDC;
        }
        fseek(f, LLDC*sizeof(uint16_t), SEEK_CUR); 
    }
    rewind(f);
    return device_count;
}

int busqueda_binaria(Registro *R, int size_struct, uint64_t ID) {
    int left = 0;
    int right = size_struct - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (R[mid].ID == ID) {
            return mid;
        } else if (R[mid].ID > ID) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1; // ID no encontrado
}
void llenar_struct(Registro *R){
    int count =0;
    uint64_t camp;
    uint64_t LLDL;
    uint64_t Device_Type;
    uint64_t info; //solo lo voy a usar para saltar
    uint64_t upper_level;
    while (fread(&camp, sizeof(uint64_t), 1, f)){
        R[].LLDC= extract_segment16(camp, 32, 47);
    }
    
};

void getRegister(int id, Registro *R, int size_struct){
    int count = busqueda_binaria(R, size_struct, id);
}

}