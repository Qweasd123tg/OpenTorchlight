void CPlayer::soldItem(CEquipment* equipment)
{
    CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(17), 1);
}
