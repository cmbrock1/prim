struct typedef node{
    struct node *next;
    struct node *prev;
    struct node *parent;
    cdll *children;
    void *value;
}node;
