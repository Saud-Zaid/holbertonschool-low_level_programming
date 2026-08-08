# Task 3: Peer Review Readiness Checklist & Verification Report

## 1. Submission Overview & Verification Matrix

| Checklist Domain | Verification Criteria | Location in Repo | Status |
| :--- | :--- | :--- | :--- |
| **Memory Model Understanding** | Stack vs. Heap lifetimes, lifetime expiration, and ownership responsibility explicitly defined. | `analysis/valgrind_analysis.md`<br>`analysis/crash_report.md` | **Verified** |
| **Pointer & Aliasing Reasoning** | Multiple references to same block, dangling pointers, and use-after-free states identified. | `analysis/valgrind_analysis.md` (Section 3) | **Verified** |
| **Valgrind Interpretation** | Mapped specific Valgrind errors (Invalid Read, Definitely Lost, Invalid Write) to lines of code and state transitions. | `analysis/valgrind_analysis.md` (Sections 2 & 3) | **Verified** |
| **Crash Root Cause Explanation** | Deterministic stack frame unwinding explained without circular reasoning ("crashes due to segfault"). | `analysis/crash_report.md` (Section 2) | **Verified** |
| **Critical AI Evaluation** | Documented specific AI hallucinations/misconceptions and provided low-level corrections. | `analysis/valgrind_analysis.md` (Section 4)<br>`analysis/crash_report.md` (Section 3) | **Verified** |

---

## 2. Peer Review Summary Statements

### A. Stack vs. Heap Memory Model
* **Stack**: Managed automatically by CPU frame allocation (`%rsp`/`%rbp` movement). Memory object lifetime ends instantly upon function epilogue/return.
* **Heap**: Managed dynamically via allocator functions (`malloc`/`free`). Lifetimes persist indefinitely until an explicit call to `free()`. The pointer holding the allocated address owns the responsibility for deallocation.

### B. Pointer Aliasing & Use-After-Free
* When two pointers `ptr_a` and `ptr_b` store identical memory addresses, `free(ptr_a)` immediately invalidates the heap region.
* Accessing memory via `ptr_b` afterward is a **Use-After-Free** operation, as `ptr_b` has become a **dangling pointer**.

### C. Valgrind Diagnostic Mapping
* `definitely lost`: Stack frame holding an un-freed heap address collapsed without passing ownership or calling `free()`.
* `Invalid read/write of size N`: Attempted memory dereference targeting an address inside an unmapped, already freed, or unallocated block.

### D. Segmentation Fault Mechanics
* `crash_example.c` crashes because `get_dangling_pointer()` returns an address residing inside its own stack frame.
* Upon return, the frame is unwound. Dereferencing this address in `main()` accesses unmapped/invalid stack space past the frame boundary, causing the MMU to trigger `SIGSEGV`.

### E. AI Output Critique Summary
* **AI Error Identified**: AI asserted that fixing `aliasing_example.c` required calling `malloc` on `ptr_b`, or that `crash_example.c` failed due to a `NULL` pointer dereference.
* **Correction**: Pointers can validly alias the same block without separate allocations; the error was premature deallocation of shared memory. In `crash_example.c`, the pointer was non-NULL, pointing directly to expired stack memory.
