#include "TwoThreeUtility.h"

// local constants

// local function prototypes

// main function
int main()
   {
    // initialize function/variables
    TwoThreeNode *treePtr, *cpdTreePtr;
    bool showLocation = true;
       // show title
       printf( "\nTwo Three Tree Test Program\n" );
       printf( "===========================\n" );

    // initialize tree pointer
    treePtr = initializeTwoThreeTree();
    cpdTreePtr = initializeTwoThreeTree();

    printf( "\nAdding: ACS Concrete LC\n" );
    treePtr = addItemWithRawData( treePtr, 317891, "ACS Concrete LC", 
                                                 "C-9", "Concrete", "Phoenix" );
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: ABC Creations LLC\n" );
    treePtr = addItemWithRawData( treePtr, 326323, "ABC Creations LLC", 
                         "CR-61", "Carpentry Remodeling and Repairs", "Mayer" );

    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Sunburst Patios LLC\n" );
    treePtr = addItemWithRawData( treePtr, 143558, "Sunburst Patios LLC", 
        "CR-3", "Awnings Canopies Carports and Patio Cove", "Prescott Valley" );

    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Ez Flow Plumbing LLC\n" );
    treePtr = addItemWithRawData( treePtr, 242432, "Ez Flow Plumbing LLC", 
        "CR-37", "Plumbing", "Chandler" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Steven Douglas Hanson\n" );
    treePtr = addItemWithRawData( treePtr, 284194, "Steven Douglas Hanson", 
        "CR-39", "Air Conditioning and Refrigeration", "Flagstaff" );

    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: JL Stainless Steel LLC\n" );
    treePtr = addItemWithRawData( treePtr, 314286, "JL Stainless Steel LLC", 
        "CR-45", "Sheet Metal", "Phoenix" );
				
    displayDataInOrder( treePtr, showLocation );
  
    printf( "\nAdding: RJ Home Improvement LLC\n" );
    treePtr = addItemWithRawData( treePtr, 334675, "RJ Home Improvement LLC", 
        "R-62", "Minor Home Improvements", "Mesa" );
				
    displayDataInOrder( treePtr, showLocation );
  
    printf( "\nAdding: On Call Refrigeration Inc\n" );
    treePtr = addItemWithRawData( treePtr, 183419, "On Call Refrigeration Inc", 
        "CR-39", "Air Conditioning and Refrigeration", "Yuma" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Everstand Construction LLC\n" );
    treePtr = addItemWithRawData( treePtr, 327027, "Everstand Construction LLC", 
        "R-2", "Excavating Grading and Oil Surfacing", "Scottsdale" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Lopez Brothers Interiors LLC\n" );
    treePtr = addItemWithRawData( treePtr, 310421, "Lopez Brothers Interiors LLC", 
        "CR-1", "Acoustical Systems", "Laveen" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Ray's Top Quality Painting LLC\n" );
    treePtr = addItemWithRawData( treePtr, 318532, "Ray's Top Quality Painting LLC", 
        "CR-34", "Painting and Wall Covering", "Glendale" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Sanctuary Custom Construction LLC\n" );
    treePtr = addItemWithRawData( treePtr, 285262, "Sanctuary Custom Construction LLC", 
        "B", "General Residential Contractor", "Tucson" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nAdding: Top Choice Electrical Contractors Corp\n" );
    treePtr = addItemWithRawData( treePtr, 333642, "Top Choice Electrical Contractors Corp", 
        "KB-1", "Dual Building Contractor", "Chandler" );
				
    displayDataInOrder( treePtr, showLocation );

    printf( "\nCopying Tree\n" );
    cpdTreePtr = copyTwoThreeTree( treePtr );

    displayDataInOrder( cpdTreePtr, showLocation );

    // end program

       // clear dynamic data
       treePtr = clearTwoThreeTree( treePtr );
       cpdTreePtr = clearTwoThreeTree( cpdTreePtr );

       // display program end
       printf( "\nProgram End\n" );

       // return successful operation
       return 0;
   }
