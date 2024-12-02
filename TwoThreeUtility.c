// header file
#include "TwoThreeUtility.h"

// function implementations
/*
Name: addAndOrganizeData
Process: adds item to a previously established node, 
         in the appropriate location,
         returns pointer to the node
Function input/parameters: working pointer (TwoThreeNode *),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to updated two or three node (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: strcpy (as needed), createContractorDataFromAdt,
              compareStrings
*/
TwoThreeNode *addAndOrganizeData( TwoThreeNode *wkgPtr, 
                                                       ContractorType *newData )
   {
      // declare variables
      ContractorType *newNode;

      // create a new node 
       // function: createContractorDataFromAdt
      newNode = createContractorDataFromAdt(newData);

      // if the num items = 1
      if(wkgPtr->numItems == ONE_DATA_ITEM)
       {
         // if name is greater than center
           // function: compareStrings
         if(compareStrings(newNode->businessName, 
                                         wkgPtr->centerData->businessName) > 0)
          {
            // left = center
            wkgPtr->leftData = wkgPtr->centerData;

             // right = new
            wkgPtr->rightData = newNode;
          }
         // if name is less than center
        else
          {
            // right = center
            wkgPtr->rightData = wkgPtr->centerData;

            // left = new
            wkgPtr->leftData = newNode;

          }
         // set center to null
         wkgPtr->centerData = NULL;
         
       }
      else
       {
         // if name is greater than right
          // function: compareStrings
         if(compareStrings(newNode->businessName, 
                                          wkgPtr->rightData->businessName) > 0)
          {
            // center = right
            wkgPtr->centerData = wkgPtr->rightData;

            // right = new
            wkgPtr->rightData = newNode;
          }
         // if name is less than left 
          // function: compareStrings
         else if(compareStrings(newNode->businessName, 
                                           wkgPtr->leftData->businessName) < 0)
          {
            // center = left
            wkgPtr->centerData = wkgPtr->leftData;

            // left = new
            wkgPtr->leftData = newNode;
          }

         // else 
         else
          {
            // center = new
            wkgPtr->centerData = newNode;
          }
       }
        // increment the items
         wkgPtr->numItems = wkgPtr->numItems + ONE_DATA_ITEM;

       // return the new node 
       return wkgPtr;
   }

/*
Name: addItemWithAdtData
Process: adds item to tree given contractor Adt data
Function input/parameters: address of root pointer (TwoThreeNode **),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to root node
Device input/---: none
Device output/---: none
Dependencies: addItemWithAdtDataHelper
*/
TwoThreeNode *addItemWithAdtData( TwoThreeNode *rootPtr,
                                                       ContractorType *newData )
   {
    TwoThreeNode *wkgPtr = rootPtr;

    addItemWithAdtDataHelper( &rootPtr, wkgPtr, newData );

    return rootPtr;
   }

