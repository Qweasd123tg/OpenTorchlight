extern "C" void raise_value(){throw 3;} extern "C" int probe(); int main(){try{return probe();}catch(...){return 99;}}
