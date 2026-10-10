FMOD_RESULT CSoundManager::fmodFileReadCallback(void* handle, void* buffer, unsigned int length, unsigned int* bytesRead, void* userData)
{
    *bytesRead = static_cast<CSoundInstance*>(handle)->m_stream->read(buffer, length);
    return *bytesRead ? FMOD_OK : static_cast<FMOD_RESULT>(22);
}
