"""Conservative SDK geometry-call repair for drafts; never production acceptance."""
import re,sys
sys.path.insert(0,'tools/decomp')
import ghidra_cpp
GEOMETRY={'getWidth':(0,True),'getHeight':(0,True),'getSize':(0,True),'setSize':(1,False),'setPosition':(1,False)}
def code_mask(text):
    # Preserve offsets while ignoring comments and quoted contents.
    pattern=r'//[^\n]*|/\*.*?\*/|L?"(?:\\.|[^"\\])*"|L?\'(?:\\.|[^\'\\])*\''
    return re.sub(pattern,lambda m:''.join('\n' if c=='\n' else ' ' for c in m.group()),text,flags=re.S)
def pure_pointer(text):
    # Only local/member pointer reads with an optional type cast. No function
    # calls, arithmetic, assignments, increments or speculative alias rewrites.
    return bool(re.fullmatch(r'(?:\([\w: ]+\s*\*\)\s*)?[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*|\[\d+\])*',text.strip()))
def rewrite(text):
    mask=code_mask(text);changes=[];records=[]
    pattern=re.compile(r'(?<![\w:])CEGUI::Window::(getWidth|getHeight|getSize|setSize|setPosition)\s*\(')
    for m in pattern.finditer(mask):
        end=m.end()+ghidra_cpp.closing_paren(mask[m.end():])+1
        method=m.group(1);count,sret=GEOMETRY[method]
        args=ghidra_cpp.split_args(text[m.end():end-1]);args=[a.strip() for a in args if a.strip()]
        if len(args)!=count+1+int(sret):continue
        prefix=''
        if sret:
            match=re.fullmatch(r'&([A-Za-z_]\w*)',args.pop(0))
            if not match:continue
            prefix=match.group(1)+' = '
        obj=args.pop(0)
        if not pure_pointer(obj):continue
        actual=[]
        for arg in args:
            match=re.fullmatch(r'&([A-Za-z_]\w*)',arg)
            if not match:break
            actual.append(match.group(1))
        else:
            # Explicit qualification retains the original direct library call;
            # do not accidentally introduce virtual dispatch through the object.
            result=prefix+'((CEGUI::Window*)('+obj+'))->CEGUI::Window::'+method+'('+', '.join(actual)+')'
            changes.append((m.start(),end,result));records.append({'method':method,'before':text[m.start():end],'after':result})
    for start,end,result in reversed(changes):text=text[:start]+result+text[end:]
    return text,records
