TArrayList<CEditorBaseObject*>* CEditorScene::GetObjectsCreatedByADescriptor(CDescriptor* descriptor)
{
    return descriptor ? &descriptor->m_Objects : NULL;
}
