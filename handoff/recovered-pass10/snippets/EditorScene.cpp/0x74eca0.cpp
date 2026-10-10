void CEditorScene::setFileLoaded(const std::wstring& path)
{
    m_sFileLoaded = FILESYSTEM::CleanPath(path);
}
