# Bonus — patch to accept any password

Each patched binary (`level1_patched`, `level2_patched`, `level3_patched`)
is a byte-for-byte copy of the original, with the conditional jumps that
gate access rewritten so that **any** input is accepted. Nothing is
injected at runtime (no `LD_PRELOAD`, no environment tricks): the checks
are disabled directly inside the executable file, and no library function
used by the program (`strcmp`, `scanf`, `atoi`, ...) is overwritten —
only the program's own branch instructions are modified.

All patches were applied with a small Python script that seeks to a file
offset, verifies the original bytes (so the patch fails loudly if it's
applied to the wrong build), and overwrites them. Since these binaries
are non-stripped PIE executables whose `.text` section has file offset
== virtual address, the disassembled addresses from `objdump` can be
used directly as file offsets.

## level1

`main` ends with:

```
123c: call strcmp
1241: cmp  eax, 0x0
1244: jne  1260        ; 0f 85 16 00 00 00   -> jump to "Nope."
124a: ...              ; "Good job." path (fallthrough when equal)
```

Patch: the 6-byte `jne` at file offset `0x1244` is overwritten with 6
`NOP` (`0x90`) instructions. The conditional branch to the failure path
disappears, so execution always falls through into the "Good job."
branch regardless of what `strcmp` returned.

## level2

Three checks gate the "Good job." branch: two single-character checks
on the first two bytes of the input (`input[0] == '0'`, `input[1] ==
'0'`) and the final `strcmp` against the decoded password.

```
1337: je 1345   ; 0f 84 08 00 00 00  -> taken only if input[1] == '0'
1350: je 135e   ; 0f 84 08 00 00 00  -> taken only if input[0] == '0'
146d: jne 1480  ; 0f 85 0d 00 00 00  -> taken (failure) if strcmp != 0
```

The two `je` at `0x1337` and `0x1350` are conditional "skip the failure
call" jumps: they must be taken to avoid the `no()` call, but they are
only taken when the character check passes. Turning them into
**unconditional** jumps (opcode `0f 84` -> `e9`, 5-byte `jmp rel32`,
padded with one trailing `NOP` to keep the same 6-byte slot and every
following address unchanged) makes the "skip failure" path unconditional,
so the prefix check can never fail.

The final `jne` at `0x146d` works like level1's: it is replaced with 6
`NOP`s so the "Good job." branch is always reached regardless of the
`strcmp` result.

With all three patches applied the program accepts any string as the
key, including ones that don't even start with `"00"`.

## level3

Same idea, adapted to level3's checks:

```
1370: je 137b   ; 0f 84 05 00 00 00  -> taken only if input[0] == '4'
1386: je 1391   ; 0f 84 05 00 00 00  -> taken only if input[1] == '2'
14a7: je 155e   ; 0f 84 b1 00 00 00  -> taken only if strcmp result == 0
```

All three are `je` (jump when the check passes) rather than `jne`, so
all three are converted into unconditional `jmp` (same `0f 84 -> e9`
transform, rel32 adjusted by +1 for the 1-byte-shorter encoding, padded
with a trailing `NOP`). This forces every gate to always take its
"success" branch.

## Rebuilding the patches

The patch script is inlined in the project's development history; the
transform for each instruction is:

```python
# je  (0f 84 <rel32>)  ->  jmp (e9 <rel32+1>) + nop   [condition removed, always taken]
# jne (0f 85 <rel32>)  ->  nop x6                      [branch removed, never taken]
```

Verify with, e.g.:

```bash
echo "any random string" | ./level1_patched   # -> Good job.
echo "any random string" | ./level2_patched   # -> Good job.
echo "any random string" | ./level3_patched   # -> Good job.
```

while the original, unpatched binaries in `../level1/`, `../level2/`
and `../level3/` still require their real password.
