#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct SnekObject snek_object_t;

typedef struct {
  size_t size;
  snek_object_t **elements;
} snek_array_t;

typedef struct {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
  ARRAY,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
  snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject {
  int refcount;
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
);
snek_object_t *new_snek_array(size_t size);

void refcount_inc(snek_object_t *obj);
void refcount_dec(snek_object_t *obj);
void refcount_free(snek_object_t *obj);

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value);
snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index);
snek_object_t *snek_add(snek_object_t *a, snek_object_t *b);
int snek_length(snek_object_t *obj);


/*
Garbage Collector

As you're painfully aware, we've been manually managing memory throughout this course with our C code. However, Sneklang, the language we're building, has automatic memory management. Specifically, it makes use of a garbage collector.

In C and C++, management of heap memory is done manually with malloc and free (and new and delete in C++).
Rust has a compile-time system that ensures memory safety.
Zig gives the programmer access to "allocators" to manage memory.
These are all examples of "manual memory management" - the programmer has to write code that keeps track of and frees memory.

So What's a Garbage Collector?
A garbage collector is a program (or part of a program) that automatically frees memory that is no longer in use. Languages like Python, Java, JavaScript, OCaml, and even Go use garbage collectors as the code is running to manage memory. It's "automatic memory management". Automatic memory management can be a huge productivity boost for developers (less code, and sometimes fewer memory-related bugs) but it typically comes with a performance cost because, like Forrest Gump, the garbage collector is always running.

It's no coincidence that C, C++, Rust, and Zig are all great choices when you need to squeeze every last drop of performance out of your code.

Refcounting
One of the simplest ways to implement a garbage collector is to use a reference counting algorithm. It goes something like this:

All objects keep track of a reference_count integer.
When that object is referenced, its reference count is incremented.
When an object is garbage collected, the reference count of any object it references is decremented.
When any object's reference count reaches zero, the object is garbage collected.

*/