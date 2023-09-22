/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "jetbrainsmono:size=10" };
static const char dmenufont[]       = "jetbrainsmono:size=10";
static const char col_bg[]       = "#1F1F28";
static const char col_bg_light[]       = "#2A2A37";
static const char col_fg_dark[]       = "#C8C093";
static const char col_fg[]       = "#DCD7BA";
static const char col_hl[]        = "#363646";
static const char col_border[]		= "#C8C093";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_dark, col_bg, col_bg_light },
	[SchemeSel]  = { col_fg, col_hl,  col_border },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "🖵", "♟", "♫" };

static const Rule rules[] = {
	/*		class				instance		title		tags mask		isfloating		moniter */
       { "Gimp",     NULL,       NULL,       0,            1,           -1 },
			 { "Spotify",  NULL,       NULL,      1 << 8,            0,           -1 },
       { "Steam",    NULL,       NULL,      1 << 6,             0,           -1},
};

/* volume keys */
#include <X11/XF86keysym.h>
static const char *upvol[]   = { "amixer", "set", "Master", "5%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "5%-",     NULL };
static const char *mutevol[] = { "amixer", "set",   "Master", "toggle",  NULL };
static const char *light_up[] = {"brillo", "-A", "5", NULL};
static const char *light_down[] = {"brillo", "-U", "5", NULL};
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "float",      NULL },    /* no layout function means floating behavior */
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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "movestack.c"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg_dark, "-sb", col_hl, "-sf", col_fg, NULL };
static const char *j4cmd[] = {"j4-dmenu-desktop", NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *flamshot[] = { "flameshot", "gui", NULL};
static const char *firefox[] = { "firefox", NULL};
static const char *firefoxp[] = { "firefox", "-private-window",  NULL};
static const char *notes[] = { "konsole", "-e", "vifm", "/home/james/Notes", NULL};
static const char *zzz[] = { "zzz", NULL};
static const char *search[] = {"konsole", "-e", "links", "search.brave.com", NULL};
static const char *ZZZ[] = { "ZZZ", NULL};
static const char *passmenu[] = {"passmenu", NULL};
static const char *dolphin[] = {"dolphin", NULL};
static const char *emacs[] = {"emacs", NULL};
static const char *sleeplock[] = {"loginctl", "suspend", "&", "slock", NULL};
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                     XK_p,      spawn,          {.v = j4cmd } },
	{ MODKEY,                     XK_c,      setlayout,      {.v = &layouts[12]}},
	{ MODKEY,                     XK_e,      spawn,          {.v = emacs}},
	{ MODKEY|ShiftMask,                     XK_p,      spawn,          {.v = passmenu} },
	{ 0,              XF86XK_AudioMute, spawn,    {.v = mutevol } },
	{ 0,       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,    XF86XK_MonBrightnessUp,		spawn,	{.v = light_up} },
	{ 0,    XF86XK_MonBrightnessDown,	spawn,	{.v = light_down} },
	{ MODKEY,                       XK_t, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      spawn,          {.v = firefox} },
	{ MODKEY,                       XK_d,      spawn,          {.v = dolphin} },
	{ MODKEY,                       XK_n,      spawn,          {.v = notes} },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = sleeplock} },
	{ MODKEY|ControlMask,           XK_b,      spawn,          {.v = firefoxp} },
	{ MODKEY,                       XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_minus,  defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = flamshot } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

