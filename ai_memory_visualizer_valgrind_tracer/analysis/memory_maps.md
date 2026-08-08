# Memory Analysis and Visualizations

## Overview
This document presents a step-by-step low-level analysis of memory layout, stack and heap lifetimes, pointer aliasing, and memory errors for the C programs in the `programs/` directory.

---

## 1. Stack Memory Analysis (`stack_example.c`)

### Overview & Execution Context
The program `stack_example.c` demonstrates recursive function calls and the dynamics of stack frames. The `main` function invokes `walk_stack(0, 3)`.

### Stack Frame Lifecycle & Memory Layout
1. **`main()` Frame:**
   - Occupies the base of the stack.
   - Contains return addresses and frame pointer linkage.

2. **`walk_stack(depth, max_depth)` Frames:**
   - Each recursive call creates a new stack frame on top of the call stack.
   - For `walk_stack(0, 3)`, frames are allocated sequentially for `depth = 0, 1, 2, 3` (4 frames active simultaneously at maximum depth).
   - Local variable `marker` is allocated inside each `walk_stack` frame.
   - Stack memory addresses grow downwards towards lower memory addresses on x86_64 architecture as new frames are pushed.

3. **`dump_frame(label, depth)` Frames:**
   - Called twice per `walk_stack` iteration: once upon entry (`"enter"`) and once upon exit (`"exit"`).
   - Local variables allocated within `dump_frame`:
     - `local_int` (4 bytes, integer)
     - `local_buf` (16 bytes, character array)
     - `p_local` (8 bytes pointer, initialized to `&local_int`)

### Lifetime Analysis
- **Scope & Lifetime:** `local_int`, `local_buf`, and `p_local` are bound to the execution scope of `dump_frame`.
- **Frame Deallocation:** When `dump_frame` returns, its stack frame is popped by restoring the stack pointer (`RSP`). The memory is marked as deallocated/invalid for the program's logical state, but the physical bits remain unchanged until overwritten by subsequent function calls (stack reuse).

---

## 2. Heap Memory & Lifetime Analysis (`heap_example.c`)

### Dynamic Allocation Layout
The program dynamically allocates structure instances and string buffers on the heap using `malloc`.

1. **`alice = person_new("Alice", 30);`**
   - Allocation 1: `sizeof(Person)` (16 bytes: 8 bytes for `char *name` pointer, 4 bytes for `int age`, plus padding).
   - Allocation 2: `len + 1` bytes (6 bytes for `"Alice "`).
   - `alice->name` points to Allocation 2.

2. **`bob = person_new("Bob", 41);`**
   - Allocation 3: `sizeof(Person)` for Bob's structure.
   - Allocation 4: 4 bytes for `"Bob "`.
   - `bob->name` points to Allocation 4.

### Deallocation & Ownership Analysis
- **Correct Deallocation (`bob`):**
  ```c
  free(bob->name); // Frees the heap string buffer (Allocation 4)
  free(bob);       // Frees the structure container (Allocation 3)
  ```
  Both allocated heap blocks owned by `bob` are explicitly returned to the heap allocator.

- **Partial Deallocation / Memory Leak (`alice`):**
  ```c
  person_free_partial(alice); // Calls free(alice) directly
  ```
  `person_free_partial` only calls `free(p)`, which releases the structure block (Allocation 1). The dynamically allocated string buffer `"Alice "` (Allocation 2) pointed to by `alice->name` remains allocated on the heap. Because the structure containing the pointer `alice->name` was freed, the address of Allocation 2 is permanently lost. This constitutes a **Direct Memory Leak**.

---

## 3. Pointer Aliasing & Use-After-Free (`aliasing_example.c`)

### Aliasing Setup
```c
a = make_numbers(n); // Allocates dynamic array of 5 integers on heap
b = a;               // Pointer Aliasing: 'b' holds the exact memory address as 'a'
```
Both `a` and `b` point to the exact same starting address in heap memory (`a == b`).

### Use-After-Free Mechanics
```c
free(a); // Deallocates heap chunk
```
1. `free(a)` notifies the C runtime heap allocator that the memory block at address `a` is available for reuse.
2. `free(a)` **does not** clear or nullify the pointer variable `a`, nor does it modify `b`.
3. Both `a` and `b` become **Dangling Pointers** holding a non-NULL memory address that no longer represents a valid, owned heap allocation.

### Invalid Memory Access
```c
printf(" reading b[2]=%d\n", b[2]); // Read Use-After-Free
b[3] = 1234;                        // Write Use-After-Free
```
Accessing `b[2]` or writing to `b[3]` accesses heap memory that has been freed. This triggers an **Invalid Read / Invalid Write** condition leading to **Undefined Behavior (UB)**.

---

## 4. AI Explanation Critical Evaluation & Corrections

### Case Study: AI Misconception on Use-After-Free & Stack Frame Cleanup

During automated memory analysis generation by an LLM assistant, two distinct inaccuracies were identified:

#### Inaccuracy 1: Guaranteed Immediate Crash on Use-After-Free
- **AI Statement:** *"Executing `b[2]` after `free(a)` will cause the OS to immediately crash the program with a Segmentation Fault because `b` points to invalid memory."*
- **Correction:** In C standard specification, reading or writing through a dangling pointer is **Undefined Behavior (UB)**, not a guaranteed deterministic crash. Heap allocators do not immediately unmap memory pages back to the kernel upon small `free()` calls. Thus, `b[2]` often reads stale data or garbage without crashing. Claiming a guaranteed crash confuses low-level OS page fault mechanics with C memory safety rules.

#### Inaccuracy 2: Memory Erasure on Stack Return
- **AI Statement:** *"When `dump_frame` exits, all its local variables (`local_int`, `local_buf`) are zeroed out and erased from RAM."*
- **Correction:** Exiting a function only adjusts the stack pointer register (`RSP/ESP`). The data previously stored in that stack frame remains intact in physical RAM until overwritten by future stack allocations. It is marked logically invalid, not zeroed out or erased.
