/*
Linked List Project
Derek O'Brien
CIS 170 Section 01

This program will allow user to create an inventory list of parts. The user will be able to
create new lists, display list, display information related to an individual part,
modify list, insert to new items, delete items, save list, open existing list,
and add to an existing list.  
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Inventory{
	
	int part;
	int qty;
	float price;
	struct Inventory* next;
}*start;

void createList();
void displayList();
void insertStruct();
void displayPartInfo();
void deleteStruct(int);
void saveList();
void modifyStruct();
void addToList();
int findPart(struct Inventory **, int *);

int main()
{
	int partNo;
	char choice;
	start = NULL;
	
	while(1)
	{
		system("cls");
		printf("Please selected the corresponding letter of the action you would like to take:\n");
		printf("\n\tA. Create a new linked list of part number, quantity, and price");
		printf("\n\tB. Add to an existing list (read from a file)");
		printf("\n\tC. Print the entire list");
		printf("\n\tD. Print the information for one user selected part number");
		printf("\n\tE. Insert a new structure into the linked list");
		printf("\n\tF. Modify an existing structure into the linked list");
		printf("\n\tG. Delete an existing structure from the list");
		printf("\n\tH. Save a list (to a file)");
		printf("\n\tI. Exit from the program");
		printf("\n\nEnter your choice: ");
		scanf("\n%c", &choice);
		switch(choice)
		{
			case  'A' : case 'a':
			createList();
			break;
		case 'B' : case 'b' :
			addToList();
			break;
		case 'C' : case 'c' :
			displayList();
			break;
		case 'D' : case 'd' :
			displayPartInfo();
			break;			
		case 'E' : case 'e' :
			insertStruct();
			break;
		case 'F' : case 'f' :
			modifyStruct();
			break;				
		case 'G' : case 'g' :
			printf("Enter part number to delete: ");
			scanf("%d", &partNo);
			deleteStruct(partNo);
			break;
		case 'H' : case 'h' :
			saveList();
			break;  			
		case 'I' : case 'i' :
			 exit(1);
		default :
			printf("Invalid selection!");
			getch();
			break;
		}
	}
	return 0;
}

void createList()
{
	int partNo, quantity;
	float cost;
	char check = 'y';
	system("cls");
	struct Inventory *temp, *ptr;
	
	while(check == 'y' || check =='Y')
	{
		temp = (struct Inventory *)malloc(sizeof(struct Inventory));
		
			printf("Enter part number: ");
			scanf("%d", &partNo);
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			printf("Enter price: ");
			scanf("%f", &cost);
			
			temp->part=partNo;
			temp->qty=quantity;
			temp->price=cost;
			temp->next=NULL;
		
		if(start==NULL)
		{
			start=temp;
		}
		else
		{
			ptr->next = temp;
		}
		
		ptr = temp;
		
		printf("Would you like to enter another item (y/n)? ");
		scanf("\n%c", &check);
	}
	printf("List created");
	getch();
	system("cls");
}

void displayList()
{
	struct Inventory *ptr;
	ptr=start;
	system("cls");
	if(start == NULL)
	{
	
		printf("List is empty");
		getch();
		return;
	}
	puts("Inventory List");
    printf("Part# Quantity Price\n");
	while(ptr !=NULL)
	{
			printf("%-6d\t%5d\t%.2f\n", ptr->part, ptr->qty, ptr->price);
			ptr=ptr->next;
	}
	getch();
	system("cls");
}

void insertStruct() 
{
    int partNo, quantity, found = 0;;
	float cost;
	struct Inventory *current;
    struct Inventory *temp;
    struct Inventory *previous; 
   
   partNo = findPart(&current, &found);
   
   if (found == 1)
   {
   		printf("Part number %d already exists in list! \nEnter new part number or choose modify from the main menu!", partNo);
   		getch();
   }
   else
   {
	   //create new node
	    current = (struct Inventory *)malloc(sizeof(struct Inventory)); 
	
	    //check whether node is created or not
	    if(current == NULL) 
	    {
	        printf("Insufficient memory.");
	        return;
	    }   
	    
		printf("Enter quantity: ");
		scanf("%d", &quantity);
		printf("Enter price: ");
		scanf("%f", &cost);
	
	    //assigning values to the parts of the node 
		current->part=partNo;
		current->qty=quantity;
		current->price=cost;
		current->next=NULL;
		
	    //checking if new node is the only node in list
	    if (start == NULL) 
	    {       
	        start = current;
	    } 
	    //If value is less than the value of first node
	    else if(partNo < start -> part) 
	    {
	        current -> next = start;
	        start = current;
	    } 
	    else 
	    {   
	        previous = start;
	        temp = start -> next;
	
	        //Go to the position where node is to be inserted
	        while(temp != NULL && partNo > temp -> part) 
	        {
	            previous = temp;
	            temp = temp -> next;
	        }
	
	        //Insert the node at particular position
	        if(temp == NULL) 
	        {
	            previous -> next = current;
	        } 
	        else 
	        {
	            current -> next = temp;
	            previous -> next = current;
	        }
	    } 
	    printf("Part number %d added to list.", partNo);
	    getch();
	}
}

void displayPartInfo()
{
	int partNo, found = 0;
	struct Inventory *current;
	current = start;
       
    partNo = findPart(&current, &found);
        
    if (found == 1)
    {	
       	printf("Part# Quantity Price\n");
       	printf("%-6d\t%5d\t%.2f\n", current->part, current->qty, current->price);
        getch();
    }
    else
    {
		printf("Part number %d not found", partNo);
        getch();
    }
}

void deleteStruct(int partNo)
{
	struct Inventory *ptr;
	ptr = start;
	
	if (ptr == start && ptr->part == partNo)
	{
		start=start->next;
		free(ptr);
	}
	else
	{
        // Go to the node next to the node that is to be deleted 
        while(ptr->next != NULL && (ptr->next)->part != partNo)
        {
                ptr = ptr -> next;
        }
        if(ptr->next==NULL)
        {
                printf("Part number %d is not present in the list\n",partNo);
                getch();
                return;
        }
        // ptr points to the node next to the one that will be deleted
        struct Inventory *temp;
        temp = ptr -> next;
        //temp points to the node that will be removed
        ptr->next = temp->next;
        free(temp); //deallocate memory of deleted node
	}
   
    printf("Part number %d info deleted.", partNo);
    getch();
}

void saveList()
{
	FILE *fp;
	struct Inventory *ptr;
	ptr=start;
	
	fp = fopen("testlinklist.csv","w");
	if (fp == NULL)
	{
		printf("You may not open this file");
		getch();
		exit(0);
	}
	
	if(start == NULL)
	{
		printf("List is empty");
		getch();
		return;
	}

	while(ptr !=NULL)
	{
			fprintf(fp, "%d,%d,%.2f\n", ptr->part, ptr->qty, ptr->price);
			ptr=ptr->next;
	}
	fclose(fp);
	
	printf("File saved.");
	getch();
}

void addToList()
{
	FILE *fp;
    struct Inventory *temp, *ptr;
    temp = start;
    int partNo, quantity;
    float cost;
    char line[1000];
	char *p;
	
	fp = fopen("testlinklist.csv","r");
	
	if (fp == NULL)
	{
		printf("Error opening file");
		getch();
		exit(0);
	}
 
     while(fgets(line, 1000, fp) != NULL) 
	 {
	 	
		temp = (struct Inventory *)malloc(sizeof(struct Inventory));
		
			p = strtok(line, ",");
	 		sscanf(p,"%d",&partNo);
	 		p = strtok(NULL, ",");
	 		sscanf(p,"%d",&quantity);
	 		p = strtok(NULL, ",");
	 		sscanf(p,"%f",&cost);
			
			temp->part=partNo;
			temp->qty=quantity;
			temp->price=cost;
			temp->next=NULL;
		
		if(start==NULL)
		{
			start=temp;
		}
		else
		{
			ptr->next = temp;
		}
		
		ptr = temp;

	}
	fclose( fp );
	printf("List loaded!\nMake a selection from the main menu to carry out desired action.");
	getch();
 		
}

void modifyStruct()
{
	struct Inventory *current;
	int partNo, quantity, found = 0;
	float cost;
	current=start;
	
	partNo = findPart(&current, &found);
    
	if (found == 1)
	{
		printf("Enter quantity: ");
		scanf("%d", &quantity);
		printf("Enter price: ");
		scanf("%f", &cost);
		
	    current->qty = quantity;
	    current->price = cost;
	    
	    printf("Part number %d information updated.", partNo);
	}
	else
		printf("Part number %d not founded", partNo);
	
	getch();
}

int findPart(struct Inventory **currentPtr, int *foundPtr)
{
	int partNo;
	*currentPtr = start;
	
	printf("Enter part number: ");
	scanf("%d", &partNo);
	
 	while(*currentPtr != NULL)
 	{
 		if ((*currentPtr)->part == partNo)
 		{
 			*foundPtr = 1;
 			break;
		 }
        *currentPtr = (*currentPtr)-> next;
    }
    return partNo;
}

