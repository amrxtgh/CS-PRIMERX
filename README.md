# CS-PRIMERX

> A personal computer science primer — working through the fundamentals of systems programming, one concept and one directory at a time.

`CS-PRIMERX` is a hands-on learning repository where I study the foundations of how computers actually work — from C memory management to machine-level (assembly) representation — by writing code, reading disassembly, and taking notes. The repo is organized so that **each directory is a self-contained topic**, and the directory tree itself doubles as a progress tracker / roadmap.

---

## What's inside

```
CS-PRIMERX/
├── Cronus/                       # Standalone C practice projects
│   └── storagealloc/             #   1. A rudimentary memory allocator
│       ├── main.c                #      alloc() / afree() + 12 test cases
│       ├── test                  #      compiled binary
│       └── README.md
└── systems-programming/          # Guided study tracks
    └── csapp/                    #   CS:APP (Computer Systems: A Programmer's Perspective)
        └── chapter2/             #     Machine-level representation
            ├── chapter2.md       #       notes: registers, operands, mov
            ├── main.c            #       data types & sizes
            ├── memory.c          #       array / sizeof behavior
            ├── dm.c   / dm.s     #       data movement (exchange) + asm
            └── msstore.c / msstore.s  #  multstore call + asm
```

### `Cronus/` — C practice projects

Small, self-contained C programs written to build intuition for low-level concepts. Each subfolder is one project with its own source, tests, and notes.

- **`storagealloc`** — A from-scratch storage allocator implementing `alloc(n)` and `afree(p)` over a static `allocbuf`. It's a stack-style (LIFO) allocator: `alloc` hands out slices of a big char array and bumps a pointer; `afree` rewinds the pointer. `main.c` ships **12 assertion-based tests** covering basic allocation, zero-byte allocs, full-buffer fills, overflow, exhaustion, and invalid `afree` bounds.

### `systems-programming/csapp/` — CS:APP study track

Working through *Computer Systems: A Programmer's Perspective* by reading the book, writing C, and inspecting the generated x86-64 assembly (`.s` files) side by side.

- **`chapter2/` — Machine-level representation.** Notes and code on x86-64 registers, operand types (immediate / register / memory), addressing modes (`Imm + R[rb] + R[ri]·s`), and the `mov` family (`movb/w/d/q`, `movabsq`). Code examples:
  - `dm.c` → `exchange()`, compiled to `dm.s` to see register usage (`%rdi`, `%rsi`, `%rax`).
  - `msstore.c` → `multstore()` calling `mult2()`, compiled to `msstore.s` to see `pushq`/`popq` callee-saved register handling and `call`.
  - `memory.c` and `main.c` — quick experiments with `sizeof` and data types.

---

## How things are built / run

This is plain C + GCC. From any source directory:

```bash
# Compile a C file
gcc -O0 -Wall main.c -o test

# Generate assembly to read alongside the source
gcc -O0 -S dm.c -o dm.s

# Run the storage allocator tests
cd Cronus/storagealloc
gcc -O0 -Wall main.c -o test
./test
```

> `-O0` is used deliberately so the generated assembly stays close to the source and is easy to read while learning.

---

## Roadmap

The directory structure *is* the roadmap. Existing folders are ✅ done (or in progress); planned folders are marked with the concept they'll cover. New work = new folder.

### `Cronus/` — C practice projects
- [x] `storagealloc` — static-buffer `alloc`/`afree` allocator
- [ ] `dynalloc` — a real `malloc`/`free` with a free list
- [ ] `strlib` — re-implement common string functions from scratch
- [ ] `vec` — a growable dynamic array / vector in C
- [ ] `hashtable` — open-addressing hash table
- [ ] `linkedlist` — singly/doubly linked lists + tests
- [ ] `fileio` — buffered file I/O and a small `cat`/`wc` clone

### `systems-programming/csapp/` — CS:APP chapters
- [ ] `chapter1/` — A Tour of Computer Systems (intro / big picture)
- [x] `chapter2/` — Machine-level representation: registers, operands, `mov`
- [ ] `chapter3/` — Arithmetic & logical ops, control flow, loops, switch
- [ ] `chapter4/` — Procedures, stack discipline, recursion in asm
- [ ] `chapter5/` — Arrays, structs, and data alignment in memory
- [ ] `chapter6/` — Memory hierarchy & cache effects
- [ ] `chapter7/` — Linking (object files, symbols, relocation)
- [ ] `chapter8/` — Exceptional control flow (processes, signals, `fork`)
- [ ] `chapter9/` — Virtual memory & memory mapping
- [ ] `chapter10/` — System-level I/O (`open`/`read`/`write`)
- [ ] `chapter11/` — Concurrent programming (threads, mutexes)
- [ ] `chapter12/` — Network & concurrent servers

### Future tracks (new top-level dirs, when started)
- [ ] `operating-systems/` — OS concepts (scheduling, paging, a tiny shell)
- [ ] `networking/` — sockets, a small HTTP server, TCP/UDP experiments
- [ ] `algorithms/` — classic data structures & algorithms in C
- [ ] `compilers/` — a toy interpreter / compiler front end

---

## Conventions

- **One folder = one topic.** Keep each topic isolated so it can be studied, built, and tested independently.
- **Source + assembly pairs.** For the CS:APP track, keep the `.c` and its generated `.s` next to each other so the mapping is obvious.
- **Notes live in a `chapterN.md` / `README.md`** inside each topic folder.
- **Tests are assertions in `main.c`** (or a dedicated test file) — run the binary, see `All ... tests passed!`.
- Build artifacts (`*.o`, `*.out`, executables) are gitignored; commit source and notes, not binaries.

---

## Environment

- Language: **C** (compiled with **GCC 15.x** on x86-64 Linux)
- Book: *Computer Systems: A Programmer's Perspective* (CS:APP), 3rd ed.
- OS: Linux (x86-64)

---

## Why

Because reading about a stack frame is not the same as watching `pushq %rbx` show up in your own disassembly. This repo is the "do it yourself" part.