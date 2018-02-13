int main(){


unsigned int test = 12345;
unsigned int ptr = &test;

printf("test: %d, &test: %p\n", test, &test);

ptr = (ptr<<14U)>>14U;

printf("ptr: %x\n", ptr);


}
