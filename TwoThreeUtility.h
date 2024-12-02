#ifndef TWO_THREE_UTILITY_H
#define TWO_THREE_UTILITY_H

// header file
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StandardConstants.h"

// local constants
typedef enum { LEFT_CHILD_SELECT = 101, 
                        CENTER_CHILD_SELECT, RIGHT_CHILD_SELECT } SelectionCode;
typedef enum { ZERO_DATA_ITEMS, ONE_DATA_ITEM, 
                               TWO_DATA_ITEMS, THREE_DATA_ITEMS } ItemCountCode;

// data structures
typedef struct ContractorStruct
   {
    int licenseNum;
    char businessName[ STD_STR_LEN ];
    char classCode[ MIN_STR_LEN ];
    char classDetail[ STD_STR_LEN ];
    char city[ MIN_STR_LEN ];
   } ContractorType;

typedef struct TwoThreeStruct
   {
    ContractorType *leftData, *centerData, *rightData;

    int numItems;

    struct TwoThreeStruct *leftChildPtr, *ctrChildPtr, *rightChildPtr;
    struct TwoThreeStruct *auxLeftPtr, *auxRightPtr;
    struct TwoThreeStruct *parentPtr;
    
   } TwoThreeNode;

// prototypes

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
                                                      ContractorType *newData );

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
                                                      ContractorType *newData );

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
                                                      ContractorType *newData );

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
                                      const char *clsDetail, const char *city );

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
TwoThreeNode *clearTwoThreeNode( TwoThreeNode *wkgPtr );

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
TwoThreeNode *clearTwoThreeTree( TwoThreeNode *wkgPtr );

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
int compareStrings( const char *leftString, const char *rightString );

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
TwoThreeNode *copyTwoThreeTree( TwoThreeNode *wkgPtr );

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
                 const char *clsCode, const char *clsDetail, const char *city );

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
ContractorType *createContractorDataFromAdt( const ContractorType *sourcePtr );

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
TwoThreeNode *createEmptyTwoThreeNode();

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
                                TwoThreeNode *parPtr, SelectionCode childCode );

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
void displayDataInOrder( TwoThreeNode *wkgPtr, bool showLocation );

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
                                            int levelCount, bool showLocation );

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
TwoThreeNode *initializeTwoThreeTree();

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
void resolveThreeFourNode( TwoThreeNode **rootPtr, TwoThreeNode *wkgPtr );

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
char toLowerCase( char testChar );

#endif  // TWO_THREE_UTILITY_H
