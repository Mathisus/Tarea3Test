#ifndef treemap_h
#define treemap_h

// Estructuras de datos

typedef struct TreeNode {
    int key;
    int value;
    struct Pair *pair;
    struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Pair {
    void *key;
    void *value;
} Pair;

typedef struct TreeMap {
    TreeNode *root;
    TreeNode *actual;
    int size;
    int (*lower_than) (void* key1, void* key2);
    int (*compare)(void*, void*);
    void (*destroyKey)(void*);
    void (*destroyValue)(void*);
} TreeMap;

// Funciones de utilidad

int is_equal(TreeMap *tree, void *key1, void *key2);
TreeNode *minimum(TreeNode *x);
TreeNode *createTreeNode(void *key, void *value);

// Funciones principales

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2), int (*compare)(void*, void*), void (*destroyKey)(void*), void (*destroyValue)(void*));
void destroyTreeMap(TreeMap* map);
void eraseTreeMap(TreeMap* map);
void eraseTreeMapNode(TreeNode* node, void (*destroyKey)(void*), void (*destroyValue)(void*));
void insertTreeMap(TreeMap *tree, void *key, void *value);
void RemoveNode(TreeMap *tree, TreeNode *node);
void eraseTreeMap(TreeMap *tree);
void* firstTreeMap(TreeMap *tree);
void* nextTreeMap(TreeMap *tree);

#endif  // treemap.h