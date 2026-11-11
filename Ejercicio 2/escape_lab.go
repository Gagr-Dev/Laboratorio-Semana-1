package main

import "fmt"

type SesionTelco struct {
	ID     uint64 // 8 bytes
	Activa bool   // 1 byte + 7 bytes padding
}

// Esta función mantiene la estructura en el STACK (Copia por valor, 0 presión al Garbage Collector)
func crearSesionEnStack(id uint64) SesionTelco {
	s := SesionTelco{ID: id, Activa: true}
	return s
}

// Esta función retorna un PUNTERO a una variable local.
// En C sería un Dangling Pointer crítico; en Go, el compilador detecta que la referencia "escapa"
// del Stack Frame de la función y la aloja automáticamente en el HEAP ("moved to heap: s").

func crearSesionConEscapeAlHeap(id uint64) *SesionTelco {
	s := SesionTelco{ID: id, Activa: true}
	return &s
}

func main() {
	s1 := crearSesionEnStack(1001)
	s2 := crearSesionConEscapeAlHeap(2002)
	fmt.Printf("Stack ID: %d | Heap ID: %d\n", s1.ID, s2.ID)
}
