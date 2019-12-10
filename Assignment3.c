/* Brittany Vanderlip
   Date: August 8, 2019 */

//Include appropriate libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Create a new type named Node to store tweet information
//Stores tweet id, time created at, text, and user information
struct Node{

   int id;
   char created_at[51];
   char text[141];
   char user[21];

   struct Node *next; //To create a linked list

};

typedef struct Node tweet; //Declare new variable tweet as type Node

//Create new type named TwitterHeader that stores a count and version
//Used in saveTweets and loadTweets
typedef struct TwitterHeader{
  int count;
  float version;
}Header;

//Function prototypes
tweet * CreateTweet(int id, char *username);

void InsertAtHead(tweet **head, char *username, int id);

void SearchTweet(tweet *head, char *keyword);

void DisplayTweets(tweet *head);

void *SaveTweets(tweet *head, Header tweetHeader, char *filename);

void clearTweets(tweet **head);

void LoadTweets(tweet **head, Header tweetHeader, char *filename);

//begin program execution
int main(){

  //declaration of variables
  tweet *head;
  char keyword[21];
  head = NULL; //Setting head as null or empty
  char username[21];
  int id = 1;
  int option;
  char filename[21];
  Header tweetHeader;

  //Prompt user to enter a username and store in variable username of 20 characters
  printf("Hello! And welcome to Twitter!\nPlease enter your username: ");
  scanf("%20[^\n]s\n", username);

  //Message to user
  printf("\nHi %s, please choose a number from the menu list below: \n\n", username);

  //Do while loop to create menu. Exit out of menu when user enters the number 6
  do {
    //Prints the menu
    printf("***********************************\n\n");
    printf("1. Create a new tweet\n");
    printf("2. Search tweets\n");
    printf("3. Display tweets\n");
    printf("4. Save tweets to file\n");
    printf("5. Load tweets from file\n");
    printf("6. Exit\n\n");

    scanf("%d", &option);
    getchar();//Consumes newline character
    printf("\n");

    //Switch case based on which option user chooses
    switch (option) {
      case 1:   InsertAtHead(&head, username, id); //Call function to insert at head which then calls function create tweet
                id++;//Incrememnt id for next tweet
                break;

      case 2:   printf("Enter the keyword you wish to find in the tweet: ");//Prompt user to enter keyword they wish to find
                scanf("%20[^\n]s", keyword);
                SearchTweet(head, keyword);//Call search function
                break;

      case 3:   DisplayTweets(head);//Call display tweets function
                break;

      case 4:   tweetHeader.count = 0; //Set tweetheader.count to 0 to save tweets to a file
                tweetHeader.version = 1.0;
                printf("Please enter a filename you wish to save your tweets in: ");//Prompt user to create filename to save tweets
                scanf("%[^\n]s", filename);
                getchar();
                SaveTweets(head, tweetHeader, filename);//Call SaveTweets function
                break;

      case 5:   printf("Please enter the filename you wish to load: ");//Prompt user to enter filename of tweets they want to load
                scanf("%[^\n]s", filename);
                getchar();
                clearTweets(&head);//Clear tweets in filename to overwrite them with newest tweets
                LoadTweets(&head, tweetHeader, filename);//Call LoadTweets Function
                break;

      default: if (option!=6)//If user does not eneter a valid number prompt user to try again
                printf("Invalid option. Please choose a valid number.\n");
    }
  }while(option != 6);//If user enters 6, exit menu

  printf("It's been great tweeting! See you again!\n");
}

//Function: Creates tweet and stores in linked list of type tweet
//Input: Id and username
//Output: Tweet that displays the id, UTC time, username, and tweet itself
tweet * CreateTweet(int id, char *username){
  //declare pointer of type tweet
  tweet *new;

  //Memory allocation for pointer new
  new = (tweet *) malloc(sizeof(tweet));

  //Copy username into the linked list
  strcpy(new->user, username);

  //Assign id into the linked list
  new -> id = id;

  //Prompt user to enter text for tweet and store in linked list
  printf("Please enter a tweet no more than 140 characters: ");
  scanf("%140[^\n]s\n", new->text);


  //Code to find UTC from java2s.com.
  struct tm *local; //Create a new struct
  time_t t;

  t = time(NULL);
  local = gmtime(&t); //Gets UTC time and data
  strcpy(new->created_at, asctime(local));//Copy the time into the linked list


  //Print out user's tweet with Id, date and time and username
  printf("\nHere is your tweet!\n\n");
  printf("id : %d \t Time & Date : %s\n", id, new->created_at);
  printf("Username: %s\tTweet:\"%s\"\n\n", new -> user, new->text);

  //Assign null to next node in linked list
  new -> next = NULL;

  //End function
  return new;
}

//Function: Insert the tweet into the head of the linked list
//Input: pointer head, username, id
//Output: Stores tweetInfo into the head if not empty
void InsertAtHead(tweet **head, char *username, int id){
  tweet * tweetInfo = CreateTweet(id, username);

  if(*head == NULL){
    *head = tweetInfo;
  }
  else {
    tweetInfo -> next = *head;
    *head = tweetInfo;
  }

}

