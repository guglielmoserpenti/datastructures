#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    int data;
};

struct list_node *list_get_tail(struct list_node **head) 
{
    if (!head || !*head) return NULL; // Gestisce i casi di lista vuota o puntatori NULL
    
    struct list_node *current = *head;
    while (current->next) 
    {
        current = current->next;
    }
    return current; // Ritorna l'ultimo nodo
}

struct list_node *list_append (struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail (head);

    if (!tail)
    {
        * head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct list_node *create_node(int data)
{
    struct list_node *new_node = malloc(sizeof(struct list_node));
    
    if(new_node)
    {
        new_node->prev = NULL;
        new_node->next = NULL;
        new_node->data = data;

    }

    return new_node;
}

void list_remove(struct list_node **head, int data) 
{
    if (!head || !*head) 
    {
        return; // Lista non valida
    }

    struct list_node *current_node = *head;

    while (current_node) 
    {
        if (current_node->data == data) 
        {
            if (current_node->prev) 
            {
                current_node->prev->next = current_node->next;
            } else 
            {
                *head = current_node->next;
            }

            if (current_node->next) 
            {
                current_node->next->prev = current_node->prev;
            }

            free(current_node);
            return; // Uscita dopo la rimozione del nodo
        }

        current_node = current_node->next; // Avanza al nodo successivo
    }
}

void list_insert_after(struct list_node **head, int data_to_insert, int data_target) {
    if (!head || !*head) 
    {
        return; // Lista non valida
    }

    struct list_node *current_node = *head;

    while (current_node) 
    {
        if (current_node->data == data_target) 
        {
            struct list_node *new_node = create_node(data_to_insert);

            new_node->next = current_node->next; // Il nuovo nodo punta al successivo del nodo corrente
            new_node->prev = current_node;       // Il nuovo nodo punta al nodo corrente come precedente

            if (current_node->next) 
            {
                current_node->next->prev = new_node; // Aggiorna il precedente del successivo nodo corrente
            }

            current_node->next = new_node; // Il nodo corrente punta al nuovo nodo come il suo successivo

            return; // Uscita dopo l'inserimento
        }

        current_node = current_node->next; // Avanza al nodo successivo
    }
}

void list_insert_before(struct list_node **head, int data_to_insert, int data_target) 
{
    if (!head || !*head) 
    {
        return; // Lista non valida
    }

    struct list_node *current_node = *head;

    while (current_node) 
    {
        if (current_node->data == data_target) {
            struct list_node *new_node = create_node(data_to_insert);

            new_node->prev = current_node->prev;
            new_node->next = current_node;

            if (current_node->prev) 
            {
                current_node->prev->next = new_node; // Aggiorna il precedente del successivo nodo corrente
            }

            current_node->prev = new_node; // Il nodo corrente punta al nuovo nodo come il suo successivo

            return; // Uscita dopo l'inserimento
        }

        current_node = current_node->next; // Avanza al nodo successivo
    }
}

void list_shuffle(struct list_node **head) 
{
    if (!head || !*head || !(*head)->next) 
    {
        return; // Lista non valida o troppo corta per lo shuffle
    }

    // Contare il numero di nodi
    int count = 0;
    struct list_node *current = *head;
    while (current) 
    {
        count++;
        current = current->next;
    }

    // Creare un array di puntatori ai nodi
    struct list_node **array = malloc(count * sizeof(struct list_node *));
    if (!array) 
    {
        return; // Fallimento dell'allocazione della memoria
    }

    // Riempire l'array con i puntatori ai nodi
    current = *head;
    for (int i = 0; i < count; i++) 
    {
        array[i] = current;
        current = current->next;
    }

    // Mescolare l'array
    srand(time(NULL)); // Inizializzazione del generatore di numeri casuali
    for (int i = count - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);

        // Scambiare array[i] e array[j]
        struct list_node *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Ricostruire la lista dai nodi nell'array mescolato
    for (int i = 0; i < count - 1; i++) 
    {
        array[i]->next = array[i + 1];
        array[i + 1]->prev = array[i];
    }
    array[0]->prev = NULL;
    array[count - 1]->next = NULL;

    // Aggiornare la testa della lista
    *head = array[0];

    free(array); // Liberare la memoria allocata
}



void print_list(struct list_node *head)
{
    struct list_node *current_node = head;
    while((current_node))
    {
        printf("%d \n", current_node->data);

        
        current_node = current_node -> next;
    }
    
}


int main()
{
    struct list_node *my_doubly_linked_list = NULL;
    list_append(&my_doubly_linked_list, create_node(1));
    list_append(&my_doubly_linked_list, create_node(2));
    list_append(&my_doubly_linked_list, create_node(3));
    list_append(&my_doubly_linked_list, create_node(4));

    printf("Lista inziale : \n");
    print_list(my_doubly_linked_list);

     int data_to_remove = 3;
     list_remove(&my_doubly_linked_list, data_to_remove);

     printf("Lista con rimozione di %d \n", data_to_remove);
     print_list(my_doubly_linked_list);

     int data_to_insert_after = 10;
     list_insert_after(&my_doubly_linked_list, data_to_insert_after, 2);

     printf("Lista con inserimento di %d \n", data_to_insert_after);
     print_list(my_doubly_linked_list);

     int data_to_insert_before = 10;
     list_insert_before(&my_doubly_linked_list, data_to_insert_before, 2);

     printf("Lista con inserimento di %d \n", data_to_insert_before);
     print_list(my_doubly_linked_list);

    printf("Lista prima dello shuffle: \n");
    print_list(my_doubly_linked_list);

    list_shuffle(&my_doubly_linked_list);

    printf("Lista dopo lo shuffle: \n");
    print_list(my_doubly_linked_list);


    return 0;
}