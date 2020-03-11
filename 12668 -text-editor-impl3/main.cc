#include<iostream>
#include<cstdlib>
#include<string>

enum role{HEAD, REAR};

typedef struct _node{
    char c;
    struct _node *next, *prev;
} node;
using namespace std;
int main(){
    int t, n, i;
    // using implement 2, dummy head and rear.
    node *head, *rear, *cur, *delete_node, *new_node;
    string text;
    cin >> t;

    while(t--){
        cin >> n >> text;
        // init_list(head, rear)
        head = (node*)malloc(sizeof(node));
        rear = (node*)malloc(sizeof(node));
        head->c = HEAD, rear->c = REAR;
        head->prev = rear->next = NULL;
        head->next = rear, rear->prev = head;

        cur = rear;
        for(i=0; i<n; i++){
            if(text[i] == 'L'){
                if(cur->prev != NULL)
                    cur = cur->prev;
            }else if(text[i] == 'R'){
                if(cur->next != NULL)
                    cur = cur->next;
            }else if(text[i] == 'B'){
                // delete_before
                if(cur->prev == head || cur->prev == NULL) break;
                delete_node = cur->prev;
                delete_node->prev->next = cur;
                cur->prev = delete_node->prev;

                delete(delete_node);
            }else{
                // insert_before
                if(cur->prev == NULL) break;
                new_node = (node*)malloc(sizeof(node));
                new_node->c = text[i];
                new_node->next = cur;
                new_node->prev = cur->prev;

                cur->prev->next = new_node;
                cur->prev = new_node;
            }
        }
        // traversal
        cur = head->next;
        while(cur != rear){
            cout << cur->c;
            cur = cur->next;
        }
        cout << "\n";
        // // back traversal
        // cur = rear->prev;
        // while(cur != head){
        //     printf("%c", cur->c);
        //     cur = cur->prev;
        // }
        // printf("\n");
        // free list
        cur = rear;
        while(cur->prev != head){
            delete_node = cur->prev;
            
            delete_node->prev->next = cur;
            cur->prev = delete_node->prev;

            delete(delete_node);
        }
        delete(head);
        delete(rear);
    }


    return 0;
}

/*
2
15
aaaaaaLLLbbbBRc
16
aLRLRLRLRLRLRLRz

3
15
aaaLLLbbbRRRccc
15
abcdefghijklmno
16
aLRLRLRLRLRLRLRz

*/