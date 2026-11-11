# vaccine

A hand-written SQL injection detection/exploitation tool. No SQLi
automation library is used — every payload, error signature and
extraction query is written out in `./vaccine` itself; the only
non-trivial dependency is `urllib` (a plain HTTP client that knows
nothing about SQL).

**Only ever point this at a URL you own or are explicitly authorized
to test.** `tests/vulnerable_app.py` is a small, deliberately
vulnerable local target (stdlib only) provided so the tool can be
exercised end to end without touching anything real.

## Usage

```bash
./vaccine [-o FILE] [-X METHOD] [-A USER-AGENT] URL
```

- `-o FILE` — results storage file (default `vaccine_results.json`,
  created on first run if missing).
- `-X METHOD` — `GET` (default) or `POST`.
- `-A USER-AGENT` — override the `User-Agent` header (bonus).
- The URL's query-string parameters are the ones tested. With
  `-X POST`, the same parameters are sent as the POST body instead.

```bash
./vaccine "http://127.0.0.1:8000/products?id=1"
./vaccine -X POST -o results.json "http://127.0.0.1:8000/products?id=1"
```

Exit code: `0` if vulnerable, `2` if not, `1` on a usage/input error.

## What it does

Runs, for every query-string parameter, in order:

1. **Error-based** — injects `'`, `"`, `');`, etc. and matches the
   response against per-engine error-message signatures (MySQL,
   PostgreSQL, SQLite, Microsoft SQL Server, Oracle).
2. **Boolean-based blind** — compares the response to `AND 1=1` vs.
   `AND 1=2`, expecting the former to resemble the baseline and the
   latter to clearly differ.
3. **Time-based blind** — injects an engine-specific delay (`SLEEP()`,
   `pg_sleep()`, `WAITFOR DELAY`, or, for SQLite which has no sleep
   function, a calibrated heavy recursive `WITH RECURSIVE` query) and
   measures the response delay against the baseline.
4. **UNION-based** — probes the column count with `ORDER BY N`, finds
   which column position gets echoed back into the page with a unique
   marker string, and fingerprints the engine via its version
   function (`version()`, `sqlite_version()`, `@@version`).

Every test above tries **both** a numeric injection context
(`id=1 AND 1=1`) and a quoted-string context (`id=1' AND 1=1-- -`),
since a stray quote breaks a query the same way regardless of context
but a syntactically-valid injected clause only works if it matches
the target's actual context.

If a UNION point is found (and its engine identified), extraction
proceeds automatically: **database names**, then for each of the
first few, **table names**, then for each of the first few tables,
**column names**, then a **row-by-row dump of the whole table**
(capped at 500 rows/table as a safety limit) — using
`information_schema` for MySQL/PostgreSQL and `sqlite_master` for
SQLite, one row fetched per request via `LIMIT 1 OFFSET N` so no
engine-specific aggregate function (`GROUP_CONCAT`/`STRING_AGG`/...)
is ever needed.

## Supported engines / methods (bonus scope)

- Engines: **MySQL, PostgreSQL, SQLite, Microsoft SQL Server** (error
  fingerprinting + time-based); full UNION-based extraction is
  implemented for **MySQL, PostgreSQL, SQLite** (2 required, 3
  delivered).
- Methods: **error, boolean, time, UNION** (2 required, 4 delivered).
- `-A/--user-agent` lets you edit the request's User-Agent (bonus).

## Test

```bash
./tests/run_tests.sh
```

Starts `tests/vulnerable_app.py` (a tiny stdlib-only HTTP server
backed by SQLite with a `products` table and a `users` table
containing fake credentials), runs `vaccine` against it over both GET
and POST, and asserts: all three non-UNION finding types are reported,
the engine is fingerprinted as SQLite, and both tables are fully and
correctly dumped through the UNION extraction path (12 checks total).

## Design notes

- **Storage** (`load_store`/`save_store`) is a flat JSON file, created
  on first run, appended to on every scan — one record per run with
  its timestamp, target, findings, and any extracted data.
- **Row extraction** always goes through `_wrap()`, which surrounds
  the extracted value with plain-ASCII sentinels (`VACCROWSTART` /
  `VACCROWEND`, no `<`/`>` so an HTML-escaping target wouldn't mangle
  them) so it can be pulled out of arbitrary surrounding page markup
  reliably.
- **Why row-by-row (`LIMIT 1 OFFSET N`) instead of aggregating**:
  `GROUP_CONCAT` (MySQL/SQLite) and `STRING_AGG` (PostgreSQL) are
  different function names, and picking the wrong one silently breaks
  extraction on that engine. One row per request is slower but uses
  syntax that is identical across all three supported engines.
