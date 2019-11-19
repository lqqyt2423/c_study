int strlen(char s[]) {
  int i;

  i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

int atoi(char s[]) {
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) n = 10 * n + (s[i] - '0');
  return n;
}

int lower(int c) {
  if (c >= 'A' && c <= 'Z') return c + 'a' - 'A';
  return c;
}

// 从字符串s中删除字符c
void squeeze(char s[], int c) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}
