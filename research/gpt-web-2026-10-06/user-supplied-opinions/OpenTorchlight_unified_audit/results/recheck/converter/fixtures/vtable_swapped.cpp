struct COver {
 virtual int f(long);
 virtual int f(int);
};
int COver::f(int) { return 11; }
int COver::f(long) { return 22; }
COver instance;
