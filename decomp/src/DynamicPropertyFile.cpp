#include "DynamicPropertyFile.h"


float CDynamicPropertyFile::GetFloat(unsigned int property)
{
    if (property < m_floatValues.size())
        return m_floatValues[property];
    return -1.0f;
}

int CDynamicPropertyFile::GetInt(unsigned int property)
{
    if (property < m_intValues.size())
        return m_intValues[property];
    return -1;
}

const std::wstring& CDynamicPropertyFile::GetString(unsigned int property)
{
    if (property >= m_stringValues.size())
        return m_missingString;
    return m_stringValues[property];
}

bool CDynamicPropertyFile::isNonLocalVariable(const std::wstring& name)
{
    for (unsigned int i = 0; i < m_nonLocalVariables.size(); ++i)
        if (m_nonLocalVariables[i] == name)
            return true;
    return false;
}

bool CDynamicPropertyFile::SetString(unsigned int property, const std::wstring& value)
{
    if (property < m_stringValues.size())
    {
        m_stringValues[property] = value;
        if (property < m_callbacks.size())
            for (unsigned int i = 0; i < m_callbacks[property].size(); ++i)
                m_callbacks[property][i](property);
        return true;
    }
    return false;
}

void CDynamicPropertyFile::SetStatChangeCallback(unsigned int property, void (*callback)(unsigned int))
{
    if (callback)
        m_callbacks[property].push_back(callback);
}

bool CDynamicPropertyFile::SaveSettings(const std::wstring& file)
{
    if (!saveSettings(file, false))
        return false;
    if (!m_secondaryFile.empty())
        return saveSettings(m_secondaryFile, true);
    return true;
}

bool CDynamicPropertyFile::LoadSettings(const std::wstring& file)
{
    if (!loadSettings(file))
        return false;
    if (!m_secondaryFile.empty())
        return loadSettings(m_secondaryFile);
    return true;
}


bool CDynamicPropertyFile::SetInt(unsigned int property, int value)
{
    if (property >= m_intValues.size())
        return false;
    m_intValues[property] = value;
    if (property < m_callbacks.size())
        for (unsigned int i = 0; i < m_callbacks[property].size(); ++i)
            m_callbacks[property][i](property);
    return true;
}

bool CDynamicPropertyFile::SetFloat(unsigned int property, float value)
{
    if (property >= m_floatValues.size())
        return false;
    m_floatValues[property] = value;
    if (property < m_callbacks.size())
        for (unsigned int i = 0; i < m_callbacks[property].size(); ++i)
            m_callbacks[property][i](property);
    return true;
}

unsigned int CDynamicPropertyFile::GetStringPropertyIndex(const std::wstring& name, std::wstring value, bool nonLocal)
{
    if (m_stringIndices.find(name) != m_stringIndices.end())
        return m_stringIndices[name];
    m_stringValues.push_back(value);
    unsigned int index = m_stringValues.size() - 1;
    m_stringIndices[name] = index;
    if (nonLocal)
        m_nonLocalVariables.push_back(name);
    return index;
}

unsigned int CDynamicPropertyFile::GetFloatPropertyIndex(const std::wstring& name, float value, bool nonLocal)
{
    if (m_floatIndices.find(name) != m_floatIndices.end())
        return m_floatIndices[name];
    m_floatValues.push_back(value);
    unsigned int index = m_floatValues.size() - 1;
    m_floatIndices[name] = index;
    if (nonLocal)
        m_nonLocalVariables.push_back(name);
    return index;
}

unsigned int CDynamicPropertyFile::GetIntPropertyIndex(const std::wstring& name, int value, bool nonLocal)
{
    if (m_intIndices.find(name) != m_intIndices.end())
        return m_intIndices[name];
    m_intValues.push_back(value);
    unsigned int index = m_intValues.size() - 1;
    m_intIndices[name] = index;
    if (nonLocal)
        m_nonLocalVariables.push_back(name);
    return index;
}

#include "StringUtilities.h"

CDynamicPropertyFile::~CDynamicPropertyFile()
{
}

unsigned int CDynamicPropertyFile::SetFloat(const std::wstring& name, float value)
{
    if (m_floatIndices.find(name) == m_floatIndices.end())
    {
        m_floatValues.push_back(value);
        unsigned int index = m_floatValues.size() - 1;
        m_floatIndices[name] = index;
        return index;
    }
    unsigned int index = m_floatIndices[name];
    m_floatValues[index] = value;
    return index;
}

unsigned int CDynamicPropertyFile::SetInt(const std::wstring& name, int value)
{
    if (m_intIndices.find(name) == m_intIndices.end())
    {
        m_intValues.push_back(value);
        unsigned int index = m_intValues.size() - 1;
        m_intIndices[name] = index;
        return index;
    }
    unsigned int index = m_intIndices[name];
    m_intValues[index] = value;
    return index;
}

unsigned int CDynamicPropertyFile::SetString(const std::wstring& name, const std::wstring& value)
{
    unsigned int index;
    if (m_stringIndices.find(name) == m_stringIndices.end())
    {
        m_stringValues.push_back(value);
        index = m_stringValues.size() - 1;
        m_stringIndices[name] = index;
    }
    else
    {
        index = m_stringIndices[name];
        m_stringValues[index] = value;
    }
    return index;
}

