#!/usr/bin/env python3
"""
Extract STM32 RM register headings that look like:
  10.8.X <Register title> (REGISTER_NAME)

PyPDF2-only, streaming page-by-page (low memory).

Usage:
  python3 extract_rm_regs_pypdf2.py <manual.pdf> [--csv out.csv] [--section 10.8.]

Examples:
  python3 extract_rm_regs_pypdf2.py RM0475.pdf --csv regs.csv --section 10.8.
"""
import argparse, re, csv, sys
from typing import Iterator, Tuple

Heading = Tuple[str, str, str]  # (section, title, register)

def make_regex(section_prefix: str) -> re.Pattern:
    """
    Build a regex that matches lines like:
      10.8.<digits> <title possibly no '(' characters> (<UPPERCASE_NAME_WITH_UNDERSCORES>)
    """
    prefix = re.escape(section_prefix.rstrip('.')) + r'\.'  # "10\.8\."
    return re.compile(rf'^\s*({prefix}\d+)\s+([^\n(]+?)\s*\(([A-Z0-9_]+)\)', re.UNICODE)

def iter_pages_text(pdf_path: str) -> Iterator[str]:
    from PyPDF2 import PdfReader
    try:
        reader = PdfReader(pdf_path)
    except Exception as e:
        print(f"Failed to open PDF: {e}", file=sys.stderr)
        return
    for page in reader.pages:
        txt = page.extract_text() or ""
        yield txt

def scan_pages(page_text_iter: Iterator[str], pat: re.Pattern) -> Iterator[Heading]:
    seen = set()
    for txt in page_text_iter:
        # Split to lines; strip empty
        lines = [l.strip() for l in (txt or "").splitlines() if l.strip()]
        n = len(lines)
        for i in range(n):
            # check current line and join with next to catch wraps before '('
            candidates = [lines[i]]
            if i + 1 < n:
                candidates.append(lines[i] + " " + lines[i + 1])
            for cand in candidates:
                m = pat.match(cand)
                if not m:
                    continue
                section, title, reg = m.group(1).strip(), m.group(2).strip(), m.group(3).strip()
                key = (section, reg)
                if key in seen:
                    continue
                seen.add(key)
                # normalize whitespace in title
                title = re.sub(r'\s+', ' ', title)
                yield (section, title, reg)

def main(argv=None):
    ap = argparse.ArgumentParser(description="Extract register headings from a PDF (PyPDF2-only).")
    ap.add_argument("pdf", help="Path to the Reference Manual PDF")
    ap.add_argument("--csv", help="Optional CSV output path")
    ap.add_argument("--section", default="10.8.", help="Section prefix to match (default: 10.8.)")
    args = ap.parse_args(argv)

    pat = make_regex(args.section)

    writer = None
    if args.csv:
        f = open(args.csv, "w", newline="", encoding="utf-8")
        writer = csv.writer(f)
        writer.writerow(["section", "title", "register"])

    count = 0
    for section, title, reg in scan_pages(iter_pages_text(args.pdf), pat):
        count += 1
        if writer:
            writer.writerow([section, title, reg])
        else:
            # print(f"{section} | {title} | {reg}")
            print (reg)

    if writer:
        f.close()
    if count == 0:
        print("No matches found. Check --section or the PDF's text extraction quality.", file=sys.stderr)

if __name__ == "__main__":
    main()
