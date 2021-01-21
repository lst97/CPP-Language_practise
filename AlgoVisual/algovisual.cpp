#include "algovisual.h"

//////////
// Constructor
////
AlgoVisual::AlgoVisual(int* plist, int size, window wind){
    m_wind.instance = wind;
    rectangle r = window_area(wind);
    m_wind.height = r.height;
    m_wind.width = r.width;

    m_plist = plist;
    m_listsize = size;
    m_delay = DEFAULT_DELAY;

    return;
}

////
// Defination
////
int AlgoVisual::start(){
    // Check if enough screen space
    if (m_listsize > m_wind.width) return -1;
    
    m_barwidth = m_wind.width / m_listsize;
    m_drawbar(m_plist);
    m_bubbleSort();
    return 0;
}

void AlgoVisual::m_drawbar(int* plist){
    rectangle r;
    for (int ecx = 0; ecx < m_listsize; ecx++){
        r.x = (double)(ecx * m_barwidth);
        r.y = (double)m_wind.height - TEXT_RESERVED;
        r.width = (double)m_barwidth;
        r.height = -(double)*(plist + ecx);
        fill_rectangle(BAR_COLOR_DEFAULT, r);
    }

    refresh_screen();

    return;
}

void AlgoVisual::m_drawbar(int pos, color ccode){
    fill_rectangle(
        ccode, 
        (double)(pos * m_barwidth),
        (double)m_wind.height - TEXT_RESERVED,
        (double)m_barwidth,
        -(double)*(m_plist + pos));
    return;
}

void AlgoVisual::m_bubbleSort(){
    string lval, rval, cpos;
    int ecx, edx;
    bool swapped; 
    for (ecx = 0; ecx < m_listsize - 1; ecx++){
        swapped = false;
        for (edx = 0; edx < m_listsize - ecx - 1; edx++){
            #ifdef MANUAL_RUN
                while (!quit_requested()){
                    process_events();

                    if(key_down(SPACE_KEY)){
                        clear_screen(BACKGROUND_COLOR);
                        m_drawbar(m_plist);
                        m_drawbar(edx, BAR_COLOR_CURRENT);
                        m_drawbar(edx + 1, BAR_COLOR_COMP);

                        lval = std::to_string(m_plist[edx]);
                        rval = std::to_string(m_plist[edx + 1]);
                        m_drawcondidtion(edx, lval, rval, BAR_COLOR_DEFAULT);
                        refresh_screen();
                        delay(m_delay);

                        if (m_plist[edx] > m_plist[edx + 1]){
                            m_drawbar(edx + 1, BAR_COLOR_SWAP);
                            m_drawcondidtion(edx, lval, rval, BAR_COLOR_CURRENT);
                            refresh_screen();
                            delay(m_delay);
                            m_swap(m_plist + edx, m_plist + edx + 1);
                            swapped = true;
                        }else{
                            m_drawcondidtion(edx, lval, rval, BAR_COLOR_SWAP);
                            refresh_screen();
                            delay(m_delay);
                        }
                        break;
                    }
                }
            #else
                clear_screen(BACKGROUND_COLOR);
                m_drawbar(m_plist);
                m_drawbar(edx, BAR_COLOR_CURRENT);
                m_drawbar(edx + 1, BAR_COLOR_COMP);

                lval = std::to_string(m_plist[edx]);
                rval = std::to_string(m_plist[edx + 1]);
                m_drawcondidtion(edx, lval, rval, BAR_COLOR_DEFAULT);
                refresh_screen();
                delay(m_delay);

                // If the text color is green, swap happened.
                if (m_plist[edx] > m_plist[edx + 1]){
                    m_drawbar(edx + 1, BAR_COLOR_SWAP);
                    m_drawcondidtion(edx, lval, rval, BAR_COLOR_CURRENT);
                    refresh_screen();
                    delay(m_delay);
                    m_swap(m_plist + edx, m_plist + edx + 1);
                    swapped = true;
                }else{
                    m_drawcondidtion(edx, lval, rval, BAR_COLOR_SWAP);
                    refresh_screen();
                    delay(m_delay);
                }
            #endif
        }
        if (swapped == false) break;
    }

    // Finish
    clear_screen(BACKGROUND_COLOR);
    m_drawbar(m_plist);
    draw_text("DONE!", BAR_COLOR_DEFAULT, (double)20, (double)(m_wind.height - TEXT_RESERVED + 10));
    refresh_screen();
    for (ecx = 0; ecx < m_listsize; ecx++){
        m_drawbar(ecx, BAR_COLOR_CURRENT);
        refresh_screen();
        delay(10);
    }

    delay(5000);
    return;
}

void AlgoVisual::m_drawcondidtion(int cpos, string lval, string rval, color ccode){
    draw_text("[" + std::to_string(cpos) + "]" + " Condidtion: " + lval + " > " + rval + " ?", ccode, 20, m_wind.height - TEXT_RESERVED + 10);
    return;
}

void AlgoVisual::m_swap(int* lpos, int* rpos){
    int temp = *lpos;
    *lpos = *rpos;
    *rpos = temp;
    return;
}
//////////
