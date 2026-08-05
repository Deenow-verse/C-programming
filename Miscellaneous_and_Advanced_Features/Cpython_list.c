#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define Py_INCREF(obj) ((obj)->refcnt++)
#define Py_DECREF(obj) do { \
    if (--((obj)->refcnt) == 0) { \
        printf("Garbage Collector: Freeing object!\n"); \
        free(obj); \
    } \
} while(0)

typedef enum { PY_INT, PY_FLOAT, PY_STRING } PyType;

struct PyObject;

typedef struct PyObject
{
    int refcnt;
    PyType type;
    void (*print)(struct PyObject*);
    union
    {
        int i_val;
        float f_val;
        char *s_val;
    } data;

} PyObject;

typedef struct
{
    size_t size;
    size_t allocated;
    PyObject **items;   
} PyList;

void printInt(PyObject *obj);
void printFloat(PyObject *obj);
void printChar (PyObject *obj);
PyList *pylist ();
void PyList_Append (PyList *list, PyObject *obj);
void PyList_Insert(PyList *list, int index, PyObject *obj);
void PyList_Pop(PyList *list, int index);
void PyList_Free(PyList *list);

int exit_status;

int main (void)
{
    PyList *my_list = PyList_New();

    PyObject *num1 = malloc(sizeof(PyObject));
    num1->refcnt = 1; 
    num1->type = PY_INT;
    num1->data.i_val = 42;
    num1->print = printInt; 

    printf("Testing print function directly: ");
    num1->print(num1);

    Py_DECREF(num1); 

    PyList_Append(my_list, num1);
    
    free(my_list);
    return 0;
} 

void printInt(PyObject *obj)
{
    printf("%d\n", obj->data.i_val);
}

void printFloat(PyObject *obj)
{
    printf("%f\n", obj->data.f_val);
}

void printChar (PyObject *obj)
{
    printf("%s\n", obj->data.s_val);
}

PyList *PyList_New()
{
    PyList *list = malloc(sizeof(PyList));
    if (list == NULL) return NULL;
    
    list->size = 0;
    list->allocated = 0;
    list->items = NULL;
    
    return list;
}

void PyList_Append (PyList *list, PyObject *obj)
{
    size_t newsize, new_allocated;
    newsize = list -> size + 1;

    if (list -> size == list -> allocated)
    {
        new_allocated = (newsize >> 3) + (newsize < 9 ? 3 : 6) + newsize;
        PyObject **temp = realloc(list->items, new_allocated * sizeof(PyObject *));

        if (temp == NULL)
        {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }

        list -> items = temp;
        list -> allocated = new_allocated;
                       
    }

    list->items[list->size] = obj;
    list->size = newsize;
        
    Py_INCREF(obj);
}

void PyList_Insert(PyList *list, int index, PyObject *obj)
{
    void *memmove(void *newlist, const void *list, size_t n);
}

void PyList_Pop(PyList *list, int index)
{
    Py_DECREF(*obj); 
}

void PyList_Free(PyList *list)
{
    while (list != NULL)
    {
        free(list);
    }

    free (PyList);
}