#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "object.h"

void test_integer() {
    printf("Running test_integer...\n");
    snek_object_t *a = new_snek_integer(10);
    assert(a != NULL);
    printf("Integer value: %d\n", a->data.v_int);
    assert(snek_length(a) == 1);
    refcount_dec(a);
}

void test_float() {
    printf("Running test_float...\n");
    snek_object_t *a = new_snek_float(3.14f);
    assert(a != NULL);
    printf("Float value: %.2f\n", a->data.v_float);
    assert(snek_length(a) == 1);
    refcount_dec(a);
}

void test_string() {
    printf("Running test_string...\n");
    snek_object_t *a = new_snek_string("hi");
    assert(a != NULL);
    printf("String value: %s\n", a->data.v_string);
    assert(snek_length(a) == 2);
    refcount_dec(a);
}

void test_add_integer() {
    printf("Running test_add_integer...\n");
    snek_object_t *a = new_snek_integer(4);
    snek_object_t *b = new_snek_integer(6);
    snek_object_t *c = snek_add(a, b);
    assert(c != NULL);
    printf("4 + 6 = %d\n", c->data.v_int);
    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_add_string() {
    printf("Running test_add_string...\n");
    snek_object_t *a = new_snek_string("abc");
    snek_object_t *b = new_snek_string("def");
    snek_object_t *c = snek_add(a, b);
    assert(c != NULL);
    printf("abc + def = %s\n", c->data.v_string);
    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_vector3_add() {
    printf("Running test_vector3_add...\n");
    snek_object_t *x1 = new_snek_integer(1);
    snek_object_t *y1 = new_snek_integer(2);
    snek_object_t *z1 = new_snek_integer(3);
    snek_object_t *vec1 = new_snek_vector3(x1, y1, z1);

    snek_object_t *x2 = new_snek_integer(4);
    snek_object_t *y2 = new_snek_integer(5);
    snek_object_t *z2 = new_snek_integer(6);
    snek_object_t *vec2 = new_snek_vector3(x2, y2, z2);

    snek_object_t *sum = snek_add(vec1, vec2);
    assert(sum != NULL);
    printf("Vector3 sum = (%d, %d, %d)\n",
           sum->data.v_vector3.x->data.v_int,
           sum->data.v_vector3.y->data.v_int,
           sum->data.v_vector3.z->data.v_int);

    refcount_dec(vec1);
    refcount_dec(vec2);
    refcount_dec(sum);
}

void test_array() {
    printf("Running test_array...\n");
    snek_object_t *array = new_snek_array(2);
    snek_object_t *v1 = new_snek_integer(5);
    snek_object_t *v2 = new_snek_integer(10);

    assert(snek_array_set(array, 0, v1));
    assert(snek_array_set(array, 1, v2));

    snek_object_t *get1 = snek_array_get(array, 0);
    snek_object_t *get2 = snek_array_get(array, 1);

    printf("Array[0] = %d, Array[1] = %d\n", get1->data.v_int, get2->data.v_int);
    assert(snek_length(array) == 2);

    refcount_dec(array);
    refcount_dec(v1); // decrement if not consumed fully
    refcount_dec(v2);
}

int main() {
    test_integer();
    test_float();
    test_string();
    test_add_integer();
    test_add_string();
    test_vector3_add();
    test_array();
    printf("\n✅ All tests passed successfully!\n");
    return 0;
}