/*
Name: addItemWithAdtDataHelper
Process: helper function adds item to tree given contractor Adt data
Function input/parameters: address of root pointer (TwoThreeNode **),
                           working pointer (TwoThreeNode *),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: strcpy (as needed), createContractorDataFromAdt,
              compareStrings, addItemWithAdtDataHelper,
              addAndOrganizeData, resolveThreeFourNode
*/
void addItemWithAdtDataHelper( TwoThreeNode **rootPtr, 
                                              TwoThreeNode *wkgPtr,
                                                       ContractorType *newData )
   {

     // if working pointer is null
     if(wkgPtr == NULL) 
      {
        // create empty node
          // function: createEmptyTwoThreeNode
        wkgPtr = createEmptyTwoThreeNode();
        
       // set numitems = 1
        wkgPtr->numItems = ONE_DATA_ITEM;

       // set centerData = newData
         // function: createContractorDataFromAdt
        wkgPtr->centerData = createContractorDataFromAdt(newData);

       // set root pointer to working pointer we just set up 
        *rootPtr = wkgPtr; 
      }
     // else if numitems = 1 && left child is not null
     else if(wkgPtr->numItems == ONE_DATA_ITEM && wkgPtr->leftChildPtr != NULL)
      {
         // new data < center
           // function: compareStrings
         if(compareStrings(newData->businessName, 
                                         wkgPtr->centerData->businessName) < 0)
          {
              // recurse on the left child 
                // function: addItemWithAdtDataHelper
              addItemWithAdtDataHelper(rootPtr, wkgPtr->leftChildPtr, newData);
          }
         else 
          {
              // recurse on the right child 
               // function: addItemWithAdtDataHelper
             addItemWithAdtDataHelper(rootPtr, wkgPtr->rightChildPtr, newData);
          }
         
      }
     // else numitems = 2 && ctrchild != NULL
     else if(wkgPtr->numItems == TWO_DATA_ITEMS && wkgPtr->ctrChildPtr != NULL)
      {  
          // new data < left data
            // function: compareStrings
          if(compareStrings(newData->businessName, 
                                           wkgPtr->leftData->businessName) < 0)
           {
             // recurse on the left child 
               // function: addItemWithAdtDataHelper
             addItemWithAdtDataHelper(rootPtr, wkgPtr->leftChildPtr, newData);
           }
           // new data > right data
             // function: compareStrings
          else if(compareStrings(newData->businessName, 
                                          wkgPtr->rightData->businessName) > 0)
           {
             // recurse on the right child 
              // function: addItemWithAdtDataHelper
             addItemWithAdtDataHelper(rootPtr, wkgPtr->rightChildPtr, newData);
           }
          else 
           {
             // recurse on the center child 
              // function: addItemWithAdtDataHelper
             addItemWithAdtDataHelper(rootPtr, wkgPtr->ctrChildPtr, newData);
           }
      }
     // else 
     else 
      {
         // call the add and organize 
          // function: addAndOrganizeData
         wkgPtr = addAndOrganizeData(wkgPtr, newData);

         // call the resolve
           // function: resolveThreeFourNode 
         resolveThreeFourNode(rootPtr, wkgPtr);
      }
   }

/*
Name: addItemWithRawData
Process: adds node with all Contractor data
Function input/parameters: pointer to root node (TwoThreeNode *),
                           license number (int), business name (const char *),
                           class code, class detail, city (const char *)
Function output/parameters: none
Function output/returned: pointer to root node
Device input/---: none
Device output/---: none
Dependencies: createContractorDataWithData, addItemWithAdtDataHelper, free
*/
TwoThreeNode *addItemWithRawData( TwoThreeNode *rootPtr,
                              int licNum, 
                                 const char *bizName, const char *clsCode,
                                       const char *clsDetail, const char *city )
   {
    ContractorType *newData = createContractorDataWithData( licNum, 
                                            bizName, clsCode, clsDetail, city );
    TwoThreeNode *wkgPtr = rootPtr;

    addItemWithAdtDataHelper( &rootPtr, wkgPtr, newData );

    free( newData );

    return rootPtr;
   }

/*
Name: clearTwoThreeNode
Process: deallocates memory for one individual node
         returns NULL,
         does not handle children of node
Function input/parameters: pointer to node (TwoThreeNode *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
TwoThreeNode *clearTwoThreeNode( TwoThreeNode *wkgPtr )
   {
     // if the working pointer is not null
     if(wkgPtr != NULL)
      {
        // if the left data is not null
        if(wkgPtr->leftData != NULL)
         {
           // clear the left 
           // function: free
           free(wkgPtr->leftData);
         }
         // if the center data is not null
         if(wkgPtr->centerData != NULL)
          {
            // clear the center 
            // function: free
            free(wkgPtr->centerData);

          }
         
         if(wkgPtr->rightData != NULL)
          {
            // clear the right
           // function: free
            free(wkgPtr->rightData);
          }
         
         // free the working pointer
          // function: free
         free(wkgPtr);
      }
     // return null 
     return wkgPtr; 
   }

/*
Name: clearTwoThreeTree
Process: deallocates memory for all tree nodes individually, 
         returns NULL
Function input/parameters: pointer to tree (TwoThreeNode *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: clearTwoThreeNode, clearTwoThreeTree (recursively)
*/
TwoThreeNode *clearTwoThreeTree( TwoThreeNode *wkgPtr )
   {
    // check if working pointer is null
    if(wkgPtr != NULL)
     {
       // clearing the left pointer 
        // function: clearTwoThreeTree
       clearTwoThreeTree(wkgPtr->leftChildPtr);

       // clearing the center pointer
        // function: clearTwoThreeTree
       clearTwoThreeTree(wkgPtr->ctrChildPtr);

       // clearing the right pointer 
        // function: clearTwoThreeTree
       clearTwoThreeTree(wkgPtr->rightChildPtr);

       // clear the tree
        // function: clearTwoThreeNode
       clearTwoThreeNode(wkgPtr);
     }

    return NULL; 
   }

