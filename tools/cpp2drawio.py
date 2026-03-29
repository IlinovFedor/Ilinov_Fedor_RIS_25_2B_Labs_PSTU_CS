#!/usr/bin/env python3
"""
!!! ВНИМАНИЕ! VIBE-CODE! DO NOT TOUCH !!!
АВТОР ПРОГРАММЫ ДАЖЕ НЕ ЗНАЕТ ПИТОН
100% AI-SLOP HUMAN-FREE

cpp2drawio.py - Convert C++ source files to draw.io flowchart diagrams.

Usage:
    python3 cpp2drawio.py input.cpp [output_dir]
    python3 cpp2drawio.py input.cpp [output_dir] --png

If output_dir is not specified, .drawio files are created next to the input file.
Each function in the .cpp file generates a separate .drawio file.
Use --png flag to also export PNG via draw.io CLI (requires drawio installed).

Examples:
    python3 cpp2drawio.py main.cpp
    python3 cpp2drawio.py main.cpp ./output/
    python3 cpp2drawio.py main.cpp ./output/ --png
"""

import re
import sys
import os
import subprocess
import html
from dataclasses import dataclass, field
from typing import Optional, List, Tuple


# ============================================================================
# AST Node Types
# ============================================================================

@dataclass
class ASTNode:
    pass

@dataclass
class IncludeNode(ASTNode):
    text: str

@dataclass
class UsingNode(ASTNode):
    text: str

@dataclass
class GlobalVarNode(ASTNode):
    text: str

@dataclass
class DefineNode(ASTNode):
    name: str
    params: str
    body: list

@dataclass
class FunctionNode(ASTNode):
    signature: str
    body: list

@dataclass
class ReturnNode(ASTNode):
    text: str

@dataclass
class WhileNode(ASTNode):
    condition: str
    body: list

@dataclass
class ForNode(ASTNode):
    init: str
    condition: str
    increment: str
    body: list
    header: str

@dataclass
class RangeForNode(ASTNode):
    header: str
    body: list

@dataclass
class DoWhileNode(ASTNode):
    condition: str
    body: list

@dataclass
class IfNode(ASTNode):
    condition: str
    then_body: list
    else_body: list

@dataclass
class CoutNode(ASTNode):
    text: str

@dataclass
class CinNode(ASTNode):
    text: str

@dataclass
class AssignmentNode(ASTNode):
    text: str

@dataclass
class DeclarationNode(ASTNode):
    text: str

@dataclass
class FunctionCallNode(ASTNode):
    text: str

@dataclass
class DeleteNode(ASTNode):
    text: str

@dataclass
class RawStatementNode(ASTNode):
    text: str

@dataclass
class MacroWrapperNode(ASTNode):
    """A macro like TIMER(...) that wraps real code inside its parens."""
    name: str
    body: list

@dataclass
class StructMethodNode(ASTNode):
    """A method inside a struct: signature + optional parsed body."""
    signature: str
    body: Optional[list]   # None if only declared (no braces in struct body)

@dataclass
class StructNode(ASTNode):
    """A C++ struct definition."""
    name: str
    # Ordered list of members: each item is either
    #   ('field',  str)             — a field declaration text
    #   ('method', StructMethodNode)— a method (with or without body)
    members: list


# ============================================================================
# C++ Parser
# ============================================================================

