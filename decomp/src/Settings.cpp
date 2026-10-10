#include "Settings.h"

void CSettings::findClosestResolution(int width,int height,int& resultWidth,int& resultHeight)
{
    for (unsigned int i = 0; i < m_resolutions.size(); ++i) {
        if (m_resolutions[i].width == width && m_resolutions[i].height == height) {
            resultWidth = width;
            resultHeight = height;
            return;
        }
        if (width >= m_resolutions[i].width) {
            resultWidth = m_resolutions[i].width;
            resultHeight = m_resolutions[i].height;
        }
    }
}

void CSettings::addResolutionCombo(int width, int height, bool flag8, bool flagA, bool flag9)
{
    CSettingsResolution resolution;
    resolution.width = width;
    resolution.height = height;
    resolution.flag8 = flag8;
    resolution.flagA = flagA;
    resolution.flag9 = flag9;
    m_resolutions.add(resolution);
}
