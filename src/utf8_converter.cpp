#include "utf8_converter.h"

// Конвертор UTF-8 -> CP-1251
/*String utf8rus(const String& source) {
    int i,k;
    String target;
    unsigned char n;
    char m[2] = { '0', '\0' };
  
    k = source.length(); i = 0;
  
    while (i < k) {
      n = source[i]; i++;
  
      if (n >= 0xC0) {
        switch (n) {
          case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) { n = 0xA8; break; }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
            break;
          }
          case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) { n = 0xB8; break; }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
            break;
          }
        }
      }
      m[0] = n; target = target + String(m);
    }
  return target;
}*/

String utf8rus(const String& source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}


//более эффективный вариант по потреблению памяти
/*#define maxString 21
char target[maxString + 1] = "";

char *utf8rus(char *source) {

    int i,j,k;
    unsigned char n;
    char m[2] = { '0', '\0' };

    strcpy(target, ""); k = strlen(source); i = j = 0;

    while (i < k) {
        n = source[i]; i++;

    if (n >= 0xC0) {
        switch (n) {
            case 0xD0: {
                n = source[i]; i++;
                if (n == 0x81) { n = 0xA8; break; }
                if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
                break;
            }
            case 0xD1: {
                n = source[i]; i++;
                if (n == 0x91) { n = 0xB8; break; }
                if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
                break;
            }
        }
    }

    m[0] = n; strcat(target, m);
    j++; if (j >= maxString) break;
  }
  return target;
}*/