class CppParser:
    """Simple regex-based C++ parser that produces AST nodes."""

    def __init__(self, source: str):
        self.source = source
        self.pos = 0

    def parse(self) -> list:
        cleaned = self._remove_comments(self.source)
        self.source = cleaned
        self.pos = 0
        nodes = []
        while self.pos < len(self.source):
            self._skip_ws()
            if self.pos >= len(self.source):
                break
            node = self._parse_top_level()
            if node:
                nodes.append(node)
            else:
                self.pos += 1
        return nodes

    # -- helpers --

    def _remove_comments(self, text):
        result = []
        i = 0
        while i < len(text):
            if text[i] == '"' and (i == 0 or text[i - 1] != '\\'):
                j = i + 1
                while j < len(text):
                    if text[j] == '"' and text[j - 1] != '\\':
                        j += 1
                        break
                    j += 1
                result.append(text[i:j])
                i = j
            elif text[i] == '\'' and (i == 0 or text[i - 1] != '\\'):
                j = i + 1
                while j < len(text):
                    if text[j] == '\'' and text[j - 1] != '\\':
                        j += 1
                        break
                    j += 1
                result.append(text[i:j])
                i = j
            elif i + 1 < len(text) and text[i:i + 2] == '//':
                while i < len(text) and text[i] != '\n':
                    i += 1
            elif i + 1 < len(text) and text[i:i + 2] == '/*':
                i += 2
                while i + 1 < len(text) and text[i:i + 2] != '*/':
                    i += 1
                i += 2
            else:
                result.append(text[i])
                i += 1
        return ''.join(result)

    def _skip_ws(self):
        while self.pos < len(self.source) and self.source[self.pos] in ' \t\n\r':
            self.pos += 1

    def _remaining(self):
        return self.source[self.pos:]

    # -- top level --

    def _parse_top_level(self):
        self._skip_ws()
        if self.pos >= len(self.source):
            return None
        remaining = self._remaining()

        # #include
        m = re.match(r'#\s*include\s*[<"]([^>"]+)[>"]', remaining)
        if m:
            self.pos += m.end()
            return IncludeNode(m.group(0).strip())

        # #define MACRO(params) with continuation lines
        m = re.match(r'#\s*define\s+(\w+)\(([^)]*)\)\s*\\\s*\n', remaining)
        if m:
            name, params = m.group(1), m.group(2)
            self.pos += m.end()
            body_text = ""
            while self.pos < len(self.source):
                le = self.source.find('\n', self.pos)
                if le == -1:
                    le = len(self.source)
                line = self.source[self.pos:le].strip()
                if line.endswith('\\'):
                    body_text += line[:-1].strip() + '\n'
                    self.pos = le + 1
                else:
                    body_text += line + '\n'
                    self.pos = le + 1
                    break
            body_nodes = self._parse_block(body_text)
            return DefineNode(name, params, body_nodes)

        # simple #define (no parens) -- skip
        m = re.match(r'#\s*define\s+\w+[^\n]*\n', remaining)
        if m:
            self.pos += m.end()
            return None

        # using namespace
        m = re.match(r'using\s+namespace\s+\w+\s*;', remaining)
        if m:
            self.pos += m.end()
            return UsingNode(m.group(0).strip())

        # struct definition
        m = re.match(r'struct\s+(\w+)\s*\{', remaining)
        if m:
            name = m.group(1)
            self.pos += m.end() - 1   # position on '{'
            body_text = self._extract_braced()
            # consume optional ';' after '}'
            self._skip_ws()
            if self.pos < len(self.source) and self.source[self.pos] == ';':
                self.pos += 1
            members = self._parse_struct_body(body_text)
            return StructNode(name, members)

        # function definition
        func = self._try_parse_function()
        if func:
            return func

        # global variable (covers many types)
        m = re.match(
            r'((?:const\s+)?(?:static\s+)?(?:unsigned\s+)?'
            r'(?:int|double|float|char|bool|long|short|string|size_t|void|timeval)'
            r'(?:\s*[*&]+)?\s+)'
            r'[^;{]+;',
            remaining,
        )
        if m:
            self.pos += m.end()
            return GlobalVarNode(m.group(0).strip())

        if remaining[0] == ';':
            self.pos += 1
            return None

        le = self.source.find('\n', self.pos)
        self.pos = le + 1 if le != -1 else len(self.source)
        return None

    def _try_parse_function(self):
        remaining = self._remaining()
        pattern = r'(template\s*<[^>]*>\s*)?((?:[\w:*&<>,\s]+?)\s+([\w:~<>]+)\s*\([^)]*\))\s*(const)?\s*\{'
        m = re.match(pattern, remaining)
        if not m:
            return None
        template_prefix = m.group(1) or ""
        signature = m.group(2).strip()
        const_suffix = m.group(4) or ""
        if const_suffix:
            signature = signature + " const"
        if template_prefix:
            signature = template_prefix.strip() + " " + signature
        first = signature.split()[0]
        if first in ('if', 'else', 'while', 'for', 'switch', 'do'):
            return None
        self.pos += m.end() - 1
        body_text = self._extract_braced()
        return FunctionNode(signature, self._parse_block(body_text))

    def _extract_braced(self):
        if self.pos >= len(self.source) or self.source[self.pos] != '{':
            return ""
        depth = 0
        start = self.pos + 1
        i = self.pos
        while i < len(self.source):
            ch = self.source[i]
            if ch in ('"', "'"):
                q = ch
                i += 1
                while i < len(self.source) and self.source[i] != q:
                    if self.source[i] == '\\':
                        i += 1
                    i += 1
            elif ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    self.pos = i + 1
                    return self.source[start:i]
            i += 1
        self.pos = len(self.source)
        return self.source[start:]

    # -- block content --

    def _parse_block(self, text: str) -> list:
        nodes: list = []
        pos = 0
        text = text.strip()

        while pos < len(text):
            while pos < len(text) and text[pos] in ' \t\n\r':
                pos += 1
            if pos >= len(text):
                break
            rem = text[pos:]
            node = None
            consumed = 0

            # return
            m = re.match(r'return\b\s*([^;]*);', rem)
            if m:
                node = ReturnNode("return " + m.group(1).strip() + ";")
                consumed = m.end()

            # while
            if not node:
                m = re.match(r'while\s*\(', rem)
                if m:
                    pc, ep = self._parens(rem, rem.index('('))
                    rest = rem[ep:].strip()
                    off = ep + (len(rem[ep:]) - len(rest))
                    if rest.startswith('{'):
                        bt, be = self._braced_text(rem, off)
                        node = WhileNode(pc, self._parse_block(bt))
                        consumed = be
                    else:
                        se = self._stmt_end(rest)
                        node = WhileNode(pc, self._parse_block(rest[:se]))
                        consumed = off + se

            # do-while
            if not node:
                m = re.match(r'do\s*\{', rem)
                if m:
                    bt, be = self._braced_text(rem, rem.index('{'))
                    rest = rem[be:].strip()
                    wm = re.match(r'while\s*\(', rest)
                    if wm:
                        pc, pe = self._parens(rest, rest.index('('))
                        semi = rest.find(';', pe)
                        node = DoWhileNode(pc, self._parse_block(bt))
                        consumed = be + (len(rem[be:]) - len(rest)) + (semi + 1 if semi != -1 else pe)

            # for
            if not node:
                m = re.match(r'for\s*\(', rem)
                if m:
                    pc, ep = self._parens(rem, rem.index('('))
                    rest = rem[ep:].strip()
                    off = ep + (len(rem[ep:]) - len(rest))
                    if ':' in pc:
                        hdr = "for (" + pc + ")"
                        if rest.startswith('{'):
                            bt, be = self._braced_text(rem, off)
                            node = RangeForNode(hdr, self._parse_block(bt))
                            consumed = be
                        else:
                            se = self._stmt_end(rest)
                            node = RangeForNode(hdr, self._parse_block(rest[:se]))
                            consumed = off + se
                    else:
                        parts = pc.split(';')
                        init = parts[0].strip() if len(parts) > 0 else ""
                        cond = parts[1].strip() if len(parts) > 1 else ""
                        inc = parts[2].strip() if len(parts) > 2 else ""
                        hdr = f"for ({init}; {cond}; {inc})"
                        if rest.startswith('{'):
                            bt, be = self._braced_text(rem, off)
                            node = ForNode(init, cond, inc, self._parse_block(bt), hdr)
                            consumed = be
                        else:
                            se = self._stmt_end(rest)
                            node = ForNode(init, cond, inc, self._parse_block(rest[:se]), hdr)
                            consumed = off + se

            # if
            if not node:
                m = re.match(r'if\s*\(', rem)
                if m:
                    node, consumed = self._parse_if(rem)

            # cout
            if not node:
                m = re.match(r'cout\s*<<', rem)
                if m:
                    se = self._stmt_end(rem)
                    node = CoutNode(rem[:se].strip())
                    consumed = se

            # cin
            if not node:
                m = re.match(r'cin\s*>>', rem)
                if m:
                    se = self._stmt_end(rem)
                    node = CinNode(rem[:se].strip())
                    consumed = se

            # delete
            if not node:
                m = re.match(r'delete\s', rem)
                if m:
                    se = self._stmt_end(rem)
                    node = DeleteNode(rem[:se].strip())
                    consumed = se

            # declaration
            if not node:
                m = re.match(
                    r'(?:const\s+)?(?:static\s+)?(?:unsigned\s+)?'
                    r'(?:int|double|float|char|bool|long|short|string|size_t|auto|void|timeval)'
                    r'(?:\s*[*&]+\s*|\s+[*&]*\s*)'
                    r'\w',
                    rem,
                )
                if m:
                    se = self._stmt_end(rem)
                    node = DeclarationNode(rem[:se].strip())
                    consumed = se

            # macro wrapper (TIMER, etc.)
            if not node:
                m = re.match(r'([A-Z_][A-Z0-9_]*)\s*\(', rem)
                if m and m.group(1) not in ('if', 'else', 'while', 'for', 'switch', 'do', 'return'):
                    name = m.group(1)
                    pc, ep = self._parens(rem, rem.index('('))
                    if ';' in pc or '{' in pc:
                        inner_nodes = self._parse_block(pc)
                        node = MacroWrapperNode(name, inner_nodes)
                        consumed = ep
                        rest_after = rem[ep:].lstrip()
                        if rest_after.startswith(';'):
                            consumed = ep + (len(rem[ep:]) - len(rest_after)) + 1

            # function call
            if not node:
                m = re.match(r'(\w+)\s*\(', rem)
                if m and m.group(1) not in ('if', 'else', 'while', 'for', 'switch', 'do', 'return'):
                    se = self._stmt_end(rem)
                    node = FunctionCallNode(rem[:se].strip())
                    consumed = se

            # assignment / increment
            if not node:
                m = re.match(r'[\w\[\].>*+-]+\s*(\+\+|--|[+\-*/%]?=)', rem)
                if m:
                    se = self._stmt_end(rem)
                    node = AssignmentNode(rem[:se].strip())
                    consumed = se

            # prefix increment / decrement
            if not node:
                m = re.match(r'(\+\+|--)\w', rem)
                if m:
                    se = self._stmt_end(rem)
                    node = AssignmentNode(rem[:se].strip())
                    consumed = se

            # fallback
            if not node:
                se = self._stmt_end(rem)
                if se > 0:
                    t = rem[:se].strip()
                    if t and t != ';':
                        node = RawStatementNode(t)
                    consumed = se
                else:
                    consumed = 1

            if node:
                nodes.append(node)
            pos += max(consumed, 1)

        return nodes

    def _parse_if(self, text: str):
        m = re.match(r'if\s*\(', text)
        if not m:
            return None, 0
        pc, ep = self._parens(text, text.index('('))
        rest = text[ep:].strip()
        off = ep + (len(text[ep:]) - len(rest))

        if rest.startswith('{'):
            bt, be = self._braced_text(text, off)
            then = self._parse_block(bt)
            off2 = be
        else:
            se = self._stmt_end(rest)
            then = self._parse_block(rest[:se])
            off2 = off + se

        rest2 = text[off2:].strip()
        r2off = off2 + (len(text[off2:]) - len(rest2))
        else_body: list = []

        if rest2.startswith('else'):
            after = rest2[4:].strip()
            ae = 4 + (len(rest2[4:]) - len(after))
            if after.startswith('if'):
                enode, ec = self._parse_if(after)
                if enode:
                    else_body = [enode]
                    off2 = r2off + ae + ec
            elif after.startswith('{'):
                bt, be = self._braced_text(rest2, ae)
                else_body = self._parse_block(bt)
                off2 = r2off + be
            else:
                se = self._stmt_end(after)
                else_body = self._parse_block(after[:se])
                off2 = r2off + ae + se

        return IfNode(pc, then, else_body), off2

    def _parse_struct_body(self, text: str) -> list:
        """Parse the body of a struct into an ordered list of ('field'|'method', ...) tuples.

        Each tuple is one of:
          ('field',  str)              — field declaration text
          ('method', StructMethodNode) — method (with optional body)

        Members are returned in source order.
        """
        members = []
        pos = 0
        text = text.strip()

        while pos < len(text):
            # skip whitespace
            while pos < len(text) and text[pos] in ' \t\n\r':
                pos += 1
            if pos >= len(text):
                break
            rem = text[pos:]

            # access specifiers: public: / private: / protected:
            m = re.match(r'(public|private|protected)\s*:', rem)
            if m:
                pos += m.end()
                continue

            # method: anything that contains '(' before ';' or '{'
            # Find the first ';' or '{' to decide
            # We must be careful not to confuse e.g. "int arr[10];" with a method
            first_semi = self._find_first_unquoted(rem, ';')
            first_brace = self._find_first_unquoted(rem, '{')
            first_paren = self._find_first_unquoted(rem, '(')

            # if there's a '(' and it comes before the first ';', it's a method
            is_method = (first_paren != -1 and
                         (first_semi == -1 or first_paren < first_semi))

            if is_method:
                # extract signature up to (and including) the closing ')'
                sig_end, _ = self._parens(rem, first_paren)
                # sig_end is the content; the closing ')' index = second return value
                _, paren_end = self._parens(rem, first_paren)
                signature = rem[:paren_end].strip()

                # does it have a body?
                after_paren = rem[paren_end:].lstrip()
                ap_off = paren_end + (len(rem[paren_end:]) - len(after_paren))

                if after_paren.startswith('{'):
                    body_text, be = self._braced_text(rem, ap_off)
                    body_nodes = self._parse_block(body_text)
                    # skip trailing ';' if any
                    rest = rem[be:].lstrip()
                    extra = be + (len(rem[be:]) - len(rest))
                    if rest.startswith(';'):
                        extra += 1
                    members.append(('method', StructMethodNode(signature, body_nodes)))
                    pos += extra
                else:
                    # declaration only (no body): find ';'
                    se = self._stmt_end(rem)
                    sig_text = rem[:se].strip().rstrip(';')
                    members.append(('method', StructMethodNode(sig_text, None)))
                    pos += se
            else:
                # field: read up to ';'
                se = first_semi + 1 if first_semi != -1 else len(rem)
                field_text = rem[:se].strip().rstrip(';')
                if field_text:
                    members.append(('field', field_text))
                pos += se

        return members

    def _find_first_unquoted(self, text: str, ch: str) -> int:
        """Return index of first occurrence of ch outside of strings, or -1."""
        i = 0
        while i < len(text):
            c = text[i]
            if c in ('"', "'"):
                q = c; i += 1
                while i < len(text) and text[i] != q:
                    if text[i] == '\\':
                        i += 1
                    i += 1
            elif c == ch:
                return i
            i += 1
        return -1

    # -- micro-helpers --

    def _parens(self, text, start):
        if start >= len(text) or text[start] != '(':
            return "", start
        d = 0
        i = start
        while i < len(text):
            ch = text[i]
            if ch in ('"', "'"):
                q = ch; i += 1
                while i < len(text) and text[i] != q:
                    if text[i] == '\\': i += 1
                    i += 1
            elif ch == '(':
                d += 1
            elif ch == ')':
                d -= 1
                if d == 0:
                    return text[start + 1:i], i + 1
            i += 1
        return text[start + 1:], len(text)

    def _braced_text(self, text, start):
        idx = text.find('{', start)
        if idx == -1:
            return "", len(text)
        d = 0; i = idx
        while i < len(text):
            ch = text[i]
            if ch in ('"', "'"):
                q = ch; i += 1
                while i < len(text) and text[i] != q:
                    if text[i] == '\\': i += 1
                    i += 1
            elif ch == '{':
                d += 1
            elif ch == '}':
                d -= 1
                if d == 0:
                    return text[idx + 1:i], i + 1
            i += 1
        return text[idx + 1:], len(text)

    def _stmt_end(self, text):
        dp = db = 0; i = 0
        while i < len(text):
            ch = text[i]
            if ch in ('"', "'"):
                q = ch; i += 1
                while i < len(text) and text[i] != q:
                    if text[i] == '\\': i += 1
                    i += 1
            elif ch == '(':
                dp += 1
            elif ch == ')':
                dp -= 1
            elif ch == '{':
                db += 1
            elif ch == '}':
                db -= 1
            elif ch == ';' and dp == 0 and db == 0:
                return i + 1
            i += 1
        return len(text)


