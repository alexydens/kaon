/* Implements io/vga_text_term.h */
#include <io/vga_text_term.h>

/* Global variables */
static u16 *_vga_text_mem = (u16 *)0xc03ff000;
static u16 *_vga_text_cursor = (u16 *)0xc03ff000;
static u8 _vga_color = 15;

/* Helpers */
/* Get character from color */
static inline u16 _get_char(u8 c, u8 color) {
  return c | color << 8;
}
/* Get color from fg and bg */
static inline u8 _get_color(u8 fg, u8 bg) {
  return fg | bg << 4;
}
/* Update the cursor position */
static inline void _update_cursor(void) {
  port_out_8(VGA_TEXT_REG_CTRL, 14);
  port_out_8(VGA_TEXT_REG_DATA, 
      (u8)((_vga_text_cursor - _vga_text_mem) >> 8));
  port_out_8(VGA_TEXT_REG_CTRL, 15);
  port_out_8(VGA_TEXT_REG_DATA, 
      (u8)(_vga_text_cursor - _vga_text_mem));
}
/* Put one character to the screen */
static inline void _putc(char c) {
  if (_vga_text_cursor >= _vga_text_mem + VGA_TEXT_TERM_SIZE) {
    memcpy(
        _vga_text_mem,
        _vga_text_mem + VGA_TEXT_TERM_COLS,
        (VGA_TEXT_TERM_SIZE - VGA_TEXT_TERM_COLS) * 2
    );
    for (
        u16 *i = _vga_text_mem + VGA_TEXT_TERM_SIZE - VGA_TEXT_TERM_COLS;
        i < _vga_text_mem + VGA_TEXT_TERM_SIZE;
        i++
    ) {
      *i = _get_char(' ', _vga_color);
    }
    _vga_text_cursor -= VGA_TEXT_TERM_COLS;
  }
  switch (c) {
    case '\n':
      _vga_text_cursor += VGA_TEXT_TERM_COLS;
      break;
    case '\r':
      _vga_text_cursor -=
        (int)(_vga_text_cursor - _vga_text_mem) % VGA_TEXT_TERM_COLS;
      break;
    case '\t':
      _vga_text_cursor += VGA_TEXT_TAB_WIDTH
        - ((int)(_vga_text_cursor - _vga_text_mem) % VGA_TEXT_TAB_WIDTH);
      break;
    default:
      *_vga_text_cursor++ = _get_char(c, _vga_color);
  }
}

/* Clear vga text buffer with character c */
void vga_text_clear(char c) {
  char char_used = c == 0 ? ' ' : c;
  u16 *vga_text_cursor = _vga_text_cursor;
  for (size_t i = 0; i < VGA_TEXT_TERM_SIZE; i++) {
    *vga_text_cursor++ = _get_char(char_used, _vga_color);
  }
}
/* Set color for vga text functions */
void vga_text_set_color(u8 fg, u8 bg) {
  _vga_color = _get_color(fg, bg);
}
/* Set cursor position for vga text functions */
void vga_text_set_cursor(u8 x, u8 y) {
  /* TODO: Validate with assertions */
  _vga_text_cursor = _vga_text_mem + (y * VGA_TEXT_TERM_COLS) + x;
}
/* Write character to vga text buffer */
void vga_text_putc(char c) {
  _putc(c);
  _update_cursor();
}
/* Write a string (null terminated) to the vga text buffer */
void vga_text_puts(char *str) {
  while (*str) {
    _putc(*str++);
  }
  _update_cursor();
}
