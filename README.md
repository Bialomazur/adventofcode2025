# Advent of Code - Rust/C/C++/Java Rotation

I'm solving Advent of Code in a strict rotation: Rust → C → C++ → Java → repeat. This keeps things interesting and forces me to think in different paradigms.

## The Cycle

Day 1 = Rust  
Day 2 = C  
Day 3 = C++  
Day 4 = Java  
Day 5 = Rust (back to start)  
Day 6 = C  
...and so on

## Project Layout

```
.
├── rust/
│   ├── src/bin/day01.rs    # Day 1 solution
│   ├── src/bin/day05.rs    # Day 5 solution
│   └── Cargo.toml
├── c/
│   ├── day02/              # Day 2
│   │   ├── main.c
│   │   └── Makefile
│   └── day06/              # Day 6
├── cpp/
│   ├── day03/              # Day 3
│   │   ├── solution.cpp
│   │   └── Makefile
│   └── day07/              # Day 7
└── java/
    ├── Day04.java          # Day 4
    └── Day08.java          # Day 8
```

## Quick Commands

**Rust:**
```bash
cd rust
cargo run --bin day01
cargo run --bin day05
```

**C:**
```bash
cd c/day02
make && ./a.out
```

**C++:**
```bash
cd cpp/day03
make && ./solution
```

**Java:**
```bash
cd java
javac Day04.java && java Day04
```

## Why This Rotation?

1. **Rust**: Memory safety, pattern matching, `Result`/`Option` types  
2. **C**: Raw pointers, manual memory, simple and direct  
3. **C++**: STL containers, RAII, OOP/functional mix  
4. **Java**: JVM ecosystem, straightforward OOP, built-in libs

It's annoying switching contexts every day, but that's the point—keeps me sharp.

## Input Files

All inputs go in `inputs/day01.txt`, `inputs/day02.txt`, etc. These are `.gitignore`'d because Eric (AoC creator) asks us not to share puzzle inputs.

## Common Utilities

If I find myself writing the same shit in multiple languages, I'll stick it in `shared/`. Things like:
- Linked list implementations (C/C++ need these, Java/Rust don't)
- Quick integer parsing functions
- Vector/array utility functions

---

*Advent of Code by Eric Wastl. Not affiliated with this messy multi-language project.*
