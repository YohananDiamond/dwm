/* See LICENSE file for copyright and license details. */

#define AltMask Mod1Mask
#define SuperMask Mod4Mask

/* options */
static const unsigned int borderpx       = 1; /* window border size */
static const int gappx		         = 8; /* gaps size */
static const unsigned int snap           = 8; /* snap pixel */
static const int showbar                 = 1; /* 0 means no bar */
static const int topbar                  = 1; /* 0 means bottom bar */
static const unsigned int systraypinning = 0; /* 0 means systray follows selected monitor,
                                                 >0 means systray is in monitor X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1 means that if pinning fails, display systray on the first monitor
                                                 0 makes systray should be displayed on the last monitor */
static const int showsystray             = 1; /* 0 means no systray */

/* theme */
static char *fonts[] = {
	"monospace:size=10",
	"JoyPixels:pixelsize=10:antialias=true:autohint=true",
};

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static char *colors[][3] = {
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] = { selfgcolor, selbgcolor, selbordercolor },
};

/* tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance     title       tags mask     isfloating   monitor */
	{ "float",          NULL,       NULL,           0,            1,           -1 },
	{ "Pavucontrol",    NULL,       NULL,           0,            1,           -1 },
	{ "gnome-pomodoro", NULL,       NULL,           0,            1,           -1 },
	{ NULL,             NULL,       "Event Tester", 0,            1,           -1 },
	{ NULL,             NULL,       "Steam - News", 0,            1,           -1 },
};

/* layout-related */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "<F>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SuperMask,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ SuperMask|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SuperMask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SuperMask|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]) { "/bin/sh", "-c", (cmd), NULL } }

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ SuperMask,                       XK_q,      killclient,     {0} },
	{ SuperMask|ShiftMask|ControlMask, XK_e,      quit,           {0} },
	{ SuperMask|ShiftMask,             XK_b,      togglebar,      {0} },
	{ SuperMask,                       XK_j,      focusstack,     {.i = +1 } },
	{ SuperMask,                       XK_k,      focusstack,     {.i = -1 } },
	{ SuperMask,                       XK_h,      setmfact,       {.f = -0.05} },
	{ SuperMask,                       XK_l,      setmfact,       {.f = +0.05} },
	{ SuperMask|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ SuperMask|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ SuperMask|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ SuperMask|ShiftMask,             XK_k,      movestack,      {.i = -1 } },


	/* layouts: toggles & misc */
	{ SuperMask,                       XK_f,      toggle_fullscreen, {0} },
	{ SuperMask,                       XK_t,      setlayout_default, {0} },
	{ SuperMask|ShiftMask,             XK_space,  toggle_floating,   {0} },

	/* layouts: change */
	/* { SuperMask|ShiftMask,             XK_f,      setlayout,         {.v = &layouts[1] } }, /1* floating *1/ */
	{ SuperMask,                       XK_m,      setlayout,         {.v = &layouts[2] } }, /* monocle */

	/* tagging */
	{ SuperMask,                       XK_0,      view,           {.ui = ~0 } },
	{ SuperMask|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ SuperMask,                       XK_Tab,    view,           {0} },

	/* monitor control */
	{ SuperMask|AltMask,                       XK_k,  focusmon,       {.i = -1 } },
	{ SuperMask|AltMask,                       XK_j, focusmon,       {.i = +1 } },
	{ SuperMask|AltMask|ShiftMask,             XK_k,  tagmon,         {.i = -1 } },
	{ SuperMask|AltMask|ShiftMask,             XK_j, tagmon,         {.i = +1 } },

	{ SuperMask|ShiftMask,             XK_g,	   setgaps,        {.i = -5 } },
	{ SuperMask,                       XK_g,	   setgaps,        {.i = +5 } },
	{ SuperMask|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	/* { SuperMask,						XK_p,	   zoom,           {0} }, */

	/* switch workspaces */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

  /* specials */
	{ SuperMask,                       XK_F5,      key_xrdb,          { .v = NULL } },
	{ SuperMask|ShiftMask|ControlMask, XK_s,       spawn,             SHCMD("start-sxhkd standard") },
	{ SuperMask|ControlMask,           XK_t,       spawn,             SHCMD("st") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask       button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,       {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,       { .v = &layouts[2] } },
	{ ClkWinTitle,          0,                Button2,        zoom,            {0} },
	{ ClkStatusText,        0,                Button2,        spawn,           SHCMD("st") },
	{ ClkClientWin,         SuperMask,           Button1,        movemouse,       {0} },
	{ ClkClientWin,         SuperMask,           Button2,        toggle_floating, {0} },
	{ ClkClientWin,         SuperMask|ShiftMask, Button1,        resizemouse,     {0} },
	/* { ClkClientWin,         SuperMask,          Button3,        resizemouse,     {0} }, */
	{ ClkTagBar,            0,                Button1,        view,            {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,      {0} },
	{ ClkTagBar,            SuperMask,           Button1,        tag,             {0} },
	{ ClkTagBar,            SuperMask,           Button3,        toggletag,       {0} },
};
