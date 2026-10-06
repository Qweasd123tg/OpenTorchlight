struct COver {
 virtual int f(int);
 virtual int f(long);
};
int COver::f(int) { return 11; }
int COver::f(long) { return 22; }
COver instance;
