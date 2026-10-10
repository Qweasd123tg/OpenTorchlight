bool CEditorScene::canObjectBeSaved(CResourceManager* manager, CEditorBaseObject* object)
{
    for (;;) {
        if (static_cast<signed char>(object->getDescriptor()->m_iFlags) < 0) return false;
        if (object->HasBaseObjectFlag(EDITOROBJECT_FLAG_DONT_SAVE)) return false;
        long long parent = object->getParentGuid();
        if (parent == -1) return true;
        std::map<long long, CEditorBaseObject*>::iterator found = m_Objects.find(parent);
        if (found == m_Objects.end()) return true;
        object = found->second;
        if (!object) return true;
    }
}
