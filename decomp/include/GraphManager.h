#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <map>
#include <string>
#include "RunicCore.h"
#include "Graph.h"

class CGraphManager : public CRunicCore
{
public:
    CGraphManager(const std::wstring& directory);
    virtual ~CGraphManager();
    static CGraphManager* getSingleton();
    void clear();
    CGraph* getGraphByFileName(const std::wstring& filename);
    CGraph* getGraph(const std::wstring& name);
    void loadGraph(std::wstring filename);
    void reload();

private:
    std::wstring m_sDirectory;
    std::map<std::wstring, CGraph*> m_GraphsByName;
    std::map<std::wstring, CGraph*> m_GraphsByFilename;
    TArrayList<CRunicCore*> m_OwnedObjects;
};

#endif
