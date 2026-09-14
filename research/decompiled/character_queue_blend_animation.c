/* address=0080fd80
   symbol=CCharacter::queueBlendAnimation */


/* CCharacter::queueBlendAnimation(std::string const&, bool, float, float) */

void __thiscall
CCharacter::queueBlendAnimation
          (CCharacter *this,string *param_1,bool param_2,float param_3,float param_4)

{
  if (*(CGenericModel **)(this + 0x200) != (CGenericModel *)0x0) {
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 0x200),param_1,param_2,param_3,param_4);
    return;
  }
  return;
}
