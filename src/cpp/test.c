#include <stdio.h>

extern int validate_password(const char *password);

int main() {
  printf("Starting\n");

  int ret = validate_password("abc");
  printf("Return: %d\n", ret);

  return 0;
}
