#include "splashkit.h"
#include <string>

/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : alfovisual.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 09/01/2021
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce Bubble sort
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 09012021    lst97       1      First release
;*
;* Known Issue       :
;* 
;* TODO              :
;*
;|**********************************************************************;
*/

//#define MANUAL_RUN

#define BACKGROUND_COLOR COLOR_WHITE
#define BAR_COLOR_DEFAULT COLOR_BLACK
#define BAR_COLOR_CURRENT COLOR_GREEN
#define BAR_COLOR_COMP COLOR_ORANGE
#define BAR_COLOR_SWAP COLOR_RED

#define TEXT_RESERVED 25
#define DEFAULT_DELAY 1

/**
 * AlgoVisual object, save all data it needs to visualize number to a bar.
 * 
 * @field   m_plist             List contain random integer variable
 * @field   m_listsize          List size
 * @field   m_barwidth          Width of each bar
 * @field   m_delay             Time delay in ms for each visuzlize operation
 */
class AlgoVisual{
private:
    int* m_plist;
    int m_listsize;
    int m_barwidth;
    int m_delay;

private:
    /**
     * Sub object, used for memorize the window instance and its' size.
     * 
     * @field   instance             Instance for the main window
     * @field   height               Window height
     * @field   width                Window width
     */
    class Wind{
    public:
        window instance;
        int height;
        int width;
    }m_wind;

private:
    /**
     * Bubblesort algorithm also handle graphic.
     */
    void m_bubbleSort();

    /**
     * Swap two list attributes.
     * 
     * @param lpos    Left target
     * @param rpos    Right target
     */
    void m_swap(int* lpos, int* rpos);

    /**
     * Drawing all attribute in the list to window with DEFAULT_COLOR
     * 
     * @param plist    Array pointer
     */
    void m_drawbar(int* plist);

    /**
     * Draw one bar with different color
     * 
     * @param pos   The posistion in the array
     * @param ccode Color code from Splashkit
     */
    void m_drawbar(int pos, color ccode);

    /**
     * Draws the condition text in the window
     * 
     * @param cpos    Posistion for current iteration
     * @param lval    Left value
     * @param rval    Right value
     * @param ccode   Color code from Splashkit
     */
    void m_drawcondidtion(int cpos, string lval, string rval, color ccode);

    /**
     * Update Window Paint
     * 
     * @param player_to_draw    The player to draw to the screen
     */
    void m_refresh();

public:
    /**
     * Constructor, visualize all bar in the list
     * 
     * @param plist    Array pointer
     * @param size     Array size
     * @param wind     Window instance
     */
    AlgoVisual(int* plist, int size, window wind);

public:
    /**
     * Start to draw
     * 
     * @return 0 If the attributes in the class is OK.
     */
    int start();
};
