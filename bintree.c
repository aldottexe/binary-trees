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
void smartAddNode(node ** head_p, int val);

int main()
{
    node * head = NULL;
    smartAddNode(&head, 2);
    smartAddNode(&head, 6);
    smartAddNode(&head, 25);
    smartAddNode(&head, 1);
    smartAddNode(&head, 5);
    smartAddNode(&head, 81);
    smartAddNode(&head, 9);
    smartAddNode(&head, 12);
    smartAddNode(&head, 2);
    smartAddNode(&head, 5);


    printTree(head, 0);

    //head = rotateRight(head);
    //printf("\nrotated right\n\n");     
    //printTree(head, 0);


    //head = rotateLeft(head);
    //printf("\nrotated Left\n\n");     
    //printTree(head, 0);

    
    //head = rotateLeft(head);
    //printf("\nrotated Left\n\n");     
    //printTree(head, 0);
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

void smartAddNode(node ** head_p, int val)
{
    node * head = *head_p;
    
    //if the head doesnt exist, create a new node in its place
    if(!head) 
    {
        head = malloc(sizeof(node)); 

        head -> val = val;
        head -> count = 1;

        *head_p = head;
        return;
    }    
    
    //if the value is less, try again to the left
    if(head -> val < val)
        smartAddNode(&(head -> left), val);
    //if value is more, try again to the right
    else if(head -> val > val)
        smartAddNode(&(head -> right), val);
    //if the value is found, increment count
    else
    {
        head -> count += 1;
        return;
    }
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
            rotateRight(head);
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
    return;

}

void printTree(node * head, int depth)
{
    for(int i = 0; i < depth; i++)
        printf("| ");
   
    if(!head)
    {
        printf("<empty>\n");
        return;
    }
    printf("%i: %i\n", head -> val, head -> count);
    
    printTree(head -> left, depth + 1);
    printTree(head -> right, depth + 1);
}

node * rotateRight(node * old_head)
{
    node * new_head = old_head -> left;
    old_head -> left = new_head -> right;
    new_head -> right = old_head;

    return new_head;
}

node * rotateLeft(node * old_head)
{
    node * new_head = old_head -> right;
    old_head -> right = new_head -> left;
    new_head -> left = old_head;

    return new_head;
}