# ============================================================================
# Draw.io XML Generator
# ============================================================================

class DrawioGenerator:
    """Generates draw.io XML from AST nodes, matching reference examples."""

    # -- styles --

    S_ELLIPSE = "ellipse;whiteSpace=wrap;html=1;"
    S_RECT = "rounded=0;whiteSpace=wrap;html=1;"
    S_DIAMOND = "rhombus;whiteSpace=wrap;html=1;"
    S_HEXAGON = "shape=hexagon;perimeter=hexagonPerimeter2;whiteSpace=wrap;html=1;fixedSize=1;"
    S_PARA = ("shape=parallelogram;perimeter=parallelogramPerimeter;"
              "whiteSpace=wrap;html=1;fixedSize=1;")
    S_PROCESS = "shape=process;whiteSpace=wrap;html=1;backgroundOutline=1;"
    S_ARROW = "endArrow=classic;html=1;rounded=0;"
    S_TEXT = ("text;html=1;whiteSpace=wrap;strokeColor=none;fillColor=none;"
              "align=center;verticalAlign=middle;rounded=0;")
    S_TEXT_L = ("text;html=1;whiteSpace=wrap;strokeColor=none;fillColor=none;"
                "align=left;verticalAlign=middle;rounded=0;")
    S_DASH = "endArrow=none;dashed=1;html=1;dashPattern=1 3;strokeWidth=2;rounded=0;"
    S_BRACKET = "endArrow=none;html=1;rounded=0;"
    S_INVIS = "rounded=0;whiteSpace=wrap;html=1;fillColor=none;strokeColor=none;"
    S_ARROW_NO_END = "endArrow=none;html=1;rounded=0;"

    # -- layout constants --
    #    Increased gaps and sizes to match reference examples.

    CX = 350          # centre X
    SY = 20           # start Y
    GAP = 30          # vertical gap between shapes
    BRACE_GAP = 18    # gap for { } brace text
    BRACE_OFF = 5     # offset from edge of gap to brace text
    RH = 30           # rect height
    EH = 30           # ellipse height
    DH = 50           # diamond height
    DW = 170          # diamond default width
    HH = 40           # hexagon height
    PH = 30           # parallelogram height
    RW = 120          # default rect / ellipse / process width
    EW = 120          # default ellipse width
    PROC_H = 30       # process (function call) height

    # Loop routing
    LOOP_BASE_OFF = 60    # base offset from shape edge for loop arrows
    LOOP_STEP = 25        # additional offset per nesting level
    ROUTE_MARGIN = 20     # extra margin from body shapes for routing lines

    # If branching
    IF_BRANCH_OFF = 160   # horizontal offset for if branches from center

    def __init__(self):
        self._cells: list = []
        self._edges: list = []
        self._id = 1
        self._cy = self.SY
        self._cx = self.CX
        self._mx = 0
        self._my = 0
        self._left_x = self.CX     # leftmost X of any cell placed
        self._right_x = self.CX    # rightmost X+W of any cell placed
        self._loop_depth = 0
        self._loop_route_counter = 0

    # -- id generator --

    def _uid(self):
        self._id += 1
        return f"c{self._id}"

    # -- text helpers --

    @staticmethod
    def _esc(text):
        return html.escape(str(text), quote=True)

    def _tw(self, text):
        """Estimate text pixel width."""
        return max(len(text) * 7 + 20, self.RW)

    # -- cell / edge primitives --

    def _cell(self, cid, style, val, x, y, w, h):
        self._cells.append(dict(id=cid, style=style, value=self._esc(val),
                                x=int(x), y=int(y), w=int(w), h=int(h)))
        self._mx = max(self._mx, x + w)
        self._my = max(self._my, y + h)
        # Track horizontal extent (skip invisible/text cells for routing)
        if style not in (self.S_INVIS, self.S_TEXT, self.S_TEXT_L):
            self._left_x = min(self._left_x, x)
            self._right_x = max(self._right_x, x + w)
        return cid

    def _edge(self, src, tgt, style=None, pts=None,
              ex: float = 0.5, ey: float = 1, nx: float = 0.5, ny: float = 0):
        if style is None:
            style = self.S_ARROW
        eid = self._uid()
        self._edges.append(dict(id=eid, src=src, tgt=tgt, style=style,
                                pts=pts or [], ex=ex, ey=ey, nx=nx, ny=ny))
        return eid

    def _invis(self, x, y, w=2, h=2):
        """Create an invisible merge-point cell."""
        cid = self._uid()
        return self._cell(cid, self.S_INVIS, "", int(x), int(y), w, h)

    # -- shape shortcuts --

    def _ellipse(self, text, y=None, w=None):
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.EW)
        return self._cell(self._uid(), self.S_ELLIPSE, text,
                          self._cx - w // 2, y, w, self.EH)

    def _rect(self, text, y=None, w=None):
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.RW)
        return self._cell(self._uid(), self.S_RECT, text,
                          self._cx - w // 2, y, w, self.RH)

    def _diamond(self, text, y=None, w=None):
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.DW)
        return self._cell(self._uid(), self.S_DIAMOND, text,
                          self._cx - w // 2, y, w, self.DH)

    def _hexagon(self, text, y=None, w=None):
        """Hexagon shape for for-loops."""
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.DW)
        return self._cell(self._uid(), self.S_HEXAGON, text,
                          self._cx - w // 2, y, w, self.HH)

    def _para(self, text, y=None, w=None):
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.RW)
        return self._cell(self._uid(), self.S_PARA, text,
                          self._cx - w // 2, y, w, self.PH)

    def _process(self, text, y=None, w=None):
        if y is None:
            y = self._cy
        if w is None:
            w = max(self._tw(text), self.RW)
        return self._cell(self._uid(), self.S_PROCESS, text,
                          self._cx - w // 2, y, w, self.PROC_H)

    def _text(self, text, x, y, w=30, h=20):
        return self._cell(self._uid(), self.S_TEXT, text, int(x), int(y), w, h)

    # -- public entry points --

    @staticmethod
    def _has_return(nodes: list) -> bool:
        """Check if any node (recursively) is a ReturnNode."""
        for n in nodes:
            if isinstance(n, ReturnNode):
                return True
            for attr in ('body', 'then_body', 'else_body'):
                sub = getattr(n, attr, None)
                if sub and DrawioGenerator._has_return(sub):
                    return True
        return False

    def generate_function(self, func: FunctionNode,
                          includes, usings, global_vars) -> str:
        self._reset()
        # function header ellipse
        fid = self._ellipse(func.signature)
        self._cy += self.EH + self.GAP

        # opening brace — centered in the gap between ellipse and first body element
        brace_y = self.SY + self.EH + self.GAP // 2 - 8
        self._text("{", self._cx - 15, brace_y, 20, 16)

        # body
        last = self._body(func.body, fid)

        # implicit return
        has_ret = self._has_return(func.body)
        is_void = func.signature.strip().startswith('void ')
        if not has_ret:
            # closing brace centered in gap before the return ellipse
            close_brace_y = self._cy - self.GAP // 2 - 8
            self._text("}", self._cx + 5, close_brace_y, 20, 16)
            if is_void:
                rid = self._ellipse("return;")
            else:
                rid = self._ellipse("return 0;")
            self._edge(last, rid)
            self._cy += self.EH + self.GAP
        else:
            # Return was already placed in _body; "}" centered in gap before return
            close_brace_y = self._cy - self.EH - self.GAP // 2 - 8
            self._text("}", self._cx + 5, close_brace_y, 20, 16)

        # annotation
        self._annotation(includes, usings, global_vars)
        return self._xml()

    def generate_define(self, d: DefineNode, includes) -> str:
        self._reset()
        hdr = f"{d.name}({d.params})"
        fid = self._ellipse(hdr)
        self._cy += self.EH + self.GAP
        last = self._body(d.body, fid)
        eid = self._ellipse("end")
        self._edge(last, eid)
        self._cy += self.EH + self.GAP
        if includes:
            ax = self._cx + 120
            ay = self.SY + 40
            self._edges.append(dict(id=self._uid(), src=None, tgt=None,
                                     style=self.S_DASH, pts=[
                                         (self._cx + 60, ay + 10),
                                         (ax, ay + 10)],
                                     ex=.5, ey=.5, nx=.5, ny=.5))
            # Square bracket "[" shape
            serif = 10
            bx = ax + 20
            y_top = ay - 5
            y_bot = ay + 30
            self._edges.append(dict(id=self._uid(), src=None, tgt=None,
                                     style=self.S_BRACKET, pts=[
                                         (bx + serif, y_top),
                                         (bx, y_top),
                                         (bx, y_bot),
                                         (bx + serif, y_bot)],
                                     ex=.5, ey=.5, nx=.5, ny=.5))
            html_lines = [f"<div>{self._esc(i.text)}</div>" for i in includes]
            txt = ''.join(html_lines)
            self._cell(self._uid(), self.S_TEXT_L, txt,
                       bx + serif + 5, ay - 5, 200, 40)
        return self._xml()

    def generate_struct(self, struct: 'StructNode') -> str:
        """Generate a draw.io flowchart for a C++ struct.

        Layout:
          oval  "struct Name"
          for each member in source order:
            rect        if it is a field
            process     if it is a method (double vertical lines)
          oval  "end"
        """
        self._reset()

        # header oval
        hdr = f"struct {struct.name}"
        sid = self._ellipse(hdr)
        self._cy += self.EH + self.GAP

        last = sid
        for kind, member in struct.members:
            if kind == 'field':
                w = self._tw(member)
                rid = self._rect(member, w=w)
                self._edge(last, rid)
                self._cy += self.RH + self.GAP
                last = rid
            else:  # method
                sig = member.signature
                w = self._tw(sig)
                pid = self._process(sig, w=w)
                self._edge(last, pid)
                self._cy += self.PROC_H + self.GAP
                last = pid

        # closing oval
        eid = self._ellipse("end")
        self._edge(last, eid)
        self._cy += self.EH + self.GAP

        return self._xml()

    # -- body processing --

    def _body(self, nodes: list, prev) -> str:
        last = prev
        for n in nodes:
            if isinstance(n, ReturnNode):
                rid = self._ellipse(n.text)
                self._edge(last, rid)
                self._cy += self.EH + self.GAP
                last = rid

            elif isinstance(n, WhileNode):
                last = self._while(n, last)

            elif isinstance(n, DoWhileNode):
                last = self._do_while(n, last)

            elif isinstance(n, ForNode):
                last = self._for(n, last)

            elif isinstance(n, RangeForNode):
                last = self._range_for(n, last)

            elif isinstance(n, IfNode):
                last = self._if(n, last)

            elif isinstance(n, CoutNode):
                w = self._tw(n.text)
                pid = self._para(n.text, w=w)
                self._edge(last, pid)
                self._cy += self.PH + self.GAP
                last = pid

            elif isinstance(n, CinNode):
                w = self._tw(n.text)
                pid = self._para(n.text, w=w)
                self._edge(last, pid)
                self._cy += self.PH + self.GAP
                last = pid

            elif isinstance(n, DeclarationNode):
                w = self._tw(n.text)
                rid = self._rect(n.text, w=w)
                self._edge(last, rid)
                self._cy += self.RH + self.GAP
                last = rid

            elif isinstance(n, AssignmentNode):
                w = self._tw(n.text)
                rid = self._rect(n.text, w=w)
                self._edge(last, rid)
                self._cy += self.RH + self.GAP
                last = rid

            elif isinstance(n, FunctionCallNode):
                w = self._tw(n.text)
                pid = self._process(n.text, w=w)
                self._edge(last, pid)
                self._cy += self.PROC_H + self.GAP
                last = pid

            elif isinstance(n, DeleteNode):
                w = self._tw(n.text)
                rid = self._rect(n.text, w=w)
                self._edge(last, rid)
                self._cy += self.RH + self.GAP
                last = rid

            elif isinstance(n, RawStatementNode):
                t = n.text.strip()
                if t and t != ';':
                    w = self._tw(t)
                    rid = self._rect(t, w=w)
                    self._edge(last, rid)
                    self._cy += self.RH + self.GAP
                    last = rid

            elif isinstance(n, MacroWrapperNode):
                w = self._tw(n.name)
                mid = self._rect(n.name, w=w)
                self._edge(last, mid)
                self._cy += self.RH + self.GAP
                self._text("(", self._cx - 5, self._cy - self.GAP + 2, 10, 16)
                last = self._body(n.body, mid)
                self._text(")", self._cx + 30, self._cy - 5, 10, 16)

        return last

    # ================================================================
    # Loop drawing
    # ================================================================

    def _loop_offset(self):
        """Get routing offset for current loop and increment counter."""
        off = self._loop_route_counter * self.LOOP_STEP
        self._loop_route_counter += 1
        return off

    def _while(self, node: WhileNode, prev):
        """While loop: diamond condition, "1" down to body, "0" right to exit."""
        dy = self._cy
        ctext = f"while({node.condition})"
        w = max(self._tw(ctext), self.DW)
        did = self._diamond(ctext, w=w)
        self._edge(prev, did)

        # "1" label and "{" brace: centered in the gap between diamond and body
        self._cy += self.DH + self.GAP
        brace_y = dy + self.DH + self.GAP // 2 - 8
        self._text("{", self._cx - 15, brace_y, 20, 16)
        self._text("1", self._cx - 35, brace_y, 20, 16)

        # "0" label: above-right of diamond (above the false-exit horizontal arrow)
        self._text("0", self._cx + w // 2 + 5, dy + self.DH // 2 - 20, 20, 16)

        # body — save X extent before, measure after
        save_lx = self._left_x
        save_rx = self._right_x
        self._left_x = self._cx
        self._right_x = self._cx
        self._loop_depth += 1
        last = self._body(node.body, did)
        self._loop_depth -= 1
        body_left = self._left_x
        body_right = self._right_x
        self._left_x = min(save_lx, body_left)
        self._right_x = max(save_rx, body_right)

        # closing brace: centered in the gap between last body element and loop-back
        close_brace_y = self._cy - self.GAP // 2 - 8
        self._text("}", self._cx + 5, close_brace_y, 20, 16)

        # loop-back: last -> down -> left -> up -> left side of diamond
        route_off = self._loop_offset()
        lx = min(body_left, self._cx - w // 2) - self.ROUTE_MARGIN - route_off
        loopback_y = self._cy + 5
        self._edge(last, did,
                   style=self.S_ARROW,
                   pts=[(self._cx, loopback_y),
                        (lx, loopback_y),
                        (lx, dy + self.DH // 2)],
                   ex=0.5, ey=1, nx=0, ny=0.5)

        # false exit: right side of diamond -> right -> down -> center (merge)
        merge_y = loopback_y + self.GAP
        mid = self._invis(self._cx - 1, merge_y)

        rx = max(body_right, self._cx + w // 2) + self.ROUTE_MARGIN + route_off
        self._edge(did, mid,
                   style=self.S_ARROW_NO_END,
                   pts=[(rx, dy + self.DH // 2),
                        (rx, merge_y),
                        (self._cx, merge_y)],
                   ex=1, ey=0.5, nx=0.5, ny=0)

        self._cy = merge_y + self.GAP
        return mid

    def _do_while(self, node: DoWhileNode, prev):
        """Do-while loop: body first, then diamond condition at bottom."""
        sy = self._cy
        # body — save X extent before, measure after
        save_lx = self._left_x
        save_rx = self._right_x
        self._left_x = self._cx
        self._right_x = self._cx
        self._loop_depth += 1
        last = self._body(node.body, prev)
        self._loop_depth -= 1
        body_left = self._left_x
        body_right = self._right_x
        self._left_x = min(save_lx, body_left)
        self._right_x = max(save_rx, body_right)

        dy = self._cy
        ctext = f"while({node.condition})"
        w = max(self._tw(ctext), self.DW)
        did = self._diamond(ctext, w=w)
        self._edge(last, did)

        # "1" = left (loop-back, true)
        self._text("1", self._cx - w // 2 - 25, dy + self.DH // 2 - 20, 20, 16)
        # "0" = right (exit, false)
        self._text("0", self._cx + w // 2 + 5, dy + self.DH // 2 - 20, 20, 16)

        self._cy += self.DH + self.GAP

        # loop-back (true) -- left and up
        route_off = self._loop_offset()
        lx = min(body_left, self._cx - w // 2) - self.ROUTE_MARGIN - route_off
        self._edge(did, prev,
                   style=self.S_ARROW,
                   pts=[(lx, dy + self.DH // 2), (lx, sy)],
                   ex=0, ey=0.5, nx=0, ny=0.5)

        # false exit -- right side
        merge_y = self._cy
        mid = self._invis(self._cx - 1, merge_y)

        rx = max(body_right, self._cx + w // 2) + self.ROUTE_MARGIN + route_off
        self._edge(did, mid,
                   style=self.S_ARROW_NO_END,
                   pts=[(rx, dy + self.DH // 2),
                        (rx, merge_y),
                        (self._cx, merge_y)],
                   ex=1, ey=0.5, nx=0.5, ny=0)

        self._cy = merge_y + self.GAP
        return mid

    def _for(self, node: ForNode, prev):
        """For loop: hexagon shape, "1" down to body, "0" right to exit."""
        dy = self._cy
        w = max(self._tw(node.header), self.DW)
        did = self._hexagon(node.header, w=w)
        self._edge(prev, did)

        # "1" label and "{" brace centered in gap between hexagon and body
        self._cy += self.HH + self.GAP
        brace_y = dy + self.HH + self.GAP // 2 - 8
        self._text("{", self._cx - 15, brace_y, 20, 16)
        self._text("1", self._cx - 35, brace_y, 20, 16)
        self._text("0", self._cx + w // 2 + 5, dy + self.HH // 2 - 20, 20, 16)

        # body — save X extent before, measure after
        save_lx = self._left_x
        save_rx = self._right_x
        self._left_x = self._cx
        self._right_x = self._cx
        self._loop_depth += 1
        last = self._body(node.body, did)
        self._loop_depth -= 1
        body_left = self._left_x
        body_right = self._right_x
        self._left_x = min(save_lx, body_left)
        self._right_x = max(save_rx, body_right)

        # closing brace: centered in the gap between last body element and loop-back
        close_brace_y = self._cy - self.GAP // 2 - 8
        self._text("}", self._cx + 5, close_brace_y, 20, 16)

        # loop-back
        route_off = self._loop_offset()
        lx = min(body_left, self._cx - w // 2) - self.ROUTE_MARGIN - route_off
        loopback_y = self._cy + 5
        self._edge(last, did,
                   style=self.S_ARROW,
                   pts=[(self._cx, loopback_y),
                        (lx, loopback_y),
                        (lx, dy + self.HH // 2)],
                   ex=0.5, ey=1, nx=0, ny=0.5)

        # false exit
        merge_y = loopback_y + self.GAP
        mid = self._invis(self._cx - 1, merge_y)

        rx = max(body_right, self._cx + w // 2) + self.ROUTE_MARGIN + route_off
        self._edge(did, mid,
                   style=self.S_ARROW_NO_END,
                   pts=[(rx, dy + self.HH // 2),
                        (rx, merge_y),
                        (self._cx, merge_y)],
                   ex=1, ey=0.5, nx=0.5, ny=0)

        self._cy = merge_y + self.GAP
        return mid

    def _range_for(self, node: RangeForNode, prev):
        """Range-based for: uses hexagon like regular for."""
        dy = self._cy
        w = max(self._tw(node.header), self.DW)
        did = self._hexagon(node.header, w=w)
        self._edge(prev, did)

        # labels: "{" and "1" centered in gap between hexagon and body
        self._cy += self.HH + self.GAP
        brace_y = dy + self.HH + self.GAP // 2 - 8
        self._text("{", self._cx - 15, brace_y, 20, 16)
        self._text("1", self._cx - 35, brace_y, 20, 16)
        self._text("0", self._cx + w // 2 + 5, dy + self.HH // 2 - 20, 20, 16)

        # body — save X extent before, measure after
        save_lx = self._left_x
        save_rx = self._right_x
        self._left_x = self._cx
        self._right_x = self._cx
        self._loop_depth += 1
        last = self._body(node.body, did)
        self._loop_depth -= 1
        body_left = self._left_x
        body_right = self._right_x
        self._left_x = min(save_lx, body_left)
        self._right_x = max(save_rx, body_right)

        # closing brace: centered in the gap between last body element and loop-back
        close_brace_y = self._cy - self.GAP // 2 - 8
        self._text("}", self._cx + 5, close_brace_y, 20, 16)

        # loop-back
        route_off = self._loop_offset()
        lx = min(body_left, self._cx - w // 2) - self.ROUTE_MARGIN - route_off
        loopback_y = self._cy + 5
        self._edge(last, did,
                   style=self.S_ARROW,
                   pts=[(self._cx, loopback_y),
                        (lx, loopback_y),
                        (lx, dy + self.HH // 2)],
                   ex=0.5, ey=1, nx=0, ny=0.5)

        # false exit
        merge_y = loopback_y + self.GAP
        mid = self._invis(self._cx - 1, merge_y)

        rx = max(body_right, self._cx + w // 2) + self.ROUTE_MARGIN + route_off
        self._edge(did, mid,
                   style=self.S_ARROW_NO_END,
                   pts=[(rx, dy + self.HH // 2),
                        (rx, merge_y),
                        (self._cx, merge_y)],
                   ex=1, ey=0.5, nx=0.5, ny=0)

        self._cy = merge_y + self.GAP
        return mid

    # ================================================================
    # If drawing
    # ================================================================

    def _if(self, node: IfNode, prev):
        """If statement: diamond, true exits left, false exits right.
        All arrows are strictly orthogonal (horizontal or vertical only)."""
        dy = self._cy
        ctext = f"if ({node.condition})"
        w = max(self._tw(ctext), self.DW)
        did = self._diamond(ctext, w=w)
        self._edge(prev, did)

        # "1" label: below-left of diamond (next to left branch arrow exit)
        self._text("1", self._cx - w // 2 - 25, dy + self.DH // 2 - 20, 20, 16)
        # "0" label: above-right of diamond (above the right branch arrow exit)
        self._text("0", self._cx + w // 2 + 5, dy + self.DH // 2 - 20, 20, 16)

        branch_off = self.IF_BRANCH_OFF

        self._cy += self.DH + self.GAP
        save_cx = self._cx
        save_y = self._cy

        # -- true branch (left) --
        true_cx = save_cx - branch_off
        self._cx = true_cx
        # "{" centered in gap between diamond bottom and body start
        brace_y = dy + self.DH + self.GAP // 2 - 8
        self._text("{", self._cx - 15, brace_y, 20, 16)

        # Place invis entry at the horizontal routing level (diamond mid-height),
        # so the edge from invis to first body element has visible length.
        entry_y = dy + self.DH // 2
        true_entry = self._invis(self._cx - 1, entry_y)
        self._edge(did, true_entry,
                   style=self.S_ARROW_NO_END,
                   pts=[(save_cx - w // 2, entry_y),
                        (true_cx, entry_y)],
                   ex=0, ey=0.5, nx=0.5, ny=0)

        true_last = self._body(node.then_body, true_entry)
        true_end = self._cy
        # "}" centered in gap between last body element and merge
        close_brace_y = self._cy - self.GAP // 2 - 8
        self._text("}", self._cx + 5, close_brace_y, 20, 16)
        self._cx = save_cx

        # -- false branch (right) --
        false_last = None
        false_end = save_y

        if node.else_body:
            self._cy = save_y
            false_cx = save_cx + branch_off

            if len(node.else_body) == 1 and isinstance(node.else_body[0], IfNode):
                # else-if chain
                self._cx = false_cx
                entry_y = dy + self.DH // 2
                false_entry = self._invis(self._cx - 1, entry_y)
                self._edge(did, false_entry,
                           style=self.S_ARROW_NO_END,
                           pts=[(save_cx + w // 2, entry_y),
                                (false_cx, entry_y)],
                           ex=1, ey=0.5, nx=0.5, ny=0)
                false_last = self._if(node.else_body[0], false_entry)
                false_end = self._cy
                self._cx = save_cx
            else:
                # else body
                self._cx = false_cx
                # "{" centered in gap between diamond bottom and body start
                brace_y = dy + self.DH + self.GAP // 2 - 8
                self._text("{", self._cx - 15, brace_y, 20, 16)
                entry_y = dy + self.DH // 2
                false_entry = self._invis(self._cx - 1, entry_y)
                self._edge(did, false_entry,
                           style=self.S_ARROW_NO_END,
                           pts=[(save_cx + w // 2, entry_y),
                                (false_cx, entry_y)],
                           ex=1, ey=0.5, nx=0.5, ny=0)
                false_last = self._body(node.else_body, false_entry)
                false_end = self._cy
                # "}" centered in gap between last body element and merge
                close_brace_y = self._cy - self.GAP // 2 - 8
                self._text("}", self._cx + 5, close_brace_y, 20, 16)
                self._cx = save_cx

        # -- merge --
        merge_y = max(true_end, false_end) + self.GAP
        self._cy = merge_y

        mid = self._invis(save_cx - 1, merge_y)

        # connect true branch -> merge (orthogonal: down, then right)
        self._edge(true_last, mid,
                   pts=[(true_cx, true_end),
                        (true_cx, merge_y),
                        (save_cx, merge_y)])

        if false_last:
            # connect false branch -> merge (orthogonal: down, then left)
            false_cx = save_cx + branch_off
            self._edge(false_last, mid,
                       pts=[(false_cx, false_end),
                            (false_cx, merge_y),
                            (save_cx, merge_y)])
        else:
            # no else -- false exit from diamond goes right then down to merge
            # Route just outside the rightmost element (not fixed branch_off)
            rx = max(self._right_x, save_cx + w // 2) + self.ROUTE_MARGIN
            self._edge(did, mid,
                       style=self.S_ARROW,
                       pts=[(rx, dy + self.DH // 2),
                            (rx, merge_y),
                            (save_cx, merge_y)],
                       ex=1, ey=0.5, nx=0.5, ny=0)

        # Track routing extent so enclosing loops route outside if-branches
        if node.else_body:
            self._right_x = max(self._right_x, save_cx + branch_off)
            self._left_x = min(self._left_x, save_cx - branch_off)
        else:
            # For if-no-else, rx was computed above; track it
            rx_actual = max(self._right_x, save_cx + w // 2) + self.ROUTE_MARGIN
            self._right_x = max(self._right_x, rx_actual)
            self._left_x = min(self._left_x, save_cx - branch_off)

        self._cy = merge_y + self.GAP
        return mid

    # ================================================================
    # Annotation
    # ================================================================

    def _annotation(self, includes, usings, global_vars):
        """Draw annotation block on the right side: includes, using, global vars.
        Format matches reference examples with proper grouping and blank lines."""
        if not includes and not usings and not global_vars:
            return

        # Build annotation text lines with proper grouping
        lines: list[str] = []
        for i in includes:
            lines.append(i.text)
        if lines and (usings or global_vars):
            lines.append("")
        for u in usings:
            lines.append(u.text)
        if usings and global_vars:
            lines.append("")
        for g in global_vars:
            lines.append(g.text)

        # Position: to the right of the function, clear of any routing arrows
        ax = max(self._right_x + 40, self._cx + 120)
        ay = self.SY + self.EH + 5

        # Dashed horizontal connector line
        self._edges.append(dict(id=self._uid(), src=None, tgt=None,
                                style=self.S_DASH,
                                pts=[(self._cx + 60, ay + 5), (ax, ay + 5)],
                                ex=.5, ey=.5, nx=.5, ny=.5))

        # Square bracket "[" shape: top serif, vertical bar, bottom serif
        bh = max(len(lines) * 16 + 10, 40)
        bracket_x = ax + 10
        serif = 10  # horizontal serif length
        y_top = ay - 10
        y_bot = ay - 10 + bh
        self._edges.append(dict(id=self._uid(), src=None, tgt=None,
                                style=self.S_BRACKET,
                                pts=[(bracket_x + serif, y_top),
                                     (bracket_x, y_top),
                                     (bracket_x, y_bot),
                                     (bracket_x + serif, y_bot)],
                                ex=.5, ey=.5, nx=.5, ny=.5))

        # Text block — use <div> per line for draw.io HTML rendering
        # Each line is wrapped in <div>...</div>; empty lines use <div><br></div>
        # Inner text with < > is escaped for HTML (e.g. <iostream> -> &lt;iostream&gt;)
        # Then the whole value is escaped again by _cell for XML attribute context
        html_lines = []
        for ln in lines:
            if ln:
                html_lines.append(f"<div>{self._esc(ln)}</div>")
            else:
                html_lines.append("<div><br></div>")
        txt = ''.join(html_lines)
        self._cell(self._uid(), self.S_TEXT_L, txt,
                   bracket_x + serif + 5, ay - 10, 280, bh)

    # -- XML serialisation --

    def _reset(self):
        self._cells.clear()
        self._edges.clear()
        self._id = 1
        self._cy = self.SY
        self._cx = self.CX
        self._mx = self._my = 0
        self._left_x = self.CX
        self._right_x = self.CX
        self._loop_depth = 0
        self._loop_route_counter = 0

    def _xml(self) -> str:
        pw = max(827, int(self._mx) + 100)
        ph = max(1169, int(self._my) + 100)
        L: list[str] = []
        a = L.append
        a('<mxfile host="app.diagrams.net" version="29.2.9">')
        a('  <diagram name="Page-1" id="d1">')
        a(f'    <mxGraphModel dx="1422" dy="784" grid="1" gridSize="10" guides="1"'
          f' tooltips="1" connect="1" arrows="1" fold="1" page="1" pageScale="1"'
          f' pageWidth="{pw}" pageHeight="{ph}" background="#ffffff" math="0" shadow="0">')
        a('      <root>')
        a('        <mxCell id="0" />')
        a('        <mxCell id="1" parent="0" />')

        for c in self._cells:
            a(f'        <mxCell id="{c["id"]}" parent="1"'
              f' style="{c["style"]}" value="{c["value"]}" vertex="1">')
            a(f'          <mxGeometry x="{c["x"]}" y="{c["y"]}"'
              f' width="{c["w"]}" height="{c["h"]}" as="geometry" />')
            a(f'        </mxCell>')

        for e in self._edges:
            s = e['style']
            sa = f' source="{e["src"]}"' if e['src'] else ''
            ta = f' target="{e["tgt"]}"' if e['tgt'] else ''
            if e['src']:
                s += f"exitX={e['ex']};exitY={e['ey']};exitDx=0;exitDy=0;"
            if e['tgt']:
                s += f"entryX={e['nx']};entryY={e['ny']};entryDx=0;entryDy=0;"
            a(f'        <mxCell id="{e["id"]}" edge="1" parent="1"'
              f'{sa}{ta} style="{s}" value="">')
            a(f'          <mxGeometry relative="1" as="geometry">')
            if e['pts']:
                a('            <Array as="points">')
                for px, py in e['pts']:
                    a(f'              <mxPoint x="{int(px)}" y="{int(py)}" />')
                a('            </Array>')
            if not e['src'] and e['pts']:
                px, py = e['pts'][0]
                a(f'            <mxPoint x="{int(px)}" y="{int(py)}" as="sourcePoint" />')
            if not e['tgt'] and e['pts'] and len(e['pts']) > 1:
                px, py = e['pts'][-1]
                a(f'            <mxPoint x="{int(px)}" y="{int(py)}" as="targetPoint" />')
            a('          </mxGeometry>')
            a('        </mxCell>')

        a('      </root>')
        a('    </mxGraphModel>')
        a('  </diagram>')
        a('</mxfile>')
        return '\n'.join(L)


# ============================================================================
# Main
# ============================================================================

def _func_name(sig: str) -> str:
    m = re.search(r'(\w+)\s*\(', sig)
    return m.group(1) if m else "unknown"


def convert(input_file: str, output_dir: str | None = None, png: bool = False):
    with open(input_file, encoding='utf-8') as f:
        src = f.read()

    if output_dir is None:
        output_dir = os.path.dirname(os.path.abspath(input_file))
    os.makedirs(output_dir, exist_ok=True)

    base = os.path.splitext(os.path.basename(input_file))[0]

    parser = CppParser(src)
    nodes = parser.parse()

    includes = [n for n in nodes if isinstance(n, IncludeNode)]
    usings = [n for n in nodes if isinstance(n, UsingNode)]
    gvars = [n for n in nodes if isinstance(n, GlobalVarNode)]
    funcs = [n for n in nodes if isinstance(n, FunctionNode)]
    defs = [n for n in nodes if isinstance(n, DefineNode)]
    structs = [n for n in nodes if isinstance(n, StructNode)]

    files: list[str] = []
    name_counts: dict[str, int] = {}

    for fn in funcs:
        g = DrawioGenerator()
        name = _func_name(fn.signature)
        # Annotation (includes/using/globals) only for main()
        if name == 'main':
            xml = g.generate_function(fn, includes, usings, gvars)
        else:
            xml = g.generate_function(fn, [], [], [])
        if name in name_counts:
            name_counts[name] += 1
            unique_name = f"{name}{name_counts[name]}"
        else:
            name_counts[name] = 1
            unique_name = name
        fname = f"{base}.drawio" if len(funcs) == 1 else f"{base}-{unique_name}.drawio"
        path = os.path.join(output_dir, fname)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(xml)
        print(f"  -> {path}")
        files.append(path)

    for d in defs:
        g = DrawioGenerator()
        xml = g.generate_define(d, includes)
        fname = f"{base}-{d.name}.drawio"
        path = os.path.join(output_dir, fname)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(xml)
        print(f"  -> {path}")
        files.append(path)

    for st in structs:
        # 1. Struct overview diagram: oval + fields (rect) + methods (process) + end
        g = DrawioGenerator()
        xml = g.generate_struct(st)
        fname = f"{base}-{st.name}.drawio"
        path = os.path.join(output_dir, fname)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(xml)
        print(f"  -> {path}")
        files.append(path)

        # 2. For every method that has a body, generate a full function flowchart
        method_name_counts: dict[str, int] = {}
        for kind, member in st.members:
            if kind != 'method':
                continue
            if member.body is None:
                continue  # only declaration, no body to diagram
            # wrap in a FunctionNode so generate_function can reuse it
            fn_node = FunctionNode(signature=member.signature, body=member.body)
            g2 = DrawioGenerator()
            xml2 = g2.generate_function(fn_node, [], [], [])
            mname = _func_name(member.signature)
            if mname in method_name_counts:
                method_name_counts[mname] += 1
                unique_mname = f"{mname}{method_name_counts[mname]}"
            else:
                method_name_counts[mname] = 1
                unique_mname = mname
            mfname = f"{base}-{st.name}_{unique_mname}.drawio"
            mpath = os.path.join(output_dir, mfname)
            with open(mpath, 'w', encoding='utf-8') as f:
                f.write(xml2)
            print(f"  -> {mpath}")
            files.append(mpath)

    if png:
        for df in files:
            _export_png(df, df + ".png")

    return files


def _export_png(drawio_file, png_file):
    cmds = ['drawio', 'draw.io', '/snap/bin/drawio', '/usr/local/bin/drawio']
    for cmd in cmds:
        for prefix in [[], ['xvfb-run', '-a']]:
            try:
                r = subprocess.run(
                    prefix + [cmd, '--export', '--format', 'png',
                              '--output', png_file, drawio_file],
                    capture_output=True, text=True, timeout=30)
                if r.returncode == 0:
                    print(f"  -> {png_file}")
                    return True
            except (FileNotFoundError, subprocess.TimeoutExpired):
                continue
    print(f"  !! PNG export failed for {drawio_file} (install draw.io CLI)")
    return False


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    inp = sys.argv[1]
    out = None
    do_png = False
    args = sys.argv[2:]
    i = 0
    while i < len(args):
        if args[i] == '--png':
            do_png = True
        elif args[i] in ('-o', '--output'):
            i += 1
            if i < len(args):
                out = args[i]
        elif not args[i].startswith('-'):
            out = args[i]
        i += 1

    if not os.path.exists(inp):
        print(f"Error: {inp} not found")
        sys.exit(1)

    print(f"Converting {inp} ...")
    files = convert(inp, out, do_png)
    print(f"Done -- {len(files)} file(s) generated.")


if __name__ == '__main__':
    main()
