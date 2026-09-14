/* address=00887a90
   symbol=CEquipment::equipped */


/* CEquipment::equipped(CInventory*, CCharacter*, EEQUIP_LOCATIONS) */

void __thiscall
CEquipment::equipped(CEquipment *this,undefined8 param_2_00,undefined8 param_2,undefined4 param_4)

{
  resetVisualLayout(this);
  (**(code **)(*(long *)this + 0x208))(this,0);
  setRenderBehind(this,true);
  attachToGivenLocation(this,param_2,param_4);
  if (this[0x1d0] == (CEquipment)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00887b21. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x6c);
  return;
}
