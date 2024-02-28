#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

struct Card {
  char *suit;
  int value;
  struct Card *next;
};

struct Deck {
  struct Card *head;
  struct Card *tail;
};

char suits[4][10] = { "Hearts", "Diamonds", "Clubs", "Spades" };

int values[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A'
};

void dump_deck(struct Deck *deck) {
  struct Card *curr = deck->head, *prev = deck->head;
  int total = 1;
  while (curr) {
    if (curr->suit != prev->suit)
      printf("\n\n");
    printf("value: %d\tsuit: %s\n", curr->value, curr->suit);
    if (curr == deck->tail)
      printf("\n");
    total++;
    prev = curr;
    curr = curr->next;
  }
  printf("total cards: %d\n", total);
}


void add_card(struct Deck *deck, int val, char *suit) {
  struct Card *card = (struct Card *) malloc(sizeof(struct Card));
  card->next = NULL;
  card->suit = suit;
  card->value = val;

  if (deck->head == NULL)
    deck->head = card;

  if (deck->tail != NULL)
    deck->tail->next = card;

  deck->tail = card;
}

int main() {
  struct Deck deck;
  
  deck.head = NULL;
  deck.tail = NULL;

  int i, j;

  for (i = 0; i < ARRAY_SIZE(suits); i++)
    for (j = 0; j < ARRAY_SIZE(values); j++)
      add_card(&deck, values[j], suits[i]);

  dump_deck(&deck);

  return 0;
}
