float STRINGS::GetFloat(const std::string& text)
{
    return static_cast<float>(strtod(text.c_str(),NULL));
}
