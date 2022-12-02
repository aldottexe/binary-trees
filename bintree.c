//im gonna try to make it myself cause he never taught us
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int height; // only used for the avl thing
    int ballance_fac; //also only for avl

    struct node * left;
    struct node * right;
    int val;
    int count;
} node;

node * rotateLeft(node * old_head);
node * rotateRight(node * old_head);
void printTree(node * head, int depth);
void addNode(node ** head_p, int val);
int smartAddNode(node ** head_p, int val);

int main()
{
    printf("////////////////////////////////////////////////////////////////////////////////\nprepare for a mess\n\n");
    node * head = NULL;
    printf("adding 2\n");
    smartAddNode(&head, 2);
    printTree(head, 0);
    printf("adding 6\n");
    smartAddNode(&head, 6);
    printTree(head, 0);
    printf("adding 25\n");
    smartAddNode(&head, 25);
    printTree(head, 0);
    printf("adding 1\n");
    smartAddNode(&head, 1);
    printTree(head, 0);
    printf("adding 5\n");
    smartAddNode(&head, 5);
    printTree(head, 0);
    printf("adding 81\n");
    smartAddNode(&head, 81);
    printTree(head, 0);
    printf("adding 9\n");
    smartAddNode(&head, 9);
    printTree(head, 0);
    printf("adding 12\n");
    smartAddNode(&head, 12);
    printTree(head, 0);
    printf("adding 2\n");
    smartAddNode(&head, 2);
    printTree(head, 0);
    printf("adding 5\n");
    smartAddNode(&head, 5);
    printTree(head, 0);
    printf("adding 14\n");
    smartAddNode(&head, 14);
    printTree(head, 0);
    printf("adding 8\n");
    smartAddNode(&head, 8);
    printTree(head, 0);
    printf("adding 11\n");
    smartAddNode(&head, 11);


    printTree(head, 0);
}

void addNode(node ** head_p, int val)
{
    //if the head doesnt exist, create a new node in its place
    if(!*head_p) 
    {
        *head_p = malloc(sizeof(node)); 

        (*head_p) -> val = val;
        (*head_p) -> count = 1;

        return;
    }    
    //if the value is less, try again to the left
    if((*head_p) -> val < val)
        addNode(&((*head_p) -> left), val);
    //if value is more, try again to the right
    else if((*head_p) -> val > val)
        addNode(&((*head_p) -> right), val);
    //if the value is found, increment count
    else
        (*head_p) -> count += 1;
}

int smartAddNode(node ** head_p, int val)
{
    node * head = *head_p;
    
    //if the head doesnt exist, create a new node in its place
    if(!head) 
    {
        head = malloc(sizeof(node)); 

        head -> val = val;
        head -> count = 1;

        *head_p = head;
        return 1; //returning a 1 will tell outer recursions to reorganize the tree
    }    
    int nodeAdded;
    //if the value is less, try again to the left
    if(head -> val < val)
        nodeAdded = smartAddNode(&(head -> left), val);
    //if value is more, try again to the right
    else if(head -> val > val)
        nodeAdded = smartAddNode(&(head -> right), val);
    //if the value is equal to this node's value, increment count
    else
    {
        head -> count += 1;
        return 0; //if no new node is added, no need to reorganize tree
    }

    //if reorganize is false end the function
    //if(!nodeAdded) return 0;

    //update the hight of property based on the heights of it's children
    int lh, rh = -1;
    if (head -> left)  lh = head -> left -> height;
    if (head -> right) rh = head -> right -> height;

    if(lh >= rh) head -> height = 1 + lh;
    else         head -> height = 1 + rh;

    //update the ballance factor, which records the relationship between 
    //the lowest leaf on either side relative to this node
    head -> ballance_fac = rh - lh;

    //if the ballance factor is off (one side is more than 1 level lower than the other)
    //then rotate the tree accordingly to even it out
    if(head -> ballance_fac == -2)
        if(head -> left -> ballance_fac <= 0)
            //leftleft
            head = rotateRight(head);
        else
        {
            //leftright
            head -> left = rotateLeft(head -> left);
            head = rotateRight(head);
        }
    
    else if(head -> ballance_fac ==2)
        if(head -> right -> ballance_fac >= 0)
            //rightright
            head = rotateLeft(head);
        else
        {
            //rightleft
            head -> right = rotateRight(head -> right);
            head = rotateLeft(head);
        }

    *head_p = head;
    return 1;
}

void printTree(node * head, int depth)
{
    for(int i = 0; i < depth; i++)
        printf("    |");
   
    if(!head)
    {
        printf("~\n");
        return;
    }
    printf("----%i:%ih%ibf%i\n", head -> val, head -> count, head -> height, head -> ballance_fac);
    
    printTree(head -> left, depth + 1);
    printTree(head -> right, depth + 1);
    
    for(int i = 0; i < depth; i++)
    printf("    |");
    printf("\n");
}

node * rotateRight(node * old_head)
{
    printf("rotating right @%dh%d\n",old_head->val,old_head->height);

    node * new_head = old_head -> left;
    old_head -> left = new_head -> right;
    new_head -> right = old_head;

    //no clue if this is right so heads up
    old_head -> height -= 2;
    old_head -> ballance_fac += 2;
    new_head -> ballance_fac += 1;

    return new_head;
}

node * rotateLeft(node * old_head)
{
    printf("rotating left @%dh%d\n",old_head->val,old_head->height);
    node * new_head = old_head -> right;
    old_head -> right = new_head -> left;
    new_head -> left = old_head;

    //no clue if this is right either
    old_head -> height -= 2;
    old_head -> ballance_fac -= 2;
    new_head -> ballance_fac -= 1;

    return new_head;
}