/*
Name: compareStrings
Process: test for alphabetical difference between two strings,
         returns less than zero if left string 
         is alphabetically less than right string,
         returns equal to zero if left string 
         is alphabetically equal to right string,
         returns greater than zero if left string 
         is alphabetically greater than right string,
         tests all characters as lower case,
         if two strings are alphabetically equal,
         longer string is greater unless they are equal length
Function input/parameters: left and right strings (const char *)
Function output/parameters: none
Function output/returned: result as specified (int)
Device input/---: none
Device output/---: none
Dependencies: toLowerCase, strlen
*/
int compareStrings( const char *leftString, const char *rightString )
   {
    int diff, index = 0;

    while( leftString[ index ] != NULL_CHAR 
                                          && rightString[ index ] != NULL_CHAR )
       {
        diff = toLowerCase( leftString[ index ] ) 
                                          - toLowerCase( rightString[ index ] );

        if( diff != 0 )
           {
            return diff;
           }

        index++;
       }

    return strlen( leftString ) - strlen( rightString );
   }

/*
Name: copyTwoThreeTree
Process: creates duplicate copy of given two three tree
Function input/parameters: pointer to two three tree (TwoThreeNode *)
Function output/parameters: none
Function output/returned: pointer to new copy of two three tree (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: createEmptyTwoThreeNode, createContractorDataFromAdt,
              copyTwoThreeTree (recursively)
*/
TwoThreeNode *copyTwoThreeTree( TwoThreeNode *wkgPtr )
   {
    // declare variables 
    TwoThreeNode *newNode;

    // check if working pointer is null
    if(wkgPtr != NULL)
     {
         // create a new node
          // function: createEmptyTwoThreeNode
         newNode = createEmptyTwoThreeNode();

         // set the left child 
          // function: copyTwoThreeTree
         newNode->leftChildPtr = copyTwoThreeTree(wkgPtr->leftChildPtr);

         // check if left child is not null
         if(newNode->leftChildPtr != NULL)
          {
            // if not null, set left child parent to new node
            wkgPtr->leftChildPtr->parentPtr = newNode;
          }
         // check if there's only 1 data item, set the center data
         if(wkgPtr->numItems == ONE_DATA_ITEM)
          {
            // set num items to 1
            newNode->numItems = ONE_DATA_ITEM;

            // set center data
             // function: createContractorDataFromAdt
            newNode->centerData = 
                               createContractorDataFromAdt(wkgPtr->centerData);
          }
         // if 2, set left data, center data
         if(wkgPtr->numItems == TWO_DATA_ITEMS)
          {
            // set num items to 2
            newNode->numItems = TWO_DATA_ITEMS;

            // set the left data
             // function: createContractorDataFromAdt
            newNode->leftData = createContractorDataFromAdt(wkgPtr->leftData);

            // set the center child
             // function: copyTwoThreeTree
            newNode->ctrChildPtr = copyTwoThreeTree(wkgPtr->ctrChildPtr);
          
           // check if center is not null
           if(newNode->ctrChildPtr != NULL)
            {
              // if not null, set center child parent pointer to new node 
              newNode->ctrChildPtr->parentPtr = newNode;
            }
    
           // set the right data
            // function: createContractorDataFromAdt
           newNode->rightData = createContractorDataFromAdt(wkgPtr->rightData);
        }
         // set the right child 
          // function: copyTwoThreeTree
          newNode->rightChildPtr = copyTwoThreeTree(wkgPtr->rightChildPtr);

         // if right child is not null
         if(newNode->rightChildPtr != NULL)
          {
            // set the right child parent pointer to new node 
            newNode->rightChildPtr->parentPtr = newNode;
          }
         // return new node            
        return newNode;  
     }
     // return null
    return NULL;
   }

