/* address=008996e0
   symbol=CAttackDescription::CAttackDescription */


/* CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int,
   unsigned int, int, float) */

void __thiscall
CAttackDescription::CAttackDescription
          (CAttackDescription *this,string *param_1,bool param_2,float param_3,float param_4,
          uint param_5,uint param_6,int param_7,float param_8)

{
  long lVar1;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CAttackDescription_00fce390;
                    /* try { // try from 00899738 to 0089973c has its CatchHandler @ 008997cd */
  std::string::string((string *)(this + 0x10),param_1);
  this[0x18] = (CAttackDescription)param_2;
  *(float *)(this + 0x68) = param_3;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;
  *(float *)(this + 0x6c) = param_4;
  *(int *)(this + 0x74) = param_7;
  lVar1 = 0;
  *(undefined4 *)(this + 0x78) = 0;
  *(float *)(this + 0x70) = param_8;
  do {
    *(undefined4 *)(this + lVar1 + 0x24) = 0;
    *(undefined4 *)(this + lVar1 + 0x40) = 0;
    lVar1 = lVar1 + 4;
  } while (lVar1 != 0x1c);
  *(uint *)(this + 0x24) = param_6;
  *(uint *)(this + 0x40) = param_5;
  return;
}
