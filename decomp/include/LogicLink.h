#ifndef LOGICLINK_H
#define LOGICLINK_H

#include <fstream>
#include <string>

#include "DataGroup.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "LogicObject.h"
#include "LogicWrapper.h"
#include "RunicCore.h"

class CLogicLink : public CRunicCore
{
public:
	virtual ~CLogicLink();

	long long GetObjectIDInitiatingLink();
	unsigned int GetEventIDForOutput();
	long long GetInputFuncID();
	long long GetOutputFuncID();
	long long GetObjectLinkingTo();
	long long GetObjectInitiatingLink();

	CLogicLink(
		CEditorScene* pEditorScene,
		CLogicObject* pInitiatingLogicObject,
		CLogicWrapper* pOutputLogicWrapper,
		CLogicObject* pLinkingToLogicObject,
		CLogicWrapper* pInputLogicWrapper
	);

	void saveLogicLinksToBinaryFile(
		std::basic_ofstream<char, std::char_traits<char> >* pFile
	);
	void saveLogicLinksToDataGroup(CDataGroup* pDataGroup);
	void InitiateInputEvent(
		unsigned int uiEventID,
		CEditorBaseObject* pInitiatingObject
	);

	CEditorScene* m_pEditorScene;
	CDescriptor* m_pLinkingToDescriptor;
	CLogicObject* m_pInitiatingLogicObject;
	CLogicObject* m_pLinkingToLogicObject;
	CLogicWrapper* m_pInputLogicWrapper;
	CLogicWrapper* m_pOutputLogicWrapper;
};

#endif
