#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

typedef struct node* Node;
typedef struct node* Tree;

Tree Read(); // Function to read a tree
Node Find(int X, Tree T); // Function to find a node with a specific Id in the tree
Node FindMin(Tree T); // Function to find the node with the minimum value in the tree
Node Insert(int Id,int IdClass ,char Name[],char Address[],char DateEnrollment[], Tree T); // Function to insert a new node with the given values into the tree
Node Delete(int Id,Tree T);// Function to delete a node with a specific Id from the tree
void PrintFile(Tree tree);// Function to print the contents of the tree to a file

Node InsertByName(int Id,int IdClass ,char Name[],char Address[],char DateEnrollment[], Tree T);// Function to insert a new node into the tree based on the name field
Tree SortByName(Tree dest,Tree sor);// Function to sort the tree based on the name field and store the sorted tree in a new destination tree
void Print(Tree tree);// Function to print the contents of the tree
void SearchCity (char Address[],Tree tree);// Function to search for nodes based on the city (address) field
void SearchClass(int IdClass,Tree tree);// Function to search for nodes based on the class field


struct node {
    int Id;
    int IdClass;
    char Name[SIZE];
    char Address[SIZE];
    char DateEnrollment[SIZE];
    Node Right;
    Node Left;
};

int main() {
    Tree Students =Read();  // Read the tree of students
    int op=0;
    while (op!=8){
        printf("plz choose operation\n");
        printf("1- Insert new student\n");
        printf("2- Update information for student\n");
        printf("3- Print All Student\n");
        printf("4- Search City\n");
        printf("5- Search Class \n");
        printf("6- Delete Student\n");
        printf("7- Save Students in file\n");
        printf("8- Exit\n");
        scanf("%d",&op);

        if (op==1){   // Insert a new student
            int Id,IdClass ;
            char Name[SIZE], Address[SIZE],DateEnrollment[SIZE];
            printf("Please enter Id, IdClass, Name, Address, Date Enrollment:\n");
            scanf("%d%d%s%s%s",&Id,&IdClass,Name,Address,DateEnrollment);

            while (Find(Id,Students)!=NULL){ // Check if a student with the same ID already exists
                printf("There is student has this Id please enter another Id:\n");
                scanf("%d",&Id);
            }

            Students = Insert(Id,IdClass,Name,Address,DateEnrollment,Students); // Insert the new student into the tree
        }
        else if (op==2){  // Update student information
            int Id,IdClass ;
            char Name[SIZE], Address[SIZE],DateEnrollment[SIZE];
            printf("Please enter the id of student who you want to update her information\n");
            scanf("%d",&Id);
            Node node = Find(Id,Students);

            while (node == NULL){  // Check if the student exists in the tree
                printf("This student doesn't exist, please enter another Id:\n");
                scanf("%d",&Id);
                node = Find(Id,Students);
            }

            int flag=0 ;
            while(flag!=6){
                printf("plz choose data want update\n");
                printf("1- ID\n");
                printf("2- ID Class\n");
                printf("3- Name\n");
                printf("4- Address\n");
                printf("5- Date Enrollment\n");
                printf("6- Exit \n");
                scanf("%d",&flag);

                if (flag==1){ // Update the ID of the student
                    printf("please enter new ID\n");
                    scanf("%d",&Id);

                    while (Find(Id,Students)!=NULL){ // Check if another student with the same ID already exists
                        printf("There is student has this Id please enter another Id:\n");
                        scanf("%d",&Id);
                    }
                    // Store the current values of the other attributes
                    IdClass=node->IdClass;
                    strcpy(Name,node->Name);
                    strcpy(Address,node->Address);
                    strcpy(DateEnrollment,node->DateEnrollment);
                    // Delete the current student and insert the updated student
                    Students = Delete(node->Id,Students);
                    Students = Insert(Id,IdClass,Name,Address,DateEnrollment,Students);
                }
                else if (flag==2){ // Update the ID Class of the student
                    printf("please enter new Id Class\n");
                    scanf("%d",&IdClass);
                    node->IdClass=IdClass;
                }
                else if (flag==3){  // Update the Name of the student
                    printf("please enter new Name\n");
                    scanf("%s",Name);
                    strcpy(node->Name,Name);
                }
                else if (flag==4){ // Update the Address of the student
                    printf("please enter new Address\n");
                    scanf("%s",Address);
                    strcpy(node->Address,Address);
                }
                else if (flag==5){ // Update the Date Enrollment of the student1
                    printf("please enter new Date Enrollment\n");
                    scanf("%s",DateEnrollment);
                    strcpy(node->DateEnrollment,DateEnrollment);
                }
            }
            printf("Done\n");
        }
        else if (op==3){   // Print all students
            Tree ByNames = NULL;
            if (Students!=NULL)
                ByNames=SortByName(ByNames,Students);
            else
                printf("There is not has students\n");
            Print(ByNames);
        }
        else if (op==4){ // Search for students by city
            char City[SIZE];
            printf("Enter the name of city\n");\
            scanf("%s",City);

            Tree ByNames = NULL;
            if (Students!=NULL)
                ByNames=SortByName(ByNames,Students);
            else
                printf("There is not has students\n");
            SearchCity(City,ByNames);
        }
        else if (op==5){  // Search for students by class
            int id;
            printf("Enter the Id class\n");
            scanf("%d",&id);

            Tree ByNames = NULL;
            if (Students!=NULL)
                ByNames=SortByName(ByNames,Students);
            else
                printf("There is not has students\n");
            SearchClass(id,ByNames);
        }
        else if (op==6){  // Delete a student
            int id;
            printf("Please enter id for student you want delete:\n");
            scanf("%d",&id);

            while (Find(id,Students)==NULL){
                printf("This student doesn't exist, please enter another Id:\n");
                scanf("%d",&id);
            }

            Students = Delete(id,Students);
        }
        else if (op==7){  // Save students to a file
            FILE* file = fopen("students.txt","w");
            fclose(file);
            PrintFile(Students);
        }
    }

    return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function to read the data from a file and construct a tree
Tree Read (){
    /*
     *      The format for file as:
     *      Id,IdClass,Name,Address,DateEnrollment
     *
     *      Each student in line
     */
    Tree Students = NULL ;

    FILE* file = fopen("students.txt","r");// Open the file for reading
    int Id,IdClass ;
    char Name[SIZE], Address[SIZE],DateEnrollment[SIZE];
    int flag = fscanf(file,"%d",&Id);// Read the first Id from the file

    while (flag!=EOF){ // Read data from the file until the end
        fscanf(file,"%d%s%s%s",&IdClass,Name,Address,DateEnrollment);  // Read the remaining fields for each student
        Students= Insert(Id,IdClass,Name,Address,DateEnrollment,Students); // Insert the student into the tree
        flag = fscanf(file,"%d",&Id); // Read the next Id from the file
    }
    fclose(file); // Close the file

    return Students; // Return the constructed tree
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function to insert a new node into the tree based on the name field
Node InsertByName(int Id,int IdClass ,char Name[],char Address[],char DateEnrollment[], Tree T){
    if( T == NULL){
        T = (Node)malloc(sizeof( struct node ) ); // Create a new node if the tree is empty
        if( T == NULL)
            printf("Out of space");
        else{ // Set the values of the new node
            T->Id = Id;
            T->IdClass = IdClass;
            strcpy(T->Name,Name);
            strcpy(T->Address,Address);
            strcpy(T->DateEnrollment,DateEnrollment);
            T->Left = T->Right = NULL;
        }
    }
    else if(strcmp(Name,T->Name)<=0 ) // Recursively insert into the left subtree if the name is less than or equal to the current node's name
        T->Left = InsertByName( Id, IdClass ,Name,Address, DateEnrollment,T->Left);
    else  // Recursively insert into the right subtree if the name is greater than the current node's name
        T->Right = InsertByName( Id, IdClass ,Name,Address, DateEnrollment,T->Right );
    return T;
}

Tree SortByName(Tree dest, Tree sor) {
    // Traverse the tree in an inorder manner

    // Process the left subtree if it exists
    if (sor->Left != NULL)
        dest = SortByName(dest, sor->Left);

    // Insert the current node into the destination tree based on the name
    dest = InsertByName(sor->Id, sor->IdClass, sor->Name, sor->Address, sor->DateEnrollment, dest);

    // Process the right subtree if it exists
    if (sor->Right != NULL)
        dest = SortByName(dest, sor->Right);

    // Return the updated destination tree
    return dest;
}

void Print(Tree tree) {
    // Base case: if the tree is empty, return
    if (tree == NULL)
        return;

    // Inorder traversal: print the left subtree, current node, and then the right subtree

    // Recursively print the left subtree
    Print(tree->Left);

    // Print the current node's information
    printf("%d\t%d\t%s\t%s\t%s\n", tree->Id, tree->IdClass, tree->Name, tree->Address, tree->DateEnrollment);

    // Recursively print the right subtree
    Print(tree->Right);
}

void SearchCity(char Address[], Tree tree) {
    // Base case: if the tree is empty, return
    if (tree == NULL)
        return;

    // Inorder traversal: search for the given city in the tree

    // Recursively search in the left subtree
    SearchCity(Address, tree->Left);

    // Check if the current node's address matches the given city
    if (strcmp(tree->Address, Address) == 0)
        printf("%d\t%d\t%s\t%s\t%s\n", tree->Id, tree->IdClass, tree->Name, tree->Address, tree->DateEnrollment);

    // Recursively search in the right subtree
    SearchCity(Address, tree->Right);
}

void SearchClass(int IdClass, Tree tree) {
    // Base case: if the tree is empty, return
    if (tree == NULL)
        return;

    // Inorder traversal: search for the given class ID in the tree

    // Recursively search in the left subtree
    SearchClass(IdClass, tree->Left);

    // Check if the current node's class ID matches the given class ID
    if (IdClass == tree->IdClass)
        printf("%d\t%d\t%s\t%s\t%s\n", tree->Id, tree->IdClass, tree->Name, tree->Address, tree->DateEnrollment);

    // Recursively search in the right subtree
    SearchClass(IdClass, tree->Right);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Node Find(int X, Tree T) {
    // Base case: if the tree is empty, return NULL
    if (T == NULL)
        return NULL;

        // If the target value is less than the current node's ID, go to the left subtree
    else if (X < T->Id)
        return Find(X, T->Left);

        // If the target value is greater than the current node's ID, go to the right subtree
    else if (X > T->Id)
        return Find(X, T->Right);

        // If the target value is equal to the current node's ID, return the current node
    else
        return T;
}
Node FindMin(Tree T) {
    // Base case: if the tree is empty, return NULL
    if (T == NULL)
        return NULL;

        // If the current node has no left child, it is the minimum node
    else if (T->Left == NULL)
        return T;

        // Otherwise, recursively search for the minimum node in the left subtree
    else
        return FindMin(T->Left);
}

Node Insert(int Id, int IdClass, char Name[], char Address[], char DateEnrollment[], Tree T) {
    // Base case: if the tree is empty, create a new node and assign the values
    if (T == NULL) {
        T = (Node)malloc(sizeof(struct node));
        if (T == NULL)
            printf("Out of space");
        else {
            T->Id = Id;
            T->IdClass = IdClass;
            strcpy(T->Name, Name);
            strcpy(T->Address, Address);
            strcpy(T->DateEnrollment, DateEnrollment);
            T->Left = T->Right = NULL;
        }
    }
        // If the new ID is less than the current node's ID, go to the left subtree
    else if (Id < T->Id)
        T->Left = Insert(Id, IdClass, Name, Address, DateEnrollment, T->Left);
        // If the new ID is greater than the current node's ID, go to the right subtree
    else if (Id > T->Id)
        T->Right = Insert(Id, IdClass, Name, Address, DateEnrollment, T->Right);

    return T;
}

Node Delete(int Id, Tree T) {
    Node TmpCell;
    // Base case: if the tree is empty, print "Element not found"
    if (T == NULL) {
        printf("Element not found");
        return T;
    }
    // Recursively search for the node to delete
    if (Id < T->Id) // If the target ID is less than the current node's ID, go to the left subtree
        T->Left = Delete(Id, T->Left);
    else if (Id > T->Id) // If the target ID is greater than the current node's ID, go to the right subtree
        T->Right = Delete(Id, T->Right);
    else {      // If the target ID is equal to the current node's ID, perform deletion
        // If the node has both left and right children
        if (T->Left && T->Right) {
            // Find the minimum value node in the right subtree
            TmpCell = FindMin(T->Right);
            T->Id = TmpCell->Id; // Replace the current node's ID with the minimum value found
            T->Right = Delete(T->Id, T->Right);// Delete the minimum value node from the right subtree
        }
        else {// If the node has only one child or no child
            TmpCell = T;
            // If the node has no left child
            if (T->Left == NULL)
                T = T->Right;
                // If the node has no right child
            else if (T->Right == NULL)
                T = T->Left;
            free(TmpCell);  // Free the memory of the deleted node
        }
    }
    return T;
}
void PrintFile(Tree tree) {
    // Open the file in append mode
    FILE* file = fopen("students.txt", "a");
    // Base case: if the tree is empty, return
    if (tree == NULL) {
        fclose(file);  // Close the file before returning
        return;
    }
    // Inorder traversal: write the tree nodes to the file
    // Recursively write the left subtree to the file
    PrintFile(tree->Left);
    // Write the current node's information to the file
    fprintf(file, "%d\t%d\t%s\t%s\t%s\n", tree->Id, tree->IdClass, tree->Name, tree->Address, tree->DateEnrollment);
    // Close the file after writing
    fclose(file);
    // Recursively write the right subtree to the file
    PrintFile(tree->Right);
}