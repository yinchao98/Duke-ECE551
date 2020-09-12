#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  if (str == NULL) {
    return;
  }
  // head pointer and tail pointer
  char* head = str;
  char* tail = str;
  size_t length = 0;
  // look for the tail of string
  while(*tail != '\0') {
    tail++;
    length++;
  }
  tail--;
  // half length of the string
  size_t halfLen;
  if (length % 2 == 0) {
    halfLen = length / 2;
  } else {
    halfLen = (length - 1) / 2;
  }
  // reverse the string
  for (size_t i = 0; i < halfLen; i++) {
    // swap the char in header pointer and tail pointer
    char temp = *tail;
    *tail = *head;
    *head = temp;
    head++;
    tail--;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