//Function: Search through the tweet to find keyword
//Input: head, keyword
//Output: If corresponding tweets match the keyword
void SearchTweet(tweet *head, char *keyword){
  //Search linked list tweets for keyword string, if match, display strings
  //strstr function handles this
  int count = 0;       //if count is 0; print no tweet has been found

  //Loop through each text in the list to find a match to the keyword
  while(head!=NULL){

      //When the word in the text matches the keyword, print out the results
      if(strstr( head->text, keyword) != NULL ){

          printf("Match Found!\n\n");

          printf("id : %d \t Time & Date : %s\n", head->id, head->created_at);
          printf("Username: %s \t Tweet:\"%s\"\n\n", head -> user, head->text);

          count++;
      }
      //head becomes the next node in the linked list
      head = head -> next;
    }

    //If count = 0, this means no matches were found
    if(count == 0){

        printf("No tweets found\n\n");

    }else{

        printf("Found %d tweets with the keyword \"%s\"!\n\n", count, keyword);

    }

    return;

 }

//Function: Display tweets to user
//Input: head
//Output: Print the id, username, UTC time, and tweet
void DisplayTweets(tweet *head){
  //If the head is empty, do not print anything
  if (head == NULL)
    return;

  //Display the tweet to the user
  printf("\nid : %d \t  Time & Date : %s\n", head->id, head->created_at);
  printf("Username:%s \t  Tweet:\"%s\"\n\n", head -> user, head->text);

  //Call DisplayTweets of next tweet in the linked list
  DisplayTweets(head -> next);
}

//Function: Determines the size of the linked List
//Input: Head
//Output: Returns the number of tweets in the linked list
int ListSize(tweet *head){
  int count = 0;

  //Loops through list to count how many tweets there are
  while (head != NULL){
    count += 1;
    head = head -> next;
  }
  return count;
}

//Function: saves tweets in linked list to a file
//Input: head, tweetHeader, filename
//Output: Saves tweets into the filename
void *SaveTweets(tweet *head, Header tweetHeader, char *filename){
  int count = 0;

  //Open file to write to
  FILE *tweetFile = fopen(filename, "wb");
  tweetHeader.count += ListSize(head);

  fwrite(&tweetHeader, sizeof(tweetHeader), 1, tweetFile);

  //If no tweets have been made. AKA linked list is empty
  if(head == NULL){
    printf("No tweets have been made. Cannot store in file.\n");
  }

  //Loop through the tweets (linked list) and write the tweet information to the file
  while(head != NULL){
    tweet * c = head -> next;
    head -> next = NULL;
    fwrite(head, sizeof(tweet), 1, tweetFile);

    head = c;
    count++;
  }
  //Display a success prompt to user
  printf("\nSuccess!! Your tweets have been saved to \"%s\"!\n\n", filename);
  fclose(tweetFile);//Close the file

}

//Function: Clears tweet information in file you want to load to replace with new tweets. ID increments
//Input: head
//Output: clear tweet list
void clearTweets(tweet **head){
  tweet * current = *head;

  while (current !=NULL){
    current = current->next;
    free(*head);//Free the head
    *head = current;
  }
}

//Function: load tweets from file
//Input: head, tweetHeader, filename
//Output: Display the tweets in the file back to the user
void LoadTweets(tweet **head, Header tweetHeader, char *filename){

  //Open file to read
  FILE *tweetFile = fopen(filename, "rb");
  fread(&tweetHeader, sizeof(Header), 1, tweetFile);

  //Store the number of tweets into variable size
  int size = tweetHeader.count;

  //Display the number of tweets in file to user
  printf("\nNumber of Tweets in File = %d\n", tweetHeader.count);

  //Declare variable and pointer of type tweet
  tweet temp;
  tweet *ptr;

  //Loop through the list to load the tweets from the file
  for(int i = 0; i < size; i++){
    fread(&temp, sizeof(tweet), 1, tweetFile);

    ptr = (tweet*)malloc(sizeof(tweet));
    strcpy(ptr -> user, temp.user);//copy temp.user to ptr->user
    strcpy(ptr -> text, temp.text);//copy temp.text to ptr -> text
    strcpy(ptr -> created_at, temp.created_at);//copy temp.created_at to ptr->created_at
    ptr -> id = temp.id;//store temp.id to prt->id

    //Display the tweet information to the user
    printf("\nid : %d \t  Time & Date : %s\n", ptr -> id, ptr -> created_at);
    printf("Username:%s \t  Tweet:\"%s\"\n\n", ptr -> user, ptr -> text);

    //If head of the list is empty, ptr is assigned back to *head
    if(*head == NULL){
      *head = ptr;
    }
    //If not at the end of the list, then assign *head to ptr->next (next in the list) and loop through again
    else {
      ptr -> next = *head;
      *head = ptr;
    }

  }
  fclose(tweetFile);//Close the file

  }
