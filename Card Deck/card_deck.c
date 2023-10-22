#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure for a card
typedef struct Card {
    char* name;
    struct Card* next;
} Card;

// Define the structure for a deck
typedef struct Deck {
    char* name;
    Card* cards;
    struct Deck* next;
} Deck;

// Create a new card with the given name
Card* createCard(char* name) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->name = strdup(name);
    newCard->next = NULL;
    return newCard;
}

// Create a new deck with the given name
Deck* createDeck(char* name) {
    Deck* newDeck = (Deck*)malloc(sizeof(Deck));
    newDeck->name = strdup(name);
    newDeck->cards = NULL;
    newDeck->next = NULL;
    return newDeck;
}

// Add a new card to the given deck
void addCard(Deck* deck, char* cardName) {
    Card* newCard = createCard(cardName);
    if (deck->cards == NULL) {
        deck->cards = newCard;
    } else {
        Card* current = deck->cards;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCard;
    }
}

// Remove a card with the given name from the deck
void removeCard(Deck* deck, char* cardName) {
    Card* current = deck->cards;
    Card* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, cardName) == 0) {
            if (prev == NULL) {
                deck->cards = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Shuffle the cards in the deck
void shuffleDeck(Deck* deck) {
    int count = 0;
    Card* current = deck->cards;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Card** cardsArray = (Card**)malloc(count * sizeof(Card*));
    current = deck->cards;
    int index = 0;
    while (current != NULL) {
        cardsArray[index++] = current;
        current = current->next;
    }

    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = cardsArray[i];
        cardsArray[i] = cardsArray[j];
        cardsArray[j] = temp;
    }

    deck->cards = cardsArray[0];
    current = deck->cards;
    for (int i = 1; i < count; i++) {
        current->next = cardsArray[i];
        current = current->next;
    }
    current->next = NULL;

    free(cardsArray);
}

// Sort the cards in the deck in alphabetical order
void sortDeck(Deck* deck) {
    Card* current = deck->cards;
    Card* index = NULL;
    char* temp;

    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->name, index->name) > 0) {
                temp = current->name;
                current->name = index->name;
                index->name = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

// Driver code for testing the card deck manipulator
int main() {
    Deck* deck = createDeck("SampleDeck");

    // Adding cards
    addCard(deck, "Ace of Spades");
    addCard(deck, "King of Hearts");
    addCard(deck, "Queen of Diamonds");
    addCard(deck, "Jack of Clubs");

    // Removing a card
    removeCard(deck, "King of Hearts");

    // Shuffling the deck
    shuffleDeck(deck);

    // Sorting the deck
    sortDeck(deck);

    // Printing the deck
    printf("Deck: %s\n", deck->name);
    Card* current = deck->cards;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }

    return 0;
}