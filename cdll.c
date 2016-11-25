void initCdll(cdll *ll){
    ll->head = ll->tail = NULL;
}
cdll *newCdll(cdll *ll){
    if ((ll = (cdll *)malloc(sizeof(cdll))) == 0)
        Fatal("out of memory\n");
    initCdll(ll);
    return ll;
}
bool EmptyCdll(cdll *ll){
    if(ll->head == NULL && ll->tail == NULL)
        return true;
    else
        return false;
}
void unionCdll(cdll *x, cdll *y)
{
    while (y->head != NULL)
    {
        pushCdll(x, y->head);
        popCdll(y);
    }
    return;
}
void pushCdll(cdll *ll,node *n){
    node *temp;
    if(EmptyCdll(ll)){
        ll->head = ll->tail = n;
        ll->head->prev = ll->tail;
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->tail->next = ll->head;
    }
    else{
        ll->head->prev = n;
        n->next = ll->head;
        n->prev = ll->tail;
        ll->tail->next = n;
        ll->head = n;
    }
}
void popCdll(cdll *ll){
    if(ll->head == ll->tail){
        ll->head = ll->tail = NULL;
        ll->head->prev = NULL;
        ll->head->next = NULL;
        ll->tail->prev = NULL;
        ll->tail->next = NULL;
    }
    else{
        ll->tail->next = ll->head->next;
        ll->head->next->prev = ll->tail;
        ll->head = ll->head->next;
    }
}

node *deleteCdll(cdll *ll){
	if(EmptyCdll(ll))
        Fatal("Delete Empty Cdll\n");
	node *temp = ll->head->data;
	ll->head = ll->head->next;
	if (ll->head == NULL)
		ll->tail = NULL;
	return temp;
}