/*
Name: createContractorDataWithData
Process: creates contractor data node from given contractor data items
Function input/parameters: license number (int), business name (const char *),
                           class code, class detail, and city (const char *)
Function output/parameters: none
Function output/returned: pointer to new contractor data (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: malloc/sizeof, strcpy
*/
ContractorType *createContractorDataWithData( int licNum, const char *bizName, 
                  const char *clsCode, const char *clsDetail, const char *city )
   {
    ContractorType *newPtr 
                         = (ContractorType *)malloc( sizeof( ContractorType ) );

    newPtr->licenseNum = licNum;
 
    strcpy( newPtr->businessName, bizName );
    strcpy( newPtr->classCode, clsCode );
    strcpy( newPtr->classDetail, clsDetail );
    strcpy( newPtr->city, city );

    return newPtr;
   }

/*
Name: createContractorDataFromAdt
Process: creates contractor data node from given contractor Adt
Function input/parameters: source Adt pointer (const ContractorType *)
Function output/parameters: none
Function output/returned: pointer to new contractor data (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: createContractorDataWithData
*/
ContractorType *createContractorDataFromAdt( const ContractorType *sourcePtr )
   {
    return createContractorDataWithData( sourcePtr->licenseNum, 
                           sourcePtr->businessName, sourcePtr->classCode, 
                                      sourcePtr->classDetail, sourcePtr->city );
   }

/*
Name: createEmptyTwoThreeNode
Process: allocates data for two three node, sets all data to zero or NULL
         as appropriate, returns pointer to node
Function input/parameters: none
Function output/parameters: none
Function output/returned: pointer to created node (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: malloc/sizeof
*/
TwoThreeNode *createEmptyTwoThreeNode()
   {
    TwoThreeNode *newPtr = (TwoThreeNode *)malloc( sizeof( TwoThreeNode ) );

    newPtr->numItems = ZERO_DATA_ITEMS;

    newPtr->leftData = NULL;
    newPtr->centerData = NULL;
    newPtr->rightData = NULL;

    newPtr->leftChildPtr = NULL;
    newPtr->auxLeftPtr = NULL;
    newPtr->ctrChildPtr = NULL;
    newPtr->auxRightPtr = NULL;
    newPtr->rightChildPtr = NULL;

    newPtr->parentPtr = NULL;

    return newPtr;
   }

/*
Name: createNewChild
Process: creates new child selectably from left or right side of three four node,
         sets all links for the new node, returns pointer to node
Function input/parameters: working and parent pointers (TwoThreeNode *),
                           code to indicate left or right child (SelectionCode)
Function output/parameters: none
Function output/returned: pointer to newly created child
Device input/---: none
Device output/---: none
Dependencies: createContractorDataFromAdt, createEmptyTwoThreeNode
*/
TwoThreeNode *createNewChild( TwoThreeNode *wkgPtr, 
                                 TwoThreeNode *parPtr, SelectionCode childCode )
   {
    TwoThreeNode *newPtr = createEmptyTwoThreeNode();

    if( childCode == LEFT_CHILD_SELECT )
       {
        newPtr->centerData = createContractorDataFromAdt( wkgPtr->leftData );
        newPtr->leftChildPtr = wkgPtr->leftChildPtr;
        newPtr->rightChildPtr = wkgPtr->auxLeftPtr;
       
        if( newPtr->leftChildPtr != NULL )
           {
            newPtr->leftChildPtr->parentPtr = newPtr;
            newPtr->rightChildPtr->parentPtr = newPtr;
           }
       }
   
    else  // assume right child select
       {
        newPtr->centerData = createContractorDataFromAdt( wkgPtr->rightData );
        newPtr->leftChildPtr = wkgPtr->auxRightPtr;
        newPtr->rightChildPtr = wkgPtr->rightChildPtr;

        if( newPtr->rightChildPtr != NULL )
           {
            newPtr->leftChildPtr->parentPtr = newPtr;
            newPtr->rightChildPtr->parentPtr = newPtr;
           }
       }

    newPtr->parentPtr = parPtr;

    newPtr->numItems = ONE_DATA_ITEM;

    return newPtr;
   }

/*
Name: displayDataInOrder
Process: user function to call for in order display,
         uses divider bars above and below display with title on top bar,
         calls helper, must display "Data Not Found - Display Aborted"
         if tree is empty
Function input/parameters: working pointer (TwoThreeNode *),
                           Boolean flag to indicate position and level display
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: displayDataInOrderHelper, printf
*/
void displayDataInOrder( TwoThreeNode *wkgPtr, bool showLocation )
   {
    int levelCount = 0;

    printf( "\n========== Two Three Tree Display ==========\n" );

    if( wkgPtr != NULL )
       {
        displayDataInOrderHelper( wkgPtr, levelCount, showLocation );

        printf( "\n============================================\n" );
       }

    else
       {
        printf( "\nData Not Found - Display Aborted\n" );
       }
   }

