bool CGenericModel::animationPlaying(const std::string& animation) const
{
    return animationPlaying(getAnimationIndex(animation));
}
