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

struct Pile {
  struct Card *top;
};

char suits[4][10] = { "Hearts", "Diamonds", "Clubs", "Spades" };

int values[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A'
};

void print_card(struct Card *card) {
  const int value = card->value;
  const char *suit = card->suit;
  if (value >= 65 && value <= 81)
    printf("value: %c\tvalue: %s\n", value, suit);
  else
    printf("value: %d\tvalue: %s\n", value, suit);
}

void dump_deck(struct Deck *deck) {
  struct Card *curr = deck->head;
  int total = 0;
  while (curr) {
    print_card(curr);
    total++;
    curr = curr->next;
  }
  printf("total cards: %d\n", total);
}

void discard(struct Pile *pile, struct Deck *deck) {
  struct Card *card = pile->top, *next = pile->top->next;

  pile->top = next;
  card->next = NULL;

  deck->tail->next = card;
  deck->tail = card;

}

void dump_pile(struct Pile *pile) {
  struct Card *curr;
  for (curr = pile->top; curr != NULL; curr = curr->next)
    print_card(curr);
}

void pile_of_cards(struct Pile *pile, struct Deck *deck, int value) {
  struct Card *curr = deck->head, *prev = deck->head, *piled[4];
  int i, count = 0;
  
  while (curr) {
    if (curr->value == value) {
      if (curr == deck->head)
        deck->head = curr->next;

      if (curr == deck->tail)
        deck->tail = prev;

      prev->next = curr->next;
      piled[count++] = curr;
    }

    prev = curr;
    curr = curr->next;
  }

  for (i = count - 1; i >= 0; i--) {
    if (i == count && pile->top != NULL)
      piled[i]->next = NULL;
    else
      piled[i]->next = pile->top;
    pile->top = piled[i];
  }
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

  struct Pile pile;

  pile.top = NULL;

  pile_of_cards(&pile, &deck, 3);
  pile_of_cards(&pile, &deck, 'A');
  pile_of_cards(&pile, &deck, 4);
  pile_of_cards(&pile, &deck, 5);
  pile_of_cards(&pile, &deck, 10);
  pile_of_cards(&pile, &deck, 'J');
  pile_of_cards(&pile, &deck, 2);
  pile_of_cards(&pile, &deck, 'K');

  printf("==== PILE ====\n");
  dump_pile(&pile);
  printf("==============\n\n");
  
  dump_deck(&deck);

  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);
  discard(&pile, &deck);

  printf("==== PILE ====\n");
  dump_pile(&pile);
  printf("==============\n\n");

  dump_deck(&deck);

  return 0;
}
