int strlen(char s[]) {
  int i;

  i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

// 字符串转数字
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

// 统计x中值为1的二进制位数
int bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x >>= 1)
    if (x & 01)
      b++;
  return b;
}

// 数字转字符串
void itoa(int n, char s[]) {
  int i, sign;

  // 记录符号
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}
