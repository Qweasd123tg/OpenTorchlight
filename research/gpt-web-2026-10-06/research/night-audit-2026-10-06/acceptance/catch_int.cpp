extern "C" void raise_value(); extern "C" int probe(){try {raise_value();} catch(int) {return 7;} return 0;}
