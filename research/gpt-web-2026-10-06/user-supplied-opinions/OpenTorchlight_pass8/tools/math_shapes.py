"""Strict ordered expression recognition. No algebraic reassociation is allowed."""
from __future__ import annotations
import ast

def _name(n): return n.id if isinstance(n,ast.Name) else None

def squared_length(expression:str,known_floats:set[str])->dict|None:
    try: n=ast.parse(expression,mode='eval').body
    except SyntaxError:return None
    if not (isinstance(n,ast.BinOp) and isinstance(n.op,ast.Add)
            and isinstance(n.left,ast.BinOp) and isinstance(n.left.op,ast.Add)):return None
    out=[]
    for term in [n.left.left,n.left.right,n.right]:
        if not isinstance(term,ast.BinOp) or not isinstance(term.op,ast.Mult):return None
        a,b=_name(term.left),_name(term.right)
        if a!=b or a not in known_floats:return None
        out.append(a)
    return {'kind':'ordered_squares3','components':out,
            'candidate':'Ogre::Vector3('+', '.join(out)+').squaredLength()',
            'requirements':['nonvolatile float32 inputs','same operation order and FP environment',
                            'same operand bit patterns','compiler and original comparison required']}
