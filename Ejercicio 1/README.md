# Laboratorio Semana 1

Ejercicio Práctico 1: Inspección de Segmentos Virtuales y Struct Padding en C (lab1_memoria.c) 

El estudiante deberá codificar, compilar sin advertencias mediante el comando gcc -Wall -Wextra -O0 lab1_memoria.c -o lab1_memoria y analizar la salida hexadecimal en consola: 

Durante la realizacion de la prueba tuve ciertos incovenientes con el comando asignado para compilar el archivo lab1_memoria(gcc -Wall -Wextra -O0 lab1_memoria.c -o lab1_memoria), debido a la falta de la instalacion de la herramienta GCC, recurri a instarla pero notaba incovenientes en el editor de codigo (visual studio code) que seguia marcando la herramienta como desconocida, cuando estaba instalada. Asi que opte por otro metodo para el cumplimiento del ejercicio.

Usando la terminal de desarrollo que trae visual studio 2022, compile el archivo y me arrojo el .exe que me arrojaba la salida esperada:

=== 1. AUDITORIA DE SEGMENTOS DE MEMORIA VIRTUAL (x86-64) ===
  [.TEXT] Direccion de la funcion main()           : 00007FF7D96D17AC
  [.DATA] Direccion de version_protocolo           : 00007FF7D96D4010
  [.BSS ] Direccion de contador_paquetes_global    : 00007FF7D96D9080
  [HEAP ] Direccion de bloque_heap_1               : 000001466AC31440
  [HEAP ] Direccion de bloque_heap_2 (crece arriba): 000001466AC31530
  [STACK] Nivel 1 -> Direccion de variable_local_stack: 0000000460DFF64C
  [STACK] Nivel 2 -> Direccion de variable_local_stack: 0000000460DFF60C
  [STACK] Nivel 3 -> Direccion de variable_local_stack: 0000000460DFF5CC

=== 2. AUDITORIA DE ALINEACION Y STRUCT PADDING ===
  Tamano de struct CDR_Desalineado : 32 bytes
  Tamano de struct CDR_Optimizado  : 16 bytes
  Estructuras optimizadas por Cache Line (64B): 4 unidades

  Donde podemos observar que el struct CDR desalineado ocupa mas bytes para hacer la misma operacion debido que al momento de declarar se hizo de manera desorganizada, haciendo que se desperdicie 17 bytes duplicando el uso de memoria y disminuyeno la cantidad de estructuras que entran en el procesador al hacer de 32 bytes y la linea de cache mide 64 bytes (64/32 = 2 ) haciendo que solo quepan 2 estructuras desalineadas.

  En el caso de la estructura alineada debido a que se organizan de una mejor manera permite el desperdicio minimo de bytes ambas estructura estan compuestas por 15bytes pero esta solo desperdicia 1 byte haciendo un mejor uso de la memoria y de la cantidad de estructuras que pueden pasar por la linea de cache (64/16 = 4) duplicando la cantidad de operaciones solo organizando mejor la declaracion de las variables dentro de un struct. 

  es importante el orden en que se declaran las variables dentro de una struct en lenguajes como C,C++,Go , Rust cambia drasticamente el uso de la memoria RAM debido a una restriccion fisica del procesador llamada alineacion de memoria y al relleno automatico que hace el compilador.

  Debido a que no pude hacer la prueba como usted especifico, investigue por que habia fallado para intentar hacerlo de la manera correcta, al momento de instalar GCC la herramienta se instalo correctamente , verifique las variables de entorno y estaba dentro del PATH con su ruta correcta, agregue la ruta de forma manual al visual studio code a traves de la configuracion del JSON y seguia sin funcionar.

  despues de hacer todo esto, la extension run code compilaba el archivo .exe directamente pero no es la manera que lo pidio.

  Probe buscar la ruta del bin de GCC desde la terminal dentro de visual studio code y si la encontro despues de ahi se pueden aplicar el comando dado en el documento de la clase 1 , se compila  y se ejecuta dando el resultado esperado pero al momento de cerra el visual studio y repetir el proceso para compilar vuelve a no reconcoer al GCC.

  La terminal incorporada de visual studio code si reconoce la herramienta si ejecutas un script  para hacer que lea el path de forma manual, pero al momento de reinicar el editor de codigo vuelve a estar en el mismo estado de no reconocer la herramienta.

  El script fue este ($env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User"))

  Desconoco los motivos por que pasa esto, pero habro otro terminal, independiente del visual studio code y si reconoce la herramienta a la primera sin la necesidad de ningun script.


    