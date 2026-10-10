float CGameUI::scaledY(float value)
{
    return m_settings->GetFloat(KSETTINGS_YRATIO) * value;
}
