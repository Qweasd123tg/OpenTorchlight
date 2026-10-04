#include <map>
#include <string>
#include <Ogre.h>
#define private public
#define protected public
#include "MoneyTaker.h"
#include "GameClient.h"
#include "Player.h"
#undef private
#undef protected
typedef char size_money[sizeof(CMoneyTaker)==0x68?1:-1];
typedef char size_client[sizeof(CGameClient)==0x3910?1:-1];
typedef char size_character[sizeof(CCharacter)==0x720?1:-1];
typedef char size_player[sizeof(CPlayer)==0xa70?1:-1];
typedef char offset_player[__builtin_offsetof(CGameClient,m_pPlayer)==0x58?1:-1];
typedef char offset_gold[__builtin_offsetof(CCharacter,m_iGold)==0x444?1:-1];
typedef char offset_ai[__builtin_offsetof(CCharacter,m_pAIManager)==0x718?1:-1];
typedef char offset_amount[__builtin_offsetof(CMoneyTaker,m_iAmount)==0x58?1:-1];
typedef char offset_resource[__builtin_offsetof(CMoneyTaker,m_pResourceManager)==0x60?1:-1];
