#include "EmptyStrings.h"
#include "GraphManager.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"

static CGraphManager* g_pGraphManager = NULL;

CGraphManager::CGraphManager(const std::wstring& directory)
    : m_sDirectory(directory), m_OwnedObjects(10)
{
    m_sDirectory = FILESYSTEM::CleanPath(STRINGS::StringUpper(m_sDirectory));
    g_pGraphManager = this;
    reload();
}

CGraphManager* CGraphManager::getSingleton()
{
    return g_pGraphManager;
}

CGraphManager::~CGraphManager()
{
    clear();
    m_OwnedObjects.deleteAll();
    g_pGraphManager = NULL;
}

void CGraphManager::clear()
{
    for (std::map<std::wstring, CGraph*>::iterator i = m_GraphsByName.begin(); i != m_GraphsByName.end(); ++i)
    {
        if (i->second != NULL)
        {
            delete i->second;
            i->second = NULL;
        }
    }
    m_GraphsByName.clear();
    m_GraphsByFilename.clear();
}

CGraph* CGraphManager::getGraphByFileName(const std::wstring& filename)
{
    std::map<std::wstring, CGraph*>::iterator i = m_GraphsByFilename.find(filename);
    return i != m_GraphsByFilename.end() ? i->second : NULL;
}

CGraph* CGraphManager::getGraph(const std::wstring& name)
{
    std::map<std::wstring, CGraph*>::iterator i = m_GraphsByName.find(name);
    return i != m_GraphsByName.end() ? i->second : NULL;
}

void CGraphManager::loadGraph(std::wstring filename)
{
    filename = STRINGS::StringUpper(filename);
    filename = FILESYSTEM::CleanPath(filename);
    CGraph* graph = new CGraph(filename);
    if (graph->getName().empty())
    {
        delete graph;
        return;
    }
    std::wstring name = STRINGS::StringUpper(graph->getName());
    if (m_GraphsByName.find(name) != m_GraphsByName.end())
    {
        delete graph;
        return;
    }
    m_GraphsByFilename[filename] = graph;
    m_GraphsByName[name] = graph;
}

void CGraphManager::reload()
{
    clear();
    TArrayList<std::wstring> files(25);
    CFileSystem::getSingleton()->getFileList(m_sDirectory, files, L"*.dat", true, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i)
        loadGraph(files[i]);
}
