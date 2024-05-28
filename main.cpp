#include "examen_lib.h"

int main(){
    FILE *f= fopen("C:\\Users\\arace\\Downloads\\Consignas\\network_structure.dat", "rb");
    if( f == NULL){
        printf("\n Error");
        return -1;
    }
    int count = Count_IDs(f);
    Registro *R = new Registro[count];
    showIDs(f, R);
    rewind(f);
    uint64_t count2 = countDevices(f);
    printf("\n Ingrese un ID: ");
    int id;
    scanf("%d",&id);
    getRegister(id);
    delete []R;
    fclose(f);
}

