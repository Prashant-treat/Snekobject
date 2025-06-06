

##   A Object System in C with Reference Counting Garbase Collector
This project implements a simple object system in C that supports:

* Integers
* Floats
* Strings
* 3D Vectors (`VECTOR3`)
* Arrays

With basic reference-counting memory management and operations like addition (`snek_add`) and length calculation (`snek_length`).

---

###  Files Overview

| File             | Description                                |
| ---------------- | ------------------------------------------ |
| `object.h`       | Header file with type definitions and APIs |
| `object.c`       | Core implementation of the object system   |
| `testobject.c`   | Unit tests and example usage               |
| `testobject.exe` | Compiled Windows executable (if provided)  |

---

### 🔧 How to Compile and Run

Ensure you have `gcc` installed. Then run:

```bash
gcc object.c testobject.c -o testobject
./testobject
```

If you're on Windows with MinGW:

```bash
gcc object.c testobject.c -o testobject.exe
./testobject.exe
```

---

### 📦 Example Output

```
Running test_integer...
Integer value: 10
Running test_float...
Float value: 3.14
Running test_string...
String value: hi
Running test_add_integer...
4 + 6 = 10
Running test_add_string...
abc + def = abcdef
Running test_vector3_add...
Vector3 sum = (5, 7, 9)
Running test_array...
Array[0] = 5, Array[1] = 10

✅ All tests passed successfully!
```

---

### 💡 Features Explained

#### `snek_add(a, b)`

Adds two compatible objects:

* Integer + Integer → Integer
* Integer + Float → Float
* String + String → Concatenated String
* Vector3 + Vector3 → Element-wise added Vector3
* Array + Array → Merged Array

#### `snek_length(obj)`

Returns the "length" of an object:

* Integer / Float → 1
* String → string length
* Array → number of elements
* Vector3 → always 3

#### `snek_array_set` / `snek_array_get`

Set and get elements in arrays, with reference counting handled internally.

#### Reference Counting

Each `snek_object_t` has a `refcount` field:

* `refcount_inc(obj)` increases reference count
* `refcount_dec(obj)` decreases reference count, and frees if zero

### Limitation

1.  Cannot Handle Cyclic References
 The biggest weakness.

    If two (or more) objects reference each other, their refcount never reaches zero — even if they are unreachable from the rest of the program.
```c
snek_object_t *a = new_snek_array(1);
snek_object_t *b = new_snek_array(1);
snek_array_set(a, 0, b);
snek_array_set(b, 0, a);

// refcount of both a and b is 2
// Even if you call refcount_dec(a) and refcount_dec(b), they won’t be freed
```
These form a reference cycle, which reference counting cannot collect.

2. Performance Overhead
Every time an object is assigned, passed, or copied, you must increment/decrement its refcount.

These frequent operations can slow down performance compared to traditional garbage collection, especially in tight loops.

3. Manual Management Required
In C, you have to manually call refcount_inc() and refcount_dec() at the right places.

Forgetting to increment → premature free (use-after-free bug)

Forgetting to decrement → memory leak



---


###  GitHub Setup (Step-by-step)

To publish this project on GitHub:

#### 1. Initialize Git

```bash
git init
```

#### 2. Create `.gitignore`

```bash
echo testobject > .gitignore
echo testobject.exe >> .gitignore
```

#### 3. Commit Your Files

```bash
git add .
git commit -m "Initial commit: SnekObject system with unit tests"
```

#### 4. Create GitHub Repo

Go to [https://github.com/new](https://github.com/new), create a repo (e.g., `snek-object-c`), **don't** initialize with README.

#### 5. Connect and Push

```bash
git remote add origin https://github.com/your-username/snek-object-c.git
git branch -M main
git push -u origin main
```

---

###  Future Improvements

* Add more data types (e.g., Boolean, Map)
* Use Valgrind to track memory leaks
* Integrate with C testing frameworks like [Unity](https://github.com/ThrowTheSwitch/Unity)

---

###  License

MIT License — free to use, modify, and distribute.

---