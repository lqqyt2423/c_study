#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

char *_strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) strcpy(p, s);
  return p;
}

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = _strdup(name)) == NULL) {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free((void *)np->defn);
  }

  if ((np->defn = _strdup(defn)) == NULL) {
    return NULL;
  }
  return np;
}

void undef(char *name) {
  struct nlist *np;
  struct nlist *target = NULL;
  struct nlist *before = NULL;

  unsigned hashval = hash(name);
  for (np = hashtab[hashval]; np != NULL; before = np, np = np->next) {
    if (strcmp(name, np->name) == 0) {
      target = np;
      break;
    }
  }

  if (target != NULL) {
    if (before != NULL) {
      before->next = target->next;
    } else {
      hashtab[hashval] = target->next;
    }

    free((void *)target->name);
    free((void *)target->defn);
    free((void *)target);
  }
}

int main() {
  install("name", "lq");
  install("age", "26");
  printf("name: %s\n", lookup("name")->defn);
  printf("age: %s\n", lookup("age")->defn);

  undef("name");

  struct nlist *i;
  if ((i = lookup("name")) != NULL) {
    printf("name: %s\n", i->defn);
  }

  printf("hashtab[0]: %p hashtab[1]: %p\n", hashtab[0], hashtab[1]);
}
