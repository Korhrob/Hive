#include <stdio.h>
#include "list.h"
#include <limits.h>

static int move_count; // debug
static int possible_save; // debug
static int saved; // debug

#define ABS(x)(x >= 0 ? x : -x)

typedef struct s_cost {
	int	a_cost;
	int b_cost;
	int total;
	int discount;
} t_cost;

typedef struct s_info {
	int a_count;
	int b_count;
	int b_highest;
	int b_smallest;
} t_info;

// sa, sb, ss - swap first two elements
void	swap_first(t_list** list) {
	t_list* first;
	t_list* second;

	first = *list;
	second = first->next;
	if (first == 0 || second == 0)
		return;
	first->next = second->next;
	second->next = first;
	*list = second;
}

// pa pb - remove first element of src and put it on top of dst
void	push_first(t_list** src, t_list** dst) {
	t_list* top;

	if (*src == 0)
		return;
	top = list_remove_first(src);
	list_add_first(dst, top);
}

// ra rb rr - shift up all elements
void	rotate_up(t_list** list) {
	t_list* top;
	
	if (*list == 0)
		return;
	top = list_remove_first(list);
	list_add_last(list, top);
}

// rra rrb rrr - shift down all elements
void	rotate_down(t_list** list) {
	t_list* bot;

	if (*list == 0)
		return;
	bot = list_remove_last(list);
	list_add_first(list, bot);
}

void rotate_stack_up_single(t_list** list, int i) {
	while (i > 0) {
		rotate_up(list);
		i--;
		move_count++; // debug
	}
}

void rotate_stack_down_single(t_list** list, int i) {
	while (i < 0) {
		rotate_down(list);
		i++;
		move_count++; // debug
	}
}

void	rotate_stack_up(t_list** a, t_list** b, t_cost best) {
	while (best.a_cost > 0 && best.b_cost > 0) {
		printf("rr\n");
		rotate_up(a);
		rotate_up(b);
		best.a_cost--;
		best.b_cost--;
		move_count++; // debug
	}
	rotate_stack_up_single(a, best.a_cost);
	rotate_stack_up_single(b, best.b_cost);
}

void	rotate_stack_down(t_list** a, t_list** b, t_cost best) {
	while (best.a_cost < 0 && best.b_cost < 0) {
		printf("rrr\n");
		rotate_down(a);
		rotate_down(b);
		best.a_cost++;
		best.b_cost++;
		move_count++; // debug
	}
	rotate_stack_down_single(a, best.a_cost);
	rotate_stack_down_single(b, best.b_cost);
}

// return cost when rotating down instead of up (median)
int inverted_cost(int count, int index) {
	int invert;
	
	invert = (count - index);
	if (ABS(invert) < ABS(index))
		return (-invert);
	return (index);
}

// calculates how many moves are saved when using rr / rrr instead of ra + rb
int	combined_cost(int ra, int rb) {
	int total;

	total = 0;
	while (ra > 0 && rb > 0) {
		ra--;
		rb--;
		total++;
	}
	while (ra < 0 && rb < 0) {
		ra++;
		rb++;
		total++;
	}
	total += ABS(ra) + ABS(rb);
	return (total);
}

