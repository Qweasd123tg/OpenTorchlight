
/* WARNING: Removing unreachable block (ram,0x0087f946) */
/* CEquipment::getMaxSockets() */

int __thiscall CEquipment::getMaxSockets(CEquipment *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  long local_28;
  allocator local_19;
  
  if (this->m_pDataGroup == (CDataGroup *)0x0) {
    iVar3 = 0;
  }
  else {
                    /* try { // try from 0087f8b5 to 0087f8d3 has its CatchHandler @ 0087f92e */
    std::wstring::wstring((wstring *)&local_28,L"MAX_SOCKETS",&local_19);
    iVar3 = CDataGroup::GetDataValue(this->m_pDataGroup,(wstring *)&local_28,2);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
  }
  return iVar3;
}

