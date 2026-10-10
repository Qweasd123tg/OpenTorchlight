int GetCursorPos(POINT* point)
{
    point->x=MouseX;
    point->y=MouseY;
    return 0;
}
