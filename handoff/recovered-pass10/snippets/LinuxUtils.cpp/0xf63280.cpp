short GetKeyState(unsigned int key)
{
    return keyStates[key] ? static_cast<short>(0x8000) : 0;
}
