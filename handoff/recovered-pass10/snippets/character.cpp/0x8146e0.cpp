int CCharacter::minimumAC()
{
    return static_cast<int>(ceilf(static_cast<float>(AC()) * 0.5f));
}
