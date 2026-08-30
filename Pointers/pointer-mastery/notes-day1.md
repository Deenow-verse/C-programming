# Day 1 – Pointers Foundation

## 1.1 Memory and Variables

Computer memory is a sequence of bytes.  
Each byte has an integer address that increases sequentially.

You can think of memory as a giant array of bytes.  
The number that identifies a byte is its **address**.

Not every type uses only 1 byte — use `sizeof` to find out how many bytes a type occupies on *this* system.

### Important memory facts
- When a type needs more than one byte, those bytes are always adjacent.
- The order of those bytes (endianness) is platform-dependent:
  - Little-endian (most common today): least-significant byte first
  - Big-endian: most-significant byte first
- C does not guarantee a particular endianness, so write code that doesn’t depend on it when possible.

### What is a pointer?
A pointer is a variable that stores an **address**.

- You have a normal variable that holds a value.
- That value lives at some address in memory.
- A pointer variable can hold that address.
- The pointer does **not** hold the value itself — it tells you *where* to find the value.

To get the address of a variable → use the address-of operator `&`.  
To print a pointer → use `%p` and cast to `(void *)`.

### Experiments done
- `print-pointer.c` → prints value + address of an `int`
- `data-type_system-mem_alocated.c` → prints `sizeof` for all common types

## 1.2 Pointer Types

To declare a pointer, write the type, then an asterisk, then the variable name:

```c
int *p;          // p is a pointer to int
The asterisk tells the compiler that this variable will hold an address, not a normal value.
To store an address in a pointer you use the address-of operator &:

int i = 10;
int *p;
p = &i;      // p now holds the address of i

Important rule: the pointer and the variable whose address you take must be of the same type.

### Experiments done

- `pointer_declaration_and_assignment.c` → declaring a pointer and assigning it
