/* key definitions
 * by Ryan Lucchese
 * December 29 2011 */

#ifndef keys_h
#define keys_h

#define n_keys 		104

enum
{
	vektor_key_none  = 0,
	
	// function keys
	vektor_key_escape = 1,
	vektor_key_f1     = 2,
	vektor_key_f2     = 3,
	vektor_key_f3     = 4,
	vektor_key_f4     = 5,
	vektor_key_f5     = 6,
	vektor_key_f6     = 7,
	vektor_key_f7     = 8,
	vektor_key_f8     = 9,
	vektor_key_f9     = 10,
	vektor_key_f10    = 11,
	vektor_key_f11    = 12,
	vektor_key_f12    = 13,
	
	// `1234567890-=
	vektor_key_backtick  = 14,
	vektor_key_1         = 15,
	vektor_key_2         = 16,
	vektor_key_3         = 17,
	vektor_key_4         = 18,
	vektor_key_5         = 19,
	vektor_key_6         = 20,
	vektor_key_7         = 21,
	vektor_key_8         = 22,
	vektor_key_9         = 23,
	vektor_key_0         = 24,
	vektor_key_dash      = 25,
	vektor_key_equal     = 26,
	vektor_key_backspace = 27,
	
	// 	qwertyuiop[]
	vektor_key_tab       = 28,
	vektor_key_q         = 29,
	vektor_key_w         = 30,
	vektor_key_e         = 31,
	vektor_key_r         = 32,
	vektor_key_t         = 33,
	vektor_key_y         = 34,
	vektor_key_u         = 35,
	vektor_key_i         = 36,
	vektor_key_o         = 37,
	vektor_key_p         = 38,
	vektor_key_bracketl  = 39,
	vektor_key_bracketr  = 40,
	vektor_key_backslash = 41,

	// asdfghjkl;'
	vektor_key_caps      = 42,
	vektor_key_a         = 43,
	vektor_key_s         = 44,
	vektor_key_d         = 45,
	vektor_key_f         = 46,
	vektor_key_g         = 47,
	vektor_key_h         = 48,
	vektor_key_j         = 49,
	vektor_key_k         = 50,
	vektor_key_l         = 51,
	vektor_key_semicolon = 52,
	vektor_key_quote     = 53,
	vektor_key_enter     = 54,

	// zxcvbnm,./
	vektor_key_shiftl   = 55,
	vektor_key_z        = 56,
	vektor_key_x        = 57,
	vektor_key_c        = 58,
	vektor_key_v        = 59,
	vektor_key_b        = 60,
	vektor_key_n        = 61,
	vektor_key_m        = 62,
	vektor_key_comma    = 63,
	vektor_key_fullstop = 64,
	vektor_key_slash    = 65,
	vektor_key_shiftr   = 66,

	// bottom row
	vektor_key_ctrll    = 67,
	vektor_key_winl     = 68,
	vektor_key_altl     = 69,
	vektor_key_space    = 70,
	vektor_key_altr     = 71,
	vektor_key_winr     = 72,
	vektor_key_option   = 73,
	vektor_key_ctrlr    = 74,

	// middle column
	vektor_key_printscrn  = 75,
	vektor_key_scrolllock = 76,
	vektor_key_break      = 77,

	vektor_key_insert = 78,
	vektor_key_home   = 79,
	vektor_key_pgup   = 80,
	vektor_key_delete = 81,
	vektor_key_end    = 82,
	vektor_key_pgdn   = 83,

	vektor_key_up    = 84,
	vektor_key_left  = 85,
	vektor_key_down  = 86,
	vektor_key_right = 87,

	// numpad
	vektor_key_numlock   = 88,
	vektor_key_divide    = 89,
	vektor_key_multiply  = 90,
	vektor_key_minus     = 91,
	vektor_key_plus      = 92,
	vektor_key_num_enter = 93,
	vektor_key_decimal   = 94,
	vektor_key_num_0     = 95,
	vektor_key_num_1     = 96,
	vektor_key_num_2     = 97,
	vektor_key_num_3     = 98,
	vektor_key_num_4     = 99,
	vektor_key_num_5     = 100,
	vektor_key_num_6     = 101,
	vektor_key_num_7     = 102,
	vektor_key_num_8     = 103,
	vektor_key_num_9     = 104,
};

#endif // keys_h
