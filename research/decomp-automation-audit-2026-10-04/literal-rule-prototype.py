import re

def inline_temp_strings(text):
    """std::wstring::wstring((T *)local_x, L"lit", &alloc); ... (T *)local_x  ->  L"lit"."""
    temps = {}

    def capture(m):
        temps[m.group(1)] = m.group(2)
        return ""
    text = re.sub(r"\n[ \t]*std::w?string::(?:w?string|basic_string)\s*\(\s*\([\w:]+ \*\)&?(local_\w+)\s*,\s*"
                  r"(L?\"(?:[^\"\\]|\\.)*\")\s*,\s*&?local_\w+\s*\);", capture, text)
    for local, literal in temps.items():
        text = re.sub(rf"\n[ \t]*[\w:<>]+[ \t]*\**[ \t]*{local}[ \t]*(?:\[\d*\])?;", "", text)
        text = re.sub(rf"\([\w:]+ \*\)&?{local}\b", lambda _match: literal, text)
        text = re.sub(rf"&{local}\b|\b{local}\b(?!\s*\[)", lambda _match: literal, text)
    return text
