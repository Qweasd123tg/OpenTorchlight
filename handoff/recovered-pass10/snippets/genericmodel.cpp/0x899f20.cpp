const std::string& CGenericModel::getAnimationName(unsigned int animation) const
{
    return m_animationSet ? m_animationSet->m_lUnknown28[animation] : EMPTY_STRING;
}
