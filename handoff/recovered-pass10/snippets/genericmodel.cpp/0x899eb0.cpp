TArrayList<int>* CGenericModel::getValueIndexes(int animation, CKeyframe* key)
{
    int index = findKey(animation, key);
    return &m_valueIndexes[animation][index];
}
