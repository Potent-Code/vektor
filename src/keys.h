/* key definitions
 * by Ryan Lucchese
 * December 29 2011 */

#ifndef keys_h

#ifndef vektor_in_h
#define keys_h
#endif // vektor_in_h

enum
{
	vektor_key_none  = -1,
	
	// function keys
	vektor_key_escape = 0,
	vektor_key_f1,
	vektor_key_f2,
	vektor_key_f3,
	vektor_key_f4,
	vektor_key_f5,
	vektor_key_f6,
	vektor_key_f7,
	vektor_key_f8,
	vektor_key_f9,
	vektor_key_f10,
	vektor_key_f11,
	vektor_key_f12,
	
	// `1234567890-=
	vektor_key_backtick,
	vektor_key_1,
	vektor_key_2,
	vektor_key_3,
	vektor_key_4,
	vektor_key_5,
	vektor_key_6,
	vektor_key_7,
	vektor_key_8,
	vektor_key_9,
	vektor_key_0,
	vektor_key_dash,
	vektor_key_equal,
	vektor_key_backspace,
	
	// 	qwertyuiop[]
	vektor_key_tab,
	vektor_key_q,
	vektor_key_w,
	vektor_key_e,
	vektor_key_r,
	vektor_key_t,
	vektor_key_y,
	vektor_key_u,
	vektor_key_i,
	vektor_key_o,
	vektor_key_p,
	vektor_key_bracketl,
	vektor_key_bracketr,
	vektor_key_backslash,

	// asdfghjkl;'
	vektor_key_caps,
	vektor_key_a,
	vektor_key_s,
	vektor_key_d,
	vektor_key_f,
	vektor_key_g,
	vektor_key_h,
	vektor_key_j,
	vektor_key_k,
	vektor_key_l,
	vektor_key_semicolon,
	vektor_key_quote,
	vektor_key_enter,

	// zxcvbnm,./
	vektor_key_shiftl,
	vektor_key_z,
	vektor_key_x,
	vektor_key_c,
	vektor_key_v,
	vektor_key_b,
	vektor_key_n,
	vektor_key_m,
	vektor_key_comma,
	vektor_key_fullstop,
	vektor_key_slash,
	vektor_key_shiftr,

	// bottom row
	vektor_key_ctrll,
	vektor_key_winl,
	vektor_key_altl,
	vektor_key_space,
	vektor_key_altr,
	vektor_key_winr,
	vektor_key_option,
	vektor_key_ctrlr,

	// middle column
	vektor_key_printscrn,
	vektor_key_scrolllock,
	vektor_key_break,

	vektor_key_insert,
	vektor_key_home,
	vektor_key_pgup,
	vektor_key_delete,
	vektor_key_end,
	vektor_key_pgdn,

	vektor_key_up,
	vektor_key_left,
	vektor_key_down,
	vektor_key_right,

	// numpad
	vektor_key_numlock,
	vektor_key_divide,
	vektor_key_multiply,
	vektor_key_minus,
	vektor_key_plus,
	vektor_key_num_enter,
	vektor_key_decimal,
	vektor_key_num_0,
	vektor_key_num_1,
	vektor_key_num_2,
	vektor_key_num_3,
	vektor_key_num_4,
	vektor_key_num_5,
	vektor_key_num_6,
	vektor_key_num_7,
	vektor_key_num_8,
	vektor_key_num_9,
	
	vektor_key_last,
};

#endif // keys_h
