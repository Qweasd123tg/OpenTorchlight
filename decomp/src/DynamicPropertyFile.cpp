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