//final move count : ~5127
void	sort(t_list** a, t_list** b) { // rename to stack_a and stack_b
	t_list* cur_a; // rename to a
	t_list* cur_b; // rename to b

	t_cost temp;
	t_cost cost;
	t_cost best;

	t_info info;

	// can compress to t_info
	int b_smallest;
	int b_largest;

	int a_count;
	int b_count;

	a_count = list_count(a);
	b_count = list_count(b);
	b_smallest = list_smallest(b);
	b_largest = list_largest(b);
	
	// force insert 2, can move elsewhere
	if (list_count(b) < 2) {

		printf("pb\n");
		push_first(a, b);
		move_count++;
		return;

	}

	cur_a = *a;
	temp = (t_cost){ 0, 0, 0 };
	cost = (t_cost){ 0, 0, 0 };
	best = (t_cost){ INT_MAX, INT_MAX, INT_MAX };

	while (cur_a != 0) {
		
		cur_b = *b;
		cost.b_cost = 0;
		int prev_b = list_last(b);

		// Inverted A cost (median)
		// High saves

		temp.discount = 0;
		temp.a_cost = inverted_cost(a_count, cost.a_cost);

		while (cur_b != 0) {

			temp.b_cost = cost.b_cost;

			if ((cur_a->data < prev_b && cur_a->data > cur_b->data)
				|| (cur_a->data < b_smallest && cur_b->data == b_largest)
				|| (cur_a->data > b_largest && cur_b->data == b_largest)) {

				// Discount A: two good numbers in a row fit well gives bonus value for this move
				// saves : minimal, infact sometimes ends up costing more in the end

				if (cur_a->next != 0) {

					if (cur_a->next->data > cur_a->data && cur_a->next->data < prev_b)
						temp.discount++;

				}

				// Inverted B cost (median)
				// saves : high

				temp.b_cost = inverted_cost(b_count, temp.b_cost);

				// Discount B: for both goin in the same direction, decent saves
				// saves : medium

				temp.total = combined_cost(temp.a_cost, temp.b_cost);

				if (temp.total < best.total
					|| (temp.total == best.total && temp.discount > best.discount)) { 

					// temp.discount < best.discount
					// sometimes gives better results when avoiding the "good moves"
					// maybe cause saving good moves = potentially even more good moves later ?

					best.a_cost = temp.a_cost;
					best.b_cost = temp.b_cost;
					best.total = temp.total;
					best.discount = temp.discount;

				}

				// Could calculate next move cost after this move if lists were rotated to this position (recursion)
				// Potential saves : overkill

			}

			cost.b_cost++;
			prev_b = cur_b->data;
			cur_b = cur_b->next;

		}

		cost.a_cost++;
		cur_a = cur_a->next;

	}

	// actual sorting

	possible_save += best.discount;
	printf("best cost A: (%d) + B: (%d) + pb(1), total: %d, discount %d\n", best.a_cost, best.b_cost, best.total + 1, best.discount);

	rotate_stack_up(a, b, best);
	rotate_stack_down(a, b, best);

	printf("pb\n");
	push_first(a, b);
	move_count++;

}

// returns true/false
int	is_sorted(t_list** list) {
	t_list* prev;
	t_list* cur;

	prev = *list;
	cur = prev->next;

	while (cur != 0) {

		if (cur->data < prev->data)
			return (0);

		prev = cur;
		cur = cur->next;
	}
	return (1);
}