/*
Name: displayDataInOrderHelper
Process: helper function implements in order data display of two three tree,
         if Boolean flag is set, also shows position in node
         and level in tree,
         no display (printf) may be repeated for a given position
         (i.e., one printf for 'C', one printf for 'L', one printf for 'R')
Function input/parameters: working pointer (TwoThreeNode *), level count (int),
                           Boolean flag for level/position (bool)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf, displayDataInOrderHelper (recursively)
*/
void displayDataInOrderHelper( TwoThreeNode *wkgPtr, 
                                             int levelCount, bool showLocation )
   {
    
     // if the working pointer not null 
     if(wkgPtr != NULL)
      {
         
        // recurse with left child 
         // function: displayDataInOrderHelper
        displayDataInOrderHelper(wkgPtr->leftChildPtr, 
                                       levelCount+ONE_DATA_ITEM, showLocation);
         
            // check if numitems = 1
          if(wkgPtr->numItems == ONE_DATA_ITEM)
           {
            // if the show location is true
            if(showLocation) 
             {
               // print the level count
                // function: printf
               printf("C%d/", levelCount);
             }
             // print center data
              // function: printf
             printf("%s\n", wkgPtr->centerData->businessName);
           }
            // if numitems = 2
            if(wkgPtr->numItems == TWO_DATA_ITEMS)
             {
              // if showLocation is true
               if(showLocation)
                {
                 // print the level count
                  // function: printf
                  printf("L%d/", levelCount);
                }
               // print the left data
                // function: printf
               printf("%s\n", wkgPtr->leftData->businessName);
            
               // recurse with center child 
                // function: displayDataInOrderHelper
               displayDataInOrderHelper(wkgPtr->ctrChildPtr,
                                        levelCount+ONE_DATA_ITEM,showLocation);
 
               // if showLocation is true
               if(showLocation)
               {
                // print the level count
                 // function: printf
                 printf("R%d/", levelCount);
                 
               }

               // print the right data
                // function: printf
               printf("%s\n", wkgPtr->rightData->businessName);
         
             }
         
       // recurse with right data
        // function: displayDataInOrderHelper
       displayDataInOrderHelper(wkgPtr->rightChildPtr,levelCount+ONE_DATA_ITEM,
                                                                 showLocation);
      }
      
   }

