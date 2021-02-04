# Linux native

Abstract Machine implementation over Linux native.

Currently we can run Nanos-lite over native!

## TRM

* `_putc()` -> `putchar()`
* `_halt()` -> `exit()`
* `_heap` - Use POSIX shared memory API to implement a region of "physical memory".

So `_heap` is actually a file. By using `mmap()`, it is easier to shared the same
"physical memory region" by different virtual memory regions. We map the virtual memory
region [0x100000, 128MB) to the shared memory object. To achieve this, we compile the
native binary as a PIE, making this virtual memory region available in the virtual
address space. (See the compile flags in Makefile.compile.) This is a hack.  On the
another hand, we should also call `mmap()` mentioned above before entering `main()`. In C,
there is no way to do this. Therefore we leverage the constructor of global object in
C++ to perform the initialization. See `src/platform.cpp` for details. Also see VME below.

## IOE

* `_DEVREG_TIMER_UPTIME` -> `gettimeofday()`
* `_DEVREG_TIMER_DATE` -> `localtime()`
* `_DEVREG_INPUT_KBD` -> SDL key events
* `_DEVREG_VIDEO_FBCTL` -> SDL texture update & render

We provide an auto-sync frame buffer by periodically call SDL APIs to render the screen.
The contents written into frame buffer by applications will be eventually rendered.

## CTE

* `_Context` -> `ucontext_t`
* `_yield()` -> `asm volatile("call *0x100000": : "a"(-1))`
* `intr_read()/intr_write()` -> NOT IMPLEMENTED YET
* `_kcontext()` -> NOT IMPLEMENTED YET

To implement CTE, the first issue to consider is how to let system calls from Navy-apps
jump to the `asm_trap()` entry. However, they belong to different projects. This makes it
impossible for them to directly send information to each other, for example, OS tells the
address of entry to Navy-apps. The only way is to define some conventions. We put the
address of `asm_trap()` at address `0x100000` in `_cte_init()`. Then Navy-apps can use
an indirect call to jump to the correct entry address:
```
asm volatile("call *0x100000": "=a"(ret): "a"(type), "S"(a0), "d"(a1), "c"(a2));
```
Both system call and `_yield()` can work in this way.

The second issue is how to perform context saving/restoring. It is easy to use `getcontext()/
setcontext()` in the user space of Linux. However, to save the context near the exception
point as much as possible, we should deal with some tricky cases, including `%eax` is not
preserved during `getcontext()`, and how to return to the exception point gracefully with
`setcontext()`. Also, it seems that it is not allowed to call `getcontext()/setcontext()`
in the assembly code, because we compile the native binary as a PIE. After calling `setcontext()`
in C code, we should clean the stack and return to the exception point. See `src/cte.c` and
`src/trap.S` for details.

The implementation of CTE makes the code less portable, since we should examine the content
of the context. For example, we should get the system call arguments inside
`ucontext_t.uc_mcontext.gregs`.  They are archtecture-dependent. Also, we should define the
macro `__USE_GNU` and compile with the `-std=gnuxx` flags to use `ucontext_t.uc_mcontext.gregs`.

## VME

To implement VME, the first issue is to maintain "page tables". But we can not access the
real page table over the Linux native environment, we should simulate it for the OS. Since
page tables are inherently mappings from virtual address space to physical address space,
we use link list to maintain them. Therefore, most of the code in VME is about link list.

The next issue is how to enforce these mappings. We use `mmap()` again. The basic idea is to
update the mappings with `_map()`, and enforce the mappings when switching to the target address
space with `_switch()`. Therefore, we implement the VME APIs as following

* `_vme_init()` - Do nothing, since we can call `malloc()` in native, and the callbacks from OS
is unnecessary.
* `_protect()` - Initialize an empty link list.
* `_switch()` - Traverse the link list of the current address space, and unmap all old mappings.
After that, tranverse the link list of the target address space, and enforce all new mappings.
* `_map()` - update a mapping
* `_ucontext()` - Make a context based on the example context saved by `init_platform()`. The
example context is get with `getcontext()`. This means that we only need to modify some register
of this context to get a valid one.
* `unprotect()` - NOT IMPLEMENTED YET

There are some corner cases to address. For example, updating the current address space with
`_map()` should enforce the new mapping immediately.

Compared to x86-qemu, VME in native only needs to maintain mappings map to the shared memory
object. This is because the native binary is not located inside the "physical memory address
space" implemented by the shared memory object. VME can not affect the mappings of the native
binary itselt, since these mappings are managed by Linux kernel. This is the other reason that
`_vme_init()` does nothing.

## MPE

NOT IMPLEMENTED YET
