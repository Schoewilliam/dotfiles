/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/** modifiers **/
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.52
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define PANEL_HEIGHT    20        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    TILE      /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define ATTACH_ASIDE    True      /* False means new window is master */
#define FOLLOW_WINDOW   False     /* follow the window when moved to a different desktop */
#define FOLLOW_MOUSE    False     /* focus the window the mouse just entered */
#define CLICK_TO_FOCUS  True      /* focus an unfocused window when clicked  */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define BORDER_WIDTH    1         /* window border width */
#define FOCUS           "#ff950e" /* focused window border color    */
#define UNFOCUS         "#444444" /* unfocused window border color  */
#define MINWSZ          50        /* minimum window size in pixels  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        7         /* number of desktops - edit DESKTOPCHANGE keys to suit */

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     desktop  follow  float */
    { "MPlayer",     -1,    True,   True },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with ', NULL };'
 */
static const char *termcmd[] = { "urxvt",     NULL };
static const char *menucmd[] = { "dmenu_run", "-fn", "-*-envypn-medium-*-*--13-*-*-*-*-*-*-1", "-nb", "#909090", "-nf", "#222", "-sb", "#1a1a1a", "-sf", "#ccc", "-l", "10", NULL };
static const char *volupcmd[] = { "amixer", "-c", "0", "set", "Master", "3+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-c", "0", "set", "Master", "3-", "unmute", NULL };
static const char *volmutecmd[] = { "amixer", "sset", "Master", "toggle", NULL };
static const char *mpdplaycmd[] = { "ncmpcpp", "toggle", NULL };

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  MOD1,             XK_b,          togglepanel,       {NULL}},
    {  MOD1,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD4,             XK_q,          killclient,        {NULL}},
    {  MOD1,             XK_Right,      next_win,          {NULL}},
    {  MOD1,             XK_Left,       prev_win,          {NULL}},
    {  MOD1,             XK_r,          resize_master,     {.i = -10}}, /* decrease size in px */
    {  MOD1,             XK_s,          resize_master,     {.i = +10}}, /* increase size in px */
    {  MOD1,             XK_l,          resize_stack,      {.i = -10}}, /* shrink   size in px */
    {  MOD1,             XK_g,          resize_stack,      {.i = +10}}, /* grow     size in px */
    {  MOD1|CONTROL,     XK_Left,       rotate,            {.i = -1}},
    {  MOD1|CONTROL,     XK_Right,      rotate,            {.i = +1}},
    {  MOD1|SHIFT,       XK_h,          rotate_filled,     {.i = -1}},
    {  MOD1|SHIFT,       XK_l,          rotate_filled,     {.i = +1}},
    {  MOD1,             XK_Tab,        last_desktop,      {NULL}},
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|SHIFT,       XK_l,          move_down,         {NULL}},
    {  MOD1|SHIFT,       XK_g,          move_up,           {NULL}},
    {  MOD1|SHIFT,       XK_t,          switch_mode,       {.i = TILE}},
    {  MOD1|SHIFT,       XK_m,          switch_mode,       {.i = MONOCLE}},
    {  MOD1|SHIFT,       XK_b,          switch_mode,       {.i = BSTACK}},
    {  MOD1|SHIFT,       XK_g,          switch_mode,       {.i = GRID}},
    {  MOD1|SHIFT,       XK_f,          switch_mode,       {.i = FLOAT}},
    {  MOD1|CONTROL,     XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD4,             XK_Return,     spawn,             {.com = termcmd}},
    {  MOD1,             XK_p,          spawn,             {.com = menucmd}},
    {  0,                0x1008ff13,    spawn,             {.com = volupcmd}}, /* Augmenter le volume  touche multimédia */
    {  0,                0x1008ff11,    spawn,             {.com = voldowncmd}}, /* réduire le volume */
    {  0,                0x1008ff12,    spawn,             {.com = volmutecmd}}, /* muet */
    {  0,                0x1008ff14,    spawn,             {.com = mpdplaycmd}}, /* play music via ncmpcpp */
    {  MOD4,             XK_j,          moveresize,        {.v = (int []){   0,  25,   0,   0 }}}, /* move down  */
    {  MOD4,             XK_k,          moveresize,        {.v = (int []){   0, -25,   0,   0 }}}, /* move up    */
    {  MOD4,             XK_l,          moveresize,        {.v = (int []){  25,   0,   0,   0 }}}, /* move right */
    {  MOD4,             XK_h,          moveresize,        {.v = (int []){ -25,   0,   0,   0 }}}, /* move left  */
    {  MOD4|SHIFT,       XK_j,          moveresize,        {.v = (int []){   0,   0,   0,  25 }}}, /* height grow   */
    {  MOD4|SHIFT,       XK_k,          moveresize,        {.v = (int []){   0,   0,   0, -25 }}}, /* height shrink */
    {  MOD4|SHIFT,       XK_l,          moveresize,        {.v = (int []){   0,   0,  25,   0 }}}, /* width grow    */
    {  MOD4|SHIFT,       XK_h,          moveresize,        {.v = (int []){   0,   0, -25,   0 }}}, /* width shrink  */
       DESKTOPCHANGE(    XK_F1,                             0)
       DESKTOPCHANGE(    XK_F2,                             1)
       DESKTOPCHANGE(    XK_F3,                             2)
       DESKTOPCHANGE(    XK_F4,                             3)
       DESKTOPCHANGE(    XK_F5,                             4)
       DESKTOPCHANGE(    XK_F6,                             5)
       DESKTOPCHANGE(    XK_F7,                             6)
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD1,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD1,    Button3,     mousemotion,   {.i = RESIZE}},
    {  MOD4,    Button3,     spawn,         {.com = menucmd}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */
