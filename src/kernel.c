void kernel_main(void) {
  *(unsigned short *)0xc03ff000 = 'A' | 15 << 8;
}
