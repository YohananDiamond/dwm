/* See LICENSE file for copyright and license details. */

/* options */
static const unsigned int borderpx  = 2;        /* window border size */
static const int gappx		        = 8;        /* gaps size */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* theme */
static const char *fonts[]          = {
	"JetBrains Mono Medium:size=10",
	"JoyPixels:pixelsize=10:antialias=true:autohint=true",
	"monospace:size=10",
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
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "float",    NULL,       NULL,       NULL,         1,           -1 },
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
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", (cmd), NULL } }

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_e,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* layouts: toggles & misc */
	{ MODKEY,                       XK_f,      toggle_fullscreen, {0} },
	{ MODKEY,                       XK_t,      setlayout_default, {0} },
	{ MODKEY|ShiftMask,             XK_space,  toggle_floating,   {0} },

	/* layouts: change */
	/* { MODKEY|ShiftMask,             XK_f,      setlayout,         {.v = &layouts[1] } }, /1* floating *1/ */
	{ MODKEY,                       XK_m,      setlayout,         {.v = &layouts[2] } }, /* monocle */

	/* tagging */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	/* monitor-related */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,             XK_k,	   setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_j,	   setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	{ MODKEY,						XK_p,	   zoom,           {0} },
	{ MODKEY,                       XK_F5,	   xrdb,           {.v = NULL } },

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

        /* shell commands */
	{ MODKEY|ShiftMask|ControlMask, XK_s,       spawn,         SHCMD("start-sxhkd standard") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("st") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        toggle_floating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	/* { ClkTagBar,            0,              Button1,        view,           {0} }, */
	/* { ClkTagBar,            0,              Button3,        toggleview,     {0} }, */
	/* { ClkTagBar,            MODKEY,         Button1,        tag,            {0} }, */
	/* { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, */
};
