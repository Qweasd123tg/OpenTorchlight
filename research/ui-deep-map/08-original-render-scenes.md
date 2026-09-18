# 08-original-render-scenes

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `research/decompiled-core/game.c:1770–2180`

SHA256 полного файла: `446b47ef83b1acdf3b14b3666add65df19f201bcfd6b34e3c8e800a7db733357`

```text
 1770 | /* address=005613f0
 1771 |    symbol=CGame::createCamera */
 1772 | 
 1773 | /* WARNING: Removing unreachable block (ram,0x00561831) */
 1774 | /* WARNING: Removing unreachable block (ram,0x00561872) */
 1775 | /* WARNING: Removing unreachable block (ram,0x00561880) */
 1776 | /* CGame::createCamera() */
 1777 | 
 1778 | void __thiscall CGame::createCamera(CGame *this)
 1779 | 
 1780 | {
 1781 |   int *piVar1;
 1782 |   code *pcVar2;
 1783 |   int iVar3;
 1784 |   Vector3 *pVVar4;
 1785 |   Vector3 *pVVar5;
 1786 |   Vector3 *pVVar6;
 1787 |   CCameraControl *this_00;
 1788 |   long local_98 [2];
 1789 |   long local_88 [2];
 1790 |   long local_78 [2];
 1791 |   float local_68 [4];
 1792 |   float local_58 [4];
 1793 |   float local_48 [3];
 1794 |   allocator local_3b;
 1795 |   allocator local_3a;
 1796 |   allocator local_39 [9];
 1797 | 
 1798 |   if (*(long **)(this + 0x38) != (long *)0x0) {
 1799 |     (**(code **)(**(long **)(this + 0x38) + 8))();
 1800 |     *(undefined8 *)(this + 0x38) = 0;
 1801 |   }
 1802 |   pcVar2 = *(code **)(**(long **)(this + 0x50) + 0x1a8);
 1803 |                     /* try { // try from 00561441 to 00561445 has its CatchHandler @ 00561856 */
 1804 |   std::string::string((string *)local_78,"PlayerCam",local_39);
 1805 |                     /* try { // try from 0056144d to 0056144f has its CatchHandler @ 0056183c */
 1806 |   pVVar4 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x50),(string *)local_78);
 1807 |   if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1808 |     LOCK();
 1809 |     piVar1 = (int *)(local_78[0] + -8);
 1810 |     iVar3 = *piVar1;
 1811 |     *piVar1 = *piVar1 + -1;
 1812 |     UNLOCK();
 1813 |     if (iVar3 < 1) {
 1814 |       std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
 1815 |     }
 1816 |   }
 1817 |   local_48[0] = DAT_00fa4814 * Ogre::Math::fDeg2Rad;
 1818 |   (**(code **)(*(long *)pVVar4 + 0x248))(pVVar4,local_48);
 1819 |   Ogre::Camera::setPosition(pVVar4);
 1820 |   Ogre::Camera::lookAt(pVVar4);
 1821 |   (**(code **)(*(long *)pVVar4 + 600))(DAT_00fa47fc,pVVar4);
 1822 |   Ogre::Camera::setAutoAspectRatio(SUB81(pVVar4,0));
 1823 |   iVar3 = CDynamicPropertyFile::GetInt
 1824 |                     (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NETBOOK_MODE);
 1825 |   if (iVar3 == 1) {
 1826 |     (**(code **)(*(long *)pVVar4 + 0x268))(DAT_00fa4818,pVVar4);
 1827 |   }
 1828 |   else {
 1829 |     (**(code **)(*(long *)pVVar4 + 0x268))(DAT_00fa481c,pVVar4);
 1830 |   }
 1831 |   pcVar2 = *(code **)(**(long **)(this + 0x58) + 0x1a8);
 1832 |                     /* try { // try from 0056155e to 00561562 has its CatchHandler @ 00561826 */
 1833 |   std::string::string((string *)local_88,"UICam",&local_3a);
 1834 |                     /* try { // try from 0056156a to 0056156c has its CatchHandler @ 00561862 */
 1835 |   pVVar5 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x58),(string *)local_88);
 1836 |   if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1837 |     LOCK();
 1838 |     piVar1 = (int *)(local_88[0] + -8);
 1839 |     iVar3 = *piVar1;
 1840 |     *piVar1 = *piVar1 + -1;
 1841 |     UNLOCK();
 1842 |     if (iVar3 < 1) {
 1843 |       std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
 1844 |     }
 1845 |   }
 1846 |   (**(code **)(*(long *)pVVar5 + 0x368))(pVVar5,0);
 1847 |   local_58[0] = DAT_00fa4814 * Ogre::Math::fDeg2Rad;
 1848 |   (**(code **)(*(long *)pVVar5 + 0x248))(pVVar5,local_58);
 1849 |   Ogre::Camera::setPosition(pVVar5);
 1850 |   Ogre::Camera::lookAt(pVVar5);
 1851 |   (**(code **)(*(long *)pVVar5 + 600))(DAT_00fa480c,pVVar5);
 1852 |   (**(code **)(*(long *)pVVar5 + 0x268))(DAT_00fa481c,pVVar5);
 1853 |   Ogre::Camera::setAutoAspectRatio(SUB81(pVVar5,0));
 1854 |   pcVar2 = *(code **)(**(long **)(this + 0x48) + 0x1a8);
 1855 |                     /* try { // try from 00561666 to 0056166a has its CatchHandler @ 00561858 */
 1856 |   std::string::string((string *)local_98,"BKCam",&local_3b);
 1857 |                     /* try { // try from 00561672 to 00561674 has its CatchHandler @ 00561849 */
 1858 |   pVVar6 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x48),(string *)local_98);
 1859 |   if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1860 |     LOCK();
 1861 |     piVar1 = (int *)(local_98[0] + -8);
 1862 |     iVar3 = *piVar1;
 1863 |     *piVar1 = *piVar1 + -1;
 1864 |     UNLOCK();
 1865 |     if (iVar3 < 1) {
 1866 |       std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
 1867 |     }
 1868 |   }
 1869 |   local_68[0] = Ogre::Math::fDeg2Rad * DAT_00fa4820;
 1870 |   (**(code **)(*(long *)pVVar6 + 0x248))(pVVar6,local_68);
 1871 |   Ogre::Camera::setPosition(pVVar6);
 1872 |   Ogre::Camera::lookAt(pVVar6);
 1873 |   (**(code **)(*(long *)pVVar6 + 600))(DAT_00fa47fc,pVVar6);
 1874 |   (**(code **)(*(long *)pVVar6 + 0x268))(DAT_00fa4824,pVVar6);
 1875 |   Ogre::Camera::setAutoAspectRatio(SUB81(pVVar6,0));
 1876 |   this_00 = (CCameraControl *)Ogre::NedAllocImpl::allocBytes(0xa0,(char *)0x0,0,(char *)0x0);
 1877 |                     /* try { // try from 0056175e to 00561762 has its CatchHandler @ 00561864 */
 1878 |   CCameraControl::CCameraControl
 1879 |             (this_00,(Camera *)pVVar4,(Camera *)pVVar5,(Camera *)pVVar6,(Camera *)0x0,(Camera *)0x0)
 1880 |   ;
 1881 |   *(CCameraControl **)(this + 0x38) = this_00;
 1882 |   return;
 1883 | }
 1884 | 
 1885 | 
 1886 | 
 1887 | /* address=00561890
 1888 |    symbol=CGame::chooseSceneManager */
 1889 | 
 1890 | /* WARNING: Removing unreachable block (ram,0x00561bec) */
 1891 | /* WARNING: Removing unreachable block (ram,0x00561bde) */
 1892 | /* WARNING: Removing unreachable block (ram,0x00561bc2) */
 1893 | /* WARNING: Removing unreachable block (ram,0x00561b64) */
 1894 | /* WARNING: Removing unreachable block (ram,0x00561bfa) */
 1895 | /* WARNING: Removing unreachable block (ram,0x00561bd0) */
 1896 | /* CGame::chooseSceneManager() */
 1897 | 
 1898 | void __thiscall CGame::chooseSceneManager(CGame *this)
 1899 | 
 1900 | {
 1901 |   int *piVar1;
 1902 |   int iVar2;
 1903 |   undefined8 uVar3;
 1904 |   long *plVar4;
 1905 |   long local_88 [2];
 1906 |   long local_78 [2];
 1907 |   long local_68 [2];
 1908 |   long local_58 [2];
 1909 |   long local_48 [2];
 1910 |   long local_38 [3];
 1911 |   allocator local_1e;
 1912 |   allocator local_1d;
 1913 |   allocator local_1c;
 1914 |   allocator local_1b;
 1915 |   allocator local_1a;
 1916 |   allocator local_19;
 1917 | 
 1918 |   Ogre::MovableObject::msDefaultVisibilityFlags = 1;
 1919 |                     /* try { // try from 005618b7 to 005618bb has its CatchHandler @ 00561ba4 */
 1920 |   std::string::string((string *)local_38,"SMBKInstance",&local_19);
 1921 |                     /* try { // try from 005618c8 to 005618cc has its CatchHandler @ 00561bb2 */
 1922 |   uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 1923 |   *(undefined8 *)(this + 0x48) = uVar3;
 1924 |   if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1925 |     LOCK();
 1926 |     piVar1 = (int *)(local_38[0] + -8);
 1927 |     iVar2 = *piVar1;
 1928 |     *piVar1 = *piVar1 + -1;
 1929 |     UNLOCK();
 1930 |     if (iVar2 < 1) {
 1931 |       std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
 1932 |     }
 1933 |   }
 1934 |                     /* try { // try from 005618fa to 005618fe has its CatchHandler @ 00561b92 */
 1935 |   std::string::string((string *)local_48,"SMInstance",&local_1a);
 1936 |                     /* try { // try from 0056190b to 0056190f has its CatchHandler @ 00561b89 */
 1937 |   plVar4 = (long *)Ogre::Root::createSceneManager
 1938 |                              ((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 1939 |   *(long **)(this + 0x50) = plVar4;
 1940 |   if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1941 |     LOCK();
 1942 |     piVar1 = (int *)(local_48[0] + -8);
 1943 |     iVar2 = *piVar1;
 1944 |     *piVar1 = *piVar1 + -1;
 1945 |     UNLOCK();
 1946 |     if (iVar2 < 1) {
 1947 |       std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
 1948 |     }
 1949 |     plVar4 = *(long **)(this + 0x50);
 1950 |   }
 1951 |   (**(code **)(*plVar4 + 0x7f0))(plVar4,7);
 1952 |                     /* try { // try from 00561949 to 0056194d has its CatchHandler @ 00561b87 */
 1953 |   std::string::string((string *)local_58,"SMUIInstance",&local_1b);
 1954 |                     /* try { // try from 0056195a to 0056195e has its CatchHandler @ 00561b7a */
 1955 |   uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 1956 |   *(undefined8 *)(this + 0x58) = uVar3;
 1957 |   if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1958 |     LOCK();
 1959 |     piVar1 = (int *)(local_58[0] + -8);
 1960 |     iVar2 = *piVar1;
 1961 |     *piVar1 = *piVar1 + -1;
 1962 |     UNLOCK();
 1963 |     if (iVar2 < 1) {
 1964 |       std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
 1965 |     }
 1966 |   }
 1967 |   Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x58));
 1968 |                     /* try { // try from 005619b2 to 005619b6 has its CatchHandler @ 00561bbf */
 1969 |   std::string::string((string *)local_68,"SMRBInstance",&local_1c);
 1970 |                     /* try { // try from 005619c3 to 005619c7 has its CatchHandler @ 00561ba2 */
 1971 |   uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 1972 |   *(undefined8 *)(this + 0x60) = uVar3;
 1973 |   if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1974 |     LOCK();
 1975 |     piVar1 = (int *)(local_68[0] + -8);
 1976 |     iVar2 = *piVar1;
 1977 |     *piVar1 = *piVar1 + -1;
 1978 |     UNLOCK();
 1979 |     if (iVar2 < 1) {
 1980 |       std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
 1981 |     }
 1982 |   }
 1983 |                     /* try { // try from 005619f0 to 005619f4 has its CatchHandler @ 00561b96 */
 1984 |   std::string::string((string *)local_78,"SMRBPInstance",&local_1d);
 1985 |                     /* try { // try from 00561a01 to 00561a05 has its CatchHandler @ 00561b94 */
 1986 |   uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 1987 |   *(undefined8 *)(this + 0x68) = uVar3;
 1988 |   if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 1989 |     LOCK();
 1990 |     piVar1 = (int *)(local_78[0] + -8);
 1991 |     iVar2 = *piVar1;
 1992 |     *piVar1 = *piVar1 + -1;
 1993 |     UNLOCK();
 1994 |     if (iVar2 < 1) {
 1995 |       std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
 1996 |     }
 1997 |   }
 1998 |                     /* try { // try from 00561a2e to 00561a32 has its CatchHandler @ 00561b6f */
 1999 |   std::string::string((string *)local_88,"SMAMInstance",&local_1e);
 2000 |                     /* try { // try from 00561a3f to 00561a43 has its CatchHandler @ 00561ba6 */
 2001 |   uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
 2002 |   *(undefined8 *)(this + 0x70) = uVar3;
 2003 |   if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 2004 |     LOCK();
 2005 |     piVar1 = (int *)(local_88[0] + -8);
 2006 |     iVar2 = *piVar1;
 2007 |     *piVar1 = *piVar1 + -1;
 2008 |     UNLOCK();
 2009 |     if (iVar2 < 1) {
 2010 |       std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
 2011 |     }
 2012 |   }
 2013 |   return;
 2014 | }
 2015 | 
 2016 | 
 2017 | 
 2018 | /* address=00561c10
 2019 |    symbol=CGame::createViewports */
 2020 | 
 2021 | /* WARNING: Removing unreachable block (ram,0x00562180) */
 2022 | /* WARNING: Removing unreachable block (ram,0x0056218e) */
 2023 | /* WARNING: Removing unreachable block (ram,0x005620eb) */
 2024 | /* WARNING: Removing unreachable block (ram,0x00562148) */
 2025 | /* WARNING: Removing unreachable block (ram,0x00562172) */
 2026 | /* WARNING: Removing unreachable block (ram,0x00562156) */
 2027 | /* WARNING: Removing unreachable block (ram,0x00562164) */
 2028 | /* CGame::createViewports() */
 2029 | 
 2030 | void __thiscall CGame::createViewports(CGame *this)
 2031 | 
 2032 | {
 2033 |   int *piVar1;
 2034 |   long *plVar2;
 2035 |   int iVar3;
 2036 |   int iVar4;
 2037 |   ColourValue *pCVar5;
 2038 |   undefined8 uVar6;
 2039 |   float fVar7;
 2040 |   CCameraControl *pCVar8;
 2041 |   long local_a8 [2];
 2042 |   long local_98 [2];
 2043 |   long local_88 [2];
 2044 |   long local_78 [2];
 2045 |   long local_68 [2];
 2046 |   long local_58 [2];
 2047 |   long local_48 [3];
 2048 | 
 2049 |   if ((*(long *)(this + 0x38) != 0) && (plVar2 = *(long **)(this + 0x80), plVar2 != (long *)0x0)) {
 2050 |     pCVar5 = (ColourValue *)
 2051 |              (**(code **)(*plVar2 + 0x48))
 2052 |                        (0,0,DAT_00fa47fc,plVar2,*(undefined8 *)(*(long *)(this + 0x38) + 0x10),1);
 2053 |     *(ColourValue **)(this + 0x78) = pCVar5;
 2054 |     Ogre::Viewport::setBackgroundColour(pCVar5);
 2055 |     Ogre::Viewport::setClearEveryFrame(SUB81(pCVar5,0),0);
 2056 |     pCVar5 = (ColourValue *)
 2057 |              (**(code **)(**(long **)(this + 0x80) + 0x48))
 2058 |                        (0,0,DAT_00fa47fc,*(long **)(this + 0x80),
 2059 |                         *(undefined8 *)(*(long *)(this + 0x38) + 0x18),5);
 2060 |     Ogre::Viewport::setBackgroundColour(pCVar5);
 2061 |     Ogre::Viewport::setClearEveryFrame(SUB81(pCVar5,0),1);
 2062 |     pCVar5 = (ColourValue *)
 2063 |              (**(code **)(**(long **)(this + 0x80) + 0x48))
 2064 |                        (0,0,DAT_00fa47fc,*(long **)(this + 0x80),
 2065 |                         *(undefined8 *)(*(long *)(this + 0x38) + 0x20),0);
 2066 |     Ogre::Viewport::setBackgroundColour(pCVar5);
 2067 |     iVar3 = Ogre::Viewport::getActualHeight();
 2068 |     fVar7 = (float)iVar3;
 2069 |     iVar3 = Ogre::Viewport::getActualWidth();
 2070 |     pCVar8._0_4_ = (CCameraControl *)(float)iVar3;
 2071 |     uVar6 = *(undefined8 *)(this + 0x38);
 2072 |     CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,0);
 2073 |     CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,1);
 2074 |     CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,2);
 2075 |     iVar3 = Ogre::Viewport::getActualHeight();
 2076 |     STRINGS::GetValueAsString((STRINGS *)local_78,iVar3);
 2077 |                     /* try { // try from 00561dfa to 00561e12 has its CatchHandler @ 00562123 */
 2078 |     iVar3 = Ogre::Viewport::getActualWidth();
 2079 |     STRINGS::GetValueAsString((STRINGS *)local_48,(float)iVar3);
 2080 |                     /* try { // try from 00561e26 to 00561e2a has its CatchHandler @ 0056211c */
 2081 |     std::operator+((char *)local_58,(string *)"CreateViewports AspectRatio message - ");
 2082 |                     /* try { // try from 00561e39 to 00561e3d has its CatchHandler @ 005620e4 */
 2083 |     std::string::string((string *)local_68,(string *)local_58);
 2084 |                     /* try { // try from 00561e4b to 00561e4f has its CatchHandler @ 005620b5 */
 2085 |     std::string::append((char *)local_68,0xfa040c);
 2086 |                     /* try { // try from 00561e5e to 00561e62 has its CatchHandler @ 00562141 */
 2087 |     std::operator+((string *)local_88,(string *)local_68);
 2088 |                     /* try { // try from 00561e63 to 00561e79 has its CatchHandler @ 0056212a */
 2089 |     uVar6 = Ogre::LogManager::getSingleton();
 2090 |     Ogre::LogManager::logMessage(uVar6,(string *)local_88,3,0);
 2091 |     if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2092 |     {
 2093 |       LOCK();
 2094 |       piVar1 = (int *)(local_88[0] + -8);
 2095 |       iVar3 = *piVar1;
 2096 |       *piVar1 = *piVar1 + -1;
 2097 |       UNLOCK();
 2098 |       if (iVar3 < 1) {
 2099 |         std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
 2100 |       }
 2101 |     }
 2102 |     if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2103 |     {
 2104 |       LOCK();
 2105 |       piVar1 = (int *)(local_68[0] + -8);
 2106 |       iVar3 = *piVar1;
 2107 |       *piVar1 = *piVar1 + -1;
 2108 |       UNLOCK();
 2109 |       if (iVar3 < 1) {
 2110 |         std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
 2111 |       }
 2112 |     }
 2113 |     if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2114 |     {
 2115 |       LOCK();
 2116 |       piVar1 = (int *)(local_58[0] + -8);
 2117 |       iVar3 = *piVar1;
 2118 |       *piVar1 = *piVar1 + -1;
 2119 |       UNLOCK();
 2120 |       if (iVar3 < 1) {
 2121 |         std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
 2122 |       }
 2123 |     }
 2124 |     if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2125 |     {
 2126 |       LOCK();
 2127 |       piVar1 = (int *)(local_48[0] + -8);
 2128 |       iVar3 = *piVar1;
 2129 |       *piVar1 = *piVar1 + -1;
 2130 |       UNLOCK();
 2131 |       if (iVar3 < 1) {
 2132 |         std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
 2133 |       }
 2134 |     }
 2135 |     if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2136 |     {
 2137 |       LOCK();
 2138 |       piVar1 = (int *)(local_78[0] + -8);
 2139 |       iVar3 = *piVar1;
 2140 |       *piVar1 = *piVar1 + -1;
 2141 |       UNLOCK();
 2142 |       if (iVar3 < 1) {
 2143 |         std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
 2144 |       }
 2145 |     }
 2146 |     iVar3 = Ogre::Viewport::getActualWidth();
 2147 |     iVar4 = Ogre::Viewport::getActualHeight();
 2148 |     STRINGS::GetValueAsString((STRINGS *)local_98,(float)iVar3 / (float)iVar4);
 2149 |                     /* try { // try from 00561f22 to 00561f26 has its CatchHandler @ 00562115 */
 2150 |     std::operator+((char *)local_a8,(string *)"CreateViewports AspectRatio message AR - ");
 2151 |                     /* try { // try from 00561f27 to 00561f3d has its CatchHandler @ 005620f6 */
 2152 |     uVar6 = Ogre::LogManager::getSingleton();
 2153 |     Ogre::LogManager::logMessage(uVar6,local_a8,3,0);
 2154 |     if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2155 |     {
 2156 |       LOCK();
 2157 |       piVar1 = (int *)(local_a8[0] + -8);
 2158 |       iVar3 = *piVar1;
 2159 |       *piVar1 = *piVar1 + -1;
 2160 |       UNLOCK();
 2161 |       if (iVar3 < 1) {
 2162 |         std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
 2163 |       }
 2164 |     }
 2165 |     if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2166 |     {
 2167 |       LOCK();
 2168 |       piVar1 = (int *)(local_98[0] + -8);
 2169 |       iVar3 = *piVar1;
 2170 |       *piVar1 = *piVar1 + -1;
 2171 |       UNLOCK();
 2172 |       if (iVar3 < 1) {
 2173 |         std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
 2174 |       }
 2175 |     }
 2176 |   }
 2177 |   return;
 2178 | }
 2179 | 
 2180 | 
```

