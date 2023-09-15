/* See LICENSE file for copyright and license details. */
 
/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 31;  /* snap pixel */
static const unsigned int gappih         = 9;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 9;  /* vert inner gap between windows */
static const unsigned int gappoh         = 20;  /* horiz outer gap between windows and screen edge */ 
static const unsigned int gappov         = 30; 
static       int smartgaps               = 0;   /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 0;   /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 1;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False display systray on other*/
static const int showsystray             = 0;   /* 0 means no systray */

static const char *fonts[]        = { "monofur:size=14:antialias=true:autohint=true", "Noto sans CJK JP:size=17:antialias=true:autohint" };
static const char dmenufont[]       =  "Comic sans:size=69";
/* Tag names and lenght*/
//static const char *tags[] = { "§", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
static const char *tags[] = { "夢", "歌", "世", "梨", "曜", "羽", "花", "瑠", "海", "風", "愛" };
static const Rule rules[] = {

        /* class          instance    title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "Gimp",          NULL,      NULL,           0,          0,          0,           0,        -1 },
//      { "firefox",       NULL,      NULL,           1 << 2,     0,          0,          -1,        -1 },
        { "discord",       NULL,      NULL,           1 << 10,    0,          0,          -1,        -1 },
        { "Dwarf_Fortress",NULL,      NULL,           1 << 9,     0,          0,          -1,        -1 },
        { "st",            NULL,      NULL,           0,          0,          1,           0,        -1 },
        { "Alacritty",     NULL,      NULL,           0,          0,          1,           0,        -1 },
        { "Audacious",     NULL,      NULL,           1 << 1,     0,          0,           0,        -1 },
        { NULL,            NULL,     "Event Tester",  0,          0,          0,           1,        -1 }, /* xev */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 0  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
   /* symbol     arrange function */
   { "",         tile },    /* first entry is default */
   { "[M]",      monocle },
   { "|M|",      centeredmaster },
   { "[@]",      spiral },
   { "[\\]",     dwindle },
   { "H[]",      deck },
   { "TTT",      bstack },
   { "===",      bstackhoriz },
   { "HHH",      grid },
   { "###",      nrowgrid },
   { "---",      horizgrid },
   { ":::",      gaplessgrid },
   { ">M>",      centeredfloatingmaster },
   { "><>",      NULL },    /* no layout function means floating behavior */
   { NULL,       NULL },

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

#include "/home/lu/.cache/wal/colors-wal-dwm.h"

/* commands */
//static const char *[]            = {""};
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run"};
static const char *termcmd[] = {"NULL"};
static unsigned int nexttagskip(void);
static void viewnextskip(const Arg *arg);
#include "movestack.c"
void resetnmaster(const Arg *arg);

#include "focusurgent.c"
static Key keys[] = {
/* modifier                     key            function        argument */

{ Mod1Mask|ShiftMask,           XK_Tab,        focusurgent,    {0} },
{ MODKEY,                       XK_d,          spawn,          {.v = dmenucmd } },
{ MODKEY|ShiftMask,             XK_d,          spawn,          {.v = (const char *[]){"/home/lu/.local/bin/sha"} } }, 
{ MODKEY|ShiftMask,             XK_Return,     spawn,          {.v = (const char *[]){"alacritty", NULL} } },
{ MODKEY,                       XK_t,          spawn,          {.v = (const char *[]){"st", NULL} } },
{ MODKEY|ShiftMask,             XK_e,          spawn,          {.v = (const char *[]){"/home/lu/.local/bin/emacsclient.sh" } } },
{ MODKEY,         		        XK_b,          spawn,          {.v = (const char *[]){"/home/lu/.local/bin/btc"} } },
{ MODKEY|ShiftMask,             XK_v,          spawn,          {.v = (const char *[]){"swm", NULL } } },
//{ Mod1Mask,                   XK_Tab,        spawn,          SHCMD("rofi -show")  },
{ MODKEY,                       XK_n,          spawn,          SHCMD("xclip -o -se c >> /tmp/clip")  },  
{ MODKEY|ShiftMask,             XK_n,          spawn,          SHCMD("cat /tmp/clip | dmenu -c -l 5 | xclip -se c")  },  
{ MODKEY,                       XK_v,          spawn,          SHCMD("compiledwm && pkill dwm && dwm") },
{ MODKEY,                       XK_adiaeresis, spawn,          SHCMD("killall ruby; exec rubyxsr") },
//{ MODKEY,                     XK_apostrophe, spawn,          {.v = (const char *[]){"compiledwm", NULL } } },
{ MODKEY,      		           XK_F1,         spawn,          {.v = (const char *[]){"/home/lu/.local/bin/redshift_inc.sh" } } },
{ MODKEY,      		           XK_End,        spawn,          {.v = (const char *[]){"/home/lu/.local/bin/rngwall" } } },
{ MODKEY,      		           XK_Next,       spawn,          {.v = (const char *[]){"/home/lu/.local/bin/selwall" } } },
{ MODKEY,      		           XK_m,          spawn,          {.v = (const char *[]){"/home/lu/.local/bin/dmbook"  } } },
{ MODKEY,                       XK_c,          spawn,          SHCMD("pkill picom || picom") },
{ MODKEY,      	     	        XK_Insert,     spawn,          SHCMD("pactl set-sink-mute $(pactl info | awk '/Default Sink/ {print $3}') toggle ; refresh-xsrdwm") },
{ MODKEY,      	     	        XK_e,          spawn,          SHCMD("pactl set-sink-volume '@DEFAULT_SINK@' +500 ; refresh-xsrdwm") },
{ MODKEY,         		        XK_w,          spawn,          SHCMD("pactl set-sink-volume '@DEFAULT_SINK@' -500 ; refresh-xsrdwm") },
{ MODKEY,                       XK_F3,         spawn,          SHCMD("notify-send Volume: $(pamixer --get-volume-human)") },
{ MODKEY,      	    	        XK_F2,         spawn,          {.v = (const char *[]){"/home/lu/.local/bin/pactl_sink" } } },
{ MODKEY,         	  	        XK_r,          spawn,          SHCMD("st -e pulsemixer") },
{ MODKEY,      	    	        XK_F4,         spawn,          SHCMD("xrandr --output DP-1 --mode 1920x1080") },
{ MODKEY,      	    	        XK_F5,         spawn,          SHCMD("xrandr --output DVI-D-0 --mode 1920x1080 --right-of HDMI-0") },
{ MODKEY|ShiftMask,             XK_F5,         spawn,          SHCMD("xrandr --output DVI-D-0 --off") },
{ MODKEY,                       XK_q,          spawn,          SHCMD("dmkill") },
{ NULL,                         XK_Print,      spawn,          SHCMD("maim -m 10 -s -u | tee /home/lu/.trash/$(date +%s).webp | xclip -se c -t image/png") },
{ MODKEY,                       XK_Print,      spawn,          SHCMD("maim -m 10 -u /home/lu/.trash/$(date +%s).webp") },
{ MODKEY,                       XK_Scroll_Lock,spawn,          SHCMD("zenity --filename=/home/lu/.trash/ --file-selection") },
{ MODKEY,                       XK_y,          spawn,          SHCMD("mpv $(xclip -o)") },
{ MODKEY,         		        XK_Pause,      spawn,          {.v = (const char *[]){"/home/lu/.local/bin/./dmpower"} } },
{ MODKEY|ShiftMask,             XK_s,          spawn,          {.v = (const char *[]){"/home/lu/.local/bin/./dmsearch"} } },
{ MODKEY,                       XK_Home,       spawn,          {.v = (const char *[]){"tabletarea"} } },
{ MODKEY|ShiftMask,	           XK_p,          togglebar,      {0} },
{ MODKEY|ControlMask,           XK_Down,       moveresize,     {.v = "0x 25y 0w 0h" } },
{ MODKEY|ControlMask,           XK_Up,         moveresize,     {.v = "0x -25y 0w 0h" } },
{ MODKEY|ControlMask,           XK_Right,      moveresize,     {.v = "25x 0y 0w 0h" } },
{ MODKEY|ControlMask,           XK_Left,       moveresize,     {.v = "-25x 0y 0w 0h" } },
{ MODKEY|ControlMask|ShiftMask, XK_Down,       moveresize,     {.v = "0x 0y 0w 25h" } },
{ MODKEY|ControlMask|ShiftMask, XK_Up,         moveresize,     {.v = "0x 0y 0w -25h" } },
{ MODKEY|ControlMask|ShiftMask, XK_Right,      moveresize,     {.v = "0x 0y 25w 0h" } },
{ MODKEY|ControlMask|ShiftMask, XK_Left,       moveresize,     {.v = "0x 0y -25w 0h" } },
{ MODKEY,                       XK_Up,         focusstack,     {.i = -1 } },	
{ MODKEY,                       XK_Down,       focusstack,     {.i = +1 } },
{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },	
{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
{ MODKEY|ShiftMask,             XK_period,     incnmaster,     {.i = +1 } },
{ MODKEY,                       XK_period,     incnmaster,     {.i = +1 } },
{ MODKEY|ShiftMask,             XK_comma,      incnmaster,     {.i = -1 } },
{ MODKEY,                       XK_comma,      incnmaster,     {.i = -1 } },
{ MODKEY,                       XK_minus,      resetnmaster,   {0} },
{ MODKEY|ShiftMask,             XK_minus,      resetnmaster,   {0} },
{ MODKEY,                       XK_Left,       movestack,      {.i = +1 } },
{ MODKEY,                       XK_Right,      movestack,      {.i = -1 } },
{ MODKEY,                       XK_h,          movestack,      {.i = +1 } },
{ MODKEY,                       XK_l,          movestack,      {.i = -1 } },
//{ MODKEY|ControlMask|ShiftMask, XK_j,        aspectresize,   {.i = +24} },
//{ MODKEY|ControlMask|ShiftMask, XK_k,        aspectresize,   {.i = -24} },
{ MODKEY|ShiftMask,             XK_h,          setmfact,       {.f = -0.05} },
{ MODKEY|ShiftMask,             XK_l,          setmfact,       {.f = +0.05} },
{ MODKEY|ShiftMask,             XK_k,          setcfact,       {.f = +0.25} },
{ MODKEY|ShiftMask,             XK_j,          setcfact,       {.f = -0.25} },

{ MODKEY|ShiftMask,             XK_Left,       setmfact,       {.f = -0.05} },
{ MODKEY|ShiftMask,             XK_Right,      setmfact,       {.f = +0.05} },
{ MODKEY|ShiftMask,             XK_Up,         setcfact,       {.f = +0.25} },
{ MODKEY|ShiftMask,             XK_Down,       setcfact,       {.f = -0.25} },

{ MODKEY|ShiftMask,             XK_o,          setcfact,       {.f =  0.00} },
{ MODKEY,                       XK_Return,     zoom,           {0} },
{ MODKEY|Mod1Mask,              XK_u,          incrgaps,       {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,       {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_i,          incrigaps,      {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,      {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_o,          incrogaps,      {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,      {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,     {.i = -1 } },
{ MODKEY,                       XK_p,          togglegaps,     {0} },
{ MODKEY|Mod1Mask,              XK_p,          defaultgaps,    {0} },
{ MODKEY|Mod1Mask,              XK_Tab,        view,           {0 } },
{ MODKEY,                       XK_Tab,        viewnext,       {0} },
{ MODKEY,                       XK_BackSpace,  viewprev,       {0} },
//{ MODKEY,                       XK_Tab,        viewnextskip,   {0} },
{ MODKEY|ShiftMask,             XK_Tab,        tagtonext,      {0} },
{ MODKEY|ShiftMask,             XK_BackSpace,  tagtoprev,      {0} },
{ MODKEY|ShiftMask,             XK_q,          killclient,     {0} },
{ MODKEY|ShiftMask,             XK_a,          setlayout,      {.v = &layouts[0]} },
{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[1]} },
{ MODKEY,                       XK_s,          setlayout,      {.v = &layouts[2]} },
{ MODKEY,                       XK_g,          setlayout,      {.v = &layouts[3]} },
{ MODKEY|Mod1Mask,              XK_a,          setlayout,      {.v = &layouts[4]} },
{ MODKEY|Mod1Mask,              XK_s,          setlayout,      {.v = &layouts[5]} },
{ MODKEY|Mod1Mask,              XK_d,          setlayout,      {.v = &layouts[6]} },
{ MODKEY|Mod1Mask,              XK_q,          setlayout,      {.v = &layouts[7]} },
{ MODKEY|Mod1Mask,              XK_w,          setlayout,      {.v = &layouts[8]} },
{ MODKEY|Mod1Mask,              XK_e,          setlayout,      {.v = &layouts[9]} },
{ MODKEY|Mod1Mask,              XK_r,          setlayout,      {.v = &layouts[10]} },
{ MODKEY|Mod1Mask,              XK_f,          setlayout,      {.v = &layouts[11]} },
{ MODKEY|Mod1Mask,              XK_z,          setlayout,      {.v = &layouts[12]} },
{ MODKEY|Mod1Mask,              XK_x,          setlayout,      {.v = &layouts[13]} },
{ MODKEY|ShiftMask,             XK_space,      setlayout,      {0} },
{ MODKEY,                       XK_space,      togglefloating, {0} },
{ MODKEY|ShiftMask,             XK_f,          togglefullscr,  {0} },
{ MODKEY,                       XK_plus,       view,           {.ui = ~0 } },
{ MODKEY|ShiftMask,             XK_plus,       tag,            {.ui = ~0 } },
{ MODKEY,                       XK_z,          focusmon,       {.i = -1 } },
{ MODKEY,                       XK_x,          focusmon,       {.i = +1 } },
{ MODKEY|ShiftMask,             XK_z,          tagmon,         {.i = -1 } },
{ MODKEY|ShiftMask,             XK_x,          tagmon,         {.i = +1 } },
TAGKEYS(                        XK_section,                    0)
TAGKEYS(                        XK_1,                          1)
TAGKEYS(                        XK_2,                          2)
TAGKEYS(                        XK_3,                          3)
TAGKEYS(                        XK_4,                          4)
TAGKEYS(                        XK_5,                          5)
TAGKEYS(                        XK_6,                          6)
TAGKEYS(                        XK_7,                          7)
TAGKEYS(                        XK_8,                          8)
TAGKEYS(                        XK_9,                          9)
TAGKEYS(                        XK_0,                         10)
TAGKEYS(                        XK_Escape,                    11)
TAGKEYS(                        NULL,                         12)
TAGKEYS(                        NULL,                         13)
TAGKEYS(                        NULL,                         14)
TAGKEYS(                        NULL,                         15)
TAGKEYS(                        NULL,                         16)
TAGKEYS(                        NULL,                         17)
TAGKEYS(                        NULL,                         17)
TAGKEYS(                        NULL,                         18)
TAGKEYS(                        NULL,                         19)
//{ MODKEY|ShiftMask,           XK_r,          quit,          {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

unsigned int
nexttagskip(void)
{
	unsigned int seltag = selmon->tagset[selmon->seltags];
	unsigned int usedtags = 0;
	Client *c = selmon->clients;

	if (!c)
		return seltag;

	/* skip vacant tags */
	do {
		usedtags |= c->tags;
		c = c->next;
	} while (c);

	do {
		seltag = seltag == (1 << (LENGTH(tags) - 1)) ? 1 : seltag << 1;
	} while (!(seltag & usedtags));

	return seltag;
}

void
viewnextskip(const Arg *arg)
{
	view(&(const Arg){.ui = nexttagskip()});
}


void
resetnmaster(const Arg *arg)
{
	selmon->nmaster = 1;
	arrange(selmon);
}

