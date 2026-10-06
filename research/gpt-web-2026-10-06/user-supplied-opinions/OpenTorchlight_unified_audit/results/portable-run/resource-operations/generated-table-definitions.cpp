// Generated logical values only. Initializer order and behavior require a separate check.

#include <string>

std::wstring sampleNames[8] = {
    std::wstring(L"", 0),
    std::wstring(L"SAVE", 4),
    std::wstring(L"A\000B", 3),
    std::wstring(L"\012\015\011", 3),
    std::wstring(L"quote\"slash\\", 12),
    std::wstring(L"\u0421\u043b\u043e\u0432\u043e", 5),
    std::wstring(L"\U0001f680", 1),
    std::wstring(L"\00177", 3)
};

std::wstring sampleTags[2][3] = {
{
    std::wstring(L"VALUE", 5),
    std::wstring(L"VALUE2", 6),
    std::wstring(L"VALUE3", 6)
},
{
    std::wstring(L"", 0),
    std::wstring(L"VALUE2", 6),
    std::wstring(L"", 0)
}
};

int sampleLimits[4] = {
    (-2147483647 - 1),
    -1,
    0,
    2147483647
};
