typedef void* ordDLL;
typedef void* item;

/*
 * Cria o cabeçalho da lista e retorna ela 
 * devidamente inicializada
 * 
 * args: void
 * 
 * return ordDLL;
*/
ordDLL dListCreate();

/*
 * Desaloca toda memoria ocupada pela lista l
 * 
 * args: ordDLL l : lista a ser destruida
 * 
 * return void
*/
void dListDestroy(ordDLL l);

/*
 * Encontra o elemento e, na lista l
 * 
 * Procura o elemento e, percorrendo toda a lista
 * e realizando a comparação dos elementos.
 * Se ela não encontrar o elemento, retorna NULL.
 * 
 * args: ordDLL l : lista  a ser realizada a busca
 *       void *e  : elemento procurado
 *       int (*cmp) (c v *a, c v *b) : função comparadora dos elementos
 * 
 * return ordDLL
 * 
*/

item listFindE(ordDLL l, void *e, int (*cmp) (const void *a, const void *b));

/*
 * Retorna o i-ésimo elemento da lista
 * 
 * args: ordDLL l: lista
 *       int i: posição do elemento a ser retornado
 * 
 * return: ordDLL: elemento i
*/

ordDLL dListGetI(ordDLL l, int p);

/* Insere um elemento de maneira ordenada em uma lista
 * duplamente encadeada, para tal ele usa o algoritmo 
 * de ordenação por insereção, aplicado a listas dupla-
 * mente encadeada.
 * 
 * args: ordDLL l : cabeçalho da lista
 *       *elem : elemento de um tipo qualquer
 *       int (*cmp) (c v *a, c v *b) : função comparadora dos elementos
 * 
 * return void
*/
void listInsert(ordDLL l, void *elem, int (*cmp) (const void *a, const void *b));

/*
 * Retorna o tamanho de uma lista
 * 
 * args: ordDLL l : cabeçalho da lista
 * 
 * return int
*/
int length(ordDLL l);

/*
 * Retorna o elemento e, pertencente a lista l para ser removido
 * adequadamente pela aplicação.
 * 
 * args: ordDLL : cabeçalho da lista
 *       *elem  : elemento a ser removido
 *       int (*cmp) (c v *a, c v *b) : função comparadora dos elementos
 * 
 * return item
*/
item listRemove(ordDLL l, void *elem, int (*cmp) (const void *a, const void*b));