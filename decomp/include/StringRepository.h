#ifndef STRINGREPOSITORY_H
#define STRINGREPOSITORY_H

#include <map>
#include <string>

// Interns strings: every distinct string gets a sequential ID.
class CStringRepository
{
public:
    CStringRepository();
    ~CStringRepository();

    const std::wstring& GetString(unsigned int id);
    int GetStringID(const std::wstring& text);
    unsigned int AddString(const std::wstring& text);

private:
    typedef std::map<std::wstring, unsigned int> StringToID;

    unsigned int m_iNextID;
    std::map<unsigned int, StringToID::iterator> m_Strings;
    StringToID m_IDs;
    std::wstring m_sEmpty;
};

#endif
