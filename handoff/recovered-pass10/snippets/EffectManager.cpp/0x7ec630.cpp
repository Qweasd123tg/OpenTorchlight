CAffix* CEffectManager::cloneAffix(CAffix* affix, unsigned int level, CBaseUnit* source, float scale)
{
    CAffix* result=NULL;
    if (affix) {
        result=new CAffix(affix, level);
        if (result) {
            result->addEffectsToEffectManager(this);
            if (scale>0.0f) result->m_fDuration=scale;
            addAffix(result,level,source,scale);
            clearOutDescriptions();
        }
    }
    return result;
}
