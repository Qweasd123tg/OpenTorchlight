bool FILESYSTEM::FileExists(const std::wstring& path)
{
    return FileExists(path.c_str());
}
