bool CGenericModel::animationQueued(const std::string& animation) const
{
    return animationQueued(getAnimationIndex(animation));
}
