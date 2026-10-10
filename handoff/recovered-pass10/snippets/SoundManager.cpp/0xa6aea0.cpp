FMOD_RESULT CSoundManager::fmodFileSeekCallback(void* handle, unsigned int position, void* userData)
{
    if (handle && !static_cast<CSoundInstance*>(handle)->m_stream.isNull()) {
        static_cast<CSoundInstance*>(handle)->m_stream->seek(position);
        return FMOD_OK;
    }
    return static_cast<FMOD_RESULT>(20);
}