void CDynamicPropertyFile::SetSetting(const std::wstring& name, const std::wstring& value)
{
    if (m_intIndices.find(name) != m_intIndices.end())
        m_intValues[m_intIndices[name]] = STRINGS::GetInt(value);
    else if (m_floatIndices.find(name) != m_floatIndices.end())
        SetFloat(m_floatIndices[name], STRINGS::GetFloat(value));
    else if (m_stringIndices.find(name) != m_stringIndices.end())
        m_stringValues[m_stringIndices[name]] = value;
}

CDynamicPropertyFile::CDynamicPropertyFile(std::wstring directory, std::wstring file, std::wstring section)
    : m_directory(directory), m_file(file), m_secondaryFile(section), m_missingString(L"-1")
{
    m_Unrecovered130[0] = 0;
    for (unsigned int i = 4; i < 8; ++i)
        m_Unrecovered130[i] = 0;
}

#include <cstdio>
#include <cwchar>
#include <queue>
#include "FileReader.h"
#include "LinuxUtils.h"
#include "UTFConversion.h"

bool CDynamicPropertyFile::saveSettings(const std::wstring& file, bool nonLocal)
{
    std::wstring fileName = file.compare(L"") == 0 ? m_file : file;
    if (nonLocal)
        fileName = m_secondaryFile;
    FILE* output = NULL;
    utf16string text;
    m_lastFileError = _wfopen_s(&output, (m_directory + L"/" + fileName).c_str(), L"w");
    unsigned short byteOrderMark = 0xfeff;
    fwrite(&byteOrderMark, 2, 1, output);
    if (!output)
        return false;

    unsigned int index = 0;
    std::map<std::wstring, unsigned int>::iterator it = m_intIndices.begin();
    while (index < m_intValues.size() && it != m_intIndices.end())
    {
        unsigned int property = it->second;
        if (property == index)
        {
            if (isNonLocalVariable(it->first) == nonLocal)
            {
                wchar_t buffer[200];
                std::wstring format = it->first + L" :%i\n";
                swprintf(buffer, 200, format.c_str(), m_intValues[property]);
                text = UTF32ToUTF16(std::wstring(buffer));
                fwrite(text.c_str(), text.length() * 2, 1, output);
            }
            index = property + 1;
            it = m_intIndices.begin();
        }
        else
            ++it;
    }

    index = 0;
    it = m_floatIndices.begin();
    while (index < m_floatValues.size() && it != m_floatIndices.end())
    {
        unsigned int property = it->second;
        if (property == index)
        {
            if (isNonLocalVariable(it->first) == nonLocal)
            {
                wchar_t buffer[200];
                std::wstring format = it->first + L" :%f\n";
                swprintf(buffer, 200, format.c_str(), GetFloat(property));
                text = UTF32ToUTF16(std::wstring(buffer));
                fwrite(text.c_str(), text.length() * 2, 1, output);
            }
            index = property + 1;
            it = m_floatIndices.begin();
        }
        else
            ++it;
    }

    index = 0;
    it = m_stringIndices.begin();
    while (index < m_stringValues.size() && it != m_stringIndices.end())
    {
        unsigned int property = it->second;
        if (property == index)
        {
            if (isNonLocalVariable(it->first) == nonLocal)
            {
                std::wstring line = it->first + L" :" + m_stringValues[property] + L"\n";
                text = UTF32ToUTF16(line);
                fwrite(text.c_str(), text.length() * 2, 1, output);
            }
            index = property + 1;
            it = m_stringIndices.begin();
        }
        else
            ++it;
    }
    fclose(output);
    return true;
}

bool CDynamicPropertyFile::loadSettings(const std::wstring& file)
{
    m_loaded = false;
    std::wstring fileName = file.compare(L"") == 0 ? m_file : file;
    CFileReader reader;
    if (reader.ReadFile(m_directory + L"/" + fileName))
    {
        std::queue<std::wstring> tokens;
        int lines = 0;
        while (!reader.EndOfFile())
        {
            std::wstring line = reader.ReadLine();
            {
                const wchar_t* separators = L" :";
                std::wstring separator(separators);
                size_t position = line.find(separators);
                if (position != std::wstring::npos)
                {
                    size_t start = 0;
                    do
                    {
                        std::wstring token = line.substr(start, position - start);
                        tokens.push(token);
                        start = position + separator.length();
                        position = line.find(separators, start);
                    } while (position != std::wstring::npos);
                    if (start < line.length())
                    {
                        std::wstring token = line.substr(start, line.length() - start);
                        tokens.push(token);
                    }
                }
                if (tokens.empty() && line.length() != 0)
                {
                    unsigned int last = 0;
                    for (unsigned int i = 0; i < line.length(); ++i)
                    {
                        if (line.c_str()[i] == separators[0])
                        {
                            std::wstring token = line.substr(last, i);
                            tokens.push(token);
                            last = i + 1;
                        }
                    }
                }
            }
            if (tokens.size() != 0)
            {
                std::wstring name = tokens.front();
                tokens.pop();
                if (tokens.size() != 0)
                {
                    std::wstring value = tokens.front();
                    SetSetting(name, value);
                }
                ++lines;
            }
            while (!tokens.empty())
                tokens.pop();
        }
        m_callbacks.resize(lines);
        m_loaded = true;
    }
    return m_loaded;
}
