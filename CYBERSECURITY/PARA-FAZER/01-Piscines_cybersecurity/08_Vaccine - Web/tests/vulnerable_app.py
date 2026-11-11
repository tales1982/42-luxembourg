#!/usr/bin/env python3
"""
Deliberately vulnerable HTTP app used ONLY to test `vaccine` against a
target we are explicitly authorized to attack (ourselves, locally).
Stdlib only (http.server + sqlite3). Do not expose this outside
localhost, and never point `vaccine` (or any SQLi tool) at a target
you don't own or have explicit permission to test.

Schema:
  products(id, name, price)   <- the injectable endpoint queries this
  users(id, username, password, email)  <- the "juicy" table to dump

GET/POST /products?id=<value>  -- vulnerable: id is concatenated
straight into the SQL string, no parameterization.
"""
import sqlite3
import http.server
import socketserver
import urllib.parse
import sys

DB_PATH = ":memory:shared:"
HOST = "127.0.0.1"
PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8000


def init_db():
    conn = sqlite3.connect("file::memory:?cache=shared", uri=True)
    conn.execute("CREATE TABLE products (id INTEGER PRIMARY KEY, name TEXT, price TEXT)")
    conn.execute("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT, email TEXT)")
    conn.executemany("INSERT INTO products VALUES (?, ?, ?)", [
        (1, "Widget", "9.99"),
        (2, "Gadget", "19.99"),
        (3, "Gizmo", "29.99"),
    ])
    conn.executemany("INSERT INTO users VALUES (?, ?, ?, ?)", [
        (1, "admin", "s3cr3t_flag_hunter2", "admin@example.test"),
        (2, "alice", "alicepass", "alice@example.test"),
    ])
    conn.commit()
    return conn


# Keep one connection alive for the whole process lifetime so the
# shared in-memory database isn't dropped between requests.
_KEEPALIVE_CONN = init_db()


def run_query(sql):
    conn = sqlite3.connect("file::memory:?cache=shared", uri=True)
    try:
        cur = conn.execute(sql)
        rows = cur.fetchall()
        cols = [d[0] for d in cur.description] if cur.description else []
        return cols, rows, None
    except sqlite3.Error as e:
        return None, None, str(e)
    finally:
        conn.close()


PAGE_TMPL = """<!doctype html>
<html><body>
<h1>Product catalog</h1>
{content}
</body></html>
"""


class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        pass  # keep test output quiet

    def _handle(self, id_param):
        # THE VULNERABILITY: raw string concatenation, no parameter binding.
        sql = "SELECT id, name, price FROM products WHERE id = " + id_param
        cols, rows, err = run_query(sql)
        if err:
            content = "<pre>SQL error: %s</pre>" % err
        elif not rows:
            content = "<p>No products found.</p>"
        else:
            content = "<table>" + "".join(
                "<tr>" + "".join(f"<td>{c}</td>" for c in r) + "</tr>" for r in rows
            ) + "</table>"
        body = PAGE_TMPL.format(content=content).encode()
        self.send_response(200)
        self.send_header("Content-Type", "text/html")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        if parsed.path != "/products":
            self.send_response(404)
            self.end_headers()
            return
        qs = urllib.parse.parse_qs(parsed.query, keep_blank_values=True)
        id_param = qs.get("id", ["1"])[0]
        self._handle(id_param)

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        if parsed.path != "/products":
            self.send_response(404)
            self.end_headers()
            return
        length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(length).decode()
        qs = urllib.parse.parse_qs(body, keep_blank_values=True)
        id_param = qs.get("id", ["1"])[0]
        self._handle(id_param)


if __name__ == "__main__":
    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.TCPServer((HOST, PORT), Handler) as httpd:
        print(f"vulnerable test app listening on http://{HOST}:{PORT}/products?id=1")
        httpd.serve_forever()
