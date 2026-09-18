# 10-original-ui-input-and-scale

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `research/decompiled-core/game_ui.c:1286–1569`

SHA256 полного файла: `f415f44a95978d36423f19824326b89f99d9870acd982f4bad5153364068c05f`

```text
 1286 | /* address=00a83ed0
 1287 |    symbol=CGameUI::convertToScreenScale */
 1288 | 
 1289 | /* CGameUI::convertToScreenScale(CEGUI::Window*, bool) */
 1290 | 
 1291 | void __thiscall CGameUI::convertToScreenScale(CGameUI *this,Window *param_1,bool param_2)
 1292 | 
 1293 | {
 1294 |   long lVar1;
 1295 |   undefined8 *puVar2;
 1296 |   int iVar3;
 1297 |   long lVar4;
 1298 |   int iVar5;
 1299 |   float local_54;
 1300 |   float local_4c;
 1301 |   float fStack_44;
 1302 |   float fStack_3c;
 1303 | 
 1304 |   lVar1 = *(long *)(param_1 + 0x78);
 1305 |   iVar5 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar1) >> 3);
 1306 |   if (0 < iVar5) {
 1307 |     lVar4 = 0;
 1308 |     iVar3 = 0;
 1309 |     while( true ) {
 1310 |       puVar2 = (undefined8 *)(lVar1 + lVar4);
 1311 |       iVar3 = iVar3 + 1;
 1312 |       lVar4 = lVar4 + 8;
 1313 |       convertToScreenScale(this,(Window *)*puVar2,param_2);
 1314 |       if (iVar5 <= iVar3) break;
 1315 |       lVar1 = *(long *)(param_1 + 0x78);
 1316 |     }
 1317 |   }
 1318 |   puVar2 = (undefined8 *)CEGUI::Window::getPosition();
 1319 |   fStack_44 = (float)((ulong)*puVar2 >> 0x20);
 1320 |   fStack_3c = (float)((ulong)puVar2[1] >> 0x20);
 1321 |   if (param_2) {
 1322 |                     /* try { // try from 00a83f5c to 00a83f97 has its CatchHandler @ 00a84034 */
 1323 |     scaledX(this,fStack_44);
 1324 |     scaledX(this,fStack_3c);
 1325 |   }
 1326 |   else {
 1327 |                     /* try { // try from 00a83fe9 to 00a84001 has its CatchHandler @ 00a84034 */
 1328 |     scaledY(this,fStack_44);
 1329 |     scaledY(this,fStack_3c);
 1330 |   }
 1331 |   CEGUI::Window::setPosition((UVector2 *)param_1);
 1332 |   CEGUI::Window::getSize();
 1333 |   if (param_2) {
 1334 |                     /* try { // try from 00a83fa6 to 00a83fcf has its CatchHandler @ 00a8403c */
 1335 |     scaledX(this,local_54);
 1336 |     scaledX(this,local_4c);
 1337 |   }
 1338 |   else {
 1339 |                     /* try { // try from 00a84019 to 00a84031 has its CatchHandler @ 00a8403c */
 1340 |     scaledY(this,local_54);
 1341 |     scaledY(this,local_4c);
 1342 |   }
 1343 |   CEGUI::Window::setSize((UVector2 *)param_1);
 1344 |   return;
 1345 | }
 1346 | 
 1347 | /* address=00a84050
 1348 |    symbol=CGameUI::notifyOfDeletion */
 1349 | 
 1350 | /* CGameUI::notifyOfDeletion(CItem*) */
 1351 | 
 1352 | void __thiscall CGameUI::notifyOfDeletion(CGameUI *this,CItem *param_1)
 1353 | 
 1354 | {
 1355 |   if ((param_1 == *(CItem **)(this + 0x68)) && (param_1 != (CItem *)0x0)) {
 1356 |     CRunicCore::removeSafePointer
 1357 |               ((CRunicCore *)param_1,(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
 1358 |     *(undefined8 *)(this + 0x68) = 0;
 1359 |   }
 1360 |   if (*(long *)(*(long *)(this + 0x4d8) + 0x1020) != 0) {
 1361 |     *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
 1362 |   }
 1363 |   if (*(long *)(*(long *)(this + 0x4f0) + 0x3438) != 0) {
 1364 |     *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
 1365 |   }
 1366 |   if (*(long *)(*(long *)(this + 0x4f8) + 0xf0) != 0) {
 1367 |     *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
 1368 |   }
 1369 |   if (*(long *)(*(long *)(this + 0x500) + 400) != 0) {
 1370 |     *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
 1371 |   }
 1372 |   if (*(long *)(*(long *)(this + 0x508) + 0x3408) != 0) {
 1373 |     *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
 1374 |   }
 1375 |   if (*(long *)(*(long *)(this + 0x4e8) + 0x1370) != 0) {
 1376 |     *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
 1377 |   }
 1378 |   return;
 1379 | }
 1380 | 
 1381 | /* address=00a84140
 1382 |    symbol=CGameUI::getConsoleIsOpen */
 1383 | 
 1384 | /* CGameUI::getConsoleIsOpen() */
 1385 | 
 1386 | undefined8 __thiscall CGameUI::getConsoleIsOpen(CGameUI *this)
 1387 | 
 1388 | {
 1389 |   undefined8 uVar1;
 1390 | 
 1391 |   if (*(CConsole **)(this + 0x1690) != (CConsole *)0x0) {
 1392 |     uVar1 = CConsole::getVisible(*(CConsole **)(this + 0x1690));
 1393 |     return uVar1;
 1394 |   }
 1395 |   return 0;
 1396 | }
 1397 | 
 1398 | /* address=00a84160
 1399 |    symbol=CGameUI::processMenuInput */
 1400 | 
 1401 | /* CGameUI::processMenuInput(void*, float, bool) */
 1402 | 
 1403 | undefined8 __thiscall
 1404 | CGameUI::processMenuInput(CGameUI *this,void *param_1,float param_2,bool param_3)
 1405 | 
 1406 | {
 1407 |   long lVar1;
 1408 |   long lVar2;
 1409 |   undefined8 uVar3;
 1410 | 
 1411 |   CMouseManager::update(this + 0x12a8);
 1412 |   lVar1 = *(long *)(this + 0x12d8);
 1413 |   lVar2 = *(long *)(this + 0x12d0);
 1414 |   CEGUI::System::getSingleton();
 1415 |   CEGUI::System::injectMousePosition((float)lVar2,(float)lVar1);
 1416 |   CEGUI::System::getSingleton();
 1417 |   CEGUI::System::injectTimePulse(param_2);
 1418 |   if (*(CMenuManager **)(this + 0x588) != (CMenuManager *)0x0) {
 1419 |     uVar3 = CMenuManager::processInput(*(CMenuManager **)(this + 0x588),param_1,param_2,param_3);
 1420 |     return uVar3;
 1421 |   }
 1422 |   return 1;
 1423 | }
 1424 | 
 1425 | /* address=00a84230
 1426 |    symbol=CGameUI::captureProcessInput */
 1427 | 
 1428 | /* CGameUI::captureProcessInput() */
 1429 | 
 1430 | void __thiscall CGameUI::captureProcessInput(CGameUI *this)
 1431 | 
 1432 | {
 1433 |   CMouseManager::capture((CMouseManager *)(this + 0x12a8));
 1434 |   CKeyManager::capture((CKeyManager *)(this + 0x590));
 1435 |   return;
 1436 | }
 1437 | 
 1438 | /* address=00a84250
 1439 |    symbol=CGameUI::setRightButtonPressed */
 1440 | 
 1441 | /* CGameUI::setRightButtonPressed() */
 1442 | 
 1443 | void __thiscall CGameUI::setRightButtonPressed(CGameUI *this)
 1444 | 
 1445 | {
 1446 |   CMouseManager::mouseEvent((CMouseManager *)(this + 0x12a8),0x204,0);
 1447 |   CMouseManager::capture((CMouseManager *)(this + 0x12a8));
 1448 |   return;
 1449 | }
 1450 | 
 1451 | /* address=00a84270
 1452 |    symbol=CGameUI::flushInput */
 1453 | 
 1454 | /* CGameUI::flushInput() */
 1455 | 
 1456 | void __thiscall CGameUI::flushInput(CGameUI *this)
 1457 | 
 1458 | {
 1459 |   this[0x12fb] = (CGameUI)0x0;
 1460 |   *(undefined4 *)(this + 0x1674) = 0xffffffff;
 1461 |   *(undefined4 *)(this + 0x1678) = 0xffffffff;
 1462 |   *(undefined4 *)(this + 0x167c) = 0xffffffff;
 1463 |   CKeyManager::flushAll((CKeyManager *)(this + 0x590));
 1464 |   CMouseManager::flushAll((CMouseManager *)(this + 0x12a8));
 1465 |   return;
 1466 | }
 1467 | 
 1468 | /* address=00a842c0
 1469 |    symbol=CGameUI::mouseEvent */
 1470 | 
 1471 | /* CGameUI::mouseEvent(unsigned int, unsigned int) */
 1472 | 
 1473 | void __thiscall CGameUI::mouseEvent(CGameUI *this,uint param_1,uint param_2)
 1474 | 
 1475 | {
 1476 |   undefined8 uVar1;
 1477 | 
 1478 |   if (param_1 == 0x201) {
 1479 |     uVar1 = CEGUI::System::getSingleton();
 1480 |     CEGUI::System::injectMouseButtonDown(uVar1,0);
 1481 |   }
 1482 |   else if (param_1 == 0x202) {
 1483 |     uVar1 = CEGUI::System::getSingleton();
 1484 |     CEGUI::System::injectMouseButtonUp(uVar1,0);
 1485 |   }
 1486 |   else if (param_1 == 0x204) {
 1487 |     uVar1 = CEGUI::System::getSingleton();
 1488 |     CEGUI::System::injectMouseButtonDown(uVar1,1);
 1489 |   }
 1490 |   else if (param_1 == 0x205) {
 1491 |     uVar1 = CEGUI::System::getSingleton();
 1492 |     CEGUI::System::injectMouseButtonUp(uVar1,1);
 1493 |   }
 1494 |   CMouseManager::mouseEvent((CMouseManager *)(this + 0x12a8),param_1,param_2);
 1495 |   return;
 1496 | }
 1497 | 
 1498 | /* address=00a843a0
 1499 |    symbol=CGameUI::keyEvent */
 1500 | 
 1501 | /* CGameUI::keyEvent(unsigned int, unsigned int, long) */
 1502 | 
 1503 | void CGameUI::keyEvent(uint param_1,uint param_2,long param_3)
 1504 | 
 1505 | {
 1506 |   long lVar1;
 1507 |   short sVar2;
 1508 |   uint uVar3;
 1509 |   undefined4 in_register_0000003c;
 1510 | 
 1511 |   uVar3 = (uint)param_3;
 1512 |   CKeyManager::keyEvent
 1513 |             ((CKeyManager *)(CONCAT44(in_register_0000003c,param_1) + 0x590),param_2,uVar3);
 1514 |   lVar1 = *(long *)(CONCAT44(in_register_0000003c,param_1) + 0x1690);
 1515 |   if (lVar1 != 0) {
 1516 |     CConsole::keyEvent((uint)lVar1,param_2,param_3 & 0xffffffff);
 1517 |   }
 1518 |   switch(param_2) {
 1519 |   case 0x100:
 1520 |   case 0x104:
 1521 |     LinuxMapVirtual2Scancode(uVar3);
 1522 |     uVar3 = CEGUI::System::getSingleton();
 1523 |     CEGUI::System::injectKeyDown(uVar3);
 1524 |     return;
 1525 |   case 0x101:
 1526 |   case 0x105:
 1527 |     LinuxMapVirtual2Scancode(uVar3);
 1528 |     uVar3 = CEGUI::System::getSingleton();
 1529 |     CEGUI::System::injectKeyUp(uVar3);
 1530 |     return;
 1531 |   case 0x102:
 1532 |     sVar2 = GetAsyncKeyState(0x10);
 1533 |     if ((-1 < sVar2) || (uVar3 != 0x7e)) {
 1534 |       uVar3 = CEGUI::System::getSingleton();
 1535 |       CEGUI::System::injectChar(uVar3);
 1536 |       return;
 1537 |     }
 1538 |   }
 1539 |   return;
 1540 | }
 1541 | 
 1542 | /* address=00a844d0
 1543 |    symbol=CGameUI::updateMenuUI */
 1544 | 
 1545 | /* CGameUI::updateMenuUI(float, CGameClient*, Ogre::RenderWindow*) */
 1546 | 
 1547 | void CGameUI::updateMenuUI(float param_1,CGameClient *param_2,RenderWindow *param_3)
 1548 | 
 1549 | {
 1550 |   CMouseManager *pCVar1;
 1551 |   long *plVar2;
 1552 |   UVector2 *pUVar3;
 1553 |   char cVar4;
 1554 | 
 1555 |   plVar2 = *(long **)(param_2 + 0x518);
 1556 |   if (((char)plVar2[6] == '\0') && (*(char *)((long)plVar2 + 0x31) != '\0')) {
 1557 |     pCVar1 = (CMouseManager *)(param_2 + 0x12a8);
 1558 |     cVar4 = CMouseManager::buttonPressed(pCVar1,1);
 1559 |     if ((((cVar4 == '\0') && (cVar4 = CMouseManager::buttonPressed(pCVar1,0), cVar4 == '\0')) &&
 1560 |         (cVar4 = CMouseManager::buttonHeld(pCVar1,1), cVar4 == '\0')) &&
 1561 |        (cVar4 = CMouseManager::buttonHeld(pCVar1,0), cVar4 == '\0')) {
 1562 |       pUVar3 = *(UVector2 **)(*(long *)(param_2 + 0x430) + 0x238);
 1563 |       cVar4 = CEGUI::Window::isVisible(SUB81(pUVar3,0));
 1564 |       if (cVar4 != '\0') {
 1565 |         getWindowWidth((CGameUI *)param_2);
 1566 |         getWindowHeight((CGameUI *)param_2);
 1567 |         CEGUI::Window::getWidth();
 1568 |         CEGUI::Window::getHeight();
 1569 |                     /* try { // try from 00a8471f to 00a84723 has its CatchHandler @ 00a84729 */
```

