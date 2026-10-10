void CDynamicLine::update()
{
    if (m_dirty) fillHardwareBuffers();
}
