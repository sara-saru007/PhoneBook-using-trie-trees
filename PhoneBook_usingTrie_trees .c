#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// welcome to the phonebook record management using trees
/*
Tanish B 
*/

// to create struct for entry
typedef struct pbentry {
	char lastname[16];
	char firstname[11];
	char phone[11];
	char email[26];
} Entry;

//Create tree node structure
struct tree_node {
	Entry data;
	struct tree_node *left;
	struct tree_node *right;
};

//functions
struct tree_node * insert(struct tree_node *p, Entry e);
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e);
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]);
struct tree_node * findmin(struct tree_node *p);
void print_tree(struct tree_node *p);

int main(void)
{
	int option = 0; /*Variable for option selection.*/
	Entry e;  /*Basic phone book entry*/
	struct tree_node *p = NULL; /*Basic tree node*/
	char ln[16]; /*Used for deletions, editing, and searching*/
	char fn[11]; /*Used for deletions, editing, and searching*/

	/*Return to menu after each instruction until the user quits.*/
	while (option != 4) {
		//show option menu
		printf("MENU\n");
		printf("1. Add\n");
		printf("2. Delete\n");
		printf("3. List\n");
		printf("4. Quit\n");
		
		printf("\nPlease select an option: ");
		scanf("%d", &option);
		
		if (option == 1) {
			//take data
			printf("Please enter the last name: ");
			scanf("%s", &e.lastname);
			printf("Please enter the first name: ");
			scanf("%s", &e.firstname);
			printf("Please enter the phone number: ");
			scanf("%s", &e.phone);
			printf("Please enter the e-mail address: ");
			scanf("%s", &e.email);
			//create new node
			p = insert(p, e);
			
			printf("Record added successfully.\n\n");
		}
			
		else if (option == 2) {
			
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			printf("Please enter the first name: ");
			scanf("%s", &fn);
			
			p = delete_node(p, ln, fn);
		}
		
				
		else if (option == 3) {
			print_tree(p);
		}
				
		else if (option == 4) {
			/*End the program.*/
			break;
		}
	
		else {
			/*Print error message.*/
			printf("That option does not exist. Please try again.\n\n");
		}

	}
	return 0;
}


struct tree_node * insert(struct tree_node *p, Entry e) {
	
	if (p == NULL) {
		
		p = create_node(NULL, NULL, e);
	}
	
	else if (strcmp(e.lastname, p->data.lastname) < 0) {
		
		p->left = insert(p->left, e);
	}
	/*If there is a root, and the entry belongs after the root:*/
	else if (strcmp(e.lastname, p->data.lastname) > 0) {
		
		p->right = insert(p->right, e);
	}
	
	else {
		
		if (strcmp(e.firstname, p->data.firstname) < 0) {
			/*Add before root.*/
			p->left = insert(p->left, e);
		}
		
		else if (strcmp(e.firstname, p->data.firstname) > 0) {
			/*Add after root.*/
			p->right = insert(p->right, e);
		}
		
		else {
			/*Do nothing.*/
			return p;
		}
	}
	/*Return revised tree.*/
	return p;
}

//create new node
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e) {
	struct tree_node* newnode;
	newnode = (struct tree_node*)(malloc(sizeof(struct tree_node)));
	newnode->data = e;
	newnode->left = q;
	newnode->right = r;
	return newnode;
}

//delete node from tree
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]) {
	
	if (strcmp(l, p->data.lastname) < 0 || strcmp(f, p->data.firstname) != 0) {
		/*Delete from before root.*/
		p->left = delete_node(p->left, l, f);
	}
	
	else if (strcmp(l, p->data.lastname) > 0 || strcmp(f, p->data.firstname) != 0) {
		/*Delete from after root.*/
		p->right = delete_node(p->right, l, f);
	}
	
	else if (p->left != NULL && p->right != NULL) {
		/*Find which branch moves up in the tree.*/
		p->data = findmin(p->right)->data;
		p->right = delete_node(p->right, l, f);
		/*Confirm node deletion.*/
		printf("Record deleted successfully.\n\n");
	}
	
	else if (p->left != NULL) {
		
		p = p->left;
		
		printf("Record deleted successfully.\n\n");
	}
	/*If entry is located and has a right branch:*/
	else if (p->right != NULL) {
		/*Move right branch up.*/
		p = p->right;
		/*Confirm node deletion.*/
		printf("Record deleted successfully.\n\n");
	}
	/*If entry is not found:*/
	else {
		//error
		printf("Record could not be found.\n\n");
	}
	/*Return revised tree.*/
	return p;
}

/*Finds the leftmost node in the right branch.*/
struct tree_node * findmin(struct tree_node *p) {
	
	if (p->left != NULL) {
		/*Go to the left node.*/
		findmin(p->left);
	}
	
	return p;
}



void print_tree(struct tree_node *p)
{
	
	if (p != NULL) {
		//print node data
		print_tree(p->left);
		printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
		print_tree(p->right);
	}
}