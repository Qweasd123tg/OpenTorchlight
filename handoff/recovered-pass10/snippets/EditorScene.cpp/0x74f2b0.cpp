unsigned int CEditorScene::saveObjectsHavingParent(long long parent, CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    unsigned int count=0;
    for (std::map<long long, CEditorBaseObject*>::iterator it=m_Objects.begin(); it!=m_Objects.end(); ++it) {
        if (it->second->getParentGuid()==parent && it->second->getDescriptor())
            count += saveObjectAndChildren(it->second, group, configuration);
    }
    return count;
}
