void CCharacter::queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed)
{
    if (m_pUnitModel) m_pUnitModel->queueBlendAnimation(animation, loop, blend, speed);
}
