Ejercicio Práctico 2: Escape Analysis en Lenguaje Go (escape_lab.go) Posteriormente, el estudiante comprobará cómo el compilador de Go gestiona automáticamente la seguridad de memoria y decide si una variable permanece en el Stack o escapa al Heap ejecutando go build gcflags="-m" escape_lab.go (Donovan & Kernighan, 2015):


Al crear cada instancia de SesionTelco (ocupando 16 bytes) mediante la funcion crearSesionEnStack la variable "s" se creo dentro del stack frame de esa funcion

Al return s, Go realiza una copia exacta de los 16 bytes hacia el stack frame de main (asignandolos a s1)

El marco de crearSesionEnStack se limpia, como la referencia de la memoria de "s" nunca salio de la funcion el compilador lo mantiene en el stack.

El marco de crearSesionConEscapeAlHeap antes de compilar Go detecta el operador &s que da una direccion de memoria sin realizar copia entonces se ejecuta el analysis y manda la direccion de memoria donde se guardo la operaccion al heap y haciendo un puntero hacia el mismo para que la funcion main no quede con un puntero invalido o apuntando hacia basura 

esta es la demostracion del escape Analysis de Go es una decision automatica en compilacon, como programador no decides si usar malloc/ free (como en C) ni tampoco tienes que preocuparte por destruir variables locales.

y se ejecuta el garbage collector una vez la variable escapo al heap , este mismo vigila en segundo plano cuando main( ) (o cualquiera otra funcion ) deja de apuntar a esa direccion para liberar esa memoria de forma segura.

manda automaticamente la operacion al heap antes de si quiera compilar 