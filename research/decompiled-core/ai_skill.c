/* Targeted Ghidra class export.
   namespace=CAISkill
   Treat pseudocode as navigation evidence. */


/* address=00d86560
   symbol=CAISkill::update */

/* CAISkill::update(float) */

bool __thiscall CAISkill::update(CAISkill *this,float param_1)

{
  float fVar1;
  float fVar2;

  fVar2 = DAT_00fa47f8;
  fVar1 = *(float *)(this + 0x10);
  *(float *)(this + 0x10) = fVar1 - param_1;
  return fVar2 < fVar1 - param_1;
}



/* address=00d86580
   symbol=CAISkill::CAISkill */

/* CAISkill::CAISkill(std::wstring) */

void __thiscall CAISkill::CAISkill(CAISkill *this)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CAISkill_00ffa8f0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 **)(this + 0x18) = &DAT_01424558;
                    /* try { // try from 00d865be to 00d865c2 has its CatchHandler @ 00d865d6 */
  std::wstring::assign((wstring_conflict *)(this + 0x18));
  return;
}



/* address=00d86600
   symbol=CAISkill::_GLOBAL__I_CAISkill */

/* CAISkill::CAISkill(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>
   >) */

void CAISkill::_GLOBAL__I_CAISkill(void)

{
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;
  allocator local_18;
  allocator local_17;
  allocator local_16;
  allocator local_15;
  allocator local_14;
  allocator local_13;
  allocator local_12;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
                    /* try { // try from 00d86675 to 00d86679 has its CatchHandler @ 00d86893 */
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&local_9);
                    /* try { // try from 00d8668e to 00d86692 has its CatchHandler @ 00d869c5 */
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&local_a);
                    /* try { // try from 00d866a7 to 00d866ab has its CatchHandler @ 00d869b5 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&local_b);
                    /* try { // try from 00d866c0 to 00d866c4 has its CatchHandler @ 00d869a5 */
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&local_c);
                    /* try { // try from 00d866d9 to 00d866dd has its CatchHandler @ 00d86995 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&local_d);
                    /* try { // try from 00d866f2 to 00d866f6 has its CatchHandler @ 00d86987 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&local_e);
                    /* try { // try from 00d86708 to 00d8670c has its CatchHandler @ 00d86982 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&local_f);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
                    /* try { // try from 00d86732 to 00d86736 has its CatchHandler @ 00d86976 */
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&local_10);
                    /* try { // try from 00d8674b to 00d8674f has its CatchHandler @ 00d86974 */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&local_11);
                    /* try { // try from 00d86764 to 00d86768 has its CatchHandler @ 00d86972 */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&local_12);
                    /* try { // try from 00d8677d to 00d86781 has its CatchHandler @ 00d8696c */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&local_13);
                    /* try { // try from 00d86796 to 00d8679a has its CatchHandler @ 00d8696a */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&local_14);
                    /* try { // try from 00d867ac to 00d867b0 has its CatchHandler @ 00d86939 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&local_15);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
                    /* try { // try from 00d867d6 to 00d867da has its CatchHandler @ 00d86937 */
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&local_16);
                    /* try { // try from 00d867ec to 00d867f0 has its CatchHandler @ 00d86906 */
  std::wstring::wstring((wstring_conflict *)&DAT_0150c938,L"ABOVE",&local_17);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
                    /* try { // try from 00d86816 to 00d8681a has its CatchHandler @ 00d86904 */
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&local_18);
                    /* try { // try from 00d8682f to 00d86833 has its CatchHandler @ 00d86902 */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&local_19);
                    /* try { // try from 00d86848 to 00d8684c has its CatchHandler @ 00d868ff */
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&local_1a);
                    /* try { // try from 00d86861 to 00d86865 has its CatchHandler @ 00d868fd */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&local_1b);
                    /* try { // try from 00d86877 to 00d8687b has its CatchHandler @ 00d868c4 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&local_1c);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  return;
}



/* address=00d86c20
   symbol=CAISkill::~CAISkill */

/* WARNING: Removing unreachable block (ram,0x00d86c70) */
/* CAISkill::~CAISkill() */

void __thiscall CAISkill::~CAISkill(CAISkill *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CAISkill_00ffa8f0;
  paVar1 = (allocator *)(*(long *)(this + 0x18) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x18) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00d86c80
   symbol=CAISkill::~CAISkill */

/* CAISkill::~CAISkill() */

void __thiscall CAISkill::~CAISkill(CAISkill *this)

{
  ~CAISkill(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=5 failures=0 */