int main() {

	// debug
	move_count = 0;
	possible_save = 0;
	saved = 0;

	int test[] = { 509, 567, 148, 989, 964, 954, 444, 502, 935, 190, 685, 743, 487, 867, 98, 605, 9, 859, 448, 967, 416, 380, 160, 177, 83, 979, 869, 814, 882, 805, 573, 503, 917, 933, 165, 940, 966, 691, 656, 606, 898, 689, 341, 629, 648, 977, 599, 651, 6, 372, 279, 568, 945, 486, 827, 875, 658, 368, 597, 788, 415, 85, 764, 884, 952, 865, 104, 768, 793, 895, 59, 351, 67, 431, 164, 460, 960, 383, 90, 209, 845, 578, 971, 81, 92, 927, 101, 370, 276, 94, 982, 915, 113, 517, 254, 41, 836, 355, 821, 127, 442, 773, 871, 472, 117, 889, 727, 655, 562, 432, 846, 614, 993, 96, 3, 774, 877, 735, 78, 496, 399, 421, 116, 514, 549, 152, 227, 278, 837, 883, 693, 21, 121, 506, 166, 505, 170, 518, 69, 844, 118, 699, 723, 433, 500, 79, 8, 850, 471, 103, 120, 783, 492, 548, 824, 334, 997, 50, 426, 537, 665, 234, 916, 396, 453, 797, 577, 75, 523, 604, 212, 149, 357, 201, 795, 361, 594, 588, 939, 247, 389, 248, 295, 984, 504, 937, 640, 701, 542, 52, 660, 554, 259, 274, 776, 702, 938, 622, 410, 551, 222, 198, 692, 534, 631, 558, 817, 681, 141, 294, 308, 661, 931, 445, 134, 305, 983, 437, 789, 682, 920, 953, 775, 329, 733, 151, 637, 395, 462, 143, 767, 467, 760, 100, 281, 560, 543, 922, 345, 708, 868, 528, 919, 478, 207, 948, 72, 711, 129, 65, 124, 896, 890, 137, 930, 796, 618, 759, 468, 559, 366, 306, 371, 941, 70, 155, 443, 452, 126, 475, 38, 489, 893, 440, 586, 771, 273, 299, 833, 841, 133, 986, 400, 193, 992, 947, 818, 321, 550, 923, 42, 913, 359, 66, 470, 925, 593, 71, 44, 643, 238, 131, 621, 855, 161, 189, 360, 742, 571, 323, 263, 946, 547, 570, 663, 880, 683, 409, 738, 82, 236, 713, 132, 257, 167, 950, 269, 734, 13, 37, 434, 772, 739, 623, 677, 697, 476, 522, 575, 181, 272, 23, 245, 912, 580, 791, 265, 376, 610, 390, 310, 378, 668, 114, 210, 425, 140, 864, 838, 806, 638, 186, 404, 162, 174, 819, 1000, 627, 616, 753, 976, 936, 799, 362, 904, 293, 86, 816, 630, 726, 54, 872, 555, 290, 2, 944, 318, 955, 965, 756, 266, 911, 195, 168, 512, 662, 58, 346, 676, 620, 628, 196, 645, 659, 115, 625, 493, 110, 962, 918, 466, 540, 792, 712, 213, 385, 763, 88, 182, 220, 226, 284, 89, 839, 673, 55, 479, 675, 319, 304, 921, 388, 688, 538, 477, 972, 636, 252, 902, 171, 847, 885, 224, 943, 474, 406, 887, 900, 853, 959, 527, 715, 57, 147, 624, 119, 311, 974, 309, 741, 344, 364, 192, 268, 802, 403, 879, 732, 991, 322, 981, 312, 414, 751, 762, 256, 718, 830, 804, 709, 200, 93, 419, 313, 928, 205, 690, 199, 237, 261, 724, 790, 585, 863, 324, 510, 446, 603, 980, 494 };
	//int test[] = { 794, -581, -590, -907, 834, 905, -627, -857, 902, -154, -534, -837, 616, 58, -656, 201, 679, 782, -5, 52, 425, 155, -730, -818, -228, 520, -153, -474, 190, 70, 806, -371, -36, -696, 12, 506, 173, 290, -389, 1, 847, 246, -138, -643, -486, -720, -500, -738, -613, 9, -68, 227, -95, -199, -269, -218, 797, 289, 789, -746, -12, -436, -105, 927, 272, 141, 8, -79, 586, -451, 55, -769, -470, -570, 449, 799, -588, 826, -936, 377, 819, -150, 186, 935, -219, 275, -791, 325, -259, 26, 696, -809, 124, -367, -203, -520, 928, 237, 252, -635, 142, 589, 809, 987, 384, -606, -526, 544, -89, 123, -805, 51, -287, -614, -975, -602, 689, 708, -30, 951, 57, -699, -535, -543, 824, 468, -604, -917, 885, -466, -745, 963, 426, 44, -187, 752, 543, 999, -281, -740, 457, -735, 540, 144, -981, 214, -339, -876, 353, 306, -683, -529, 720, 136, 726, -525, 79, -658, 598, 167, -234, -429, -697, 900, 577, -725, 599, -260, -506, 839, -998, 463, 367, 600, 823, 636, -958, -372, 813, -137, 406, 18, -418, -554, 947, -976, -350, 189, -533, 335, 555, 818, 832, 968, -527, -991, 287, -188, 749, -826, -457, -251, 258, -220, -649, -143, 511, 415, -507, 573, -835, -557, -667, -197, -484, 803, 798, 274, 761, -497, -854, 576, -277, 318, -619, 651, 948, -988, 341, -709, 502, -32, 208, 705, 128, -849, 169, -548, 268, -795, 667, -195, 433, 43, -980, -894, 140, -847, -785, -858, -407, -820, -764, -956, -313, 313, -136, -311, -977, -424, -513, 453, 703, 920, 959, -292, 349, 35, -817, -645, 76, 495, -721, 198, -214, 664, 439, -874, 814, -461, 125, 80, -171, -13, -763, 357, -303, 131, -333, -293, -489, -668, -390, -499, -566, -175, 249, 508, 251, -629, 464, -215, -684, 535, -712, 271, 644, 422, -957, 915, -718, 672, -363, -681, 139, 23, 602, -582, 88, 567, 103, 528, -387, -158, -498, -396, -45, -448, 59, -974, 462, -868, 477, -64, -758, -394, -258, -439, -773, 575, -592, -926, 286, 176, 28, 979, 743, 156, 866, 650, -633, -770, -717, -398, -731, -599, 54, -256, 811, -949, 721, -903, 717, 773, 909, 361, 497, 601, -46, -81, 697, -836, 640, 634, -61, 603, 993, -425, 182, 168, -928, 405, 533, -427, 924, -734, 398, 658, -412, 731, -744, -669, -41, -182, 893, 110, 545, 489, -124, 954, -812, -867, -752, -955, -578, -7, -700, 966, 29, -555, 431, 804, -887, -212, -432, 296, -355, -811, -201, 263, -176, 848, -230, -618, 419, 225, 111, 879, -532, -843, -222, 473, 755, 308, 608, -595, -810, -401, -450, -170, 498, 843, -117, 891, -610, 231, 485, -672, -275, 735, -438, 790, 929, 934, 264, -553, 352, -66, -80, -122, 403, -671, 873, 38, -732, 135, 763, -123, 677, -442, -148, 860, -931, -488, -971, 222, -250, 459, 408, -445, 684, -514, -198, -594, -967, -345, -221, 446, -301, 133, 304, -896, 760, -771, 503, 626, -404, -573, -654, 223 };
	int test_size = 500; 

	t_list** stack_a;
	t_list** stack_b;

	stack_a = malloc(sizeof(t_list*));
	stack_b = malloc(sizeof(t_list*));
	*stack_a = 0;
	*stack_b = 0;

	for (int i = 0; i < test_size; i++) {
		
		// check for duplicates in list

		t_list* element = list_new(test[i]);
		list_add_last(stack_a, element);

	}

	list_print_both(stack_a, stack_b);

	// sort

	while (1) {

		// could stop at 3 and do small sort on a, minimal gains but something
		if (list_count(stack_a) <= 0)
			break;

		sort(stack_a, stack_b);
		//list_print_both(stack_a, stack_b);

	}

	// push highest first, but check which way is least moves (median)

	int b_largest = list_largest(stack_b);
	int highest_index = list_index_of(stack_b, b_largest);

	int inverted_index = (list_count(stack_b) - highest_index);

	if (inverted_index < highest_index)
		highest_index = -inverted_index;

	while (highest_index > 0) {

		printf("rb\n");
		rotate_up(stack_b);
		highest_index--;

	}

	while (highest_index < 0) {

		printf("rrb\n");
		rotate_down(stack_b);
		highest_index++;

	}

	// move back to stack_a

	for (int i = 0; i < test_size; i++) {

		printf("pa\n");
		push_first(stack_b, stack_a);
		move_count++;

	}

	list_print_both(stack_a, stack_b);

	printf("final move count : %d, potential saves from discount %d\n", move_count, possible_save);

	if (is_sorted(stack_a))
		printf("stack_a is sorted");
	else
		printf("stack_a IS NOT SORTED!");

	list_free(stack_a);
	list_free(stack_b);

	return (0);
}

// mini optimization
// push all but 3 to stack_b
// mini sort stack_a
// sort stack_b into stack_a
// rotate stack_a into correct position