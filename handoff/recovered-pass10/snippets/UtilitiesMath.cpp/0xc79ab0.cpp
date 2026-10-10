void MATH::worldToLocal(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix)
{
    float x=point.x,y=point.y,z=point.z;
    result.x=x*matrix[0][0]+y*matrix[1][0]+z*matrix[2][0];
    result.y=x*matrix[0][1]+y*matrix[1][1]+z*matrix[2][1];
    result.z=x*matrix[0][2]+y*matrix[1][2]+z*matrix[2][2];
}