/*
Name: initializeTwoThreeTree
Process: returns NULL to initialize tree pointer
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
TwoThreeNode *initializeTwoThreeTree()
   {
    return NULL;
   }

/*
Name: resolveThreeFourNode
Process: is passed the most recent node added,
         checks for 3/4 node, if so, breaks it up into separate left and right
         children and passes the center value to the node above,
         when complete, recurses to the parent node to resolve that as needed
Function input/parameters: address of root pointer (TwoThreeNode **),
                           pointer to working pointer (TwoThreeNode *)
Function output/parameters: root pointer address, in case root pointer
                            is updated (TwoThreeNode **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: createEmptyTwoThreeNode, createContractorDataFromAdt,
              createNewChild, resolveThreeFourNode (recursively)
*/
void resolveThreeFourNode( TwoThreeNode **rootPtr, TwoThreeNode *wkgPtr)
   {
      
      // declare variables
      TwoThreeNode *newNode = wkgPtr->parentPtr;
      
      // if there's 3 data items
      if(wkgPtr->numItems == THREE_DATA_ITEMS)
       {
         // check if wkg's parent is null
         if(newNode == NULL)
          {
            // create empty node
             // function: createEmptyTwoThreeNode
             newNode = createEmptyTwoThreeNode();

            // set root to parent
            *rootPtr = newNode;

            // set num items = 1
            newNode->numItems = ONE_DATA_ITEM;

            // create center data
             // function: createContractorDataFromAdt
            newNode->centerData = 
                               createContractorDataFromAdt(wkgPtr->centerData);

            // create left child
             // function: createNewChild
            newNode->leftChildPtr = 
                            createNewChild(wkgPtr, newNode, LEFT_CHILD_SELECT);

            // create right child
             // function: createNewChild
            newNode->rightChildPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT); 
          }
          // else: parent num items = 1
         else if(newNode->numItems == ONE_DATA_ITEM)
         {
           // increment items
           newNode->numItems = TWO_DATA_ITEMS;

          // if left child = wkg
          if(newNode->leftChildPtr == wkgPtr)
           {
            // right data = center data
            newNode->rightData = newNode->centerData;

            // center data = null
            newNode->centerData = NULL;

            // create left data
             // function: createContractorDataFromAdt
            newNode->leftData =createContractorDataFromAdt(wkgPtr->centerData);

            // create left child
             // function: createNewChild
            newNode->leftChildPtr = createNewChild(wkgPtr, newNode, 
                                                            LEFT_CHILD_SELECT);

            // create the center child
             // function: createNewChild
            newNode->ctrChildPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT);
           }
         
         // else 
         else 
         {
           
          // parent->leftData = null
           newNode->leftData = newNode->centerData;

          // center = null
           newNode->centerData = NULL;

          // create right data
           // function: createContractorDataFromAdt
           newNode->rightData =createContractorDataFromAdt(wkgPtr->centerData);

         // create center child
          // function: createNewChild
           newNode->ctrChildPtr = createNewChild(wkgPtr, newNode, 
                                                            LEFT_CHILD_SELECT);

         // create right child 
          // function: createNewChild
           newNode->rightChildPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT);
         }
         
       }
     // else for the 3 nodes 
     else
      {
        // increment num items
        newNode->numItems = THREE_DATA_ITEMS;

        //  if parent->leftChild = wkg
        if(newNode->leftChildPtr == wkgPtr)
         {
            // center to left
            newNode->centerData = newNode->leftData;
            
           // create left data
            // function: createContractorDataFromAdt
           newNode->leftData = createContractorDataFromAdt(wkgPtr->centerData);

         // create left child 
          // function: createNewChild
           newNode->leftChildPtr = createNewChild(wkgPtr, newNode, 
                                                            LEFT_CHILD_SELECT);

         // create aux left 
          // function: createNewChild
           newNode->auxLeftPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT);

         // aux right = center child 
           newNode->auxRightPtr = newNode->ctrChildPtr;

         // center child = null 
           newNode->ctrChildPtr = NULL;
         }
       // else : parent->center child = wkg
        else if(newNode->ctrChildPtr == wkgPtr)
         {
            
          // create center data
           // function: createContractorDataFromAdt
           newNode->centerData = 
                               createContractorDataFromAdt(wkgPtr->centerData);

          // create aux left 
           // function: createNewChild
           newNode->auxLeftPtr = createNewChild(wkgPtr, newNode, 
                                                            LEFT_CHILD_SELECT);
           // aux left->parent = parent
           newNode->auxLeftPtr->parentPtr = newNode;
          // create aux right
           // function: createNewChild
           newNode->auxRightPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT);
        
          // aux right->parent = parent
           newNode->auxRightPtr->parentPtr = newNode;
         }
         
       // else assume the center
       else 
        {
         
         // center data = right data
         newNode->centerData = newNode->rightData;

         // create right data
          // function: createContractorDataFromAdt
         newNode->rightData = createContractorDataFromAdt(wkgPtr->centerData);

         // create aux right
          // function: createNewChild
         newNode->auxRightPtr = createNewChild(wkgPtr, newNode, 
                                                            LEFT_CHILD_SELECT);

         // create right child
          // function: createNewChild
         newNode->rightChildPtr = createNewChild(wkgPtr, newNode, 
                                                           RIGHT_CHILD_SELECT);

         // aux left = center child 
         newNode->auxLeftPtr = newNode->ctrChildPtr;

         // center child = null
         newNode->ctrChildPtr = NULL;
        }
         
      }
      
       // free working pointer
        // function: free
       free(wkgPtr);
       
       // resolve(root, parent)
        // function: resolveThreeFourNode
       resolveThreeFourNode(rootPtr, newNode);
       }

   }

/*
Name: toLowerCase
Process: tests for upper case character, if so, converts to lower case,
         otherwise, takes no action
Function input/parameters: test character (char)
Function output/parameters: none
Function output/returned: updated character as specified
Device input/---: none
Device output/---: none
Dependencies: none
*/
char toLowerCase( char testChar )
   {
    if( testChar >= 'A' && testChar <= 'Z' )
       {
        return testChar - 'A' + 'a';
       }

    return testChar;
   }