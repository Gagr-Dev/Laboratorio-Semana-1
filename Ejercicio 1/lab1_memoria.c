#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Variable Global Inicializada -> Segmento .data
int version_protocolo = 5;

// Variable Global No Inicializada -> Segmento .bss
long contador_paquetes_global;

// 1, Demostracion de Desalineación vs Alineacion de Memoria (Cache Lines de 64 bytes)
struct CDR_Desalineado
{
    char codigo_pais;        // 1 byte + 7 bytes padding
    int64_t __timestamp__ns; // 8 bytes
    char estado_llamada;     // 1 byte + 3 bytes padding
    int32_t duracion_seg;    // 4 bytes
    char tipo_celda;         // 1 byte + 7 bytes padding
}; // total esperados 32 bytes

struct CDR_Optimizado
{
    int64_t timestanp_ns; // 8 bytes (offset 0..7)
    int32_t duracion_seg; // 4 bytes (offset 8..11)
    char codigo_pais;     // 1 byte  (offset 12)
    char estado_llamada;  // 1 byte  (offset 13)
    char tipo_celda;      // 1 byte  (offset 14) + 1 byte padding (offset 15)
};

void inspeccionar_stack(int nivel_recursion)
{
    int variable_local_stack = nivel_recursion * 10;
    printf("  [STACK] Nivel %d -> Direccion de variable_local_stack: %p\n", nivel_recursion, (void *)&variable_local_stack);
    if (nivel_recursion < 3)
    {
        inspeccionar_stack(nivel_recursion + 1);
    }
}
int main(void)
{
    printf("=== 1. AUDITORIA DE SEGMENTOS DE MEMORIA VIRTUAL (x86-64) ===\n");
    printf("  [.TEXT] Direccion de la funcion main()           : %p\n", (void *)main);
    printf("  [.DATA] Direccion de version_protocolo           : %p\n", (void *)&version_protocolo);
    printf("  [.BSS ] Direccion de contador_paquetes_global    : %p\n", (void *)&contador_paquetes_global);
    int64_t *bloque_heap_1 = (int64_t *)malloc(sizeof(int64_t) * 4);
    int64_t *bloque_heap_2 = (int64_t *)malloc(sizeof(int64_t) * 4);
    printf("  [HEAP ] Direccion de bloque_heap_1               : %p\n", (void *)bloque_heap_1);
    printf("  [HEAP ] Direccion de bloque_heap_2 (crece arriba): %p\n", (void *)bloque_heap_2);
    inspeccionar_stack(1);
    printf("\n=== 2. AUDITORIA DE ALINEACION Y STRUCT PADDING ===\n");
    printf("  Tamano de struct CDR_Desalineado : %zu bytes\n", sizeof(struct CDR_Desalineado));
    printf("  Tamano de struct CDR_Optimizado  : %zu bytes\n", sizeof(struct CDR_Optimizado));
    printf("  Estructuras optimizadas por Cache Line (64B): %zu unidades\n", 64 / sizeof(struct CDR_Optimizado));
    free(bloque_heap_1);
    free(bloque_heap_2);
    return 0;
}
