int CEquipment::getMaxSockets()
{
    int iVar3;

    if (m_pDataGroup == NULL) {
        iVar3 = 0;
    }
    else {

        iVar3 = m_pDataGroup->GetDataValue(L"MAX_SOCKETS", 2);
    }
    return iVar3;
}
