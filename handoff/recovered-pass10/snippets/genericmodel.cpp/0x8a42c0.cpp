void CGenericModel::queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed)
{
    queueBlendAnimation(getAnimationIndex(animation), loop, blend, speed);
}
