void CEditorScene::setChildrenVisible(long long parent, bool visible)
{
    for (std::map<long long, CEditorBaseObject*>::iterator i=m_Objects.begin(); i!=m_Objects.end(); ++i) {
        if (i->second->isChildOfObject(parent)) {
            CSceneNodeObject* object = dynamic_cast<CSceneNodeObject*>(i->second);
            if (object) object->setVisible(visible);
        }
    }
}
