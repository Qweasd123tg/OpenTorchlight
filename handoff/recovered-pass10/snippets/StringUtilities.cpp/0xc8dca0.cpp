std::wstring STRINGS::GetValueAsWString(bool value)
{
    if(value)return std::wstring(L"true");
    return std::wstring(L"false");
}
