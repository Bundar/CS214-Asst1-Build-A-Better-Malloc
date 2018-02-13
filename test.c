int main(){


unsigned short test = 12345;
unsigned short ptr = (unsigned)&test;

printf("test: %u, &test: %p\n", test, &test);

ptr = (ptr<<14)>>14;

printf("ptr: %x\n", ptr);


}
