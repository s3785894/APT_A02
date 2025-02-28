#ifndef COSC_ASS_ONE_TYPES
#define COSC_ASS_ONE_TYPES

//--------------------------------------------------------------------
// Student Information for Credits

#define STUDENT_ONE     "Name: Nicholas Linney-Barber \n"\
                        "ID: s3660035 \n"\
                        "Email: s3660035@student.rmit.edu.au"

#define STUDENT_TWO     "Name: David Brown \n"\
                        "ID: s3785894 \n"\
                        "Email: s3785894@student.rmit.edu.au"

#define STUDENT_THREE   "Name: Si Long Leong \n"\
                        "ID: s3785099 \n"\
                        "Email: s3785099@student.rmit.edu.au"

//--------------------------------------------------------------------

#define LINE_DIVIDER    std::cout << "---------------------------------" << std::endl;

// Game Parameters for a basic game of azul as per M1 specifications
#define NUM_FACTORIES 5
#define FACTORY_SIZE 4
#define MOSAIC_DIM 5
#define MAX_TILES 100
#define NUM_COLOURS 5
#define FLOOR_SIZE 7

#define EXIT_SUCESS 0

typedef char Mosaic[MOSAIC_DIM][MOSAIC_DIM];
typedef char Factories[NUM_FACTORIES][FACTORY_SIZE];

#endif 
