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
