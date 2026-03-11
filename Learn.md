# 🧠 12-Month Systems Programming Roadmap
### Becoming a Strong Candidate for Wine / Proton / Compatibility Layer Development

> **"You don't learn systems programming by reading about it. You learn it by breaking things, tracing crashes, and rebuilding from the wreckage."**

---

## Table of Contents

1. [Overview & Philosophy](#1-overview--philosophy)
2. [Skills to Master](#2-skills-to-master)
3. [12-Month Roadmap](#3-12-month-roadmap)
4. [Weekly Study Schedule](#4-weekly-study-schedule)
5. [Unique Portfolio Projects](#5-unique-portfolio-projects)
6. [Flagship Project](#6-flagship-project)
7. [Open Source Contribution Plan](#7-open-source-contribution-plan)
8. [Daily Practice Routine](#8-daily-practice-routine)
9. [GitHub Portfolio Structure](#9-github-portfolio-structure)
10. [Final 12-Month Checklist](#10-final-12-month-checklist)

---

## 1. Overview & Philosophy

### What This Roadmap Is

This is a **12-month intensive learning plan** designed to take a motivated developer from intermediate programming knowledge to a strong candidate for systems-level roles at companies like CodeWeavers, Valve (Proton team), or any organization working on compatibility layers, runtime systems, or OS-level software.

### Why This Field Is Hard

Working on Wine or Proton is not standard software engineering. It requires simultaneously understanding:

- The **deep internals of Linux** (syscalls, memory management, ELF loading, dynamic linking)
- The **internals of Windows** (Win32 API, PE format, COM, DCOM, the NT kernel model)
- **Low-level C programming** with no safety nets
- **Graphics APIs** across multiple generations and platforms
- **Reverse engineering** techniques to understand undocumented behavior
- **Debugging at the binary level**, not just the source level

Most engineers specialize in one or two of these areas. Wine developers must be competent across all of them simultaneously.

### The Learning Philosophy

**Principle 1 — Always Be Running Code**
Every concept you learn must be immediately grounded in something you can compile, run, trace, or break. Reading without building creates the illusion of understanding.

**Principle 2 — Debug First, Read Second**
When something doesn't work, spend at least 30 minutes investigating it yourself before reaching for documentation. The debugging instinct is the most important skill in this field.

**Principle 3 — Build Progressively Uglier Things**
Start simple. A 50-line ELF parser is more valuable than a textbook chapter on ELF. A 200-line PE loader that partially works is more impressive to a hiring engineer than a perfectly-read specification.

**Principle 4 — Document Everything Publicly**
Every experiment, every debugging session, every failed attempt belongs in your GitHub learning log. Engineers hiring for Wine development respect documented process more than polished outcomes. The log proves you can think at this level.

**Principle 5 — Contribute Early, Contribute Often**
Open source contributions are not a milestone at the end. They start in Month 4. Even trivial contributions establish you as someone who understands the codebase and community norms.

**Principle 6 — Go Deep, Not Wide**
This roadmap intentionally ignores modern web, cloud, and product engineering. Every hour is directed toward the narrow and deep skillset required for systems and compatibility layer work.

### What Success Looks Like

After 12 months you should be able to:

- Read and navigate a million-line C codebase comfortably
- Load and execute a PE binary on Linux from scratch
- Trace a crashing Windows application through Wine and identify the failing DLL stub
- Write and submit a patch to the Wine mailing list
- Explain the difference between how Linux and Windows handle dynamic linking
- Describe the architecture of DXVK and why translating DirectX calls to Vulkan is non-trivial
- Show a GitHub portfolio that demonstrates all of the above

---

## 2. Skills to Master

---

### C Programming

**What to learn:**
- Pointer arithmetic, pointer-to-pointer, function pointers
- Manual memory management with `malloc`, `realloc`, `free` and understanding alignment
- Structs, unions, bitfields, and packed structs for reading binary formats
- Preprocessor macros used in large codebases (`X macros`, include guards, conditional compilation)
- `volatile`, `restrict`, `__attribute__` extensions used in systems code
- Calling conventions: `cdecl`, `stdcall`, `fastcall`, `thiscall` — critical for Wine
- Inline assembly (x86/x86_64 AT&T and Intel syntax)
- Undefined behavior, strict aliasing, and type punning
- POSIX APIs: file descriptors, `mmap`, `fork`, `exec`, signals, pipes
- Thread programming: pthreads, mutexes, condition variables, atomics

**Why it matters:**
Wine is written almost entirely in C. Every DLL stub, every Win32 API implementation, every loader component is C. You cannot contribute meaningfully without mastering C at the systems level, not just the application level.

**Recommended tools:**
- `gcc` and `clang` with `-Wall -Wextra -fsanitize=address,undefined`
- `valgrind` for memory error detection
- `gdb` for step-through debugging at the C level
- `cscope` and `ctags` for navigating large C codebases
- `bear` for generating compile databases

---

### Linux Internals

**What to learn:**
- Process lifecycle: `fork`, `exec`, `wait`, zombie processes, orphan processes
- Virtual memory: page tables, page faults, demand paging, `mmap`, `brk`
- The VFS layer and how system calls reach the kernel
- Dynamic linker (`ld.so`): `RPATH`, `RUNPATH`, `LD_PRELOAD`, `LD_LIBRARY_PATH`
- Signal handling and how signals interact with system calls (`SA_RESTART`)
- File descriptors, `epoll`, `inotify`, `/proc` and `/sys` pseudo-filesystems
- Namespaces and cgroups (relevant to Wine's sandboxing and Proton's container model)
- ELF loading: how the kernel loads an ELF binary and transfers control to `ld.so`
- The `ptrace` system call (the foundation of `strace`, `gdb`, and Wine's debugging infrastructure)
- `seccomp` and how it interacts with Wine's syscall emulation

**Why it matters:**
Wine runs on Linux. Every API call a Windows program makes eventually maps to Linux system calls. Understanding the Linux side deeply means you can trace behavior end-to-end, from the Win32 function call down to the kernel.

**Recommended tools:**
- `strace`, `ltrace`, `ftrace`
- `/proc/$PID/maps`, `/proc/$PID/smaps`
- `lsof`, `pmap`, `ss`
- Kernel source at `elixir.bootlin.com`

---

### Debugging & Reverse Engineering

**What to learn:**
- `gdb`: breakpoints, watchpoints, conditional breakpoints, `info registers`, `x` command for memory inspection, scripting with Python
- `strace` and `ltrace` for syscall and library call tracing
- `perf` for performance profiling and hardware counter analysis
- `valgrind`: Memcheck, Callgrind, Massif
- `rr` (Mozilla Record-and-Replay): essential for debugging non-deterministic crashes in Wine
- `objdump`, `readelf`, `nm`, `strings`, `file` for binary inspection
- `radare2` or `Ghidra` for disassembly and reverse engineering
- x86 and x86_64 assembly: reading compiler output, understanding calling conventions in practice
- DWARF debug information format
- Core dumps: generating them, loading them in `gdb`, extracting useful information

**Why it matters:**
Wine debugging is almost never source-level debugging. A crashing Windows game in Wine produces behavior that must be traced through layers of stub implementations, translated system calls, and binary-level execution. The engineers who can navigate this are rare and valuable.

**Recommended tools:**
- `gdb` with `pwndbg` or `gef` plugins
- `rr` (record and replay debugger)
- `Ghidra` (NSA reverse engineering suite)
- `radare2` / `Cutter`
- `x64dbg` (Windows-side debugging, run under Wine)

---

### Windows Internals

**What to learn:**
- The Windows NT architecture: kernel mode vs user mode, the HAL, executive subsystems
- The Win32 subsystem: `csrss.exe`, `win32k.sys`, the message loop model
- Windows processes and threads vs Linux processes and threads
- The Windows registry: structure, hives, how Wine emulates it
- Windows memory model: virtual address space layout, sections, memory-mapped files
- COM and DCOM: the Component Object Model that underpins most Win32 subsystems
- The Windows loader: how PE files are loaded, relocation, import resolution
- Windows exception handling: SEH (Structured Exception Handling), VEH, how Wine intercepts these
- NTDLL: the lowest-level user-mode DLL, the interface between Win32 and the NT kernel
- Handle tables, object manager, named objects
- Windows file system semantics vs Linux (case sensitivity, locking, alternate data streams)

**Why it matters:**
Wine is an implementation of the Windows API on Linux. You cannot implement something you do not understand. Deep knowledge of Windows internals reveals *why* Wine makes the implementation choices it does, and where the remaining compatibility gaps come from.

**Recommended tools:**
- *Windows Internals* books (Yosifovich, Russinovich et al.)
- A Windows VM with `Process Monitor`, `Process Explorer`, `WinObj` (Sysinternals)
- `x64dbg` for Windows-side debugging
- Wine source code as a secondary reference for Windows behavior

---

### Executable Formats (ELF & PE)

**What to learn:**

**ELF (Executable and Linkable Format):**
- File header, section headers, program headers
- Sections vs segments and why both exist
- Symbol tables: `SHT_SYMTAB`, `SHT_DYNSYM`
- Relocation types: `R_X86_64_PC32`, `R_X86_64_PLT32`, `R_X86_64_GLOB_DAT`, `R_X86_64_JUMP_SLOT`
- The PLT (Procedure Linkage Table) and GOT (Global Offset Table)
- DWARF debug sections
- How `ld.so` processes `PT_DYNAMIC` to resolve shared library dependencies

**PE (Portable Executable):**
- DOS header, PE signature, COFF header, optional header
- Section table: `.text`, `.data`, `.rdata`, `.bss`, `.rsrc`, `.reloc`
- Data directories: Import Directory, Export Directory, Resource Directory, TLS Directory, Debug Directory
- Import Address Table (IAT) and how the loader patches it
- Base relocations and ASLR
- PE32 vs PE32+ (64-bit)
- Delay-load imports
- Rich header (undocumented Microsoft build metadata)

**Why it matters:**
Wine's core job is loading PE files and executing them on Linux. Understanding both formats at the byte level means you can debug loader failures, understand relocation errors, and eventually contribute to Wine's PE loader (`ntdll/loader.c`).

**Recommended tools:**
- `readelf`, `objdump` for ELF
- `PE-bear`, `CFF Explorer`, `dumpbin` for PE
- Python with `pefile` and `pyelftools` libraries
- Writing your own parsers from scratch

---

### Graphics APIs (DirectX, Vulkan, OpenGL)

**What to learn:**
- OpenGL fundamentals: the rendering pipeline, buffers, shaders, textures, framebuffers
- Vulkan fundamentals: instances, devices, queues, command buffers, render passes, synchronization
- DirectX 9, 10, 11 API patterns: device creation, swap chains, draw calls
- DirectX 12: explicit resource management, descriptor heaps, command lists
- HLSL vs GLSL: shader languages, SPIR-V as an intermediate representation
- DXVK architecture: how D3D9/D3D10/D3D11 calls map to Vulkan
- VKD3D-Proton architecture: D3D12 to Vulkan translation
- Wine's built-in DirectX implementation vs DXVK as a drop-in override
- GPU driver architecture on Linux: Mesa, the DRM subsystem, Gallium3D

**Why it matters:**
Modern game compatibility is dominated by graphics API translation. DXVK and VKD3D-Proton are the most performance-critical components of Proton. Understanding this layer is essential for working on game compatibility.

**Recommended tools:**
- `RenderDoc` for GPU frame capture and debugging
- `apitrace` for recording and replaying API calls
- Vulkan SDK with validation layers
- Mesa source code (particularly `src/gallium`)

---

### Build Systems

**What to learn:**
- `make` and Makefiles: implicit rules, pattern rules, automatic variables (`$@`, `$<`, `$^`)
- `autoconf` / `automake` / `configure` scripts — the system Wine uses
- `cmake`: `CMakeLists.txt`, out-of-tree builds, toolchain files for cross-compilation
- `meson`: the system used by Mesa and increasingly by Wine-adjacent projects
- Cross-compilation: building PE binaries with MinGW-w64 from Linux (critical for Wine)
- Understanding `pkg-config` and how library detection works
- `ccache` for build acceleration
- `ninja` as a `cmake` and `meson` backend

**Why it matters:**
Wine uses a highly customized `autoconf`-based build system that simultaneously builds Linux ELF shared libraries and Windows PE DLLs using MinGW-w64. Contributing to Wine requires understanding this hybrid build environment.

**Recommended tools:**
- GNU `make`, `autoconf`, `automake`
- `mingw-w64` cross-compiler toolchain
- `meson` + `ninja`
- `cmake`

---

### Compatibility Layer Architecture

**What to learn:**
- Wine's high-level architecture: `wine` loader, `wineserver`, per-process `ntdll.so`
- The `wineserver`: what it implements, why it exists, the request/reply protocol
- How Wine maps Win32 threads to Linux threads
- How Wine implements the Windows registry using flat files
- Wine's DLL loading: the interaction between the PE loader in `ntdll` and the ELF dynamic linker
- Wine's thunking layer: how 32-bit Windows code calls into 64-bit Linux libraries
- `wow64` in Wine: running 32-bit Windows applications on 64-bit Linux
- Proton's layered architecture: Steam Runtime container + Wine + DXVK + VKD3D-Proton + Steamworks compatibility
- How `LD_PRELOAD` and DLL overrides work together
- `wineprefix`: what it contains, how it's initialized, how Wine finds DLLs

**Why it matters:**
This is the capstone knowledge area. Everything else feeds into understanding compatibility layer architecture. You cannot contribute meaningfully to Wine without a mental model of how its components interact.

**Recommended tools:**
- Wine source code (gitlab.winehq.org)
- `winedbg` (Wine's built-in debugger)
- `WINEDEBUG` environment variable and Wine's debug channel system
- ProtonDB for understanding real-world compatibility issues

---

## 3. 12-Month Roadmap

---

### Month 1 — C Mastery & Linux Foundation

**Concepts to Learn**

- Pointers, pointer arithmetic, pointer-to-pointer
- Manual memory management: `malloc`, `calloc`, `realloc`, `free`
- Structs, unions, bitfields, flexible array members
- Function pointers and callbacks
- POSIX file I/O: `open`, `read`, `write`, `close`, `lseek`
- Process creation: `fork`, `exec`, `waitpid`
- Basic Makefile structure

**Tools to Learn**

- `gcc` / `clang` with sanitizers (`-fsanitize=address,undefined`)
- `gdb`: basic usage — `break`, `run`, `next`, `step`, `print`, `backtrace`
- `valgrind --leak-check=full`
- `make`

**Exercises**

- Implement `malloc` using `sbrk` or `mmap` (bump allocator first, then free list)
- Write a program that forks 5 children and collects their exit codes
- Implement `cat`, `wc`, `head` using only POSIX syscalls (no `stdio`)
- Debug 10 intentionally buggy C programs using only `gdb`

**Projects**

- **Tiny shell**: A minimal Unix shell supporting pipes, redirection, and background jobs
- **Memory allocator**: A `malloc` implementation with a first-fit free list

**Milestone**

You can write, debug, and reason about 500-line C programs using only manual memory management, POSIX APIs, and a debugger.

**Progress Checklist**

- [ ] Completed K&R C exercises for chapters 1–8
- [ ] Built a working `malloc` from scratch
- [ ] Built a working shell with pipes and redirection
- [ ] Debugged 10 programs in `gdb` without using `printf`
- [ ] Zero memory leaks in all projects (verified with `valgrind`)
- [ ] Can explain the difference between stack and heap allocation from first principles

---

### Month 2 — Deep C & Binary Fundamentals

**Concepts to Learn**

- Calling conventions: `cdecl`, `stdcall`, `fastcall` — understand the stack layout for each
- Inline assembly: `asm volatile`, clobber lists, input/output constraints
- x86-64 assembly basics: registers, `mov`, `push`/`pop`, `call`/`ret`, `lea`
- Undefined behavior: strict aliasing, signed overflow, out-of-bounds access
- Type punning safely using `memcpy` and unions
- Linker concepts: symbol resolution, strong vs weak symbols, `static` linkage
- Object files: sections (`.text`, `.data`, `.bss`, `.rodata`)
- Static vs dynamic libraries (`.a` vs `.so`)

**Tools to Learn**

- `objdump -d` for disassembly
- `nm` for symbol inspection
- `readelf` for ELF section/segment inspection
- `ld` linker scripts (basic)
- `strings`, `hexdump`, `xxd`

**Exercises**

- Write a function in inline assembly that performs a 64-bit integer swap
- Use `objdump` to annotate a compiled binary with C source line numbers
- Manually link two object files using only `ld` (no `gcc` wrapper)
- Write a program that intentionally triggers strict aliasing UB and observe the optimizer's behavior at `-O2`

**Projects**

- **ELF section dumper**: A C program that reads an ELF file and prints all section names, types, sizes, and flags
- **Calling convention demonstrator**: A set of C + assembly files that demonstrates `cdecl` vs `stdcall` at the stack level

**Milestone**

You can read compiler-generated x86-64 assembly, understand what the linker does with object files, and inspect any ELF binary's structure with command-line tools.

**Progress Checklist**

- [ ] Can read and annotate 50-line compiler-generated assembly functions
- [ ] Have built and inspected ELF files at the section level
- [ ] Understand the role of the PLT and GOT
- [ ] Have written at least one function in inline assembly
- [ ] Can explain `stdcall` vs `cdecl` and why Wine cares about this distinction

---

### Month 3 — Linux Internals & System Calls

**Concepts to Learn**

- The Linux system call interface: `syscall(2)`, `man 2` pages
- Virtual memory: `mmap`, `munmap`, `mprotect`, page alignment
- The `/proc` filesystem: `/proc/$PID/maps`, `/proc/$PID/status`, `/proc/$PID/fd`
- Signals: `sigaction`, `sigprocmask`, signal-safe functions, `SA_SIGINFO`
- `ptrace`: `PTRACE_ATTACH`, `PTRACE_PEEKDATA`, `PTRACE_SINGLESTEP` — the foundation of debuggers
- File descriptor table internals: `dup`, `dup2`, `fcntl`, `O_CLOEXEC`
- Anonymous vs file-backed memory mappings

**Tools to Learn**

- `strace` — thorough understanding of all flags (`-f`, `-e`, `-p`, `-k`)
- `ltrace`
- `/proc` inspection tools: `pmap`, `lsof`, `ss`
- Writing your own `strace` using `ptrace`

**Exercises**

- Write a minimal `strace` clone using `ptrace` that logs syscall numbers and arguments
- Use `mmap` to implement a basic shared memory IPC system between two processes
- Write a signal handler that catches `SIGSEGV` and prints the fault address
- Parse `/proc/self/maps` and print all mapped regions with their permissions

**Projects**

- **Minimal strace**: A `ptrace`-based syscall tracer that decodes the 20 most common syscalls
- **Memory map visualizer**: A tool that reads `/proc/$PID/maps` and generates a visual ASCII map of a process's address space

**Milestone**

You understand how Linux manages processes, memory, and system calls at the kernel interface level, and you have built a working `ptrace`-based tool.

**Progress Checklist**

- [ ] Built a working syscall tracer using `ptrace`
- [ ] Can read and interpret `/proc/$PID/maps` output for any process
- [ ] Understand how `mmap` creates anonymous and file-backed mappings
- [ ] Have written a `SIGSEGV` handler that recovers gracefully
- [ ] Can trace a program with `strace` and explain every syscall it makes

---

### Month 4 — ELF Deep Dive & Dynamic Linking

**Concepts to Learn**

- ELF file header: `e_ident`, `e_type`, `e_machine`, `e_entry`, `e_phoff`, `e_shoff`
- Program headers (`PT_LOAD`, `PT_DYNAMIC`, `PT_INTERP`, `PT_GNU_STACK`)
- Section headers and their relationship to program headers
- Dynamic section: `DT_NEEDED`, `DT_SONAME`, `DT_RPATH`, `DT_RUNPATH`, `DT_SYMTAB`, `DT_STRTAB`
- Symbol resolution order in the dynamic linker
- Relocation processing: understanding each relocation type
- The PLT stub code: how a lazy-bound function call works step by step
- `LD_PRELOAD` internals: how it intercepts symbol resolution
- Writing shared libraries: `__attribute__((visibility("default")))`, `soname`, `versionscript`
- `dlopen`, `dlsym`, `dlclose`: runtime dynamic loading

**Tools to Learn**

- `readelf -a`, `readelf -d`, `readelf -r`
- `objdump -d -R`
- `ldd` and understanding its output
- `ld.so` debug output: `LD_DEBUG=all`

**Exercises**

- Write an ELF parser in C that prints the full dynamic section and all `DT_NEEDED` entries
- Use `LD_PRELOAD` to intercept `malloc` and `free`, log all allocations to a file
- Manually implement lazy binding: write a PLT stub in assembly that resolves a symbol on first call
- Build a shared library with a version script that hides internal symbols

**Projects**

- **ELF loader**: A program that manually loads a statically-linked ELF executable into memory using `mmap` and jumps to its entry point
- **LD_PRELOAD function interceptor**: A shared library that intercepts and logs all `open`, `read`, `write` calls

**Milestone**

You can load a simple ELF binary without using `execve` and understand every step the dynamic linker takes to prepare a program for execution.

**Progress Checklist**

- [ ] Have written a complete ELF parser in C
- [ ] Have loaded and executed a static ELF binary manually using `mmap`
- [ ] Understand PLT/GOT lazy binding at the assembly level
- [ ] Have written and published an `LD_PRELOAD` function interceptor
- [ ] **First contact with Wine source**: Read `ntdll/loader.c` and map concepts to your ELF knowledge

---

### Month 5 — Windows Internals & PE Format

**Concepts to Learn**

- Windows NT architecture overview: kernel vs user mode, NTDLL as the user-mode boundary
- The PE file format: all headers byte-by-byte
- PE sections: `.text`, `.data`, `.rdata`, `.bss`, `.rsrc`, `.reloc`, `.tls`
- Import Directory Table: how Windows resolves DLL imports at load time
- Export Directory Table: named and ordinal exports
- Base relocations: why they exist and how they're applied
- Thread Local Storage (TLS) in PE files
- Resources in PE files: `RT_STRING`, `RT_DIALOG`, `RT_ICON`, `RT_VERSION`
- COM basics: `IUnknown`, `IClassFactory`, `CoCreateInstance`, `QueryInterface`
- Windows SEH: `__try`, `__except`, the exception directory in PE files

**Tools to Learn**

- `PE-bear` (cross-platform PE inspector)
- `CFF Explorer`
- `dumpbin` (from Windows SDK, runs under Wine)
- Python `pefile` library

**Exercises**

- Write a PE parser in C that prints all section headers, imports, and exports
- Use `pefile` in Python to write a script that extracts all imported function names from a PE binary
- Compile a small C program with MinGW-w64 and manually trace the relocation process
- Set up a Windows VM and use `Process Monitor` to trace what a simple EXE does at the API level

**Projects**

- **PE inspector**: A C tool that displays PE headers, sections, imports, and exports in a readable format
- **PE import scanner**: Given a directory of PE files, identify all unique imported DLLs and functions — useful for Wine compatibility analysis

**Milestone**

You can parse any PE binary by hand, understand how Windows loads it, and relate every PE concept to its ELF equivalent.

**Progress Checklist**

- [ ] Have written a complete PE parser in C
- [ ] Can explain PE relocations and why ASLR makes them necessary
- [ ] Understand COM `IUnknown` and `QueryInterface` at the code level
- [ ] Have set up MinGW-w64 cross-compilation on Linux
- [ ] Have used `Process Monitor` on Windows to trace file and registry access

---

### Month 6 — Wine Architecture & First Contributions

**Concepts to Learn**

- Wine's directory structure: `dlls/`, `libs/`, `loader/`, `programs/`, `server/`
- The `wineserver`: its purpose, the Unix socket it exposes, the request/reply system
- How Wine implements Win32 threads using pthreads
- Wine's DLL loading: `ntdll/loader.c` — the PE loader in detail
- Wine's registry implementation: flat files in the `wineprefix`
- `WINEDEBUG` channels: how to enable debug output for specific subsystems
- Wine's `wine_dbg_log` and `TRACE`, `WARN`, `ERR`, `FIXME` macros
- How to build Wine from source
- Wine's coding style and patch submission requirements
- The Wine mailing list and patch review process

**Tools to Learn**

- `winedbg` — Wine's built-in debugger
- `WINEDEBUG=+relay` — traces every Win32 API call
- `WINEDEBUG=+seh` — traces exception handling
- `git format-patch` and `git send-email` for patch submission
- `gitlab.winehq.org` and the issue tracker

**Exercises**

- Build Wine from source on your Linux machine
- Run a simple Windows EXE under Wine with `WINEDEBUG=+all` and analyze the output
- Find and read the implementation of `CreateFile` in Wine (`dlls/kernelbase/file.c`)
- Use `winedbg` to set a breakpoint on `CreateFile` and trace a program's file access

**Projects**

- **Wine debug log analyzer**: A Python script that parses `WINEDEBUG=+relay` output and generates a call graph
- **Wine DLL stub finder**: A script that identifies unimplemented (`FIXME`) stubs in Wine's DLLs

**Milestone**

You have built Wine from source, can navigate its codebase, have filed or fixed your first bug, and have submitted your first patch to the mailing list.

**Progress Checklist**

- [ ] Wine built from source successfully
- [ ] Can navigate from a Win32 API function name to its Wine implementation in under 2 minutes
- [ ] Have filed at least one bug on the Wine bug tracker with a proper test case
- [ ] Have submitted at least one patch (even trivial — typo fix, FIXME stub, test case)
- [ ] Have introduced yourself on `wine-devel` mailing list
- [ ] Debug log analyzer tool published on GitHub

---

### Month 7 — Graphics APIs & DXVK Architecture

**Concepts to Learn**

- OpenGL rendering pipeline: vertices → vertex shader → rasterization → fragment shader → framebuffer
- Vulkan fundamentals: instances, physical devices, logical devices, queues, command pools
- Vulkan synchronization: semaphores, fences, barriers, render passes
- DirectX 9 API: device creation, vertex/index buffers, textures, shaders
- DirectX 11 API: device contexts, resources, shader model 4/5
- HLSL shader language basics
- SPIR-V: Vulkan's binary shader format
- DXVK's architecture: how D3D9/D3D10/D3D11 calls map to Vulkan objects
- Wine's built-in D3D implementation vs DXVK as a DLL override
- `RenderDoc` frame capture: how to capture and analyze a frame

**Tools to Learn**

- Vulkan SDK with validation layers
- `RenderDoc`
- `apitrace` for recording and replaying D3D/OpenGL calls
- `spirv-cross` for shader inspection and conversion
- Mesa source code as a reference

**Exercises**

- Write a Vulkan triangle renderer from scratch (no abstraction libraries)
- Write a D3D9 triangle renderer in C++ and run it under Wine
- Use `RenderDoc` to capture a frame from a simple D3D9 game running under DXVK
- Read DXVK's `src/d3d9/d3d9_device.cpp` and trace how `DrawPrimitive` maps to Vulkan

**Projects**

- **Vulkan triangle**: From-scratch Vulkan renderer (proves you understand the API, not just tutorials)
- **D3D9 tracer**: Using Wine's `WINEDEBUG=+d3d` and `apitrace` to trace and compare D3D9 calls

**Milestone**

You understand the rendering pipeline in Vulkan, can read DXVK's source code, and have captured and analyzed a real GPU frame.

**Progress Checklist**

- [ ] Vulkan triangle renderer working from scratch
- [ ] D3D9 application running correctly under Wine + DXVK
- [ ] RenderDoc frame capture analyzed and documented
- [ ] Have read and annotated DXVK's D3D9 device implementation
- [ ] Can explain the DXVK architecture to someone unfamiliar with it

---

### Month 8 — Advanced Debugging & Reverse Engineering

**Concepts to Learn**

- `rr` (record and replay): recording executions, replaying deterministically, reverse execution
- GDB Python scripting: writing custom commands, pretty-printers, breakpoint conditions
- DWARF debug information: understanding how debug info is structured and used by GDB
- Core dump analysis: generating, loading, and extracting information from core dumps
- Binary instrumentation: what it is and how tools like `Valgrind` and `DynamoRIO` work
- `perf`: `perf record`, `perf report`, `perf stat`, flame graphs
- Reverse engineering basics with `Ghidra`: loading a binary, renaming symbols, following data flows
- Debugging Wine crashes: the typical workflow from crash → WINEDEBUG → gdb → winedbg → patch

**Tools to Learn**

- `rr` (Mozilla's record-and-replay debugger)
- `gdb` Python scripting API
- `Ghidra` for static analysis
- `perf` + `flamegraph.pl` for performance analysis
- `addr2line` for translating addresses to source lines

**Exercises**

- Record a Wine crash with `rr`, replay it, and use reverse-continue to find the root cause
- Write a GDB Python script that automatically extracts the Win32 call stack from a Wine process
- Use `Ghidra` to reverse engineer a small Windows utility and document its behavior
- Generate a flame graph for a 3D game running under Wine and identify the hottest functions

**Projects**

- **Wine crash analyzer**: A tool that takes a Wine crash log and automatically identifies the failing DLL and function
- **GDB Wine extension**: A set of GDB Python commands tailored for debugging Wine processes (win32 stack trace, wineserver state, etc.)

**Milestone**

You can debug any Wine crash from first principles using `rr`, `gdb`, and `winedbg`, and you have published debugging tools that others can use.

**Progress Checklist**

- [ ] Have used `rr` to debug a non-deterministic Wine crash
- [ ] Have written at least one GDB Python extension
- [ ] Have reverse-engineered a small Windows binary with Ghidra
- [ ] Have generated and analyzed a flame graph for a Wine workload
- [ ] Published Wine debugging tools on GitHub with documentation

---

### Month 9 — Win32 API Implementation & Wine DLL Work

**Concepts to Learn**

- Win32 API categories: kernel32, user32, gdi32, advapi32, shell32, ole32, msvcrt
- The `ntdll` / `kernel32` split: what lives in ntdll vs what wraps it in kernel32
- Implementing a Win32 stub in Wine: the anatomy of a proper implementation
- Wine's test suite (`dlls/*/tests/`): how tests are structured and how to write them
- Cross-compiling Wine tests with MinGW-w64 and running them on Windows for comparison
- Registry operations in Wine: `RegCreateKeyEx`, `RegSetValueEx`, `RegQueryValueEx`
- Windows Messaging: `PostMessage`, `SendMessage`, the message queue, `GetMessage`/`DispatchMessage`
- GDI: device contexts, pens, brushes, bitmaps, the GDI object model

**Tools to Learn**

- Wine's `make test` infrastructure
- MinGW-w64 cross-compiler (for building Wine tests)
- `wine-test-bot` understanding (the automated test system)
- Comparing Wine test output with Windows test output

**Exercises**

- Write a Wine conformance test for a `kernel32` function that you know has edge-case bugs
- Implement a simple Win32 stub function in Wine from scratch and submit it as a patch
- Run the full Wine test suite and document any failures you encounter
- Write a MinGW-w64 test program that exercises obscure `msvcrt` behavior and compare against Wine

**Projects**

- **Win32 API conformance tester**: A tool that runs a set of Win32 API calls and compares results between Wine and a real Windows system
- **Wine DLL implementation**: A meaningful implementation of a stub or incomplete function in Wine (intended for upstreaming)

**Milestone**

You have a merged or pending-review patch in the Wine codebase that implements real functionality, not just a cleanup.

**Progress Checklist**

- [ ] Have written and submitted Wine conformance tests
- [ ] Have implemented at least one non-trivial Win32 function in Wine
- [ ] Patch is posted to `wine-patches` and has received maintainer feedback
- [ ] Understand the full path from `CreateFile` → `NtCreateFile` → Linux `open()` in Wine
- [ ] Have compared Wine test output against native Windows for 10+ functions

---

### Month 10 — Compatibility Layer Internals & Proton

**Concepts to Learn**

- Proton's architecture: how it differs from standalone Wine
- The Steam Runtime: what it provides, why it exists, pressure-vessel container
- DXVK integration in Proton: DLL override mechanism
- VKD3D-Proton: D3D12 to Vulkan translation, how it differs from upstream VKD3D
- Steam Play and `PROTON_LOG` debugging
- `proton-call` and manual Proton invocation
- Wine `wow64`: running 32-bit Windows applications in a 64-bit Wine build
- Wine's PE/ELF hybrid DLLs: the `.so` that wraps a `.dll`
- `wineboot`, `wineserver` lifecycle in a Proton context
- Lutris and Heroic Launcher internals as alternative frontends

**Tools to Learn**

- `PROTON_LOG=1` for Proton debug output
- `protontricks` for managing Proton environments
- `Winetricks` source code study
- GameScope (Valve's compositor for gaming)

**Exercises**

- Run a broken Steam game with `PROTON_LOG=1` and diagnose the failure
- Build Proton from source (or a modified DXVK) and inject it into a Steam game
- Trace a D3D11 game startup with `apitrace` under Proton and analyze the API call sequence
- Study `VKD3D-Proton`'s `vkd3d_pipeline_cache.c` and document your understanding

**Projects**

- **Proton game compatibility reporter**: A tool that runs a game under Proton, collects DXVK logs, Wine logs, and Proton logs, and generates a structured compatibility report
- **Custom Proton build**: A fork of Proton with a specific patch applied and documented

**Milestone**

You understand Proton's layered architecture end-to-end and have built and modified at least one component of the Proton stack.

**Progress Checklist**

- [ ] Have built DXVK from source and tested it
- [ ] Have diagnosed and documented a real game compatibility failure
- [ ] Understand the Proton + Steam Runtime container model
- [ ] Have read and annotated VKD3D-Proton's D3D12 command list implementation
- [ ] Proton compatibility reporter tool published on GitHub

---

### Month 11 — Flagship Project Development

**Concepts to Learn**

- Project architecture design for systems-level tools
- API design for debugging and analysis tools
- Performance considerations for tracer tools (overhead, ring buffers, lock-free structures)
- Documentation standards for systems projects (man pages, GitHub wikis, architecture docs)
- Profiling and optimizing your own tools

**Focus**

This month is dedicated primarily to building the [Flagship Project](#6-flagship-project). The concepts learned are driven by the project's requirements.

**Exercises**

- Profile your flagship project and reduce its overhead by 30%
- Write architecture documentation for the project
- Get feedback on the project from the Wine developer community

**Milestone**

The flagship project is functional, documented, and publicly released. A post about it has been made on the Wine mailing list or a related forum.

**Progress Checklist**

- [ ] Flagship project is feature-complete and publicly released
- [ ] Architecture documentation published
- [ ] Performance benchmarks documented
- [ ] Feedback received from at least one systems engineer
- [ ] Blog post or technical writeup published about the project

---

### Month 12 — Polish, Contributions & Portfolio Completion

**Concepts to Learn**

- Writing effective technical documentation
- Preparing for systems programming interviews
- Communicating low-level concepts clearly in writing

**Focus**

- Land remaining Wine patches
- Complete any unfinished portfolio projects
- Write comprehensive technical writeups for all major projects
- Polish the GitHub portfolio README

**Exercises**

- Write a 2,000-word technical post explaining how Wine's PE loader works
- Record a short video demonstrating your flagship project
- Review and clean up all GitHub repositories for public presentation

**Milestone**

A complete, polished, and impressive public GitHub portfolio exists. You have multiple Wine contributions, a flagship project, and technical writeups documenting your understanding.

**Progress Checklist**

- [ ] All major projects have README files with architecture explanations
- [ ] At least 3 merged patches in Wine or related projects
- [ ] Flagship project is complete and documented
- [ ] Technical blog or writeup series published
- [ ] GitHub profile README summarizes the journey
- [ ] Portfolio is ready to share with CodeWeavers, Valve, or similar companies

---

## 4. Weekly Study Schedule

> Assumes 4–6 hours per day, 6 days per week. Sunday is review and planning only.

| Day       | Focus Area                                      | Activity Type                  |
| --------- | ----------------------------------------------- | ------------------------------ |
| Monday    | C programming / systems concepts               | Reading + exercises            |
| Tuesday   | Project work (current month's main project)    | Hands-on building              |
| Wednesday | Debugging practice + tool exploration          | Practical tracing/debugging    |
| Thursday  | Wine codebase reading + contribution work      | Code reading + patch writing   |
| Friday    | Reverse engineering / binary inspection        | Tools + analysis               |
| Saturday  | Long project session + documentation writing   | Deep work + writing            |
| Sunday    | Review weekly progress, plan next week, rest   | Review + planning (2 hrs max)  |

### Daily Time Allocation (Weekdays)

| Time Block      | Activity                                              |
| --------------- | ----------------------------------------------------- |
| First 90 min    | Deep reading or concept study (no interruptions)      |
| Next 60 min     | Exercises related to what was just read               |
| Break (30 min)  | Walk, rest                                            |
| Next 2 hours    | Project work or Wine codebase exploration             |
| Last 30 min     | Learning log entry: document what was learned         |

### Daily Time Allocation (Saturday)

| Time Block      | Activity                                              |
| --------------- | ----------------------------------------------------- |
| First 3 hours   | Major project work session                            |
| Break (1 hour)  | Lunch and rest                                        |
| Next 2 hours    | Technical writing: document experiments and findings  |
| Last 30 min     | Read Wine mailing list, open source community activity|

---

## 5. Unique Portfolio Projects

---

### Project 1 — `elfpeek`: Interactive ELF & PE Binary Inspector

**Concept**

A terminal-based interactive tool (using `ncurses` or a TUI library) that allows browsing ELF and PE binary structures interactively. Navigate sections, segments, imports, exports, relocations, and symbol tables using a keyboard-driven interface. Annotate entries with notes and export reports.

**Why it stands out**

Most binary inspection tools (`readelf`, `PE-bear`) are either command-line dump tools or heavyweight GUI applications. An interactive terminal inspector that handles both ELF and PE demonstrates simultaneous mastery of both formats — directly relevant to Wine's dual-world nature.

**Core technologies**

- C with `ncurses` or `notcurses` for TUI
- Custom ELF and PE parsers (no library dependencies)
- `libmagic` for format detection

**Difficulty**

⭐⭐⭐ Medium-Hard

**Estimated build time**

6–8 weeks

---

### Project 2 — `wintrace`: A Windows API Call Tracer for Wine

**Concept**

An `LD_PRELOAD` + Wine debug channel hybrid that intercepts Win32 API calls at the Wine DLL boundary and logs them in a structured, searchable format. Goes beyond `WINEDEBUG=+relay` by adding argument decoding, call graph visualization, and filtering by process, thread, or DLL.

**Why it stands out**

`WINEDEBUG=+relay` output is enormous and hard to parse. A tool that makes Wine API tracing practical and structured would be immediately useful to the Wine community and demonstrates deep understanding of Wine's internal call dispatch mechanism.

**Core technologies**

- C with Wine's internal `WINEDEBUG` infrastructure
- Wine `LD_PRELOAD` hook mechanism
- Python for post-processing and visualization
- `graphviz` for call graph output

**Difficulty**

⭐⭐⭐⭐ Hard

**Estimated build time**

8–10 weeks

---

### Project 3 — `peloader`: A Minimal PE Loader for Linux

**Concept**

A standalone C program that loads and executes simple Windows PE executables on Linux without Wine. Handles PE header parsing, section mapping with correct permissions, import resolution against a small set of manually implemented Win32 stubs, base relocation, and TLS initialization.

**Why it stands out**

This is effectively a baby Wine. Building it requires understanding every step of the Windows loader, which is the core of what Wine's `ntdll/loader.c` does. Any Wine developer who sees this project immediately understands you've done the hard work.

**Core technologies**

- C with `mmap`, `mprotect`, `dlopen`
- MinGW-w64 for building test PE files
- Custom Win32 stub implementations

**Difficulty**

⭐⭐⭐⭐⭐ Very Hard

**Estimated build time**

10–14 weeks (incremental)

---

### Project 4 — `d3d9spy`: A DirectX 9 API Tracer

**Concept**

A DLL (compiled with MinGW-w64, loaded via Wine's DLL override mechanism) that wraps `d3d9.dll` and intercepts every DirectX 9 call. Logs calls with arguments and return values, detects state corruption, and can generate a replay script that recreates the API call sequence.

**Why it stands out**

Understanding D3D9 at the API interception level is directly relevant to DXVK and Wine's built-in D3D implementation. Building a proxy DLL demonstrates knowledge of COM interface implementation, vtable hooking, and Wine's DLL override system.

**Core technologies**

- C++ with MinGW-w64
- Wine DLL override mechanism
- COM vtable proxying
- DirectX 9 SDK headers

**Difficulty**

⭐⭐⭐⭐ Hard

**Estimated build time**

6–8 weeks

---

### Project 5 — `wineprefix-doctor`: Automated Wine Prefix Diagnostics

**Concept**

A comprehensive diagnostic and repair tool for Wine prefixes. Analyzes a prefix for common problems (DLL conflicts, registry corruption, missing libraries, DXVK misconfiguration), reports issues with severity levels, and applies automatic fixes where safe. Includes a "compatibility mode" that configures a prefix optimally for specific game engines.

**Why it stands out**

This demonstrates practical knowledge of Wine's prefix structure, DLL loading order, registry layout, and common failure modes. It's immediately useful to end users while demonstrating deep technical knowledge.

**Core technologies**

- Python with Wine prefix inspection
- Shell scripting for Wine invocation
- JSON configuration for game engine profiles
- SQLite for tracking prefix state over time

**Difficulty**

⭐⭐⭐ Medium

**Estimated build time**

4–6 weeks

---

### Project 6 — `syscall-bridge`: A Linux/Windows Syscall Comparison Tool

**Concept**

A research and documentation tool that maps Windows NT system calls to their Linux equivalents, documents semantic differences (e.g., `NtCreateFile` vs `open()`, `NtMapViewOfSection` vs `mmap()`), and includes a runtime component that traces both sides simultaneously for a Wine process to show the translation in action.

**Why it stands out**

This is the kind of deep comparative systems work that Wine developers do every day. Documenting it in a tool form demonstrates that you've internalized the conceptual model that Wine is built on.

**Core technologies**

- C with `ptrace` for syscall interception
- NTDLL source analysis
- Python for documentation generation

**Difficulty**

⭐⭐⭐⭐ Hard

**Estimated build time**

6–8 weeks

---

### Project 7 — `comspy`: A COM Interface Tracker for Wine

**Concept**

A tool that instruments Wine's COM infrastructure to trace `CoCreateInstance`, `QueryInterface`, `AddRef`, and `Release` calls. Detects reference counting leaks (objects not properly released), tracks which COM objects a program uses, and generates a report of all COM interfaces exercised during a program's execution.

**Why it stands out**

COM is at the heart of many Windows subsystems (shell, media, accessibility, D3D). COM bugs in Wine are notoriously hard to debug. A COM-aware debugging tool demonstrates you understand one of Wine's most complex subsystems.

**Core technologies**

- C with Wine's COM infrastructure hooks
- `LD_PRELOAD` and vtable patching
- Python for leak report generation

**Difficulty**

⭐⭐⭐⭐ Hard

**Estimated build time**

8–10 weeks

---

### Project 8 — `game-compat-scanner`: Static Game Compatibility Analyzer

**Concept**

A tool that takes a game's PE executables and DLLs and statically analyzes them to predict Wine compatibility. Checks imported functions against Wine's implementation database, identifies missing stubs, detects use of protected-process features, checks for kernel-mode anti-cheat indicators, and generates a structured compatibility report.

**Why it stands out**

This combines PE parsing, Wine knowledge, and practical compatibility work into a tool that has immediate real-world value for the gaming community. It demonstrates knowledge of what actually makes games fail in Wine.

**Core technologies**

- Python with `pefile`
- Wine DLL database (built from Wine source)
- SQLite for storing results
- Web interface (optional) for browsing results

**Difficulty**

⭐⭐⭐ Medium

**Estimated build time**

4–6 weeks

---

### Project 9 — `allocator-wars`: A Memory Allocator Benchmark Suite

**Concept**

A rigorous benchmark suite for memory allocators in a Wine context. Tests `ntdll`'s heap implementation against `glibc`'s `malloc`, `jemalloc`, and `mimalloc` under workloads derived from real Windows game memory patterns. Measures fragmentation, allocation latency, and throughput under multithreaded load.

**Why it stands out**

Memory allocator performance is a real and documented issue in Wine for some games. This project demonstrates performance engineering skills, low-level memory knowledge, and direct relevance to Wine's practical performance problems.

**Core technologies**

- C with multiple allocator implementations
- `perf` and custom instrumentation
- Python for result visualization
- Statistical analysis of latency distributions

**Difficulty**

⭐⭐⭐ Medium-Hard

**Estimated build time**

4–5 weeks

---

## 6. Flagship Project

---

### `libwine-trace`: A Comprehensive Wine Execution Tracer & Analyzer

#### Project Idea

A multi-layer Wine execution tracing system that captures, correlates, and analyzes everything that happens when a Windows application runs under Wine — from Win32 API calls at the top, through Wine's internal dispatch, down to Linux system calls at the bottom. Provides a unified timeline view, call correlation, performance attribution, and a query interface for investigating compatibility failures.

This is the tool that Wine developers would actually want to use every day.

---

#### Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    libwine-trace                            │
│                                                             │
│  ┌─────────────┐  ┌──────────────┐  ┌──────────────────┐    │
│  │  Win32 API  │  │  Wine DLL    │  │  Linux Syscall   │    │
│  │  Intercept  │  │  Relay Hook  │  │  Capture         │    │
│  │  (DLL hook) │  │  (WINEDEBUG) │  │  (ptrace/ebpf)   │    │
│  └──────┬──────┘  └──────┬───────┘  └────────┬─────────┘    │
│         │                │                    │             │
│         └────────────────┼────────────────────┘             │
│                          │                                  │
│                   ┌──────▼──────┐                           │
│                   │  Correlation│                           │
│                   │   Engine    │                           │
│                   └──────┬──────┘                           │
│                          │                                  │
│         ┌────────────────┼────────────────┐                 │
│         │                │                │                 │
│  ┌──────▼──────┐  ┌──────▼──────┐  ┌─────▼──────┐           │
│  │  Timeline   │  │  Query CLI  │  │  Report     │          │
│  │  Viewer     │  │  Interface  │  │  Generator  │          │
│  └─────────────┘  └─────────────┘  └────────────┘           │
└─────────────────────────────────────────────────────────────┘
```

---

#### Components

**1. Win32 API Interceptor**
A MinGW-compiled DLL that registers itself via Wine's DLL override mechanism and wraps key Win32 DLLs (`kernel32`, `user32`, `ntdll`). Intercepts function calls before they reach Wine's implementation and after they return. Captures function name, arguments (decoded according to type), return value, timestamp, thread ID, and call stack.

**2. Wine DLL Relay Hook**
Processes `WINEDEBUG=+relay` output in real-time, parsing it into structured events. Correlates relay events with the Win32 API intercept events to create a complete call chain.

**3. Linux Syscall Capture**
Uses `ptrace` or Linux eBPF (if available) to capture every Linux system call made by the Wine process. Records syscall number, arguments, return value, and timestamp. Correlates with the layers above using thread ID and timestamp proximity.

**4. Correlation Engine**
The heart of the system. Takes events from all three layers and correlates them into unified call chains: "CreateFile call → ntdll relay → NtCreateFile → open() syscall → return value → propagated back up." Detects mismatches (e.g., a Win32 call that reaches the syscall layer but returns an unexpected error).

**5. Timeline Viewer**
An ncurses-based or web-based timeline that shows all events on a unified time axis, color-coded by layer, with drill-down capability.

**6. Query CLI Interface**
A SQL-like query interface: `"show all CreateFile calls that returned ERROR_FILE_NOT_FOUND"`, `"show all COM QueryInterface calls for IDirectDraw"`, `"show all calls that took longer than 10ms"`.

**7. Report Generator**
Generates structured HTML or Markdown compatibility reports: most frequent API calls, unimplemented stubs hit, error patterns, performance bottlenecks.

---

#### Major Technical Challenges

- **Timing correlation**: Events arrive from three different capture mechanisms with different timing characteristics. Designing a robust correlation algorithm that handles clock skew and ordering ambiguity is non-trivial.

- **Overhead management**: A naive implementation would add 10x overhead and make the program unusable. Requires ring buffers, lock-free data structures, and sampling strategies.

- **Argument decoding**: Win32 APIs have hundreds of different argument types including complex structs, bitfield flags, and output parameters. Building a type description system that can decode all of them is a significant engineering effort.

- **Thread safety**: Wine is heavily multithreaded. All capture mechanisms must be thread-safe and the correlation engine must handle concurrent event streams.

- **Cross-architecture support**: Wine runs 32-bit Windows apps in 64-bit Linux. The tracer must handle both.

---

#### Why It Would Impress Wine Developers

- It demonstrates mastery of every layer of Wine's stack simultaneously
- It's a tool that would be genuinely useful for Wine development — the kind of thing that gets linked on the mailing list
- The correlation engine requires deep understanding of how Wine translates Windows concepts to Linux concepts
- The argument decoding system requires encyclopedic knowledge of Win32 API types
- The performance engineering required shows systems-level maturity

---

## 7. Open Source Contribution Plan

### Understanding Large Codebases

Navigating a codebase as large as Wine requires a systematic approach:

```bash
# Step 1: Get oriented with the top-level structure
ls -la wine/
# dlls/ libs/ loader/ programs/ server/ tools/ include/

# Step 2: Find an API you want to study
grep -r "CreateFileW" dlls/kernelbase/ --include="*.c" -l

# Step 3: Use cscope for cross-reference navigation
cscope -Rb  # build database
# Then use cscope to find all callers of a function

# Step 4: Use ctags for symbol lookup
ctags -R .
# Then use vim/emacs ctags integration
```

Build a mental model of how data flows through Wine for one specific API call before trying to understand the whole system. `CreateFile → CreateFileW → NtCreateFile → unix_fd` is a good starting path.

### Exploring the Wine Codebase

Start with these files in order:

1. `loader/main.c` — How the Wine process starts
2. `libs/wine/loader.c` — The Wine ELF loader entry points
3. `dlls/ntdll/loader.c` — The PE loader (the most important file in Wine)
4. `dlls/kernel32/file.c` — A simple Win32 DLL implementation
5. `server/main.c` — The wineserver entry point
6. `server/process.c` — How the wineserver manages processes

### Finding Beginner Bugs

**The best sources for first contributions:**

1. **Wine Bugzilla** (`bugs.winehq.org`): Filter by `Component: kernel32` or other DLLs you've studied. Look for bugs marked `UNCONFIRMED` with a test case.

2. **FIXME stubs**: Run `grep -r "FIXME" dlls/kernel32/ | head -50`. Many of these are legitimate unimplemented features waiting for someone to implement them.

3. **Wine test failures**: Run `make test` in a specific DLL directory and look for failures. A failing test you can fix is a perfect first contribution.

4. **Valgrind reports**: Run common Windows programs under Wine + Valgrind and look for memory errors. Fixing real memory bugs is highly valued.

```bash
# Finding FIXME stubs as contribution opportunities
grep -rn "FIXME(" dlls/kernelbase/ | grep -v "not implemented" | head -20
```

### Submitting Patches

Wine uses email-based patch submission, not GitHub pull requests:

```bash
# 1. Make your change, commit it
git add dlls/kernelbase/file.c
git commit -m "kernelbase: Implement GetFinalPathNameByHandle."

# 2. Generate a patch
git format-patch HEAD~1

# 3. Check the patch with Wine's check script
./tools/checkpatch.pl 0001-kernelbase-Implement-GetFinalPathNameByHandle.patch

# 4. Send to the mailing list
git send-email --to=wine-patches@winehq.org 0001-...patch
```

**Patch requirements:**
- Must include a conformance test in `dlls/<dll>/tests/`
- Test must pass on both Wine and native Windows
- Follow Wine's coding style (K&R brace style, `WINE_DEFAULT_DEBUG_CHANNEL`)
- Subject line format: `[PATCH] component: Description.`

### Interacting with Maintainers

- **Subscribe to `wine-devel`** and read it daily for one month before posting
- **Be patient**: patch review can take weeks
- **Respond professionally** to all feedback, even critical feedback
- **Never argue** about style — Wine has established conventions, follow them
- **Ask questions on `#winehackers`** on the Libera.chat IRC network
- **Attend WineConf** (annual conference) if possible

---

## 8. Daily Practice Routine

### The Core Daily Practice (30 minutes minimum, every day)

**Binary Reading (10 minutes)**
Pick any binary on your system. Run it through `objdump`, `readelf`, or `PE-bear`. Find something you haven't seen before. Look it up.

```bash
# Example: Look at a random system library each day
readelf -a /usr/lib/x86_64-linux-gnu/libpthread.so.0 | less
```

**Syscall Tracing (10 minutes)**
Pick any program you use and trace it with `strace`. Find a syscall whose behavior surprises you. Read its man page.

```bash
strace -e trace=openat,mmap,mprotect -f /usr/bin/git status 2>&1 | less
```

**Wine Codebase Reading (10 minutes)**
Read 50 lines of Wine source code per day. Navigate from API calls you know to their implementations. Build familiarity slowly.

```bash
# Example navigation
vim dlls/kernelbase/file.c +/CreateFileW
```

### Weekly Practices

**Monday — Write C Without Safety Nets**
Write 50 lines of C that uses raw pointers, manual memory management, and no error-ignoring. Fix all bugs without `printf` debugging — use only `gdb`.

**Wednesday — Debug Someone Else's Code**
Take a random open-source C project, compile it with sanitizers, run it, and investigate any warnings or errors it produces.

**Friday — Wine Bug Triage**
Spend one hour on Wine Bugzilla. Read 5 bug reports, try to reproduce at least one, add information if you can.

### The Learning Log Rule

Every evening, write 3–10 lines in your learning log (`learning-log/YYYY-MM-DD.md`):

```markdown
## 2025-MM-DD

**Learned**: How `PT_DYNAMIC` is processed by ld.so during shared library loading.
**Did**: Built a minimal ELF with a custom `PT_DYNAMIC` section and traced ld.so's processing with `LD_DEBUG=all`.
**Confused about**: Why `DT_BIND_NOW` forces eager binding but some loaders ignore it.
**Tomorrow**: Read the ld.so source to understand the `DT_BIND_NOW` check.
```

This log becomes your portfolio's most convincing evidence of genuine learning.

---

## 9. GitHub Portfolio Structure

```
systems-programming-journey/
│
├── README.md                          # Portfolio overview + 12-month summary
├── roadmap.md                         # This document
│
├── learning-log/
│   ├── README.md                      # How to read the log
│   ├── 2025-01/                       # Daily entries by month
│   │   ├── 2025-01-01.md
│   │   └── ...
│   └── monthly-summaries/
│       ├── month-01-summary.md
│       └── ...
│
├── projects/
│   ├── README.md                      # Index of all projects
│   ├── elfpeek/                       # ELF + PE interactive inspector
│   ├── wintrace/                      # Windows API call tracer
│   ├── peloader/                      # Minimal PE loader for Linux
│   ├── d3d9spy/                       # DirectX 9 API tracer
│   ├── wineprefix-doctor/             # Wine prefix diagnostics
│   ├── syscall-bridge/                # Linux/Windows syscall mapper
│   ├── comspy/                        # COM interface tracker
│   ├── game-compat-scanner/           # Static game compatibility analyzer
│   ├── allocator-wars/                # Memory allocator benchmark suite
│   └── libwine-trace/                 # FLAGSHIP: Wine execution tracer
│
├── experiments/
│   ├── README.md
│   ├── elf-loading/                   # ELF loader experiments
│   ├── pe-parsing/                    # PE parser iterations
│   ├── ptrace-experiments/            # ptrace-based tool experiments
│   ├── calling-conventions/           # Assembly + calling convention demos
│   ├── dynamic-linking/               # LD_PRELOAD experiments
│   └── vulkan-experiments/            # Vulkan renderer iterations
│
├── wine-contributions/
│   ├── README.md                      # Index of Wine patches and contributions
│   ├── patches/                       # Formatted patch files
│   │   ├── 0001-kernelbase-...patch
│   │   └── ...
│   └── test-results/                  # Wine test output comparisons
│
├── debugging-notes/
│   ├── README.md
│   ├── gdb-techniques.md              # GDB tricks and commands discovered
│   ├── wine-debugging-workflow.md     # Workflow for debugging Wine crashes
│   ├── rr-sessions/                   # Notable rr debugging sessions
│   └── crash-analyses/               # Documented crash investigations
│
├── writeups/
│   ├── README.md
│   ├── how-wine-pe-loader-works.md
│   ├── elf-vs-pe-comparison.md
│   ├── dxvk-architecture-explained.md
│   ├── wine-wineserver-protocol.md
│   └── windows-linux-syscall-comparison.md
│
└── resources/
    ├── README.md
    ├── books.md                       # Recommended books with notes
    ├── papers.md                      # Academic papers and references
    ├── tools.md                       # Tools reference with usage examples
    └── links.md                       # Curated links to documentation
```

---

## 10. Final 12-Month Checklist

### C Programming

- [ ] Have implemented a custom memory allocator (`malloc` + `free`)
- [ ] Have written a working Unix shell with pipes and redirection
- [ ] Can read and write inline x86-64 assembly
- [ ] Can navigate a 100,000+ line C codebase comfortably
- [ ] Zero tolerance for memory leaks in own code

### Linux Internals

- [ ] Have built a `ptrace`-based syscall tracer
- [ ] Understand ELF loading at the byte level
- [ ] Understand dynamic linking, PLT/GOT, and `LD_PRELOAD` from first principles
- [ ] Can trace any Linux process end-to-end with `strace`
- [ ] Have written code that uses `mmap`, `mprotect`, and `fork` directly

### Debugging

- [ ] Comfortable with `gdb` at an advanced level (scripting, reverse debugging)
- [ ] Have used `rr` to debug a non-deterministic crash
- [ ] Have written at least one `gdb` Python extension
- [ ] Have used `Ghidra` for reverse engineering
- [ ] Have generated and analyzed flame graphs with `perf`

### Windows Internals

- [ ] Understand the PE format at the byte level
- [ ] Have written a PE parser and a PE loader
- [ ] Understand COM `IUnknown`, `QueryInterface`, `AddRef`, `Release`
- [ ] Understand Windows SEH and how Wine intercepts it
- [ ] Have used Windows Sysinternals tools to analyze real Windows behavior

### Wine

- [ ] Have built Wine from source
- [ ] Can navigate the Wine source to find any Win32 API implementation in under 2 minutes
- [ ] Have filed bug reports on Wine Bugzilla with proper test cases
- [ ] Have at least **3 patches accepted** into Wine (tests, bug fixes, or stubs)
- [ ] Understand the wineserver architecture and the request/reply protocol
- [ ] Have used `WINEDEBUG=+relay` to trace real program execution

### Graphics

- [ ] Have written a Vulkan triangle renderer from scratch
- [ ] Understand the D3D9 → Vulkan translation in DXVK at a conceptual level
- [ ] Have captured and analyzed a GPU frame with `RenderDoc`
- [ ] Understand SPIR-V and shader compilation pipelines

### Projects

- [ ] **ELF + PE Inspector** — published and documented
- [ ] **Win32 API Tracer** — published and documented
- [ ] **PE Loader for Linux** — published and demonstrated
- [ ] **D3D9 Spy DLL** — published and documented
- [ ] **Game Compatibility Scanner** — published with results
- [ ] **At least 2 additional portfolio projects** from the list above
- [ ] **Flagship project (`libwine-trace`)** — complete, released, and documented

### Documentation & Portfolio

- [ ] Daily learning log maintained for 12 months (200+ entries)
- [ ] At least **5 technical writeups** explaining systems concepts
- [ ] All projects have thorough README files with architecture explanations
- [ ] GitHub portfolio README summarizes the journey compellingly
- [ ] At least one conference talk proposal submitted or community presentation given

### Career Readiness

- [ ] Can explain Wine's architecture in a 15-minute whiteboard session
- [ ] Can read a Wine crash log and identify the probable root cause
- [ ] Have interacted positively with Wine maintainers on the mailing list
- [ ] Portfolio is something you would confidently send to CodeWeavers or Valve
- [ ] Can articulate the difference between Wine, Proton, DXVK, and VKD3D clearly

---

## Appendix: Essential References

### Books

| Title | Author | Relevance |
|-------|--------|-----------|
| *The C Programming Language* | Kernighan & Ritchie | Foundation |
| *Advanced Programming in the UNIX Environment* | Stevens & Rago | Linux internals |
| *Computer Systems: A Programmer's Perspective* | Bryant & O'Hallaron | Systems foundation |
| *Windows Internals (7th ed.)* | Yosifovich, Russinovich et al. | Windows internals |
| *The Linux Programming Interface* | Kerrisk | Linux API reference |
| *Linkers and Loaders* | Levine | ELF and PE loading |
| *Understanding the Linux Kernel* | Bovet & Cesati | Kernel internals |
| *Hacking: The Art of Exploitation* | Erickson | Low-level + assembly |

### Online Resources

| Resource | URL | Use |
|----------|-----|-----|
| Wine source | `gitlab.winehq.org/wine/wine` | Primary codebase |
| Wine Bugzilla | `bugs.winehq.org` | Bug tracking |
| Wine wiki | `wiki.winehq.org` | Architecture docs |
| Bootlin Elixir | `elixir.bootlin.com` | Linux kernel cross-reference |
| OSDev Wiki | `wiki.osdev.org` | Low-level systems reference |
| DXVK source | `github.com/doitsujin/dxvk` | D3D→Vulkan reference |
| VKD3D-Proton | `github.com/HansKristian-Work/vkd3d-proton` | D3D12→Vulkan reference |
| PE Format spec | Microsoft docs | PE reference |
| ELF spec | `refspecs.linuxfoundation.org` | ELF reference |
| Sysinternals | `learn.microsoft.com/sysinternals` | Windows debugging tools |

---

*This roadmap was designed for a highly motivated learner committing 4–6 hours per day. Adjust the timeline based on prior experience. The goal is not to complete every item — it is to reach the point where you are thinking, debugging, and building at the systems level every day.*

*The best evidence that this worked is not a certificate or a completed checklist. It is a GitHub profile that any experienced Wine developer can read and immediately recognize as the work of someone who has done the hard things.*