extern "C" void raise_value(); extern "C" int probe(){try {raise_value();} catch(double) {return 7;} return 0;}
